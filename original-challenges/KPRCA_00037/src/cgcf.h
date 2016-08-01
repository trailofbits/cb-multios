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

#ifndef CGCF_H
#define CGCF_H

#include <libcgc.h>
#include <string.h>

#define EI_NIDENT   16
#define SHT_SYMTAB  2

// CGC File header
typedef struct {
  unsigned char   e_ident[EI_NIDENT];
  unsigned short  e_type;
  unsigned short  e_machine;
  unsigned int    e_version;
  unsigned int    e_entry;
  unsigned int    e_phoff;
  unsigned int    e_shoff;
  unsigned int    e_flags;
  unsigned short  e_ehsize;
  unsigned short  e_phentsize;
  unsigned short  e_phnum;
  unsigned short  e_shentsize;
  unsigned short  e_shnum;
  unsigned short  e_shstrndx;
} cgcf_Ehdr;

// CGC Section header
typedef struct {
  unsigned int    sh_name;
  unsigned int    sh_type;
  unsigned int    sh_flags;
  unsigned int    sh_addr;
  unsigned int    sh_offset;
  unsigned int    sh_size;
  unsigned int    sh_link;
  unsigned int    sh_info;
  unsigned int    sh_addralign;
  unsigned int    sh_entsize;
  char *          sh_name_str;
} cgcf_Shdr;

// Section Type
#define SHT_NULL            0
#define SHT_PROGBITS        1
#define SHT_SYMTAB          2
#define SHT_STRTAB          3
#define SHT_RELA            4
#define SHT_HASH            5
#define SHT_DYNAMIC         6
#define SHT_NOTE            7
#define SHT_NOBITS          8
#define SHT_REL             9
#define SHT_SHLIB           10
#define SHT_DYNSYM          11
#define SHT_INIT_ARRAY      14
#define SHT_FINI_ARRAY      15
#define SHT_PREINIT_ARRAY   16
#define SHT_GROUP           17
#define SHT_SYMTAB_SHNDX    18
#define SHT_NUM             19

// CGC Symbol table
typedef struct {
  unsigned int    st_name;
  unsigned int    st_value;
  unsigned int    st_size;
  unsigned char   st_info;
  unsigned char   st_other;
  unsigned short  st_shndx;
  char *          st_name_str;
} cgcf_Sym;

// Symbol Info
// bind
#define STB_LOCAL   0
#define STB_GLOBAL  1
#define STB_WEAK    2
#define STB_NUM     3
// type
#define STT_NOTYPE  0
#define STT_OBJECT  1
#define STT_FUNC    2
#define STT_SECTION 3
#define STT_FILE    4
#define STT_COMMON  5
#define STT_TLS     6
#define STT_NUM     7

char* cgcf_section_type2str(unsigned int type);
char* cgcf_symbol_bind2str(unsigned char bind);
char* cgcf_symbol_type2str(unsigned char type);
int cgcf_is_valid(cgcf_Ehdr *hdr);
int cgcf_parse_file_header(const char *buf, size_t buf_len, cgcf_Ehdr *hdr);
int cgcf_parse_section_header(const char *buf, size_t buf_len, short idx, cgcf_Shdr *shdr);

#endif
