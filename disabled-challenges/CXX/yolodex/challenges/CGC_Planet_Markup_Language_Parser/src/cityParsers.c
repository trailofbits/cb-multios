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

#include "cgc_cityParsers.h"

int cgc_cityMenu ( pCity ci )
{
	int choice = 0;
	char selection[30];
	pBorder pb = NULL;
	
	if ( ci == NULL ) {
		return 0;
	}

	while (1) {
		cgc_printf("\nCity: @s\n", ci->name);
		cgc_printf("1) Display City Info\n");
		cgc_printf("2) Set Mayor\n");
		cgc_printf("3) Set Url\n");
		cgc_printf("4) Set Population\n");
		cgc_printf("5) Add Border\n");
		cgc_printf("6) Delete City and Exit Menu\n");
		cgc_printf("7) Exit Menu\n");
		cgc_printf("Selection: ");

		cgc_bzero( selection, 30 );
		cgc_receive_until( selection, '\n', 4 );
		choice = cgc_atoi( selection );

		switch (choice) {
			case 1:
				cgc_printCityInfo( ci );
				break;
			case 2:
				cgc_printf("\n-> ");
				cgc_bzero( selection, 30 );
				cgc_receive_until( selection, '\n', 29);

				choice = 0;
				while ( cgc_isalnum(selection[choice]) || selection[choice] == ' ') {
					ci->mayor[choice] = selection[choice];
					choice++;
				}
				ci->mayor[choice] = '\x00';
				break;
			case 3:
				cgc_printf("\n-> ");
				cgc_bzero( selection, 30 );
				cgc_receive_until( selection, '\n', 29 );

				/// While it is valid url data copy loop and copy it
				/// Since the buffer is zeroed and the max received is 29 this loop
				///	should be safe
				choice = 0;
				while( cgc_isalnum(selection[choice]) || selection[choice] == ':' || selection[choice] == '.' || selection[choice] == '/') {
					ci->url[choice] = selection[choice];
					choice++;
				}

				ci->url[choice] = '\x00';
				break;
			case 4:
				cgc_printf("\n-> ");
				cgc_bzero( selection, 30);
				cgc_receive_until( selection, '\n', 29 );
				ci->population = cgc_atoi( selection);
				break;
			case 5:
				if ( ci->border_count > CITYBORDERMAX ) {
					cgc_printf("Max Borders\n");
					break;
				}

                                if ( cgc_allocate( sizeof(Border), 0, (void**)&pb) != 0 ) {
                                        pb = NULL;
                                        continue;
                                }

                                cgc_printf("Lat Start: ");
                                cgc_bzero(selection, 30 );
                                cgc_receive_until( selection, '\n', 19 );
                                pb->latStart = cgc_atof(selection);

                                cgc_printf("Long Start: ");
                                cgc_bzero(selection, 30 );
                                cgc_receive_until( selection, '\n', 19 );
                                pb->lngStart = cgc_atof(selection);

                                cgc_printf("Lat End: ");
                                cgc_bzero(selection, 30 );
                                cgc_receive_until( selection, '\n', 19 );
                                pb->latEnd = cgc_atof(selection);

                                cgc_printf("Long End: ");
                                cgc_bzero(selection, 30 );
                                cgc_receive_until( selection, '\n', 19 );
                                pb->lngEnd = cgc_atof(selection);

                                ci->borders[ ci->border_count ] = pb;
                                ci->border_count++;
				break;
			case 6:
				cgc_freeCity(ci);
				return 0;
				break;
			case 7:
				return 1;
				break;
			default:
				cgc_printf("Invalid\n");
				break;
		};
	}

	return 1;
}

/**
 * Frees a buffer and sets the variable to NULL
 * @param buffer Pointer to the pointer to be freed
 * @return Returns nothing
 **/
void cgc_freeCharPtr( char**buffer )
{
	if ( buffer == NULL ) {
		return;
	}

	if ( *buffer == NULL ) {
		return;
	}

	cgc_deallocate(*buffer, cgc_strlen(*buffer) + 1 );

	*buffer = NULL;

	return;

}

/**
 * Frees a city structure any sub structures.
 * @param ci Pointer to a city structure
 * @return Returns nothing
 **/
