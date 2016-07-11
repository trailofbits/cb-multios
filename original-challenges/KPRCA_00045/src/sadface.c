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
#include "sadface.h"
#include "stack.h"

#define DEFAULT_SADFACE_O ":("
#define DEFAULT_SADFACE_C "):"


const char* strstr(const char *s1, const char *s2)
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

int sadface_init(sadface_ctx_t **ctx, faces_t *faces, char *content, dict_t **vars)
{
  sadface_ctx_t *sctx = NULL;
  if (ctx)
  {
    sctx = (sadface_ctx_t *) malloc(sizeof(sadface_ctx_t));
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

      sctx->content = strdup(content);
      if (sctx->content == NULL)
        goto fail;
      sctx->content_len = strlen(content);

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
      free(sctx->content);
    free(sctx);
  }
  return -1;
}

char* sadface_var2str(sad_var_t *var)
{
  size_t n;
  int i;
  int f1, f2;
  float fp;
  unsigned char b;
  char *ret = calloc(sizeof(char), 256);
  if (ret)
  {
    switch (var->type)
    {
      case SAD_VAR_STR:
        free(ret);
        return var->value.s;
      case SAD_VAR_INT:
        i = var->value.i;
        sprintf(ret, "%d", i);
        break;
      case SAD_VAR_FLOAT:
        f1 = (int) var->value.f;
        fp = var->value.f - (float) f1;
        f2 = ((int) (fp * 100)) % 100;
        if (f2 < 0)
          f2 = -f2;
        n = sprintf(ret, "%d", f1);
        sprintf(ret + n, ".%02d", f2);
        break;
      case SAD_VAR_BOOL:
        b = var->value.b;
        if (b)
          strcpy(ret, "true");
        else
          strcpy(ret, "false");
        break;
      default:
        break;
    }
  }
  return ret;
}

int _find_sadface(sadface_ctx_t *ctx, size_t *sf_start, size_t *sf_end)
{
  const char *start, *end;

  start = strstr(ctx->content + ctx->idx, ctx->faces.open_face);
  if (start == NULL)
    return 0;
  end = strstr(start + strlen(ctx->faces.open_face), ctx->faces.close_face);
  if (end == NULL)
    return -1;

  *sf_start = start - ctx->content;
  *sf_end = end - ctx->content + strlen(ctx->faces.close_face);
  return 1;
}

