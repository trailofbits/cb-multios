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

#include "cgc_planetParsers.h"

/**
 * Menu to manage a planet
 * @param pl Pointer to the planet to manage
 * @return Returns 0 if planet pointer should be NULL 1 otherwise
 **/
int cgc_planetMenu( pPlanet pl )
{
	int choice = 0;
	char selection[30];
	cgc_size_t length = 0;
	pCountry pc = NULL;

	if ( pl == NULL ) {
		return 0;
	}

	while ( 1 ) {
		cgc_bzero(selection, 30);

		cgc_printf("\nPlanet: @s\n", pl->name);
		cgc_printf("1) Display planet information\n");
		cgc_printf("2) Set Period\n");
		cgc_printf("3) Set Orbit Speed\n");
		cgc_printf("4) Set Aphelion\n");
		cgc_printf("5) Set Perihelion\n");
		cgc_printf("6) Set Mean Radius\n");
		cgc_printf("7) Set Equatorial Radius\n");
		cgc_printf("8) Set Mass\n");
		cgc_printf("9) Set Gravity\n");
		cgc_printf("10) Set population\n");
		cgc_printf("11) Add Country\n");
		cgc_printf("12) Select country\n");
		cgc_printf("13) Delete Planet and exit menu\n");
		cgc_printf("14) Exit menu\n");
		cgc_printf("Selection: ");

		cgc_receive_until(selection, '\n', 3);
		choice = cgc_atoi( selection );

		switch ( choice ) {
			case 1:
				cgc_printPlanetInfo( pl );
				break;
			case 2:
				cgc_printf("\n-> ");
				cgc_receive_until( selection, '\n', 10);
				pl->period = cgc_atof(selection);
				break;
			case 3:
				cgc_printf("\n-> ");
				cgc_receive_until(selection, '\n', 10);
				pl->orbitspeed = cgc_atof(selection);
				break;
			case 4:
				cgc_printf("\n-> ");
				cgc_receive_until( selection, '\n', 10);
				pl->aphelion = cgc_atof(selection);
				break;
			case 5:
				cgc_printf("\n-> ");
				cgc_receive_until( selection, '\n', 10);
				pl->perihelion = cgc_atof(selection);
				break;
			case 6:
				cgc_printf("\n-> ");
				cgc_receive_until( selection, '\n', 10);
				pl->radius = cgc_atof(selection);
				break;
			case 7:
				cgc_printf("\n-> ");
				cgc_receive_until( selection, '\n', 10);
				pl->eradius = cgc_atof(selection);
				break;
			case 8:
				cgc_printf("\n-> ");
				cgc_receive_until( selection, '\n', 10);
				pl->mass = cgc_atof(selection);
				break;
			case 9:
				cgc_printf("\n-> ");
				cgc_receive_until( selection, '\n', 10);
				pl->gravity = cgc_atof(selection);
				break;
			case 10:
				cgc_printf("\n-> ");
				cgc_receive_until( selection, '\n', 10);
				pl->population = cgc_atoi(selection);
				break;
			case 11:
				if ( pl->country_count >= COUNTRYMAX ) {
					cgc_printf("Too many countries\n");
					continue;
				}

				cgc_printf("\nNew Name: ");
				cgc_receive_until(selection, '\n', 19);

				choice = 0;
				while ( choice < COUNTRYMAX ) {
					if ( pl->countries[choice] == NULL ) {
						break;
					}
					choice++;
				}

				if ( choice == COUNTRYMAX ) {
					cgc_printf("!!No country slots\n");
					continue;
				}

				if ( cgc_allocate( sizeof(Country), 0, (void**)(&pc) ) != 0 ) {
					cgc_printf("!!Failed to allocate structure\n");
					continue;
				}

				cgc_initCountry( pc );

				pl->countries[choice] = pc;

				length = 0;
	
				while ( cgc_isalnum( selection[length] ) ) {
					pc->name[length] = selection[length];
					length++;
				}
				pc->name[length] = '\x00';

				pl->country_count++;
				break;
			case 12:
				cgc_printf("\nCountries:\n");
				for ( choice = 0; choice < pl->country_count; choice++ ) {
					if ( pl->countries[choice] != NULL ) {
						cgc_printf("@d) @s\n", choice + 1, pl->countries[choice]);
					}
				}

				cgc_bzero(selection, 30);
				cgc_printf("\n-> ");
				cgc_receive_until( selection, '\n', 3 );

				choice = cgc_atoi(selection);

				if ( choice < 1 || choice > COUNTRYMAX) {
					cgc_printf("Invalid choice...\n");
					continue;
				} else if ( pl->countries[ choice-1] == NULL ) {
					cgc_printf("Invalid choice...\n");
					continue;
				}

				if ( cgc_countryMenu( pl->countries[choice-1]) == 0 ) {
					pl->countries[choice-1] = NULL;
					pl->country_count--;
				}
				break;
			case 13:
				cgc_freePlanet( pl );
				return 0;
				break;
			case 14:
				return 1;
				break;
			default:
				cgc_printf("Invalid...\n");
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
void cgc_freePlanet( pPlanet pl )
{
	int index = 0;

	if ( pl == NULL ) {
		return;
	}

	/// Free all of the associated countries
	while ( index < COUNTRYMAX ) {
		if ( pl->countries[ index] != NULL ) {

			/// This function also frees the pointer so freePlanet does not have to.
			cgc_freeCountry( pl->countries[index] );
			pl->countries[index] = NULL;

		}

		index++;
	}
	
	cgc_deallocate( pl, sizeof(Planet) );

	return;
}

/**
 * Print the planet information
 * @param pl Pointer to the planet structure
 * @return Returns nothing
 **/
void cgc_printPlanetInfo( pPlanet pl )
{
        int index = 0;

        if ( pl == NULL ) {
                return;
        }

        if ( pl->name[0] == '\x00' ) {
                cgc_printf("Name: Unknown\n");
        } else {
                cgc_printf("Name: @s\n", pl->name );
        }

        if ( pl->population >= 0 ) {
                cgc_printf("\tPopulation: @d\n", pl->population);
        }

        if ( pl->period >= 0.0 ) {
                cgc_printf("\tPeriod: @f\n", pl->period);
        }

        if ( pl->orbitspeed >= 0.0 ) {
                cgc_printf("\tOrbit Speed: @f\n", pl->orbitspeed);
        }

        if ( pl->aphelion >= 0.0 ) {
                cgc_printf("\tAphelion: @f\n", pl->aphelion);
        }

        if ( pl->perihelion >= 0.0 ) {
                cgc_printf("\tPerihelion: @f\n", pl->perihelion);
        }

        if ( pl->radius >= 0.0 ) {
                cgc_printf("\tRadius: @f\n", pl->radius);
        }

        if ( pl->eradius >= 0.0 ) {
                cgc_printf("\tERadius: @f\n", pl->eradius);
        }
        if ( pl->mass >= 0.0 ) {
                cgc_printf("\tMass: @f\n", pl->mass);
        }
	
	if ( pl->gravity >= 0.0 ) {
		cgc_printf("\tGravity: @f\n", pl->gravity);
	}

	/// Print each country's information
        while ( index < COUNTRYMAX ) {
                if ( pl->countries[ index ] != NULL ) {
                        cgc_printCountryInfo( pl->countries[index] );
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
void cgc_initPlanet( pPlanet pl )
{
        register int index = 0;

        if ( pl == NULL ) {
                return;
        }

        cgc_bzero( pl->name, 20 );
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
pPlanet cgc_planetTopLevel( pstring topLevel )
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
        cgc_skipWhiteSpace( topLevel );

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

	cgc_skipWhiteSpace( topLevel );

        /// Allocate a new planet structure
        if ( cgc_allocate( sizeof(Planet), 0, (void**)&newPlanet) != 0 ) {
                goto end;
        }

        cgc_initPlanet( newPlanet );

        /// Extract the next element name
        fl = cgc_pullNextElementName( topLevel );

        cgc_getIndex( topLevel, &lastGood);

        while ( fl != NULL ) {
                /// Convert the element name
                el = cgc_elementNameToEnum( fl );

                /// The name is no longer needed so free it
                cgc_deallocate( fl, cgc_strlen(fl) + 1 );

                switch (el) {
                        case name:
                                fl = cgc_extractName( topLevel );

                                if ( fl == NULL ) {
                                        goto error;
                                }

				cgc_bzero( newPlanet->name, 20 );
                                cgc_strncpy( newPlanet->name, fl, 19 );

                                cgc_deallocate(fl, cgc_strlen(fl) + 1 );
                                fl = NULL;

                                break;
                        case population:
                                newPlanet->population = cgc_extractPopulation( topLevel );

                                if ( newPlanet->population < 0 ) {
                                        goto error;
                                }

                                break;
                        case period:
                                /// Extract period and check result
                                newPlanet->period = cgc_extractPeriod( topLevel );
                                if ( newPlanet->period < 0.0 ) {
                                        goto error;
                                }

                                break;
                        case orbitspeed:
                                newPlanet->orbitspeed = cgc_extractOrbitSpeed( topLevel );

                                if ( newPlanet->orbitspeed < 0.0 ) {
                                        goto error;
                                }
                                break;
                        case aphelion:
                                newPlanet->aphelion = cgc_extractAphelion( topLevel );

                                if ( newPlanet->aphelion < 0.0 ) {
                                        goto error;
                                }
                                break;
                        case perihelion:
                                newPlanet->perihelion = cgc_extractPerihelion( topLevel );

                                if ( newPlanet->perihelion < 0.0 ) {
                                        goto error;
                                }

                                break;
                        case radius:
                                newPlanet->radius = cgc_extractRadius( topLevel );

                                if ( newPlanet->radius < 0.0 ) {
                                        goto error;
                                }
                                break;

                        case eradius:
                                newPlanet->eradius = cgc_extractERadius( topLevel );

                                if ( newPlanet->eradius < 0.0 ) {
                                        goto error;
                                }
                                break;
                        case mass:
                                newPlanet->mass = cgc_extractMass( topLevel );

                                if ( newPlanet->mass < 0.0 ) {
                                        goto error;
                                }

                                break;

                        case gravity:
                                newPlanet->gravity = cgc_extractGravity( topLevel );

                                if ( newPlanet->gravity < 0.0 ) {
                                        goto error;
                                }

                                break;
                        case country:
                                if ( newPlanet->country_count >= COUNTRYMAX ) {
                                        cgc_printf("!!Only @d countries allowed\n", COUNTRYMAX);
                                        goto error;
                                }

                                newPlanet->countries[ newPlanet->country_count] = cgc_countryTopLevel(topLevel);

                                if (newPlanet->countries[ newPlanet->country_count ] == NULL ) {
                                        goto error;
                                }

                                newPlanet->country_count++;
                                break;

                        default:
                                cgc_printf("Not allowed under Planet\n", fl);
                                goto error;
                                break;
                };


                cgc_getIndex( topLevel, &lastGood );
                fl = cgc_pullNextElementName( topLevel );

        }

        /// Since no more valid elements need to be parsed, check the closing element
        cgc_skipWhiteSpace( topLevel );

        if ( !cgc_atChar( topLevel, '{' ) ) {
                cgc_printf("!!Closing value failed for Planet\n");
                goto error;
        }

        /// Skip the open brace
        if ( cgc_incChar( topLevel ) < 0 ) {
                goto error;
        }

        cgc_skipWhiteSpace( topLevel );

        if ( !cgc_atChar( topLevel, '#' ) ) {
                cgc_printf("!!Malformed closing element\n");
                goto error;
        }

        /// Skip past #
        if ( cgc_incChar( topLevel ) == -1 ) {
                goto error;
        }

        cgc_getIndex( topLevel, &temp_index );

        endIndex = cgc_skipAlpha( topLevel );

        if ( endIndex == -1 ) {
                endIndex = 0;
                goto error;
        }

        if ( temp_index == endIndex ) {
                goto error;
        }

        fl = cgc_copyData( topLevel, temp_index, endIndex );

        if ( fl == NULL ) {
                goto error;
        }

        if ( cgc_strcmp( fl, "Planet") != 0 ) {
                cgc_printf("!!Closing element malformed\n");
                cgc_deallocate( fl, (endIndex-temp_index) + 1 );
                goto error;
        }

        cgc_deallocate(fl, (endIndex-temp_index) + 1 );

        cgc_skipWhiteSpace( topLevel );

        if ( !cgc_atChar( topLevel, '}' ) ) {
                cgc_printf("!!Failed to find final closing brace\n");
                goto error;
        }

        cgc_incChar(topLevel);
	
        goto end;

error:
        topLevel->index = lastGood;

        cgc_printf("!!Error at: @s\n", topLevel->buffer + topLevel->index);

	if ( newPlanet != NULL ) {
		cgc_freePlanet( newPlanet );
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
double cgc_extractPeriod( pstring str )
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

	cgc_skipWhiteSpace(str);

	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate opening brace\n");
		return period;
	}

	/// Skip past the curly brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip opening brace\n");
		return period;
	}

	/// Skip any additional whitespace
	start = cgc_skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the element id\n");
		return period;
	}

	/// Copy the element id from the string
	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		cgc_printf("!!Copy from @d to @d failed\n", start, end);
		return -1.0;
	}

	/// If the element id is not "Period" then this is the wrong function
	if ( cgc_strcmp( temp, "Period") != 0 ) {
		cgc_printf("!!Element id is not \"Period\"\n");
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
		temp = NULL;
		return period;
	}

	/// The buffer is no longer needed so free it
	cgc_deallocate(temp, cgc_strlen(temp) + 1);

	/// Skip to the end of the element id
	cgc_skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate initial closing brace\n");
		return -1.0;
	}

	/// Skip the closing brace as well as any whitespace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip initial closing brace\n");
		return period;
	}

	cgc_skipWhiteSpace( str );

	/// Copy the start index to store the data
	cgc_getIndex( str, &ps );

	/// The period data must be a float
	pe = cgc_skipFloat( str );

	if ( pe == -1 ) {
		cgc_printf("!!Failed to locate the end of the period data\n");
		return end;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	cgc_skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate the final opening brace\n");
		return -1.0;
	}

	/// Skip past the brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip the final opening brace\n");
		return period;
	}
	
	cgc_skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !cgc_atChar( str, '#' ) ) {
		cgc_printf("!!Failed to locate the closing mark\n");		
		return -1.0;
	}

	/// Skip past the # but save the start
	start = cgc_skipLength( str, 1 );

	if ( start == -1 ) {
		cgc_printf("!!Failed to skip closing mark\n");
		return period;
	}

	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the closing element id\n");
		return -1.0;
	}
	
	temp = cgc_copyData( str, start, end );
