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

#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_ctype.h"
#include "cgc_readuntil.h"
#include "cgc_cgcf.h"
#include "cgc_slist.h"

/* Up to 2MB file */
#define MAX_FILE_SIZE (2 * 1024 * 1024)

int cgc_max_section_name_len(sl_node *sections)
{
  int max = 0, len = 0;
  cgcf_Shdr *shdr;
  sl_node *cur = sections;

  while (cur)
  {
    shdr = (cgcf_Shdr *) cur->elem;
    if (shdr)
    {
      len = cgc_strlen(shdr->sh_name_str);
      if (max < len)
        max = len;
    }
    cur = cur->next;
  }
  return max;
}

void cgc_print_ws(int n)
{
  int i;
  for (i = 0; i < n; ++i)
    cgc_printf(" ");
}


void cgc_print_sections(sl_node *sections, int count)
{
  int i = 0, len;
  char *type_str;
  cgcf_Shdr *shdr;
  sl_node *cur = sections;

  cgc_printf("%d section header(s):\n", count);
  len = cgc_max_section_name_len(sections);
  cgc_printf("  [No.] Name");
  cgc_print_ws(len - 4);
  cgc_printf("  Type           Addr     Off    Size\n");

  while (cur)
  {
    shdr = (cgcf_Shdr *) cur->elem;
    if (shdr)
    {
      cgc_printf("  [%3d] %s", i++, shdr->sh_name_str);
      cgc_print_ws(len - cgc_strlen(shdr->sh_name_str));
      type_str = cgc_cgcf_section_type2str(shdr->sh_type);
      cgc_printf("  %s", type_str);
      cgc_print_ws(14 - cgc_strlen(type_str));
      cgc_printf(" %08x %06x %06x\n", shdr->sh_addr, shdr->sh_offset, shdr->sh_size);
    }
    cur = cur->next;
  }
  cgc_printf("\n");
}

void cgc_print_symbols(sl_node *symbols, int count)
{
  char *type, *bind;
  int i = 0;
  cgcf_Sym *symb;
  sl_node *cur = symbols;

  cgc_printf("%d symbol(s):\n", count);
  cgc_printf("  [No.] Value       Size Type    Bind    Name\n");
  while (cur)
  {
    symb = (cgcf_Sym *) cur->elem;
    if (symb)
    {
      type = cgc_cgcf_symbol_type2str(symb->st_info & 0xf);
      bind = cgc_cgcf_symbol_bind2str(symb->st_info >> 4);
      cgc_printf("  [%3d] 0x%08x %5d", i++, symb->st_value, symb->st_size);
      cgc_printf(" %s", type);
      cgc_print_ws(7 - cgc_strlen(type));
      cgc_printf(" %s", bind);
      cgc_print_ws(7 - cgc_strlen(bind));
      cgc_printf(" %s\n", symb->st_name_str);
    }
    cur = cur->next;
  }
  cgc_printf("\n");
}

int cgc_cmp_section(void *e1, void *e2)
{
  if (e1 && e2)
  {
    cgcf_Shdr *s1 = (cgcf_Shdr *)e1;
    cgcf_Shdr *s2 = (cgcf_Shdr *)e2;
    return s1->sh_offset - s2->sh_offset;
  }
  return 0;
}

int cgc_cmp_symbol(void *e1, void *e2)
{
  if (e1 && e2)
  {
    cgcf_Sym *s1 = (cgcf_Sym *)e1;
    cgcf_Sym *s2 = (cgcf_Sym *)e2;
    return cgc_strcmp(s1->st_name_str, s2->st_name_str);
  }
  return 0;
}

void cgc_free_section(void *e)
{
  if (e)
  {
    cgcf_Shdr *s = (cgcf_Shdr *)e;
    if (s->sh_name_str)
      cgc_free(s->sh_name_str);
    cgc_free(s);
  }
}

void cgc_free_symbol(void *e)
{
  if (e)
  {
    cgcf_Sym *s = (cgcf_Sym *)e;
    if (s->st_name_str)
      cgc_free(s->st_name_str);
    cgc_free(s);
  }
}

