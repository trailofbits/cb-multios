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

#include <stdlib.h>
#include <string.h>
#include "kty.h"
#include "strdup.h"
#include "strncmp.h"
#include "strtod.h"

kty_parser_t *g_parser;

void kty_print_item(kty_item_t *item, int depth);
char* parse_item(kty_item_t *item, char *str);

char* eat_ws(char *str)
{
  while (str && str[0] && str[0] <= ' ')
    str++;
  return str;
}

void print_escaped(char *str, int len)
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
        fdprintf(STDOUT, "\\\""); break;
      case '\\':
        fdprintf(STDOUT, "\\\\"); break;
      case '/':
        fdprintf(STDOUT, "\\/");  break;
      case '\b':
        fdprintf(STDOUT, "\\b");  break;
      case '\f':
        fdprintf(STDOUT, "\\f");  break;
      case '\n':
        fdprintf(STDOUT, "\\n");  break;
      case '\r':
        fdprintf(STDOUT, "\\r");  break;
      case '\t':
        fdprintf(STDOUT, "\\t");  break;
      default:
        fdprintf(STDOUT, "%s", c); break;
    }
  }
}

void print_indent(int depth)
{
  int i;
  for (i = 0; i < depth * 2; ++i)
    fdprintf(STDOUT, " ");
}

void kty_int_to_string(kty_item_t *item)
{
  fdprintf(STDOUT, "%d", item->item.i_int);
}

void kty_double_to_string(kty_item_t *item)
{
  int tmp;
  double val;

  val = item->item.i_double;
  tmp = (int) val;
  if (val < 0.0 && tmp == 0)
    fdprintf(STDOUT, "-");
  fdprintf(STDOUT, "%d.", tmp);
  tmp = ((int)(val * 100.0)) % 100;
  if (tmp < 0)
    tmp = -tmp;
  fdprintf(STDOUT, "%02d", tmp);
}

void kty_string_to_string(kty_item_t *item)
{
  fdprintf(STDOUT, "\"");
  print_escaped(item->item.i_string.s, item->item.i_string.len);
  fdprintf(STDOUT, "\"");
}

void kty_object_to_string(kty_item_t *item, int depth)
{
  int count = 0;
  htbl_t *table;
  entry_t *entry;

  fdprintf(STDOUT, "{");
  table = item->item.i_object;
  if (table)
  {
    fdprintf(STDOUT, "\n");
    for (entry = table->head; entry != NULL ; entry = entry->next)
    {
      if (count > 0)
        fdprintf(STDOUT, ",\n");
      count++;
      print_indent(depth + 1);
      fdprintf(STDOUT, "\"");
      print_escaped(entry->key, strlen(entry->key));
      fdprintf(STDOUT, "\": ");
      kty_print_item(entry->val, depth + 1);
    }
  }
  if (count > 0)
  {
    fdprintf(STDOUT, "\n");
    print_indent(depth);
  }
  fdprintf(STDOUT, "}");
}

void kty_array_to_string(kty_item_t *item, int depth)
{
  int i, count = 0;
  kty_item_t *elem;

  fdprintf(STDOUT, "[");
  if (array_length(item->item.i_array) > 0)
    fdprintf(STDOUT, "\n");
  for (i = 0; i < array_length(item->item.i_array); ++i)
  {
    if (count > 0)
      fdprintf(STDOUT, ",\n");
    count++;
    print_indent(depth + 1);
    elem = array_get(item->item.i_array, i);
    kty_print_item(elem, depth + 1);
  }
  if (count > 0)
  {
    fdprintf(STDOUT, "\n");
    print_indent(depth);
  }
  fdprintf(STDOUT, "]");
}

void kty_boolean_to_string(kty_item_t *item)
{
  fdprintf(STDOUT, "%s", item->item.i_bool ? "true" : "false");
}

void kty_null_to_string(kty_item_t *item)
{
  fdprintf(STDOUT, "null");
}

void kty_cat_to_string(kty_item_t *item)
{
  g_parser->cats++;
  fdprintf(STDOUT, "=^.^=");
}

