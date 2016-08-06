/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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

#include <libcgc.h>

#include "ctype.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define dbg(s, ...) fdprintf(STDERR, "DEBUG %s:%d:\t" s "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define err(s, ...) \
({ \
  fdprintf(STDERR, "DEBUG %s:%d:\t" s "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
  exit(1); \
})

static size_t end_marker = 0xDEEDACED;

// calloc or crash
void *mcalloc(size_t size)
{
  void *x = calloc(1, size);
  if (!x)
    err("Bad alloc\n");
  return x;
}

typedef struct any_list_t any_list_t;
struct any_list_t {
  any_list_t* prev;
  any_list_t* next;
  void* data;
};

void any_list_add(any_list_t* new, any_list_t* prev, any_list_t* next)
{
  if (next)
    next->prev = new;
  if (prev)
    prev->next = new;
  new->next = next;
  new->prev = prev;
}

#define any_list_add_head(new, head) any_list_add((new), (head), (head)->next)
#define any_list_add_tail(new, head) any_list_add((new), ((head)->prev), (head))
#define any_list_first(head) (head)->next

void any_list_remv(any_list_t* entry)
{
  if (!entry)
    return;
  entry->next->prev = entry->prev;
  entry->prev->next = entry->next;
  if (entry->data)
    free(entry->data);
  free(entry);
}

int any_list_empty(any_list_t* head)
{
  return head->next == head;
}

size_t any_list_length(any_list_t* head)
{
  size_t n = 0;
  any_list_t* cur = head->next;
  while (cur->next != head)
    n++;
  return n;
}

any_list_t* any_list_alloc(void *data)
{
  any_list_t* new = mcalloc(sizeof(any_list_t));
  new->next = new;
  new->prev = new;
  new->data = data;
  return new;
}

any_list_t* any_list_shallow_copy(any_list_t* list)
{
  if (!list)
    return NULL;
  any_list_t* copy = any_list_alloc(NULL);
  for (any_list_t* cur = list; cur->next != list; cur = cur->next)
    any_list_add_tail(cur, copy);
  return copy;
}

int send_n_bytes(int fd, size_t n, char *buf)
{
  if (!n || !buf)
    return -1;

  size_t tx = 0, total_sent = 0;

  while (total_sent < n) {
    if (transmit(fd, buf + total_sent, n - total_sent, &tx) != 0) {
      return -1;
    } else if (tx == 0) {
      break;
    } else {
      total_sent += tx;
    }
  }

  return total_sent;
}

int read_n_bytes(int fd, size_t n, char *buf)
{
  if (!n || !buf)
    return -1;

  size_t rx = 0, total_read = 0;

  while (total_read < n) {
    if (receive(fd, buf + total_read, n - total_read, &rx) != 0) {
      return -1;
    } else if (rx == 0) {
      break;
    } else {
      total_read += rx;
    }
  }

  return total_read;
}

char* read_until_sequence(int fd, char* sequence, size_t sequence_len)
{
#define STEP 128
  char* out = mcalloc(sizeof(char) * STEP);
  char* seq_loc = NULL;
  size_t sz = STEP;
  size_t rx = 0;

  while (1) {
    if (rx == sz) {
      sz += STEP;
      out = realloc(out, sz);
      if (!out)
        err("Bad alloc");
    }

    size_t lrx = read_n_bytes(fd, 1, out + rx);
    if (lrx <= 0)
      goto error;

    for (size_t k = 0; k < sequence_len; k++)
      if (memcmp(out + rx - k, sequence, sequence_len) == 0)
        goto done;

    rx += lrx;
  }

done:
  return out;
error:
  free(out);
  return NULL;
}

#define STEP 128
char* readline(int fd)
{
  char* out = mcalloc(sizeof(char) * STEP);
  char* newline_loc = NULL;
  size_t sz = STEP;
  size_t rx = 0;

  while (1) {
    if (rx == sz) {
      sz += STEP;
      out = realloc(out, sz);
      if (!out)
        err("Bad alloc");
    }

    size_t lrx = read_n_bytes(fd, 1, out + rx);
    if (lrx <= 0)
      goto error;

    if (*(out + rx) == '\n')
      goto done;

    rx += lrx;
  }

done:
  newline_loc = memchr(out + rx, '\n', STEP);
  if (!newline_loc)
    goto error;

  *newline_loc = '\0';
  return out;
error:
  free(out);
  return NULL;
}

typedef struct writer_t writer_t;
struct writer_t
{
  size_t offset;
  size_t cap;
  char* buf;
};

writer_t* writer_new(char* buf, size_t cap)
{
  writer_t* new = mcalloc(sizeof(writer_t));
  new->offset = 0;
  new->cap = cap;
  new->buf = buf;
  return new;
}

int writer_write(writer_t* writer, void* data, size_t len)
{
  for (size_t i = 0; i < len; i++)
    *(u8*)(writer->buf + writer->offset + i) = *(u8*)(data + i);
  writer->offset += len;
  return 0;
}

typedef struct lz_elem_t lz_elem_t;
struct lz_elem_t {
  enum {
    BACKPOINTER = 1,
    LITERAL
  } type;
  size_t back;
  char c;
  size_t len;
};


void print_lzelem(int fd, lz_elem_t* lzelem)
{
  switch (lzelem->type) {
  case BACKPOINTER:
    fdprintf(fd, "(%d,%d)", lzelem->back, lzelem->len);
    break;
  case LITERAL:
    fdprintf(fd, "%c", lzelem->c);
    break;
  }
}

u32 swap_u32(u32 x)
{
  x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF);
  return (x << 16) | (x >> 16);
}

