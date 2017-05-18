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
#include "cgc_command_handler.h"
#include "cgc_database.h"
#include "cgc_io.h"
#include "cgc_expression_parser.h"
#include "cgc_exception_handler.h"

// State machine for the authenticated user

// The command handler table
tCommandHandlerTable g_cmdTable[] =
{
    { "insert", cgc_command_insert, CMD_FLAG_AUTH },
    { "remove", cgc_command_remove, CMD_FLAG_AUTH },
    { "update", cgc_command_update, CMD_FLAG_AUTH },
    { "print", cgc_command_print, CMD_FLAG_AUTH },
    { "find", cgc_command_find, CMD_FLAG_AUTH },
    { "login", cgc_command_login, CMD_FLAG_NOAUTH },
    { "logout", cgc_command_logout, CMD_FLAG_AUTH },
    { "exit", cgc_command_exit, CMD_FLAG_NOAUTH | CMD_FLAG_EXIT },
    { "", NULL, 0 }
};

int32_t cgc_stringbeg( uint8_t *pszInString, uint8_t *pszMatchString )
{
    int32_t index;

    index = 0;
    while ( *pszInString )
    {
        if ( cgc_isspace( *pszInString ) )
        {
            pszInString++;
            index++;
            continue;
        }

        break;
    }

    while ( *pszInString && *pszMatchString )
    {
        if ( cgc_tolower( *pszInString ) != cgc_tolower( *pszMatchString ) )
            return -1;

        pszInString++;
        pszMatchString++;
        index++;
    }

    return index;
}

void cgc_init_user( tUserState *pState )
{
    pState->state = USER_STATE_NOAUTH;
}

int8_t cgc_parse_command( uint8_t *pszCommandString, tUserState *pState )
{
    uint32_t i;
    int32_t index;
    int8_t iRetVal = -1;

    // Find command!
    for ( i = 0; ; i++ )
    {
        if ( g_cmdTable[i].pCmdHandler == NULL )
            break;

        if ( (index = cgc_stringbeg( pszCommandString, g_cmdTable[i].szCommand )) > 0 )
        {
            if ( (g_cmdTable[i].flags & CMD_FLAG_AUTH) && pState->state == USER_STATE_NOAUTH )
            {
                cgc_printf( "Authentication required. Try login\n" );
                return -1;
            }

            // Call cmd fptr
            return (*g_cmdTable[i].pCmdHandler)( pszCommandString+index, pState );
        }
    }

    cgc_printf( "Command not found.\n" );

    return -1;
}

int8_t cgc_command_insert( uint8_t *pszCommandString, tUserState *pState )
{
    int32_t iRetVal;
    tDateTime tempDate;
    char szFirstName[MAX_STRING_LENGTH+1];
    char szLastName[MAX_STRING_LENGTH+1];
    char szUserName[MAX_STRING_LENGTH+1];
    char szTemp[MAX_STRING_LENGTH+1];
    uint32_t creationDate;
    uint32_t newRecordNumber;

    cgc_printf( "First name: " );

    iRetVal = cgc_readLine( STDIN, szFirstName, MAX_STRING_LENGTH );

    cgc_sanitize_string( szFirstName );

    cgc_printf( "Last name: " );

    iRetVal = cgc_readLine( STDIN, szLastName, MAX_STRING_LENGTH );

    cgc_sanitize_string( szLastName );

    cgc_printf( "User name: " );

    iRetVal = cgc_readLine( STDIN, szUserName, MAX_STRING_LENGTH );

    cgc_sanitize_string( szUserName );

    cgc_printf( "Birthdate (mm/dd/yy hh:mm:ss): " );

    iRetVal = cgc_readLine( STDIN, szTemp, MAX_STRING_LENGTH );

    creationDate = cgc_parse_date( szTemp, &tempDate );

    if ( creationDate == 0 )
    {
        cgc_printf( "Date parsing error.\n" );
        return 0;
    }

    cgc_printf( "Date is: $d/$d/$d $d:$d:$d\n", tempDate.month, tempDate.day, GET_DB_YEAR(tempDate.year), tempDate.hour, tempDate.minute, tempDate.second );

    // Insert into database
    newRecordNumber = cgc_db_add_record( szUserName, szFirstName, szLastName, tempDate );

    if ( newRecordNumber == BAD_RECORD_ERROR )
    {
        cgc_printf( "Database full.\n" );
        return 0;
    }

    cgc_printf( "Data added, record $d\n", newRecordNumber );
    return 0;
}

int8_t cgc_command_remove( uint8_t *pszCommandString, tUserState *pState )
{
    int32_t iRetVal;
    uint32_t index;
    char szTemp[MAX_STRING_LENGTH+1];

    cgc_printf( "Enter record number to remove: " );

    iRetVal = cgc_readLine( STDIN, szTemp, MAX_STRING_LENGTH );

    index = cgc_atoi( szTemp );

    if ( cgc_db_remove_record( index ) )
        cgc_printf( "Record $d removed.\n", index );
    else
        cgc_printf( "Record not found.\n" );

    return 0;
}

