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

#include "countyParsers.h"

int countyMenu( pCounty co )
{
	int choice = 0;
	char selection[30];
	pBorder pb = NULL;
	pCity pc = NULL;

	if ( co == NULL ) {
		return 0;
	}

	while ( 1 ) {
		printf("County: @s\n", co->name );
		printf("1) Display County Info\n");
		printf("2) Set Seat\n");
		printf("3) Set Population\n");
		printf("4) Set Area\n");
		printf("5) Set Density\n");
		printf("6) Add Border\n");
		printf("7) Add City\n");
		printf("8) Select City\n");
		printf("9) Delete County and Exit Menu\n");
		printf("10) Exit Menu\n");
		printf("Selection: ");

		bzero(selection, 4 );
		receive_until( selection, '\n', 3);

		choice = atoi( selection );
		bzero( selection, 30 );

		switch( choice ) {
			case 1:
				printCountyInfo( co );
				break;
			case 2: 	// Set Seat
				printf("\n-> ");
				receive_until(selection, '\n', 19 );
				
				choice = 0;
				while ( isalpha( selection[choice] ) ) {
					co->seat[choice] = selection[choice];
					choice++;
				}
				
				/// NULL terminated
				co->seat[choice] = '\x00';				
				break;
			case 3:		// Set Population
				printf("\n-> ");
				receive_until( selection, '\n', 19 );

				co->population = atoi(selection);

				break;
			case 4:		/// Set Area
				printf("\n-> ");
				receive_until( selection, '\n', 19);
				co->area = atof( selection );
				break;
			case 5:		/// Set Density
				printf("\n-> ");
				receive_until( selection, '\n', 19);
				co->density = atof( selection );
				break;
			case 6:	/// Add border
				if ( co->border_count >= COUNTYBORDERMAX) {
                                        printf("!!Max borders reached\n");
					break;
                                }

                                if ( allocate( sizeof(Border), 0, (void**)&pb) != 0 ) {
                                        pb = NULL;
                                        break;
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
					printf("!!Max cities reached\n");
					continue;
				}

				if ( allocate( sizeof(City), 0, (void**)(&pc)) != 0 ) {
					pc = NULL;
					continue;
				}

				initCity( pc );

				co->cities[choice] = pc;

				printf("New City Name: ");
				receive_until( selection, '\n', 19 );

				choice = 0;
				while( isalnum( selection[choice] ) ) {
					pc->name[choice] = selection[choice];
					choice++;
				} 

				pc->name[choice] = '\x00';
				co->city_count++;
				break;
			case 8:
				/// select city
				for ( choice = 0; choice < COUNTYCITYMAX; choice++ ) {
					if ( co->cities[choice] != NULL ) {
						printf("@d) @s\n", choice + 1, co->cities[choice]);
					}
				}

				printf("\n-> ");
				bzero( selection, 30 );
				receive_until( selection, '\n', 4 );

				choice = atoi( selection );

				if ( choice < 1 || choice > COUNTYCITYMAX || co->cities[choice-1] == NULL ) {
					printf("Invalid choice\n");
					continue;
				}

				if ( cityMenu( co->cities[choice-1] ) == 0 ) {
					co->cities[choice-1] = NULL;
					co->city_count--;
				}
				break;
			case 9:
				freeCounty( co );
				return 0;
				break;
			case 10:
				return 1;
				break;
			default:
				printf("Invalid choice\n");
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
void freeCounty( pCounty co )
{
	int index = 0;

	if ( co == NULL ) {
		return;
	}

	for ( index = 0; index < co->border_count; index++ ) {
		if ( co->borders[index] != NULL ) {
			deallocate(co->borders[index], sizeof(Border) );
			co->borders[index] = NULL;
		}
	}

	for (index = 0; index < COUNTYCITYMAX; index++ ) {
		freeCity( co->cities[index] );
		co->cities[index] = NULL;
	}

	deallocate( co, sizeof(County) );
	
	return;
}

/**
 * Initialize the county structure
 * @param co Pointer to a county structure
 * @return Returns nothing
 **/
void initCounty( pCounty co )
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
void printCountyInfo( pCounty co )
{
	int index = 0;

	if ( co == NULL ) {
		return;
	}

	printf("\t\t\tCounty: ");
	if ( co->name[0] == '\x00' ) {
		printf("Unknown\n");
	} else {
		printf("@s\n", co->name);
	}

	printf("\t\t\t\tSeat: ");
	if ( co->seat[0] == '\x00' ) {
		printf("Unknown\n");
	} else {
		printf("@s\n", co->seat);
	}

	if ( co->population >= 0 ) {
		printf("\t\t\t\tPopulation: @d\n", co->population);
	}

	if ( co->area >= 0 ) {
		printf("\t\t\t\tArea: @f\n", co->area);
	}

	if ( co->density >= 0 ) {
		printf("\t\t\t\tDensity: @f\n", co->density);
	}

	for (index = 0; index < co->border_count; index++ ) {
		printf("\t\t\t\tBorder: @f @f @f @f\n", co->borders[index]->latStart, co->borders[index]->lngStart, co->borders[index]->latEnd, co->borders[index]->lngEnd);
	}

	for (index = 0; index < COUNTYCITYMAX; index++ ) {
		if ( co->cities[index] != NULL ) {
			printCityInfo( co->cities[ index ]);
		}
	}

	return;
}

/**
 * County parsing top level
 * @param str Pointer to the string structure to parse
 * @return Returns a pointer to a filled out county structure or NULL on failure
 **/
pCounty countyTopLevel( pstring str )
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

	skipWhiteSpace( str );

	lastGood = str->index;

	if ( !atChar( str, '{' ) ) {
		goto end;
	}

	incChar( str );

	skipWhiteSpace(str);

	getIndex( str, &startIndex );

	endIndex = skipAlpha( str );

	if ( endIndex == -1 ) {
		goto end;
	}

	if ( startIndex == endIndex ) {
		goto end;
	}

	tempChar = copyData( str, startIndex, endIndex );

	if ( tempChar == NULL ) {
		goto end;
	}

	if ( strcmp( tempChar, "County" ) != 0 ) {
		goto end;
	}

	deallocate(tempChar, (endIndex-startIndex)+1);

	skipWhiteSpace( str );

	if ( !atChar( str, '}') ) {
		goto end;
	}

	skipWhiteSpace( str );

	/// Skip past the closing brace
	incChar( str );

	if ( allocate( sizeof(County), 0, (void**)&newCounty) != 0 ) {
		newCounty = NULL;
		goto end;
	}

	lastGood = str->index;

	initCounty( newCounty );

	tempChar = pullNextElementName( str );

	while (tempChar != NULL ) {
		el = elementNameToEnum( tempChar );

		deallocate( tempChar, strlen(tempChar) + 1 );

		switch ( el ) {
			case name:
				tempChar = extractName( str );

				if ( tempChar == NULL ) {
					goto error;
				}
	
				bzero( newCounty->name, 20 );
				strncpy( newCounty->name, tempChar, 19 );

				deallocate( tempChar, strlen(tempChar) + 1 );
				tempChar = NULL;
				break;
			case seat:
				tempChar = extractSeat( str );

				if ( tempChar == NULL ) {
					goto error;
				}

				bzero( newCounty->seat, 20 );
				strncpy( newCounty->seat, tempChar, 19);

				deallocate( tempChar, strlen(tempChar) + 1 );
				tempChar = NULL;
				break;
			case density:
				newCounty->density = extractDensity( str );

				if ( newCounty->density < 0.0 ) {
					goto error;
				}
				break;
			case population:
				newCounty->population = extractPopulation( str );

				if ( newCounty->population < 0 ) {
					goto error;
				}

				break;

			case area:
				newCounty->area = extractArea( str );

				if ( newCounty->area < 0.0 ) {
					goto error;
				}

				break;
			case border:
				tempInt = newCounty->border_count;

				if ( tempInt >= COUNTYBORDERMAX ) {
					goto error;
				}

				newCounty->borders[ tempInt ] = extractBorder( str );

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

				newCounty->cities[ tempInt ] = cityTopLevel( str );

				if ( newCounty->cities[tempInt] == NULL ) {
					goto error;
				}

				newCounty->city_count++;
				break;
			default:
				printf("!!Element not allowed\n");
				goto error;
				break;
		
		};

		getIndex( str, &lastGood);

		tempChar = pullNextElementName( str );
	}

	/// Skip any residual white space
	skipWhiteSpace( str );

	/// It must be at the final opening brace
	if ( !atChar( str, '{') ) {
		goto error;
	}

	skipLength( str, 1);
	skipWhiteSpace( str );

	if ( !atChar( str, '#' ) ) {
		goto error;
	}

	skipLength(str, 1);
	
	getIndex( str, &startIndex );
	skipAlpha( str );
	getIndex( str, &endIndex);

	if ( startIndex == endIndex ) {
		goto error;
	} else if ( endIndex == -1 ) {
		goto error;
	}

	tempChar = copyData( str, startIndex, endIndex );

#ifdef PATCHED
	if ( tempChar == NULL ) {
		goto error;
	}
#endif

	if ( strcmp( tempChar, "County" ) != 0 ) {
		deallocate( tempChar, strlen(tempChar) + 1 );
		goto error;
	}

	deallocate( tempChar, strlen(tempChar) + 1 );

	skipWhiteSpace( str );
	
	if ( !atChar( str, '}' ) ) {
		goto error;
	}

	incChar( str );

	goto end;

error:
	if ( newCounty ) {
		freeCounty( newCounty );
		newCounty = NULL;
	}

	printf("!!Error at: @s\n", str->buffer + lastGood );
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
int checkId ( pstring str, char *id, int ending )
{
	int retval = 0;
	int startIndex = 0;
	int endIndex = 0;
	char *temp = NULL;

	if ( str == NULL ) {
		goto end;
	}

	skipWhiteSpace( str );
	
	if ( !atChar(str, '{'))  {
		goto end;
	}

	incChar( str );

	/// If it is the end check for #
	if ( ending == 1 ) {
		skipWhiteSpace(str);
		if ( !atChar( str, '#' ) ) {
			goto end;
		}

		incChar( str );
	}

	startIndex = skipWhiteSpace( str );
	endIndex = skipAlpha( str );

	if ( endIndex == -1 ) { 
		goto end;
	} else if ( startIndex == endIndex ) {
		goto end;
	}

	temp = copyData( str, startIndex, endIndex );

	if ( !temp ) {
		goto end;
	}

	if ( strcmp( temp, id ) != 0 ) {
		deallocate( temp, strlen(temp) + 1 );

		goto end;
	}

	deallocate( temp, strlen(temp) + 1 );

	skipWhiteSpace( str );
	if ( str->buffer[str->index] != '}' ) {
		goto end;
	}

	incChar( str );

	retval = 1;
end:
	return retval;
}

/**
 * Extracts the density data
 * @param str Pointer to the string structure
 * @return Returns the density double or -1.0 on failure
 **/
double extractDensity( pstring str )
{
	double density = -1.0;
	register int startIndex = 0;
	register int endIndex = 0;
	char *temp = NULL;
	int lastGood = 0;

	if ( str == NULL ) {
		goto end;
	}

	getIndex( str, &lastGood );

	if ( checkId( str, "Density", 0) == 0 ) {
		goto error;
	}

	startIndex = skipWhiteSpace(str);
	endIndex = skipFloat( str );

	if ( startIndex == endIndex ) {
		goto end;
	}

	if ( endIndex == -1 ) {
		goto end;
	}

	temp = copyData( str, startIndex, endIndex );

	if (temp == NULL) {
		goto end;
	}

	density = atof( temp );

	deallocate( temp, (endIndex-startIndex) + 1 );
	temp = NULL;

	if ( checkId( str, "Density", 1 ) == 0 ) {
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
double extractArea( pstring str )
{
	double area = -1.0;
	int startIndex = 0;
	int endIndex = 0;
	char *temp = NULL;
	int lastGood = 0;

	if ( str == NULL ) {
		goto end;
	}

	skipWhiteSpace( str );
	getIndex( str, &lastGood );
	
	if ( str->buffer[ str->index ] != '{' ) {
		goto end;
	}

	incChar( str );

	skipWhiteSpace( str );
	getIndex( str, &startIndex);
	endIndex = skipAlpha( str );

	if ( endIndex == -1 || startIndex == endIndex ) {
		goto end;
	}	

	temp = copyData( str, startIndex, endIndex );

	if ( !temp ) {
		goto end;
	}

	if ( strcmp( temp, "Area" ) != 0 ) {
		deallocate( temp, strlen(temp) + 1 );

		goto end;
	}

	deallocate( temp, strlen(temp) + 1 );

	skipWhiteSpace( str );
	if ( str->buffer[str->index] != '}' ) {
		goto end;
	}

	incChar( str );
	startIndex = skipWhiteSpace(str);
	endIndex = skipFloat( str );

	if ( startIndex == endIndex ) {
		goto end;
	}

	if ( endIndex == -1 ) {
		goto end;
	}

	temp = copyData( str, startIndex, endIndex );

	if (temp == NULL) {
		goto end;
	}

	area = atof( temp );

	deallocate( temp, (endIndex-startIndex) + 1 );
	temp = NULL;

	skipWhiteSpace( str );
	if ( !atChar( str, '{' ) ) {
		goto error;
	}

	incChar( str );
	skipWhiteSpace(str);

	if (!atChar( str, '#' ) ) {
		goto error;
	}

	startIndex = incChar( str );
	endIndex = skipAlpha( str );

	temp = copyData( str, startIndex, endIndex );

	if ( temp == NULL ) {
		goto error;
	}

	if ( strcmp( temp, "Area") != 0 ) {
		deallocate( temp, strlen(temp) + 1 );
		goto error;
	}

	deallocate( temp, strlen(temp) + 1 );

	skipWhiteSpace( str );
	if ( !atChar( str, '}') ) {
		goto error;
	}

	incChar( str );
	
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
char *extractSeat( pstring str )
{
	char *seat = NULL;
	int startIndex = 0;
	int endIndex = 0;
	char *temp = NULL;
	int lastGood = 0;

	if ( str == NULL ) {
		goto end;
	}

	skipWhiteSpace( str );
	getIndex( str, &lastGood );
	
	if ( str->buffer[ str->index ] != '{' ) {
		goto end;
	}

	incChar( str );

	skipWhiteSpace( str );
	getIndex( str, &startIndex);
	endIndex = skipAlpha( str );

	if ( endIndex == -1 || startIndex == endIndex ) {
		goto end;
	}	

	temp = copyData( str, startIndex, endIndex );

	if ( !temp ) {
		goto end;
	}

	if ( strcmp( temp, "Seat" ) != 0 ) {
		deallocate( temp, strlen(temp) + 1 );
		goto end;
	}

	deallocate( temp, strlen(temp) + 1 );

	skipWhiteSpace( str );
	if ( str->buffer[str->index] != '}' ) {
		goto end;
	}

	incChar( str );
	startIndex = skipWhiteSpace(str);
	endIndex = skipAlpha( str );


	if ( startIndex == endIndex ) {
		goto end;
	}

	if ( endIndex == -1 ) {
		goto end;
	}

	seat = copyData( str, startIndex, endIndex );

	if (seat == NULL) {
		goto end;
	}

	skipWhiteSpace( str );
	if ( !atChar( str, '{' ) ) {
		goto error;
	}

	incChar( str );
	skipWhiteSpace(str);

	if (!atChar( str, '#' ) ) {
		goto error;
	}

	startIndex = incChar( str );
	endIndex = skipAlpha( str );

	if ( startIndex == endIndex ) {
		goto error;
	}

	if ( endIndex == -1 ) {
		goto error;
	}

	temp = copyData( str, startIndex, endIndex );

	if ( temp == NULL ) {
		goto error;
	}

	if ( strcmp( temp, "Seat") != 0 ) {
		deallocate( temp, strlen(temp) + 1 );
		goto error;
	}

	deallocate( temp, strlen(temp) + 1 );

	skipWhiteSpace( str );
	if ( !atChar( str, '}') ) {
		goto error;
	}

	incChar( str );
	
	goto end;
	
error:
	if ( seat ) {
		deallocate( seat, strlen(seat) + 1 );
		seat = NULL;
	}

	str->index = lastGood;

end:
	return seat;
}
