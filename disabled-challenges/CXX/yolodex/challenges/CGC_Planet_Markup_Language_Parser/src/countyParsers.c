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

#include "cgc_countyParsers.h"

int cgc_countyMenu( pCounty co )
{
	int choice = 0;
	char selection[30];
	pBorder pb = NULL;
	pCity pc = NULL;

	if ( co == NULL ) {
		return 0;
	}

	while ( 1 ) {
		cgc_printf("County: @s\n", co->name );
		cgc_printf("1) Display County Info\n");
		cgc_printf("2) Set Seat\n");
		cgc_printf("3) Set Population\n");
		cgc_printf("4) Set Area\n");
		cgc_printf("5) Set Density\n");
		cgc_printf("6) Add Border\n");
		cgc_printf("7) Add City\n");
		cgc_printf("8) Select City\n");
		cgc_printf("9) Delete County and Exit Menu\n");
		cgc_printf("10) Exit Menu\n");
		cgc_printf("Selection: ");

		cgc_bzero(selection, 4 );
		cgc_receive_until( selection, '\n', 3);

		choice = cgc_atoi( selection );
		cgc_bzero( selection, 30 );

		switch( choice ) {
			case 1:
				cgc_printCountyInfo( co );
				break;
			case 2: 	// Set Seat
				cgc_printf("\n-> ");
				cgc_receive_until(selection, '\n', 19 );
				
				choice = 0;
				while ( cgc_isalpha( selection[choice] ) ) {
					co->seat[choice] = selection[choice];
					choice++;
				}
				
				/// NULL terminated
				co->seat[choice] = '\x00';				
				break;
			case 3:		// Set Population
				cgc_printf("\n-> ");
				cgc_receive_until( selection, '\n', 19 );

				co->population = cgc_atoi(selection);

				break;
			case 4:		/// Set Area
				cgc_printf("\n-> ");
				cgc_receive_until( selection, '\n', 19);
				co->area = cgc_atof( selection );
				break;
			case 5:		/// Set Density
				cgc_printf("\n-> ");
				cgc_receive_until( selection, '\n', 19);
				co->density = cgc_atof( selection );
				break;
			case 6:	/// Add border
				if ( co->border_count >= COUNTYBORDERMAX) {
                                        cgc_printf("!!Max borders reached\n");
					break;
                                }

                                if ( cgc_allocate( sizeof(Border), 0, (void**)&pb) != 0 ) {
                                        pb = NULL;
                                        break;
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

                                co->borders[ co->border_count ] = pb;
                                co->border_count++;
				break;
			case 7:
				/// Add City
				/// Find a free slot
				choice = 0;
				while ( choice < COUNTYCITYMAX ) {
					if ( co->cities[choice] == NULL ) {
						break;
					}
					choice++;
				}

				if ( choice == COUNTYCITYMAX ) {
					cgc_printf("!!Max cities reached\n");
					continue;
				}

				if ( cgc_allocate( sizeof(City), 0, (void**)(&pc)) != 0 ) {
					pc = NULL;
					continue;
				}

				cgc_initCity( pc );

				co->cities[choice] = pc;

				cgc_printf("New City Name: ");
				cgc_receive_until( selection, '\n', 19 );

				choice = 0;
				while( cgc_isalnum( selection[choice] ) ) {
					pc->name[choice] = selection[choice];
					choice++;
				} 

				pc->name[choice] = '\x00';
				co->city_count++;
				break;
			case 8:
				/// cgc_select city
				for ( choice = 0; choice < COUNTYCITYMAX; choice++ ) {
					if ( co->cities[choice] != NULL ) {
						cgc_printf("@d) @s\n", choice + 1, co->cities[choice]);
					}
				}

				cgc_printf("\n-> ");
				cgc_bzero( selection, 30 );
				cgc_receive_until( selection, '\n', 4 );

				choice = cgc_atoi( selection );

				if ( choice < 1 || choice > COUNTYCITYMAX || co->cities[choice-1] == NULL ) {
					cgc_printf("Invalid choice\n");
					continue;
				}

				if ( cgc_cityMenu( co->cities[choice-1] ) == 0 ) {
					co->cities[choice-1] = NULL;
					co->city_count--;
				}
				break;
			case 9:
				cgc_freeCounty( co );
				return 0;
				break;
			case 10:
				return 1;
				break;
			default:
				cgc_printf("Invalid choice\n");
				continue;
		};
	}
	return 1;
}

/**
 * Free a county structure
 * @param co Pointer to a county structure
 * @return Returns nothing
 **/
void cgc_freeCounty( pCounty co )
{
	int index = 0;

	if ( co == NULL ) {
		return;
	}

	for ( index = 0; index < co->border_count; index++ ) {
		if ( co->borders[index] != NULL ) {
			cgc_deallocate(co->borders[index], sizeof(Border) );
			co->borders[index] = NULL;
		}
	}

	for (index = 0; index < COUNTYCITYMAX; index++ ) {
		cgc_freeCity( co->cities[index] );
		co->cities[index] = NULL;
	}

	cgc_deallocate( co, sizeof(County) );
	
	return;
}

/**
 * Initialize the county structure
 * @param co Pointer to a county structure
 * @return Returns nothing
 **/
void cgc_initCounty( pCounty co )
{
	int index = 0;

	if ( co == NULL ) {
		return;
	}

	for ( index = 0; index < 20; index++ ) {
		co->name[index] = 0;
		co->seat[index] = 0;

		co->cities[index] = NULL;
		co->borders[index] = NULL;
	}

	co->population = -1;
	co->area = -1.0;
	co->density = -1.0;
	co->city_count = 0;
	co->border_count = 0;

	return;
}

/**
 * Print the County information
 * @param co Pointer to the county structure
 * @return Returns nothing
 **/
void cgc_printCountyInfo( pCounty co )
{
	int index = 0;

	if ( co == NULL ) {
		return;
	}

	cgc_printf("\t\t\tCounty: ");
	if ( co->name[0] == '\x00' ) {
		cgc_printf("Unknown\n");
	} else {
		cgc_printf("@s\n", co->name);
	}

	cgc_printf("\t\t\t\tSeat: ");
	if ( co->seat[0] == '\x00' ) {
		cgc_printf("Unknown\n");
	} else {
		cgc_printf("@s\n", co->seat);
	}

	if ( co->population >= 0 ) {
		cgc_printf("\t\t\t\tPopulation: @d\n", co->population);
	}

	if ( co->area >= 0 ) {
		cgc_printf("\t\t\t\tArea: @f\n", co->area);
	}

	if ( co->density >= 0 ) {
		cgc_printf("\t\t\t\tDensity: @f\n", co->density);
	}

	for (index = 0; index < co->border_count; index++ ) {
		cgc_printf("\t\t\t\tBorder: @f @f @f @f\n", co->borders[index]->latStart, co->borders[index]->lngStart, co->borders[index]->latEnd, co->borders[index]->lngEnd);
	}

	for (index = 0; index < COUNTYCITYMAX; index++ ) {
		if ( co->cities[index] != NULL ) {
			cgc_printCityInfo( co->cities[ index ]);
		}
	}

	return;
}

/**
 * County parsing top level
 * @param str Pointer to the string structure to parse
 * @return Returns a pointer to a filled out county structure or NULL on failure
 **/
pCounty cgc_countyTopLevel( pstring str )
{
	pCounty newCounty = NULL;
	int startIndex = 0;
	int endIndex = 0;
	int lastGood = 0;
	int tempInt = 0;
	char *tempChar = NULL;
	element el;

	if ( str == NULL ) {
		return NULL;
	}

	cgc_skipWhiteSpace( str );

	lastGood = str->index;

	if ( !cgc_atChar( str, '{' ) ) {
		goto end;
	}

	cgc_incChar( str );

	cgc_skipWhiteSpace(str);

	cgc_getIndex( str, &startIndex );

	endIndex = cgc_skipAlpha( str );

	if ( endIndex == -1 ) {
		goto end;
	}

	if ( startIndex == endIndex ) {
		goto end;
	}

	tempChar = cgc_copyData( str, startIndex, endIndex );

	if ( tempChar == NULL ) {
		goto end;
	}

	if ( cgc_strcmp( tempChar, "County" ) != 0 ) {
		goto end;
	}

	cgc_deallocate(tempChar, (endIndex-startIndex)+1);

	cgc_skipWhiteSpace( str );

	if ( !cgc_atChar( str, '}') ) {
		goto end;
	}

	cgc_skipWhiteSpace( str );

	/// Skip past the closing brace
	cgc_incChar( str );

	if ( cgc_allocate( sizeof(County), 0, (void**)&newCounty) != 0 ) {
		newCounty = NULL;
		goto end;
	}

	lastGood = str->index;

	cgc_initCounty( newCounty );

	tempChar = cgc_pullNextElementName( str );

	while (tempChar != NULL ) {
		el = cgc_elementNameToEnum( tempChar );

		cgc_deallocate( tempChar, cgc_strlen(tempChar) + 1 );

		switch ( el ) {
			case name:
				tempChar = cgc_extractName( str );

				if ( tempChar == NULL ) {
					goto error;
				}
	
				cgc_bzero( newCounty->name, 20 );
				cgc_strncpy( newCounty->name, tempChar, 19 );

				cgc_deallocate( tempChar, cgc_strlen(tempChar) + 1 );
				tempChar = NULL;
				break;
			case seat:
				tempChar = cgc_extractSeat( str );

				if ( tempChar == NULL ) {
					goto error;
				}

				cgc_bzero( newCounty->seat, 20 );
				cgc_strncpy( newCounty->seat, tempChar, 19);

				cgc_deallocate( tempChar, cgc_strlen(tempChar) + 1 );
				tempChar = NULL;
				break;
			case density:
				newCounty->density = cgc_extractDensity( str );

				if ( newCounty->density < 0.0 ) {
					goto error;
				}
				break;
			case population:
				newCounty->population = cgc_extractPopulation( str );

				if ( newCounty->population < 0 ) {
					goto error;
				}

				break;

			case area:
				newCounty->area = cgc_extractArea( str );

				if ( newCounty->area < 0.0 ) {
					goto error;
				}

				break;
			case border:
				tempInt = newCounty->border_count;

				if ( tempInt >= COUNTYBORDERMAX ) {
					goto error;
				}

				newCounty->borders[ tempInt ] = cgc_extractBorder( str );

				if ( newCounty->borders[tempInt] == NULL ) {
					goto error;
				}

				newCounty->border_count++;

				break;
			case city:
				tempInt = newCounty->city_count;

				if ( tempInt >= COUNTYCITYMAX ) {
					goto error;
				}

				newCounty->cities[ tempInt ] = cgc_cityTopLevel( str );

				if ( newCounty->cities[tempInt] == NULL ) {
					goto error;
				}

				newCounty->city_count++;
				break;
			default:
				cgc_printf("!!Element not allowed\n");
				goto error;
				break;
		
		};

		cgc_getIndex( str, &lastGood);

		tempChar = cgc_pullNextElementName( str );
	}

	/// Skip any residual white space
	cgc_skipWhiteSpace( str );

	/// It must be at the final opening brace
	if ( !cgc_atChar( str, '{') ) {
		goto error;
	}

	cgc_skipLength( str, 1);
	cgc_skipWhiteSpace( str );

	if ( !cgc_atChar( str, '#' ) ) {
		goto error;
	}

	cgc_skipLength(str, 1);
	
	cgc_getIndex( str, &startIndex );
	cgc_skipAlpha( str );
	cgc_getIndex( str, &endIndex);

	if ( startIndex == endIndex ) {
		goto error;
	} else if ( endIndex == -1 ) {
		goto error;
	}

	tempChar = cgc_copyData( str, startIndex, endIndex );

#ifdef PATCHED
	if ( tempChar == NULL ) {
		goto error;
	}
#endif

	if ( cgc_strcmp( tempChar, "County" ) != 0 ) {
		cgc_deallocate( tempChar, cgc_strlen(tempChar) + 1 );
		goto error;
	}

	cgc_deallocate( tempChar, cgc_strlen(tempChar) + 1 );

	cgc_skipWhiteSpace( str );
	
	if ( !cgc_atChar( str, '}' ) ) {
		goto error;
	}

	cgc_incChar( str );

	goto end;

error:
	if ( newCounty ) {
		cgc_freeCounty( newCounty );
		newCounty = NULL;
	}

	cgc_printf("!!Error at: @s\n", str->buffer + lastGood );
	str->index = lastGood;

end:

	return newCounty;
}

/**
 * Check if the id matches what is expected
 * @param str Pointer to a string structure
 * @param id Pointer to the element id to test for
 * @param ending Used as a bool to indicate if it is a closing element
 * @return Returns 1 on valid 0 on failure.
 **/
int cgc_checkId ( pstring str, char *id, int ending )
{
	int retval = 0;
	int startIndex = 0;
	int endIndex = 0;
	char *temp = NULL;

	if ( str == NULL ) {
		goto end;
	}

	cgc_skipWhiteSpace( str );
	
	if ( !cgc_atChar(str, '{'))  {
		goto end;
	}

	cgc_incChar( str );

	/// If it is the end check for #
	if ( ending == 1 ) {
		cgc_skipWhiteSpace(str);
		if ( !cgc_atChar( str, '#' ) ) {
			goto end;
		}

		cgc_incChar( str );
	}

	startIndex = cgc_skipWhiteSpace( str );
	endIndex = cgc_skipAlpha( str );

	if ( endIndex == -1 ) { 
		goto end;
	} else if ( startIndex == endIndex ) {
		goto end;
	}

	temp = cgc_copyData( str, startIndex, endIndex );

	if ( !temp ) {
		goto end;
	}

	if ( cgc_strcmp( temp, id ) != 0 ) {
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );

		goto end;
	}

	cgc_deallocate( temp, cgc_strlen(temp) + 1 );

	cgc_skipWhiteSpace( str );
	if ( str->buffer[str->index] != '}' ) {
		goto end;
	}

	cgc_incChar( str );

	retval = 1;
end:
	return retval;
}

