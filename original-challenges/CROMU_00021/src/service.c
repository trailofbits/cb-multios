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

#include <libcgc.h>
#include "stdlib.h"

#include "ltypes.h"
#include "trie.h"
#include "stack.h"

trie *root;

stack *operStack;
stack *funcStack;

void add();
void sub();
void mul();
void div();
void mod();
void xor();
void and();
void not();
void terminate();
void type();
void _int();
void equals();
void len();
void process(char *input);

int main() {
    char line[256];
    char result[256];

    root = initTrie();
    operStack = initStack();
    funcStack = initStack();
    insertInTrie(root, "add", lfunc("add", &add));
    insertInTrie(root, "sub", lfunc("sub", &sub));
    insertInTrie(root, "mul", lfunc("mul", &mul));
    insertInTrie(root, "div", lfunc("div", &div));
    insertInTrie(root, "mod", lfunc("mod", &mod));
    insertInTrie(root, "not", lfunc("not", &not));
    insertInTrie(root, "int", lfunc("int", &_int));
    insertInTrie(root, "terminate", lfunc("terminate", &terminate));
    insertInTrie(root, "equals", lfunc("equals", &equals));
    insertInTrie(root, "type", lfunc("type", &type));
    insertInTrie(root, "len", lfunc("len", &len));
 
    while(1) {
        memset(line, 0, 256);

        transmit(STDOUT, "> ", 2, NULL);
        if(receive_until(line, '\n', 255) == 0)
            _terminate(0);
        process(line);
    }

}

