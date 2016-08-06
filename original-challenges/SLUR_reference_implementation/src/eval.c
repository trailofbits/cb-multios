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
#include <libcgc.h>

#include <stdlib.h>
#include <string.h>

#include "exp.h"
#include "tokenize.h"

static exp_t *eval(exp_t *e, sym_list *s);

static exp_t *parse(tok_list *toks,  tok_list **adv)
{
  if (!toks)
    return NULL;

  if (strncmp(toks->value, "(", strlen("(")) == 0) {
    tok_list *nt = NULL;
    toks = toks->next;
    exp_t *e1 = parse(toks, &nt);
    toks = nt;
    exp_t *e2 = parse(toks, &nt);
    if (adv)
      *adv = nt;
    exp_t *c;
    CONZ(&c, e1, e2);
    if (!c)
      exit(1);
    return c;
  } else if (strncmp(toks->value, ")", strlen(")")) == 0) {
    if (adv)
      *adv = toks->next;
    return NULL;
  } else {
    tok_list *nt = NULL;
    exp_t *a = NEWE();
    if (!a)
      exit(1);
    a->t = ATOM;
    a->name = toks->value;
    toks = toks->next;
    exp_t *e2 = parse(toks, &nt);
    if (adv)
      *adv = nt;
    exp_t *c;
    CONZ(&c, a, e2);
    if (!c)
      exit(1);

    return c;
  }
}

static void print(exp_t *e)
{
  if (!e)
    return;

  if (ATOMP(e)) {
    printf("%s", e->name);
  } else {
    printf("(");

    while (e) {
      print(CAR(e));
      e = CDR(e);
      if (!e || !CONSP(e))
        break;
      printf(" ");
    }
    printf(")");
  }
}

static exp_t *find_sym(sym_list *s, char *sym)
{
  if (!s || !sym) {
    return NULL;
  }

  sym_list *c = s;
  while (c && c->value && c->value->key) {
    if (strcmp(c->value->key, sym) == 0)
      return c->value->e;
    c = c->next;
  }

  return NULL;
}

DEF_LIST_APPEND(sym, sym_t *);

static sym_t *make_fp(char *name, void *f)
{
  sym_t *cf = malloc(sizeof(sym_list));
  if (!cf)
    exit(1);
  cf->key = calloc(1, strlen(name) + 1);
  strncpy(cf->key, name, strlen(name));
  cf->e = NEWE();
  if (!cf->e)
    exit(1);
  cf->e->t = FUNC;
  cf->e->f = f;
  if (!cf->key || !cf->e)
    exit(1);
  return cf;
}

exp_t *quote_fn(exp_t *e, sym_list *s)
{
  if (!e) {
    return NULL;
  }
  return CAR(e);
}

exp_t *car_fn(exp_t *e, sym_list *s)
{
  if (!e || !CAR(e) || !CONSP(CAR(e))) {
    return NULL;
  }
  return CAR(CAR(e));
}

exp_t *cdr_fn(exp_t *e, sym_list *s)
{
  if (!e || !CAR(e)) {
    return NULL;
  }
  return CDR(CAR(e));
}

exp_t *cons_fn(exp_t *e, sym_list *s)
{
  if (!e || !s) {
    return NULL;
  }

  // 2 args
  if (!CAR(e) || !CDR(e)) {
    return NULL;
  }

  // e2 is list
  if (!CONSP(CDR(e))) {
    return NULL;
  }

  exp_t *cons = NEWE();
  cons->t = CONS;
  cons->car = CAR(e);
  exp_t *i = CAR(CDR(e));
  while (i && CONSP(i)) {
    APPEND(cons, CAR(i));
    i = CDR(i);
  }

  return cons;
}

exp_t *equal_fn(exp_t *e, sym_list *s)
{
  if (!e || !CAR(e) || !CDR(e) ||
      !CAR(e)->name || !CAR(CDR(e)) ||
      !CAR(CDR(e))->name) {
    return NULL;
  }

  if (strcmp(CAR(e)->name, CAR(CDR(e))->name) == 0)
      return find_sym(s, "t");
  else
      return find_sym(s, "nil");
}

exp_t *atom_fn(exp_t *e, sym_list *s)
{
  if (!e || !CAR(e)) {
    return NULL;
  }

  if (CAR(e)->t == ATOM)
    return find_sym(s, "t");
  else
    return find_sym(s, "nil");
}

exp_t *cond_fn(exp_t *e, sym_list *s)
{
  if (!e) {
    return NULL;
  }

  exp_t *res = NULL;

  for (;;) {
    if (!e || !CAR(e) || !CONSP(CAR(e)))
      break;

    exp_t *cond = CAR(CAR(e));
    if (!CDR(CAR(e)))
        break;
    exp_t *resp = CAR(CDR(CAR(e)));

    if (eval(cond, s) == find_sym(s, "t")) {
      res = eval(resp, s);
      break;
    }

    e = CDR(e);
  }

  return res;
}

static exp_t *get(size_t n, exp_t *l)
{
  exp_t *li = l;

  while (li && n--) {
    li = CDR(li);
  }

  if (!li) {
    return NULL;
  }

  return CAR(li);
}

// :: [(ATOM, EXP)] -> EXP -> EXP
static exp_t *subst(exptup_list *z, exp_t *e)
{
  if (!z || !e) {
    return NULL;
  }

  if (ATOMP(e)) {
    while (z) {
#ifdef PATCHED
      if (z->value && z->value->fst && z->value->fst->name && strcmp(e->name, z->value->fst->name) == 0)
#else
      if (strcmp(e->name, z->value->fst->name) == 0)
#endif
        return z->value->snd;
      else
        z = z->next;
    }

    return e;
  }

  exp_t *ne = NEWE();
  if (!ne)
    exit(1);

  while (e && CONSP(e)) {
    APPEND(ne, subst(z, CAR(e)));
    e = CDR(e);
  }

  return ne;
}