void kty_print_item(kty_item_t *item, int depth)
{
  switch (item->type)
  {
    case KTY_INT:
      kty_int_to_string(item);
      break;
    case KTY_DOUBLE:
      kty_double_to_string(item);
      break;
    case KTY_STRING:
      kty_string_to_string(item);
      break;
    case KTY_OBJECT:
      kty_object_to_string(item, depth);
      break;
    case KTY_ARRAY:
      kty_array_to_string(item, depth);
      break;
    case KTY_BOOLEAN:
      kty_boolean_to_string(item);
      break;
    case KTY_NULL:
      kty_null_to_string(item);
      break;
    case KTY_CAT:
      kty_cat_to_string(item);
      break;
    default:
      break;
  }
}

void kty_dumps(kty_item_t *kty)
{
  int depth = 0;
  g_parser->cats = 0;
  if (kty)
  {
    kty_print_item(kty, depth);
  }
}

char* parse_number(kty_item_t *item, char *str)
{
  char decimal[3] = {0};
  char *c1, *c2;
  int i;
  double d;

  c1 = strchr(str, ' ');
  if (c1 == NULL)
    c1 = strchr(str, ',');
  if (c1 == NULL)
    c1 = strchr(str, ']');
  if (c1 == NULL)
    c1 = strchr(str, '}');
  c2 = strchr(str, '.');
  if ((c1 && c2 && c2 < c1) || (c2 && c1 == NULL))
  {
    // Double
    d = strtod(str, &str);
    item->type = KTY_DOUBLE;
    item->item.i_double = d;
  }
  else
  {
    // Int
    i = strtol(str, &str, 10);
    item->type = KTY_INT;
    item->item.i_int = i;
  }

  return str;
}

char* parse_string(kty_item_t *item, char *str)
{
  int read = 0, len = 0;
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
      read++;
    }
    c++;
    len++;
    read++;
  }

  if (len >= MAX_KTY_STRING)
    return NULL;
  item->item.i_string.s = malloc(len + 1);
  if (item->item.i_string.s == NULL)
    return NULL;

  c = str + 1;
  read += 2;
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

  return str + read;
}

char* parse_array(kty_item_t *item, char *str)
{
  kty_item_t *new;

  item->type = KTY_ARRAY;
  item->item.i_array = NULL;
  str = eat_ws(str + 1);
  if (str[0] == ']')
    return str + 1;

  new = (kty_item_t *) malloc(sizeof(kty_item_t));
  if (new == NULL)
    goto fail;
  item->item.i_array = array_create(4, free_kty_item);
  if (item->item.i_array == NULL)
    goto fail;
  str = eat_ws(parse_item(new, eat_ws(str)));
  if (str == NULL)
    goto fail;
  array_append(item->item.i_array, new);
  new = NULL;

  while (str[0] == ',')
  {
    new = (kty_item_t *) malloc(sizeof(kty_item_t));
    if (new == NULL)
      goto fail;
    str++;
    str = eat_ws(parse_item(new, eat_ws(str)));
    if (str == NULL)
      goto fail;
    array_append(item->item.i_array, new);
    new = NULL;
  }

  if (str[0] == ']')
    return str + 1;

fail:
  if (new)
    free_kty_item(new);
  return NULL;
}

