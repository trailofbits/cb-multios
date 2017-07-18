/*
 * Copyright (c) 2014 Kaprica Security, Inc.
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
#include "cgc_kty.h"
#include "cgc_strdup.h"
#include "cgc_strncmp.h"
#include "cgc_strtod.h"

kty_parser_t *g_parser;

void cgc_kty_print_item(kty_item_t *item, int depth);
char* cgc_parse_item(kty_item_t *item, char *str);

char* cgc_eat_ws(char *str)
{
  while (str && str[0] && str[0] <= ' ')
    str++;
  return str;
}

void cgc_print_escaped(char *str, int len)
{
  int i = 0;
  char c[2] = {0}, tmp[2] = {0};
  char *hex_nums = "0123456789ABCDEF";

  while (len--)
  {
    c[0] = str[i++];
    switch (c[0])
    {
      case '"':
        cgc_fdprintf(STDOUT, "\\\""); break;
      case '\\':
        cgc_fdprintf(STDOUT, "\\\\"); break;
      case '/':
        cgc_fdprintf(STDOUT, "\\/");  break;
      case '\b':
        cgc_fdprintf(STDOUT, "\\b");  break;
      case '\f':
        cgc_fdprintf(STDOUT, "\\f");  break;
      case '\n':
        cgc_fdprintf(STDOUT, "\\n");  break;
      case '\r':
        cgc_fdprintf(STDOUT, "\\r");  break;
      case '\t':
        cgc_fdprintf(STDOUT, "\\t");  break;
      default:
        cgc_fdprintf(STDOUT, "%s", c); break;
    }
  }
}

void cgc_print_indent(int depth)
{
  int i;
  for (i = 0; i < depth * 2; ++i)
    cgc_fdprintf(STDOUT, " ");
}

void cgc_kty_int_to_string(kty_item_t *item)
{
  cgc_fdprintf(STDOUT, "%d", item->item.i_int);
}

void cgc_kty_double_to_string(kty_item_t *item)
{
  int tmp;
  double val;

  val = item->item.i_double;
  tmp = (int) val;
  if (val < 0.0 && tmp == 0)
    cgc_fdprintf(STDOUT, "-");
  cgc_fdprintf(STDOUT, "%d.", tmp);
  tmp = ((int)(val * 100.0)) % 100;
  if (tmp < 0)
    tmp = -tmp;
  cgc_fdprintf(STDOUT, "%02d", tmp);
}

void cgc_kty_string_to_string(kty_item_t *item)
{
  cgc_fdprintf(STDOUT, "\"");
  cgc_print_escaped(item->item.i_string.s, item->item.i_string.len);
  cgc_fdprintf(STDOUT, "\"");
}

void cgc_kty_object_to_string(kty_item_t *item, int depth)
{
  int count = 0;
  htbl_t *table;
  entry_t *entry;

  cgc_fdprintf(STDOUT, "{");
  table = item->item.i_object;
  if (table)
  {
    cgc_fdprintf(STDOUT, "\n");
    for (entry = table->head; entry != NULL ; entry = entry->next)
    {
      if (count > 0)
        cgc_fdprintf(STDOUT, ",\n");
      count++;
      cgc_print_indent(depth + 1);
      cgc_fdprintf(STDOUT, "\"");
      cgc_print_escaped(entry->key, cgc_strlen(entry->key));
      cgc_fdprintf(STDOUT, "\": ");
      cgc_kty_print_item(entry->val, depth + 1);
    }
  }
  if (count > 0)
  {
    cgc_fdprintf(STDOUT, "\n");
    cgc_print_indent(depth);
  }
  cgc_fdprintf(STDOUT, "}");
}

void cgc_kty_array_to_string(kty_item_t *item, int depth)
{
  int i, count = 0;
  kty_item_t *elem;

  cgc_fdprintf(STDOUT, "[");
  if (cgc_array_length(item->item.i_array) > 0)
    cgc_fdprintf(STDOUT, "\n");
  for (i = 0; i < cgc_array_length(item->item.i_array); ++i)
  {
    if (count > 0)
      cgc_fdprintf(STDOUT, ",\n");
    count++;
    cgc_print_indent(depth + 1);
    elem = cgc_array_get(item->item.i_array, i);
    cgc_kty_print_item(elem, depth + 1);
  }
  if (count > 0)
  {
    cgc_fdprintf(STDOUT, "\n");
    cgc_print_indent(depth);
  }
  cgc_fdprintf(STDOUT, "]");
}

void cgc_kty_boolean_to_string(kty_item_t *item)
{
  cgc_fdprintf(STDOUT, "%s", item->item.i_bool ? "true" : "false");
}

void cgc_kty_null_to_string(kty_item_t *item)
{
  cgc_fdprintf(STDOUT, "null");
}

void cgc_kty_cat_to_string(kty_item_t *item)
{
  g_parser->cats++;
  cgc_fdprintf(STDOUT, "=^.^=");
}

void cgc_kty_print_item(kty_item_t *item, int depth)
{
  switch (item->type)
  {
    case KTY_INT:
      cgc_kty_int_to_string(item);
      break;
    case KTY_DOUBLE:
      cgc_kty_double_to_string(item);
      break;
    case KTY_STRING:
      cgc_kty_string_to_string(item);
      break;
    case KTY_OBJECT:
      cgc_kty_object_to_string(item, depth);
      break;
    case KTY_ARRAY:
      cgc_kty_array_to_string(item, depth);
      break;
    case KTY_BOOLEAN:
      cgc_kty_boolean_to_string(item);
      break;
    case KTY_NULL:
      cgc_kty_null_to_string(item);
      break;
    case KTY_CAT:
      cgc_kty_cat_to_string(item);
      break;
    default:
      break;
  }
}

void cgc_kty_dumps(kty_item_t *kty)
{
  int depth = 0;
  g_parser->cats = 0;
  if (kty)
  {
    cgc_kty_print_item(kty, depth);
  }
}

char* cgc_parse_number(kty_item_t *item, char *str)
{
  char decimal[3] = {0};
  char *c1, *c2;
  int i;
  double d;

  c1 = cgc_strchr(str, ' ');
  if (c1 == NULL)
    c1 = cgc_strchr(str, ',');
  if (c1 == NULL)
    c1 = cgc_strchr(str, ']');
  if (c1 == NULL)
    c1 = cgc_strchr(str, '}');
  c2 = cgc_strchr(str, '.');
  if ((c1 && c2 && c2 < c1) || (c2 && c1 == NULL))
  {
    // Double
    d = cgc_strtod(str, &str);
    item->type = KTY_DOUBLE;
    item->item.i_double = d;
  }
  else
  {
    // Int
    i = cgc_strtol(str, &str, 10);
    item->type = KTY_INT;
    item->item.i_int = i;
  }

  return str;
}

char* cgc_parse_string(kty_item_t *item, char *str)
{
  int cgc_read = 0, len = 0;
  char *c = str + 1;

  item->type = KTY_STRING;
  item->item.i_string.s = NULL;
  if (str[0] != '\"')
    return NULL;

  while (c[0] && c[0] != '\"')
  {
    if (c[0] == '\\')
    {
      c++;
      cgc_read++;
    }
    c++;
    len++;
    cgc_read++;
  }

  if (len >= MAX_KTY_STRING)
    return NULL;
  item->item.i_string.s = cgc_malloc(len + 1);
  if (item->item.i_string.s == NULL)
    return NULL;

  c = str + 1;
  cgc_read += 2;
  len = 0;
  while (c[0] && c[0] != '\"')
  {
    if (c[0] == '\\')
    {
      c++;
      switch (c[0])
      {
        case 'b':
          item->item.i_string.s[len] = '\b';
          break;
        case 'f':
          item->item.i_string.s[len] = '\f';
          break;
        case 'n':
          item->item.i_string.s[len] = '\n';
          break;
        case 'r':
          item->item.i_string.s[len] = '\r';
          break;
        case 't':
          item->item.i_string.s[len] = '\t';
          break;
        default:
          item->item.i_string.s[len] = c[0];
          break;
      }
    }
    else
    {
      item->item.i_string.s[len] = c[0];
    }
    c++;
    len++;
  }

  item->item.i_string.s[len] = '\0';
  item->item.i_string.len = len;

  return str + cgc_read;
}

char* cgc_parse_array(kty_item_t *item, char *str)
{
  kty_item_t *new;

  item->type = KTY_ARRAY;
  item->item.i_array = NULL;
  str = cgc_eat_ws(str + 1);
  if (str[0] == ']')
    return str + 1;

  new = (kty_item_t *) cgc_malloc(sizeof(kty_item_t));
  if (new == NULL)
    goto fail;
  item->item.i_array = cgc_array_create(4, cgc_free_kty_item);
  if (item->item.i_array == NULL)
    goto fail;
  str = cgc_eat_ws(cgc_parse_item(new, cgc_eat_ws(str)));
  if (str == NULL)
    goto fail;
  cgc_array_append(item->item.i_array, new);
  new = NULL;

  while (str[0] == ',')
  {
    new = (kty_item_t *) cgc_malloc(sizeof(kty_item_t));
    if (new == NULL)
      goto fail;
    str++;
    str = cgc_eat_ws(cgc_parse_item(new, cgc_eat_ws(str)));
    if (str == NULL)
      goto fail;
    cgc_array_append(item->item.i_array, new);
    new = NULL;
  }

  if (str[0] == ']')
    return str + 1;

fail:
  if (new)
    cgc_free_kty_item(new);
  return NULL;
}

char* cgc_parse_object(kty_item_t *item, char *str)
{
  char *key = NULL;
  kty_item_t *new = NULL, *k = NULL, *dup = NULL;

  item->type = KTY_OBJECT;
  item->item.i_object = NULL;

  str = cgc_eat_ws(str + 1);
  if (str[0] == '}')
    return str + 1;

  k = (kty_item_t *) cgc_malloc(sizeof(kty_item_t));
  if (k == NULL)
    goto fail;
  item->item.i_object = cgc_htbl_create(4, cgc_free_kty_item);
  if (item->item.i_object == NULL)
    goto fail;
  str = cgc_eat_ws(cgc_parse_string(k, cgc_eat_ws(str)));
  key = k->item.i_string.s;
  if (str == NULL || str[0] != ':')
    goto fail;
  str++;
  new = (kty_item_t *) cgc_malloc(sizeof(kty_item_t));
  if (new == NULL)
    goto fail;
  str = cgc_eat_ws(cgc_parse_item(new, cgc_eat_ws(str)));
  if (str == NULL)
    goto fail;
  cgc_htbl_put(item->item.i_object, key, new);
  if (cgc_strcmp("nyan_says", key) == 0 && new->type == KTY_STRING)
  {
    dup = (kty_item_t *) cgc_malloc(sizeof(kty_item_t));
    if (dup == NULL)
      goto fail;
    dup->type = new->type;
    dup->item.i_string.s = cgc_strdup(new->item.i_string.s);
    dup->item.i_string.len = new->item.i_string.len;
    cgc_array_append(g_parser->nyan_says, dup);
    dup = NULL;
  }
  cgc_free_kty_item(k);
  k = NULL;
  new = NULL;

  while (str[0] == ',')
  {
    k = (kty_item_t *) cgc_malloc(sizeof(kty_item_t));
    if (k == NULL)
      goto fail;
    str = cgc_eat_ws(cgc_parse_string(k, cgc_eat_ws(str + 1)));
    key = k->item.i_string.s;
    if (str == NULL || str[0] != ':')
      goto fail;
    str++;
    new = (kty_item_t *) cgc_malloc(sizeof(kty_item_t));
    if (new == NULL)
      goto fail;
    str = cgc_eat_ws(cgc_parse_item(new, cgc_eat_ws(str)));
    if (str == NULL)
      goto fail;
    cgc_htbl_put(item->item.i_object, key, new);
    if (cgc_strcmp("nyan_says", key) == 0 && new->type == KTY_STRING)
    {
      dup = (kty_item_t *) cgc_malloc(sizeof(kty_item_t));
      if (dup == NULL)
        goto fail;
      dup->type = new->type;
      dup->item.i_string.s = cgc_strdup(new->item.i_string.s);
      dup->item.i_string.len = new->item.i_string.len;
      cgc_array_append(g_parser->nyan_says, dup);
      dup = NULL;
    }
    cgc_free_kty_item(k);
    k = NULL;
    new = NULL;
  }

  if (str[0] == '}')
    return str + 1;

fail:
  if (new)
    cgc_free_kty_item(new);
  if (k)
    cgc_free_kty_item(k);
  if (dup)
    cgc_free_kty_item(dup);
  return NULL;
}

char* cgc_parse_item(kty_item_t *item, char *str)
{
  char c;
  if (item && str)
  {
    c = str[0];
    if (cgc_strncmp(str, "true", 4) == 0)
    {
      item->type = KTY_BOOLEAN;
      item->item.i_bool = 1;
      return str + 4;
    }
    if (cgc_strncmp(str, "false", 5) == 0)
    {
      item->type = KTY_BOOLEAN;
      item->item.i_bool = 0;
      return str + 5;
    }
    if (cgc_strncmp(str, "null", 4) == 0)
    {
      item->type = KTY_NULL;
      return str + 4;
    }
    if (cgc_strncmp(str, "=^.^=", 5) == 0)
    {
      item->type = KTY_CAT;
      return str + 5;
    }

    switch (c)
    {
      case '[':
        return cgc_parse_array(item, str);
      case '{':
        return cgc_parse_object(item, str);
      case '-': case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9': case '+':
        return cgc_parse_number(item, str);
      case '\"':
        return cgc_parse_string(item, str);
    }
  }
#if PATCHED
  if (item)
    item->type = KTY_NULL;
#endif
  return NULL;
}

kty_item_t* cgc_kty_loads(char *str)
{
  char *c;
  char string[MAX_KTY_STRING];
  int i = 0, init = 0, state = -1;
  kty_item_t *root;

  root = (kty_item_t *) cgc_calloc(1, sizeof(kty_item_t));
  if (root == NULL)
    goto fail;

  if (g_parser->nyan_says)
    cgc_array_destroy(g_parser->nyan_says);
  g_parser->nyan_says = cgc_array_create(16, cgc_free_kty_item);
  if (g_parser->nyan_says == NULL)
    goto fail;

  c = cgc_parse_item(root, cgc_eat_ws(str));
  if (c == NULL)
    goto fail;

  return root;

fail:
  if (root)
    cgc_free_kty_item(root);
  return NULL;
}

int cgc_kty_init(kty_parser_t *parser)
{
  if (parser)
  {
    parser->cats = 0;
    parser->nyan_says = NULL;
    parser->dumps = cgc_kty_dumps;
    parser->loads = cgc_kty_loads;
    g_parser = parser;
    return 0;
  }
  return -1;
}

void cgc_free_kty_item(void *e)
{
  if (e)
  {
    kty_item_t *item = (kty_item_t *) e;

    switch (item->type)
    {
      case KTY_STRING:
        if (item->item.i_string.s)
          cgc_free(item->item.i_string.s);
        break;
      case KTY_ARRAY:
        cgc_array_destroy(item->item.i_array);
        break;
      case KTY_OBJECT:
        cgc_htbl_destroy(item->item.i_object);
        break;
      default:
        break;
    }
    cgc_free(item);
  }
}
