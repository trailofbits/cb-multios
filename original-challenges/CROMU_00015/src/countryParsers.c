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

#include "countryParsers.h"

#define BSIZE 40

int countryMenu( pCountry co )
{
	int choice = 0;
	size_t length = 0;
	char selection[BSIZE];
	char *t = NULL;
	pBorder pb = NULL;

	if ( co == NULL ) {
		return 0;
	}

	while (1) {
		printf("\nCountry: @s\n", co->name);
		printf("1) Display CountryInfo\n");
		printf("2) Set Capitol\n");
		printf("3) Set Population\n");
		printf("4) Add Language\n");
		printf("5) Add border\n");
		printf("6) Add Territory\n");
		printf("7) Select Territory\n");
		printf("8) Delete Country and Exit Menu\n");
		printf("9) Exit menu\n");

		bzero(selection, BSIZE);
		printf("Selection: ");
		receive_until( selection, '\n', 3);

		choice = atoi(selection);

		if ( choice < 1 || choice > 9 ) {
			printf("Invalid...\n");
			continue;
		}

		if ( choice == 1 ) {
			printCountryInfo( co );
		} else if (choice == 2 ) {
			printf("\n-> ");
			bzero(selection, BSIZE);

#ifdef PATCHED
			receive_until(selection, '\n', 19);
#else
			receive_until( selection, '\n', BSIZE-1);
#endif

			choice = 0;
			while ( isalpha( selection[choice]) ) {
				co->capitol[choice] = selection[choice];
				choice++;
			}
			co->capitol[choice] = '\x00';

		} else if ( choice == 3 ) {
			printf("\n-> ");
			bzero(selection, BSIZE);
			receive_until(selection, '\n', 19);

			co->population = atoi( selection );
		} else if ( choice == 4 ) {
			if ( co->language_count >= COUNTRYLANGUAGEMAX ) {
				printf("!!Max languages reached\n");
				continue;
			}

			printf("\n-> ");
			bzero(selection, BSIZE );
			receive(0, selection, 19, &length);

			if ( allocate( strlen(selection)+1, 0, (void**)&(t)) != 0 ) {
				t = NULL;
				continue;
			}

			bzero( t, strlen(selection)+1);

			choice = 0;
			while ( isalpha( selection[choice] ) ) {
				t[choice] = selection[choice];
				choice++;
			}
			t[choice] = '\x00';

			co->languages[ co->language_count ] = t;
			co->language_count++;
		} else if ( choice == 5 ) {
			if ( co->border_count >= COUNTRYBORDERMAX) {
				printf("!!Max borders reached\n");
				continue;
			}

			if ( allocate( sizeof(Border), 0, (void**)&pb) != 0 ) {
				pb = NULL;
				continue;
			}

			printf("Lat Start: ");
			bzero(selection, BSIZE );
			receive(0, selection, 19, &length);
			pb->latStart = atof(selection);

			printf("Long Start: ");
			bzero(selection, BSIZE );
			receive(0, selection, 19, &length);
			pb->lngStart = atof(selection);

			printf("Lat End: ");
			bzero(selection, BSIZE );
			receive(0, selection, 19, &length);
			pb->latEnd = atof(selection);

			printf("Long End: ");
			bzero(selection, BSIZE );
			receive(0, selection, 19, &length);
			pb->lngEnd = atof(selection);

			co->borders[ co->border_count ] = pb;
			co->border_count++;
		} else if ( choice == 6 ) {
			if ( co->territory_count >= COUNTRYTERRITORYMAX) {
				printf("!!Max Territories reached\n");
				continue;
			}

                        choice = 0;
                        while ( choice < COUNTRYTERRITORYMAX && co->territories[choice] != NULL ) {
                                choice++;
                        }

			if ( choice == COUNTRYTERRITORYMAX ) {
				printf("!!Max Territories reached\n");
				continue;
			}

                        if ( allocate( sizeof(Territory), 0, (void**)(&co->territories[ choice ]) ) != 0 ) {
                                printf("!!Failed to allocate structure\n");
                                co->territories[ choice ] = NULL;
                                continue;
                        }       
                        
                        initTerritory( co->territories[choice] );
                        
			printf("\nNew Territory: ");
			bzero(selection, BSIZE);
                        receive_until(selection, '\n', 19);

                        length = 0;
                        while ( isalnum( selection[length] ) ) {
                                co->territories[choice]->name[length] = selection[length];
                                length++;
                        }       
			co->territories[choice]->name[length] = '\x00';
			co->territory_count++;
                        
		} else if ( choice == 7 ) {

			printf("\nTerritories:\n");
			for ( choice = 0; choice < COUNTRYTERRITORYMAX; choice++ ) {
				if ( co->territories[choice] != NULL ) {
					printf("@d) @s\n", choice+1, co->territories[ choice ] );
				}
			}

			bzero(selection, BSIZE);
			printf("\n-> ");
			receive(0, selection, 3, &length);
			choice = atoi(selection);

			if ( choice < 1 || choice > COUNTRYTERRITORYMAX || co->territories[choice-1] == NULL ) {
				printf("Invalid choice...\n");
				continue;
			}

			if ( territoryMenu( co->territories[choice-1]) == 0 ) {
				co->territories[choice-1] = NULL ;
				co->territory_count--;
			}

		} else if ( choice == 8 ) {
			freeCountry(co);
			return 0;
		} else if ( choice == 9 ) {
			return 1;
		}
		
	}

end:
	return 1;
}