#ifdef PATCHED
	if ( temp == NULL ) {
		return -1.0;
	}
#endif

	if ( cgc_strcmp( temp, "Period") != 0 ) {
		cgc_printf("!!Invalid closing element id: @s\n", temp);
		cgc_deallocate(temp, cgc_strlen(temp)+1);
		return period;
	}

	cgc_deallocate(temp, cgc_strlen(temp)+1);

	cgc_skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate final closing brace\n");
		return -1.0;
	}

	/// Skip past the closing brace
	cgc_skipLength( str, 1 );
		
	/// Copy the name element data
	temp = cgc_copyData( str, ps, pe );

	if ( temp == NULL ) {
		cgc_printf("!!Failed to copy period data\n");
		return -1;
	}

	period = cgc_atof( temp );

	cgc_deallocate( temp, cgc_strlen(temp) + 1 );

	return period;
}

/**
 * Parse the OrbitSpeed element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the double value or -1.0 on failure. Orbit speed should never be negative.
 **/
double cgc_extractOrbitSpeed( pstring str )
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

	start = cgc_skipWhiteSpace(str);

	if ( !(cgc_atChar( str, '{' ) & 1) ) {
		cgc_printf("!!Failed to locate opening brace\n");
		goto reterrspeed;
	}

	/// Skip past the curly brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip opening brace\n");
		return speed;
	}

	/// Skip any additional whitespace
	start = cgc_skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the element id\n");
		goto reterrvalue;
	}

	/// Copy the element id from the string
	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		cgc_printf("!!Copy from @d to @d failed\n", start, end);
		return -1.0;
	}

	/// If the element id is not "OrbitSpeed" then this is the wrong function
	if ( cgc_strcmp( temp, "OrbitSpeed") != 0 ) {
		cgc_printf("!!Element id is not \"OrbitSpeed\"\n");
		cgc_bzero( temp, cgc_strlen(temp) );
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
		temp = NULL;
		goto reterrvalue;
	}

	/// The buffer is no longer needed so free it
	cgc_bzero( temp, cgc_strlen(temp) + 1 );
	cgc_deallocate(temp, cgc_strlen(temp) + 1);

	/// Skip to the end of the element id
	cgc_skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate initial closing brace\n");
		goto reterrspeed;
	}

	/// Skip the closing brace as well as any whitespace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip initial closing brace\n");
		goto retspeed;
	}

	cgc_skipWhiteSpace( str );

	/// Copy the start index to store the data
	ss = str->index;

	/// The period data must be a float
	se = cgc_skipFloat( str );

	if (se == -1 ) {
		cgc_printf("!!Failed to locate the end of the period data\n");
		return -1.0;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	cgc_skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate the final opening brace\n");
		goto reterrvalue;
	}

	/// Skip past the brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip the final opening brace\n");
		goto reterrspeed;
	}
	
	cgc_skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !cgc_atChar( str, '#' ) ) {
		cgc_printf("!!Failed to locate the closing mark\n");		
		return -1.0;
	}

	/// Skip past the # but save the start
	start = cgc_skipLength( str, 1 );

	if ( start == -1 ) {
		cgc_printf("!!Failed to skip closing mark\n");
		goto reterrvalue;
	}

	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the closing element id\n");
		return -1.0;
	}
	
	temp = cgc_copyData( str, start, end );

