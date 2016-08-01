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
#include "slist.h"

/* Up to 2MB file */
#define MAX_FILE_SIZE (2 * 1024 * 1024)

int max_section_name_len(sl_node *sections)
{
  int max = 0, len = 0;
  cgcf_Shdr *shdr;
  sl_node *cur = sections;

  while (cur)
  {
    shdr = (cgcf_Shdr *) cur->elem;
    if (shdr)
    {
      len = strlen(shdr->sh_name_str);
      if (max < len)
        max = len;
    }
    cur = cur->next;
  }
  return max;
}

void print_ws(int n)
{
  int i;
  for (i = 0; i < n; ++i)
    printf(" ");
}


void print_sections(sl_node *sections, int count)
{
  int i = 0, len;
  char *type_str;
  cgcf_Shdr *shdr;
  sl_node *cur = sections;

  printf("%d section header(s):\n", count);
  len = max_section_name_len(sections);
  printf("  [No.] Name");
  print_ws(len - 4);
  printf("  Type           Addr     Off    Size\n");

  while (cur)
  {
    shdr = (cgcf_Shdr *) cur->elem;
    if (shdr)
    {
      printf("  [%3d] %s", i++, shdr->sh_name_str);
      print_ws(len - strlen(shdr->sh_name_str));
      type_str = cgcf_section_type2str(shdr->sh_type);
      printf("  %s", type_str);
      print_ws(14 - strlen(type_str));
      printf(" %08x %06x %06x\n", shdr->sh_addr, shdr->sh_offset, shdr->sh_size);
    }
    cur = cur->next;
  }
  printf("\n");
}

void print_symbols(sl_node *symbols, int count)
{
  char *type, *bind;
  int i = 0;
  cgcf_Sym *symb;
  sl_node *cur = symbols;

  printf("%d symbol(s):\n", count);
  printf("  [No.] Value       Size Type    Bind    Name\n");
  while (cur)
  {
    symb = (cgcf_Sym *) cur->elem;
    if (symb)
    {
      type = cgcf_symbol_type2str(symb->st_info & 0xf);
      bind = cgcf_symbol_bind2str(symb->st_info >> 4);
      printf("  [%3d] 0x%08x %5d", i++, symb->st_value, symb->st_size);
      printf(" %s", type);
      print_ws(7 - strlen(type));
      printf(" %s", bind);
      print_ws(7 - strlen(bind));
      printf(" %s\n", symb->st_name_str);
    }
    cur = cur->next;
  }
  printf("\n");
}

int cmp_section(void *e1, void *e2)
{
  if (e1 && e2)
  {
    cgcf_Shdr *s1 = (cgcf_Shdr *)e1;
    cgcf_Shdr *s2 = (cgcf_Shdr *)e2;
    return s1->sh_offset - s2->sh_offset;
  }
  return 0;
}

int cmp_symbol(void *e1, void *e2)
{
  if (e1 && e2)
  {
    cgcf_Sym *s1 = (cgcf_Sym *)e1;
    cgcf_Sym *s2 = (cgcf_Sym *)e2;
    return strcmp(s1->st_name_str, s2->st_name_str);
  }
  return 0;
}

void free_section(void *e)
{
  if (e)
  {
    cgcf_Shdr *s = (cgcf_Shdr *)e;
    if (s->sh_name_str)
      free(s->sh_name_str);
    free(s);
  }
}

void free_symbol(void *e)
{
  if (e)
  {
    cgcf_Sym *s = (cgcf_Sym *)e;
    if (s->st_name_str)
      free(s->st_name_str);
    free(s);
  }
}