int main(int cgc_argc, char *cgc_argv[])
{
  int i;
  cgc_size_t size;
  char *file;
  cgcf_Ehdr ehdr;
  cgcf_Shdr *shdr = NULL;
  sl_node *cur = NULL;
  sl_node *sections = NULL;
  sl_node *symbols = NULL;

  /* Read in size */
  if (cgc_read_n(STDIN, (char *)&size, sizeof(size)) != sizeof(size))
    return -1;

  /* Check size */
  if (size > MAX_FILE_SIZE)
  {
    cgc_printf("Too big.\n");
    return -1;
  }

  /* Allocate memory */
  file = cgc_malloc(size);
  if (file == NULL)
    return -1;

  /* Read in file */
  if (cgc_read_n(STDIN, file, size) != size)
    goto error;

  /* Parse file header */
  if (cgc_cgcf_parse_file_header(file, size, &ehdr) != 0)
  {
    cgc_printf("Invalid CGC file header.\n");
    goto error;
  }

  /* Validate CGC magic */
  if (!cgc_cgcf_is_valid(&ehdr))
  {
    cgc_printf("Invalid CGC magic.\n");
    goto error;
  }

  cgc_printf("Valid CGC executable format found [%d bytes]\n\n", size);

  /* Get shstrtab for section names */
  cgcf_Shdr tmp;
  if (cgc_cgcf_parse_section_header(file, size, ehdr.e_shstrndx, &tmp) != 0)
    goto error;
  if (tmp.sh_offset >= size)
    goto error;
  char *shstrtab = (file + tmp.sh_offset);

  /* Parse sections */
  for (i = 0; i < ehdr.e_shnum; ++i)
  {
    shdr = (cgcf_Shdr *) cgc_malloc(sizeof(cgcf_Shdr));
    if (shdr == NULL)
      goto error;
    if (cgc_cgcf_parse_section_header(file, size, i, shdr) != 0)
      goto error;
    if ((shdr->sh_name > 0) && ((unsigned int)shstrtab > 0xFFFFFFFF - shdr->sh_name))
      goto error;
    if (shstrtab + shdr->sh_name >= file + size || shstrtab + shdr->sh_name < file)
      goto error;
    shdr->sh_name_str = cgc_malloc(cgc_strlen(shstrtab + shdr->sh_name) + 1);
    if (shdr->sh_name_str == NULL)
      goto error;
    cgc_strcpy(shdr->sh_name_str, shstrtab + shdr->sh_name);
    sections = cgc_sl_insert(sections, shdr, cgc_cmp_section);
  }

  /* Print sections */
  cgc_print_sections(sections, ehdr.e_shnum);

  /* Parse symbols */
  int num_syms = 0;
  cur = sections;
  while (cur)
  {
    cgcf_Shdr *s = (cgcf_Shdr *)(cur->elem);
    cgcf_Shdr strtab_sec;
    if (s->sh_type == SHT_SYMTAB)
    {
      if (cgc_cgcf_parse_section_header(file, size, s->sh_link, &strtab_sec) != 0)
        goto error;
      char *strtab = (file + strtab_sec.sh_offset);
      cgc_size_t sz = sizeof(cgcf_Sym) - sizeof(char *);
      num_syms = s->sh_size / sz;
      if (s->sh_offset > 0xFFFFFFFF - num_syms * sz)
        goto error;
      if (s->sh_offset + num_syms * sz >= size)
        goto error;
      for (i = 0; i < num_syms; ++i)
      {
        cgcf_Sym *sym = (cgcf_Sym *) cgc_malloc(sizeof(cgcf_Sym));
        if (sym == NULL)
          goto error;
        cgc_memmove((char *)sym, (file + s->sh_offset + i * sz), sz);
        if ((sym->st_name > 0) && ((unsigned int)strtab > 0xFFFFFFFF - sym->st_name))
          goto error;
        if (strtab + sym->st_name >= file + size || strtab + sym->st_name < file)
          goto error;
        sym->st_name_str = cgc_malloc(cgc_strlen(strtab + sym->st_name) + 1);
        if (sym->st_name_str == NULL)
          goto error;
        cgc_strcpy(sym->st_name_str, strtab + sym->st_name);
        symbols = cgc_sl_insert(symbols, sym, cgc_cmp_symbol);
      }
    }
    cur = cur->next;
  }

  /* Print symbols */
  cgc_print_symbols(symbols, num_syms);

  cgc_printf("DONE\n");

  return 0;

error:
  cgc_printf("ERROR\n");
  if (file)
    cgc_free(file);
  if (sections)
    cgc_sl_destroy(sections, cgc_free_section);
  if (symbols)
    cgc_sl_destroy(symbols, cgc_free_symbol);
  return -1;
}
