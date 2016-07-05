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

#include "planetParsers.h"

/**
 * Menu to manage a planet
 * @param pl Pointer to the planet to manage
 * @return Returns 0 if planet pointer should be NULL 1 otherwise
 **/
int planetMenu( pPlanet pl )
{
	int choice = 0;
	char selection[30];
	size_t length = 0;
	pCountry pc = NULL;

	if ( pl == NULL ) {
		return 0;
	}

	while ( 1 ) {
		bzero(selection, 30);

		printf("\nPlanet: @s\n", pl->name);
		printf("1) Display planet information\n");
		printf("2) Set Period\n");
		printf("3) Set Orbit Speed\n");
		printf("4) Set Aphelion\n");
		printf("5) Set Perihelion\n");
		printf("6) Set Mean Radius\n");
		printf("7) Set Equatorial Radius\n");
		printf("8) Set Mass\n");
		printf("9) Set Gravity\n");
		printf("10) Set population\n");
		printf("11) Add Country\n");
		printf("12) Select country\n");
		printf("13) Delete Planet and exit menu\n");
		printf("14) Exit menu\n");
		printf("Selection: ");

		receive_until(selection, '\n', 3);
		choice = atoi( selection );

		switch ( choice ) {
			case 1:
				printPlanetInfo( pl );
				break;
			case 2:
				printf("\n-> ");
				receive_until( selection, '\n', 10);
				pl->period = atof(selection);
				break;
			case 3:
				printf("\n-> ");
				receive_until(selection, '\n', 10);
				pl->orbitspeed = atof(selection);
				break;
			case 4:
				printf("\n-> ");
				receive_until( selection, '\n', 10);
				pl->aphelion = atof(selection);
				break;
			case 5:
				printf("\n-> ");
				receive_until( selection, '\n', 10);
				pl->perihelion = atof(selection);
				break;
			case 6:
				printf("\n-> ");
				receive_until( selection, '\n', 10);
				pl->radius = atof(selection);
				break;
			case 7:
				printf("\n-> ");
				receive_until( selection, '\n', 10);
				pl->eradius = atof(selection);
				break;
			case 8:
				printf("\n-> ");
				receive_until( selection, '\n', 10);
				pl->mass = atof(selection);
				break;
			case 9:
				printf("\n-> ");
				receive_until( selection, '\n', 10);
				pl->gravity = atof(selection);
				break;
			case 10:
				printf("\n-> ");
				receive_until( selection, '\n', 10);
				pl->population = atoi(selection);
				break;
			case 11:
				if ( pl->country_count >= COUNTRYMAX ) {
					printf("Too many countries\n");
					continue;
				}

				printf("\nNew Name: ");
				receive_until(selection, '\n', 19);

				choice = 0;
				while ( choice < COUNTRYMAX ) {
					if ( pl->countries[choice] == NULL ) {
						break;
					}
					choice++;
				}

				if ( choice == COUNTRYMAX ) {
					printf("!!No country slots\n");
					continue;
				}

				if ( allocate( sizeof(Country), 0, (void**)(&pc) ) != 0 ) {
					printf("!!Failed to allocate structure\n");
					continue;
				}

				initCountry( pc );

				pl->countries[choice] = pc;

				length = 0;
	
				while ( isalnum( selection[length] ) ) {
					pc->name[length] = selection[length];
					length++;
				}
				pc->name[length] = '\x00';

				pl->country_count++;
				break;
			case 12:
				printf("\nCountries:\n");
				for ( choice = 0; choice < pl->country_count; choice++ ) {
					if ( pl->countries[choice] != NULL ) {
						printf("@d) @s\n", choice + 1, pl->countries[choice]);
					}
				}

				bzero(selection, 30);
				printf("\n-> ");
				receive_until( selection, '\n', 3 );

				choice = atoi(selection);

				if ( choice < 1 || choice > COUNTRYMAX) {
					printf("Invalid choice...\n");
					continue;
				} else if ( pl->countries[ choice-1] == NULL ) {
					printf("Invalid choice...\n");
					continue;
				}

				if ( countryMenu( pl->countries[choice-1]) == 0 ) {
					pl->countries[choice-1] = NULL;
					pl->country_count--;
				}
				break;
			case 13:
				freePlanet( pl );
				return 0;
				break;
			case 14:
				return 1;
				break;
			default:
				printf("Invalid...\n");
				break;
		};
	}

end:
	return 1;
}

/**
 * Frees the planet specified by the argument
 * @param pl Pointer to the planet structure
 * @return Returns nothing
 **/
void freePlanet( pPlanet pl )
{
	int index = 0;

	if ( pl == NULL ) {
		return;
	}

	/// Free all of the associated countries
	while ( index < COUNTRYMAX ) {
		if ( pl->countries[ index] != NULL ) {

			/// This function also frees the pointer so freePlanet does not have to.
			freeCountry( pl->countries[index] );
			pl->countries[index] = NULL;

		}

		index++;
	}
	
	deallocate( pl, sizeof(Planet) );

	return;
}