sad_node_t* parse_sadface(sadface_ctx_t *ctx)
{
  size_t start = 0, end = 0;
  sad_node_t *root, *tmp;
  stack_t *stack;

  stack = stack_new(64);
  root = (sad_node_t *) malloc(sizeof(sad_node_t));
  if (stack == NULL || root == NULL)
    goto fail;
  memset(root, 0, sizeof(sad_node_t));
  root->type = SAD_NODE_ROOT;
  stack_push(stack, root);

  while (ctx->idx < ctx->content_len)
  {
    if (_find_sadface(ctx, &start, &end) <= 0)
    {
      sad_node_t *node = (sad_node_t *) malloc(sizeof(sad_node_t));
      if (node == NULL)
        goto fail;
      memset(node, 0, sizeof(sad_node_t));
      node->type = SAD_NODE_NORMAL;
      node->next = NULL;
      node->idx = ctx->idx;
      node->len = ctx->content_len - ctx->idx;

      tmp = stack_pop(stack);
      tmp->next = node;
      stack_push(stack, node);

      ctx->idx = ctx->content_len;
      break;
    }

    if (ctx->idx != start)
    {
      sad_node_t *node = (sad_node_t *) malloc(sizeof(sad_node_t));
      if (node == NULL)
        goto fail;
      memset(node, 0, sizeof(sad_node_t));
      node->type = SAD_NODE_NORMAL;
      node->next = NULL;
      node->idx = ctx->idx;
      node->len = start - ctx->idx;

      tmp = stack_pop(stack);
      tmp->next = node;
      stack_push(stack, node);

      ctx->idx = start;
    }

    size_t var_len = (end - start) - strlen(ctx->faces.open_face) - strlen(ctx->faces.close_face);
    char *var_name = &ctx->content[start + strlen(ctx->faces.open_face)];

    switch (var_name[0])
    {
      case '@':
        /* section */
        {
          sad_node_t *section, *tmp, *child;

          child = (sad_node_t *) malloc(sizeof(sad_node_t));
          section = (sad_node_t *) malloc(sizeof(sad_node_t));
          if (child == NULL || section == NULL)
            goto fail;
          memset(child, 0, sizeof(sad_node_t));
          child->type = SAD_NODE_ROOT;
          memset(section, 0, sizeof(sad_node_t));
          section->type = SAD_NODE_SECTION;

          section->idx = start + strlen(ctx->faces.open_face) + 1;
          section->len = var_len - 1;
          section->child = child;

          tmp = stack_pop(stack);
          tmp->next = section;
          stack_push(stack, section);
          stack_push(stack, child);

          ctx->idx = end;
        }
        break;
      case '/':
        /* section close */
        {
          sad_node_t *section, *child;

          child = stack_pop(stack);
          section = stack_peek(stack);

          if (section == NULL || section->type != SAD_NODE_SECTION)
            goto fail;
          if (strncmp(&ctx->content[section->idx], &var_name[1], section->len) != 0)
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
          size_t idx;
          char *tmp_name;
          sad_node_t *variable, *tmp;

          tmp_name = calloc(var_len + 1, sizeof(char));
          if (tmp_name == NULL)
            goto fail;
          memset(tmp_name, 0, var_len + 1);
          idx = start + strlen(ctx->faces.open_face);
          strncpy(tmp_name, &ctx->content[idx], var_len);

          variable = (sad_node_t *) malloc(sizeof(sad_node_t));
          if (variable == NULL)
            goto fail;
          memset(variable, 0, sizeof(sad_node_t));
          variable->type = SAD_NODE_VAR;

          variable->idx = idx;
          variable->len = var_len;
          variable->var = (sad_var_t *) dict_find(ctx->vars, tmp_name);
          free(tmp_name);

          tmp = stack_pop(stack);
          tmp->next = variable;
          stack_push(stack, variable);

          ctx->idx = end;
        }
        break;
    }

  }
  stack_destroy(stack);

  return root;

fail:
  if (stack)
    stack_destroy(stack);
  sadface_destroy(ctx);
  return NULL;
}


int sadface_render(sadface_ctx_t *ctx, char *out, size_t *out_len)
{
  stack_t *stack;
  sad_node_t *root = NULL, *cur = NULL;
  size_t total_len = 0, sadness = 0;
  size_t start = 0, end = 0, size;

  root = parse_sadface(ctx);
  if (root == NULL)
    goto fail;

  stack = stack_new(64);
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
        memcpy(&out[total_len], &ctx->content[cur->idx], cur->len);
        total_len += cur->len;
        break;
      case SAD_NODE_VAR:
        {
          sad_var_t *var = cur->var;
          if (var == NULL)
            break;
          char *var_s = sadface_var2str(var);
          if (var_s)
          {
#if PATCHED
            if (total_len + strlen(var_s) > *out_len)
              goto fail;
#endif
            memcpy(&out[total_len], var_s, strlen(var_s));
            total_len += strlen(var_s);
            if (var->type != SAD_VAR_STR)
              free(var_s);
          }
        }
        break;
      case SAD_NODE_SECTION:
        {
          char *tmp_name;
          sad_var_t *var;

          tmp_name = calloc(cur->len + 1, sizeof(char));
          if (tmp_name == NULL)
            goto fail;
          memset(tmp_name, 0, cur->len + 1);
          strncpy(tmp_name, &ctx->content[cur->idx], cur->len);
          var = (sad_var_t *) dict_find(ctx->vars, tmp_name);
          free(tmp_name);

          if (var == NULL || (var->type == SAD_VAR_BOOL && !var->value.b))
            break;
          stack_push(stack, cur);
          cur = cur->child;
        }
        break;
    }
    if (cur->next == NULL && stack->length != 0)
      cur = stack_pop(stack);
    cur = cur->next;
  }
  *out_len = total_len;
  return 0;

fail:
  if (stack)
    stack_destroy(stack);
  return -1;
}

void sadface_destroy(sadface_ctx_t *ctx)
{
  if (ctx)
  {
    if (ctx->content)
      free(ctx->content);
    free(ctx);
  }
}
