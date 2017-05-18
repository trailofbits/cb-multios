/*

Author: John Berry <hj@cromulence.co>

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

#include "cgc_genericParsers.h"

/**
 * Parse the Border element and return a structure containing the data
 * @param str Pointer to a string structure
 * @return Returns a pointer to a border structure or NULL on failure
 **/
Border *cgc_extractBorder( pstring str )
{
	char *temp = NULL;
	pBorder bor = NULL;
	int start = 0;
	int end = 0;

	if (str == NULL ) {
		return bor;
	}

	/// Allocate a new border structure
	if ( cgc_allocate( sizeof(Border), 0, (void**)&bor) != 0 ) {
		bor = NULL;
		return bor;
	}

	cgc_skipWhiteSpace(str);

	/// If it does not open with a '{' then it is invalid.
	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate opening brace\n");
		goto error;
	}

	/// Skip past the curly brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip opening brace\n");
		goto error;
	}

	/// Skip any additional whitespace
	cgc_skipWhiteSpace(str);

	/// Save the index
	start = str->index;

	/// This should skip any to either whitespace or a closing '}'
	end = cgc_skipAlpha( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the element id\n");
		goto error;
	}

	/// If start and end are then same then it is an invalid character
	if ( start == end ) {
		goto error;
	}

	/// Copy the element id from the string
	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		cgc_printf("!!Copy from @d to @d failed\n", start, end);
		goto error;
	}

	/// If the element id is not "Border" then this is the wrong function
	if ( cgc_strcmp( temp, "Border") != 0 ) {
		cgc_printf("!!Element id is not \"Border\"\n");
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
		temp = NULL;
		goto error;
	}

	/// The buffer is no longer needed so free it
	cgc_deallocate(temp, cgc_strlen(temp) + 1);

	/// Skip to the end of the element id
	cgc_skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate initial closing brace\n");
		goto error;
	}

	/// Skip the closing brace as well as any whitespace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip initial closing brace\n");
		goto error;
	}

	start = cgc_skipWhiteSpace( str );

	/// The border data must be a float
	end = cgc_skipFloat( str );

	if ( start == end ) {
		cgc_printf("!!Failed to locate first lat\n");
		goto error;
	}

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the first latitude float\n");
		goto error;
	}

	temp = cgc_copyData( str, start, end );

	if (temp == NULL ) {
		cgc_printf("!!Failed to copy first latitude float\n");
		goto error;
	}

	/// Convert the first value
	bor->latStart = cgc_atof( temp );

	cgc_deallocate( temp, (end-start) + 1 );

	/// Skip to the next value
	start = cgc_skipWhiteSpace( str );

	end = cgc_skipFloat(str);

	if ( start == end ) {
		cgc_printf("!!Failed to locate first long\n");
		goto error;
	}

	if ( start == -1 || end == -1 ) {
		cgc_printf("!!Failed to locate first longitude float\n");
		goto error;
	}

	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		cgc_printf("!!Failed to copy first longitude float\n");
		goto error;
	}

	/// Convert the first long
	bor->lngStart = cgc_atof( temp );

	cgc_deallocate( temp, (end-start) + 1 );

	/// Skip to the next value
	start = cgc_skipWhiteSpace( str );

	end = cgc_skipFloat(str);

	if ( start == end ) {
		cgc_printf("!!Failed to locate second lat\n");
		goto error;
	}

	if ( start == -1 || end == -1 ) {
		cgc_printf("!!Failed to locate second latitude float\n");
		goto error;
	}

	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		cgc_printf("!!Failed to copy second latitude float\n");
		goto error;
	}

	/// Convert the second lat
	bor->latEnd = cgc_atof( temp );

	cgc_deallocate( temp, (end-start) + 1 );

	/// Skip to the next value
	start = cgc_skipWhiteSpace( str );

	end = cgc_skipFloat(str);

	if ( start == end ) {
		cgc_printf("!!Failed to locate second long\n");
		goto error;
	}

	if ( start == -1 || end == -1 ) {
		cgc_printf("!!Failed to locate second longitude float\n");
		goto error;
	}

	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		cgc_printf("!!Failed to copy second longitude float\n");
		goto error;
	}

	/// Convert the second long
	bor->lngEnd = cgc_atof( temp );

	cgc_deallocate( temp, (end-start) + 1 );

	cgc_skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate the final opening brace\n");
		goto error;
	}

	/// Skip past the brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip the final opening brace\n");
		goto error;
	}
	
	cgc_skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !cgc_atChar( str, '#' ) ) {
		cgc_printf("!!Failed to locate the closing mark\n");		
		goto error;
	}

	/// Skip past the # but save the start
	start = cgc_skipLength( str, 1 );

	if ( start == -1 ) {
		cgc_printf("!!Failed to skip closing mark\n");
		goto error;
	}

	end = cgc_skipAlpha( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the closing element id\n");
		goto error;
	}
	
	temp = cgc_copyData( str, start, end );