/**
 * Print the planet information
 * @param pl Pointer to the planet structure
 * @return Returns nothing
 **/
void printPlanetInfo( pPlanet pl )
{
        int index = 0;

        if ( pl == NULL ) {
                return;
        }

        if ( pl->name[0] == '\x00' ) {
                printf("Name: Unknown\n");
        } else {
                printf("Name: @s\n", pl->name );
        }

        if ( pl->population >= 0 ) {
                printf("\tPopulation: @d\n", pl->population);
        }

        if ( pl->period >= 0.0 ) {
                printf("\tPeriod: @f\n", pl->period);
        }

        if ( pl->orbitspeed >= 0.0 ) {
                printf("\tOrbit Speed: @f\n", pl->orbitspeed);
        }

        if ( pl->aphelion >= 0.0 ) {
                printf("\tAphelion: @f\n", pl->aphelion);
        }

        if ( pl->perihelion >= 0.0 ) {
                printf("\tPerihelion: @f\n", pl->perihelion);
        }

        if ( pl->radius >= 0.0 ) {
                printf("\tRadius: @f\n", pl->radius);
        }

        if ( pl->eradius >= 0.0 ) {
                printf("\tERadius: @f\n", pl->eradius);
        }
        if ( pl->mass >= 0.0 ) {
                printf("\tMass: @f\n", pl->mass);
        }
	
	if ( pl->gravity >= 0.0 ) {
		printf("\tGravity: @f\n", pl->gravity);
	}

	/// Print each country's information
        while ( index < COUNTRYMAX ) {
                if ( pl->countries[ index ] != NULL ) {
                        printCountryInfo( pl->countries[index] );
                }

                index++;
        }

        return;
}

/**
 * Initialize all the planets members
 * @param pl Pointer to the planet structure
 * @return 0 on failure 1 on success
 **/
void initPlanet( pPlanet pl )
{
        register int index = 0;

        if ( pl == NULL ) {
                return;
        }

        bzero( pl->name, 20 );
        pl->period = -1.0;
        pl->orbitspeed = -1.0;
        pl->aphelion = -1.0;
        pl->perihelion = -1.0;
        pl->radius = -1.0;
        pl->eradius = -1.0;
        pl->mass = -1.0;
        pl->gravity = -1.0;
        pl->population = -1.0;

        pl->country_count = 0;

        while ( index < COUNTRYMAX ) {
                pl->countries[index] = NULL;
                index++;
        }

        return;
}

/**
 * Parse the planet string and its sub elements
 * @param topLevel Pointer to the string structure to be parsed
 * @return Returns a pointer to a planet structure with associated data. Null on failure
 **/