u32 pack_lzelem_bp(lz_elem_t* lzelem)
{
  u32 out = 0;
  if (lzelem->len >= 1 << 15)
    err("Can't pack");
  out |= 0x80000000;
  out |= (lzelem->len & 0x7FFF) << 16;
  out |= lzelem->back & 0xFFFF;
  out = swap_u32(out);
  return out;
}

lz_elem_t* unpack_lzelem_bp(u32 in)
{
  in = swap_u32(in);
  lz_elem_t* out = mcalloc(sizeof(lz_elem_t));
  out->len = (in >> 16) & 0x7FFF;
  out->back = in & 0xFFFF;
  return out;
}


lz_elem_t* lz_backpointer_new(size_t back, size_t len)
{
  lz_elem_t* new = mcalloc(sizeof(lz_elem_t));
  new->type = BACKPOINTER;
  new->back = back;
  new->len = len;
  return new;
}

lz_elem_t* lz_literal_new(char c)
{
  lz_elem_t* new = mcalloc(sizeof(lz_elem_t));
  new->type = LITERAL;
  new->c = c;
  new->len = 1;
  return new;
}


char* alnumspc_filter(char* input)
{
  if (!input)
    return NULL;

  size_t input_len = strlen(input);

  if (!input_len)
    return NULL;

  size_t k = 0;
  char* output = mcalloc(input_len + 1);

  for (size_t i = 0; i < input_len; i++)
    if (isalnum(input[i]) || input[i] == ' ')
        output[k++] = input[i];

  return output;
}

typedef struct suffix_t suffix;
struct suffix_t {
  size_t index;
  char* input;
};

suffix* make_suffix(size_t index, char* input)
{
  suffix* new = mcalloc(sizeof(suffix));
  new->index = index;
  new->input = input;
  return new;
}

typedef struct suffix_list_t suffix_list;
struct suffix_list_t {
  size_t cap;
  size_t size;
  suffix** suffixes;
};

suffix_list* make_suffix_list(size_t cap)
{
  suffix_list* new = mcalloc(sizeof(suffix_list));
  new->cap = cap;
  new->size = 0;
  new->suffixes = mcalloc(sizeof(suffix *) * cap);
  return new;
}

int append_suffix_list(suffix_list* list, suffix* suffix)
{
  if (list->size == list->cap)
    return -1;

  list->suffixes[list->size++] = suffix;
  return 0;
}

suffix* get_suffix(suffix_list* list, size_t index)
{
  if (index >= list->size)
    err("Bad suffix list access");
  return list->suffixes[index];
}

int cmp_suffix(suffix* l, suffix* r)
{
  return strcmp(l->input, r->input);
}