#ifdef PATCHED
	if ( temp == NULL ) {
		return -1.0;
	}
#endif

	if ( cgc_strcmp( temp, "OrbitSpeed") != 0 ) {
		cgc_printf("!!Invalid closing element id: @s\n", temp);
		cgc_bzero(temp, cgc_strlen(temp) + 1 );
		cgc_deallocate(temp, cgc_strlen(temp)+1);
		return -1.0;
	}

	cgc_bzero( temp, cgc_strlen(temp) + 1 );
	cgc_deallocate(temp, cgc_strlen(temp)+1);

	cgc_skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate final closing brace\n");
		goto reterrspeed;
	}

	/// Skip past the closing brace
	cgc_skipLength( str, 1 );
		
	/// Copy the name element data
	temp = cgc_copyData( str, ss, se );

	if ( temp == NULL ) {
		cgc_printf("!!Failed to copy period data\n");
		goto retspeed;
	}

	speed = cgc_atof( temp );

	cgc_deallocate( temp, cgc_strlen(temp) + 1 );

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
double cgc_extractAphelion( pstring str )
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

	start = cgc_skipWhiteSpace(str);

	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate opening brace\n");
		return aphelion;
	}

	/// Skip past the curly brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip opening brace\n");
		return aphelion;
	}

	/// Skip any additional whitespace
	start = cgc_skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the element id\n");
		return aphelion;
	}

	/// Copy the element id from the string
	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		cgc_printf("!!Copy from @d to @d failed\n", start, end);
		return -1.0;
	}

	/// If the element id is not "Aphelion" then this is the wrong function
	if ( cgc_strcmp( temp, "Aphelion") != 0 ) {
		cgc_printf("!!Element id is not \"Aphelion\"\n");
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
		temp = NULL;
		return aphelion;
	}

	/// The buffer is no longer needed so free it
	cgc_deallocate(temp, cgc_strlen(temp) + 1);

	/// Skip to the end of the element id
	cgc_skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate initial closing brace\n");
		return -1.0;
	}

	/// Skip the closing brace as well as any whitespace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip initial closing brace\n");
		return aphelion;
	}

	cgc_skipWhiteSpace( str );

	/// Copy the start index to store the data
	cgc_getIndex( str, &ps );

	/// The period data must be a float
	pe = cgc_skipFloat( str );

	if ( pe == -1 ) {
		cgc_printf("!!Failed to locate the end of the period data\n");
		return aphelion;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	cgc_skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate the final opening brace\n");
		return -1.0;
	}

	/// Skip past the brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip the final opening brace\n");
		return aphelion;
	}
	
	cgc_skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !cgc_atChar( str, '#' ) ) {
		cgc_printf("!!Failed to locate the closing mark\n");		
		return -1.0;
	}

	/// Skip past the # but save the start
	start = cgc_skipLength( str, 1 );

	if ( start == -1 ) {
		cgc_printf("!!Failed to skip closing mark\n");
		return aphelion;
	}

	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the closing element id\n");
		return -1.0;
	}
	
	temp = cgc_copyData( str, start, end );