pPlanet planetTopLevel( pstring topLevel )
{
	int endIndex = 0;
        int temp_index = 0;
        pPlanet newPlanet = NULL;
        element el;
        char *fl = NULL;
        int lastGood = 0;

        if ( topLevel == NULL ) {
                goto end;
        }

        /// Skip any leading spaces
        skipWhiteSpace( topLevel );

	lastGood = topLevel->index;

	if ( topLevel->maxlength < 9 ) {
		goto end;
	}

	char *c = "{Planet}";

	for ( int i = 0; i < 8; i++ ) {
		if ( topLevel->buffer[ topLevel->index + i ] != c[i] ) {
			goto end;
		}
	}

        /// Skip 8 bytes of top level then any whitespace
        topLevel->index += 8;

	skipWhiteSpace( topLevel );

        /// Allocate a new planet structure
        if ( allocate( sizeof(Planet), 0, (void**)&newPlanet) != 0 ) {
                goto end;
        }

        initPlanet( newPlanet );

        /// Extract the next element name
        fl = pullNextElementName( topLevel );

        getIndex( topLevel, &lastGood);

        while ( fl != NULL ) {
                /// Convert the element name
                el = elementNameToEnum( fl );

                /// The name is no longer needed so free it
                deallocate( fl, strlen(fl) + 1 );

                switch (el) {
                        case name:
                                fl = extractName( topLevel );

                                if ( fl == NULL ) {
                                        goto error;
                                }

				bzero( newPlanet->name, 20 );
                                strncpy( newPlanet->name, fl, 19 );

                                deallocate(fl, strlen(fl) + 1 );
                                fl = NULL;

                                break;
                        case population:
                                newPlanet->population = extractPopulation( topLevel );

                                if ( newPlanet->population < 0 ) {
                                        goto error;
                                }

                                break;
                        case period:
                                /// Extract period and check result
                                newPlanet->period = extractPeriod( topLevel );
                                if ( newPlanet->period < 0.0 ) {
                                        goto error;
                                }

                                break;
                        case orbitspeed:
                                newPlanet->orbitspeed = extractOrbitSpeed( topLevel );

                                if ( newPlanet->orbitspeed < 0.0 ) {
                                        goto error;
                                }
                                break;
                        case aphelion:
                                newPlanet->aphelion = extractAphelion( topLevel );

                                if ( newPlanet->aphelion < 0.0 ) {
                                        goto error;
                                }
                                break;
                        case perihelion:
                                newPlanet->perihelion = extractPerihelion( topLevel );

                                if ( newPlanet->perihelion < 0.0 ) {
                                        goto error;
                                }

                                break;
                        case radius:
                                newPlanet->radius = extractRadius( topLevel );

                                if ( newPlanet->radius < 0.0 ) {
                                        goto error;
                                }
                                break;

                        case eradius:
                                newPlanet->eradius = extractERadius( topLevel );

                                if ( newPlanet->eradius < 0.0 ) {
                                        goto error;
                                }
                                break;
                        case mass:
                                newPlanet->mass = extractMass( topLevel );

                                if ( newPlanet->mass < 0.0 ) {
                                        goto error;
                                }

                                break;

                        case gravity:
                                newPlanet->gravity = extractGravity( topLevel );

                                if ( newPlanet->gravity < 0.0 ) {
                                        goto error;
                                }

                                break;
                        case country:
                                if ( newPlanet->country_count >= COUNTRYMAX ) {
                                        printf("!!Only @d countries allowed\n", COUNTRYMAX);
                                        goto error;
                                }

                                newPlanet->countries[ newPlanet->country_count] = countryTopLevel(topLevel);

                                if (newPlanet->countries[ newPlanet->country_count ] == NULL ) {
                                        goto error;
                                }

                                newPlanet->country_count++;
                                break;

                        default:
                                printf("Not allowed under Planet\n", fl);
                                goto error;
                                break;
                };


                getIndex( topLevel, &lastGood );
                fl = pullNextElementName( topLevel );

        }

        /// Since no more valid elements need to be parsed, check the closing element
        skipWhiteSpace( topLevel );

        if ( !atChar( topLevel, '{' ) ) {
                printf("!!Closing value failed for Planet\n");
                goto error;
        }

        /// Skip the open brace
        if ( incChar( topLevel ) < 0 ) {
                goto error;
        }

        skipWhiteSpace( topLevel );

        if ( !atChar( topLevel, '#' ) ) {
                printf("!!Malformed closing element\n");
                goto error;
        }

        /// Skip past #
        if ( incChar( topLevel ) == -1 ) {
                goto error;
        }

        getIndex( topLevel, &temp_index );

        endIndex = skipAlpha( topLevel );

        if ( endIndex == -1 ) {
                endIndex = 0;
                goto error;
        }

        if ( temp_index == endIndex ) {
                goto error;
        }

        fl = copyData( topLevel, temp_index, endIndex );

        if ( fl == NULL ) {
                goto error;
        }

        if ( strcmp( fl, "Planet") != 0 ) {
                printf("!!Closing element malformed\n");
                deallocate( fl, (endIndex-temp_index) + 1 );
                goto error;
        }

        deallocate(fl, (endIndex-temp_index) + 1 );

        skipWhiteSpace( topLevel );

        if ( !atChar( topLevel, '}' ) ) {
                printf("!!Failed to find final closing brace\n");
                goto error;
        }

        incChar(topLevel);
	
        goto end;

error:
        topLevel->index = lastGood;

        printf("!!Error at: @s\n", topLevel->buffer + topLevel->index);

	if ( newPlanet != NULL ) {
		freePlanet( newPlanet );
		newPlanet = NULL;
	}

end:
        return newPlanet;
}


/**
 * Parse the Period element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the double value or -1.0 on failure. Period should never be negative.
 **/
