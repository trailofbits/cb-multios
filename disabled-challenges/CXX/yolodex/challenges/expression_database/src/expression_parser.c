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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_mem_global.h"
#include "cgc_expression_parser.h"
#include "cgc_database.h"

extern tGlobalMemoryLayout cgc_g_memoryGlobal;

uint8_t cgc_g_parseStackSize = 0;

tItemStack cgc_peek_parser_stack( void )
{
    // Return top item
    if ( cgc_g_parseStackSize == 0 )
    {
        tItemStack temp;

        temp.type = ITEM_TYPE_EMPTY;

        return (temp);
    }

    return (cgc_g_memoryGlobal.parseStack[cgc_g_parseStackSize-1]);
}

tItemStack cgc_pop_parser_stack( void )
{
    // Return top item (pulling it off the stack)
    if ( cgc_g_parseStackSize == 0 )
    {
        tItemStack temp;

        temp.type = ITEM_TYPE_EMPTY;

        return (temp);
    }

    cgc_g_parseStackSize--;

    return (cgc_g_memoryGlobal.parseStack[cgc_g_parseStackSize]);
}

void cgc_push_parser_stack( tItemStack item )
{
#ifdef PATCHED
    if ( cgc_g_parseStackSize < MAX_PARSE_STACKSIZE )
#endif
    {
        cgc_g_memoryGlobal.parseStack[cgc_g_parseStackSize] = item;
        cgc_g_parseStackSize++;
    }
#ifdef PATCHED
    else
    {
        THROW( PARSER_EXCEPTION_OVERFLOW );
    }
#endif
}


tParserSymbolTable g_parseTable[] = {
    { "(", SYM_OPEN_PARAN },
    { ")", SYM_CLOSE_PARAN },
    { "==", SYM_EQUAL },
    { "!=", SYM_NOT_EQUAL },
    { "<", SYM_LESS_THAN },
    { ">", SYM_GREATER_THAN },
    { "AND", SYM_AND },
    { "OR", SYM_OR },
    { "lastname", SYM_LASTNAME },
    { "ln", SYM_LASTNAME },
    { "firstname", SYM_FIRSTNAME },
    { "fn", SYM_FIRSTNAME },
    { "username", SYM_USERNAME },
    { "un", SYM_USERNAME },
    { "birthdate", SYM_BIRTHDATE },
    { "bd", SYM_BIRTHDATE },
    { NULL, SYM_NOTFOUND }
};

int32_t cgc_strbeg( const char *scanString, const char *searchString )
{
    uint32_t i;

    for ( i = 0; ; i++ )
    {
        if ( scanString[i] == '\0' && searchString[i] == '\0' )
            return 0;

        if ( searchString[i] == '\0' )
            return 0;

        if ( scanString[i] == '\0' )
            return 1;

        if ( scanString[i] != searchString[i] )
            return 1;
    }

    return 0;
}

eParserSymbol cgc_parse_get_symbol( char *pszString, uint32_t *new_offset )
{
    uint32_t symIndex;
    uint32_t offset = 0;

    while ( cgc_isspace( pszString[offset] ) )
        offset++;

    if ( pszString[offset] == '\0' )
    {
        (*new_offset) = offset;
        return SYM_END;
    }

    for ( symIndex = 0; ; symIndex++ )
    {
        if ( g_parseTable[symIndex].symbol == SYM_NOTFOUND )
        {
            (*new_offset) = offset;
            return SYM_NOTFOUND;
        }

        if ( cgc_strbeg( pszString+offset, g_parseTable[symIndex].text ) == 0 )
        {
            offset += cgc_strlen( g_parseTable[symIndex].text );
            (*new_offset) = offset;

            return g_parseTable[symIndex].symbol;
        }
    }

    (*new_offset) = offset;
    return SYM_NOTFOUND;
}

int32_t cgc_is_symbol_close_paran( eParserSymbol symbol )
{
    if ( symbol == SYM_CLOSE_PARAN )
        return 1;
    else
        return 0;
}

int32_t cgc_is_symbol_open_paran( eParserSymbol symbol )
{
    if ( symbol == SYM_OPEN_PARAN )
        return 1;
    else
        return 0;
}

int32_t cgc_is_symbol_result_operator( eParserSymbol symbol )
{
    switch( symbol )
    {
    case SYM_AND:
    case SYM_OR:
        return 1;

    default:
        break;
    }

    return 0;
}

int32_t cgc_is_symbol_db_operator( eParserSymbol symbol )
{
    switch ( symbol )
    {
    case SYM_EQUAL:
    case SYM_NOT_EQUAL:
    case SYM_LESS_THAN:
    case SYM_GREATER_THAN:
        return 1;

    default:
        break;
    }

    return 0;
}

