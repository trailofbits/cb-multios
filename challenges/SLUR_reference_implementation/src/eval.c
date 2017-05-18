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

#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_exp.h"
#include "cgc_tokenize.h"

static exp_t *cgc_eval(exp_t *e, sym_list *s);

static exp_t *cgc_parse(tok_list *toks,  tok_list **adv)
{
  if (!toks)
    return NULL;

  if (cgc_strncmp(toks->value, "(", cgc_strlen("(")) == 0) {
    tok_list *nt = NULL;
    toks = toks->next;
    exp_t *e1 = cgc_parse(toks, &nt);
    toks = nt;
    exp_t *e2 = cgc_parse(toks, &nt);
    if (adv)
      *adv = nt;
    exp_t *c;
    CONZ(&c, e1, e2);
    if (!c)
      cgc_exit(1);
    return c;
  } else if (cgc_strncmp(toks->value, ")", cgc_strlen(")")) == 0) {
    if (adv)
      *adv = toks->next;
    return NULL;
  } else {
    tok_list *nt = NULL;
    exp_t *a = NEWE();
    if (!a)
      cgc_exit(1);
    a->t = ATOM;
    a->name = toks->value;
    toks = toks->next;
    exp_t *e2 = cgc_parse(toks, &nt);
    if (adv)
      *adv = nt;
    exp_t *c;
    CONZ(&c, a, e2);
    if (!c)
      cgc_exit(1);

    return c;
  }
}

static void cgc_print(exp_t *e)
{
  if (!e)
    return;

  if (ATOMP(e)) {
    cgc_printf("%s", e->name);
  } else {
    cgc_printf("(");

    while (e) {
      cgc_print(CAR(e));
      e = CDR(e);
      if (!e || !CONSP(e))
        break;
      cgc_printf(" ");
    }
    cgc_printf(")");
  }
}

static exp_t *find_sym(sym_list *s, char *sym)
{
  if (!s || !sym) {
    return NULL;
  }

  sym_list *c = s;
  while (c && c->value && c->value->key) {
    if (cgc_strcmp(c->value->key, sym) == 0)
      return c->value->e;
    c = c->next;
  }

  return NULL;
}

DEF_LIST_APPEND(sym, sym_t *);

static sym_t *cgc_make_fp(char *name, void *f)
{
  sym_t *cf = cgc_malloc(sizeof(sym_list));
  if (!cf)
    cgc_exit(1);
  cf->key = cgc_calloc(1, cgc_strlen(name) + 1);
  cgc_strncpy(cf->key, name, cgc_strlen(name));
  cf->e = NEWE();
  if (!cf->e)
    cgc_exit(1);
  cf->e->t = FUNC;
  cf->e->f = f;
  if (!cf->key || !cf->e)
    cgc_exit(1);
  return cf;
}

exp_t *cgc_quote_fn(exp_t *e, sym_list *s)
{
  if (!e) {
    return NULL;
  }
  return CAR(e);
}

exp_t *cgc_car_fn(exp_t *e, sym_list *s)
{
  if (!e || !CAR(e) || !CONSP(CAR(e))) {
    return NULL;
  }
  return CAR(CAR(e));
}

exp_t *cgc_cdr_fn(exp_t *e, sym_list *s)
{
  if (!e || !CAR(e)) {
    return NULL;
  }
  return CDR(CAR(e));
}

exp_t *cgc_cons_fn(exp_t *e, sym_list *s)
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

exp_t *cgc_equal_fn(exp_t *e, sym_list *s)
{
  if (!e || !CAR(e) || !CDR(e) ||
      !CAR(e)->name || !CAR(CDR(e)) ||
      !CAR(CDR(e))->name) {
    return NULL;
  }

  if (cgc_strcmp(CAR(e)->name, CAR(CDR(e))->name) == 0)
      return find_sym(s, "t");
  else
      return find_sym(s, "nil");
}

exp_t *cgc_atom_fn(exp_t *e, sym_list *s)
{
  if (!e || !CAR(e)) {
    return NULL;
  }

  if (CAR(e)->t == ATOM)
    return find_sym(s, "t");
  else
    return find_sym(s, "nil");
}

exp_t *cgc_cond_fn(exp_t *e, sym_list *s)
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

    if (cgc_eval(cond, s) == find_sym(s, "t")) {
      res = cgc_eval(resp, s);
      break;
    }

    e = CDR(e);
  }

  return res;
}

static exp_t *get(cgc_size_t n, exp_t *l)
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
static exp_t *cgc_subst(exptup_list *z, exp_t *e)
{
  if (!z || !e) {
    return NULL;
  }

  if (ATOMP(e)) {
    while (z) {
#ifdef PATCHED
      if (z->value && z->value->fst && z->value->fst->name && cgc_strcmp(e->name, z->value->fst->name) == 0)
#else
      if (cgc_strcmp(e->name, z->value->fst->name) == 0)
#endif
        return z->value->snd;
      else
        z = z->next;
    }

    return e;
  }

  exp_t *ne = NEWE();
  if (!ne)
    cgc_exit(1);

  while (e && CONSP(e)) {
    APPEND(ne, cgc_subst(z, CAR(e)));
    e = CDR(e);
  }

  return ne;
}