/**
 * Extracts the density data
 * @param str Pointer to the string structure
 * @return Returns the density double or -1.0 on failure
 **/
double cgc_extractDensity( pstring str )
{
	double density = -1.0;
	register int startIndex = 0;
	register int endIndex = 0;
	char *temp = NULL;
	int lastGood = 0;

	if ( str == NULL ) {
		goto end;
	}

	cgc_getIndex( str, &lastGood );

	if ( cgc_checkId( str, "Density", 0) == 0 ) {
		goto error;
	}

	startIndex = cgc_skipWhiteSpace(str);
	endIndex = cgc_skipFloat( str );

	if ( startIndex == endIndex ) {
		goto end;
	}

	if ( endIndex == -1 ) {
		goto end;
	}

	temp = cgc_copyData( str, startIndex, endIndex );

	if (temp == NULL) {
		goto end;
	}

	density = cgc_atof( temp );

	cgc_deallocate( temp, (endIndex-startIndex) + 1 );
	temp = NULL;

	if ( cgc_checkId( str, "Density", 1 ) == 0 ) {
		goto error;
	}

	goto end;
	
error:
	str->index = lastGood;
	density = -1.0;

end:
	return density;
}

/**
 * Extracts the area data
 * @param str Pointer to the string structure
 * @return Returns the area double or -1.0 on failure
 **/
