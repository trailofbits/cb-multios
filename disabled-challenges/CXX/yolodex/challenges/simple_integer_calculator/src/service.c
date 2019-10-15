/*

Author: Dustin Fraze <df@cromulence.co>

Copyright (c) 2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include "libcgc.h"
#include "cgc_stdlib.h"

#include "cgc_ltypes.h"
#include "cgc_trie.h"
#include "cgc_stack.h"

trie *root;

stack *operStack;
stack *funcStack;

void cgc_add();
void cgc_sub();
void cgc_mul();
void cgc_div();
void cgc_mod();
void xor();
void and();
void cgc_not();
void cgc_terminate();
void cgc_type();
void cgc__int();
void cgc_equals();
void len();
void cgc_process(char *input);

int main(int cgc_argc, char *cgc_argv[]) {
    char line[256];
    char result[256];

    root = cgc_initTrie();
    operStack = cgc_initStack();
    funcStack = cgc_initStack();
    cgc_insertInTrie(root, "add", cgc_lfunc("add", &cgc_add));
    cgc_insertInTrie(root, "sub", cgc_lfunc("sub", &cgc_sub));
    cgc_insertInTrie(root, "mul", cgc_lfunc("mul", &cgc_mul));
    cgc_insertInTrie(root, "div", cgc_lfunc("div", &cgc_div));
    cgc_insertInTrie(root, "mod", cgc_lfunc("mod", &cgc_mod));
    cgc_insertInTrie(root, "not", cgc_lfunc("not", &cgc_not));
    cgc_insertInTrie(root, "int", cgc_lfunc("int", &cgc__int));
    cgc_insertInTrie(root, "terminate", cgc_lfunc("terminate", &cgc_terminate));
    cgc_insertInTrie(root, "equals", cgc_lfunc("equals", &cgc_equals));
    cgc_insertInTrie(root, "type", cgc_lfunc("type", &cgc_type));
    cgc_insertInTrie(root, "len", cgc_lfunc("len", &len));
 
    while(1) {
        cgc_memset(line, 0, 256);

        cgc_transmit(STDOUT, "> ", 2, NULL);
        if(cgc_receive_until(line, '\n', 255) == 0)
            cgc__terminate(0);
        cgc_process(line);
    }

}

void cgc_process(char *input) {
    char *tmp;
    int i = 0;
    ltype* foo;
    char *save;
    tmp = cgc_strtok(input, " ");
    while(tmp) {
        if(cgc_isdigit(tmp[0]) || (tmp[0] == '-' && cgc_strlen(tmp) > 1)) {
            //variables can't start with number.  Make sure the rest is a number.
            for(i=1;i<cgc_strlen(tmp);i++)
                if(!cgc_isdigit(tmp[i]))
                    break;
            if(i < cgc_strlen(tmp))
                cgc_puts("NOT A NUMBER");
            else {
                foo = cgc_lint("", tmp);
                cgc_push(operStack, foo);
            }
        } else if(tmp[0] == '"') {
            char *match;
            tmp++;
            match = cgc_strchr(tmp, '"');
            if(match) {
                *match = 0;
                cgc_push(operStack, cgc_lstring("", tmp));
            } else {
                tmp--;
                cgc_printf("Unterminated string constant: @s\n", tmp);
            }
        } else {
            //starts with alpha.  Is either a function or a variable.

            if(cgc_strcmp(tmp, "var") == 0)
            {
                //variable declaration.
                //lets assume it's an int and fix it later.
                char *varName = cgc_strtok(NULL, " ");
                char *equals = cgc_strtok(NULL, " ");
#ifdef PATCHED
		if ( equals == NULL ) {
			break;
		}
#endif
                if(equals && *equals == '=') {
                    //declaration and assignment at once.
                    char *tmp;
                    tmp = cgc_strtok(NULL, " ");
                    if(tmp == NULL) {
                        cgc_printf("Malformed variable declaration\n");
                        break;
                    }
                    if(tmp[0] == '"') {
                        char *match;
                        tmp++;
                        match = cgc_strchr(tmp, '"');
                        if(match) {
                            *match = 0;
                            cgc_insertInTrie(root, varName, (char *)cgc_lstring(varName, tmp));
                        }
                    } else {
                        if(cgc_strcmp(tmp, "False") == 0)
                            cgc_insertInTrie(root, varName, (char *)cgc_lbool(varName, tmp));
                        else if (cgc_strcmp(tmp, "True") == 0)
                            cgc_insertInTrie(root, varName, (char *)cgc_lbool(varName, tmp));
                        else
                            cgc_insertInTrie(root, varName, (char *)cgc_lint(varName, tmp));
                    }
                } else {
                    //just a declaration.  Set it to 0 for now.
                    cgc_insertInTrie(root, varName, (char *)cgc_lint(varName, "0"));
                }
                tmp = cgc_strtok(NULL, " ");
                continue;
            }
            if(cgc_strcmp(tmp, "True") == 0)
            {
                cgc_push(operStack, cgc_lbool("", "True"));
                tmp = cgc_strtok(NULL, " ");
                continue;
            }
            if(cgc_strcmp(tmp, "False") == 0)
            {
                cgc_push(operStack, cgc_lbool("", "False"));
                tmp = cgc_strtok(NULL, " ");
                continue;
            }
            if(cgc_strcmp(tmp, "+") == 0)
            {
                ltype *out;
                out = (ltype *)cgc_findInTrie(root, "add")->value;
                #ifndef PATCHED
                cgc_push(funcStack, out);
                #else
                if(cgc_strcmp(out->type, "Function") == 0)
                    cgc_push(funcStack, out);
                else
                    cgc_push(operStack, out);
                #endif
                tmp = cgc_strtok(NULL, " ");
                continue;
            }
            if(cgc_strcmp(tmp, "-") == 0)
            {
                ltype *out;
                out = (ltype *)cgc_findInTrie(root, "sub")->value;
                #ifndef PATCHED
                cgc_push(funcStack, out);
                #else
                if(cgc_strcmp(out->type, "Function") == 0)
                    cgc_push(funcStack, out);
                else
                    cgc_push(operStack, out);
                #endif
                tmp = cgc_strtok(NULL, " ");
                continue;
            }
            if(cgc_strcmp(tmp, "*") == 0)
            {
                ltype *out;
                out = (ltype *)cgc_findInTrie(root, "mul")->value;
                #ifndef PATCHED
                cgc_push(funcStack, out);
                #else
                if(cgc_strcmp(out->type, "Function") == 0)
                    cgc_push(funcStack, out);
                else
                    cgc_push(operStack, out);
                #endif
                tmp = cgc_strtok(NULL, " ");
                continue;
            }
            if(cgc_strcmp(tmp, "/") == 0)
            {
                ltype *out;
                out = (ltype *)cgc_findInTrie(root, "div")->value;
                #ifndef PATCHED
                cgc_push(funcStack, out);
                #else
                if(cgc_strcmp(out->type, "Function") == 0)
                    cgc_push(funcStack, out);
                else
                    cgc_push(operStack, out);
                #endif
                tmp = cgc_strtok(NULL, " ");
                continue;
            }
            if(cgc_strcmp(tmp, "%") == 0)
            {
                ltype *out;
                out = (ltype *)cgc_findInTrie(root, "mod")->value;
                #ifndef PATCHED
                cgc_push(funcStack, out);
                #else
                if(cgc_strcmp(out->type, "Function") == 0)
                    cgc_push(funcStack, out);
                else
                    cgc_push(operStack, out);
                #endif
                tmp = cgc_strtok(NULL, " ");
                continue;
            }
            if(cgc_strcmp(tmp, "==") == 0)
            {
                ltype *out;
                out = (ltype *)cgc_findInTrie(root, "equals")->value;
                #ifndef PATCHED
                cgc_push(funcStack, out);
                #else
                if(cgc_strcmp(out->type, "Function") == 0)
                    cgc_push(funcStack, out);
                else
                    cgc_push(operStack, out);
                #endif
                tmp = cgc_strtok(NULL, " ");
                continue;
            }

            if(cgc_findInTrie(root, tmp)) {
                ltype *out;
                out = (ltype *)cgc_findInTrie(root, tmp)->value;
                if(cgc_strcmp(out->type, "Function") == 0) {
                    cgc_push(funcStack, out);
                } else {
                    cgc_push(operStack, out);
                }
            } else {
                cgc_printf("Undeclared identifier: @s\n", tmp);
            }
        }
        tmp = cgc_strtok(NULL, " ");
    }
    while(!cgc_isEmpty(funcStack)) {
        ltype *func = cgc_pop(funcStack);
        ((void (*)())func->value)();
    }
    if(!(cgc_isEmpty(operStack))) {
        ltype *oper = cgc_pop(operStack);
        if(cgc_strcmp(oper->type, "Integer") == 0)
            cgc_printf("@d\n", oper->value);
        else if(cgc_strcmp(oper->type, "String") == 0)
            cgc_printf("@s\n", oper->value);
        else if(cgc_strcmp(oper->type, "Boolean") == 0)
            cgc_printf("@s\n", (int)oper->value == 1 ? "True" : "False");
    }
}

void cgc_add() {
    ltype *oper1 = NULL;
    ltype *oper2 = NULL;

    if(!(cgc_isEmpty(operStack)))
        oper1 = cgc_pop(operStack);
    else {
        cgc_puts("Not enough operands for add");
        return;
    }

    if(!(cgc_isEmpty(operStack)))
        oper2 = cgc_pop(operStack);
    else {
        cgc_puts("Not enough operands for add");
        return;
    }

    if((cgc_strcmp(oper1->type, "Integer") == 0) && (cgc_strcmp(oper2->type, "Integer") == 0))
    {
        char result[32];
        cgc_bzero(result, 32);
        cgc_int_to_str((int)oper1->value + (int)oper2->value, result);
        cgc_push(operStack, cgc_lint("", result));
    } else if((cgc_strcmp(oper1->type, "String") == 0) && (cgc_strcmp(oper2->type, "String") == 0)) {
        char *tmp;
        tmp = cgc_calloc(oper1->len + oper2->len + 1, 1);
        if(tmp) {
            cgc_memcpy(tmp, oper2->value, oper2->len);
            cgc_memcpy(tmp+(oper2->len), oper1->value, oper1->len);
            cgc_push(operStack, cgc_lstring("", tmp));
            cgc_free(tmp);
        } else {
            cgc_puts("Critical memory error.  Exiting.");
            cgc__terminate(-1);
        }
    } else if((cgc_strcmp(oper2->type, "String") == 0) && (cgc_strcmp(oper1->type, "Integer") == 0)) {
        char *tmp;
        char result[32];
        cgc_bzero(result, 32);
        cgc_int_to_str((int)oper1->value, result);
        tmp = cgc_calloc(oper2->len + oper1->len + 1, 1);
        if(tmp) {
            cgc_memcpy(tmp, oper2->value, oper2->len);
            cgc_memcpy(tmp+oper2->len, result, cgc_strlen(result));
            cgc_push(operStack, cgc_lstring("", tmp));
            cgc_free(tmp);
        } else {
            cgc_puts("Critical memory error.  Exiting.");
            cgc__terminate(-1);
        }
    } else {
        cgc_printf("Add doesn't make sense on @s and @s\n", oper2->type, oper1->type);
    }

}

void cgc__int() {
    ltype *oper = NULL;
    int i;
    char *tmp;

    if(!(cgc_isEmpty(operStack)))
        oper = cgc_pop(operStack);

    if(oper) {
        if(cgc_strcmp(oper->type, "Integer") == 0)
            cgc_push(operStack, oper);
        else if(cgc_strcmp(oper->type, "String") == 0)
        {
            tmp = oper->value;
            for(i=0;i<cgc_strlen(tmp);i++)
            {
                if(!cgc_isdigit(tmp[i]))
                {
                    cgc_puts("Could not convert argument to int");
                    return;
                }
            }
            cgc_push(operStack, cgc_lint("", oper->value));
        } else if(cgc_strcmp(oper->type, "Boolean") == 0) {
            if(oper->value)
                cgc_push(operStack, cgc_lint("", "1"));
            else
                cgc_push(operStack, cgc_lint("", "0"));
        }
    } else {
        cgc_puts("Not enough operands for int");
    }
}

void cgc_mul() {
    ltype *oper1 = NULL;
    ltype *oper2 = NULL;

    if(!(cgc_isEmpty(operStack)))
        oper1 = cgc_pop(operStack);

    if(!(cgc_isEmpty(operStack)))
        oper2 = cgc_pop(operStack);

    if(oper1 && oper2) {
        if(cgc_strcmp(oper2->type, "Integer") == 0 && cgc_strcmp(oper1->type, "Integer") == 0) {
            char tmp[32];
            cgc_bzero(tmp, 32);
            cgc_int_to_str((int)oper2->value * (int)oper1->value, tmp);
            cgc_push(operStack, cgc_lint("", tmp));
        } else if(cgc_strcmp(oper2->type, "String") == 0 && cgc_strcmp(oper1->type, "Integer") == 0) {
            char *tmp;
            int size;
            int times;
            char *orig;
            #ifdef PATCHED
            if ((int)oper1->value >= (0x7fffffff / oper2->len)) {
                return;
            }
            if ((int)oper1->value <= 0) {
                return;
            }
            #endif
            times = (int)oper1->value;
            size = (oper2->len * (int)oper1->value) + 1;
            tmp = cgc_calloc(size, 1);
            orig = tmp;
            if(tmp)
            {
                while(times--) {
                    cgc_memcpy(tmp, oper2->value, oper2->len);
                    tmp+=oper2->len;
                }
                cgc_push(operStack, cgc_lstring("", orig));
            } else {
                cgc_puts("Critical memory error.  Terminating.");
                cgc__terminate(-1);
            }
        } else {
            cgc_printf("Mul does not make sense with @s and @s.\n", oper2->type, oper1->type);
        }
    } else
        cgc_puts("Not enough operands for multiplication");
}

void cgc_sub() {
    ltype *oper1 = NULL;
    ltype *oper2 = NULL;

    if(!(cgc_isEmpty(operStack)))
        oper1 = cgc_pop(operStack);
    else {
        cgc_puts("Not enough operands for sub");
        return;
    }

    if(!(cgc_isEmpty(operStack)))
        oper2 = cgc_pop(operStack);
    else {
        cgc_puts("Not enough operands for sub");
        return;
    }

    if((cgc_strcmp(oper1->type, "Integer") == 0) && (cgc_strcmp(oper2->type, "Integer") == 0))
    {
        char result[32];
        cgc_bzero(result, 32);
        cgc_int_to_str((int)oper2->value - (int)oper1->value, result);
        cgc_push(operStack, cgc_lint("", result));
    } else {
        cgc_printf("Sub does not make sense on @s and @s\n", oper2->type, oper1->type);
    }
}

void cgc_div() {
    ltype *oper1 = NULL;
    ltype *oper2 = NULL;
    
    if(!(cgc_isEmpty(operStack)))
        oper1 = cgc_pop(operStack);

    if(!(cgc_isEmpty(operStack)))
        oper2 = cgc_pop(operStack);

    if(oper1 && oper2) {
        if((cgc_strcmp(oper1->type, "Integer") == 0) && (cgc_strcmp(oper2->type, "Integer") == 0)) {
            char result[32];
            cgc_bzero(result, 32);
            if(oper1->value != 0) {
                cgc_int_to_str((int)oper2->value / (int)oper1->value, result);
                cgc_push(operStack, cgc_lint("", result));
            } else
                cgc_puts("Cannot divide by zero.");
        } else
            cgc_printf("Division does not make sense on @s and @s\n", oper2->type, oper1->type);
    } else {
        cgc_puts("Not enough operands for division.");
    }
}

void cgc_mod() {
    ltype *oper1 = NULL;
    ltype *oper2 = NULL;
    
    if(!(cgc_isEmpty(operStack)))
        oper1 = cgc_pop(operStack);

    if(!(cgc_isEmpty(operStack)))
        oper2 = cgc_pop(operStack);

    if(oper1 && oper2) {
        if((cgc_strcmp(oper1->type, "Integer") == 0) && (cgc_strcmp(oper2->type, "Integer") == 0)) {
            char result[32];
            cgc_bzero(result, 32);
            if(oper1->value != 0) {
                cgc_int_to_str((int)oper2->value % (int)oper1->value, result);
                cgc_push(operStack, cgc_lint("", result));
            } else
                cgc_puts("Cannot mod by zero.");
        } else
            cgc_printf("Mod does not make sense on @s and @s\n", oper2->type, oper1->type);
    } else {
        cgc_puts("Not enough operands for mod.");
    }
}

void cgc_not() {
    ltype *oper1 = NULL;

    if(!(cgc_isEmpty(operStack)))
        oper1 = cgc_pop(operStack);
    else {
        cgc_puts("Not enough operands for not.");
        return;
    }
    //this is mostly a stupid joke...because it's not the string passed in.
    if(cgc_strcmp(oper1->type, "String") == 0) {
        if(cgc_strcmp(oper1->value, "OMG"))
            cgc_push(operStack, cgc_lstring("", "OMG"));
        else
            cgc_push(operStack, cgc_lstring("", "BBQ"));
    } else if(cgc_strcmp(oper1->type, "Integer") == 0) {
        char result[32];
        cgc_bzero(result, 32);
        cgc_int_to_str(~(int)oper1->value, result);
        cgc_push(operStack, cgc_lint("", result));
    } else {
        (int)oper1->value == 1 ? cgc_push(operStack, cgc_lbool("", "False")) : cgc_push(operStack, cgc_lbool("", "True"));
    }
}

void len() {
    ltype *oper = NULL;

    if(!(cgc_isEmpty(operStack)))
        oper = cgc_pop(operStack);
    else {
        cgc_puts("Not enough operands for len.");
        return;
    }
    char tmp[32];
    cgc_bzero(tmp, 32);
    cgc_int_to_str(oper->len, tmp);
    cgc_push(operStack, cgc_lint("", tmp));
}

void cgc_equals() {
    ltype *oper1 = NULL;
    ltype *oper2 = NULL;

    if(!(cgc_isEmpty(operStack)))
        oper1 = cgc_pop(operStack);

    if(!(cgc_isEmpty(operStack)))
        oper2 = cgc_pop(operStack);

    if(oper1 && oper2)
    {
        if((cgc_strcmp(oper1->type, "Integer") == 0 && cgc_strcmp(oper2->type, "Integer") == 0) || (cgc_strcmp(oper1->type, "Boolean") == 0 && cgc_strcmp(oper2->type, "Boolean") == 0)) {
            if(oper1->value == oper2->value)
                cgc_push(operStack, cgc_lbool("", "True"));
            else
                cgc_push(operStack, cgc_lbool("", "False"));
        } else if (cgc_strcmp(oper1->type, "String") == 0 && cgc_strcmp(oper2->type, "String") == 0) {
            if(cgc_strcmp(oper1->value, oper2->value) == 0)
                cgc_push(operStack, cgc_lbool("", "True"));
            else
                cgc_push(operStack, cgc_lbool("", "False"));
        } else
            cgc_push(operStack, cgc_lbool("", "False"));
    } else {
        cgc_puts("Not enough operands for equality");
    }
}

void cgc_type() {
    ltype *oper1 = NULL;

    if(!(cgc_isEmpty(operStack))) {
        oper1 = cgc_pop(operStack);
    }

    if(oper1 != NULL)
        cgc_push(operStack, cgc_lstring("", oper1->type));
}

void cgc_terminate() {
    ltype *oper1 = NULL;

    if(!(cgc_isEmpty(operStack))) {
        oper1 = cgc_pop(operStack);
    }
    //don't worry if the stack is empty.  We're going to terminate anyway.
    if(oper1 && (cgc_strcmp(oper1->type, "Integer") == 0))
        cgc__terminate((int)oper1->value);
    else 
        cgc__terminate(0);
}