void process(char *input) {
    char *tmp;
    int i = 0;
    ltype* foo;
    char *save;
    tmp = strtok(input, " ");
    while(tmp) {
        if(isdigit(tmp[0]) || (tmp[0] == '-' && strlen(tmp) > 1)) {
            //variables can't start with number.  Make sure the rest is a number.
            for(i=1;i<strlen(tmp);i++)
                if(!isdigit(tmp[i]))
                    break;
            if(i < strlen(tmp))
                puts("NOT A NUMBER");
            else {
                foo = lint("", tmp);
                push(operStack, foo);
            }
        } else if(tmp[0] == '"') {
            char *match;
            tmp++;
            match = strchr(tmp, '"');
            if(match) {
                *match = 0;
                push(operStack, lstring("", tmp));
            } else {
                tmp--;
                printf("Unterminated string constant: @s\n", tmp);
            }
        } else {
            //starts with alpha.  Is either a function or a variable.

            if(strcmp(tmp, "var") == 0)
            {
                //variable declaration.
                //lets assume it's an int and fix it later.
                char *varName = strtok(NULL, " ");
                char *equals = strtok(NULL, " ");
#ifdef PATCHED
		if ( equals == NULL ) {
			break;
		}
#endif
                if(equals && *equals == '=') {
                    //declaration and assignment at once.
                    char *tmp;
                    tmp = strtok(NULL, " ");
                    if(tmp == NULL) {
                        printf("Malformed variable declaration\n");
                        break;
                    }
                    if(tmp[0] == '"') {
                        char *match;
                        tmp++;
                        match = strchr(tmp, '"');
                        if(match) {
                            *match = 0;
                            insertInTrie(root, varName, (char *)lstring(varName, tmp));
                        }
                    } else {
                        if(strcmp(tmp, "False") == 0)
                            insertInTrie(root, varName, (char *)lbool(varName, tmp));
                        else if (strcmp(tmp, "True") == 0)
                            insertInTrie(root, varName, (char *)lbool(varName, tmp));
                        else
                            insertInTrie(root, varName, (char *)lint(varName, tmp));
                    }
                } else {
                    //just a declaration.  Set it to 0 for now.
                    insertInTrie(root, varName, (char *)lint(varName, "0"));
                }
                tmp = strtok(NULL, " ");
                continue;
            }
            if(strcmp(tmp, "True") == 0)
            {
                push(operStack, lbool("", "True"));
                tmp = strtok(NULL, " ");
                continue;
            }
            if(strcmp(tmp, "False") == 0)
            {
                push(operStack, lbool("", "False"));
                tmp = strtok(NULL, " ");
                continue;
            }
            if(strcmp(tmp, "+") == 0)
            {
                ltype *out;
                out = (ltype *)findInTrie(root, "add")->value;
                #ifndef PATCHED
                push(funcStack, out);
                #else
                if(strcmp(out->type, "Function") == 0)
                    push(funcStack, out);
                else
                    push(operStack, out);
                #endif
                tmp = strtok(NULL, " ");
                continue;
            }
            if(strcmp(tmp, "-") == 0)
            {
                ltype *out;
                out = (ltype *)findInTrie(root, "sub")->value;
                #ifndef PATCHED
                push(funcStack, out);
                #else
                if(strcmp(out->type, "Function") == 0)
                    push(funcStack, out);
                else
                    push(operStack, out);
                #endif
                tmp = strtok(NULL, " ");
                continue;
            }
            if(strcmp(tmp, "*") == 0)
            {
                ltype *out;
                out = (ltype *)findInTrie(root, "mul")->value;
                #ifndef PATCHED
                push(funcStack, out);
                #else
                if(strcmp(out->type, "Function") == 0)
                    push(funcStack, out);
                else
                    push(operStack, out);
                #endif
                tmp = strtok(NULL, " ");
                continue;
            }
            if(strcmp(tmp, "/") == 0)
            {
                ltype *out;
                out = (ltype *)findInTrie(root, "div")->value;
                #ifndef PATCHED
                push(funcStack, out);
                #else
                if(strcmp(out->type, "Function") == 0)
                    push(funcStack, out);
                else
                    push(operStack, out);
                #endif
                tmp = strtok(NULL, " ");
                continue;
            }
            if(strcmp(tmp, "%") == 0)
            {
                ltype *out;
                out = (ltype *)findInTrie(root, "mod")->value;
                #ifndef PATCHED
                push(funcStack, out);
                #else
                if(strcmp(out->type, "Function") == 0)
                    push(funcStack, out);
                else
                    push(operStack, out);
                #endif
                tmp = strtok(NULL, " ");
                continue;
            }
            if(strcmp(tmp, "==") == 0)
            {
                ltype *out;
                out = (ltype *)findInTrie(root, "equals")->value;
                #ifndef PATCHED
                push(funcStack, out);
                #else
                if(strcmp(out->type, "Function") == 0)
                    push(funcStack, out);
                else
                    push(operStack, out);
                #endif
                tmp = strtok(NULL, " ");
                continue;
            }

            if(findInTrie(root, tmp)) {
                ltype *out;
                out = (ltype *)findInTrie(root, tmp)->value;
                if(strcmp(out->type, "Function") == 0) {
                    push(funcStack, out);
                } else {
                    push(operStack, out);
                }
            } else {
                printf("Undeclared identifier: @s\n", tmp);
            }
        }
        tmp = strtok(NULL, " ");
    }
    while(!isEmpty(funcStack)) {
        ltype *func = pop(funcStack);
        ((void (*)())func->value)();
    }
    if(!(isEmpty(operStack))) {
        ltype *oper = pop(operStack);
        if(strcmp(oper->type, "Integer") == 0)
            printf("@d\n", oper->value);
        else if(strcmp(oper->type, "String") == 0)
            printf("@s\n", oper->value);
        else if(strcmp(oper->type, "Boolean") == 0)
            printf("@s\n", (int)oper->value == 1 ? "True" : "False");
    }
}

