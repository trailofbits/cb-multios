/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "namespace.h"
#include "tokenizer.h"
#include "parser.h"
#include "prettyprinter.h"
#include "interpreter.h"

#define INPUT_SIZE 1024
#define NAMESPACE_SIZE ((2 << 19) - 1)

static unsigned int
calculate_csum(unsigned int x)
{
    unsigned int ret = 0;
    unsigned int i;

    for (i = 0; i < 1024; i++)
        ret ^= get_flag_byte(i);

    return ret ^ x;
}

int
main(void)
{
    char *p;
    ssize_t num_tokens;
    struct ast ast;
    struct namespace ns;
    struct variable *last, result;
    int quit = 0, dump_tokens = 0, dump_ast = 0;

    static char buf[INPUT_SIZE];
    static struct token tokens[INPUT_SIZE];
    static const char prompt[] = "> ";

    if (namespace_init(&ns, NAMESPACE_SIZE) < 0)
        return EXIT_FAILURE;

    // Special variable denoting last result
    if ((last = insert_variable(&ns, "_", VAR_INTEGER)) == NULL)
        return EXIT_FAILURE;

    while (!quit) {
        // Print prompt
        if (write_all(STDOUT, prompt, sizeof(prompt) - 1) < 0)
            continue;

        if (fread_until(buf, '\n', sizeof(buf), stdin) < 0)
            continue;

        if ((p = strchr(buf, '\n')) != NULL)
            *p = '\0';
        else
            continue;


        if (buf[0] == '%') {
            if (strcmp(buf + 1, "tokens") == 0)
                dump_tokens = !dump_tokens;
            else if (strcmp(buf + 1, "ast") == 0)
                dump_ast = !dump_ast;
            else if (strcmp(buf + 1, "quit") == 0)
                quit = 1;
            else
                printf("INVALID COMMAND\n");
            continue;
        }
    
        if ((num_tokens = tokenize(buf, tokens)) < 0) {
            printf("ERROR!\n");
            continue;
        }
    
        if (parse(tokens, num_tokens, &ast) < 0) {
            printf("ERROR!\n");
            continue;
        }
    
        if (eval(&ast, &ns, &result) < 0) {
            printf("ERROR!\n");
            continue;
        }

        last->type = result.type;
        last->val = result.val;

        if (dump_tokens)
            pretty_print_tokens(tokens, num_tokens);

        if (dump_ast)
            pretty_print_ast(&ast);

        if (result.type == VAR_INTEGER)
            printf("_ = %d\n%x\n", last->val.i, calculate_csum(last->val.i));
        else
            printf("_ = %d\n%x\n", (unsigned int)last->val.p,
                    calculate_csum((unsigned int)last->val.p));
    
        ast_destroy(&ast);
    }

    return EXIT_SUCCESS;
}

