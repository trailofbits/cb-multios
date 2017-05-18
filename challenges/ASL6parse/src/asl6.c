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

#include "libcgc.h"

#include "cgc_ctype.h"
#include "cgc_stdint.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_asl6.h"

int cgc_fdprintf(int fd, const char *fmt, ...);

#ifndef DEBUG
  #define DBG(s, ...)
#else
  #define DBG(s, ...) fdprintf(STDERR, "DEBUG %s:%d:\t" s "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define ERR(s, ...) cgc_printf("ERROR: " s "\n",##__VA_ARGS__)

const char *tag_class_names[5] = {
  "UNIVERSAL",
  "APPLICATION",
  "CONTEXT",
  "PRIVATE",
  "UNKNOWN"
};

const char *utag_names[31] = {
  "UNKNOWN",
  "BOOLEAN",
  "INTEGER",
  "BITSTR",
  "OCTETSTR",
  "NULL",
  "OID",
  "ODSC",
  "EXT",
  "REAL",
  "ENUM",
  "EPDV",
  "UTFSTR",
  "ROID",
  "UNUSED_TAG",
  "UNUSED_TAG",
  "SEQ",
  "SET",
  "NUMSTR",
  "PRINTSTR",
  "TELESTR",
  "VIDSTR",
  "IA5STR",
  "UTCTIME",
  "GENTIME",
  "GRAPHSTR",
  "VISSTR",
  "GENSTR",
  "UNISTR",
  "CHRSTR",
  "BMPSTR"
};


// Element parsers
static int cgc_parse_tag_class(uint8_t *b, element *e)
{
  tag_class c = (b[0] & CLASS_MASK) >> 6;
  if (c < UNIVERSAL || c > PRIVATE)
    return -1;
  else
    e->cls = c;

  DBG("parsed tag class: %s", tag_class_names[c]);
  return 0;
}

static int cgc_parse_tag(uint8_t *b, element *e)
{
  uint8_t tval;

  tval = *b & TAG_MASK;
  if (tval > 30 || tval < 0)
    return -1;
  else
    e->tag = tval;

  DBG("parsed tag ident: name = %s, primitive = %d", utag_names[e->tag], e->primitive);
  return 0;
}

static int cgc_parse_length(uint8_t *b, element *e)
{
  cgc_size_t num_bytes, i;
  unsigned length;
  if (b[0] < 128) {
    DBG("parsed short form length: length = %d, num_bytes = 1, read = 1", *b);
    e->length = b[0];
    return 1;
  }

  num_bytes = b[0] & ~0x80;
  if (num_bytes > 4) {
    ERR("length too large");
    return -1;
  }

  if (num_bytes == 0) {
    ERR("infinite length");
    return 0;
  }

  b++;
  length = 0;
  for (i = 0; i < num_bytes; i++)
    length = (length << 8) | b[i];

  DBG("parsed long form length: length = %d, num_bytes = %d", length, num_bytes);
  e->length = length;
  return num_bytes + 1;
}

// Helpers
static void cgc_free_element(element *e)
{
  unsigned i;
  if (e != NULL && e->subs != NULL)
    for (i = 0; i < e->nsubs; i++)
      if (e->subs[i] != NULL)
        cgc_free_element(e->subs[i]);

  if (e && e->subs)
    cgc_free(e->subs);
  if (e)
    cgc_free(e);
}

static int cgc_append_sub(element *e, element *sub)
{
  unsigned new_cap;
  if (e->nsubs == e->sub_cap) {
    new_cap = e->sub_cap * 2;
    if (new_cap / e->sub_cap != 2) {
      return -1;
    }

    e->subs = cgc_realloc(e->subs, sizeof(element *) * new_cap);
    if (e->subs == NULL) {
      return -1;
    }
    e->sub_cap = new_cap;
  }

  e->subs[e->nsubs++] = sub;
  return 0;
}

// Decoder
static int cgc_within(uint8_t *b, unsigned length, unsigned st, unsigned sp)
{
  unsigned bu = (unsigned) b;
  if (bu < st || bu >= sp)
    return -1;
#ifdef PATCHED
  else if (((bu + length) < st || (bu + length) > sp) || bu + length < bu)
    return -1;
#endif
  else
    return 0;
}