double cgc_extractArea( pstring str )
{
	double area = -1.0;
	int startIndex = 0;
	int endIndex = 0;
	char *temp = NULL;
	int lastGood = 0;

	if ( str == NULL ) {
		goto end;
	}

	cgc_skipWhiteSpace( str );
	cgc_getIndex( str, &lastGood );
	
	if ( str->buffer[ str->index ] != '{' ) {
		goto end;
	}

	cgc_incChar( str );

	cgc_skipWhiteSpace( str );
	cgc_getIndex( str, &startIndex);
	endIndex = cgc_skipAlpha( str );

	if ( endIndex == -1 || startIndex == endIndex ) {
		goto end;
	}	

	temp = cgc_copyData( str, startIndex, endIndex );

	if ( !temp ) {
		goto end;
	}

	if ( cgc_strcmp( temp, "Area" ) != 0 ) {
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );

		goto end;
	}

	cgc_deallocate( temp, cgc_strlen(temp) + 1 );

	cgc_skipWhiteSpace( str );
	if ( str->buffer[str->index] != '}' ) {
		goto end;
	}

	cgc_incChar( str );
	startIndex = cgc_skipWhiteSpace(str);
	endIndex = cgc_skipFloat( str );

	if ( startIndex == endIndex ) {
		goto end;
	}

	if ( endIndex == -1 ) {
		goto end;
	}

	temp = cgc_copyData( str, startIndex, endIndex );

	if (temp == NULL) {
		goto end;
	}

	area = cgc_atof( temp );

	cgc_deallocate( temp, (endIndex-startIndex) + 1 );
	temp = NULL;

	cgc_skipWhiteSpace( str );
	if ( !cgc_atChar( str, '{' ) ) {
		goto error;
	}

	cgc_incChar( str );
	cgc_skipWhiteSpace(str);

	if (!cgc_atChar( str, '#' ) ) {
		goto error;
	}

	startIndex = cgc_incChar( str );
	endIndex = cgc_skipAlpha( str );

	temp = cgc_copyData( str, startIndex, endIndex );

	if ( temp == NULL ) {
		goto error;
	}

	if ( cgc_strcmp( temp, "Area") != 0 ) {
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
		goto error;
	}

	cgc_deallocate( temp, cgc_strlen(temp) + 1 );

	cgc_skipWhiteSpace( str );
	if ( !cgc_atChar( str, '}') ) {
		goto error;
	}

	cgc_incChar( str );
	
	goto end;
	
