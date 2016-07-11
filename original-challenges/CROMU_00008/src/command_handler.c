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
#include <libcgc.h>
#include <stdlib.h>
#include "command_handler.h"
#include "database.h"
#include "io.h"
#include "expression_parser.h"
#include "exception_handler.h"

// State machine for the authenticated user

// The command handler table
tCommandHandlerTable g_cmdTable[] =
{
    { "insert", command_insert, CMD_FLAG_AUTH },
    { "remove", command_remove, CMD_FLAG_AUTH },
    { "update", command_update, CMD_FLAG_AUTH },
    { "print", command_print, CMD_FLAG_AUTH },
    { "find", command_find, CMD_FLAG_AUTH },
    { "login", command_login, CMD_FLAG_NOAUTH },
    { "logout", command_logout, CMD_FLAG_AUTH },
    { "exit", command_exit, CMD_FLAG_NOAUTH | CMD_FLAG_EXIT },
    { "", NULL, 0 }
};

int32_t stringbeg( uint8_t *pszInString, uint8_t *pszMatchString )
{
    int32_t index;

    index = 0;
    while ( *pszInString )
    {
        if ( isspace( *pszInString ) )
        {
            pszInString++;
            index++;
            continue;
        }

        break;
    }

    while ( *pszInString && *pszMatchString )
    {
        if ( tolower( *pszInString ) != tolower( *pszMatchString ) )
            return -1;

        pszInString++;
        pszMatchString++;
        index++;
    }

    return index;
}

void init_user( tUserState *pState )
{
    pState->state = USER_STATE_NOAUTH;
}

int8_t parse_command( uint8_t *pszCommandString, tUserState *pState )
{
    uint32_t i;
    int32_t index;
    int8_t iRetVal = -1;

    // Find command!
    for ( i = 0; ; i++ )
    {
        if ( g_cmdTable[i].pCmdHandler == NULL )
            break;

        if ( (index = stringbeg( pszCommandString, g_cmdTable[i].szCommand )) > 0 )
        {
            if ( (g_cmdTable[i].flags & CMD_FLAG_AUTH) && pState->state == USER_STATE_NOAUTH )
            {
                printf( "Authentication required. Try login\n" );
                return -1;
            }

            // Call cmd fptr
            return (*g_cmdTable[i].pCmdHandler)( pszCommandString+index, pState );
        }
    }

    printf( "Command not found.\n" );

    return -1;
}

int8_t command_insert( uint8_t *pszCommandString, tUserState *pState )
{
    int32_t iRetVal;
    tDateTime tempDate;
    char szFirstName[MAX_STRING_LENGTH+1];
    char szLastName[MAX_STRING_LENGTH+1];
    char szUserName[MAX_STRING_LENGTH+1];
    char szTemp[MAX_STRING_LENGTH+1];
    uint32_t creationDate;
    uint32_t newRecordNumber;

    printf( "First name: " );

    iRetVal = readLine( STDIN, szFirstName, MAX_STRING_LENGTH );

    sanitize_string( szFirstName );

    printf( "Last name: " );

    iRetVal = readLine( STDIN, szLastName, MAX_STRING_LENGTH );

    sanitize_string( szLastName );

    printf( "User name: " );

    iRetVal = readLine( STDIN, szUserName, MAX_STRING_LENGTH );

    sanitize_string( szUserName );

    printf( "Birthdate (mm/dd/yy hh:mm:ss): " );

    iRetVal = readLine( STDIN, szTemp, MAX_STRING_LENGTH );

    creationDate = parse_date( szTemp, &tempDate );

    if ( creationDate == 0 )
    {
        printf( "Date parsing error.\n" );
        return 0;
    }

    printf( "Date is: $d/$d/$d $d:$d:$d\n", tempDate.month, tempDate.day, GET_DB_YEAR(tempDate.year), tempDate.hour, tempDate.minute, tempDate.second );

    // Insert into database
    newRecordNumber = db_add_record( szUserName, szFirstName, szLastName, tempDate );

    if ( newRecordNumber == BAD_RECORD_ERROR )
    {
        printf( "Database full.\n" );
        return 0;
    }

    printf( "Data added, record $d\n", newRecordNumber );
    return 0;
}

int8_t command_remove( uint8_t *pszCommandString, tUserState *pState )
{
    int32_t iRetVal;
    uint32_t index;
    char szTemp[MAX_STRING_LENGTH+1];

    printf( "Enter record number to remove: " );

    iRetVal = readLine( STDIN, szTemp, MAX_STRING_LENGTH );

    index = atoi( szTemp );

    if ( db_remove_record( index ) )
        printf( "Record $d removed.\n", index );
    else
        printf( "Record not found.\n" );

    return 0;
}