void cgc_freeCity( pCity ci )
{
	int index = 0;
	if ( ci == NULL ) {
		return;
	}

	for ( index = 0; index < ci->border_count; index++ ) {
		cgc_deallocate( ci->borders, sizeof(Border) );
	}

	cgc_deallocate( ci, sizeof(City) );

	return;
}

/**
 * Initializes a city structure
 * @param ci Pointer to a city structure
 * @return Returns nothing
 **/
void cgc_initCity( pCity ci )
{
	int index = 0;

	if ( ci == NULL ) {
		return;
	}

	for (index = 0; index < CITYBORDERMAX; index++ ) {
		ci->name[index] = 0x00;
		ci->borders[index] = NULL;
	}

	for (index = 0; index < 30; index++ ) {
		ci->mayor[index] = 0;
		ci->url[index] = 0;
	}

	ci->population = -1;
	ci->border_count = 0;

	return;
}

/**
 * Prints valid information from a city structure
 * @param ci Pointer to a city structure
 * @return Returns nothing
 **/
void cgc_printCityInfo( pCity ci )
{
	int index = 0;
	pBorder b = NULL;

	if ( ci == NULL ) {
		return;
	}

	cgc_printf("\t\t\t\tCity: ");

	if ( ci->name[0] != '\x00' ) {
		cgc_printf("@s\n", ci->name);
	} else {
		cgc_printf("Unknown\n");
	}

	if (ci->population >= 0 ) {
		cgc_printf("\t\t\t\t\tPopulation: @d\n", ci->population);
	}

	if ( ci->mayor[0] != '\x00') {
		cgc_printf("\t\t\t\t\tMayor: @s\n", ci->mayor);
	}

	if ( ci->url[0] != '\x00' ) {
		cgc_printf("\t\t\t\t\tUrl: @s\n", ci->url);
	}

	for ( index = 0; index < ci->border_count; index++ ) {
		b = ci->borders[index];

		if ( b!= NULL ) {
			cgc_printf("\t\t\t\t\tBorder: @f @f @f @f\n", b->latStart, b->lngStart, b->latEnd, b->lngEnd);
		}
	}

	return;

}

/**
 * Skips the opening "{" or "{#" depending upon the ending flag
 * @param str Pointer to a string structure
 * @param ending Flag indicating if it is an ending structure to expect a '#'
 * @return Returns 0 on failure, 1 on success
 **/
int cgc_skipOpen( pstring str, int ending )
{
	if (str == NULL ) {
		return 0;
	}

	cgc_skipWhiteSpace(str);
	if ( !cgc_atChar( str, '{' ) ) {
		return 0;
	}

	/// Skip the opening brace
	if ( cgc_incChar(str) == -1 ) {
		return 0;
	}

	/// Skip to the element id value or '#' if it is an end
	cgc_skipWhiteSpace(str);

	if ( ending ) {
		if (!cgc_atChar( str, '#') ) {
			return 0;
		}

		if ( cgc_incChar( str ) == -1 ) {
			return 0;
		}
	}

	return 1;
}

/**
 * Top level function for parsing a City PML element
 * @param str Pointer to a string structure
 * @return Returns a pointer to a filled in city structure or NULL on failure
 **/