int main()
{
  int i;
  size_t size;
  char *file;
  cgcf_Ehdr ehdr;
  cgcf_Shdr *shdr = NULL;
  sl_node *cur = NULL;
  sl_node *sections = NULL;
  sl_node *symbols = NULL;

  /* Read in size */
  if (read_n(STDIN, (char *)&size, sizeof(size)) != sizeof(size))
    return -1;

  /* Check size */
  if (size > MAX_FILE_SIZE)
  {
    printf("Too big.\n");
    return -1;
  }

  /* Allocate memory */
  file = malloc(size);
  if (file == NULL)
    return -1;

  /* Read in file */
  if (read_n(STDIN, file, size) != size)
    goto error;

  /* Parse file header */
  if (cgcf_parse_file_header(file, size, &ehdr) != 0)
  {
    printf("Invalid CGC file header.\n");
    goto error;
  }

  /* Validate CGC magic */
  if (!cgcf_is_valid(&ehdr))
  {
    printf("Invalid CGC magic.\n");
    goto error;
  }

  printf("Valid CGC executable format found [%d bytes]\n\n", size);

  /* Get shstrtab for section names */
  cgcf_Shdr tmp;
  if (cgcf_parse_section_header(file, size, ehdr.e_shstrndx, &tmp) != 0)
    goto error;
  if (tmp.sh_offset >= size)
    goto error;
  char *shstrtab = (file + tmp.sh_offset);

  /* Parse sections */
  for (i = 0; i < ehdr.e_shnum; ++i)
  {
    shdr = (cgcf_Shdr *) malloc(sizeof(cgcf_Shdr));
    if (shdr == NULL)
      goto error;
    if (cgcf_parse_section_header(file, size, i, shdr) != 0)
      goto error;
    if ((shdr->sh_name > 0) && ((unsigned int)shstrtab > 0xFFFFFFFF - shdr->sh_name))
      goto error;
    if (shstrtab + shdr->sh_name >= file + size || shstrtab + shdr->sh_name < file)
      goto error;
    shdr->sh_name_str = malloc(strlen(shstrtab + shdr->sh_name) + 1);
    if (shdr->sh_name_str == NULL)
      goto error;
    strcpy(shdr->sh_name_str, shstrtab + shdr->sh_name);
    sections = sl_insert(sections, shdr, cmp_section);
  }

  /* Print sections */
  print_sections(sections, ehdr.e_shnum);

  /* Parse symbols */
  int num_syms = 0;
  cur = sections;
  while (cur)
  {
    cgcf_Shdr *s = (cgcf_Shdr *)(cur->elem);
    cgcf_Shdr strtab_sec;
    if (s->sh_type == SHT_SYMTAB)
    {
      if (cgcf_parse_section_header(file, size, s->sh_link, &strtab_sec) != 0)
        goto error;
      char *strtab = (file + strtab_sec.sh_offset);
      size_t sz = sizeof(cgcf_Sym) - sizeof(char *);
      num_syms = s->sh_size / sz;
      if (s->sh_offset > 0xFFFFFFFF - num_syms * sz)
        goto error;
      if (s->sh_offset + num_syms * sz >= size)
        goto error;
      for (i = 0; i < num_syms; ++i)
      {
        cgcf_Sym *sym = (cgcf_Sym *) malloc(sizeof(cgcf_Sym));
        if (sym == NULL)
          goto error;
        memmove((char *)sym, (file + s->sh_offset + i * sz), sz);
        if ((sym->st_name > 0) && ((unsigned int)strtab > 0xFFFFFFFF - sym->st_name))
          goto error;
        if (strtab + sym->st_name >= file + size || strtab + sym->st_name < file)
          goto error;
        sym->st_name_str = malloc(strlen(strtab + sym->st_name) + 1);
        if (sym->st_name_str == NULL)
          goto error;
        strcpy(sym->st_name_str, strtab + sym->st_name);
        symbols = sl_insert(symbols, sym, cmp_symbol);
      }
    }
    cur = cur->next;
  }

  /* Print symbols */
  print_symbols(symbols, num_syms);

  printf("DONE\n");

  return 0;

error:
  printf("ERROR\n");
  if (file)
    free(file);
  if (sections)
    sl_destroy(sections, free_section);
  if (symbols)
    sl_destroy(symbols, free_symbol);
  return -1;
}