int8_t command_update( uint8_t *pszCommandString, tUserState *pState )
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

    printf( "Enter record number to update: " );

    iRetVal = readLine( STDIN, szTemp, MAX_STRING_LENGTH );

    index = atoi( szTemp );

    pCurrentRecordInfo = db_search_index( index );

    if ( pCurrentRecordInfo == NULL )
    {
        printf( "Record not found.\n" );
        return 0;
    }

    printf( "Update first name ($s): ", pCurrentRecordInfo->szFirstName  );

    iRetVal = readLine( STDIN, szFirstName, MAX_STRING_LENGTH );

    sanitize_string( szFirstName );

    printf( "Update last name ($s): ", pCurrentRecordInfo->szLastName );

    iRetVal = readLine( STDIN, szLastName, MAX_STRING_LENGTH );

    sanitize_string( szLastName );

    printf( "Update user name ($s): ", pCurrentRecordInfo->szUserName );

    iRetVal = readLine( STDIN, szUserName, MAX_STRING_LENGTH );

    sanitize_string( szUserName );

    printf( "Update birthdate ($d/$d/$d $d:$d:$d): ", pCurrentRecordInfo->birthDate.month, pCurrentRecordInfo->birthDate.day, GET_DB_YEAR(pCurrentRecordInfo->birthDate.year), pCurrentRecordInfo->birthDate.hour, pCurrentRecordInfo->birthDate.minute, pCurrentRecordInfo->birthDate.second );

    iRetVal = readLine( STDIN, szTemp, MAX_STRING_LENGTH );

    creationDate = parse_date( szTemp, &tempDate );

    if ( creationDate == 0 )
    {
        printf( "Date parsing error.\n" );
        return 0;
    }

    printf( "Date is: $d/$d/$d $d:$d:$d\n", tempDate.month, tempDate.day, GET_DB_YEAR(tempDate.year), tempDate.hour, tempDate.minute, tempDate.second );

    // Insert into database
    newRecordNumber = db_update_record( index, szUserName, szFirstName, szLastName, tempDate );

    if ( newRecordNumber == 0 )
    {
        printf( "Record update failed.\n" );
        return 0;
    }

    printf( "Record $d updated.\n", index );
    return 0;
}

int8_t command_print( uint8_t *pszCommandString, tUserState *pState )
{
    int32_t iRetVal;
    uint32_t index;
    char szTemp[MAX_STRING_LENGTH+1];
    tDDAPRecord *pCurrentRecordInfo;

    printf( "Enter record number to print (or \"all\" for all records): " );

    iRetVal = readLine( STDIN, szTemp, MAX_STRING_LENGTH );

    if ( strcmp( szTemp, "all" ) == 0 )
    {
        printf( "Printing all $d records.\n", db_get_record_count() );

        for ( index = 0; index < db_get_record_count(); index++ )
        {
            pCurrentRecordInfo = db_search_index( index );

            if ( pCurrentRecordInfo == NULL )
                return 0;

            print_record_helper( pCurrentRecordInfo );
        }
    }
    else
    {
        index = atoi( szTemp );

        pCurrentRecordInfo = db_search_index( index );

        if ( pCurrentRecordInfo == NULL )
        {
            printf( "Record not found.\n" );
            return 0;
        }

        print_record_helper( pCurrentRecordInfo );
    }

    return 0;
}

int8_t command_find( uint8_t *pszCommandString, tUserState *pState )
{
    int32_t iRetVal;
    uint32_t index;
    char szTemp[MAX_STRING_LENGTH+1];

    // Check for empty database
    if ( db_get_record_count() == 0 )
    {
        printf( "Database empty. No records to find.\n" );

        return 0;
    }

    printf( "Enter search express (firstname or fn, lastname or ln, username or un, birthdate or bd, operators ==, !=, >, <, AND and OR):\n" );

    iRetVal = readLine( STDIN, szTemp, MAX_STRING_LENGTH );

    TRY
    {
        parse_search_expression( szTemp );
    }
    CATCH( PARSER_EXCEPTION_INVALID_TOKEN )
    {
        printf( "Invalid token\n" );
    }
    CATCH( PARSER_EXCEPTION_SYNTAX_ERROR )
    {
        printf( "Syntax error\n" );
    }
    CATCH( PARSER_EXCEPTION_OVERFLOW )
    {
        printf( "Parser overflow\n" );
    }
    FINALLY
    {

    }
    ETRY

    return 0;
}

int8_t command_login( uint8_t *pszCommandString, tUserState *pState )
{
    if ( pState->state == USER_STATE_AUTH )
    {
        printf( "You are already logged in.\n" );
        return 0;
    }

    pState->state = USER_STATE_AUTH;

    printf( "You logged in.\n" );
    return 0;
}

int8_t command_logout( uint8_t *pszCommandString, tUserState *pState )
{
    pState->state = USER_STATE_NOAUTH;

    printf ("You logged out.\n" );
    return 0;
}

int8_t command_exit( uint8_t *pszCommandString, tUserState *pState )
{
    printf( "Disconnecting.\n" );

    // Exit application
    _terminate( 0 );

    return 0;
}
