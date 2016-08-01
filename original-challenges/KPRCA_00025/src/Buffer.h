#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>
#include "oo.h"

#define SEEK_BEGIN 0
#define SEEK_END ((size_t)-1)

DeclareClass(Buffer, Object)
    uint8_t *m_buf;
    size_t m_length;
    size_t m_pos;
EndDeclareClass(Buffer, Object)

DeclareClassFunctions(Buffer, Object)
    DeclareFunction(Buffer, void, enlarge, size_t)
    DeclareFunction(Buffer, void, seek, size_t)
    DeclareFunction(Buffer, size_t, tell)

    DeclareFunction(Buffer, void, write_u8, uint8_t)
    DeclareFunction(Buffer, void, write_u16, uint16_t)
    DeclareFunction(Buffer, void, write_u32, uint32_t)
    DeclareFunction(Buffer, void, write_number, int)
    DeclareFunction(Buffer, void, write_string, const char *)
    DeclareFunction(Buffer, void, write_bytes, const uint8_t *, size_t)

    DeclareFunction(Buffer, uint8_t, read_u8)
    DeclareFunction(Buffer, uint16_t, read_u16)
    DeclareFunction(Buffer, uint32_t, read_u32)
    DeclareFunction(Buffer, int, read_number)
    DeclareFunction(Buffer, char *, read_string)
    DeclareFunction(Buffer, size_t, read_bytes, uint8_t *, size_t)

    // create or parse ASCII-safe version of buffer
    DeclareFunction(Buffer, uint16_t, checksum)
    DeclareFunction(Buffer, int, dearmor, const char *)
    DeclareFunction(Buffer, char *, armor)
EndDeclareClassFunctions(Buffer)

#endif
