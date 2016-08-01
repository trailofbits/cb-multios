#ifndef DEFS_H
#define DEFS_H


#define PAGE_SIZE 4096
#define STR_LEN 128

typedef enum
{
 PROTO_GET, 
 PROTO_GET_ACK,
 PROTO_ERROR,
 PROTO_BYE
} eProtoType;

typedef struct _ProtoMsg
{
  eProtoType type;
  uint32_t msgLen;  
} ProtoMsg;

static inline void sendMsg(int fd, const void* buf, size_t count)
{
  size_t rx_bytes = 0;
  size_t total = 0;
  int ret = 0;

  do
  {
    ret = transmit(fd, buf + total, count - total, &rx_bytes);

    if ( (ret != 0) )
    {
      _terminate(-1);
    }
    total += rx_bytes;
  } while (total < count);
}

static inline void recvMsg(int fd, void* buf, size_t count)
{
  size_t rx_bytes = 0;
  size_t total = 0;
  int ret = 0;

  do 
  {
    ret = receive(fd, buf + total, count - total, &rx_bytes);

    if ( (ret != 0) || (rx_bytes == 0) )
    {
      _terminate(-1);
    }

    total += rx_bytes;
  } while (total < count);
}

#endif//DEFS_H