element *cgc__decode(uint8_t *b, unsigned depth, unsigned st, unsigned sp)
{
  if (cgc_within(b, 0, st, sp) != 0) {
    DBG("b = %x, st = %x, sp = %x\n", b, st, sp);
    ERR("bounds exceeded");
    return NULL;
  }

  element *e = cgc_malloc(sizeof(element));
  if (e == NULL)
    goto ERROR;
  e->sub_cap = DEFAULT_SUB_CAP;
  e->subs = cgc_calloc(sizeof(element *), e->sub_cap);
  if (e->subs == NULL)
    goto ERROR;
  e->nsubs = 0;
  e->depth = depth;
  e->primitive = (b[0] & PRIM_MASK) == 0;

  // Check for issues
  if (cgc_parse_tag_class(b, e) < 0) {
    ERR("unknown class");
    goto ERROR;
  }

  if (cgc_parse_tag(b, e) < 0) {
    ERR("unknown tag");
    goto ERROR;
  }

  // Enforce constructed rules
  if (!e->primitive && (e->tag != SET && e->tag != SEQ)) {
    ERR("bad constructed type");
    goto ERROR;
  }

  if (e->primitive && (e->tag == SET || e->tag == SEQ)) {
    ERR("bad primitive type");
    goto ERROR;
  }

  int bread = cgc_parse_length(b + 1, e);
  if (bread <= 0) {
    goto ERROR;
  }

  // Enforce length rules
  if (e->tag == BOOLEAN && e->length != 1) {
    ERR("invalid length for bool");
    goto ERROR;
  }

  if (e->tag == _NULL && e->length != 0) {
    ERR("invalid length for null");
    goto ERROR;
  }

  bread += 1;
  DBG("header parsing consumed %d bytes", bread);
  e->data = b + bread;
  if (cgc_within(e->data, e->length, st, sp) != 0) {
    ERR("bounds exceeded");
    goto ERROR;
  }

  if (!e->primitive) {
    uint8_t *cur;
    element *sub;
    cur = e->data;
    while (1) {
      sub = cgc__decode(cur, depth + 1, st, sp);
      if (sub == NULL) {
        goto ERROR;
      }

      if (cgc_append_sub(e, sub) < 0) {
        goto ERROR;
      }

      DBG("content parsing consumed %d bytes", sub->length);

      cur = sub->data + sub->length;
      if ((unsigned) cur < st || cur >= e->data + e->length)
        break;

    }
  }

  DBG("parsed packet: class = %s, tag = %s,"
      "type = %s, length = %u, num_subs = %d\n",
      tag_class_names[e->cls], utag_names[e->tag],
      e->primitive == 0 ? "primitive" : "constructed",
      e->length, e->nsubs);

  return e;

ERROR:
  cgc_free_element(e);
  return NULL;
}

element *cgc_decode(uint8_t *b, unsigned end)
{
  return cgc__decode(b, 0, (unsigned) b, end);
}

// Pretty Printers
static void cgc_print_indent(unsigned depth)
{
  unsigned i;
  for (i = 0; i < depth; i++)
    cgc_printf("    ");
}

static void cgc_print_time(element *e, int utc)
{
  uint8_t *d = e->data;
  unsigned req_len = utc ? 12 : 14;
  unsigned i;

  if (e->length < req_len) {
    cgc_printf("INVALID TIME");
    return;
  }

  for (i = 0; i < req_len; i++)
    if (!cgc_isdigit(d[i])) {
      cgc_printf("INVALID TIME");
      return;
    }

  if (utc) {
    cgc_printf("%c%c/%c%c/", d[4], d[5], d[2], d[3]);
    if (e->data[0] < '6')
      cgc_printf("%s", "20");
    else
      cgc_printf("%s", "19");
    cgc_printf("%c%c", d[0], d[1]);
  } else {
    cgc_printf("%c%c/%c%c/%c%c%c%c",
        d[6], d[7], d[4], d[5],
        d[0], d[1], d[2], d[3]);
    d += 2;
  }

  cgc_printf(" %c%c:%c%c:%c%c GMT", d[6], d[7], d[8], d[9], d[10], d[11]);
}