int32_t cgc_is_symbol_element( eParserSymbol symbol )
{
    switch( symbol )
    {
    case SYM_LASTNAME:
    case SYM_USERNAME:
    case SYM_FIRSTNAME:
    case SYM_BIRTHDATE:
        return 1;

    default:
        break;
    }

    return 0;
}

int32_t cgc_is_symbol_birthdate( eParserSymbol symbol )
{
    if ( symbol == SYM_BIRTHDATE )
        return 1;
    else
        return 0;
}

void cgc_do_date_search( eParserSymbol comparison_symbol, tDateTime dateCompare )
{
    uint32_t index;
    uint32_t record_total = cgc_db_get_record_count();
    tItemStack results;

    results.type = ITEM_TYPE_RESULT;
    results.result_list_size = 0;

    for ( index = 0; index < record_total; index++ )
    {
        tDDAPRecord *pCur = cgc_db_search_index( index );
        int32_t comparison_result = cgc_date_compare( pCur->birthDate, dateCompare );
        int32_t add_item = 0;

        switch ( comparison_symbol )
        {
        case SYM_LESS_THAN:
            if ( comparison_result == -1 )
                add_item = 1;
            break;

        case SYM_GREATER_THAN:
            if ( comparison_result == 1 )
                add_item = 1;
            break;

        case SYM_EQUAL:
            if ( comparison_result == 0 )
                add_item = 1;
            break;

        case SYM_NOT_EQUAL:
            if ( comparison_result != 0 )
                add_item = 1;
            break;

        default:
            THROW( PARSER_EXCEPTION_INVALID_TOKEN );
            break;
        }

        // Add the result to the result list
        if ( add_item )
            results.data.result_list[results.result_list_size++] = index;
    }

    // Add results
    cgc_push_parser_stack( results );
}

void cgc_do_string_search( eParserSymbol object_type, eParserSymbol comparison_symbol, char *pszSearchString )
{
    uint32_t index;
    uint32_t record_total = cgc_db_get_record_count();
    tItemStack results;

    results.type = ITEM_TYPE_RESULT;
    results.result_list_size = 0;

    for ( index = 0; index < record_total; index++ )
    {
        tDDAPRecord *pCur = cgc_db_search_index( index );
        int32_t comparison_result;
        int32_t add_item = 0;

        switch( object_type )
        {
        case SYM_USERNAME:
            comparison_result = cgc_strcmp( pCur->szUserName, pszSearchString );
            break;

        case SYM_FIRSTNAME:
            comparison_result = cgc_strcmp( pCur->szFirstName, pszSearchString );
            break;

        case SYM_LASTNAME:
            comparison_result = cgc_strcmp( pCur->szLastName, pszSearchString );
            break;

        default:
            THROW( PARSER_EXCEPTION_INVALID_TOKEN );
            break;
        }

        switch ( comparison_symbol )
        {
        case SYM_LESS_THAN:
            if ( comparison_result == -1 )
                add_item = 1;
            break;

        case SYM_GREATER_THAN:
            if ( comparison_result == 1 )
                add_item = 1;
            break;

        case SYM_EQUAL:
            if ( comparison_result == 0 )
                add_item = 1;
            break;

        case SYM_NOT_EQUAL:
            if ( comparison_result != 0 )
                add_item = 1;
            break;

        default:
            THROW( PARSER_EXCEPTION_INVALID_TOKEN );
            break;
        }

        // Add the result to the result list
        if ( add_item )
            results.data.result_list[results.result_list_size++] = index;
    }

    // Add results
    cgc_push_parser_stack( results );
}

