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
#ifndef __EXP_H_
#define __EXP_H_

#include "list.h"

/*
 * CONS = Cons EXP CONS | Nil
 * EXP = ATOM | CONS
 * ATOM = STR
 */
enum exp_type {
  ATOM = 1,
  FUNC,
  CONS,
  LAMB
};

struct sym_list;

typedef struct exp_t {
  enum exp_type t;
  /* ATOM / FUNC */
  char *name;

  /* FUNC */
  struct exp_t *(*f)(struct exp_t *, struct sym_list *);

  /* CONS ^ LAMBDA */
  union {
    struct exp_t *car;
    struct exp_t *bound_vars;
  };

  union {
    struct exp_t *cdr;
    struct exp_t *exp;
  };

  /* CONS */
} exp_t;

typedef struct {
  exp_t *fst;
  exp_t *snd;
} exptup_t;

DEF_LIST(exptup, exptup_t *);

typedef struct {
  char *key;
  exp_t *e;
} sym_t;

DEF_LIST(sym, sym_t *);

#define NEWE() (calloc(1, sizeof(exp_t)))

#define ATOM(e, s) \
  do { \
    if (e == NULL) \
      break; \
    if (s == NULL) { \
      *e = NULL; \
      break; \
    } \
    *e = NEWE(); \
    if (*e == NULL) \
      break; \
    e->t = ATOM; \
    e->name = s; \
    e->car = NULL; \
    e->cdr = NULL; \
  } while (0)

#define CONZ(e, e1, e2) \
  do { \
    if (e == NULL) \
      break; \
    *e = NEWE(); \
    if (*e == NULL) \
      break; \
    (*e)->t = CONS; \
    (*e)->car = e1; \
    (*e)->cdr = e2; \
    (*e)->name = NULL; \
  } while(0)

#define APPEND(l, e) \
  do { \
    exp_t *li = l; \
    li->t = CONS; \
    while (li && CDR(li)) \
      li = CDR(li); \
    /* Empty list case */ \
    if (!CAR(li)) { \
      li->car = e; \
      li->cdr = NULL; \
      break; \
    } else { \
      CONZ(&CDR(li), e, NULL); \
      if (CDR(li) == NULL) \
        exit(1); \
    } \
  } while (0)

#define CAR(e) (e->car)
#define CDR(e) (e->cdr)
#define CADR(e) (e->cdr ? NULL : e->cdr->car)
#define CDAR(e) (e->car ? NULL : e->car->cdr)

#define CONSP(e) (e->t == CONS)
#define ATOMP(e) (e->t == ATOM)


#endif /* __EXP_H_ */