int8_t cgc_command_update( uint8_t *pszCommandString, tUserState *pState )
{
    int32_t iRetVal;
    tDateTime tempDate;
    char szFirstName[MAX_STRING_LENGTH+1];
    char szLastName[MAX_STRING_LENGTH+1];
    char szUserName[MAX_STRING_LENGTH+1];
    char szTemp[MAX_STRING_LENGTH+1];
    uint32_t creationDate;
    uint32_t newRecordNumber;
    uint32_t index;
    tDDAPRecord *pCurrentRecordInfo;

    cgc_printf( "Enter record number to update: " );

    iRetVal = cgc_readLine( STDIN, szTemp, MAX_STRING_LENGTH );

    index = cgc_atoi( szTemp );

    pCurrentRecordInfo = cgc_db_search_index( index );

    if ( pCurrentRecordInfo == NULL )
    {
        cgc_printf( "Record not found.\n" );
        return 0;
    }

    cgc_printf( "Update first name ($s): ", pCurrentRecordInfo->szFirstName  );

    iRetVal = cgc_readLine( STDIN, szFirstName, MAX_STRING_LENGTH );

    cgc_sanitize_string( szFirstName );

    cgc_printf( "Update last name ($s): ", pCurrentRecordInfo->szLastName );

    iRetVal = cgc_readLine( STDIN, szLastName, MAX_STRING_LENGTH );

    cgc_sanitize_string( szLastName );

    cgc_printf( "Update user name ($s): ", pCurrentRecordInfo->szUserName );

    iRetVal = cgc_readLine( STDIN, szUserName, MAX_STRING_LENGTH );

    cgc_sanitize_string( szUserName );

    cgc_printf( "Update birthdate ($d/$d/$d $d:$d:$d): ", pCurrentRecordInfo->birthDate.month, pCurrentRecordInfo->birthDate.day, GET_DB_YEAR(pCurrentRecordInfo->birthDate.year), pCurrentRecordInfo->birthDate.hour, pCurrentRecordInfo->birthDate.minute, pCurrentRecordInfo->birthDate.second );

    iRetVal = cgc_readLine( STDIN, szTemp, MAX_STRING_LENGTH );

    creationDate = cgc_parse_date( szTemp, &tempDate );

    if ( creationDate == 0 )
    {
        cgc_printf( "Date parsing error.\n" );
        return 0;
    }

    cgc_printf( "Date is: $d/$d/$d $d:$d:$d\n", tempDate.month, tempDate.day, GET_DB_YEAR(tempDate.year), tempDate.hour, tempDate.minute, tempDate.second );

    // Insert into database
    newRecordNumber = cgc_db_update_record( index, szUserName, szFirstName, szLastName, tempDate );

    if ( newRecordNumber == 0 )
    {
        cgc_printf( "Record update failed.\n" );
        return 0;
    }

    cgc_printf( "Record $d updated.\n", index );
    return 0;
}

int8_t cgc_command_print( uint8_t *pszCommandString, tUserState *pState )
{
    int32_t iRetVal;
    uint32_t index;
    char szTemp[MAX_STRING_LENGTH+1];
    tDDAPRecord *pCurrentRecordInfo;

    cgc_printf( "Enter record number to print (or \"all\" for all records): " );

    iRetVal = cgc_readLine( STDIN, szTemp, MAX_STRING_LENGTH );

    if ( cgc_strcmp( szTemp, "all" ) == 0 )
    {
        cgc_printf( "Printing all $d records.\n", cgc_db_get_record_count() );

        for ( index = 0; index < cgc_db_get_record_count(); index++ )
        {
            pCurrentRecordInfo = cgc_db_search_index( index );

            if ( pCurrentRecordInfo == NULL )
                return 0;

            cgc_print_record_helper( pCurrentRecordInfo );
        }
    }
    else
    {
        index = cgc_atoi( szTemp );

        pCurrentRecordInfo = cgc_db_search_index( index );

        if ( pCurrentRecordInfo == NULL )
        {
            cgc_printf( "Record not found.\n" );
            return 0;
        }

        cgc_print_record_helper( pCurrentRecordInfo );
    }

    return 0;
}

int8_t cgc_command_find( uint8_t *pszCommandString, tUserState *pState )
{
    int32_t iRetVal;
    uint32_t index;
    char szTemp[MAX_STRING_LENGTH+1];

    // Check for empty database
    if ( cgc_db_get_record_count() == 0 )
    {
        cgc_printf( "Database empty. No records to find.\n" );

        return 0;
    }

    cgc_printf( "Enter search express (firstname or fn, lastname or ln, username or un, birthdate or bd, operators ==, !=, >, <, AND and OR):\n" );

    iRetVal = cgc_readLine( STDIN, szTemp, MAX_STRING_LENGTH );

    TRY
    {
        cgc_parse_search_expression( szTemp );
    }
    CATCH( PARSER_EXCEPTION_INVALID_TOKEN )
    {
        cgc_printf( "Invalid token\n" );
    }
    CATCH( PARSER_EXCEPTION_SYNTAX_ERROR )
    {
        cgc_printf( "Syntax error\n" );
    }
    CATCH( PARSER_EXCEPTION_OVERFLOW )
    {
        cgc_printf( "Parser overflow\n" );
    }
    FINALLY
    {

    }
    ETRY

    return 0;
}

int8_t cgc_command_login( uint8_t *pszCommandString, tUserState *pState )
{
    if ( pState->state == USER_STATE_AUTH )
    {
        cgc_printf( "You are already logged in.\n" );
        return 0;
    }

    pState->state = USER_STATE_AUTH;

    cgc_printf( "You logged in.\n" );
    return 0;
}

int8_t cgc_command_logout( uint8_t *pszCommandString, tUserState *pState )
{
    pState->state = USER_STATE_NOAUTH;

    cgc_printf ("You logged out.\n" );
    return 0;
}

int8_t cgc_command_exit( uint8_t *pszCommandString, tUserState *pState )
{
    cgc_printf( "Disconnecting.\n" );

    // Exit application
    cgc__terminate( 0 );

    return 0;
}