char* parse_object(kty_item_t *item, char *str)
{
  char *key = NULL;
  kty_item_t *new = NULL, *k = NULL, *dup = NULL;

  item->type = KTY_OBJECT;
  item->item.i_object = NULL;

  str = eat_ws(str + 1);
  if (str[0] == '}')
    return str + 1;

  k = (kty_item_t *) malloc(sizeof(kty_item_t));
  if (k == NULL)
    goto fail;
  item->item.i_object = htbl_create(4, free_kty_item);
  if (item->item.i_object == NULL)
    goto fail;
  str = eat_ws(parse_string(k, eat_ws(str)));
  key = k->item.i_string.s;
  if (str == NULL || str[0] != ':')
    goto fail;
  str++;
  new = (kty_item_t *) malloc(sizeof(kty_item_t));
  if (new == NULL)
    goto fail;
  str = eat_ws(parse_item(new, eat_ws(str)));
  if (str == NULL)
    goto fail;
  htbl_put(item->item.i_object, key, new);
  if (strcmp("nyan_says", key) == 0 && new->type == KTY_STRING)
  {
    dup = (kty_item_t *) malloc(sizeof(kty_item_t));
    if (dup == NULL)
      goto fail;
    dup->type = new->type;
    dup->item.i_string.s = strdup(new->item.i_string.s);
    dup->item.i_string.len = new->item.i_string.len;
    array_append(g_parser->nyan_says, dup);
    dup = NULL;
  }
  free_kty_item(k);
  k = NULL;
  new = NULL;

  while (str[0] == ',')
  {
    k = (kty_item_t *) malloc(sizeof(kty_item_t));
    if (k == NULL)
      goto fail;
    str = eat_ws(parse_string(k, eat_ws(str + 1)));
    key = k->item.i_string.s;
    if (str == NULL || str[0] != ':')
      goto fail;
    str++;
    new = (kty_item_t *) malloc(sizeof(kty_item_t));
    if (new == NULL)
      goto fail;
    str = eat_ws(parse_item(new, eat_ws(str)));
    if (str == NULL)
      goto fail;
    htbl_put(item->item.i_object, key, new);
    if (strcmp("nyan_says", key) == 0 && new->type == KTY_STRING)
    {
      dup = (kty_item_t *) malloc(sizeof(kty_item_t));
      if (dup == NULL)
        goto fail;
      dup->type = new->type;
      dup->item.i_string.s = strdup(new->item.i_string.s);
      dup->item.i_string.len = new->item.i_string.len;
      array_append(g_parser->nyan_says, dup);
      dup = NULL;
    }
    free_kty_item(k);
    k = NULL;
    new = NULL;
  }

  if (str[0] == '}')
    return str + 1;

fail:
  if (new)
    free_kty_item(new);
  if (k)
    free_kty_item(k);
  if (dup)
    free_kty_item(dup);
  return NULL;
}

char* parse_item(kty_item_t *item, char *str)
{
  char c;
  if (item && str)
  {
    c = str[0];
    if (strncmp(str, "true", 4) == 0)
    {
      item->type = KTY_BOOLEAN;
      item->item.i_bool = 1;
      return str + 4;
    }
    if (strncmp(str, "false", 5) == 0)
    {
      item->type = KTY_BOOLEAN;
      item->item.i_bool = 0;
      return str + 5;
    }
    if (strncmp(str, "null", 4) == 0)
    {
      item->type = KTY_NULL;
      return str + 4;
    }
    if (strncmp(str, "=^.^=", 5) == 0)
    {
      item->type = KTY_CAT;
      return str + 5;
    }

    switch (c)
    {
      case '[':
        return parse_array(item, str);
      case '{':
        return parse_object(item, str);
      case '-': case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9': case '+':
        return parse_number(item, str);
      case '\"':
        return parse_string(item, str);
    }
  }
#if PATCHED
  if (item)
    item->type = KTY_NULL;
#endif
  return NULL;
}

kty_item_t* kty_loads(char *str)
{
  char *c;
  char string[MAX_KTY_STRING];
  int i = 0, init = 0, state = -1;
  kty_item_t *root;

  root = (kty_item_t *) calloc(1, sizeof(kty_item_t));
  if (root == NULL)
    goto fail;

  if (g_parser->nyan_says)
    array_destroy(g_parser->nyan_says);
  g_parser->nyan_says = array_create(16, free_kty_item);
  if (g_parser->nyan_says == NULL)
    goto fail;

  c = parse_item(root, eat_ws(str));
  if (c == NULL)
    goto fail;

  return root;

fail:
  if (root)
    free_kty_item(root);
  return NULL;
}

int kty_init(kty_parser_t *parser)
{
  if (parser)
  {
    parser->cats = 0;
    parser->nyan_says = NULL;
    parser->dumps = kty_dumps;
    parser->loads = kty_loads;
    g_parser = parser;
    return 0;
  }
  return -1;
}

void free_kty_item(void *e)
{
  if (e)
  {
    kty_item_t *item = (kty_item_t *) e;

    switch (item->type)
    {
      case KTY_STRING:
        if (item->item.i_string.s)
          free(item->item.i_string.s);
        break;
      case KTY_ARRAY:
        array_destroy(item->item.i_array);
        break;
      case KTY_OBJECT:
        htbl_destroy(item->item.i_object);
        break;
      default:
        break;
    }
    free(item);
  }
}