#ifdef PATCHED
	if ( temp == NULL ) {
		goto error;
	}
#endif

	if ( cgc_strcmp( temp, "Border") != 0 ) {
		cgc_printf("!!Invalid closing element id: @s\n", temp);
		cgc_deallocate(temp, cgc_strlen(temp)+1);
		goto error;
	}

	cgc_deallocate(temp, cgc_strlen(temp)+1);

	cgc_skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate final closing brace\n");
		goto error;
	}

	/// Skip past the closing brace
	cgc_skipLength( str, 1 );

	/// Everything succeeded, skip error
	goto fin;
		
error:
	cgc_deallocate( bor, sizeof(Border) );
	bor = NULL;

fin:
	return bor;
}

/**
 * Parse the Population element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the integer value or -1 on failure. Population should never be negative.
 **/
int cgc_extractPopulation( pstring str )
{
	char *temp = NULL;
	int pop = -1;
	int start = 0;
	int end = 0;

	/// These will be used specifically for the name data
	int ps = 0;
	int pe = 0;

	if (str == NULL ) {
		return -1;
	}

	cgc_skipWhiteSpace(str);

	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate opening brace\n");
		return -1;
	}

	/// Skip past the curly brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip opening brace\n");
		return -1;
	}

	/// Skip any additional whitespace
	cgc_skipWhiteSpace(str);

	/// Save the index
	start = str->index;

	/// This should skip any to either whitespace or a closing '}'
	end = cgc_skipAlpha( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the element id\n");
		return -1;
	}

	/// Copy the element id from the string
	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		cgc_printf("!!Copy from @d to @d failed\n", start, end);
		return -1;
	}

	/// If the element id is not "Population" then this is the wrong function
	if ( cgc_strcmp( temp, "Population") != 0 ) {
		cgc_printf("!!Element id is not \"Population\"\n");
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
		temp = NULL;
		return -1;
	}

	/// The buffer is no longer needed so free it
	cgc_deallocate(temp, cgc_strlen(temp) + 1);

	/// Skip to the end of the element id
	cgc_skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate initial closing brace\n");
		return -1;
	}

	/// Skip the closing brace as well as any whitespace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip initial closing brace\n");
		return -1;
	}

	cgc_skipWhiteSpace( str );

	/// Copy the start index to store the data
	ps = str->index;

	/// The population data must be an integer
	pe = cgc_skipInt( str );

	if ( pe == -1 ) {
		cgc_printf("!!Failed to locate the end of the population data\n");
		return end;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	cgc_skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate the final opening brace\n");
		return -1;
	}

	/// Skip past the brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip the final opening brace\n");
		return -1;
	}
	
	cgc_skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !cgc_atChar( str, '#' ) ) {
		cgc_printf("!!Failed to locate the closing mark\n");		
		return -1;
	}

	/// Skip past the # but save the start
	start = cgc_skipLength( str, 1 );

	if ( start == -1 ) {
		cgc_printf("!!Failed to skip closing mark\n");
		return start;
	}

	end = cgc_skipAlpha( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the closing element id\n");
		return end;
	}
	
	temp = cgc_copyData( str, start, end );

#ifdef PATCHED
	if ( temp == NULL ) {
		return -1;
	}