double extractPeriod( pstring str )
{
	char *temp = NULL;
	double period = -1.0;
	int start = 0;
	int end = 0;

	/// These will be used specifically for the data
	int ps = 0;
	int pe = 0;

	if (str == NULL ) {
		return period;
	}

	skipWhiteSpace(str);

	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate opening brace\n");
		return period;
	}

	/// Skip past the curly brace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip opening brace\n");
		return period;
	}

	/// Skip any additional whitespace
	start = skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the element id\n");
		return period;
	}

	/// Copy the element id from the string
	temp = copyData( str, start, end );

	if ( temp == NULL ) {
		printf("!!Copy from @d to @d failed\n", start, end);
		return -1.0;
	}

	/// If the element id is not "Period" then this is the wrong function
	if ( strcmp( temp, "Period") != 0 ) {
		printf("!!Element id is not \"Period\"\n");
		deallocate( temp, strlen(temp) + 1 );
		temp = NULL;
		return period;
	}

	/// The buffer is no longer needed so free it
	deallocate(temp, strlen(temp) + 1);

	/// Skip to the end of the element id
	skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate initial closing brace\n");
		return -1.0;
	}

	/// Skip the closing brace as well as any whitespace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip initial closing brace\n");
		return period;
	}

	skipWhiteSpace( str );

	/// Copy the start index to store the data
	getIndex( str, &ps );

	/// The period data must be a float
	pe = skipFloat( str );

	if ( pe == -1 ) {
		printf("!!Failed to locate the end of the period data\n");
		return end;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate the final opening brace\n");
		return -1.0;
	}

	/// Skip past the brace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip the final opening brace\n");
		return period;
	}
	
	skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !atChar( str, '#' ) ) {
		printf("!!Failed to locate the closing mark\n");		
		return -1.0;
	}

	/// Skip past the # but save the start
	start = skipLength( str, 1 );

	if ( start == -1 ) {
		printf("!!Failed to skip closing mark\n");
		return period;
	}

	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the closing element id\n");
		return -1.0;
	}
	
	temp = copyData( str, start, end );
#ifdef PATCHED
	if ( temp == NULL ) {
		return -1.0;
	}
#endif

	if ( strcmp( temp, "Period") != 0 ) {
		printf("!!Invalid closing element id: @s\n", temp);
		deallocate(temp, strlen(temp)+1);
		return period;
	}

	deallocate(temp, strlen(temp)+1);

	skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate final closing brace\n");
		return -1.0;
	}

	/// Skip past the closing brace
	skipLength( str, 1 );
		
	/// Copy the name element data
	temp = copyData( str, ps, pe );

	if ( temp == NULL ) {
		printf("!!Failed to copy period data\n");
		return -1;
	}

	period = atof( temp );

	deallocate( temp, strlen(temp) + 1 );

	return period;
}

/**
 * Parse the OrbitSpeed element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the double value or -1.0 on failure. Orbit speed should never be negative.
 **/
double extractOrbitSpeed( pstring str )
{
	char *temp = NULL;
	double speed = -1.0;
	register int start = 0;
	register int end = 0;
	int ss = 0;
	int se = 0;

	if (str == NULL ) {
		goto reterrvalue;	
	}

	start = skipWhiteSpace(str);

	if ( !(atChar( str, '{' ) & 1) ) {
		printf("!!Failed to locate opening brace\n");
		goto reterrspeed;
	}

	/// Skip past the curly brace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip opening brace\n");
		return speed;
	}

	/// Skip any additional whitespace
	start = skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the element id\n");
		goto reterrvalue;
	}

	/// Copy the element id from the string
	temp = copyData( str, start, end );

	if ( temp == NULL ) {
		printf("!!Copy from @d to @d failed\n", start, end);
		return -1.0;
	}

	/// If the element id is not "OrbitSpeed" then this is the wrong function
	if ( strcmp( temp, "OrbitSpeed") != 0 ) {
		printf("!!Element id is not \"OrbitSpeed\"\n");
		bzero( temp, strlen(temp) );
		deallocate( temp, strlen(temp) + 1 );
		temp = NULL;
		goto reterrvalue;
	}

	/// The buffer is no longer needed so free it
	bzero( temp, strlen(temp) + 1 );
	deallocate(temp, strlen(temp) + 1);

	/// Skip to the end of the element id
	skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate initial closing brace\n");
		goto reterrspeed;
	}

	/// Skip the closing brace as well as any whitespace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip initial closing brace\n");
		goto retspeed;
	}

	skipWhiteSpace( str );

	/// Copy the start index to store the data
	ss = str->index;

	/// The period data must be a float
	se = skipFloat( str );

	if (se == -1 ) {
		printf("!!Failed to locate the end of the period data\n");
		return -1.0;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate the final opening brace\n");
		goto reterrvalue;
	}

	/// Skip past the brace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip the final opening brace\n");
		goto reterrspeed;
	}
	
	skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !atChar( str, '#' ) ) {
		printf("!!Failed to locate the closing mark\n");		
		return -1.0;
	}

	/// Skip past the # but save the start
	start = skipLength( str, 1 );

	if ( start == -1 ) {
		printf("!!Failed to skip closing mark\n");
		goto reterrvalue;
	}

	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the closing element id\n");
		return -1.0;
	}
	
	temp = copyData( str, start, end );

#ifdef PATCHED
	if ( temp == NULL ) {
		return -1.0;
	}