#ifdef PATCHED
	if ( temp == NULL ) {
		return -1.0;
	}
#endif

	if ( cgc_strcmp( temp, "Aphelion") != 0 ) {
		cgc_printf("!!Invalid closing element id: @s\n", temp);
		cgc_deallocate(temp, cgc_strlen(temp)+1);
		return aphelion;
	}

	cgc_deallocate(temp, cgc_strlen(temp)+1);

	cgc_skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate final closing brace\n");
		return -1.0;
	}

	/// Skip past the closing brace
	cgc_skipLength( str, 1 );
		
	/// Copy the name element data
	temp = cgc_copyData( str, ps, pe );

	if ( temp == NULL ) {
		cgc_printf("!!Failed to copy period data\n");
		return -1;
	}

	aphelion = cgc_atof( temp );

	cgc_deallocate( temp, cgc_strlen(temp) + 1 );

	return aphelion;
}

/**
 * Parse the Perihelion element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the double value or -1.0 on failure. Perihelion should never be negative.
 **/
double cgc_extractPerihelion( pstring str )
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

	start = cgc_skipWhiteSpace(str);

	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate opening brace\n");
		return perihelion;
	}

	/// Skip past the curly brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip opening brace\n");
		return perihelion;
	}

	/// Skip any additional whitespace
	start = cgc_skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the element id\n");
		return perihelion;
	}

	/// Copy the element id from the string
	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		cgc_printf("!!Copy from @d to @d failed\n", start, end);
		return -1.0;
	}

	/// If the element id is not "Perihelion" then this is the wrong function
	if ( cgc_strcmp( temp, "Perihelion") != 0 ) {
		cgc_printf("!!Element id is not \"Perihelion\"\n");
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
		temp = NULL;
		return perihelion;
	}

	/// The buffer is no longer needed so free it
	cgc_deallocate(temp, cgc_strlen(temp) + 1);

	/// Skip to the end of the element id
	cgc_skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate initial closing brace\n");
		return -1.0;
	}

	/// Skip the closing brace as well as any whitespace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip initial closing brace\n");
		return perihelion;
	}

	cgc_skipWhiteSpace( str );

	/// Copy the start index to store the data
	cgc_getIndex( str, &ps );

	/// The period data must be a float
	pe = cgc_skipFloat( str );

	if ( pe == -1 ) {
		cgc_printf("!!Failed to locate the end of the perihelion data\n");
		return perihelion;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	cgc_skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate the final opening brace\n");
		return -1.0;
	}

	/// Skip past the brace
	if ( cgc_incChar( str) == -1 ) {
		cgc_printf("!!Failed to skip the final opening brace\n");
		return perihelion;
	}
	
	cgc_skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !cgc_atChar( str, '#' ) ) {
		cgc_printf("!!Failed to locate the closing mark\n");		
		return -1.0;
	}

	/// Skip past the # but save the start
	start = cgc_skipLength( str, 1 );

	if ( start == -1 ) {
		cgc_printf("!!Failed to skip closing mark\n");
		return perihelion;
	}

	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the closing element id\n");
		return -1.0;
	}
	
	temp = cgc_copyData( str, start, end );

	if ( cgc_strcmp( temp, "Perihelion") != 0 ) {
		cgc_printf("!!Invalid closing element id: @s\n", temp);
		cgc_deallocate(temp, cgc_strlen(temp)+1);
		return perihelion;
	}

	cgc_deallocate(temp, cgc_strlen(temp)+1);

	cgc_skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate final closing brace\n");
		return -1.0;
	}

	/// Skip past the closing brace
	cgc_skipLength( str, 1 );
		
	/// Copy the name element data
	temp = cgc_copyData( str, ps, pe );

	if ( temp == NULL ) {
		cgc_printf("!!Failed to copy perihelion data\n");
		return -1;
	}

	perihelion = cgc_atof( temp );

	cgc_deallocate( temp, cgc_strlen(temp) + 1 );

	return perihelion;
}

