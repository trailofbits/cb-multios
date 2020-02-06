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

#include "cgc_helper.h"

/**
 * Extract the next element name without affecting the string
 *	This buffer must be freed by the caller
 * @param str Pointer to a string structure
 * @return Returns a new pointer to the name of the element or NULL on failure
 **/
char *cgc_pullNextElementName( pstring str )
{
        char * elementId = NULL;
        int reset = 0;
        int index = 0;
        unsigned int length = 0;

        if ( str == NULL ) {
                return NULL;
        }

        /// This will be used to reset the buffer at the end
        reset = str->index;

        /// This shouldn't be necessary but just in case
        cgc_skipWhiteSpace( str );

        /// The first character should be an open curly brace
        if (str->buffer[ str->index ] != '{' ) {
                cgc_printf("!!Invalid opening element: @s\n", str->buffer );
                goto end;
        }

        /// Increment beyond the initial '{'
	if ( cgc_incChar( str ) == -1 ) {
		goto end;
	}

        /// Skip past any whitespace
        cgc_skipWhiteSpace(str);

        /// Store the index to the start of the element name
        index = str->index;

        /// Loop until the end of the buffer, a null, or a non-alpha, white space, or  '}' character is encountered
        while ( index < str->maxlength ) {

                /// If we hit a NULL then it is improperly formatted.
                /// Just skip to the end
                if ( str->buffer[index] == '\x00' ) {
                        cgc_printf("!!Null character hit. Improperly formatted element\n");
                        goto end;
                }

                /// If it is a closing brace or a white space then the name is passed
                if ( str->buffer[ index ]  == '}' || cgc_isspace( str->buffer[index] ) ) {
                        length = index-str->index;

                        /// Copy the name for the return
                        if ( cgc_allocate( length + 1, 0, (void*)&elementId ) != 0 ) {
                                elementId = NULL;
                                goto end;
                        }

                        cgc_bzero( elementId, length + 1 );

                        cgc_strncpy( elementId, str->buffer + str->index, length );

                        /// Check for a properly formatted name. Start by updating
			///	the string index to the end of the string
			///	Then skip any proceeding whitespace
                        str->index = index;
                        cgc_skipWhiteSpace(str);

                        /// If the current character is not '}' then it invalid is
			///	invalid since only whitespace is allowed between the
			///	element id and the closing brace
                        if (str->buffer[ str->index ] != '}' ) {
                                cgc_printf("!!Improperly formatted element name\n");
                                cgc_deallocate( elementId, length + 1 );
                                elementId = NULL;
                        }

                        /// Work here is done. Skip to the end
                        goto end;
                }

                /// Non alpha characters are not allowed as element names
                if ( !cgc_isalpha( str->buffer[index] ) ) {
                        goto end;
                }

                index++;
        }

end:
	/// Revert the string to the beginning
        str->index = reset;

        return elementId;
}

/**
 * Converts an name to an enum value
 * @param elementId Pointer to the string representation of the element id
 * @return Returns the enum value of the requested element or error on failure
 **/
element cgc_elementNameToEnum( char * elementId )
{
        element retval = error;
        int length = 0;

        if ( elementId == NULL ) {
                goto end;
        }

        length = cgc_strlen(elementId);

        switch ( length ) {
		case 3:
			if ( cgc_strcmp( elementId, "Url") == 0 ) {
				retval = url;
			}

			break;
                case 4:
                        if ( cgc_strcmp( elementId, "Name") == 0 ) {
                                retval = name;
                        } else if ( cgc_strcmp( elementId, "Mass" ) == 0 ) {
                                retval = mass;
                        } else if ( cgc_strcmp( elementId, "Area" ) == 0 ) {
				retval = area;
			} else if ( cgc_strcmp( elementId, "Seat" ) == 0 ) {
				retval = seat;
			} else if ( cgc_strcmp( elementId, "City" ) == 0 ) {
				retval = city;
			}

                        break;

		case 5:
			if ( cgc_strcmp( elementId, "Mayor" ) == 0 ) {
				retval = mayor;
			}

			break;
                case 6:
                        if ( cgc_strcmp( elementId, "Planet") == 0 ) {
                                retval = planet;
                        } else if ( cgc_strcmp( elementId, "Period") == 0 ) {
                                retval = period;
                        } else if ( cgc_strcmp( elementId, "Radius" ) == 0 ) {
                                retval = radius;
                        } else if ( cgc_strcmp( elementId, "Border" ) == 0 ) {
				retval = border;
			} else if ( cgc_strcmp( elementId, "County" ) == 0 ) {
				retval = county;
			}

                        break;
                case 7:
                        if ( cgc_strcmp( elementId, "ERadius" ) == 0 ) {
                                retval = eradius;
                        } else if ( cgc_strcmp( elementId, "Gravity" ) == 0 ) {
                                retval = gravity;
                        } else if ( cgc_strcmp( elementId, "Country" ) == 0 ) {
                                retval = country;
                        } else if ( cgc_strcmp( elementId, "Capitol" ) == 0 ) {
				retval = capitol;
			} else if ( cgc_strcmp( elementId, "Founder" ) == 0 ) {
				retval = founder;
			} else if ( cgc_strcmp( elementId, "Density" ) == 0 ) {
				retval = density;
			}

                        break;

                case 8:
                        if ( cgc_strcmp( elementId, "Aphelion") == 0 ) {
                                retval = aphelion;
                        } else if ( cgc_strcmp( elementId, "Language") == 0 ) {
				retval = language;
			}

                        break;
		case 9:
			if ( cgc_strcmp( elementId, "Territory") == 0 ) {
				retval = territory;
			}
			break;
                case 10:
                        if ( cgc_strcmp( elementId, "OrbitSpeed") == 0 ) {
                                retval = orbitspeed;
                        } else if ( cgc_strcmp( elementId, "Perihelion") == 0 ) {
                                retval = perihelion;
                        } else if ( cgc_strcmp( elementId, "Population") == 0 ) {
                                retval = population;
                        }

                        break;
		case 11:
			if (cgc_strcmp( elementId, "Established") == 0 ) {
				retval = established;
			}

			break;
                default:
                        retval = error;
                        break;
        };

        if ( retval == error ) {
                cgc_printf("!!Unknown element id: @s\n", elementId);
        }

end:
        return retval;
}

