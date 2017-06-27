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
#include "cgc_dict.h"
#include "cgc_strtof.h"

#define MAX_BUF_SIZE  4096

dict_t** cgc_g_context = NULL;

const char *banner = "# Sad Face Template Engine - v0.1\n";

void cgc_print_menu()
{
  cgc_printf("1. Define variables\n");
  cgc_printf("2. View variables\n");
  cgc_printf("3. Submit templated text\n");
  cgc_printf("4. Render text\n");
  cgc_printf("5. Quit\n");
  cgc_printf("\n");
}

void cgc_define_vars(dict_t **vars)
{
  sad_var_type_t var_type;
  char var_name[MAX_BUF_SIZE];
  char var_value[MAX_BUF_SIZE];
  cgc_printf("-- Empty variable name will exit this menu\n");
  cgc_printf("-- Empty value will undefine the variable (if exists)\n");
  while (1)
  {
    cgc_printf("var name: ");
    if (cgc_read_until(STDIN, var_name, sizeof(var_name), '\n') < 0)
      return;
    if (var_name[0] == '\0')
      return;

    cgc_printf("-- Available types\n");
    cgc_printf("    0 - String (default)\n");
    cgc_printf("    1 - Integer\n");
    cgc_printf("    2 - Float\n");
    cgc_printf("    3 - Bool [true/false]\n");
    cgc_printf("var type: ");
    if (cgc_read_until(STDIN, var_value, sizeof(var_value), '\n') < 0)
      return;
    switch (cgc_strtoul(var_value, NULL, 10))
    {
      case 1: var_type = SAD_VAR_INT; break;
      case 2: var_type = SAD_VAR_FLOAT; break;
      case 3: var_type = SAD_VAR_BOOL; break;
      default: var_type = SAD_VAR_STR; break;
    }

    cgc_printf("var value: ");
    if (cgc_read_until(STDIN, var_value, sizeof(var_value), '\n') < 0)
      return;
    if (var_value[0] == '\0')
    {
      sad_var_t *var = (sad_var_t *) cgc_dict_remove(vars, var_name);
      if (var)
      {
        if (var->type == SAD_VAR_STR && var->value.s)
          cgc_free(var->value.s);
        cgc_free(var);
      }
      continue;
    }

    sad_var_t *var = (sad_var_t *) cgc_malloc(sizeof(sad_var_t));
    if (var)
    {
      var->type = var_type;
      switch (var->type)
      {
        case SAD_VAR_STR:
          var->value.s = cgc_strdup(var_value);
          break;
        case SAD_VAR_INT:
          var->value.i = cgc_strtoul(var_value, NULL, 10);
          break;
        case SAD_VAR_FLOAT:
          var->value.f = cgc_strtof(var_value, NULL);
          break;
        case SAD_VAR_BOOL:
          var->value.b = cgc_strcmp(var_value, "false");
          break;
      }
      cgc_dict_insert(vars, var_name, var);
    }
  }
}

void cgc_view_vars(dict_t **vars)
{
  int i, num_vars = 0;

  cgc_printf("-- Current variables:\n");
  for (i = 0; i < TABLE_SIZE; ++i)
  {
    dict_t *cur = vars[i];
    while (cur)
    {
      sad_var_t *var = (sad_var_t *) cur->value;
      char *var_s = cgc_sadface_var2str(var);
      if (var_s)
      {
        cgc_printf(" > %s : %s\n", cur->name, var_s);
        if (var->type != SAD_VAR_STR)
          cgc_free(var_s);
        num_vars++;
      }
      cur = cur->next;
    }
  }
  if (num_vars)
    cgc_printf("-- Total %d variable(s)\n", num_vars);
  else
    cgc_printf("-- None\n");
}

void cgc_submit_text(char *inbuf, cgc_size_t len)
{
  cgc_memset(inbuf, 0, len);
  cgc_printf("-- Submit a null-terminated string\n");
  if (cgc_read_until(STDIN, inbuf, len, '\0') < 0)
    cgc_printf("error.\n");
}

void cgc_render_text(char *input, dict_t **vars)
{
  char *output;
  cgc_size_t output_len;
  sadface_ctx_t *ctx = NULL;

  if (cgc_sadface_init(&ctx, NULL, input, vars) < 0)
  {
    cgc_printf("error.\n");
    return;
  }

  output_len = MAX_BUF_SIZE;
  output = cgc_calloc(sizeof(char), output_len);
  if (output == NULL || cgc_sadface_render(ctx, output, &output_len) < 0)
    cgc_printf("error.\n");
  else
  {
    cgc_printf("-- Render start.\n");
    cgc_printf("%s\n", output);
    cgc_printf("-- Render complete (%d bytes).\n", output_len);
  }
}

int main(int cgc_argc, char *cgc_argv[])
{
  cgc_size_t input_len;
  char buf[MAX_BUF_SIZE], input[MAX_BUF_SIZE];
  dict_t **vars = cgc_dict_new();

  /* Banner */
  cgc_printf("%s", banner);

  while (1)
  {
    /* Menu */
    cgc_print_menu();
    cgc_printf("> ");

    /* Read in response */
   if (cgc_read_until(STDIN, buf, sizeof(buf), '\n') < 0)
     goto fail;
   switch (cgc_strtol(buf, NULL, 10))
   {
     case 1:
       cgc_define_vars(vars);
       break;
     case 2:
       cgc_view_vars(vars);
       break;
     case 3:
       cgc_submit_text(input, sizeof(input));
       break;
     case 4:
       cgc_render_text(input, vars);
       break;
     case 5:
       cgc_printf("# Bye.\n\n");
       cgc_exit(0);
       break;
     default:
       cgc_printf("Invalid menu. Try again.\n");
       break;
   }
   cgc_printf("\n");
  }
  return 0;

fail:
  return -1;
}
