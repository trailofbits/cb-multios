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
#include "cgc_sadface.h"
#include "cgc_stack.h"

#define DEFAULT_SADFACE_O ":("
#define DEFAULT_SADFACE_C "):"


const char* cgc_strstr(const char *s1, const char *s2)
{
  if (s1 && s2)
  {
    while (*s1)
    {
      const char *ss1 = s1;
      const char *ss2 = s2;
      while (*ss1 && *ss2 && (*ss1++ == *ss2++));
      if (!*ss2)
        return s1;
      s1++;
    }
  }
  return NULL;
}

int cgc_sadface_init(sadface_ctx_t **ctx, faces_t *faces, char *content, dict_t **vars)
{
  sadface_ctx_t *sctx = NULL;
  if (ctx)
  {
    sctx = (sadface_ctx_t *) cgc_malloc(sizeof(sadface_ctx_t));
    if (sctx)
    {
      if (faces == NULL)
      {
        sctx->faces.open_face = DEFAULT_SADFACE_O;
        sctx->faces.close_face = DEFAULT_SADFACE_C;
      }
      else
      {
        if (faces->open_face == NULL)
          sctx->faces.open_face = DEFAULT_SADFACE_O;
        else
          sctx->faces.open_face = faces->open_face;
        if (faces->close_face == NULL)
          sctx->faces.close_face = DEFAULT_SADFACE_C;
        else
          sctx->faces.close_face = faces->close_face;
      }

      sctx->content = cgc_strdup(content);
      if (sctx->content == NULL)
        goto fail;
      sctx->content_len = cgc_strlen(content);

      sctx->idx = 0;
      sctx->vars = vars;

      *ctx = sctx;
      return 0;
    }
  }

fail:
  if (sctx)
  {
    if (sctx->content)
      cgc_free(sctx->content);
    cgc_free(sctx);
  }
  return -1;
}

char* cgc_sadface_var2str(sad_var_t *var)
{
  cgc_size_t n;
  int i;
  int f1, f2;
  float fp;
  unsigned char b;
  char *ret = cgc_calloc(sizeof(char), 256);
  if (ret)
  {
    switch (var->type)
    {
      case SAD_VAR_STR:
        cgc_free(ret);
        return var->value.s;
      case SAD_VAR_INT:
        i = var->value.i;
        cgc_sprintf(ret, "%d", i);
        break;
      case SAD_VAR_FLOAT:
        f1 = (int) var->value.f;
        fp = var->value.f - (float) f1;
        f2 = ((int) (fp * 100)) % 100;
        if (f2 < 0)
          f2 = -f2;
        n = cgc_sprintf(ret, "%d", f1);
        cgc_sprintf(ret + n, ".%02d", f2);
        break;
      case SAD_VAR_BOOL:
        b = var->value.b;
        if (b)
          cgc_strcpy(ret, "true");
        else
          cgc_strcpy(ret, "false");
        break;
      default:
        break;
    }
  }
  return ret;
}

int cgc__find_sadface(sadface_ctx_t *ctx, cgc_size_t *sf_start, cgc_size_t *sf_end)
{
  const char *start, *end;

  start = cgc_strstr(ctx->content + ctx->idx, ctx->faces.open_face);
  if (start == NULL)
    return 0;
  end = cgc_strstr(start + cgc_strlen(ctx->faces.open_face), ctx->faces.close_face);
  if (end == NULL)
    return -1;

  *sf_start = start - ctx->content;
  *sf_end = end - ctx->content + cgc_strlen(ctx->faces.close_face);
  return 1;
}