/**
 * Print the country information from the structure
 * @param co Pointer to the country structure.
 * @return Returns nothing
 */
void printCountryInfo( pCountry co )
{
	int index = 0;
	pBorder b = NULL;

	if ( co == NULL ) {
		return;
	}
	
	printf("\tCountry: ");

	if ( co->name[0] == '\x00' ) {
		printf("Unknown\n");
	} else {
		printf("@s\n", co->name);
	}

	printf("\t\tCapitol: ");
	if ( co->capitol[0] == '\x00' ) {
		printf("Unknown\n");
	} else {
		printf("@s\n", co->capitol);
	}

	if ( co->population >= 0 ) {
		printf("\t\tPopulation: @d\n", co->population);
	}

	while ( index < co->language_count ) {
		if ( co->languages[index] != NULL ) {
			printf("\t\tLanguage: @s\n", co->languages[index]);
		}
		index++;
	}

	index = 0;

	while ( index < co->border_count ) {
		b = co->borders[index];
		if ( b != NULL ) {
			printf("\t\tBorder: @f @f @f @f\n", b->latStart, b->lngStart, b->latEnd, b->lngEnd);
		}
		index++;
	}

	index = 0;

	while ( index < COUNTRYTERRITORYMAX ) {
		if ( co->territories[index] != NULL ) {
			printTerritoryInfo( co->territories[index] );
		}
		index++;
	}

	return;	
}

/**
 * Frees a country structure
 * @param co Pointer to a country structure to free
 * @return Returns nothing
 **/
void freeCountry( pCountry co )
{
	int index = 0;

	if ( co == NULL ) {
		return;
	}

	while (index < co->border_count) {
		if ( co->borders[index] != NULL ) {
			deallocate( co->borders[index], sizeof( Border ) );
			co->borders[index] = NULL;
		}
		index++;
	}

	index = 0;
	while ( index < co->language_count) {
		if ( co->languages[index] != NULL ) {
			deallocate( co->languages[index], strlen(co->languages[index]) + 1 );
			co->languages[index] = NULL;
		}
		index++;
	}

	index = 0;
	while ( index < COUNTRYTERRITORYMAX) {
		if ( co->territories[index] != NULL ) {
			freeTerritory( co->territories[index] );
			co->territories[index] = NULL;
		}
		index++;
	}

	deallocate( co, sizeof(Country) );

	return;
}