#endif

	if ( strcmp( temp, "OrbitSpeed") != 0 ) {
		printf("!!Invalid closing element id: @s\n", temp);
		bzero(temp, strlen(temp) + 1 );
		deallocate(temp, strlen(temp)+1);
		return -1.0;
	}

	bzero( temp, strlen(temp) + 1 );
	deallocate(temp, strlen(temp)+1);

	skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate final closing brace\n");
		goto reterrspeed;
	}

	/// Skip past the closing brace
	skipLength( str, 1 );
		
	/// Copy the name element data
	temp = copyData( str, ss, se );

	if ( temp == NULL ) {
		printf("!!Failed to copy period data\n");
		goto retspeed;
	}

	speed = atof( temp );

	deallocate( temp, strlen(temp) + 1 );

	goto retspeed;

reterrvalue:
	return -1.0; 

reterrspeed:
	speed = -1.0;
	return speed;

retspeed:
	return speed;
}

/**
 * Parse the Aphelion element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the double value or -1.0 on failure. Aphelion should never be negative.
 **/
double extractAphelion( pstring str )
{
	char *temp = NULL;
	double aphelion = -1.0;
	int start = 0;
	int end = 0;

	/// These will be used specifically for the data
	int ps = 0;
	int pe = 0;

	if (str == NULL ) {
		return -1.0;
	}

	start = skipWhiteSpace(str);

	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate opening brace\n");
		return aphelion;
	}

	/// Skip past the curly brace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip opening brace\n");
		return aphelion;
	}

	/// Skip any additional whitespace
	start = skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the element id\n");
		return aphelion;
	}

	/// Copy the element id from the string
	temp = copyData( str, start, end );

	if ( temp == NULL ) {
		printf("!!Copy from @d to @d failed\n", start, end);
		return -1.0;
	}

	/// If the element id is not "Aphelion" then this is the wrong function
	if ( strcmp( temp, "Aphelion") != 0 ) {
		printf("!!Element id is not \"Aphelion\"\n");
		deallocate( temp, strlen(temp) + 1 );
		temp = NULL;
		return aphelion;
	}

	/// The buffer is no longer needed so free it
	deallocate(temp, strlen(temp) + 1);

	/// Skip to the end of the element id
	skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate initial closing brace\n");
		return -1.0;
	}

	/// Skip the closing brace as well as any whitespace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip initial closing brace\n");
		return aphelion;
	}

	skipWhiteSpace( str );

	/// Copy the start index to store the data
	getIndex( str, &ps );

	/// The period data must be a float
	pe = skipFloat( str );

	if ( pe == -1 ) {
		printf("!!Failed to locate the end of the period data\n");
		return aphelion;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate the final opening brace\n");
		return -1.0;
	}

	/// Skip past the brace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip the final opening brace\n");
		return aphelion;
	}
	
	skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !atChar( str, '#' ) ) {
		printf("!!Failed to locate the closing mark\n");		
		return -1.0;
	}

	/// Skip past the # but save the start
	start = skipLength( str, 1 );

	if ( start == -1 ) {
		printf("!!Failed to skip closing mark\n");
		return aphelion;
	}

	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the closing element id\n");
		return -1.0;
	}
	
	temp = copyData( str, start, end );

#ifdef PATCHED
	if ( temp == NULL ) {
		return -1.0;
	}
#endif

	if ( strcmp( temp, "Aphelion") != 0 ) {
		printf("!!Invalid closing element id: @s\n", temp);
		deallocate(temp, strlen(temp)+1);
		return aphelion;
	}

	deallocate(temp, strlen(temp)+1);

	skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate final closing brace\n");
		return -1.0;
	}

	/// Skip past the closing brace
	skipLength( str, 1 );
		
	/// Copy the name element data
	temp = copyData( str, ps, pe );

	if ( temp == NULL ) {
		printf("!!Failed to copy period data\n");
		return -1;
	}

	aphelion = atof( temp );

	deallocate( temp, strlen(temp) + 1 );

	return aphelion;
}

/**
 * Parse the Perihelion element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the double value or -1.0 on failure. Perihelion should never be negative.
 **/