static void cgc_print_hex(element *e)
{
  unsigned i;
  if (e->length > 16) {
    cgc_printf("\n");
    cgc_print_indent(e->depth + 1);
    for (i = 0; i < e->length; i++) {
      cgc_printf("%02X", e->data[i]);
      if (i % 32 == 31) {
        cgc_printf("\n");
        cgc_print_indent(e->depth + 1);
      } else {
        cgc_printf(" ");
      }
    }
  } else {
    for (i = 0; i < e->length; i++) {
      cgc_printf("%02X ", e->data[i]);
    }
  }
}

static int cgc_read_octet_int(uint8_t *b, unsigned max, unsigned long *v)
{
  unsigned i;

  *v = 0;
  for (i = 0; i < 4 && i < max; i++) {
    *v <<= 7;
    *v |= (b[i] & ~0x80);
    if ((b[i] & 0x80) == 0) {
      return i + 1;
    }
  }

  return -1;
}

static void cgc_print_oid(element *e)
{
  unsigned i = 0;
  int ret;
  unsigned long v = 0;
  while (1) {
    if (i == 0) {
      ret = cgc_read_octet_int(&e->data[i], e->length, &v);
      if (ret < 0) {
        return;
      }

      i = ret;
      if (i >= e->length) {
        return;
      }

      if (v == 80)
        return;

      if (v < 80) {
        cgc_printf("%u", v / 40);
        cgc_printf(".%u", v % 40);
      } else {
        cgc_printf("2");
        cgc_printf(".%u", v - 80);
      }
    }

#ifdef PATCHED
    ret = cgc_read_octet_int(&e->data[i], e->length - i, &v);
#else
    ret = cgc_read_octet_int(&e->data[i], e->length, &v);
#endif
    if (ret < 0) {
      return;
    }

    i += ret;

#ifdef PATCHED
    if (i >= e->length)
      return;
#endif

    cgc_printf(".%u", v);
  }
}

static void cgc_print_tag(element *e)
{
  switch (e->cls) {
  case UNIVERSAL:
    if (e->tag < 0 || e->tag >= sizeof(utag_names) / sizeof(char *))
      cgc_printf("UNIVERSAL_%d ", e->tag);
    else
      cgc_printf("UNIVERSAL %s ", utag_names[e->tag]);
    break;
  case APPLICATION:
    cgc_printf("APPLICATION_%d ", e->tag);
    break;
  case CONTEXT:
    cgc_printf("[%d] ", e->tag);
    break;
  case PRIVATE:
    cgc_printf("PRIVATE_%d ", e->tag);
    break;
  default:
    cgc_printf("UNKNOWN_%d ", e->tag);
    break;
  }
}

static void cgc_print_string(element *e)
{
  unsigned i;
  for (i = 0; i < e->length; i++)
    if (cgc_isalnum(e->data[i]))
      cgc_printf("%c", e->data[i]);
    else
      cgc_printf("\\x%x", e->data[i]);
}

static void cgc_print_primitive(element *e)
{
  switch(e->cls) {
  case UNIVERSAL:
    switch(e->tag) {
    case BOOLEAN:
      cgc_printf("%s", e->data[0] == 0 ? "False" : "True");
      return;
    case INTEGER:
    case BITSTR:
    case OCTETSTR:
      cgc_print_hex(e);
      return;
    case OID:
      cgc_print_oid(e);
      return;
    case UTCTIME:
      cgc_print_time(e, 1);
      return;
    case GENTIME:
      cgc_print_time(e, 0);
      return;
    case UTFSTR:
    case NUMSTR:
    case PRINTSTR:
    case TELESTR:
    case VIDSTR:
    case IA5STR:
    case VISSTR:
      cgc_print_string(e);
      return;
    default:
      break;
    }
  default:
    break;
  }

  cgc_printf("UNPRINTABLE");
}

void cgc_pprint(element *e)
{
  unsigned i;
  cgc_print_indent(e->depth);
  cgc_print_tag(e);

  if (e->primitive) {
    cgc_print_primitive(e);
    cgc_printf("\n");
  } else {
    cgc_printf("\n");
    for (i = 0; i < e->nsubs; i++)
      cgc_pprint(e->subs[i]);
  }

  if (e->depth == 0)
    cgc_free_element(e);
}