/**
 * Initialize the values of a country structure
 * @param co Pointer to a country structure to initialize
 * @return Returns nothing
 **/
void initCountry( pCountry co )
{
	int index = 0;

	if ( co == NULL ) {
		return;
	}

	bzero( co->name, 20 );

	co->population = -1;
	co->language_count = 0;

	co->border_count = 0;

	bzero( co->languages, sizeof(char*) * COUNTRYLANGUAGEMAX);
	bzero( co->borders, sizeof(pBorder) * COUNTRYBORDERMAX);
	bzero( co->territories, sizeof(pTerritory) * COUNTRYTERRITORYMAX);

	return;
}

/**
 * This function handles the top level parsing of country elements
 * @param str Pointer to a string structure
 * @return Returns a pointer to a country structure or NULL on failure
 **/
pCountry countryTopLevel( pstring str )
{
	pCountry newCountry = NULL;
	char * temp_name = NULL;
	int lastGood = 0;
	int startIndex = 0;
	int endIndex = 0;
	element el = 0;

	if ( str == NULL ) {
		goto end;
	}

	/// Allocate a new country structure
	if ( allocate(sizeof(Country), 0, (void**)&newCountry) != 0 ) {
		newCountry = NULL;
		goto end;
	}

	initCountry( newCountry );

	skipWhiteSpace(str);

	lastGood = getIndex( str, &lastGood );

	if ( !atChar( str, '{' ) ) {
		goto error;
	}

	if ( skipLength( str, 1 ) < 0 ) {
		goto error;
	}

	skipWhiteSpace(str);

	startIndex = str->index;

	endIndex = skipAlpha( str );

	if ( endIndex == -1 || startIndex == endIndex ) {
		goto error;
	}
	
	/// Confirm the opening element;		
	temp_name = copyData( str, startIndex, endIndex );

	if ( temp_name == NULL ) {
		goto error;
	}

	if ( strcmp( temp_name, "Country" ) != 0 ) {
		printf("!!Country: Invalid opening element id\n");
		deallocate( temp_name, strlen(temp_name) + 1 );
		goto error;
	}

	deallocate(temp_name, strlen(temp_name) + 1 );

	skipWhiteSpace(str);

	if ( str->buffer[ str->index ] != '}' ) {
		goto error;
	}

	incChar( str );

	lastGood = str->index;

	temp_name = pullNextElementName( str );

	while ( temp_name != NULL ) {
		el = elementNameToEnum( temp_name );

		deallocate( temp_name, strlen(temp_name) + 1 );

		switch (el) {
			case name:
				temp_name = extractName( str );

				if ( temp_name == NULL ) {
					goto error;
				}

				bzero( newCountry->name, 20);
				strncpy( newCountry->name, temp_name, 19 );

				deallocate( temp_name, strlen(temp_name)+1);
				temp_name = NULL;
				break;
			case capitol:

				temp_name = extractCapitol( str );

				if ( !temp_name ) {
					goto error;
				}

				bzero( newCountry->capitol, 20 );
				strncpy( newCountry->capitol, temp_name, 19 );

				deallocate( temp_name, strlen(temp_name)+1);
				temp_name = NULL;
				break;
			case population:
				newCountry->population = extractPopulation(str);

				if (newCountry->population < 0 ) {
					goto error;
				}

				break;
			case language:

				if ( newCountry->language_count >= COUNTRYLANGUAGEMAX ) {
					printf("!!Max country language count is @d\n", COUNTRYLANGUAGEMAX);
					goto error;
				}

				newCountry->languages[newCountry->language_count] = extractLanguage(str);

				if ( newCountry->languages[ newCountry->language_count] == NULL ) {
					goto error;
				}

				newCountry->language_count++;

				break;
			case border:
				if ( newCountry->border_count >= COUNTRYBORDERMAX ) {
					printf("!!Max country border count is @d\n", COUNTRYBORDERMAX);
					goto error;
				}

				newCountry->borders[newCountry->border_count] = extractBorder(str);

				if ( newCountry->borders[ newCountry->border_count] == NULL ) {
					goto error;
				}

				newCountry->border_count++;

				break;
			case territory:
				if ( newCountry->territory_count >= COUNTRYTERRITORYMAX) {
					printf("!!Max territories is @d\n", COUNTRYTERRITORYMAX);
					goto error;
				}

				newCountry->territories[newCountry->territory_count] = territoryTopLevel(str);

				if (newCountry->territories[newCountry->territory_count] == NULL ) {
					goto error;
				}
	
				newCountry->territory_count++;

				break;
			default:
				printf("Invalid for country\n");
				goto error;
				break;
		};

		lastGood = str->index;

		temp_name = pullNextElementName( str );
	}

	skipWhiteSpace( str );

	if ( !atChar( str, '{' ) ) {
		goto error;
	}

	if ( skipLength( str, 1 ) < 0 ) {
		goto error;
	}

	skipWhiteSpace( str );

	if ( !atChar( str, '#' ) ) {
		goto error;
	}

	if ( skipLength( str, 1 ) < 0 ) {
		goto error;
	}

	startIndex = str->index;

	endIndex = skipAlpha( str );

	if ( endIndex < 0 ) {
		goto error;
	}

	if ( startIndex == endIndex ) {
		goto error;
	}

	temp_name = copyData( str, startIndex, endIndex );

	if ( temp_name == NULL ) {
		goto error;
	}

	if ( strcmp( temp_name, "Country" ) != 0 ) {
		deallocate(temp_name, strlen(temp_name) + 1 );
		goto error;
	}

	deallocate( temp_name, strlen(temp_name) + 1 );

	skipWhiteSpace(str);

	if ( !atChar( str, '}' ) ) {
		goto error;
	}

	incChar( str );

	goto end;
error:
	if (newCountry != NULL ) {
		freeCountry( newCountry );
		newCountry = NULL;
	}

	str->index = lastGood;

	printf("Error at: @s\n", str->buffer + str->index);

end:
	return newCountry;
}