sad_node_t* cgc_parse_sadface(sadface_ctx_t *ctx)
{
  cgc_size_t start = 0, end = 0;
  sad_node_t *root, *tmp;
  stack_t *stack;

  stack = cgc_stack_new(64);
  root = (sad_node_t *) cgc_malloc(sizeof(sad_node_t));
  if (stack == NULL || root == NULL)
    goto fail;
  cgc_memset(root, 0, sizeof(sad_node_t));
  root->type = SAD_NODE_ROOT;
  cgc_stack_push(stack, root);

  while (ctx->idx < ctx->content_len)
  {
    if (cgc__find_sadface(ctx, &start, &end) <= 0)
    {
      sad_node_t *node = (sad_node_t *) cgc_malloc(sizeof(sad_node_t));
      if (node == NULL)
        goto fail;
      cgc_memset(node, 0, sizeof(sad_node_t));
      node->type = SAD_NODE_NORMAL;
      node->next = NULL;
      node->idx = ctx->idx;
      node->len = ctx->content_len - ctx->idx;

      tmp = cgc_stack_pop(stack);
      tmp->next = node;
      cgc_stack_push(stack, node);

      ctx->idx = ctx->content_len;
      break;
    }

    if (ctx->idx != start)
    {
      sad_node_t *node = (sad_node_t *) cgc_malloc(sizeof(sad_node_t));
      if (node == NULL)
        goto fail;
      cgc_memset(node, 0, sizeof(sad_node_t));
      node->type = SAD_NODE_NORMAL;
      node->next = NULL;
      node->idx = ctx->idx;
      node->len = start - ctx->idx;

      tmp = cgc_stack_pop(stack);
      tmp->next = node;
      cgc_stack_push(stack, node);

      ctx->idx = start;
    }

    cgc_size_t var_len = (end - start) - cgc_strlen(ctx->faces.open_face) - cgc_strlen(ctx->faces.close_face);
    char *var_name = &ctx->content[start + cgc_strlen(ctx->faces.open_face)];

    switch (var_name[0])
    {
      case '@':
        /* section */
        {
          sad_node_t *section, *tmp, *child;

          child = (sad_node_t *) cgc_malloc(sizeof(sad_node_t));
          section = (sad_node_t *) cgc_malloc(sizeof(sad_node_t));
          if (child == NULL || section == NULL)
            goto fail;
          cgc_memset(child, 0, sizeof(sad_node_t));
          child->type = SAD_NODE_ROOT;
          cgc_memset(section, 0, sizeof(sad_node_t));
          section->type = SAD_NODE_SECTION;

          section->idx = start + cgc_strlen(ctx->faces.open_face) + 1;
          section->len = var_len - 1;
          section->child = child;

          tmp = cgc_stack_pop(stack);
          tmp->next = section;
          cgc_stack_push(stack, section);
          cgc_stack_push(stack, child);

          ctx->idx = end;
        }
        break;
      case '/':
        /* section close */
        {
          sad_node_t *section, *child;

          child = cgc_stack_pop(stack);
          section = cgc_stack_peek(stack);

          if (section == NULL || section->type != SAD_NODE_SECTION)
            goto fail;
          if (cgc_strncmp(&ctx->content[section->idx], &var_name[1], section->len) != 0)
            goto fail;

          ctx->idx = end;
        }
        break;
      case '#':
        /* comment */
        ctx->idx = end;
        break;
      default:
        /* variable */
        {
          cgc_size_t idx;
          char *tmp_name;
          sad_node_t *variable, *tmp;

          tmp_name = cgc_calloc(var_len + 1, sizeof(char));
          if (tmp_name == NULL)
            goto fail;
          cgc_memset(tmp_name, 0, var_len + 1);
          idx = start + cgc_strlen(ctx->faces.open_face);
          cgc_strncpy(tmp_name, &ctx->content[idx], var_len);

          variable = (sad_node_t *) cgc_malloc(sizeof(sad_node_t));
          if (variable == NULL)
            goto fail;
          cgc_memset(variable, 0, sizeof(sad_node_t));
          variable->type = SAD_NODE_VAR;

          variable->idx = idx;
          variable->len = var_len;
          variable->var = (sad_var_t *) cgc_dict_find(ctx->vars, tmp_name);
          cgc_free(tmp_name);

          tmp = cgc_stack_pop(stack);
          tmp->next = variable;
          cgc_stack_push(stack, variable);

          ctx->idx = end;
        }
        break;
    }

  }
  cgc_stack_destroy(stack);

  return root;

fail:
  if (stack)
    cgc_stack_destroy(stack);
  cgc_sadface_destroy(ctx);
  return NULL;
}


int cgc_sadface_render(sadface_ctx_t *ctx, char *out, cgc_size_t *out_len)
{
  stack_t *stack;
  sad_node_t *root = NULL, *cur = NULL;
  cgc_size_t total_len = 0, sadness = 0;
  cgc_size_t start = 0, end = 0, size;

  root = cgc_parse_sadface(ctx);
  if (root == NULL)
    goto fail;

  stack = cgc_stack_new(64);
  if (stack == NULL)
    goto fail;
  cur = root;
  while (cur)
  {
    switch (cur->type)
    {
      case SAD_NODE_ROOT:
        break;
      case SAD_NODE_NORMAL:
#if PATCHED
        if (total_len + cur->len > *out_len)
          goto fail;
#endif
        cgc_memcpy(&out[total_len], &ctx->content[cur->idx], cur->len);
        total_len += cur->len;
        break;
      case SAD_NODE_VAR:
        {
          sad_var_t *var = cur->var;
          if (var == NULL)
            break;
          char *var_s = cgc_sadface_var2str(var);
          if (var_s)
          {
#if PATCHED
            if (total_len + cgc_strlen(var_s) > *out_len)
              goto fail;
#endif
            cgc_memcpy(&out[total_len], var_s, cgc_strlen(var_s));
            total_len += cgc_strlen(var_s);
            if (var->type != SAD_VAR_STR)
              cgc_free(var_s);
          }
        }
        break;
      case SAD_NODE_SECTION:
        {
          char *tmp_name;
          sad_var_t *var;

          tmp_name = cgc_calloc(cur->len + 1, sizeof(char));
          if (tmp_name == NULL)
            goto fail;
          cgc_memset(tmp_name, 0, cur->len + 1);
          cgc_strncpy(tmp_name, &ctx->content[cur->idx], cur->len);
          var = (sad_var_t *) cgc_dict_find(ctx->vars, tmp_name);
          cgc_free(tmp_name);

          if (var == NULL || (var->type == SAD_VAR_BOOL && !var->value.b))
            break;
          cgc_stack_push(stack, cur);
          cur = cur->child;
        }
        break;
    }
    if (cur->next == NULL && stack->length != 0)
      cur = cgc_stack_pop(stack);
    cur = cur->next;
  }
  *out_len = total_len;
  return 0;

fail:
  if (stack)
    cgc_stack_destroy(stack);
  return -1;
}

void cgc_sadface_destroy(sadface_ctx_t *ctx)
{
  if (ctx)
  {
    if (ctx->content)
      cgc_free(ctx->content);
    cgc_free(ctx);
  }
}
