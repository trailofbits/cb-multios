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
#include "cgc_date.h"
#include "cgc_database.h"

tDDAPRecord g_ddapDatabase[MAX_DDAP_RECORDS];
uint32_t g_recordCount;

void cgc_init_database( void )
{
    g_recordCount = 0;
}

uint32_t cgc_db_add_record( char *pszUserName, char *pszFirstName, char *pszLastName, tDateTime birthDate )
{
    uint32_t index;

    if ( g_recordCount >= MAX_DDAP_RECORDS )
        return (BAD_RECORD_ERROR);

    index = g_recordCount;
    g_ddapDatabase[g_recordCount].index = index;

    cgc_strncpy( g_ddapDatabase[g_recordCount].szFirstName, pszFirstName, MAX_STRING_LENGTH );
    cgc_strncpy( g_ddapDatabase[g_recordCount].szLastName, pszLastName, MAX_STRING_LENGTH );
    cgc_strncpy( g_ddapDatabase[g_recordCount].szUserName, pszUserName, MAX_STRING_LENGTH );

    cgc_memcpy( &g_ddapDatabase[g_recordCount].birthDate, &birthDate, sizeof(tDateTime) );

    g_recordCount++;

    return (index);
}

uint32_t cgc_db_update_record( uint32_t index, char *pszUserName, char *pszFirstName, char *pszLastName, tDateTime birthDate )
{
    if ( index >= g_recordCount )
        return (0);

    cgc_strncpy( g_ddapDatabase[index].szFirstName, pszFirstName, MAX_STRING_LENGTH );
    cgc_strncpy( g_ddapDatabase[index].szLastName, pszLastName, MAX_STRING_LENGTH );
    cgc_strncpy( g_ddapDatabase[index].szUserName, pszUserName, MAX_STRING_LENGTH );

    cgc_memcpy( &g_ddapDatabase[index].birthDate, &birthDate, sizeof(tDateTime) );

    return (1);
}

uint32_t cgc_db_remove_record( uint32_t index )
{
    uint32_t i;

    if ( index >= g_recordCount )
        return 0;

    if ( g_recordCount == 0 )
        return 0;

    g_recordCount--;

    for ( i = index; i < g_recordCount; i++ )
    {
        g_ddapDatabase[i].index = g_ddapDatabase[i+1].index-1;
        cgc_strcpy( g_ddapDatabase[i].szFirstName, g_ddapDatabase[i+1].szFirstName );
        cgc_strcpy( g_ddapDatabase[i].szLastName, g_ddapDatabase[i+1].szLastName );
        cgc_strcpy( g_ddapDatabase[i].szUserName, g_ddapDatabase[i+1].szUserName );

        cgc_memcpy( &g_ddapDatabase[i].birthDate, &g_ddapDatabase[i+1].birthDate, sizeof(tDateTime) );
    }

    // 1 for successly deleting record
    return 1;
}

uint32_t cgc_db_get_record_count( void )
{
    return (g_recordCount);
}

tDDAPRecord *cgc_db_search_first_name( char *pszFirstName )
{
    uint32_t i;

    for ( i = 0; i < g_recordCount; i++ )
    {
        if ( cgc_strcmp( pszFirstName, g_ddapDatabase[i].szFirstName ) == 0 )
            return (&g_ddapDatabase[i]);
    }

    return (NULL);
}

tDDAPRecord *cgc_db_search_last_name( char *pszLastName )
{
    uint32_t i;

    for ( i = 0; i < g_recordCount; i++ )
    {
        if ( cgc_strcmp( pszLastName, g_ddapDatabase[i].szLastName ) == 0 )
            return (&g_ddapDatabase[i]);
    }

    return (NULL);
}

tDDAPRecord *cgc_db_search_user_name( char *pszUserName )
{
    uint32_t i;

    for ( i = 0; i < g_recordCount; i++ )
    {
        if ( cgc_strcmp( pszUserName, g_ddapDatabase[i].szUserName ) == 0 )
            return (&g_ddapDatabase[i]);
    }

    return (NULL);
}

tDDAPRecord *cgc_db_search_birth_date( tDateTime birthDate )
{
    uint32_t i;

    for ( i = 0; i < g_recordCount; i++ )
    {
        if ( cgc_date_compare( g_ddapDatabase[i].birthDate, birthDate ) == 0 )
            return (&g_ddapDatabase[i]);
    }

    return (NULL);
}

tDDAPRecord *cgc_db_search_index( uint32_t index )
{
    if ( index < g_recordCount )
        return (&g_ddapDatabase[index]);

    return (NULL);
}

void cgc_print_record_helper( tDDAPRecord *pRecord )
{
    if ( pRecord == NULL )
        return;

    cgc_printf( "Record [$d]\n", pRecord->index );
    cgc_printf( "First name: $s\n", pRecord->szFirstName );
    cgc_printf( "Last name: $s\n", pRecord->szLastName );
    cgc_printf( "User name: $s\n", pRecord->szUserName );
    cgc_printf( "Birthdate: $d/$d/$d $d:$d:$d\n", pRecord->birthDate.month, pRecord->birthDate.day, GET_DB_YEAR(pRecord->birthDate.year), pRecord->birthDate.hour, pRecord->birthDate.minute, pRecord->birthDate.second );
}