/**
 * Parse the Language element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the language character string or NULL on failure
 **/
char* extractLanguage( pstring str )
{
	char *temp = NULL;
	char *language = NULL;
	register int start = 0;
	register int end = 0;

	if (str == NULL ) {
		return NULL;
	}

	start = skipWhiteSpace(str);

	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate opening brace\n");
		return language;
	}

	/// Skip past the curly brace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip opening brace\n");
		return language;
	}

	/// Skip any additional whitespace
	start = skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the element id\n");
		return language;
	}

	/// Copy the element id from the string
	temp = copyData( str, start, end );

	if ( temp == NULL ) {
		printf("!!Copy from @d to @d failed\n", start, end);
		return NULL;
	}

	/// If the element id is not "Language" then this is the wrong function
	if ( strcmp( temp, "Language") != 0 ) {
		printf("!!Element id is not \"Language\"\n");
		deallocate( temp, strlen(temp) + 1 );
		temp = NULL;
		return language;
	}

	/// The buffer is no longer needed so free it
	deallocate(temp, strlen(temp) + 1);

	/// Skip to the end of the element id
	skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate initial closing brace\n");
		return NULL;
	}

	/// Skip the closing brace as well as any whitespace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip initial closing brace\n");
		return language;
	}

	start = skipWhiteSpace( str );
	end = skipAlpha( str );

	if ( start == end ) {
		printf("!!Failed to find language data\n");
		return language;
	}

	/// Copy the language element data
	language = copyData( str, start, end );

	if ( language == NULL ) {
		printf("!!Failed to copy language data\n");
		return language;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate the final opening brace\n");
		goto error;
	}

	/// Skip past the brace
	if ( incChar( str) == -1 ) {
		printf("!!Failed to skip the final opening brace\n");
		goto error;
	}
	
	skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !atChar( str, '#' ) ) {
		printf("!!Failed to locate the closing mark\n");		
		goto error;
	}

	/// Skip past the # but save the start
	start = skipLength( str, 1 );

	if ( start == -1 ) {
		printf("!!Failed to skip closing mark\n");
		goto error;
	}

	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the closing element id\n");
		goto error;
	}
	
	temp = copyData( str, start, end );