void add() {
    ltype *oper1 = NULL;
    ltype *oper2 = NULL;

    if(!(isEmpty(operStack)))
        oper1 = pop(operStack);
    else {
        puts("Not enough operands for add");
        return;
    }

    if(!(isEmpty(operStack)))
        oper2 = pop(operStack);
    else {
        puts("Not enough operands for add");
        return;
    }

    if((strcmp(oper1->type, "Integer") == 0) && (strcmp(oper2->type, "Integer") == 0))
    {
        char result[32];
        bzero(result, 32);
        int_to_str((int)oper1->value + (int)oper2->value, result);
        push(operStack, lint("", result));
    } else if((strcmp(oper1->type, "String") == 0) && (strcmp(oper2->type, "String") == 0)) {
        char *tmp;
        tmp = calloc(oper1->len + oper2->len + 1, 1);
        if(tmp) {
            memcpy(tmp, oper2->value, oper2->len);
            memcpy(tmp+(oper2->len), oper1->value, oper1->len);
            push(operStack, lstring("", tmp));
            free(tmp);
        } else {
            puts("Critical memory error.  Exiting.");
            _terminate(-1);
        }
    } else if((strcmp(oper2->type, "String") == 0) && (strcmp(oper1->type, "Integer") == 0)) {
        char *tmp;
        char result[32];
        bzero(result, 32);
        int_to_str((int)oper1->value, result);
        tmp = calloc(oper2->len + oper1->len + 1, 1);
        if(tmp) {
            memcpy(tmp, oper2->value, oper2->len);
            memcpy(tmp+oper2->len, result, strlen(result));
            push(operStack, lstring("", tmp));
            free(tmp);
        } else {
            puts("Critical memory error.  Exiting.");
            _terminate(-1);
        }
    } else {
        printf("Add doesn't make sense on @s and @s\n", oper2->type, oper1->type);
    }

}

void _int() {
    ltype *oper = NULL;
    int i;
    char *tmp;

    if(!(isEmpty(operStack)))
        oper = pop(operStack);

    if(oper) {
        if(strcmp(oper->type, "Integer") == 0)
            push(operStack, oper);
        else if(strcmp(oper->type, "String") == 0)
        {
            tmp = oper->value;
            for(i=0;i<strlen(tmp);i++)
            {
                if(!isdigit(tmp[i]))
                {
                    puts("Could not convert argument to int");
                    return;
                }
            }
            push(operStack, lint("", oper->value));
        } else if(strcmp(oper->type, "Boolean") == 0) {
            if(oper->value)
                push(operStack, lint("", "1"));
            else
                push(operStack, lint("", "0"));
        }
    } else {
        puts("Not enough operands for int");
    }
}

void mul() {
    ltype *oper1 = NULL;
    ltype *oper2 = NULL;

    if(!(isEmpty(operStack)))
        oper1 = pop(operStack);

    if(!(isEmpty(operStack)))
        oper2 = pop(operStack);

    if(oper1 && oper2) {
        if(strcmp(oper2->type, "Integer") == 0 && strcmp(oper1->type, "Integer") == 0) {
            char tmp[32];
            bzero(tmp, 32);
            int_to_str((int)oper2->value * (int)oper1->value, tmp);
            push(operStack, lint("", tmp));
        } else if(strcmp(oper2->type, "String") == 0 && strcmp(oper1->type, "Integer") == 0) {
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
            tmp = calloc(size, 1);
            orig = tmp;
            if(tmp)
            {
                while(times--) {
                    memcpy(tmp, oper2->value, oper2->len);
                    tmp+=oper2->len;
                }
                push(operStack, lstring("", orig));
            } else {
                puts("Critical memory error.  Terminating.");
                _terminate(-1);
            }
        } else {
            printf("Mul does not make sense with @s and @s.\n", oper2->type, oper1->type);
        }
    } else
        puts("Not enough operands for multiplication");
}

void sub() {
    ltype *oper1 = NULL;
    ltype *oper2 = NULL;

    if(!(isEmpty(operStack)))
        oper1 = pop(operStack);
    else {
        puts("Not enough operands for sub");
        return;
    }

    if(!(isEmpty(operStack)))
        oper2 = pop(operStack);
    else {
        puts("Not enough operands for sub");
        return;
    }

    if((strcmp(oper1->type, "Integer") == 0) && (strcmp(oper2->type, "Integer") == 0))
    {
        char result[32];
        bzero(result, 32);
        int_to_str((int)oper2->value - (int)oper1->value, result);
        push(operStack, lint("", result));
    } else {
        printf("Sub does not make sense on @s and @s\n", oper2->type, oper1->type);
    }
}

