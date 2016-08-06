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

#ifndef __ASL6_H__
#define __ASL6_H__

#define DEFAULT_SUB_CAP 2
#define PRIM_MASK 0x20
#define TAG_MASK 0x1F
#define CLASS_MASK 0xC0

#define EOC 0x00

typedef uint8_t bool;

typedef struct element {
  uint8_t cls;
  uint8_t tag;
  bool primitive;
  uint8_t *data;
  unsigned length;
  unsigned depth;
  unsigned sub_cap;
  unsigned nsubs;
  struct element **subs;
} element;

typedef enum {
  UNIVERSAL,
  APPLICATION,
  CONTEXT,
  PRIVATE,
  CLASS_UNKNOWN
} tag_class;

typedef enum {
  TAG_UNKNOWN = 0,
  BOOLEAN = 1,
  INTEGER = 2,
  BITSTR = 3,
  OCTETSTR = 4,
  _NULL = 5,
  OID = 6,
  ODSC = 7,
  EXT = 8,
  REAL = 9,
  ENUM = 10,
  EPDV = 11,
  UTFSTR = 12,
  ROID = 13,

  SEQ = 16,
  SET = 17,
  NUMSTR = 18,
  PRINTSTR = 19,
  TELESTR = 20,
  VIDSTR = 21,
  IA5STR = 22,
  UTCTIME = 23,
  GENTIME = 24,
  GRAPHSTR = 25,
  VISSTR = 26,
  GENSTR = 27,
  UNISTR = 28,
  CHRSTR = 29,
  BMPSTR = 30
} utag;

element *decode(uint8_t *b, unsigned max);
void pprint(element *e);
#endif /* __ASL6_H__ */