#ifdef PATCHED
	if ( temp == NULL ) {
		goto error;
	}
#endif

	if ( strcmp( temp, "Language") != 0 ) {
		printf("!!Invalid closing element id: @s\n", temp);
		deallocate(temp, strlen(temp)+1);
		goto error;
	}

	deallocate(temp, strlen(temp)+1);

	skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate final closing brace\n");
		goto error;
	}

	/// Skip past the closing brace
	skipLength( str, 1 );
		

	goto end;

error:
	if (language != NULL) {
		deallocate( language, strlen(language) + 1 );
		language = NULL;
	}

end:
	return language;
}

/**
 * Parse the Capitol element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the capitol string or NULL on failure
 **/
char* extractCapitol( pstring str )
{
	char *temp = NULL;
	char *capitol = NULL;
	int start = 0;
	int end = 0;

	if (str == NULL ) {
		return NULL;
	}

	skipWhiteSpace(str);

	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate opening brace\n");
		return capitol;
	}

	/// Skip past the curly brace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip opening brace\n");
		return NULL;
	}

	/// Skip any additional whitespace
	start = skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		return NULL;
	}

	/// Copy the element id from the string
	temp = copyData( str, start, end );

	if ( temp == NULL ) {
		return NULL;
	}

	/// If the element id is not "Capitol" then this is the wrong function
	if ( strcmp( temp, "Capitol") != 0 ) {
		deallocate( temp, (end-start) + 1 );
		temp = NULL;
		return temp;
	}

	/// The buffer is no longer needed so free it
	deallocate(temp, (end-start) + 1);

	/// Skip to the end of the element id
	skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !atChar( str, '}' ) ) {
		return NULL;
	}

	/// Skip the closing brace as well as any whitespace
	if ( incChar( str ) == -1 ) {
		return NULL;
	}

	skipWhiteSpace( str );
	getIndex( str, &start );

	end = skipAlpha( str );

	if ( !(start ^ end) ) {
		return NULL;
	}

	/// Copy the capitol element data
	capitol = copyData( str, start, end );

	if ( capitol == NULL ) {
		return NULL;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate the final opening brace\n");
		goto error;
	}

	/// Skip past the brace
	if ( incChar( str) == -1 ) {
		printf("!!Failed to skip the final opening brace\n");
		goto error;
	}
	
	skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !atChar( str, '#' ) ) {
		printf("!!Failed to locate the closing mark\n");		
		goto error;
	}

	/// Skip past the # but save the start
	start = skipLength( str, 1 );

	if ( start == -1 ) {
		printf("!!Failed to skip closing mark\n");
		goto error;
	}

	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the closing element id\n");
		goto error;
	}
	
	temp = copyData( str, start, end );

#ifdef PATCHED
	if ( temp == NULL ) {
		goto error;
	}
#endif

	if ( strcmp( temp, "Capitol") != 0 ) {
		printf("!!Invalid closing element id: @s\n", temp);
		deallocate(temp, strlen(temp)+1);
		goto error;
	}

	deallocate(temp, strlen(temp)+1);

	skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate final closing brace\n");
		goto error;
	}

	/// Skip past the closing brace
	skipLength( str, 1 );
		

	goto end;

error:
	if (capitol != NULL) {
		deallocate( capitol, strlen(capitol) + 1 );
		capitol = NULL;
	}

end:
	return capitol;
}