double extractPerihelion( pstring str )
{
	char *temp = NULL;
	double perihelion = -1.0;
	int start = 0;
	int end = 0;

	/// These will be used specifically for the data
	int ps = 0;
	int pe = 0;

	if (str == NULL ) {
		return -1.0;
	}

	start = skipWhiteSpace(str);

	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate opening brace\n");
		return perihelion;
	}

	/// Skip past the curly brace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip opening brace\n");
		return perihelion;
	}

	/// Skip any additional whitespace
	start = skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the element id\n");
		return perihelion;
	}

	/// Copy the element id from the string
	temp = copyData( str, start, end );

	if ( temp == NULL ) {
		printf("!!Copy from @d to @d failed\n", start, end);
		return -1.0;
	}

	/// If the element id is not "Perihelion" then this is the wrong function
	if ( strcmp( temp, "Perihelion") != 0 ) {
		printf("!!Element id is not \"Perihelion\"\n");
		deallocate( temp, strlen(temp) + 1 );
		temp = NULL;
		return perihelion;
	}

	/// The buffer is no longer needed so free it
	deallocate(temp, strlen(temp) + 1);

	/// Skip to the end of the element id
	skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate initial closing brace\n");
		return -1.0;
	}

	/// Skip the closing brace as well as any whitespace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip initial closing brace\n");
		return perihelion;
	}

	skipWhiteSpace( str );

	/// Copy the start index to store the data
	getIndex( str, &ps );

	/// The period data must be a float
	pe = skipFloat( str );

	if ( pe == -1 ) {
		printf("!!Failed to locate the end of the perihelion data\n");
		return perihelion;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate the final opening brace\n");
		return -1.0;
	}

	/// Skip past the brace
	if ( incChar( str) == -1 ) {
		printf("!!Failed to skip the final opening brace\n");
		return perihelion;
	}
	
	skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !atChar( str, '#' ) ) {
		printf("!!Failed to locate the closing mark\n");		
		return -1.0;
	}

	/// Skip past the # but save the start
	start = skipLength( str, 1 );

	if ( start == -1 ) {
		printf("!!Failed to skip closing mark\n");
		return perihelion;
	}

	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the closing element id\n");
		return -1.0;
	}
	
	temp = copyData( str, start, end );

	if ( strcmp( temp, "Perihelion") != 0 ) {
		printf("!!Invalid closing element id: @s\n", temp);
		deallocate(temp, strlen(temp)+1);
		return perihelion;
	}

	deallocate(temp, strlen(temp)+1);

	skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate final closing brace\n");
		return -1.0;
	}

	/// Skip past the closing brace
	skipLength( str, 1 );
		
	/// Copy the name element data
	temp = copyData( str, ps, pe );

	if ( temp == NULL ) {
		printf("!!Failed to copy perihelion data\n");
		return -1;
	}

	perihelion = atof( temp );

	deallocate( temp, strlen(temp) + 1 );

	return perihelion;
}

/**
 * Parse the Radius element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the double value or -1.0 on failure. Radius should never be negative.
 **/
double extractRadius( pstring str )
{
	char *temp = NULL;
	double radius = -1.0;
	int start = 0;
	int end = 0;

	/// These will be used specifically for the data
	int rs = 0;
	int re = 0;

	if (str == NULL ) {
		return -1.0;
	}

	start = skipWhiteSpace(str);

	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate opening brace\n");
		return radius;
	}

	/// Skip past the curly brace
	if ( incChar( str ) == -1 ) {
		printf("!!Failed to skip opening brace\n");
		return radius;
	}

	/// Skip any additional whitespace
	start = skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the element id\n");
		return radius;
	}

	/// Copy the element id from the string
	temp = copyData( str, start, end );

	if ( temp == NULL ) {
		printf("!!Copy from @d to @d failed\n", start, end);
		return -1.0;
	}

	/// If the element id is not "Radius" then this is the wrong function
	if ( strcmp( temp, "Radius") != 0 ) {
		printf("!!Element id is not \"Radius\"\n");
		deallocate( temp, strlen(temp) + 1 );
		temp = NULL;
		return radius;
	}

	/// The buffer is no longer needed so free it
	deallocate(temp, strlen(temp) + 1);

	/// Skip to the end of the element id
	skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate initial closing brace\n");
		return -1.0;
	}

	/// Skip the closing brace as well as any whitespace
	if ( incChar( str) == -1 ) {
		printf("!!Failed to skip initial closing brace\n");
		return radius;
	}

	skipWhiteSpace( str );

	/// Copy the start index to store the data
	getIndex( str, &rs );

	/// The radius data must be a float
	re = skipFloat( str );

	if ( re == -1 ) {
		printf("!!Failed to locate the end of the radius data\n");
		return radius;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate the final opening brace\n");
		return -1.0;
	}

	/// Skip past the brace
	if ( incChar( str) == -1 ) {
		printf("!!Failed to skip the final opening brace\n");
		return radius;
	}
	
	skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !atChar( str, '#' ) ) {
		printf("!!Failed to locate the closing mark\n");		
		return -1.0;
	}

	/// Skip past the # but save the start
	start = incChar( str );

	if ( start == -1 ) {
		printf("!!Failed to skip closing mark\n");
		return radius;
	}

	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the closing element id\n");
		return -1.0;
	}
	
	temp = copyData( str, start, end );

	if ( strcmp( temp, "Radius") != 0 ) {
		printf("!!Invalid closing element id: @s\n", temp);
		deallocate(temp, strlen(temp)+1);
		return radius;
	}

	deallocate(temp, strlen(temp)+1);

	skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate final closing brace\n");
		return -1.0;
	}

	/// Skip past the closing brace
	skipLength( str, 1 );
		
	/// Copy the name element data
	temp = copyData( str, rs, re );

	if ( temp == NULL ) {
		printf("!!Failed to copy radius data\n");
		return -1.0;
	}

	radius = atof( temp );

	deallocate( temp, strlen(temp) + 1 );

	return radius;
}