/**
 * Parse the Radius element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the double value or -1.0 on failure. Radius should never be negative.
 **/
double cgc_extractRadius( pstring str )
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

	start = cgc_skipWhiteSpace(str);

	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate opening brace\n");
		return radius;
	}

	/// Skip past the curly brace
	if ( cgc_incChar( str ) == -1 ) {
		cgc_printf("!!Failed to skip opening brace\n");
		return radius;
	}

	/// Skip any additional whitespace
	start = cgc_skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the element id\n");
		return radius;
	}

	/// Copy the element id from the string
	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		cgc_printf("!!Copy from @d to @d failed\n", start, end);
		return -1.0;
	}

	/// If the element id is not "Radius" then this is the wrong function
	if ( cgc_strcmp( temp, "Radius") != 0 ) {
		cgc_printf("!!Element id is not \"Radius\"\n");
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
		temp = NULL;
		return radius;
	}

	/// The buffer is no longer needed so free it
	cgc_deallocate(temp, cgc_strlen(temp) + 1);

	/// Skip to the end of the element id
	cgc_skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate initial closing brace\n");
		return -1.0;
	}

	/// Skip the closing brace as well as any whitespace
	if ( cgc_incChar( str) == -1 ) {
		cgc_printf("!!Failed to skip initial closing brace\n");
		return radius;
	}

	cgc_skipWhiteSpace( str );

	/// Copy the start index to store the data
	cgc_getIndex( str, &rs );

	/// The radius data must be a float
	re = cgc_skipFloat( str );

	if ( re == -1 ) {
		cgc_printf("!!Failed to locate the end of the radius data\n");
		return radius;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	cgc_skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate the final opening brace\n");
		return -1.0;
	}

	/// Skip past the brace
	if ( cgc_incChar( str) == -1 ) {
		cgc_printf("!!Failed to skip the final opening brace\n");
		return radius;
	}
	
	cgc_skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !cgc_atChar( str, '#' ) ) {
		cgc_printf("!!Failed to locate the closing mark\n");		
		return -1.0;
	}

	/// Skip past the # but save the start
	start = cgc_incChar( str );

	if ( start == -1 ) {
		cgc_printf("!!Failed to skip closing mark\n");
		return radius;
	}

	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the closing element id\n");
		return -1.0;
	}
	
	temp = cgc_copyData( str, start, end );

	if ( cgc_strcmp( temp, "Radius") != 0 ) {
		cgc_printf("!!Invalid closing element id: @s\n", temp);
		cgc_deallocate(temp, cgc_strlen(temp)+1);
		return radius;
	}

	cgc_deallocate(temp, cgc_strlen(temp)+1);

	cgc_skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate final closing brace\n");
		return -1.0;
	}

	/// Skip past the closing brace
	cgc_skipLength( str, 1 );
		
	/// Copy the name element data
	temp = cgc_copyData( str, rs, re );

	if ( temp == NULL ) {
		cgc_printf("!!Failed to copy radius data\n");
		return -1.0;
	}

	radius = cgc_atof( temp );

	cgc_deallocate( temp, cgc_strlen(temp) + 1 );

	return radius;
}