suffix_list* merge(suffix_list* l, suffix_list* r)
{
  size_t l_len = l->size;
  size_t r_len = r->size;
  size_t l_idx, r_idx, idx;
  suffix_list* result = make_suffix_list(l_len + r_len);

  l_idx = r_idx = idx = 0;

  while (l_idx < l_len && r_idx < r_len) {
    if (cmp_suffix(l->suffixes[l_idx], r->suffixes[r_idx]) <= 0) {
      append_suffix_list(result, get_suffix(l, l_idx));
      idx++;
      l_idx++;
    } else {
      append_suffix_list(result, get_suffix(r, r_idx));
      idx++;
      r_idx++;
    }
  }

  while (l_idx < l_len) {
      append_suffix_list(result, get_suffix(l, l_idx));
      idx++;
      l_idx++;
  }

  while (r_idx < r_len) {
      append_suffix_list(result, get_suffix(r, r_idx));
      idx++;
      r_idx++;
  }

  return result;
}

suffix_list* merge_sort(suffix_list* input)
{
  size_t length = input->size;

  if (length <= 1)
    return input;

  suffix_list* l = make_suffix_list(length);
  suffix_list* r = make_suffix_list(length);

  size_t middle = length / 2;

  for (size_t i = 0; i < middle; i++)
    append_suffix_list(l, get_suffix(input, i));

  for (size_t i = middle; i < length; i++)
    append_suffix_list(r, get_suffix(input, i));

  suffix_list* ls = merge_sort(l);
  suffix_list* rs = merge_sort(r);

  if (ls != l)
    free(l);
  if (rs != r)
    free(r);

  return merge(ls, rs);
}

size_t* build_suffix_array(char* input)
{
  size_t length = strlen(input);
  size_t* sa = mcalloc(sizeof(size_t) * length);

  suffix_list* list = make_suffix_list(length);
  for (size_t i = 0; i < length; i++)
    append_suffix_list(list, make_suffix(i, input + i));

  list = merge_sort(list);

  for (size_t i = 0; i < length; i++) {
    sa[i] = get_suffix(list, i)->index;
  }
  return sa;
}

/*
 * match = string we want to find
 * input = string in which we want to find match
 * sa = suffix array
 */
ssize_t search(char* match, size_t match_len, size_t* sa, char* input, size_t input_len, ssize_t max_index)
{
  if (!match || !match_len || !sa || !input || !input_len)
    return -1;

  size_t l = 0, r = input_len - 1, mid;

  while (l <= r) {
    mid = l + ((r - l) / 2);

    int cmp = strncmp(match, input + sa[mid], match_len);

    if (cmp == 0) {
      if (max_index >= 0 && sa[mid] + match_len >= max_index)
        return -1;
      return sa[mid];
    } else if (cmp < 0)
      r = mid - 1;
    else
      l = mid + 1;
  }

  return -1;
}

static inline size_t clamp_sub(size_t x, size_t y, size_t min)
{
  if (x - y > x)
    return min;
  else
    return x - y;
}

static inline size_t min(a, b) {
  return a > b ? b : a;
}

size_t prefix_len(const char* s1, const char* s2, const char* end)
{
  size_t max = 0, n = 0;
  if (s1 < s2) {
    max = s2 - s1;
    if (end - s2 < max)
      max = end - s2;
  } else {
    max = s1 - s2;
    if (end - s1 < max)
      max = end - s1;
  }

#define BLOCK_SIZE (8)

  size_t rounded = max & ~(BLOCK_SIZE - 1);

  while (n < rounded &&
      *s1++ == *s2++ &&
      *s1++ == *s2++ &&
      *s1++ == *s2++ &&
      *s1++ == *s2++ &&
      *s1++ == *s2++ &&
      *s1++ == *s2++ &&
      *s1++ == *s2++ &&
      *s1++ == *s2++
  )
    n += BLOCK_SIZE;

  while (n < max && *s1 && *s2 && *s1 == *s2)
    n++, s1++, s2++;

  return n;
}

