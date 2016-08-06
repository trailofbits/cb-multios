/*

Author: Jason Williams <jdw@cromulence.com>

Copyright (c) 2014 Cromulence LLC

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
#ifndef __EXPRESSION_PARSER_H__
#define __EXPRESSION_PARSER_H__

#include "database.h"

#define PARSER_EXCEPTION_INVALID_TOKEN          1
#define PARSER_EXCEPTION_SYNTAX_ERROR           2
#define PARSER_EXCEPTION_OVERFLOW               3

typedef enum
{
    SYM_OPEN_PARAN,
    SYM_CLOSE_PARAN,
    SYM_EQUAL,
    SYM_NOT_EQUAL,
    SYM_LESS_THAN,
    SYM_GREATER_THAN,
    SYM_AND,
    SYM_OR,
    SYM_LASTNAME,
    SYM_FIRSTNAME,
    SYM_USERNAME,
    SYM_BIRTHDATE,
    SYM_NOTFOUND,
    SYM_END
} eParserSymbol;

typedef enum
{
    ITEM_TYPE_SYMBOL,
    ITEM_TYPE_RESULT,
    ITEM_TYPE_EMPTY
} eItemType;

typedef struct _PARSER_SYMBOL_TABLE
{
    char *text;
    eParserSymbol symbol;
} tParserSymbolTable;

typedef struct _RESULT_ITEM_STACK
{
    eItemType type;
    union
    {
        eParserSymbol symbol;
        uint8_t result_list[MAX_DDAP_RECORDS];
    } data;
    uint8_t result_list_size;
} tItemStack;

void parse_search_expression( char *pszTemp );

#endif // EXPRESSION_PARSER_H__