/**
 * Parse the ERadius element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the double value or -1.0 on failure. ERadius should never be negative.
 **/
double cgc_extractERadius( pstring str )
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

	start = cgc_skipWhiteSpace(str);

	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate opening brace\n");
		return eradius;
	}

	/// Skip past the curly brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip opening brace\n");
		return eradius;
	}

	/// Skip any additional whitespace
	start = cgc_skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the element id\n");
		return eradius;
	}

	/// Copy the element id from the string
	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		cgc_printf("!!Copy from @d to @d failed\n", start, end);
		return -1.0;
	}

	/// If the element id is not "ERadius" then this is the wrong function
	if ( cgc_strcmp( temp, "ERadius") != 0 ) {
		cgc_printf("!!Element id is not \"ERadius\"\n");
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
		temp = NULL;
		return eradius;
	}

	/// The buffer is no longer needed so free it
	cgc_deallocate(temp, cgc_strlen(temp) + 1);

	/// Skip to the end of the element id
	cgc_skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate initial closing brace\n");
		return -1.0;
	}

	/// Skip the closing brace as well as any whitespace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip initial closing brace\n");
		return eradius;
	}

	cgc_skipWhiteSpace( str );

	/// Copy the start index to store the data
	cgc_getIndex( str, &es );

	/// The eradius data must be a float
	ee = cgc_skipFloat( str );

	if ( ee == -1 ) {
		cgc_printf("!!Failed to locate the end of the eradius data\n");
		return eradius;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	cgc_skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate the final opening brace\n");
		return -1.0;
	}

	/// Skip past the brace
	if ( cgc_incChar( str) == -1 ) {
		cgc_printf("!!Failed to skip the final opening brace\n");
		return eradius;
	}
	
	cgc_skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !cgc_atChar( str, '#' ) ) {
		cgc_printf("!!Failed to locate the closing mark\n");		
		return -1.0;
	}

	/// Skip past the # but save the start
	start = cgc_skipLength( str, 1 );

	if ( start == -1 ) {
		cgc_printf("!!Failed to skip closing mark\n");
		return eradius;
	}

	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the closing element id\n");
		return -1.0;
	}
	
	temp = cgc_copyData( str, start, end );

	if ( cgc_strcmp( temp, "ERadius") != 0 ) {
		cgc_printf("!!Invalid closing element id: @s\n", temp);
		cgc_deallocate(temp, cgc_strlen(temp)+1);
		return eradius;
	}

	cgc_deallocate(temp, cgc_strlen(temp)+1);

	cgc_skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate final closing brace\n");
		return -1.0;
	}

	/// Skip past the closing brace
	cgc_skipLength( str, 1 );
		
	/// Copy the eradius element data
	temp = cgc_copyData( str, es, ee );

	if ( temp == NULL ) {
		cgc_printf("!!Failed to copy eradius data\n");
		return -1;
	}

	eradius = cgc_atof( temp );

	cgc_deallocate( temp, cgc_strlen(temp) + 1 );

	return eradius;
}

