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
#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <stdint.h>
#include "date.h"

#define MAX_STRING_LENGTH       (128)
#define MAX_DDAP_RECORDS        (64)

#define BAD_RECORD_ERROR        (0xFFFFFFFF)

typedef struct __DDAP_RECORD_ENTRY
{
    uint32_t index;
    char szFirstName[MAX_STRING_LENGTH+1];
    char szLastName[MAX_STRING_LENGTH+1];
    char szUserName[MAX_STRING_LENGTH+1];
    tDateTime birthDate;
} tDDAPRecord;

#define GET_DB_YEAR( year ) ( year + 1900 )

void init_database( void );

uint32_t db_add_record( char *pszUserName, char *pszFirstName, char *pszLastName, tDateTime birthDate );
uint32_t db_update_record( uint32_t index, char *pszUserName, char *pszFirstName, char *pszLastName, tDateTime birthDate );
uint32_t db_remove_record( uint32_t index );
uint32_t db_get_record_count( void );

tDDAPRecord *db_search_first_name( char *pszFirstName );
tDDAPRecord *db_search_last_name( char *pszLastName );
tDDAPRecord *db_search_index( uint32_t index );
tDDAPRecord *db_search_user_name( char *pszUserName );
tDDAPRecord *db_search_birth_date( tDateTime date  );

void print_record_helper( tDDAPRecord * );

#endif // __DATABASE_H__