pCity cgc_cityTopLevel( pstring str )
{
	int lastGood = 0;
	pCity newCity = NULL;
	int startIndex = 0;
	int endIndex = 0;
	char *temp = NULL;
	int tempInt = 0;
	element el;

	if ( str == NULL ) {
		goto end;
	}

	/// Skip the opening "{"
	if ( cgc_skipOpen( str, 0 ) == 0 ) {
		goto end;
	}

	/// Get the start and end index of the element id
	cgc_getIndex( str, &startIndex);
	endIndex = cgc_skipAlpha(str);

	if ( endIndex == -1 ) {
		goto end;
	}

	if ( startIndex == endIndex ) {
		goto end;
	}

	temp = cgc_copyData( str, startIndex, endIndex );

	if ( temp == NULL ) {
		goto end;
	}

	if ( cgc_strcmp( temp, "City") != 0 ) {
		cgc_deallocate(temp, cgc_strlen(temp) + 1 );
		goto end;
	}

	cgc_deallocate(temp, cgc_strlen(temp) + 1 );

	cgc_skipWhiteSpace( str );
	if ( !cgc_atChar( str, '}') ) {
		goto end;
	}

	cgc_incChar( str );
	cgc_skipWhiteSpace(str);

	lastGood = str->index;

	if ( cgc_allocate( sizeof(City), 0, (void**)&newCity) != 0 ) {
		newCity = NULL;
		goto error;
	}

	cgc_initCity( newCity );

	temp = cgc_pullNextElementName( str );

	while ( temp != NULL ) {
		el = cgc_elementNameToEnum( temp );

		cgc_deallocate(temp, cgc_strlen(temp) + 1 );

		switch (el) {
			case name:
				temp = cgc_extractName( str );

				if ( temp == NULL ) {
					goto error;
				}

				/// Clear it out
				cgc_bzero( newCity->name, 20 );

				/// Copy the name data. It has already been filtered 
				///	for invalid characters.
				cgc_strncpy( newCity->name, temp, 19);

				/// Free the buffer
				cgc_deallocate( temp, cgc_strlen(temp) + 1 );
				temp = NULL;
				break;
			case mayor:
				temp = cgc_extractMayor( str );

				if ( temp == NULL ) {
					goto error;
				}
			
				cgc_bzero( newCity->mayor, 30 );
#ifdef PATCHED
				cgc_strncpy( newCity->mayor, temp, 29 );
#else
				cgc_strcpy( newCity->mayor, temp );
#endif
				cgc_freeCharPtr( &temp );

				break;
			case url:
				temp = cgc_extractUrl( str );

				if ( temp == NULL ) {
					goto error;
				}

				cgc_bzero( newCity->url, 30 );

				cgc_strncpy( newCity->url, temp, 29 );
				cgc_freeCharPtr( &temp );
				break;
			case border:
				if ( newCity->border_count >= CITYBORDERMAX) {
					goto error;
				}

				tempInt = newCity->border_count;

				newCity->borders[ tempInt ] = cgc_extractBorder(str);

				if ( newCity->borders[ tempInt] == NULL ) {
					goto error;
				}

				newCity->border_count++;
				break;
			case population:
				newCity->population = cgc_extractPopulation( str );

				if ( newCity->population < 0 ) {
					goto error;
				}

				break;
			default:
				cgc_printf("!!Invalid element ID for City\n");
				goto error;
				break;
		};

		lastGood = str->index;
		temp = cgc_pullNextElementName(str);
	}

	if ( cgc_skipOpen( str, 1) == 0 ) {
		goto error;
	}

	cgc_getIndex( str, &startIndex);
	endIndex = cgc_skipAlpha( str );

	if ( endIndex == -1 ) {
		goto error;
	} else if ( startIndex == endIndex ) {
		goto error;
	}

	temp = cgc_copyData( str, startIndex, endIndex );

	if ( temp == NULL ) {
		goto error;
	}

	if ( cgc_strcmp( temp, "City") != 0 ) {
		cgc_deallocate(temp, cgc_strlen(temp) + 1 );
		goto error;
	}

	cgc_deallocate( temp, cgc_strlen(temp) + 1 );
	cgc_skipWhiteSpace(str);
	if ( !cgc_atChar( str, '}') ) {
		goto error;
	}

	cgc_incChar(str);
	goto end;
error:
	if ( newCity ) {
		cgc_freeCity( newCity );
		newCity = NULL;
	}

	cgc_printf("!!Error at: @s\n", str->buffer + lastGood);
	str->index = lastGood;

end:
	return newCity;
}

/**
 * Extracts the data from the Mayor element id
 * @param str Pointer to a string structure
 * @return Returns a pointer to the data or NULL on failure
 *	The caller must free the pointer
 **/
