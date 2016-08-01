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

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "readuntil.h"
#include "cgcf.h"

char* cgcf_section_type2str(unsigned int type)
{
  switch (type)
  {
    case SHT_NULL:          return "NULL";
    case SHT_PROGBITS:      return "PROGBITS";
    case SHT_SYMTAB:        return "SYMTAB";
    case SHT_STRTAB:        return "STRTAB";
    case SHT_RELA:          return "RELA";
    case SHT_HASH:          return "HASH";
    case SHT_DYNAMIC:       return "DYNAMIC";
    case SHT_NOTE:          return "NOTE";
    case SHT_NOBITS:        return "NOBITS";
    case SHT_REL:           return "REL";
    case SHT_SHLIB:         return "-reserved-";
    case SHT_DYNSYM:        return "DYNSYM";
    case SHT_INIT_ARRAY:    return "INIT_ARRAY";
    case SHT_FINI_ARRAY:    return "FINI_ARRAY";
    case SHT_PREINIT_ARRAY: return "PREINIT_ARRAY";
    case SHT_GROUP:         return "GROUP";
    case SHT_SYMTAB_SHNDX:  return "SYMTAB_SHNDX";
    case SHT_NUM:           return "NUM";
    default:
      return "UNKNOWN";
  }
}

char* cgcf_symbol_bind2str(unsigned char bind)
{
  switch (bind)
  {
    case STB_LOCAL:   return "LOCAL";
    case STB_GLOBAL:  return "GLOBAL";
    case STB_WEAK:    return "WEAK";
    case STB_NUM:     return "NUM";
    default:
      return "UNKNOWN";
  }
}

char* cgcf_symbol_type2str(unsigned char type)
{
  switch (type)
  {
    case STT_NOTYPE:  return "NOTYPE";
    case STT_OBJECT:  return "OBJECT";
    case STT_FUNC:    return "FUNC";
    case STT_SECTION: return "SECTION";
    case STT_FILE:    return "FILE";
    case STT_COMMON:  return "COMMON";
    case STT_TLS:     return "TLS";
    case STT_NUM:     return "NUM";
    default:
      return "UNKNOWN";
  }
}

int cgcf_is_valid(cgcf_Ehdr *hdr)
{
  return (memcmp(hdr->e_ident, "\x7f""CGC", 4) == 0);
}

int cgcf_parse_file_header(const char *buf, size_t buf_len, cgcf_Ehdr *hdr)
{
  /* Check if the pointers are NULL */
  if (buf == NULL || hdr == NULL)
    return -1;

  /* Check if the buffer is large enough */
  if (buf_len < sizeof(cgcf_Ehdr))
    return -1;

  /* Copy over the file header */
  memmove(hdr, buf, sizeof(cgcf_Ehdr));

  return 0;
}

int cgcf_parse_section_header(const char *buf, size_t buf_len, short idx, cgcf_Shdr *shdr)
{
  /* Check if the pointers are NULL */
  if (buf == NULL || shdr == NULL)
    return -1;

  short shnum = 0;
  size_t sz = sizeof(cgcf_Shdr) - sizeof(char *);
  cgcf_Ehdr ehdr;
  cgcf_parse_file_header(buf, buf_len, &ehdr);
  if (ehdr.e_shoff + ehdr.e_shentsize * idx + sz > buf_len)
    return -1;
  shnum = ehdr.e_shnum;
#if PATCHED
  if (idx < shnum && idx >= 0 && !(ehdr.e_shoff > buf_len || ehdr.e_shentsize * idx > buf_len))
#else
  if (idx < shnum)
#endif
  {
    memmove(shdr, buf + ehdr.e_shoff + ehdr.e_shentsize * idx, sz);
    return 0;
  }
  return -1;
}