#endif 

	if ( cgc_strcmp( temp, "Population") != 0 ) {
		cgc_printf("!!Invalid closing element id: @s\n", temp);
		cgc_deallocate(temp, cgc_strlen(temp)+1);
		return -1;
	}

	cgc_deallocate(temp, cgc_strlen(temp)+1);

	cgc_skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate final closing brace\n");
		return -1;
	}

	/// Skip past the closing brace
	cgc_skipLength( str, 1 );
		
	/// Copy the name element data
	temp = cgc_copyData( str, ps, pe );

	if ( temp == NULL ) {
		cgc_printf("!!Failed to copy population data\n");
		return -1;
	}

	pop = cgc_atoi( temp );

	cgc_deallocate( temp, cgc_strlen(temp) + 1 );

	return pop;
}

/**
 * Extracts the data from the Name element
 * @param str Pointer to a string structure
 * @return Returns a pointer to the name data or NULL on failure
 *	The calling function must free the name pointer
 **/
char *cgc_extractName( pstring str )
{
	char *temp = NULL;
	char *name = NULL;
	int start = 0;
	int end = 0;

	/// These will be used specifically for the name data
	int ns = 0;
	int ne = 0;

	if (str == NULL ) {
		return name;
	}

	cgc_skipWhiteSpace(str);

	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate opening brace\n");
		return name;
	}

	/// Skip past the curly brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip opening brace\n");
		return name;
	}

	/// Skip any additional whitespace
	cgc_skipWhiteSpace(str);

	/// Save the index
	start = str->index;

	/// This should skip any to either whitespace or a closing '}'
	end = cgc_skipAlpha( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the element id\n");
		return NULL;
	}

	/// Copy the element id from the string
	temp = cgc_copyData( str, start, end );

#ifdef PATCHED
	if ( temp == NULL ) {
		return NULL;
	}
#endif

	if ( temp == NULL ) {
		cgc_printf("!!Copy from @d to @d failed\n", start, end);
		return NULL;
	}

	/// If the element id is not "Name" then this is the wrong function
	if ( cgc_strcmp( temp, "Name") != 0 ) {
		cgc_printf("!!Element id is not \"Name\"\n");
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
		temp = NULL;
		return NULL;
	}

	/// The buffer is no longer needed so free it
	cgc_deallocate(temp, cgc_strlen(temp) + 1);

	/// Skip to the end of the element id
	cgc_skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate initial closing brace\n");
		return NULL;
	}

	/// Skip the closing brace as well as any whitespace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip initial closing brace\n");
		return NULL;
	}

	cgc_skipWhiteSpace( str );

	/// Copy the start index to store the data
	ns = str->index;

	/// The name data must be alphanumeric
	ne = cgc_skipToNonAlphaNum( str );

	if ( ne == -1 ) {
		cgc_printf("!!Failed to locate the end of the name data\n");
		return NULL;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	cgc_skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate the final opening brace\n");
		return NULL;
	}

	/// Skip past the brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip the final opening brace\n");
		return NULL;
	}
	
	cgc_skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !cgc_atChar( str, '#' ) ) {
		cgc_printf("!!Failed to locate the closing mark\n");		
		return NULL;
	}

	/// Skip past the # but save the start
	start = cgc_skipLength( str, 1 );

	if ( start == -1 ) {
		cgc_printf("!!Failed to skip closing mark\n");
		return NULL;
	}

	end = cgc_skipAlpha( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the closing element id\n");
		return NULL;
	}
	
	temp = cgc_copyData( str, start, end );

#ifdef PATCHED
	if ( temp == NULL ) {
		return NULL;
	}
#endif

	if ( cgc_strcmp( temp, "Name") != 0 ) {
		cgc_printf("!!Invalid closing element id: @s\n", temp);
		cgc_deallocate(temp, cgc_strlen(temp)+1);
		return NULL;
	}

	cgc_deallocate(temp, cgc_strlen(temp)+1);

	cgc_skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate final closing brace\n");
		return NULL;
	}

	/// Skip past the closing brace
	cgc_skipLength( str, 1 );
		
	/// Copy the name element data
	name = cgc_copyData( str, ns, ne );

	return name;
}