/**
 * Parse the ERadius element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the double value or -1.0 on failure. ERadius should never be negative.
 **/
double extractERadius( pstring str )
{
	char *temp = NULL;
	double eradius = -1.0;
	int start = 0;
	int end = 0;

	/// These will be used specifically for the data
	int es = 0;
	int ee = 0;

	if (str == NULL ) {
		return -1.0;
	}

	start = skipWhiteSpace(str);

	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate opening brace\n");
		return eradius;
	}

	/// Skip past the curly brace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip opening brace\n");
		return eradius;
	}

	/// Skip any additional whitespace
	start = skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the element id\n");
		return eradius;
	}

	/// Copy the element id from the string
	temp = copyData( str, start, end );

	if ( temp == NULL ) {
		printf("!!Copy from @d to @d failed\n", start, end);
		return -1.0;
	}

	/// If the element id is not "ERadius" then this is the wrong function
	if ( strcmp( temp, "ERadius") != 0 ) {
		printf("!!Element id is not \"ERadius\"\n");
		deallocate( temp, strlen(temp) + 1 );
		temp = NULL;
		return eradius;
	}

	/// The buffer is no longer needed so free it
	deallocate(temp, strlen(temp) + 1);

	/// Skip to the end of the element id
	skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate initial closing brace\n");
		return -1.0;
	}

	/// Skip the closing brace as well as any whitespace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip initial closing brace\n");
		return eradius;
	}

	skipWhiteSpace( str );

	/// Copy the start index to store the data
	getIndex( str, &es );

	/// The eradius data must be a float
	ee = skipFloat( str );

	if ( ee == -1 ) {
		printf("!!Failed to locate the end of the eradius data\n");
		return eradius;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate the final opening brace\n");
		return -1.0;
	}

	/// Skip past the brace
	if ( incChar( str) == -1 ) {
		printf("!!Failed to skip the final opening brace\n");
		return eradius;
	}
	
	skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !atChar( str, '#' ) ) {
		printf("!!Failed to locate the closing mark\n");		
		return -1.0;
	}

	/// Skip past the # but save the start
	start = skipLength( str, 1 );

	if ( start == -1 ) {
		printf("!!Failed to skip closing mark\n");
		return eradius;
	}

	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the closing element id\n");
		return -1.0;
	}
	
	temp = copyData( str, start, end );

	if ( strcmp( temp, "ERadius") != 0 ) {
		printf("!!Invalid closing element id: @s\n", temp);
		deallocate(temp, strlen(temp)+1);
		return eradius;
	}

	deallocate(temp, strlen(temp)+1);

	skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate final closing brace\n");
		return -1.0;
	}

	/// Skip past the closing brace
	skipLength( str, 1 );
		
	/// Copy the eradius element data
	temp = copyData( str, es, ee );

	if ( temp == NULL ) {
		printf("!!Failed to copy eradius data\n");
		return -1;
	}

	eradius = atof( temp );

	deallocate( temp, strlen(temp) + 1 );

	return eradius;
}

/**
 * Parse the Mass element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the double value or -1.0 on failure. Mass should never be negative.
 **/
double extractMass( pstring str )
{
	char *temp = NULL;
	double mass = -1.0;
	int start = 0;
	int end = 0;

	/// These will be used specifically for the data
	int es = 0;
	int ee = 0;

	if (str == NULL ) {
		return -1.0;
	}

	start = skipWhiteSpace(str);

	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate opening brace\n");
		return mass;
	}

	/// Skip past the curly brace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip opening brace\n");
		return mass;
	}

	/// Skip any additional whitespace
	start = skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the element id\n");
		return mass;
	}

	/// Copy the element id from the string
	temp = copyData( str, start, end );

	if ( temp == NULL ) {
		printf("!!Copy from @d to @d failed\n", start, end);
		return -1.0;
	}

	/// If the element id is not "Mass" then this is the wrong function
	if ( strcmp( temp, "Mass") != 0 ) {
		printf("!!Element id is not \"Mass\"\n");
		deallocate( temp, strlen(temp) + 1 );
		temp = NULL;
		return mass;
	}

	/// The buffer is no longer needed so free it
	deallocate(temp, strlen(temp) + 1);

	/// Skip to the end of the element id
	skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate initial closing brace\n");
		return -1.0;
	}

	/// Skip the closing brace as well as any whitespace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip initial closing brace\n");
		return mass;
	}

	skipWhiteSpace( str );

	/// Copy the start index to store the data
	getIndex( str, &es );

	/// The mass data must be a float
	ee = skipFloat( str );

	if ( ee == -1 ) {
		printf("!!Failed to locate the end of the mass data\n");
		return mass;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate the final opening brace\n");
		return -1.0;
	}

	/// Skip past the brace
	if ( incChar( str) == -1 ) {
		printf("!!Failed to skip the final opening brace\n");
		return mass;
	}
	
	skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !atChar( str, '#' ) ) {
		printf("!!Failed to locate the closing mark\n");		
		return -1.0;
	}

	/// Skip past the # but save the start
	start = skipLength( str, 1 );

	if ( start == -1 ) {
		printf("!!Failed to skip closing mark\n");
		return mass;
	}

	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the closing element id\n");
		return -1.0;
	}
	
	temp = copyData( str, start, end );