error:
	str->index = lastGood;
	area = -1.0;

end:
	return area;
}

/**
 * Extracts the seat data
 * @param str Pointer to the string structure
 * @return Returns a pointer to the seat data or NULL on failure
 **/
char *cgc_extractSeat( pstring str )
{
	char *seat = NULL;
	int startIndex = 0;
	int endIndex = 0;
	char *temp = NULL;
	int lastGood = 0;

	if ( str == NULL ) {
		goto end;
	}

	cgc_skipWhiteSpace( str );
	cgc_getIndex( str, &lastGood );
	
	if ( str->buffer[ str->index ] != '{' ) {
		goto end;
	}

	cgc_incChar( str );

	cgc_skipWhiteSpace( str );
	cgc_getIndex( str, &startIndex);
	endIndex = cgc_skipAlpha( str );

	if ( endIndex == -1 || startIndex == endIndex ) {
		goto end;
	}	

	temp = cgc_copyData( str, startIndex, endIndex );

	if ( !temp ) {
		goto end;
	}

	if ( cgc_strcmp( temp, "Seat" ) != 0 ) {
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
		goto end;
	}

	cgc_deallocate( temp, cgc_strlen(temp) + 1 );

	cgc_skipWhiteSpace( str );
	if ( str->buffer[str->index] != '}' ) {
		goto end;
	}

	cgc_incChar( str );
	startIndex = cgc_skipWhiteSpace(str);
	endIndex = cgc_skipAlpha( str );


	if ( startIndex == endIndex ) {
		goto end;
	}

	if ( endIndex == -1 ) {
		goto end;
	}

	seat = cgc_copyData( str, startIndex, endIndex );

	if (seat == NULL) {
		goto end;
	}

	cgc_skipWhiteSpace( str );
	if ( !cgc_atChar( str, '{' ) ) {
		goto error;
	}

	cgc_incChar( str );
	cgc_skipWhiteSpace(str);

	if (!cgc_atChar( str, '#' ) ) {
		goto error;
	}

	startIndex = cgc_incChar( str );
	endIndex = cgc_skipAlpha( str );

	if ( startIndex == endIndex ) {
		goto error;
	}

	if ( endIndex == -1 ) {
		goto error;
	}

	temp = cgc_copyData( str, startIndex, endIndex );

	if ( temp == NULL ) {
		goto error;
	}

	if ( cgc_strcmp( temp, "Seat") != 0 ) {
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
		goto error;
	}

	cgc_deallocate( temp, cgc_strlen(temp) + 1 );

	cgc_skipWhiteSpace( str );
	if ( !cgc_atChar( str, '}') ) {
		goto error;
	}

	cgc_incChar( str );
	
	goto end;
	
error:
	if ( seat ) {
		cgc_deallocate( seat, cgc_strlen(seat) + 1 );
		seat = NULL;
	}

	str->index = lastGood;

end:
	return seat;
}
