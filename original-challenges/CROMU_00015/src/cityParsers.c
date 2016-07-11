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

#include "cityParsers.h"

int cityMenu ( pCity ci )
{
	int choice = 0;
	char selection[30];
	pBorder pb = NULL;
	
	if ( ci == NULL ) {
		return 0;
	}

	while (1) {
		printf("\nCity: @s\n", ci->name);
		printf("1) Display City Info\n");
		printf("2) Set Mayor\n");
		printf("3) Set Url\n");
		printf("4) Set Population\n");
		printf("5) Add Border\n");
		printf("6) Delete City and Exit Menu\n");
		printf("7) Exit Menu\n");
		printf("Selection: ");

		bzero( selection, 30 );
		receive_until( selection, '\n', 4 );
		choice = atoi( selection );

		switch (choice) {
			case 1:
				printCityInfo( ci );
				break;
			case 2:
				printf("\n-> ");
				bzero( selection, 30 );
				receive_until( selection, '\n', 29);

				choice = 0;
				while ( isalnum(selection[choice]) || selection[choice] == ' ') {
					ci->mayor[choice] = selection[choice];
					choice++;
				}
				ci->mayor[choice] = '\x00';
				break;
			case 3:
				printf("\n-> ");
				bzero( selection, 30 );
				receive_until( selection, '\n', 29 );

				/// While it is valid url data copy loop and copy it
				/// Since the buffer is zeroed and the max received is 29 this loop
				///	should be safe
				choice = 0;
				while( isalnum(selection[choice]) || selection[choice] == ':' || selection[choice] == '.' || selection[choice] == '/') {
					ci->url[choice] = selection[choice];
					choice++;
				}

				ci->url[choice] = '\x00';
				break;
			case 4:
				printf("\n-> ");
				bzero( selection, 30);
				receive_until( selection, '\n', 29 );
				ci->population = atoi( selection);
				break;
			case 5:
				if ( ci->border_count > CITYBORDERMAX ) {
					printf("Max Borders\n");
					break;
				}

                                if ( allocate( sizeof(Border), 0, (void**)&pb) != 0 ) {
                                        pb = NULL;
                                        continue;
                                }

                                printf("Lat Start: ");
                                bzero(selection, 30 );
                                receive_until( selection, '\n', 19 );
                                pb->latStart = atof(selection);

                                printf("Long Start: ");
                                bzero(selection, 30 );
                                receive_until( selection, '\n', 19 );
                                pb->lngStart = atof(selection);

                                printf("Lat End: ");
                                bzero(selection, 30 );
                                receive_until( selection, '\n', 19 );
                                pb->latEnd = atof(selection);

                                printf("Long End: ");
                                bzero(selection, 30 );
                                receive_until( selection, '\n', 19 );
                                pb->lngEnd = atof(selection);

                                ci->borders[ ci->border_count ] = pb;
                                ci->border_count++;
				break;
			case 6:
				freeCity(ci);
				return 0;
				break;
			case 7:
				return 1;
				break;
			default:
				printf("Invalid\n");
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
void freeCharPtr( char**buffer )
{
	if ( buffer == NULL ) {
		return;
	}

	if ( *buffer == NULL ) {
		return;
	}

	deallocate(*buffer, strlen(*buffer) + 1 );

	*buffer = NULL;

	return;

}

/**
 * Frees a city structure any sub structures.
 * @param ci Pointer to a city structure
 * @return Returns nothing
 **/
void freeCity( pCity ci )
{
	int index = 0;
	if ( ci == NULL ) {
		return;
	}

	for ( index = 0; index < ci->border_count; index++ ) {
		deallocate( ci->borders, sizeof(Border) );
	}

	deallocate( ci, sizeof(City) );

	return;
}

/**
 * Initializes a city structure
 * @param ci Pointer to a city structure
 * @return Returns nothing
 **/
void initCity( pCity ci )
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
void printCityInfo( pCity ci )
{
	int index = 0;
	pBorder b = NULL;

	if ( ci == NULL ) {
		return;
	}

	printf("\t\t\t\tCity: ");

	if ( ci->name[0] != '\x00' ) {
		printf("@s\n", ci->name);
	} else {
		printf("Unknown\n");
	}

	if (ci->population >= 0 ) {
		printf("\t\t\t\t\tPopulation: @d\n", ci->population);
	}

	if ( ci->mayor[0] != '\x00') {
		printf("\t\t\t\t\tMayor: @s\n", ci->mayor);
	}

	if ( ci->url[0] != '\x00' ) {
		printf("\t\t\t\t\tUrl: @s\n", ci->url);
	}

	for ( index = 0; index < ci->border_count; index++ ) {
		b = ci->borders[index];

		if ( b!= NULL ) {
			printf("\t\t\t\t\tBorder: @f @f @f @f\n", b->latStart, b->lngStart, b->latEnd, b->lngEnd);
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
int skipOpen( pstring str, int ending )
{
	if (str == NULL ) {
		return 0;
	}

	skipWhiteSpace(str);
	if ( !atChar( str, '{' ) ) {
		return 0;
	}

	/// Skip the opening brace
	if ( incChar(str) == -1 ) {
		return 0;
	}

	/// Skip to the element id value or '#' if it is an end
	skipWhiteSpace(str);

	if ( ending ) {
		if (!atChar( str, '#') ) {
			return 0;
		}

		if ( incChar( str ) == -1 ) {
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
pCity cityTopLevel( pstring str )
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
	if ( skipOpen( str, 0 ) == 0 ) {
		goto end;
	}

	/// Get the start and end index of the element id
	getIndex( str, &startIndex);
	endIndex = skipAlpha(str);

	if ( endIndex == -1 ) {
		goto end;
	}

	if ( startIndex == endIndex ) {
		goto end;
	}

	temp = copyData( str, startIndex, endIndex );

	if ( temp == NULL ) {
		goto end;
	}

	if ( strcmp( temp, "City") != 0 ) {
		deallocate(temp, strlen(temp) + 1 );
		goto end;
	}

	deallocate(temp, strlen(temp) + 1 );

	skipWhiteSpace( str );
	if ( !atChar( str, '}') ) {
		goto end;
	}

	incChar( str );
	skipWhiteSpace(str);

	lastGood = str->index;

	if ( allocate( sizeof(City), 0, (void**)&newCity) != 0 ) {
		newCity = NULL;
		goto error;
	}

	initCity( newCity );

	temp = pullNextElementName( str );

	while ( temp != NULL ) {
		el = elementNameToEnum( temp );

		deallocate(temp, strlen(temp) + 1 );

		switch (el) {
			case name:
				temp = extractName( str );

				if ( temp == NULL ) {
					goto error;
				}

				/// Clear it out
				bzero( newCity->name, 20 );

				/// Copy the name data. It has already been filtered 
				///	for invalid characters.
				strncpy( newCity->name, temp, 19);

				/// Free the buffer
				deallocate( temp, strlen(temp) + 1 );
				temp = NULL;
				break;
			case mayor:
				temp = extractMayor( str );

				if ( temp == NULL ) {
					goto error;
				}
			
				bzero( newCity->mayor, 30 );
#ifdef PATCHED
				strncpy( newCity->mayor, temp, 29 );
#else
				strcpy( newCity->mayor, temp );
#endif
				freeCharPtr( &temp );

				break;
			case url:
				temp = extractUrl( str );

				if ( temp == NULL ) {
					goto error;
				}

				bzero( newCity->url, 30 );

				strncpy( newCity->url, temp, 29 );
				freeCharPtr( &temp );
				break;
			case border:
				if ( newCity->border_count >= CITYBORDERMAX) {
					goto error;
				}

				tempInt = newCity->border_count;

				newCity->borders[ tempInt ] = extractBorder(str);

				if ( newCity->borders[ tempInt] == NULL ) {
					goto error;
				}

				newCity->border_count++;
				break;
			case population:
				newCity->population = extractPopulation( str );

				if ( newCity->population < 0 ) {
					goto error;
				}

				break;
			default:
				printf("!!Invalid element ID for City\n");
				goto error;
				break;
		};

		lastGood = str->index;
		temp = pullNextElementName(str);
	}

	if ( skipOpen( str, 1) == 0 ) {
		goto error;
	}

	getIndex( str, &startIndex);
	endIndex = skipAlpha( str );

	if ( endIndex == -1 ) {
		goto error;
	} else if ( startIndex == endIndex ) {
		goto error;
	}

	temp = copyData( str, startIndex, endIndex );

	if ( temp == NULL ) {
		goto error;
	}

	if ( strcmp( temp, "City") != 0 ) {
		deallocate(temp, strlen(temp) + 1 );
		goto error;
	}

	deallocate( temp, strlen(temp) + 1 );
	skipWhiteSpace(str);
	if ( !atChar( str, '}') ) {
		goto error;
	}

	incChar(str);
	goto end;
error:
	if ( newCity ) {
		freeCity( newCity );
		newCity = NULL;
	}

	printf("!!Error at: @s\n", str->buffer + lastGood);
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
char *extractMayor( pstring str )
{
	char *mayor = NULL;
	register int startIndex = 0;
	register int endIndex = 0;
 	char *temp = NULL;

	if ( !str ) {
		return NULL;
	}

	/// This skips any whitespace and opening '{ '
	if (skipOpen(str, 0 ) == 0 ) {
		return NULL;
	}

	startIndex = str->index;
	endIndex = skipAlpha(str);

	if ( endIndex == -1 || startIndex == endIndex ) {
		return NULL;
	}

	mayor = copyData( str, startIndex, endIndex );

	if ( mayor == NULL ) {
		return NULL;
	}

	if ( strcmp( mayor, "Mayor") != 0 ) {
		freeCharPtr( &mayor );
		return NULL;
	}

	freeCharPtr( &mayor );

	skipWhiteSpace( str );

	if (!atChar( str, '}') ) {
		return NULL;
	}

	/// Skip the Closing brace
	incChar( str );

	startIndex = skipWhiteSpace(str);

	/// Using this function allows things like Sir Winston Churchill 3rd
	endIndex = skipToNonAlphaNumSpace( str );

	if ( endIndex < 0 || startIndex == endIndex ) {
		return NULL;
	}

	while ( isspace( str->buffer[endIndex-1] ) ) {
		endIndex--;
	}

	mayor = copyData( str, startIndex, endIndex );

	if ( mayor == NULL ) {
		return NULL;
	}

	skipWhiteSpace(str);

	/// Skip the opening brace and '#'
	if ( skipOpen( str, 1 ) == 0 ) {
		goto error;
	}

	startIndex = str->index;
	endIndex = skipAlpha( str );

	if ( endIndex == -1 || startIndex == endIndex ) {
		goto error;
	}

	temp = copyData( str, startIndex, endIndex );

	if ( temp == NULL ) {
		goto error;
	}

	if ( strcmp( temp, "Mayor") != 0 ) {
		freeCharPtr( &temp );
		goto error;
	}

	skipWhiteSpace(str);

	if ( !atChar( str, '}' ) ) {
		goto error;
	}

	incChar(str);
	
	goto end;
error:
	freeCharPtr( &mayor );
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
char *extractUrl( pstring str ) 
{
	char *url = NULL;
	int startIndex = 0;
	char *temp = NULL;

	if ( str == NULL ) {
		goto end;
	}

	if ( skipOpen( str, 0 ) == 0 ) {
		goto end;
	}

	getIndex( str, &startIndex );

	skipAlpha(str);

	url = copyData( str, startIndex, str->index);

	if ( url == NULL ) {
		goto end;
	}

	if ( strcmp( url, "Url" ) ) {
		freeCharPtr( &url );
		goto end;
	}

	skipWhiteSpace( str );

	if (!atChar( str, '}') ) {
		goto end;
	}

	incChar(str);
	skipWhiteSpace(str);
	getIndex( str, &startIndex);

	skipUrl( str );

	url = copyData( str, startIndex, str->index );

	if ( url == NULL ) {
		goto end;
	}

	skipWhiteSpace(str);
	if ( skipOpen( str, 1 ) == 0 ) {
		goto error;
	}

	getIndex( str, &startIndex );
	skipAlpha(str);
	temp = copyData( str, startIndex, str->index);

	if ( temp == NULL ) {
		goto error;
	}

	if ( strcmp( temp, "Url") != 0 ) {
		freeCharPtr( &temp );
		goto error;
	}

	freeCharPtr( &temp );

	skipWhiteSpace(str);
	if ( !atChar( str, '}') ) {
		goto error;
	}

	incChar(str);

	goto end;
error:
	if ( url ) {
		freeCharPtr( &url );
	}

end:
	return url;
}