void cgc_do_result_search( tItemStack lval, eParserSymbol operator_symbol, tItemStack rval )
{
    if ( operator_symbol == SYM_AND )
    {
        uint32_t record_lval_count = lval.result_list_size;
        uint32_t record_rval_count = rval.result_list_size;
        uint32_t lval_idx, rval_idx;

        tItemStack results;

        results.type = ITEM_TYPE_RESULT;
        results.result_list_size = 0;

        for ( lval_idx = 0; lval_idx < record_lval_count; lval_idx++ )
            for ( rval_idx = 0; rval_idx < record_rval_count; rval_idx++ )
            {
                if ( lval.data.result_list[lval_idx] == rval.data.result_list[rval_idx] )
                {
                    results.data.result_list[results.result_list_size++] = lval.data.result_list[lval_idx];
                }
            }

        // Add new results
        cgc_push_parser_stack( results );
    }
    else if ( operator_symbol == SYM_OR )
    {
        uint32_t record_lval_count = lval.result_list_size;
        uint32_t record_rval_count = rval.result_list_size;
        uint32_t lval_idx, rval_idx;

        tItemStack results;

        results.type = ITEM_TYPE_RESULT;
        results.result_list_size = 0;

        for ( lval_idx = 0; lval_idx < record_lval_count; lval_idx++ )
        {
            uint32_t result_idx = 0;
            uint32_t result_count = results.result_list_size;
            int32_t found = 0;

            for ( result_idx = 0; result_idx < result_count; result_idx++ )
            {
                if ( lval.data.result_list[lval_idx] == results.data.result_list[result_idx] )
                {
                    found = 1;
                    break;
                }
            }

            if ( found == 0 )
                results.data.result_list[results.result_list_size++] = lval.data.result_list[lval_idx];
        }

        for ( rval_idx = 0; rval_idx < record_rval_count; rval_idx++ )
        {
            uint32_t result_idx = 0;
            uint32_t result_count = results.result_list_size;
            int32_t found = 0;

            for ( result_idx = 0; result_idx < result_count; result_idx++ )
            {
                if ( rval.data.result_list[rval_idx] == results.data.result_list[result_idx] )
                {
                    found = 1;
                    break;
                }
            }

            if ( found == 0 )
                results.data.result_list[results.result_list_size++] = rval.data.result_list[rval_idx];
        }

        // Add the new results back
        cgc_push_parser_stack( results );
    }

}

void cgc_do_reduce_stack( void )
{
    for (;;)
    {
        if ( cgc_g_parseStackSize <= 2 )
            break;

        if ( cgc_g_memoryGlobal.parseStack[cgc_g_parseStackSize-1].type == ITEM_TYPE_RESULT &&
             (cgc_g_memoryGlobal.parseStack[cgc_g_parseStackSize-2].type == ITEM_TYPE_SYMBOL && cgc_is_symbol_result_operator( cgc_g_memoryGlobal.parseStack[cgc_g_parseStackSize-2].data.symbol )) &&
             cgc_g_memoryGlobal.parseStack[cgc_g_parseStackSize-3].type == ITEM_TYPE_RESULT )
        {
            tItemStack rval = cgc_pop_parser_stack();
            tItemStack operator = cgc_pop_parser_stack();
            tItemStack lval = cgc_pop_parser_stack();

            // Perform results search search
            cgc_do_result_search( lval, operator.data.symbol, rval );
        }
        else
            break;
    }
}

