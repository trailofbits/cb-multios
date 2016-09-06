/*
 * Copyright (c) 2016 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdint.h>
#include <cstdio.h>
#include <cstdlib.h>
#include <cstring.h>
#ifdef DEBUG
#define dbg(s, ...) fprintf(stderr, "DEBUG:\t" s "\n", ##__VA_ARGS__)
#else
#define dbg(s, ...)
#endif
#define err(s, ...) ({ \
    fprintf(stderr, "ERROR:\t" s "\n", ##__VA_ARGS__); \
    exit(1); \
})
#define assert(__x) ({ \
    if (!(__x)) err("failed assertion"); \
})
#define min(__x, __y) (__x) < (__y) ? (__x) : (__y)
#define BUFFER_SZ 0x1000
typedef ssize_t off_t;
typedef uint32_t buffer_id_t;
typedef enum
{
  RDONLY = 1 << 0,
  RDWR   = 1 << 1,
  TRUNC  = 1 << 2,
  APPEND = 1 << 3,
} open_flags_t;
template<typename T>
class ArrayList
{
  private:
    static const size_t default_capacity_ = 1024;
    size_t capacity_;
    size_t length_;
    T** array_;
  public:
    ArrayList(void)
    {
      capacity_ = default_capacity_;
      length_ = 0;
      array_ = new T*[default_capacity_];
    }
    ~ArrayList(void)
    {
      delete array_;
    }

    int Append(T* value)
    {
      if (!value)
      {
        err("Appended nullptr");
      }

      array_[length_++] = value;

      if (length_ == capacity_)
      {
        capacity_ *= 2;
        array_ = static_cast<T**>(realloc(array_, sizeof(T *) * capacity_));
      }

      return 0;
    }

    T* Get(size_t index)
    {
      if (index >= length_)
      {
        err("Bad get: %d", (int)index);
      }

      return array_[index];
    }

    T* Last(void)
    {
      if (length_ < 1)
      {
        return nullptr;
      }

      return array_[length_ - 1];
    }

    T* RemoveByValue(T* elem)
    {
      for (size_t i = 0; i < length_; ++i)
      {
        if (array_[i] == elem)
        {
          return RemoveByIndex(i);
        }
      }

      return nullptr;
    }

    T* RemoveByIndex(size_t idx)
    {
      if (idx >= length_)
      {
        return nullptr;
      }

      T* removed = array_[idx];
      array_[idx] = nullptr;

      for (size_t i = idx; i < length_ - 1; ++i)
      {
        array_[i] = array_[i + 1];
      }

      array_[length_ -  1] = nullptr;
      length_--;

      return removed;
    }

    size_t Size()
    {
      return length_;
    }
};

class Buffer
{
  public:
    uint8_t data[BUFFER_SZ];
    static uint32_t counter;
    buffer_id_t id;
    uint32_t left_;
    bool free_;

    void MarkUsed(void);
    void MarkFree(void);

    Buffer(void)
    {
      id = counter++;
      left_ = BUFFER_SZ;
      free_ = true;
    }

    size_t Size(void)
    {
      return BUFFER_SZ - left_;
    }

    int SetContents(uint8_t* bytes, size_t offset, size_t len)
    {
      if (len > BUFFER_SZ - offset)
      {
        return -1;
      }

      memcpy(data + offset, bytes, len);
      if (BUFFER_SZ - offset - len < left_)
      {
        left_ = BUFFER_SZ - offset - len;
      }

      return 0;
    }
};

class BufferCache
{
#define NUM_BUFS 32
#define NUM_QS 32
  private:
    ArrayList<Buffer>* Queues_[NUM_QS];
    ArrayList<Buffer>* Free_;

  public:
    BufferCache(void)
    {
      for (size_t i = 0; i < NUM_QS; ++i)
      {
        Queues_[i] = new ArrayList<Buffer>();
      }

      Free_ = new ArrayList<Buffer>();
      AllocateMore();
    }

    Buffer* GetFree(void)
    {
      if (!Free_->Size())
      {
        AllocateMore();
      }

      Buffer* B = Free_->Get(0);
      Free_->RemoveByIndex(0);
      return B;
    }

    void AllocateMore(void)
    {
      for (size_t i = 0; i < NUM_BUFS; ++i)
      {
        Free_->Append(new Buffer());
      }
    }

    size_t FreeLeft(void)
    {
      return Free_->Size();
    }

    void AddFree(Buffer* B)
    {
      B->MarkFree();
      Free_->Append(B);
    }

    void MarkUsed(Buffer* B)
    {
      Free_->RemoveByValue(B);
      auto q = Queues_[B->id % NUM_QS];
      q->Append(B);
    }

    void MarkFree(Buffer* B)
    {
      return;
    }

    Buffer* Get(uint32_t id)
    {
      size_t idx = id % NUM_QS;
      auto q = Queues_[idx];
      for(size_t i = 0; i < q->Size(); ++i)
      {
        if (q->Get(i)->id == id)
        {
          return q->Get(i);
        }
      }

      return nullptr;
    }
};


uint32_t Buffer::counter = 0;
static BufferCache* BCache = new BufferCache();

void Buffer::MarkFree(void)
{
  free_ = true;
  left_ = BUFFER_SZ;
  BCache->MarkFree(this);
}

void Buffer::MarkUsed(void)
{
  free_ = false;
  BCache->MarkUsed(this);
}

class Chunk
{
  private:
    size_t len_;
    uint8_t* bytes_;
  public:
    Chunk(uint8_t* bytes, size_t len)
    {
      len_ = len;
      bytes_ = (uint8_t*)calloc(sizeof(uint8_t), len);
      memcpy(bytes_, bytes, len);
    }

    ~Chunk(void)
    {
      delete bytes_;
    }

    size_t Size(void)
    {
      return len_;
    }

    uint8_t* operator[](const size_t idx)
    {
      return bytes_ + idx;
    }
};

class BytesReader
{
  private:
    size_t index_;
    Chunk* chunk_;

  public:
    BytesReader(uint8_t* bytes, size_t len)
    {
      chunk_ = new Chunk(bytes, len);
      index_ = 0;
    }

    ~BytesReader(void)
    {
      delete chunk_;
    }

    size_t Size(void)
    {
      return chunk_->Size() - index_;;
    }

    bool Empty(void)
    {
      return index_ >= chunk_->Size();
    }

    uint8_t Read(void)
    {
      if (index_ >= chunk_->Size())
      {
        return 0;
      }

      return *(*chunk_)[index_++];
    }

    uint8_t* ReadN(size_t len, bool is_str = false)
    {
      if (index_ + len > chunk_->Size())
      {
        return nullptr;
      }

      uint8_t* ret = nullptr;

      if (!is_str)
      {
        ret = (*chunk_)[index_];
      }
      else
      {
        ret = new uint8_t(len + 1);
        memcpy(ret, (*chunk_)[index_], len);
        ret[len] = '\x00';
      }

      index_ += len;

      return ret;
    }
};

class Response
{
#define MAX_RESP_SZ (32 * 1024)
  private:
    enum {
      STATUS_OK = 1,
      STATUS_ERR,
    };

  public:
    int Status;
    size_t Length;
    uint8_t Bytes[MAX_RESP_SZ];

    Response(void)
    {
      Status = STATUS_ERR;
      Length = 0;
    }

    void SetOK(void)
    {
      Status = STATUS_OK;
    }

    int Append(uint8_t* bytes, size_t len)
    {
      if (Length + len >= MAX_RESP_SZ)
      {
        return -1;
      }

      memcpy(Bytes + Length, bytes, len);
      Length += len;

      return 0;
    }
};

class Request
{
  private:
    uint32_t f_num_;
    uint32_t size_;
    uint8_t* data_;

  public:
    Request(uint8_t n, uint32_t size, uint8_t* data)
    {
      size_ = size;
      f_num_ = n;
      data_ = data;
      assert(data_);
    }

    uint8_t Num(void)
    {
      return f_num_;
    }

    uint32_t Size(void)
    {
      return size_;
    }

    uint8_t* Data(void)
    {
      return data_;
    }
};

template<typename T>
class Pair
{
  public:
    T fst;
    T snd;

    Pair(T fst, T snd) : fst(fst), snd(snd) {}
};


class Pathname
{
  private:
    static const uint8_t seperator = '/';

    size_t size_;
    uint8_t* data_;
    ArrayList<Pair<size_t>>* components_ = new ArrayList<Pair<size_t>>();


  public:
    Pathname(const char* pathname)
    {
      size_ = strlen((char *)pathname);
      size_t i;
      size_t start;

      data_ = new uint8_t[size_ + 1];
      memcpy(data_, pathname, size_);
      start = i = 0;
      for (;i < size_; ++i)
      {
        if (pathname[i] == seperator)
        {
          if (i > start)
          {
            components_->Append(new Pair<size_t>(start, i));
          }

          while (pathname[i] == seperator)
          {
            i++;
          }

          start = i;
        }
      }

      if (i == size_ && i > start)
      {
        components_->Append(new Pair<size_t>(start, i));
      }
    }

    const char* Get(size_t index)
    {
      Pair<size_t>* p =  components_->Get(index);
      char* cpy = new char[p->snd - p->fst + 1];
      memcpy(cpy, data_ + p->fst, p->snd - p->fst);
      cpy[p->snd - p->fst] = '\0';
      return cpy;
    }

    char* AsString(void)
    {
      char* s = new char[size_ + 1];
      memcpy(s, data_, size_);
      s[size_] = '\0';
      return s;
    }

    size_t Size()
    {
      return components_->Size();
    }
};

class File
{
  private:
    ArrayList<buffer_id_t> buffers_;
    size_t ref_cnt_;

  public:
    const char* name;
    File(const char* path)
    {
      name = path;
      ref_cnt_ = 0;
    }

    ~File(void)
    {
      for (size_t i = 0; i < buffers_.Size(); ++i)
      {
        auto A = buffers_.Get(i);
        auto B = BCache->Get(*A);
        BCache->AddFree(B);
      }
    }

    bool operator ==(const File &b) const
    {
      return strcmp(name, b.name) == 0;
    }

    virtual size_t Size(void)
    {
      size_t ret = 0;
      for (size_t i = 0; i < buffers_.Size(); ++i)
      {
        ret += BCache->Get(*buffers_.Get(i))->Size();
      }

      return ret;
    }

    int IncRef(void)
    {
      ref_cnt_++;
      return 0;
    }

    int DecRef(void)
    {
      ref_cnt_--;
      return 0;
    }

    virtual int RefCnt(void)
    {
      return ref_cnt_;
    }

    int Write(uint8_t* bytes, size_t offset, size_t len)
    {
      if (!bytes)
      {
        return -1;
      }

      size_t cnt = 0;
      size_t buf = 0;
      size_t cpy = 0;

      if (offset)
      {
        buf = offset / BUFFER_SZ;
      }

      size_t req_buffs = (len + (BUFFER_SZ - 1)) / BUFFER_SZ;
      size_t cur_buffs = buffers_.Size();
      size_t offset_in_bufs = offset / BUFFER_SZ;
      size_t n_new_buffs = 0;
      if (req_buffs + offset_in_bufs > cur_buffs)
      {
        n_new_buffs = req_buffs - cur_buffs + offset_in_bufs;
      }

      if (BCache->FreeLeft() < n_new_buffs)
      {
        BCache->AllocateMore();
      }

      Buffer* bufp;
      while (cnt < len)
      {
        if (buf >= buffers_.Size())
        {
          bufp = BCache->GetFree();
          bufp->MarkUsed();
          buffers_.Append(&bufp->id);
        }
        else
        {
          bufp = BCache->Get(*buffers_.Get(buf));
        }

        if (offset && buf == (offset / BUFFER_SZ))
        {
          cpy = min(len, BUFFER_SZ - (offset % BUFFER_SZ));
          if (bufp->SetContents(bytes + cnt, offset % BUFFER_SZ, cpy) != 0)
          {
            err("Bad buffer write");
          }
        }
        else
        {
          cpy = min((len - cnt), BUFFER_SZ);
          if (bufp->SetContents(bytes + cnt, 0, cpy) != 0)
          {
            err("Bad buffer write");
          }
        }

        cnt += cpy;
        buf++;
      }

      return 0;
    }

    int Read(uint8_t* bytes, size_t offset, size_t len)
    {
      if (!bytes || len + offset > Size())
      {
        return -1;
      }

      size_t cnt = 0;
      size_t buf = 0;
      size_t cpy = 0;

      if (offset)
      {
        buf = offset / BUFFER_SZ;
      }

      while (cnt < len)
      {
        auto buf_idx = buffers_.Get(buf);
        auto bufp = BCache->Get(*buf_idx);

        if (offset && buf == (offset / BUFFER_SZ))
        {
          cpy = min(len, BUFFER_SZ - (offset % BUFFER_SZ));
          memcpy(bytes + cnt, bufp->data + (offset % BUFFER_SZ), cpy);
        } else {
          cpy = min((len - cnt), BUFFER_SZ);
          memcpy(bytes + cnt, bufp->data, cpy);
        }

        cnt += cpy;
        buf++;
      }

      return 0;
    }
};

template<typename L, typename R>
class Either
{
  private:
    bool is_left_;
  public:
    L* l;
    R* r;

    Either(L* left = nullptr, R* right = nullptr)
    {
      if (left && right)
      {
        err("Either can't be both");
      }

      l = left;
      r = right;
      if (left)
      {
        is_left_ = true;
      }
      else
      {
        is_left_ = false;
      }
    }

    ~Either(void)
    {
      if (l)
      {
        delete l;
      }

      if (r)
      {
        delete r;
      }
    }

    bool IsLeft(void)
    {
      return is_left_;
    }
};

class DirTree
{
  public:
    ArrayList<Either<DirTree, File>> children;
    const char* name;

    DirTree(const char* n)
    {
      name = n;
    }

    Either<DirTree, File>* Search(const char* s)
    {
      for (size_t i = 0; i < children.Size(); i++)
      {
        auto E = children.Get(i);
        if (E->IsLeft())
        {
          if (strcmp(E->l->name, s) == 0)
          {
            return E;
          };
        }
        else
        {
          if (strcmp(E->r->name, s) == 0)
          {
            return E;
          }
        }
      }
      return nullptr;
    }
};



class FileHandle
{
  public:
    File& file_;
    off_t offset_;
    open_flags_t flags_;

  FileHandle(File& file, open_flags_t flags) : file_(file), flags_(flags)
  {
    file.IncRef();
    if (flags & APPEND)
    {
      offset_ = file_.Size();
    }
    else
    {
      offset_ = 0;
    }
  }

  ~FileHandle(void)
  {
    file_.DecRef();
  }

  int Read(uint8_t* bytes, size_t len)
  {
    if (file_.Read(bytes, offset_, len) != 0)
    {
      err("Bad fh read");
    }

    offset_ += len;
    return len;
  }

  size_t Size(void)
  {
    return file_.Size();
  }

  int Write(uint8_t* bytes, size_t len)
  {
    if (flags_ & RDONLY)
    {
      return -1;
    }

    if (file_.Write(bytes, offset_, len) != 0)
    {
      err("Bad fh write");
    }

    offset_ += len;
    return len;
  }
};

auto Root = DirTree(nullptr);

#define MAX_FDS 1024
FileHandle* UserFDs[MAX_FDS];

int api_open(const char* pathname, open_flags_t flags, uint32_t mode)
{
  dbg("Called open(%s, %x, %x)", pathname, flags, mode);
  int fd = -1;

  if (flags & RDONLY && flags & RDWR)
  {
    return -1;
  }

  if (flags & TRUNC && flags & APPEND)
  {
    return -1;
  }

  if (flags & RDONLY)
  {
    flags = (open_flags_t)(RDONLY | TRUNC);
  }

  if (!(flags & TRUNC || flags & APPEND))
  {
    flags = (open_flags_t)(flags | APPEND);
  }

  if (!(flags & RDONLY || flags & RDWR))
  {
    flags = (open_flags_t)(flags | RDONLY);
  }

  auto node = new Either<DirTree, File>(&Root, nullptr);
  auto pn = new Pathname(pathname);

  for (size_t i = 0; i < pn->Size(); ++i)
  {
    if (node && node->IsLeft())
    {
      node = node->l->Search(pn->Get(i));
    }
    else
    {
      goto done;
    }
  }

  if (!node || node->IsLeft() || strcmp(node->r->name, pn->Get(pn->Size() - 1)) != 0)
  {
    goto done;
  }

  size_t i;
  for (i = 0; i < MAX_FDS; ++i)
  {
    if (UserFDs[i] == nullptr)
    {
      break;
    }
  }

  if (i == MAX_FDS)
  {
    goto done;
  }
  UserFDs[i] = new FileHandle(*node->r, flags);
  fd = i;

done:
  return fd;
}

ssize_t api_read(int fd, uint8_t* buffer, size_t count)
{
  if (fd >= MAX_FDS)
  {
    return -1;
  }

  FileHandle* FH = UserFDs[fd];
  if (!FH)
  {
    return -1;
  }

  if (count > FH->Size() - FH->offset_)
  {
    return -1;
  }

  return FH->Read(buffer, count);
}


ssize_t api_write(int fd, uint8_t* buffer, size_t count)
{
  if (fd >= MAX_FDS)
  {
    return -1;
  }

  FileHandle* FH = UserFDs[fd];

  if (!FH)
  {
    return -1;
  }

  return FH->Write(buffer, count);
}

off_t api_lseek(int fd, off_t offset, int whence)
{
  dbg("Called lseek(%d, %u, %d)", fd, offset, whence);
  off_t position = -1;

#define SEEK_SET  0
#define SEEK_CUR  1
  if (fd >= MAX_FDS)
  {
    return -1;
  }

  FileHandle* FH = UserFDs[fd];

  if (!FH)
  {
    return -1;
  }

  if (whence == SEEK_SET)
  {
    if (offset >= FH->Size())
    {
      return -1;
    }

    FH->offset_ = offset;
    position = FH->offset_;
  }
  else if (whence == SEEK_CUR)
  {
    if (offset + FH->offset_ >= FH->Size())
    {
      return -1;
    }

    FH->offset_ += offset;
    position = FH->offset_;
  }

  return position;
}

int api_close(int fd)
{
  dbg("Called close(%d)", fd);
  int ret = 0;
  if (fd >= MAX_FDS)
  {
    return -1;
  }

  FileHandle* FH = UserFDs[fd];

  if (!FH)
  {
    return -1;
  }

  UserFDs[fd] = nullptr;
  delete FH;
  return ret;
}

#define MAKE_PARENTS (1 << 1)
int api_creat(const char* pathname, int mode)
{
  int ret = -1;

  if (pathname && pathname[0] != '/')
  {
    return -1;
  }

  dbg("Called create(%s, %d)", pathname, mode);
  auto pn = Pathname(pathname);
  auto node = new Either<DirTree, File>(&Root);
  File* f = nullptr;

  for (size_t i = 0; i < pn.Size() - 1; ++i)
  {
    auto x = pn.Get(i);
    if (node->IsLeft())
    {
      auto old = node;
      node = node->l->Search(x);
      if (!node)
      {
        node = old;
        if (mode & MAKE_PARENTS)
        {
          auto new_node = new Either<DirTree, File>(new DirTree(x));
          node->l->children.Append(new_node);
          node = new_node;
        }
        else
        {
          goto done;
        }
      }
    }
    else
    {
      goto done;
    }
  }

  if (!node->IsLeft())
  {
    return -1;
  }

  for (size_t i = 0; i < node->l->children.Size(); ++i)
  {
    auto name = pn.Get(pn.Size() -1);
    auto c = node->l->children.Get(i);
    if (c->IsLeft())
    {
      if (strcmp(c->l->name, name) == 0)
      {
        goto done;
      }
    }
    else
    {
      if (strcmp(c->r->name, name) == 0)
      {
        goto done;
      }
    }
  }

  f = new File(pn.Get(pn.Size() - 1));
  node->l->children.Append(new Either<DirTree, File>(nullptr, f));
  ret = 0;

done:
  return ret;
}

int api_unlink(const char* pathname)
{
  dbg("Called unlink(%s)", pathname);

  int ret = -1;

  DirTree* dir;
  auto pn = Pathname(pathname);
  auto node = new Either<DirTree, File>(&Root);
  File* f = nullptr;

  for (size_t i = 0; i < pn.Size(); ++i)
  {
    auto x = pn.Get(i);
    if (node->IsLeft())
    {
      dir = node->l;
      node = node->l->Search(x);
      if (!node)
      {
        goto done;
      }
    }
    else
    {
      goto done;
    }
  }

  if (!node->IsLeft())
  {
    f = node->r;
#ifdef PATCHED_1
    if (f->RefCnt() < 1)
#else
    if (f->RefCnt() <= 1)
#endif
    {
      auto x = dir->children.RemoveByValue(node);
      delete x;
      ret = 0;
    }
  }

done:
 return ret;
}

int load_req(FILE* fd, Request** req)
{
  uint32_t f_num;
  uint32_t size;
  *req = nullptr;

  if (fread(&f_num, sizeof(f_num), fd) != sizeof(f_num))
  {
    return -1;
  }

  // Check for done signal
  if (f_num == 0xb7eb7e)
  {
    return -1;
  }

  if (fread(&size, sizeof(size), fd) != sizeof(size))
  {
    return -1;
  }


  uint8_t* data = new uint8_t[size];

  if (fread(data, size, fd) != size)
  {
    return -1;
  }

  *req = new Request(f_num, size, data);

  return 0;
}


typedef enum {
  OPEN_F_NUM = 1,
  READ_F_NUM,
  WRITE_F_NUM,
  LSEEK_F_NUM,
  CLOSE_F_NUM,
  CREAT_F_NUM,
  UNLINK_F_NUM,
} FuncID;

Response* process_req(Request* req)
{
  Response* resp = nullptr;
  BytesReader* br = new BytesReader(req->Data(), req->Size());

  switch (req->Num())
  {
    case OPEN_F_NUM:
      {
        size_t pathlen = *(size_t*)br->ReadN(sizeof(pathlen));
        const char* pathname = (const char*)br->ReadN(pathlen, true);
        open_flags_t flags = *(open_flags_t*)br->ReadN(sizeof(flags));
        uint32_t mode = *(uint32_t*)br->ReadN(sizeof(mode));
        int fd = api_open(pathname, flags, mode);

        resp = new Response();
        if (fd >= 0)
        {
          resp->Append((uint8_t*)&fd, sizeof(fd));
          resp->SetOK();
        }

        break;
      }
    case READ_F_NUM:
      {
        int fd = *(int *)br->ReadN(sizeof(fd));
        size_t count = *(size_t *)br->ReadN(sizeof(count));

        uint8_t* buf = new uint8_t[count];
        ssize_t rx_cnt = api_read(fd, buf, count);

        resp = new Response();
        if (rx_cnt >= 0)
        {
          resp->Append((uint8_t*)&rx_cnt, sizeof(rx_cnt));
          resp->Append(buf, rx_cnt);
          resp->SetOK();
        }

        break;
      }
    case WRITE_F_NUM:
      {
        int fd = *(int *)br->ReadN(sizeof(fd));
        size_t count = *(size_t *)br->ReadN(sizeof(count));
        uint8_t* buf = (uint8_t *)br->ReadN(count);

        ssize_t tx_cnt = api_write(fd, buf, count);

        resp = new Response();

        if (tx_cnt >= 0)
        {
          resp->Append((uint8_t*)&tx_cnt, sizeof(tx_cnt));
          resp->SetOK();
        }

        break;
      }
    case LSEEK_F_NUM:
      {
        int fd = *(int *)br->ReadN(sizeof(fd));
        off_t offset = *(off_t *)br->ReadN(sizeof(offset));
        int whence = *(int *)br->ReadN(sizeof(whence));
        off_t noffset = api_lseek(fd, offset, whence);
        resp = new Response();
        if (noffset >= 0)
        {
          resp->Append((uint8_t *)&noffset, sizeof(noffset));
          resp->SetOK();
        }
        break;
      }
    case CLOSE_F_NUM:
      {
        int fd = *(int *)br->ReadN(sizeof(fd));
        int ret = api_close(fd);
        resp = new Response();
        if (ret == 0)
        {
          resp->Append((uint8_t*)&ret, sizeof(fd));
          resp->SetOK();
        }
        break;
      }
    case CREAT_F_NUM:
      {
        size_t pathlen = *(size_t*)br->ReadN(sizeof(pathlen));
        const char* pathname = (const char*)br->ReadN(pathlen, true);
        uint32_t mode = *(uint32_t *)br->ReadN(sizeof(mode));
        int fd = api_creat(pathname, mode);
        resp = new Response();
        if (fd >= 0)
        {
          resp->Append((uint8_t*)&fd, sizeof(fd));
          resp->SetOK();
        }
        break;
      }
    case UNLINK_F_NUM:
      {
        size_t pathlen = *(size_t*)br->ReadN(sizeof(pathlen));
        const char* pathname = (const char*)br->ReadN(pathlen, true);
        int ret = api_unlink(pathname);
        resp = new Response();
        if (ret == 0)
        {
          resp->Append((uint8_t*)&ret, sizeof(ret));
          resp->SetOK();
        }
        break;
      }
  }
  return resp;
}
void send_resp(FILE* fd, Response* resp)
{
  if (!fd || !resp)
  {
    err("Bad send_resp");
  }
  fwrite(&resp->Status, sizeof(resp->Status), stdout);
  fwrite(&resp->Length, sizeof(resp->Length), stdout);
  fwrite(resp->Bytes, resp->Length, stdout);
}
extern "C" int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
    uint32_t volatile *secret_page = (uint32_t *)secret_page_i;
    uint64_t delim = 0x8442e492f255bf31;
    /* fxlat(stdin, "HASHTAGYOLOSWAG"); */
    /* fxlat(stdout, "HASHTAGYOLOSWAG"); */
    uint32_t sig = 0;
    for (size_t i = 0; i < 0x1000 / sizeof(uint32_t); i++)
    {
      sig ^= *(secret_page + i);
    }
    Request* cur_req;
    printf("FSAAS\n");
    printf("%x\n", sig);
    fbuffered(stdout, 1);
    while (1)
    {
      printf("QQQ\n");
      fflush(stdout);
      if (load_req(stdin, &cur_req) != 0)
      {
        break;
      }
      Response* resp = process_req(cur_req);
      if (!resp)
      {
        break;
      }
      send_resp(stdout, resp);
      fwrite(&delim, sizeof(delim), stdout);
    }
    fflush(stdout);
    return 0;
}