DEF_LIST_APPEND(exptup, exptup_t *);

exp_t *lambda(exp_t *l, exp_t *e, sym_list *s)
{
  if (!l || !e || !s) {
    return NULL;
  }

  // Zip up bound vars with args
  exptup_list *z = malloc(sizeof(exptup_list));
  if (!z)
    exit(1);

  size_t n = 0;
  for (;;) {
      exp_t *cur_bnd = get(n, l->bound_vars);
      exp_t *cur_arg = get(n, e);
      if (!cur_bnd && !cur_arg)
        break;

      exptup_t *ele = malloc(sizeof(exptup_t));
      if (!ele)
        exit(1);

      ele->fst = cur_bnd;
      ele->snd = cur_arg;
      if (!ele->fst || !ele->snd) {
        return NULL;
      }

      exptup_list_append(z, ele);
      n++;
  }

  exp_t *sub = subst(z->next, l->exp);
  exp_t *ret = eval(sub, s);

  if (!ret)
    return NULL;

  size_t cnt = 0;
  exp_t *cake = ret;
  for (cnt = 0; cnt < 4; cnt++) {
    if (cake && CAR(cake) && ATOMP(CAR(cake)) && strncmp(CAR(cake)->name, "CAKE", strlen("CAKE")) == 0) {
      if (cake && CDR(cake) && CONSP(CDR(cake))) {
        cake = CDR(cake);
        continue;
      }
    }

    break;
  }

  if (cnt == 4) {
    exp_t *n = NEWE();
    exp_t *a = NEWE();
    if (!n || !a)
      exit(1);

    a->t = ATOM;
    a->name = "That's a lot of CAKE!";
    n->t = CONS;
    n->car = a;
    n->cdr = NULL;

#ifdef PATCHED
    CDR(cake) = n;
#else
    CDR(CDR(cake)) = n;
#endif
  }

  return ret;
}


static sym_list *make_syms(void) {
  sym_list *s = malloc(sizeof(sym_list));
  if (!s) {
    return NULL;
  }
  sym_t *cf;

  cf = make_fp("quote", quote_fn);
  sym_list_append(s, cf);

  cf = make_fp("car", car_fn);
  sym_list_append(s, cf);

  cf = make_fp("cdr", cdr_fn);
  sym_list_append(s, cf);

  cf = make_fp("cons", cons_fn);
  sym_list_append(s, cf);

  cf = make_fp("equal", equal_fn);
  sym_list_append(s, cf);

  cf = make_fp("atom", atom_fn);
  sym_list_append(s, cf);

  cf = make_fp("cond", cond_fn);
  sym_list_append(s, cf);

  sym_t *nil = malloc(sizeof(sym_list));
  if (!nil)
    exit(1);
  nil->key = calloc(1, strlen("nil") + 1);
  if (!nil->key)
    exit(1);
  strncpy(nil->key, "nil", strlen("nil"));
  nil->e = NEWE();
  if (!nil->e)
    exit(1);
  nil->e->t = CONS;
  sym_list_append(s, nil);

  sym_t *t = malloc(sizeof(sym_list));
  if (!t)
    exit(1);
  t->key = calloc(1, strlen("t") + 1);
  if (!t->key)
    exit(1);
  strncpy(t->key, "t", strlen("t"));
  t->e = malloc(sizeof(exp_t));
  if (!t->e)
    exit(1);
  t->e->t = ATOM;
  t->e->name = t->key;
  sym_list_append(s, t);

  return s->next;
}

static exp_t *eval(exp_t *e, sym_list *s)
{
  if (!e) {
    return NULL;
  }

  if (ATOMP(e)) {
    exp_t *le = find_sym(s, e->name);
    if (!le)
      return e;
    else
      return le;
  }

  if (!CAR(e))
    return NULL;

  if (ATOMP(CAR(e)) && strncmp(CAR(e)->name, "lambda", strlen("lambda")) == 0) {
    if (!CDR(e) || !CDR(CDR(e)) || !CAR(CDR(CDR(e)))) {
      return NULL;
    }
    exp_t *le = NEWE();
    if (!le)
      exit(1);
    le->t = LAMB;
    le->bound_vars = CAR(CDR(e));
    le->exp = CAR(CDR(CDR(e)));
    return le;
  }

  // Eval func
  exp_t *f = eval(CAR(e), s);

  if (f == NULL) {
    return NULL;
  }

  exp_t *l;
  CONZ(&l, f, NULL);

  // Eval args
  exp_t *a = CDR(e);
  while (a && CONSP(a)) {
    exp_t *ev = eval(CAR(a), s);
    APPEND(l, ev);
    a = CDR(a);
  }

  if (CAR(l)->t == LAMB) {
    return lambda(CAR(l), CDR(l), s);
  }

  if (CAR(l)->t == FUNC) {
    return CAR(l)->f(CDR(l), s);
  }

  return l;
}

int repl(char *expr)
{
  tok_list *toks = tokenize(expr);
  if (toks && toks->value && strncmp(toks->value, "(", strlen(toks->value)) == 0) {
    exp_t *prog = parse(toks->next, NULL);
    sym_list *syms = make_syms();
    exp_t *ed = eval(prog, syms);
    if (!ed)
      return -1;
    print(eval(prog, syms));
    return 0;
  } else {
    return -1;
  }
}