void cgc_parse_search_expression( char *pszTemp )
{
    int32_t bDone = 0;
    eParserSymbol cur_symbol;
    eParserSymbol last_symbol;
    char *pszCur = pszTemp;
    uint32_t symbol_offset;

    // Reset parse stack
    cgc_g_parseStackSize = 0;

    // Reset last symbol
    last_symbol = SYM_NOTFOUND;

    // Begin parsing
    do
    {
        symbol_offset = 0;
        cur_symbol = cgc_parse_get_symbol( pszCur, &symbol_offset );

        pszCur += symbol_offset;

        // Push symbol onto stack if it is a db operator, open paran, operator, or result operator
        if ( cgc_is_symbol_db_operator( cur_symbol ) )
        {
            // Check to make sure stack is valid
            // Top of stack should be element
            tItemStack item_peek_top = cgc_pop_parser_stack();

            if ( item_peek_top.type != ITEM_TYPE_SYMBOL || !cgc_is_symbol_element( item_peek_top.data.symbol ) )
            {
                THROW( PARSER_EXCEPTION_SYNTAX_ERROR );
                return;
            }

            // Consume next (either string or birthdate)
            if ( item_peek_top.data.symbol == SYM_BIRTHDATE )
            {
                tDateTime tempDate;

                // Parse birthdate
                int32_t result = cgc_parse_date( pszCur, &tempDate );

                if ( result == 0 )
                {
                    THROW( PARSER_EXCEPTION_SYNTAX_ERROR );
                    return;
                }

                pszCur += result;

                // Build result!
                cgc_do_date_search( cur_symbol, tempDate );
            }
            else
            {
                char szTemp[MAX_STRING_LENGTH+1];
                uint32_t cur_pos;

                // Parse string
                while ( cgc_isspace( *pszCur ) )
                    pszCur++;

                if ( *pszCur != '\"' )
                {
                    THROW( PARSER_EXCEPTION_SYNTAX_ERROR );
                    return;
                }

                pszCur++;

                cur_pos = 0;
                while ( *pszCur && *pszCur != '\"' )
                {
                    szTemp[cur_pos++] = *pszCur;
                    pszCur++;

                    if ( cur_pos >= MAX_STRING_LENGTH )
                        break;
                }
                szTemp[cur_pos] = '\0';

                if ( pszCur == '\0' )
                {
                    THROW( PARSER_EXCEPTION_SYNTAX_ERROR );
                    return;
                }

                pszCur++;

                // Perform search
                cgc_do_string_search( item_peek_top.data.symbol, cur_symbol, szTemp );
            }
        }
        else if ( cgc_is_symbol_open_paran( cur_symbol ) )
        {
            tItemStack item_peek_top = cgc_peek_parser_stack();

            // Open paran valid with either no symbol or result operator (AND, OR)
            if ( !(item_peek_top.type == ITEM_TYPE_EMPTY ||
                 (item_peek_top.type == ITEM_TYPE_SYMBOL && item_peek_top.data.symbol == SYM_OPEN_PARAN) ||
                 (item_peek_top.type == ITEM_TYPE_SYMBOL && cgc_is_symbol_result_operator( item_peek_top.data.symbol ))) )
            {
                THROW( PARSER_EXCEPTION_SYNTAX_ERROR );
                return;
            }

            // Push
            tItemStack new_item;
            new_item.type = ITEM_TYPE_SYMBOL;
            new_item.data.symbol = cur_symbol;

            cgc_push_parser_stack( new_item );
        }
        else if ( cgc_is_symbol_close_paran( cur_symbol ) )
        {
            // Should be result on top of stack
            tItemStack item_top = cgc_pop_parser_stack();

            if ( item_top.type != ITEM_TYPE_RESULT )
            {
                THROW( PARSER_EXCEPTION_SYNTAX_ERROR );
                return;
            }

            tItemStack item_next = cgc_pop_parser_stack();

            if ( !(item_next.type == ITEM_TYPE_SYMBOL && item_next.data.symbol == SYM_OPEN_PARAN) )
            {
                THROW( PARSER_EXCEPTION_SYNTAX_ERROR );
                return;
            }

            // Push results back onto the stack
            cgc_push_parser_stack( item_top );
        }
        else if ( cgc_is_symbol_result_operator( cur_symbol ) )
        {
            // Check to make sure the previous items on top of the stack are valid
            tItemStack item_peek_top = cgc_peek_parser_stack();

            // Result operator valid if top of stack is a DB result set
            if ( !(item_peek_top.type == ITEM_TYPE_RESULT) )
            {
                THROW( PARSER_EXCEPTION_SYNTAX_ERROR );
                return;
            }

            // Push operator on the stack
            tItemStack new_item;
            new_item.type = ITEM_TYPE_SYMBOL;
            new_item.data.symbol = cur_symbol;

            // Push results back onto the stack
            cgc_push_parser_stack( new_item );
        }
        else if ( cgc_is_symbol_element( cur_symbol ) )
        {
            // Check to make sure the previous items on top of the stack are valid
            tItemStack item_peek_top = cgc_peek_parser_stack();

            if ( !(item_peek_top.type == ITEM_TYPE_EMPTY ||
                  (item_peek_top.type == ITEM_TYPE_SYMBOL && cgc_is_symbol_open_paran( item_peek_top.data.symbol )) ||
                 (item_peek_top.type == ITEM_TYPE_SYMBOL && cgc_is_symbol_result_operator( item_peek_top.data.symbol ))) )
            {
                THROW( PARSER_EXCEPTION_SYNTAX_ERROR );
                return;
            }

            // If it is an element push it on the stack
            tItemStack new_item;

            new_item.type = ITEM_TYPE_SYMBOL;
            new_item.data.symbol = cur_symbol;

            cgc_push_parser_stack( new_item );
        }
        else if ( cur_symbol == SYM_END )
        {
            bDone = 1;
        }
        else if ( cur_symbol == SYM_NOTFOUND )
        {
            THROW( PARSER_EXCEPTION_SYNTAX_ERROR );
        }

        // Reduce stack if necessary
        cgc_do_reduce_stack();
    } while ( !bDone );

    // Show results
    tItemStack results = cgc_pop_parser_stack();

    if ( results.type != ITEM_TYPE_RESULT || cgc_g_parseStackSize != 0 )
    {
        THROW( PARSER_EXCEPTION_SYNTAX_ERROR );
        return;
    }
    else
    {
        uint32_t result_count = results.result_list_size;
        uint32_t idx;

        // Print search results
        cgc_printf( "Search results, $d items found:\n", result_count );

        for ( idx = 0; idx < result_count; idx++ )
            cgc_print_record_helper( cgc_db_search_index( results.data.result_list[idx] ) );
    }
}