char *cgc_extractMayor( pstring str )
{
	char *mayor = NULL;
	register int startIndex = 0;
	register int endIndex = 0;
 	char *temp = NULL;

	if ( !str ) {
		return NULL;
	}

	/// This skips any whitespace and opening '{ '
	if (cgc_skipOpen(str, 0 ) == 0 ) {
		return NULL;
	}

	startIndex = str->index;
	endIndex = cgc_skipAlpha(str);

	if ( endIndex == -1 || startIndex == endIndex ) {
		return NULL;
	}

	mayor = cgc_copyData( str, startIndex, endIndex );

	if ( mayor == NULL ) {
		return NULL;
	}

	if ( cgc_strcmp( mayor, "Mayor") != 0 ) {
		cgc_freeCharPtr( &mayor );
		return NULL;
	}

	cgc_freeCharPtr( &mayor );

	cgc_skipWhiteSpace( str );

	if (!cgc_atChar( str, '}') ) {
		return NULL;
	}

	/// Skip the Closing brace
	cgc_incChar( str );

	startIndex = cgc_skipWhiteSpace(str);

	/// Using this function allows things like Sir Winston Churchill 3rd
	endIndex = cgc_skipToNonAlphaNumSpace( str );

	if ( endIndex < 0 || startIndex == endIndex ) {
		return NULL;
	}

	while ( cgc_isspace( str->buffer[endIndex-1] ) ) {
		endIndex--;
	}

	mayor = cgc_copyData( str, startIndex, endIndex );

	if ( mayor == NULL ) {
		return NULL;
	}

	cgc_skipWhiteSpace(str);

	/// Skip the opening brace and '#'
	if ( cgc_skipOpen( str, 1 ) == 0 ) {
		goto error;
	}

	startIndex = str->index;
	endIndex = cgc_skipAlpha( str );

	if ( endIndex == -1 || startIndex == endIndex ) {
		goto error;
	}

	temp = cgc_copyData( str, startIndex, endIndex );

	if ( temp == NULL ) {
		goto error;
	}

	if ( cgc_strcmp( temp, "Mayor") != 0 ) {
		cgc_freeCharPtr( &temp );
		goto error;
	}

	cgc_skipWhiteSpace(str);

	if ( !cgc_atChar( str, '}' ) ) {
		goto error;
	}

	cgc_incChar(str);
	
	goto end;
error:
	cgc_freeCharPtr( &mayor );
end:
	return mayor; 
}

/**
 * Extract the data from the Url element.
 * 	This can be something such as http://www.rome.com
 * @param str Pointer to a string structure
 * @return Returns the element data or NULL on failure
 *	The caller is responsible for freeing the pointer
 **/
char *cgc_extractUrl( pstring str ) 
{
	char *url = NULL;
	int startIndex = 0;
	char *temp = NULL;

	if ( str == NULL ) {
		goto end;
	}

	if ( cgc_skipOpen( str, 0 ) == 0 ) {
		goto end;
	}

	cgc_getIndex( str, &startIndex );

	cgc_skipAlpha(str);

	url = cgc_copyData( str, startIndex, str->index);

	if ( url == NULL ) {
		goto end;
	}

	if ( cgc_strcmp( url, "Url" ) ) {
		cgc_freeCharPtr( &url );
		goto end;
	}

	cgc_skipWhiteSpace( str );

	if (!cgc_atChar( str, '}') ) {
		goto end;
	}

	cgc_incChar(str);
	cgc_skipWhiteSpace(str);
	cgc_getIndex( str, &startIndex);

	cgc_skipUrl( str );

	url = cgc_copyData( str, startIndex, str->index );

	if ( url == NULL ) {
		goto end;
	}

	cgc_skipWhiteSpace(str);
	if ( cgc_skipOpen( str, 1 ) == 0 ) {
		goto error;
	}

	cgc_getIndex( str, &startIndex );
	cgc_skipAlpha(str);
	temp = cgc_copyData( str, startIndex, str->index);

	if ( temp == NULL ) {
		goto error;
	}

	if ( cgc_strcmp( temp, "Url") != 0 ) {
		cgc_freeCharPtr( &temp );
		goto error;
	}

	cgc_freeCharPtr( &temp );

	cgc_skipWhiteSpace(str);
	if ( !cgc_atChar( str, '}') ) {
		goto error;
	}

	cgc_incChar(str);

	goto end;
error:
	if ( url ) {
		cgc_freeCharPtr( &url );
	}

end:
	return url;
}
