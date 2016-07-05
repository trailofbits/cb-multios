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
#include "dict.h"
#include "strtof.h"

#define MAX_BUF_SIZE  4096

dict_t** g_context = NULL;

const char *banner = "# Sad Face Template Engine - v0.1\n";

void print_menu()
{
  printf("1. Define variables\n");
  printf("2. View variables\n");
  printf("3. Submit templated text\n");
  printf("4. Render text\n");
  printf("5. Quit\n");
  printf("\n");
}

void define_vars(dict_t **vars)
{
  sad_var_type_t var_type;
  char var_name[MAX_BUF_SIZE];
  char var_value[MAX_BUF_SIZE];
  printf("-- Empty variable name will exit this menu\n");
  printf("-- Empty value will undefine the variable (if exists)\n");
  while (1)
  {
    printf("var name: ");
    if (read_until(STDIN, var_name, sizeof(var_name), '\n') < 0)
      return;
    if (var_name[0] == '\0')
      return;

    printf("-- Available types\n");
    printf("    0 - String (default)\n");
    printf("    1 - Integer\n");
    printf("    2 - Float\n");
    printf("    3 - Bool [true/false]\n");
    printf("var type: ");
    if (read_until(STDIN, var_value, sizeof(var_value), '\n') < 0)
      return;
    switch (strtoul(var_value, NULL, 10))
    {
      case 1: var_type = SAD_VAR_INT; break;
      case 2: var_type = SAD_VAR_FLOAT; break;
      case 3: var_type = SAD_VAR_BOOL; break;
      default: var_type = SAD_VAR_STR; break;
    }

    printf("var value: ");
    if (read_until(STDIN, var_value, sizeof(var_value), '\n') < 0)
      return;
    if (var_value[0] == '\0')
    {
      sad_var_t *var = (sad_var_t *) dict_remove(vars, var_name);
      if (var)
      {
        if (var->type == SAD_VAR_STR && var->value.s)
          free(var->value.s);
        free(var);
      }
      continue;
    }

    sad_var_t *var = (sad_var_t *) malloc(sizeof(sad_var_t));
    if (var)
    {
      var->type = var_type;
      switch (var->type)
      {
        case SAD_VAR_STR:
          var->value.s = strdup(var_value);
          break;
        case SAD_VAR_INT:
          var->value.i = strtoul(var_value, NULL, 10);
          break;
        case SAD_VAR_FLOAT:
          var->value.f = strtof(var_value, NULL);
          break;
        case SAD_VAR_BOOL:
          var->value.b = strcmp(var_value, "false");
          break;
      }
      dict_insert(vars, var_name, var);
    }
  }
}

void view_vars(dict_t **vars)
{
  int i, num_vars = 0;

  printf("-- Current variables:\n");
  for (i = 0; i < TABLE_SIZE; ++i)
  {
    dict_t *cur = vars[i];
    while (cur)
    {
      sad_var_t *var = (sad_var_t *) cur->value;
      char *var_s = sadface_var2str(var);
      if (var_s)
      {
        printf(" > %s : %s\n", cur->name, var_s);
        if (var->type != SAD_VAR_STR)
          free(var_s);
        num_vars++;
      }
      cur = cur->next;
    }
  }
  if (num_vars)
    printf("-- Total %d variable(s)\n", num_vars);
  else
    printf("-- None\n");
}

void submit_text(char *inbuf, size_t len)
{
  memset(inbuf, 0, len);
  printf("-- Submit a null-terminated string\n");
  if (read_until(STDIN, inbuf, len, '\0') < 0)
    printf("error.\n");
}

void render_text(char *input, dict_t **vars)
{
  char *output;
  size_t output_len;
  sadface_ctx_t *ctx = NULL;

  if (sadface_init(&ctx, NULL, input, vars) < 0)
  {
    printf("error.\n");
    return;
  }

  output_len = MAX_BUF_SIZE;
  output = calloc(sizeof(char), output_len);
  if (output == NULL || sadface_render(ctx, output, &output_len) < 0)
    printf("error.\n");
  else
  {
    printf("-- Render start.\n");
    printf("%s\n", output);
    printf("-- Render complete (%d bytes).\n", output_len);
  }
}

int main()
{
  size_t input_len;
  char buf[MAX_BUF_SIZE], input[MAX_BUF_SIZE];
  dict_t **vars = dict_new();

  /* Banner */
  printf("%s", banner);

  while (1)
  {
    /* Menu */
    print_menu();
    printf("> ");

    /* Read in response */
   if (read_until(STDIN, buf, sizeof(buf), '\n') < 0)
     goto fail;
   switch (strtol(buf, NULL, 10))
   {
     case 1:
       define_vars(vars);
       break;
     case 2:
       view_vars(vars);
       break;
     case 3:
       submit_text(input, sizeof(input));
       break;
     case 4:
       render_text(input, vars);
       break;
     case 5:
       printf("# Bye.\n\n");
       exit(0);
       break;
     default:
       printf("Invalid menu. Try again.\n");
       break;
   }
   printf("\n");
  }
  return 0;

fail:
  return -1;
}
