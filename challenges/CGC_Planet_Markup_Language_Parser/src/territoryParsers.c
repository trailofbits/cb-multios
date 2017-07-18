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

#include "cgc_territoryParsers.h"

int cgc_territoryMenu( pTerritory ty )
{
	int choice = 0;
	cgc_size_t length = 0;
	char selection[30];
	char *temp = NULL;
	pBorder pb = NULL;
	pCounty pc = NULL;

	if ( ty == NULL ) {
		return 0;
	}

	while( 1 ) {
		cgc_printf("\nTerritory: @s\n", ty->name);
		cgc_printf("1) Display Territory Info\n");
		cgc_printf("2) Set Founder\n");
		cgc_printf("3) Set Population\n");
		cgc_printf("4) Set Established\n");
		cgc_printf("5) Add Border\n");
		cgc_printf("6) Add County\n");
		cgc_printf("7) Select County\n");
		cgc_printf("8) Delete County and Exit Menu\n");
		cgc_printf("9) Exit Menu\n");

		cgc_bzero( selection, 4 );
		cgc_printf("Selection: ");
		cgc_receive_until( selection, '\n', 3);

		choice = cgc_atoi( selection );

		cgc_bzero(selection, 30);

		switch (choice) {
			case 1:
				cgc_printTerritoryInfo( ty );
				break;
			case 2:
				cgc_printf("\n-> ");
				cgc_receive_until( selection, '\n', 29);

				/// Copy as long as the data is alpha numeric
				choice = 0;
				while ( cgc_isalnum( selection[choice] ) || selection[choice] == ' ' ) {
					ty->founder[choice] = selection[choice];
					choice++;
				}
				ty->founder[choice] = '\x00';

				break;
			case 3:
				cgc_printf("\n-> ");
				cgc_receive_until( selection, '\n', 29);

				ty->population = cgc_atoi(selection);
				break;
			case 4:
				cgc_printf("\n-> ");
				cgc_receive_until( selection, '\n', 29);

				ty->established = cgc_atoi( selection );
				break;
			case 5:
                        	if ( ty->border_count >= TERRITORYBORDERMAX) {
                                	cgc_printf("!!Max borders reached\n");
                                	continue;
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
					cgc_printf("!!Max counties reached\n");
					continue;
				}

				cgc_printf("\nNew County Name: ");
				cgc_receive_until( selection, '\n', 19 );
		
				if ( cgc_allocate( sizeof(County), 0, (void**)&pc) != 0 ) {
					pc = NULL;
					continue;
				}

				cgc_initCounty( pc );

				ty->counties[choice] = pc;
	
				choice = 0;
				while ( cgc_isalnum( selection[choice]) ) {
					pc->name[choice] = selection[choice];
					choice++;
				}

				pc->name[choice] = '\x00';
				ty->county_count++;
				break;
			case 7:
				for ( choice = 0; choice < TERRITORYCOUNTYMAX; choice++) {
					if ( ty->counties[choice] != NULL ) {
						cgc_printf("@d) @s\n", choice+1, ty->counties[choice]->name);
					}
				}

				cgc_printf("\n-> ");
				cgc_receive_until( selection, '\n', 19);
				choice = cgc_atoi( selection );

				if ( choice < 1 || choice > TERRITORYCOUNTYMAX ) {
					cgc_printf("Invalid choice...\n");
					continue;
				}

				if ( ty->counties[choice-1] == NULL ) {
					cgc_printf("Invalid choice...\n");
					continue;
				}

				if ( cgc_countyMenu(ty->counties[choice-1]) == 0 ) {
					ty->counties[choice-1] = NULL;
					ty->county_count--;
				}
				break;
			case 8:
				cgc_freeTerritory(ty);
				return 0;
				break;
			case 9:
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
 * Print the territory information from the structure
 * @param ty Pointer to the territory structure
 * @return Returns nothing
 */
void cgc_printTerritoryInfo( pTerritory ty )
{
	int index = 0;
	pBorder b = NULL;

	if ( ty == NULL ) {
		return;
	}
	
	cgc_printf("\t\tTerritory: ");

	if ( ty->name[0] == '\x00' ) {
		cgc_printf("Unknown\n");
	} else {
		cgc_printf("@s\n", ty->name);
	}

	if ( ty->population >= 0 ) {
		cgc_printf("\t\t\tPopulation: @d\n", ty->population);
	}

	cgc_printf("\t\t\tEstablished: @d\n", ty->established);
	
	cgc_printf("\t\t\tFounder: ");
	if ( ty->founder[0] == '\x00' ) {
		cgc_printf("Unknown\n");
	} else {
		cgc_printf("@s\n", ty->founder);
	}

	index = 0;

	while ( index < ty->border_count ) {
		b = ty->borders[index];
		if ( b != NULL ) {
			cgc_printf("\t\t\tBorder: @f @f @f @f\n", b->latStart, b->lngStart, b->latEnd, b->lngEnd);
		}
		index++;
	}

	index = 0;

	for ( index = 0; index < TERRITORYCOUNTYMAX; index++ ) {
		if ( ty->counties[index] != NULL ) {
			cgc_printCountyInfo( ty->counties[index]);
		}
	}

	return;	
}

/**
 * Frees a Territory structure
 * @param ty Pointer to a territory structure to free
 * @return Returns nothing
 **/
void cgc_freeTerritory( pTerritory ty )
{
	int index = 0;

	if ( ty == NULL ) {
		return;
	}

	while (index < ty->border_count) {
		if ( ty->borders[index] != NULL ) {
			cgc_deallocate( ty->borders[index], sizeof( Border ) );
			ty->borders[index] = NULL;
		}
		index++;
	}

	for ( index = 0; index < ty->county_count; index++ ) {
		cgc_freeCounty( ty->counties[index]);
		ty->counties[index] = NULL;
	}

	cgc_deallocate( ty, sizeof(Territory) );

	return;
}

/**
 * Initialize the values of a territory structure
 * @param ty Pointer to a territory structure to initialize
 * @return Returns nothing
 **/
void cgc_initTerritory( pTerritory ty )
{
	int index = 0;

	if ( ty == NULL ) {
		return;
	}

	cgc_bzero( ty->name, 20 );
	cgc_bzero( ty->founder, 30);

	ty->population = -1;
	ty->county_count = 0;

	ty->border_count = 0;

	cgc_bzero( ty->borders, sizeof(pBorder) * TERRITORYBORDERMAX);
	cgc_bzero( ty->counties, sizeof(pCounty) * TERRITORYCOUNTYMAX);

	return;
}

/**
 * This function handles the top level parsing of territory elements
 * @param str Pointer to a string structure
 * @return Returns a pointer to a territory structure or NULL on failure
 **/
pTerritory cgc_territoryTopLevel( pstring str )
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
	if ( cgc_allocate(sizeof(Territory), 0, (void**)&newTerritory) != 0 ) {
		newTerritory = NULL;
		goto end;
	}

	cgc_initTerritory( newTerritory );

	cgc_skipWhiteSpace(str);

	lastGood = cgc_getIndex( str, &lastGood );

	if ( !cgc_atChar( str, '{' ) ) {
		goto error;
	}

	if ( cgc_incChar( str ) < 0 ) {
		goto error;
	}

	cgc_skipWhiteSpace(str);

	cgc_getIndex( str, &startIndex );

	endIndex = cgc_skipAlpha( str );

	if ( endIndex == -1 || startIndex == endIndex ) {
		goto error;
	}
	
	/// Confirm the opening element;		
	temp_name = cgc_copyData( str, startIndex, endIndex );

	if ( temp_name == NULL ) {
		goto error;
	}

	if ( cgc_strcmp( temp_name, "Territory" ) != 0 ) {
		cgc_printf("!!Territory: Invalid opening element id\n");
		cgc_deallocate( temp_name, cgc_strlen(temp_name) + 1 );
		goto error;
	}

	cgc_deallocate(temp_name, cgc_strlen(temp_name) + 1 );

	cgc_skipWhiteSpace(str);

	if ( !cgc_atChar( str, '}') ) {
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

				cgc_bzero( newTerritory->name, 20 );
				cgc_strncpy( newTerritory->name, temp_name, 19 );

				cgc_deallocate( temp_name, cgc_strlen(temp_name)+1);
				temp_name = NULL;
				break;
			case founder:
				temp_name = cgc_extractFounder(str);

				if ( !temp_name ) {
					goto error;
				}

				cgc_bzero( newTerritory->founder, 30 );
				cgc_strncpy( newTerritory->founder, temp_name, 29 );

				cgc_deallocate(temp_name, cgc_strlen(temp_name)+1);
				temp_name = NULL;
				break;
			case population:
				newTerritory->population = cgc_extractPopulation(str);

				if (newTerritory->population < 0 ) {
					goto error;
				}

				break;
			case established:
				newTerritory->established = cgc_extractEstablished( str );

				break;
			case border:
				if ( newTerritory->border_count >= TERRITORYBORDERMAX ) {
					cgc_printf("!!Max territory border count is @d\n", TERRITORYBORDERMAX);
					goto error;
				}

				newTerritory->borders[newTerritory->border_count] = cgc_extractBorder(str);

				if ( newTerritory->borders[ newTerritory->border_count] == NULL ) {
					goto error;
				}

				newTerritory->border_count++;

				break;
			case county:
				if ( newTerritory->county_count >= TERRITORYCOUNTYMAX ) {
					cgc_printf("!!Max territory county count is @d\n", TERRITORYCOUNTYMAX);
					goto error;
				}
	
				newTerritory->counties[newTerritory->county_count] = cgc_countyTopLevel( str );

				if ( newTerritory->counties[ newTerritory->county_count] == NULL ) {
					goto error;
				}

				newTerritory->county_count++;

				break;
			default:
				cgc_printf("Invalid for territory\n");
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

	if ( cgc_strcmp( temp_name, "Territory" ) != 0 ) {
		cgc_deallocate(temp_name, cgc_strlen(temp_name) + 1 );
		goto error;
	}

	cgc_deallocate( temp_name, cgc_strlen(temp_name) + 1 );

	cgc_skipWhiteSpace( str );

	if ( !cgc_atChar( str, '}' ) ) {
		goto error;
	}

	cgc_incChar( str );

	goto end;
error:
	if ( newTerritory ) {
		cgc_freeTerritory( newTerritory );
		newTerritory = NULL;
	}

	str->index = lastGood;

	cgc_printf("Error at: @s\n", str->buffer + str->index);

end:
	return newTerritory;
}

/**
 * Parse the Founder element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the Founder string or NULL on failure
 **/
char* cgc_extractFounder( pstring str )
{
	char *temp = NULL;
	char *founder = NULL;
	register int start = 0;
	register int end = 0;

	if (str == NULL ) {
		return NULL;
	}

	start = cgc_skipWhiteSpace(str);

	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate opening brace\n");
		return NULL;
	}

	/// Skip past the curly brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip opening brace\n");
		return NULL;
	}

	/// Skip any additional whitespace
	start = cgc_skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = cgc_skipAlpha( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the element id\n");
		return NULL;
	}

	/// Copy the element id from the string
	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		cgc_printf("!!Copy from @d to @d failed\n", start, end);
		return NULL;
	}

	if ( cgc_strcmp( temp, "Founder") != 0 ) {
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
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

	start = cgc_skipWhiteSpace( str );
	end = cgc_skipToNonAlphaNumSpace( str );

	if ( start == end ) {
		return NULL;
	}
	
	/// Do not copy trailing whitespace
	while( cgc_isspace( str->buffer[end-1] ) ) {
		end--;
	}

	founder = cgc_copyData( str, start, end );

	if ( founder == NULL ) {
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

	end = cgc_skipAlpha( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the closing element id\n");
		goto error;
	}
	
	temp = cgc_copyData( str, start, end );

	if ( cgc_strcmp( temp, "Founder") != 0 ) {
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
	if (founder != NULL) {
		cgc_deallocate( founder, cgc_strlen(founder) + 1 );
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
int cgc_extractEstablished( pstring str )
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

	start = cgc_skipWhiteSpace(str);

	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate opening brace\n");
		return established;
	}

	/// Skip past the curly brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip opening brace\n");
		return established;
	}

	/// Skip any additional whitespace
	start = cgc_skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = cgc_skipAlpha( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the element id\n");
		return established;
	}

	/// Copy the element id from the string
	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		cgc_printf("!!Copy from @d to @d failed\n", start, end);
		goto error;
	}

	/// If the element id is not "Established" then this is the wrong function
	if ( cgc_strcmp( temp, "Established") != 0 ) {
		cgc_printf("!!Element id is not \"Established\"\n");
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
		temp = NULL;
		return established;
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
		return established;
	}

	cgc_skipWhiteSpace( str );

	/// Copy the start index to store the data
	cgc_getIndex( str, &es );

	/// The established data must be an integer
	ee = cgc_skipInt( str );

	if ( ee == -1 ) {
		cgc_printf("!!Failed to locate the end of the established data\n");
		return established;
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
		return established;
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
		return established;
	}

	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the closing element id\n");
		goto error;
	}
	
	temp = cgc_copyData( str, start, end );

	if ( cgc_strcmp( temp, "Established") != 0 ) {
		cgc_deallocate(temp, cgc_strlen(temp)+1);
		return established;
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
		
	/// Copy the established element data
	temp = cgc_copyData( str, es, ee );

	if ( temp == NULL ) {
		cgc_printf("!!Failed to copy established data\n");
		goto error;
	}

	established = cgc_atoi( temp );

	cgc_deallocate( temp, cgc_strlen(temp) + 1 );

	return established;

error:
	return 0;
}