#define WINDOW_SIZE (32 * 1024)
size_t compress(char *input, size_t input_len, char *output, size_t output_len, size_t* sa)
{
  lz_elem_t* lzelem;
  any_list_t* lzelem_list = any_list_alloc(NULL);

  writer_t *writer = writer_new(output, output_len);

  lzelem = lz_literal_new(*input);
  any_list_t* new_elem = any_list_alloc(lzelem);
  any_list_add_tail(new_elem, lzelem_list);

  for (size_t i = 1; i < input_len;) {
    size_t max_match = 1;
    size_t best_len = 0;
    ssize_t best_ret = -1;
    while (max_match <= i) {
      ssize_t ret = search(input + i, max_match, sa, input, input_len, i);
      if (ret <= 0)
        break;

      size_t match_len = prefix_len(input + ret, input + i, input + input_len);

      if (match_len > best_len) {
        best_len = match_len;
        best_ret = ret;
      }

      max_match++;
    }

    if (best_ret < 0 || best_len < 8)
      lzelem = lz_literal_new(input[i]);
    else
      lzelem = lz_backpointer_new(i - best_ret, best_len);

    new_elem = any_list_alloc(lzelem);
    any_list_add_tail(new_elem, lzelem_list);
    i += lzelem->len;
  }

  any_list_t* cur;
  for (cur = any_list_first(lzelem_list); cur != lzelem_list; cur = cur->next) {
    lzelem = cur->data;
    if (lzelem->type == LITERAL) {
      if (writer->offset + sizeof(char) > writer->cap)
        err("Doesn't compress enough");
      writer_write(writer, (u8 *)&lzelem->c, 1);
    } else {
      u32 packed = pack_lzelem_bp(lzelem);
      if (writer->offset + sizeof(packed) > writer->cap)
        err("Doesn't compress enough");
      writer_write(writer, &packed, sizeof(packed));
    }
    print_lzelem(STDIN, lzelem);
  }

  writer_write(writer, (u8*)&end_marker, sizeof(end_marker));

  size_t ret =  writer->offset;
  free(writer);
  for (cur = any_list_first(lzelem_list); cur != lzelem_list;) {
    any_list_t* tmp = cur->next;;
    if (cur->data)
      free(cur->data);
    free(cur);
    cur = tmp;
  }

  return ret;
}

size_t decompress(char* input, char *output, size_t output_size)
{
  size_t in_idx = 0;
  writer_t *writer = writer_new(output, output_size);

  while (1) {
    if (memcmp(&end_marker, input + in_idx, sizeof(end_marker)) == 0)
      break;

    if ((*(input + in_idx)) & 0x80) {
      lz_elem_t* elem = unpack_lzelem_bp(*(u32*)(input + in_idx));
      if (elem->back > writer->offset)
        err("Bad back pointer %d", elem->back);

#ifdef PATCHED
      if (writer->offset + elem->len > writer->cap)
        err("Expands too much");
#endif
      writer_write(writer, writer->buf + writer->offset - elem->back, elem->len);

      in_idx += sizeof(u32);
    } else {
#ifdef PATCHED
      if (writer->offset + 1 > writer->cap)
        err("Expands too much");
#endif
      writer_write(writer, input + in_idx, 1);
      in_idx++;
    }
  }

  size_t ret =  writer->offset;
  free(writer);
  return ret;
}


extern char* padding;
int main(void)
{
#define COMPRESSED_SZ (32 * 1024 + 4)
  char compressed[COMPRESSED_SZ];
#define DECOMPRESSED_SZ (64 * 1024)
  char decompressed[DECOMPRESSED_SZ];

  while (1) {
    char* action = readline(STDIN);
    if (!action)
      return -1;

    if (strcmp(action, "compress") == 0) {
      char* input = readline(STDIN);
      char* filtered_input = alnumspc_filter(input);
      free(input);
      free(action);
      if (!filtered_input)
        return -1;

      if (strlen(filtered_input) > DECOMPRESSED_SZ)
        return -1;

      size_t* sa = build_suffix_array(filtered_input);
      if (!sa)
        return -1;

      size_t compressed_sz = compress(filtered_input, strlen(filtered_input), compressed, COMPRESSED_SZ, sa);
      send_n_bytes(STDOUT, compressed_sz, compressed);

      free(filtered_input);
      free(sa);

    } else if (strcmp(action, "decompress") == 0) {
      char* input = read_until_sequence(STDIN, (char*)&end_marker, 4);
      if (!input)
        return -1;
      memset(decompressed, 0, DECOMPRESSED_SZ);
      size_t decompressed_sz = decompress(input, decompressed, DECOMPRESSED_SZ);
      send_n_bytes(STDOUT, decompressed_sz, decompressed);

      free(action);
      free(input);

    } else if (strcmp(action, "quit") == 0) {
      break;
    }
  }
  return 0;
}