#ifdef PATCHED
	if ( temp == NULL ) {
		return -1.0;
	}
#endif

	if ( strcmp( temp, "Mass") != 0 ) {
		printf("!!Invalid closing element id: @s\n", temp);
		deallocate(temp, strlen(temp)+1);
		return mass;
	}

	deallocate(temp, strlen(temp)+1);

	skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate final closing brace\n");
		return -1.0;
	}

	/// Skip past the closing brace
	skipLength( str, 1 );
		
	/// Copy the mass element data
	temp = copyData( str, es, ee );

	if ( temp == NULL ) {
		printf("!!Failed to copy mass data\n");
		return -1;
	}

	mass = atof( temp );

	deallocate( temp, strlen(temp) + 1 );

	return mass;
}

/**
 * Parse the Gravity element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the double value or -1.0 on failure. Gravity should never be negative.
 **/
double extractGravity( pstring str )
{
	char *temp = NULL;
	double gravity = -1.0;
	int start = 0;
	int end = 0;

	/// These will be used specifically for the data
	int es = 0;
	int ee = 0;

	if (str == NULL ) {
		return -1.0;
	}

	start = skipWhiteSpace(str);

	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate opening brace\n");
		return gravity;
	}

	/// Skip past the curly brace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip opening brace\n");
		return gravity;
	}

	/// Skip any additional whitespace
	start = skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the element id\n");
		return gravity;
	}

	/// Copy the element id from the string
	temp = copyData( str, start, end );

	if ( temp == NULL ) {
		printf("!!Copy from @d to @d failed\n", start, end);
		return -1.0;
	}

	/// If the element id is not "Gravity" then this is the wrong function
	if ( strcmp( temp, "Gravity") != 0 ) {
		printf("!!Element id is not \"Gravity\"\n");
		deallocate( temp, strlen(temp) + 1 );
		temp = NULL;
		return gravity;
	}

	/// The buffer is no longer needed so free it
	deallocate(temp, strlen(temp) + 1);

	/// Skip to the end of the element id
	skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate initial closing brace\n");
		return -1.0;
	}

	/// Skip the closing brace as well as any whitespace
	if ( skipLength( str, 1 ) == -1 ) {
		printf("!!Failed to skip initial closing brace\n");
		return gravity;
	}

	skipWhiteSpace( str );

	/// Copy the start index to store the data
	getIndex( str, &es );

	/// The gravity data must be a float
	ee = skipFloat( str );

	if ( ee == -1 ) {
		printf("!!Failed to locate the end of the gravity data\n");
		return gravity;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !atChar( str, '{' ) ) {
		printf("!!Failed to locate the final opening brace\n");
		return -1.0;
	}

	/// Skip past the brace
	if ( incChar( str) == -1 ) {
		printf("!!Failed to skip the final opening brace\n");
		return gravity;
	}
	
	skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !atChar( str, '#' ) ) {
		printf("!!Failed to locate the closing mark\n");		
		return -1.0;
	}

	/// Skip past the # but save the start
	start = skipLength( str, 1 );

	if ( start == -1 ) {
		printf("!!Failed to skip closing mark\n");
		return gravity;
	}

	end = skipToNonAlphaNum( str );

	if ( end == -1 ) {
		printf("!!Failed to locate the end of the closing element id\n");
		return -1.0;
	}
	
	temp = copyData( str, start, end );

	if ( strcmp( temp, "Gravity") != 0 ) {
		printf("!!Invalid closing element id: @s\n", temp);
		deallocate(temp, strlen(temp)+1);
		return gravity;
	}

	deallocate(temp, strlen(temp)+1);

	skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !atChar( str, '}' ) ) {
		printf("!!Failed to locate final closing brace\n");
		return -1.0;
	}

	/// Skip past the closing brace
	skipLength( str, 1 );
		
	/// Copy the gravity element data
	temp = copyData( str, es, ee );

	if ( temp == NULL ) {
		printf("!!Failed to copy gravity data\n");
		return -1;
	}

	gravity = atof( temp );

	deallocate( temp, strlen(temp) + 1 );

	return gravity;
}