void div() {
    ltype *oper1 = NULL;
    ltype *oper2 = NULL;
    
    if(!(isEmpty(operStack)))
        oper1 = pop(operStack);

    if(!(isEmpty(operStack)))
        oper2 = pop(operStack);

    if(oper1 && oper2) {
        if((strcmp(oper1->type, "Integer") == 0) && (strcmp(oper2->type, "Integer") == 0)) {
            char result[32];
            bzero(result, 32);
            if(oper1->value != 0) {
                int_to_str((int)oper2->value / (int)oper1->value, result);
                push(operStack, lint("", result));
            } else
                puts("Cannot divide by zero.");
        } else
            printf("Division does not make sense on @s and @s\n", oper2->type, oper1->type);
    } else {
        puts("Not enough operands for division.");
    }
}

void mod() {
    ltype *oper1 = NULL;
    ltype *oper2 = NULL;
    
    if(!(isEmpty(operStack)))
        oper1 = pop(operStack);

    if(!(isEmpty(operStack)))
        oper2 = pop(operStack);

    if(oper1 && oper2) {
        if((strcmp(oper1->type, "Integer") == 0) && (strcmp(oper2->type, "Integer") == 0)) {
            char result[32];
            bzero(result, 32);
            if(oper1->value != 0) {
                int_to_str((int)oper2->value % (int)oper1->value, result);
                push(operStack, lint("", result));
            } else
                puts("Cannot mod by zero.");
        } else
            printf("Mod does not make sense on @s and @s\n", oper2->type, oper1->type);
    } else {
        puts("Not enough operands for mod.");
    }
}

void not() {
    ltype *oper1 = NULL;

    if(!(isEmpty(operStack)))
        oper1 = pop(operStack);
    else {
        puts("Not enough operands for not.");
        return;
    }
    //this is mostly a stupid joke...because it's not the string passed in.
    if(strcmp(oper1->type, "String") == 0) {
        if(strcmp(oper1->value, "OMG"))
            push(operStack, lstring("", "OMG"));
        else
            push(operStack, lstring("", "BBQ"));
    } else if(strcmp(oper1->type, "Integer") == 0) {
        char result[32];
        bzero(result, 32);
        int_to_str(~(int)oper1->value, result);
        push(operStack, lint("", result));
    } else {
        (int)oper1->value == 1 ? push(operStack, lbool("", "False")) : push(operStack, lbool("", "True"));
    }
}

void len() {
    ltype *oper = NULL;

    if(!(isEmpty(operStack)))
        oper = pop(operStack);
    else {
        puts("Not enough operands for len.");
        return;
    }
    char tmp[32];
    bzero(tmp, 32);
    int_to_str(oper->len, tmp);
    push(operStack, lint("", tmp));
}

void equals() {
    ltype *oper1 = NULL;
    ltype *oper2 = NULL;

    if(!(isEmpty(operStack)))
        oper1 = pop(operStack);

    if(!(isEmpty(operStack)))
        oper2 = pop(operStack);

    if(oper1 && oper2)
    {
        if((strcmp(oper1->type, "Integer") == 0 && strcmp(oper2->type, "Integer") == 0) || (strcmp(oper1->type, "Boolean") == 0 && strcmp(oper2->type, "Boolean") == 0)) {
            if(oper1->value == oper2->value)
                push(operStack, lbool("", "True"));
            else
                push(operStack, lbool("", "False"));
        } else if (strcmp(oper1->type, "String") == 0 && strcmp(oper2->type, "String") == 0) {
            if(strcmp(oper1->value, oper2->value) == 0)
                push(operStack, lbool("", "True"));
            else
                push(operStack, lbool("", "False"));
        } else
            push(operStack, lbool("", "False"));
    } else {
        puts("Not enough operands for equality");
    }
}

void type() {
    ltype *oper1 = NULL;

    if(!(isEmpty(operStack))) {
        oper1 = pop(operStack);
    }

    if(oper1 != NULL)
        push(operStack, lstring("", oper1->type));
}

void terminate() {
    ltype *oper1 = NULL;

    if(!(isEmpty(operStack))) {
        oper1 = pop(operStack);
    }
    //don't worry if the stack is empty.  We're going to terminate anyway.
    if(oper1 && (strcmp(oper1->type, "Integer") == 0))
        _terminate((int)oper1->value);
    else 
        _terminate(0);
}
