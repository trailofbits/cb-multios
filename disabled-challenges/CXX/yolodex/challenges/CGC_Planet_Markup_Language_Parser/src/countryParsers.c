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

#include "cgc_countryParsers.h"

#define BSIZE 40

int cgc_countryMenu( pCountry co )
{
	int choice = 0;
	cgc_size_t length = 0;
	char selection[BSIZE];
	char *t = NULL;
	pBorder pb = NULL;

	if ( co == NULL ) {
		return 0;
	}

	while (1) {
		cgc_printf("\nCountry: @s\n", co->name);
		cgc_printf("1) Display CountryInfo\n");
		cgc_printf("2) Set Capitol\n");
		cgc_printf("3) Set Population\n");
		cgc_printf("4) Add Language\n");
		cgc_printf("5) Add border\n");
		cgc_printf("6) Add Territory\n");
		cgc_printf("7) Select Territory\n");
		cgc_printf("8) Delete Country and Exit Menu\n");
		cgc_printf("9) Exit menu\n");

		cgc_bzero(selection, BSIZE);
		cgc_printf("Selection: ");
		cgc_receive_until( selection, '\n', 3);

		choice = cgc_atoi(selection);

		if ( choice < 1 || choice > 9 ) {
			cgc_printf("Invalid...\n");
			continue;
		}

		if ( choice == 1 ) {
			cgc_printCountryInfo( co );
		} else if (choice == 2 ) {
			cgc_printf("\n-> ");
			cgc_bzero(selection, BSIZE);

#ifdef PATCHED
			cgc_receive_until(selection, '\n', 19);
#else
			cgc_receive_until( selection, '\n', BSIZE-1);
#endif

			choice = 0;
			while ( cgc_isalpha( selection[choice]) ) {
				co->capitol[choice] = selection[choice];
				choice++;
			}
			co->capitol[choice] = '\x00';

		} else if ( choice == 3 ) {
			cgc_printf("\n-> ");
			cgc_bzero(selection, BSIZE);
			cgc_receive_until(selection, '\n', 19);

			co->population = cgc_atoi( selection );
		} else if ( choice == 4 ) {
			if ( co->language_count >= COUNTRYLANGUAGEMAX ) {
				cgc_printf("!!Max languages reached\n");
				continue;
			}

			cgc_printf("\n-> ");
			cgc_bzero(selection, BSIZE );
			cgc_receive(0, selection, 19, &length);

			if ( cgc_allocate( cgc_strlen(selection)+1, 0, (void**)&(t)) != 0 ) {
				t = NULL;
				continue;
			}

			cgc_bzero( t, cgc_strlen(selection)+1);

			choice = 0;
			while ( cgc_isalpha( selection[choice] ) ) {
				t[choice] = selection[choice];
				choice++;
			}
			t[choice] = '\x00';

			co->languages[ co->language_count ] = t;
			co->language_count++;
		} else if ( choice == 5 ) {
			if ( co->border_count >= COUNTRYBORDERMAX) {
				cgc_printf("!!Max borders reached\n");
				continue;
			}

			if ( cgc_allocate( sizeof(Border), 0, (void**)&pb) != 0 ) {
				pb = NULL;
				continue;
			}

			cgc_printf("Lat Start: ");
			cgc_bzero(selection, BSIZE );
			cgc_receive(0, selection, 19, &length);
			pb->latStart = cgc_atof(selection);

			cgc_printf("Long Start: ");
			cgc_bzero(selection, BSIZE );
			cgc_receive(0, selection, 19, &length);
			pb->lngStart = cgc_atof(selection);

			cgc_printf("Lat End: ");
			cgc_bzero(selection, BSIZE );
			cgc_receive(0, selection, 19, &length);
			pb->latEnd = cgc_atof(selection);

			cgc_printf("Long End: ");
			cgc_bzero(selection, BSIZE );
			cgc_receive(0, selection, 19, &length);
			pb->lngEnd = cgc_atof(selection);

			co->borders[ co->border_count ] = pb;
			co->border_count++;
		} else if ( choice == 6 ) {
			if ( co->territory_count >= COUNTRYTERRITORYMAX) {
				cgc_printf("!!Max Territories reached\n");
				continue;
			}

                        choice = 0;
                        while ( choice < COUNTRYTERRITORYMAX && co->territories[choice] != NULL ) {
                                choice++;
                        }

			if ( choice == COUNTRYTERRITORYMAX ) {
				cgc_printf("!!Max Territories reached\n");
				continue;
			}

                        if ( cgc_allocate( sizeof(Territory), 0, (void**)(&co->territories[ choice ]) ) != 0 ) {
                                cgc_printf("!!Failed to allocate structure\n");
                                co->territories[ choice ] = NULL;
                                continue;
                        }       
                        
                        cgc_initTerritory( co->territories[choice] );
                        
			cgc_printf("\nNew Territory: ");
			cgc_bzero(selection, BSIZE);
                        cgc_receive_until(selection, '\n', 19);

                        length = 0;
                        while ( cgc_isalnum( selection[length] ) ) {
                                co->territories[choice]->name[length] = selection[length];
                                length++;
                        }       
			co->territories[choice]->name[length] = '\x00';
			co->territory_count++;
                        
		} else if ( choice == 7 ) {

			cgc_printf("\nTerritories:\n");
			for ( choice = 0; choice < COUNTRYTERRITORYMAX; choice++ ) {
				if ( co->territories[choice] != NULL ) {
					cgc_printf("@d) @s\n", choice+1, co->territories[ choice ] );
				}
			}

			cgc_bzero(selection, BSIZE);
			cgc_printf("\n-> ");
			cgc_receive(0, selection, 3, &length);
			choice = cgc_atoi(selection);

			if ( choice < 1 || choice > COUNTRYTERRITORYMAX || co->territories[choice-1] == NULL ) {
				cgc_printf("Invalid choice...\n");
				continue;
			}

			if ( cgc_territoryMenu( co->territories[choice-1]) == 0 ) {
				co->territories[choice-1] = NULL ;
				co->territory_count--;
			}

		} else if ( choice == 8 ) {
			cgc_freeCountry(co);
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
void cgc_printCountryInfo( pCountry co )
{
	int index = 0;
	pBorder b = NULL;

	if ( co == NULL ) {
		return;
	}
	
	cgc_printf("\tCountry: ");

	if ( co->name[0] == '\x00' ) {
		cgc_printf("Unknown\n");
	} else {
		cgc_printf("@s\n", co->name);
	}

	cgc_printf("\t\tCapitol: ");
	if ( co->capitol[0] == '\x00' ) {
		cgc_printf("Unknown\n");
	} else {
		cgc_printf("@s\n", co->capitol);
	}

	if ( co->population >= 0 ) {
		cgc_printf("\t\tPopulation: @d\n", co->population);
	}

	while ( index < co->language_count ) {
		if ( co->languages[index] != NULL ) {
			cgc_printf("\t\tLanguage: @s\n", co->languages[index]);
		}
		index++;
	}

	index = 0;

	while ( index < co->border_count ) {
		b = co->borders[index];
		if ( b != NULL ) {
			cgc_printf("\t\tBorder: @f @f @f @f\n", b->latStart, b->lngStart, b->latEnd, b->lngEnd);
		}
		index++;
	}

	index = 0;

	while ( index < COUNTRYTERRITORYMAX ) {
		if ( co->territories[index] != NULL ) {
			cgc_printTerritoryInfo( co->territories[index] );
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
void cgc_freeCountry( pCountry co )
{
	int index = 0;

	if ( co == NULL ) {
		return;
	}

	while (index < co->border_count) {
		if ( co->borders[index] != NULL ) {
			cgc_deallocate( co->borders[index], sizeof( Border ) );
			co->borders[index] = NULL;
		}
		index++;
	}

	index = 0;
	while ( index < co->language_count) {
		if ( co->languages[index] != NULL ) {
			cgc_deallocate( co->languages[index], cgc_strlen(co->languages[index]) + 1 );
			co->languages[index] = NULL;
		}
		index++;
	}

	index = 0;
	while ( index < COUNTRYTERRITORYMAX) {
		if ( co->territories[index] != NULL ) {
			cgc_freeTerritory( co->territories[index] );
			co->territories[index] = NULL;
		}
		index++;
	}

	cgc_deallocate( co, sizeof(Country) );

	return;
}

/**
 * Initialize the values of a country structure
 * @param co Pointer to a country structure to initialize
 * @return Returns nothing
 **/
void cgc_initCountry( pCountry co )
{
	int index = 0;

	if ( co == NULL ) {
		return;
	}

	cgc_bzero( co->name, 20 );

	co->population = -1;
	co->language_count = 0;

	co->border_count = 0;

	cgc_bzero( co->languages, sizeof(char*) * COUNTRYLANGUAGEMAX);
	cgc_bzero( co->borders, sizeof(pBorder) * COUNTRYBORDERMAX);
	cgc_bzero( co->territories, sizeof(pTerritory) * COUNTRYTERRITORYMAX);

	return;
}

/**
 * This function handles the top level parsing of country elements
 * @param str Pointer to a string structure
 * @return Returns a pointer to a country structure or NULL on failure
 **/
pCountry cgc_countryTopLevel( pstring str )
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
	if ( cgc_allocate(sizeof(Country), 0, (void**)&newCountry) != 0 ) {
		newCountry = NULL;
		goto end;
	}

	cgc_initCountry( newCountry );

	cgc_skipWhiteSpace(str);

	lastGood = cgc_getIndex( str, &lastGood );

	if ( !cgc_atChar( str, '{' ) ) {
		goto error;
	}

	if ( cgc_skipLength( str, 1 ) < 0 ) {
		goto error;
	}

	cgc_skipWhiteSpace(str);

	startIndex = str->index;

	endIndex = cgc_skipAlpha( str );

	if ( endIndex == -1 || startIndex == endIndex ) {
		goto error;
	}
	
	/// Confirm the opening element;		
	temp_name = cgc_copyData( str, startIndex, endIndex );

	if ( temp_name == NULL ) {
		goto error;
	}

	if ( cgc_strcmp( temp_name, "Country" ) != 0 ) {
		cgc_printf("!!Country: Invalid opening element id\n");
		cgc_deallocate( temp_name, cgc_strlen(temp_name) + 1 );
		goto error;
	}

	cgc_deallocate(temp_name, cgc_strlen(temp_name) + 1 );

	cgc_skipWhiteSpace(str);

	if ( str->buffer[ str->index ] != '}' ) {
		goto error;
	}

	cgc_incChar( str );

	lastGood = str->index;

	temp_name = cgc_pullNextElementName( str );

	while ( temp_name != NULL ) {
		el = cgc_elementNameToEnum( temp_name );

		cgc_deallocate( temp_name, cgc_strlen(temp_name) + 1 );

		switch (el) {
			case name:
				temp_name = cgc_extractName( str );

				if ( temp_name == NULL ) {
					goto error;
				}

				cgc_bzero( newCountry->name, 20);
				cgc_strncpy( newCountry->name, temp_name, 19 );

				cgc_deallocate( temp_name, cgc_strlen(temp_name)+1);
				temp_name = NULL;
				break;
			case capitol:

				temp_name = cgc_extractCapitol( str );

				if ( !temp_name ) {
					goto error;
				}

				cgc_bzero( newCountry->capitol, 20 );
				cgc_strncpy( newCountry->capitol, temp_name, 19 );

				cgc_deallocate( temp_name, cgc_strlen(temp_name)+1);
				temp_name = NULL;
				break;
			case population:
				newCountry->population = cgc_extractPopulation(str);

				if (newCountry->population < 0 ) {
					goto error;
				}

				break;
			case language:

				if ( newCountry->language_count >= COUNTRYLANGUAGEMAX ) {
					cgc_printf("!!Max country language count is @d\n", COUNTRYLANGUAGEMAX);
					goto error;
				}

				newCountry->languages[newCountry->language_count] = cgc_extractLanguage(str);

				if ( newCountry->languages[ newCountry->language_count] == NULL ) {
					goto error;
				}

				newCountry->language_count++;

				break;
			case border:
				if ( newCountry->border_count >= COUNTRYBORDERMAX ) {
					cgc_printf("!!Max country border count is @d\n", COUNTRYBORDERMAX);
					goto error;
				}

				newCountry->borders[newCountry->border_count] = cgc_extractBorder(str);

				if ( newCountry->borders[ newCountry->border_count] == NULL ) {
					goto error;
				}

				newCountry->border_count++;

				break;
			case territory:
				if ( newCountry->territory_count >= COUNTRYTERRITORYMAX) {
					cgc_printf("!!Max territories is @d\n", COUNTRYTERRITORYMAX);
					goto error;
				}

				newCountry->territories[newCountry->territory_count] = cgc_territoryTopLevel(str);

				if (newCountry->territories[newCountry->territory_count] == NULL ) {
					goto error;
				}
	
				newCountry->territory_count++;

				break;
			default:
				cgc_printf("Invalid for country\n");
				goto error;
				break;
		};

		lastGood = str->index;

		temp_name = cgc_pullNextElementName( str );
	}

	cgc_skipWhiteSpace( str );

	if ( !cgc_atChar( str, '{' ) ) {
		goto error;
	}

	if ( cgc_skipLength( str, 1 ) < 0 ) {
		goto error;
	}

	cgc_skipWhiteSpace( str );

	if ( !cgc_atChar( str, '#' ) ) {
		goto error;
	}

	if ( cgc_skipLength( str, 1 ) < 0 ) {
		goto error;
	}

	startIndex = str->index;

	endIndex = cgc_skipAlpha( str );

	if ( endIndex < 0 ) {
		goto error;
	}

	if ( startIndex == endIndex ) {
		goto error;
	}

	temp_name = cgc_copyData( str, startIndex, endIndex );

	if ( temp_name == NULL ) {
		goto error;
	}

	if ( cgc_strcmp( temp_name, "Country" ) != 0 ) {
		cgc_deallocate(temp_name, cgc_strlen(temp_name) + 1 );
		goto error;
	}

	cgc_deallocate( temp_name, cgc_strlen(temp_name) + 1 );

	cgc_skipWhiteSpace(str);

	if ( !cgc_atChar( str, '}' ) ) {
		goto error;
	}

	cgc_incChar( str );

	goto end;
error:
	if (newCountry != NULL ) {
		cgc_freeCountry( newCountry );
		newCountry = NULL;
	}

	str->index = lastGood;

	cgc_printf("Error at: @s\n", str->buffer + str->index);

end:
	return newCountry;
}

/**
 * Parse the Language element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the language character string or NULL on failure
 **/
char* cgc_extractLanguage( pstring str )
{
	char *temp = NULL;
	char *language = NULL;
	register int start = 0;
	register int end = 0;

	if (str == NULL ) {
		return NULL;
	}

	start = cgc_skipWhiteSpace(str);

	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate opening brace\n");
		return language;
	}

	/// Skip past the curly brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip opening brace\n");
		return language;
	}

	/// Skip any additional whitespace
	start = cgc_skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the element id\n");
		return language;
	}

	/// Copy the element id from the string
	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		cgc_printf("!!Copy from @d to @d failed\n", start, end);
		return NULL;
	}

	/// If the element id is not "Language" then this is the wrong function
	if ( cgc_strcmp( temp, "Language") != 0 ) {
		cgc_printf("!!Element id is not \"Language\"\n");
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
		temp = NULL;
		return language;
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
		return language;
	}

	start = cgc_skipWhiteSpace( str );
	end = cgc_skipAlpha( str );

	if ( start == end ) {
		cgc_printf("!!Failed to find language data\n");
		return language;
	}

	/// Copy the language element data
	language = cgc_copyData( str, start, end );

	if ( language == NULL ) {
		cgc_printf("!!Failed to copy language data\n");
		return language;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	cgc_skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate the final opening brace\n");
		goto error;
	}

	/// Skip past the brace
	if ( cgc_incChar( str) == -1 ) {
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

	end = cgc_skipToNonAlphaNum( str );

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

	if ( cgc_strcmp( temp, "Language") != 0 ) {
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
		

	goto end;

error:
	if (language != NULL) {
		cgc_deallocate( language, cgc_strlen(language) + 1 );
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
char* cgc_extractCapitol( pstring str )
{
	char *temp = NULL;
	char *capitol = NULL;
	int start = 0;
	int end = 0;

	if (str == NULL ) {
		return NULL;
	}

	cgc_skipWhiteSpace(str);

	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate opening brace\n");
		return capitol;
	}

	/// Skip past the curly brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip opening brace\n");
		return NULL;
	}

	/// Skip any additional whitespace
	start = cgc_skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		return NULL;
	}

	/// Copy the element id from the string
	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		return NULL;
	}

	/// If the element id is not "Capitol" then this is the wrong function
	if ( cgc_strcmp( temp, "Capitol") != 0 ) {
		cgc_deallocate( temp, (end-start) + 1 );
		temp = NULL;
		return temp;
	}

	/// The buffer is no longer needed so free it
	cgc_deallocate(temp, (end-start) + 1);

	/// Skip to the end of the element id
	cgc_skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !cgc_atChar( str, '}' ) ) {
		return NULL;
	}

	/// Skip the closing brace as well as any whitespace
	if ( cgc_incChar( str ) == -1 ) {
		return NULL;
	}

	cgc_skipWhiteSpace( str );
	cgc_getIndex( str, &start );

	end = cgc_skipAlpha( str );

	if ( !(start ^ end) ) {
		return NULL;
	}

	/// Copy the capitol element data
	capitol = cgc_copyData( str, start, end );

	if ( capitol == NULL ) {
		return NULL;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	cgc_skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate the final opening brace\n");
		goto error;
	}

	/// Skip past the brace
	if ( cgc_incChar( str) == -1 ) {
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

	end = cgc_skipToNonAlphaNum( str );

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

	if ( cgc_strcmp( temp, "Capitol") != 0 ) {
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
		

	goto end;

error:
	if (capitol != NULL) {
		cgc_deallocate( capitol, cgc_strlen(capitol) + 1 );
		capitol = NULL;
	}

end:
	return capitol;
}