/**
 * Parse the Mass element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the double value or -1.0 on failure. Mass should never be negative.
 **/
double cgc_extractMass( pstring str )
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

	start = cgc_skipWhiteSpace(str);

	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate opening brace\n");
		return mass;
	}

	/// Skip past the curly brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip opening brace\n");
		return mass;
	}

	/// Skip any additional whitespace
	start = cgc_skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the element id\n");
		return mass;
	}

	/// Copy the element id from the string
	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		cgc_printf("!!Copy from @d to @d failed\n", start, end);
		return -1.0;
	}

	/// If the element id is not "Mass" then this is the wrong function
	if ( cgc_strcmp( temp, "Mass") != 0 ) {
		cgc_printf("!!Element id is not \"Mass\"\n");
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
		temp = NULL;
		return mass;
	}

	/// The buffer is no longer needed so free it
	cgc_deallocate(temp, cgc_strlen(temp) + 1);

	/// Skip to the end of the element id
	cgc_skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate initial closing brace\n");
		return -1.0;
	}

	/// Skip the closing brace as well as any whitespace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip initial closing brace\n");
		return mass;
	}

	cgc_skipWhiteSpace( str );

	/// Copy the start index to store the data
	cgc_getIndex( str, &es );

	/// The mass data must be a float
	ee = cgc_skipFloat( str );

	if ( ee == -1 ) {
		cgc_printf("!!Failed to locate the end of the mass data\n");
		return mass;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	cgc_skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate the final opening brace\n");
		return -1.0;
	}

	/// Skip past the brace
	if ( cgc_incChar( str) == -1 ) {
		cgc_printf("!!Failed to skip the final opening brace\n");
		return mass;
	}
	
	cgc_skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !cgc_atChar( str, '#' ) ) {
		cgc_printf("!!Failed to locate the closing mark\n");		
		return -1.0;
	}

	/// Skip past the # but save the start
	start = cgc_skipLength( str, 1 );

	if ( start == -1 ) {
		cgc_printf("!!Failed to skip closing mark\n");
		return mass;
	}

	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the closing element id\n");
		return -1.0;
	}
	
	temp = cgc_copyData( str, start, end );

#ifdef PATCHED
	if ( temp == NULL ) {
		return -1.0;
	}