DEF_LIST_APPEND(exptup, exptup_t *);

exp_t *cgc_lambda(exp_t *l, exp_t *e, sym_list *s)
{
  if (!l || !e || !s) {
    return NULL;
  }

  // Zip up bound vars with args
  exptup_list *z = cgc_malloc(sizeof(exptup_list));
  if (!z)
    cgc_exit(1);

  cgc_size_t n = 0;
  for (;;) {
      exp_t *cur_bnd = get(n, l->bound_vars);
      exp_t *cur_arg = get(n, e);
      if (!cur_bnd && !cur_arg)
        break;

      exptup_t *ele = cgc_malloc(sizeof(exptup_t));
      if (!ele)
        cgc_exit(1);

      ele->fst = cur_bnd;
      ele->snd = cur_arg;
      if (!ele->fst || !ele->snd) {
        return NULL;
      }

      exptup_list_append(z, ele);
      n++;
  }

  exp_t *sub = cgc_subst(z->next, l->exp);
  exp_t *ret = cgc_eval(sub, s);

  if (!ret)
    return NULL;

  cgc_size_t cnt = 0;
  exp_t *cake = ret;
  for (cnt = 0; cnt < 4; cnt++) {
    if (cake && CAR(cake) && ATOMP(CAR(cake)) && cgc_strncmp(CAR(cake)->name, "CAKE", cgc_strlen("CAKE")) == 0) {
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
      cgc_exit(1);

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
  sym_list *s = cgc_malloc(sizeof(sym_list));
  if (!s) {
    return NULL;
  }
  sym_t *cf;

  cf = cgc_make_fp("quote", cgc_quote_fn);
  sym_list_append(s, cf);

  cf = cgc_make_fp("car", cgc_car_fn);
  sym_list_append(s, cf);

  cf = cgc_make_fp("cdr", cgc_cdr_fn);
  sym_list_append(s, cf);

  cf = cgc_make_fp("cons", cgc_cons_fn);
  sym_list_append(s, cf);

  cf = cgc_make_fp("equal", cgc_equal_fn);
  sym_list_append(s, cf);

  cf = cgc_make_fp("atom", cgc_atom_fn);
  sym_list_append(s, cf);

  cf = cgc_make_fp("cond", cgc_cond_fn);
  sym_list_append(s, cf);

  sym_t *nil = cgc_malloc(sizeof(sym_list));
  if (!nil)
    cgc_exit(1);
  nil->key = cgc_calloc(1, cgc_strlen("nil") + 1);
  if (!nil->key)
    cgc_exit(1);
  cgc_strncpy(nil->key, "nil", cgc_strlen("nil"));
  nil->e = NEWE();
  if (!nil->e)
    cgc_exit(1);
  nil->e->t = CONS;
  sym_list_append(s, nil);

  sym_t *t = cgc_malloc(sizeof(sym_list));
  if (!t)
    cgc_exit(1);
  t->key = cgc_calloc(1, cgc_strlen("t") + 1);
  if (!t->key)
    cgc_exit(1);
  cgc_strncpy(t->key, "t", cgc_strlen("t"));
  t->e = cgc_malloc(sizeof(exp_t));
  if (!t->e)
    cgc_exit(1);
  t->e->t = ATOM;
  t->e->name = t->key;
  sym_list_append(s, t);

  return s->next;
}

static exp_t *cgc_eval(exp_t *e, sym_list *s)
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

  if (ATOMP(CAR(e)) && cgc_strncmp(CAR(e)->name, "lambda", cgc_strlen("lambda")) == 0) {
    if (!CDR(e) || !CDR(CDR(e)) || !CAR(CDR(CDR(e)))) {
      return NULL;
    }
    exp_t *le = NEWE();
    if (!le)
      cgc_exit(1);
    le->t = LAMB;
    le->bound_vars = CAR(CDR(e));
    le->exp = CAR(CDR(CDR(e)));
    return le;
  }

  // Eval func
  exp_t *f = cgc_eval(CAR(e), s);

  if (f == NULL) {
    return NULL;
  }

  exp_t *l;
  CONZ(&l, f, NULL);

  // Eval args
  exp_t *a = CDR(e);
  while (a && CONSP(a)) {
    exp_t *ev = cgc_eval(CAR(a), s);
    APPEND(l, ev);
    a = CDR(a);
  }

  if (CAR(l)->t == LAMB) {
    return cgc_lambda(CAR(l), CDR(l), s);
  }

  if (CAR(l)->t == FUNC) {
    return CAR(l)->f(CDR(l), s);
  }

  return l;
}

int cgc_repl(char *expr)
{
  tok_list *toks = cgc_tokenize(expr);
  if (toks && toks->value && cgc_strncmp(toks->value, "(", cgc_strlen(toks->value)) == 0) {
    exp_t *prog = cgc_parse(toks->next, NULL);
    sym_list *syms = make_syms();
    exp_t *ed = cgc_eval(prog, syms);
    if (!ed)
      return -1;
    cgc_print(cgc_eval(prog, syms));
    return 0;
  } else {
    return -1;
  }
}
