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

#include "territoryParsers.h"

int territoryMenu( pTerritory ty )
{
	int choice = 0;
	size_t length = 0;
	char selection[30];
	char *temp = NULL;
	pBorder pb = NULL;
	pCounty pc = NULL;

	if ( ty == NULL ) {
		return 0;
	}

	while( 1 ) {
		printf("\nTerritory: @s\n", ty->name);
		printf("1) Display Territory Info\n");
		printf("2) Set Founder\n");
		printf("3) Set Population\n");
		printf("4) Set Established\n");
		printf("5) Add Border\n");
		printf("6) Add County\n");
		printf("7) Select County\n");
		printf("8) Delete County and Exit Menu\n");
		printf("9) Exit Menu\n");

		bzero( selection, 4 );
		printf("Selection: ");
		receive_until( selection, '\n', 3);

		choice = atoi( selection );

		bzero(selection, 30);

		switch (choice) {
			case 1:
				printTerritoryInfo( ty );
				break;
			case 2:
				printf("\n-> ");
				receive_until( selection, '\n', 29);

				/// Copy as long as the data is alpha numeric
				choice = 0;
				while ( isalnum( selection[choice] ) || selection[choice] == ' ' ) {
					ty->founder[choice] = selection[choice];
					choice++;
				}
				ty->founder[choice] = '\x00';

				break;
			case 3:
				printf("\n-> ");
				receive_until( selection, '\n', 29);

				ty->population = atoi(selection);
				break;
			case 4:
				printf("\n-> ");
				receive_until( selection, '\n', 29);

				ty->established = atoi( selection );
				break;
			case 5:
                        	if ( ty->border_count >= TERRITORYBORDERMAX) {
                                	printf("!!Max borders reached\n");
                                	continue;
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

                    	    	ty->borders[ ty->border_count ] = pb;
                        	ty->border_count++;
				break;
			case 6:
				choice = 0;

				/// Select the first open location
				while ( choice < TERRITORYCOUNTYMAX ) {
					if ( ty->counties[choice] == NULL ) {
						break;
					}
					choice++;
				}

				if ( choice == TERRITORYCOUNTYMAX ) {
					printf("!!Max counties reached\n");
					continue;
				}

				printf("\nNew County Name: ");
				receive_until( selection, '\n', 19 );
		
				if ( allocate( sizeof(County), 0, (void**)&pc) != 0 ) {
					pc = NULL;
					continue;
				}

				initCounty( pc );

				ty->counties[choice] = pc;
	
				choice = 0;
				while ( isalnum( selection[choice]) ) {
					pc->name[choice] = selection[choice];
					choice++;
				}

				pc->name[choice] = '\x00';
				ty->county_count++;
				break;
			case 7:
				for ( choice = 0; choice < TERRITORYCOUNTYMAX; choice++) {
					if ( ty->counties[choice] != NULL ) {
						printf("@d) @s\n", choice+1, ty->counties[choice]->name);
					}
				}

				printf("\n-> ");
				receive_until( selection, '\n', 19);
				choice = atoi( selection );

				if ( choice < 1 || choice > TERRITORYCOUNTYMAX ) {
					printf("Invalid choice...\n");
					continue;
				}

				if ( ty->counties[choice-1] == NULL ) {
					printf("Invalid choice...\n");
					continue;
				}

				if ( countyMenu(ty->counties[choice-1]) == 0 ) {
					ty->counties[choice-1] = NULL;
					ty->county_count--;
				}
				break;
			case 8:
				freeTerritory(ty);
				return 0;
				break;
			case 9:
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
 * Print the territory information from the structure
 * @param ty Pointer to the territory structure
 * @return Returns nothing
 */
void printTerritoryInfo( pTerritory ty )
{
	int index = 0;
	pBorder b = NULL;

	if ( ty == NULL ) {
		return;
	}
	
	printf("\t\tTerritory: ");

	if ( ty->name[0] == '\x00' ) {
		printf("Unknown\n");
	} else {
		printf("@s\n", ty->name);
	}

	if ( ty->population >= 0 ) {
		printf("\t\t\tPopulation: @d\n", ty->population);
	}

	printf("\t\t\tEstablished: @d\n", ty->established);
	
	printf("\t\t\tFounder: ");
	if ( ty->founder[0] == '\x00' ) {
		printf("Unknown\n");
	} else {
		printf("@s\n", ty->founder);
	}

	index = 0;

	while ( index < ty->border_count ) {
		b = ty->borders[index];
		if ( b != NULL ) {
			printf("\t\t\tBorder: @f @f @f @f\n", b->latStart, b->lngStart, b->latEnd, b->lngEnd);
		}
		index++;
	}

	index = 0;

	for ( index = 0; index < TERRITORYCOUNTYMAX; index++ ) {
		if ( ty->counties[index] != NULL ) {
			printCountyInfo( ty->counties[index]);
		}
	}

	return;	
}

/**
 * Frees a Territory structure
 * @param ty Pointer to a territory structure to free
 * @return Returns nothing
 **/
void freeTerritory( pTerritory ty )
{
	int index = 0;

	if ( ty == NULL ) {
		return;
	}

	while (index < ty->border_count) {
		if ( ty->borders[index] != NULL ) {
			deallocate( ty->borders[index], sizeof( Border ) );
			ty->borders[index] = NULL;
		}
		index++;
	}

	for ( index = 0; index < ty->county_count; index++ ) {
		freeCounty( ty->counties[index]);
		ty->counties[index] = NULL;
	}

	deallocate( ty, sizeof(Territory) );

	return;
}

/**
 * Initialize the values of a territory structure
 * @param ty Pointer to a territory structure to initialize
 * @return Returns nothing
 **/
void initTerritory( pTerritory ty )
{
	int index = 0;

	if ( ty == NULL ) {
		return;
	}

	bzero( ty->name, 20 );
	bzero( ty->founder, 30);

	ty->population = -1;
	ty->county_count = 0;

	ty->border_count = 0;

	bzero( ty->borders, sizeof(pBorder) * TERRITORYBORDERMAX);
	bzero( ty->counties, sizeof(pCounty) * TERRITORYCOUNTYMAX);

	return;
}

/**
 * This function handles the top level parsing of territory elements
 * @param str Pointer to a string structure
 * @return Returns a pointer to a territory structure or NULL on failure
 **/
pTerritory territoryTopLevel( pstring str )
{
	pTerritory newTerritory = NULL;
	char * temp_name = NULL;
	int lastGood = 0;
	int startIndex = 0;
	int endIndex = 0;
	element el = 0;

	if ( str == NULL ) {
		goto end;
	}

	/// Allocate a new territory structure
	if ( allocate(sizeof(Territory), 0, (void**)&newTerritory) != 0 ) {
		newTerritory = NULL;
		goto end;
	}

	initTerritory( newTerritory );

	skipWhiteSpace(str);

	lastGood = getIndex( str, &lastGood );

	if ( !atChar( str, '{' ) ) {
		goto error;
	}

	if ( incChar( str ) < 0 ) {
		goto error;
	}

	skipWhiteSpace(str);

	getIndex( str, &startIndex );

	endIndex = skipAlpha( str );

	if ( endIndex == -1 || startIndex == endIndex ) {
		goto error;
	}
	
	/// Confirm the opening element;		
	temp_name = copyData( str, startIndex, endIndex );

	if ( temp_name == NULL ) {
		goto error;
	}

	if ( strcmp( temp_name, "Territory" ) != 0 ) {
		printf("!!Territory: Invalid opening element id\n");
		deallocate( temp_name, strlen(temp_name) + 1 );
		goto error;
	}

	deallocate(temp_name, strlen(temp_name) + 1 );

	skipWhiteSpace(str);

	if ( !atChar( str, '}') ) {
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

				bzero( newTerritory->name, 20 );
				strncpy( newTerritory->name, temp_name, 19 );

				deallocate( temp_name, strlen(temp_name)+1);
				temp_name = NULL;
				break;
			case founder:
				temp_name = extractFounder(str);

				if ( !temp_name ) {
					goto error;
				}

				bzero( newTerritory->founder, 30 );
				strncpy( newTerritory->founder, temp_name, 29 );

				deallocate(temp_name, strlen(temp_name)+1);
				temp_name = NULL;
				break;
			case population:
				newTerritory->population = extractPopulation(str);

				if (newTerritory->population < 0 ) {
					goto error;
				}

				break;
			case established:
				newTerritory->established = extractEstablished( str );

				break;
			case border:
				if ( newTerritory->border_count >= TERRITORYBORDERMAX ) {
					printf("!!Max territory border count is @d\n", TERRITORYBORDERMAX);
					goto error;
				}

				newTerritory->borders[newTerritory->border_count] = extractBorder(str);

				if ( newTerritory->borders[ newTerritory->border_count] == NULL ) {
					goto error;
				}

				newTerritory->border_count++;

				break;
			case county:
				if ( newTerritory->county_count >= TERRITORYCOUNTYMAX ) {
					printf("!!Max territory county count is @d\n", TERRITORYCOUNTYMAX);
					goto error;
				}
	
				newTerritory->counties[newTerritory->county_count] = countyTopLevel( str );

				if ( newTerritory->counties[ newTerritory->county_count] == NULL ) {
					goto error;
				}

				newTerritory->county_count++;

				break;
			default:
				printf("Invalid for territory\n");
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

	if ( strcmp( temp_name, "Territory" ) != 0 ) {
		deallocate(temp_name, strlen(temp_name) + 1 );
		goto error;
	}

	deallocate( temp_name, strlen(temp_name) + 1 );

	skipWhiteSpace( str );

	if ( !atChar( str, '}' ) ) {
		goto error;
	}

	incChar( str );

	goto end;
error:
	if ( newTerritory ) {
		freeTerritory( newTerritory );
		newTerritory = NULL;
	}

	str->index = lastGood;

	printf("Error at: @s\n", str->buffer + str->index);

end:
	return newTerritory;
}

/**
 * Parse the Founder element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the Founder string or NULL on failure
 **/
char* extractFounder( pstring str )
{
	char *temp = NULL;
	char *founder = NULL;
	register int start = 0;
	register int end = 0;

	if (str == NULL ) {
		return NULL;
	}

	start = skipWhiteSpace(str);

	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate opening brace\n");
		return NULL;
	}

	/// Skip past the curly brace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip opening brace\n");
		return NULL;
	}

	/// Skip any additional whitespace
	start = skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = skipAlpha( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the element id\n");
		return NULL;
	}

	/// Copy the element id from the string
	temp = copyData( str, start, end );

	if ( temp == NULL ) {
		printf("!!Copy from @d to @d failed\n", start, end);
		return NULL;
	}

	if ( strcmp( temp, "Founder") != 0 ) {
		deallocate( temp, strlen(temp) + 1 );
		return NULL;
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
		return NULL;
	}

	start = skipWhiteSpace( str );
	end = skipToNonAlphaNumSpace( str );

	if ( start == end ) {
		return NULL;
	}
	
	/// Do not copy trailing whitespace
	while( isspace( str->buffer[end-1] ) ) {
		end--;
	}

	founder = copyData( str, start, end );

	if ( founder == NULL ) {
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

	end = skipAlpha( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the closing element id\n");
		goto error;
	}
	
	temp = copyData( str, start, end );

	if ( strcmp( temp, "Founder") != 0 ) {
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
	if (founder != NULL) {
		deallocate( founder, strlen(founder) + 1 );
		founder = NULL;
	}

end:
	return founder;
}

/**
 * Parse the Established element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the date established. It can be negative
 **/
int extractEstablished( pstring str )
{
	char *temp = NULL;
	int established = 0;
	int start = 0;
	int end = 0;

	/// These will be used specifically for the data
	int es = 0;
	int ee = 0;

	if (str == NULL ) {
		goto error;
	}

	start = skipWhiteSpace(str);

	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate opening brace\n");
		return established;
	}

	/// Skip past the curly brace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip opening brace\n");
		return established;
	}

	/// Skip any additional whitespace
	start = skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = skipAlpha( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the element id\n");
		return established;
	}

	/// Copy the element id from the string
	temp = copyData( str, start, end );

	if ( temp == NULL ) {
		printf("!!Copy from @d to @d failed\n", start, end);
		goto error;
	}

	/// If the element id is not "Established" then this is the wrong function
	if ( strcmp( temp, "Established") != 0 ) {
		printf("!!Element id is not \"Established\"\n");
		deallocate( temp, strlen(temp) + 1 );
		temp = NULL;
		return established;
	}

	/// The buffer is no longer needed so free it
	deallocate(temp, strlen(temp) + 1);

	/// Skip to the end of the element id
	skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate initial closing brace\n");
		goto error;
	}

	/// Skip the closing brace as well as any whitespace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip initial closing brace\n");
		return established;
	}

	skipWhiteSpace( str );

	/// Copy the start index to store the data
	getIndex( str, &es );

	/// The established data must be an integer
	ee = skipInt( str );

	if ( ee == -1 ) {
		printf("!!Failed to locate the end of the established data\n");
		return established;
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
		return established;
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
		return established;
	}

	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the closing element id\n");
		goto error;
	}
	
	temp = copyData( str, start, end );

	if ( strcmp( temp, "Established") != 0 ) {
		deallocate(temp, strlen(temp)+1);
		return established;
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
		
	/// Copy the established element data
	temp = copyData( str, es, ee );

	if ( temp == NULL ) {
		printf("!!Failed to copy established data\n");
		goto error;
	}

	established = atoi( temp );

	deallocate( temp, strlen(temp) + 1 );

	return established;

error:
	return 0;
}