#endif

	if ( cgc_strcmp( temp, "Mass") != 0 ) {
		cgc_printf("!!Invalid closing element id: @s\n", temp);
		cgc_deallocate(temp, cgc_strlen(temp)+1);
		return mass;
	}

	cgc_deallocate(temp, cgc_strlen(temp)+1);

	cgc_skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate final closing brace\n");
		return -1.0;
	}

	/// Skip past the closing brace
	cgc_skipLength( str, 1 );
		
	/// Copy the mass element data
	temp = cgc_copyData( str, es, ee );

	if ( temp == NULL ) {
		cgc_printf("!!Failed to copy mass data\n");
		return -1;
	}

	mass = cgc_atof( temp );

	cgc_deallocate( temp, cgc_strlen(temp) + 1 );

	return mass;
}

/**
 * Parse the Gravity element and return the stored value
 * @param str Pointer to a string structure
 * @return Returns the double value or -1.0 on failure. Gravity should never be negative.
 **/
double cgc_extractGravity( pstring str )
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

	start = cgc_skipWhiteSpace(str);

	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate opening brace\n");
		return gravity;
	}

	/// Skip past the curly brace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip opening brace\n");
		return gravity;
	}

	/// Skip any additional whitespace
	start = cgc_skipWhiteSpace(str);

	/// This should skip any to either whitespace or a closing '}'
	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the element id\n");
		return gravity;
	}

	/// Copy the element id from the string
	temp = cgc_copyData( str, start, end );

	if ( temp == NULL ) {
		cgc_printf("!!Copy from @d to @d failed\n", start, end);
		return -1.0;
	}

	/// If the element id is not "Gravity" then this is the wrong function
	if ( cgc_strcmp( temp, "Gravity") != 0 ) {
		cgc_printf("!!Element id is not \"Gravity\"\n");
		cgc_deallocate( temp, cgc_strlen(temp) + 1 );
		temp = NULL;
		return gravity;
	}

	/// The buffer is no longer needed so free it
	cgc_deallocate(temp, cgc_strlen(temp) + 1);

	/// Skip to the end of the element id
	cgc_skipWhiteSpace( str );

	/// If it is not a closing brace then this is improperly formatted.
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate initial closing brace\n");
		return -1.0;
	}

	/// Skip the closing brace as well as any whitespace
	if ( cgc_skipLength( str, 1 ) == -1 ) {
		cgc_printf("!!Failed to skip initial closing brace\n");
		return gravity;
	}

	cgc_skipWhiteSpace( str );

	/// Copy the start index to store the data
	cgc_getIndex( str, &es );

	/// The gravity data must be a float
	ee = cgc_skipFloat( str );

	if ( ee == -1 ) {
		cgc_printf("!!Failed to locate the end of the gravity data\n");
		return gravity;
	}

	/// The rest of this code is a check to ensure proper formatting except for the copy data
	cgc_skipWhiteSpace( str );

	/// If this is not an opening curly brace then fail
	if ( !cgc_atChar( str, '{' ) ) {
		cgc_printf("!!Failed to locate the final opening brace\n");
		return -1.0;
	}

	/// Skip past the brace
	if ( cgc_incChar( str) == -1 ) {
		cgc_printf("!!Failed to skip the final opening brace\n");
		return gravity;
	}
	
	cgc_skipWhiteSpace(str);

	/// If this is not a # indicating the closing brace then fail
	if ( !cgc_atChar( str, '#' ) ) {
		cgc_printf("!!Failed to locate the closing mark\n");		
		return -1.0;
	}

	/// Skip past the # but save the start
	start = cgc_skipLength( str, 1 );

	if ( start == -1 ) {
		cgc_printf("!!Failed to skip closing mark\n");
		return gravity;
	}

	end = cgc_skipToNonAlphaNum( str );

	if ( end == -1 ) {
		cgc_printf("!!Failed to locate the end of the closing element id\n");
		return -1.0;
	}
	
	temp = cgc_copyData( str, start, end );

	if ( cgc_strcmp( temp, "Gravity") != 0 ) {
		cgc_printf("!!Invalid closing element id: @s\n", temp);
		cgc_deallocate(temp, cgc_strlen(temp)+1);
		return gravity;
	}

	cgc_deallocate(temp, cgc_strlen(temp)+1);

	cgc_skipWhiteSpace( str );

	/// Check the final curly brace
	if ( !cgc_atChar( str, '}' ) ) {
		cgc_printf("!!Failed to locate final closing brace\n");
		return -1.0;
	}

	/// Skip past the closing brace
	cgc_skipLength( str, 1 );
		
	/// Copy the gravity element data
	temp = cgc_copyData( str, es, ee );

	if ( temp == NULL ) {
		cgc_printf("!!Failed to copy gravity data\n");
		return -1;
	}

	gravity = cgc_atof( temp );

	cgc_deallocate( temp, cgc_strlen(temp) + 1 );

	return gravity;
}

