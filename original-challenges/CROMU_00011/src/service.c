/*

Author: John Berry <john.n.berry@gmail.com>

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

/**
 * This program is used to solve set theory problems via a command line
 *    interface.
 *    Possible set commands are: newset = oldset
 *    setx = |"data", setn|    (initiate a set)
 *    setx = seta+setb    (union)
 *    setx = seta^setb     (intersect)
 *    setx = seta-setb    (set difference)
 *    setx = seta~setb    (symmetric difference)
 *    seta @ setb        (subset) Prints True if seta is a subset of setb
 **/

/**
 * Invalid set tests
 *    set = |"|
 *    set = |",|
 *    set = |
 *    set = ,
 *    set = |"yo" "|
 *    set = |"yo" "dog" |
 *    set = | dd, |
 *     set = | dd "yo" |
 *     set = | "yo" dd |
 *    set = | "yo"
 **/
#include "struct_inits.h"
#include "service.h"

psetArray root = NULL;

psplitCommand parse_command_line( char *cmd )
{
    psplitCommand sc = NULL;
    int index = 0;

    if ( cmd == NULL ) {
        goto end;
    }

    if (allocate( sizeof(splitCommand), 0, (void**)&sc) != 0) {
        sc = NULL;
        goto end;
    }

    bzero( sc, sizeof(splitCommand) );

    while (cmd[index] && index < 0x100) {
        /// The only valid middle are '=' to modfiy a set's value
        ///     or '@' to print the power set
        if (cmd[index] == '=' || cmd[index] == '@') {
            /// Ensure that the left has been set first
            ///  This is to prevent command like '= |"var"|'
            ///  without a variable
            if ( sc->left == NULL ) {
                goto error;
            }
            sc->mid = cmd[index];
            cmd[index] = 0x00;
        } else if ( cmd[index] == ' ' ) {
            if ( sc->right == NULL ) {
                cmd[index] = 0x00;
            }
        } else if ( isalnum( cmd[index] ) ) {
            /// if left or right are not set then this is it
            if ( sc->left == NULL ) {
                sc->left = cmd + index;
            } else if ( sc->right == NULL && sc->mid != 0 ) {
                sc->right = cmd + index;
            }
            /// if both are set then just move on
        } else if ( cmd[index] == '|' || cmd[index] == '-' ||
                cmd[index] == '"' || cmd[index] == ',' ||
                cmd[index] == '*' || cmd[index] == '^' ||
                cmd[index] == '+' || cmd[index] == '~') {
            /// These chars are only allowed to the right
            if ( sc->left == NULL || sc->mid == 0x00 ) {
                goto error;
            }

            if ( sc->right == NULL ) {
                sc->right = cmd + index;
            }
        } else {
            /// If this is hit then the command line is invalid
            goto error;        
        }

        index++;
    }
    
    /// Final parsing check. The right will be null for powerset
    ///     and the mid can be 0 to just print the set    
    if ( sc->left != NULL) {
        goto end;
    }
error:
    printf("!!Error parsing commandline\n");
    deallocate( (void*)sc, sizeof(splitCommand) );
    sc = NULL;
end:
    return sc;
}

/**
 * Handles the .p command to print the current available sets
 * @return Returns nothing
 **/
void print_sets( )
{
    psetArray walker = root;
    int index = 0;

    while ( walker ) {
        print_set( walker );
        walker = walker->next;
        if ( walker == root ) {
            break;
        }
    }

    return;
}

int copymem( char *dest, char*src, int start, int len )
{
	int index = 0;

	while ( index < len ) {
		dest[start] = src[index];
		start++;
		index++;
	}

	return start;
}

// Max Length = 10: "aaaaaaaaaa"
// Variable name = 15 + ' = ' = 18
// 2 for the ||
// I want at least 3 recursions
// 12*15+9+2 = 191
// 191*15+11 = 2876
// 15+3= 18 for the var and ' = ' total 2894
#define DATAMAX 3200
/** Handles the .ps command. Print all sets and expand the internal sets
 * @param r Root pointer to print
 * @param addName Variable to indicate if the name of the set is to be included in the data
 * @return Returns a buffer containing the subset
 **/
#ifdef PATCHED 
char * print_subsets( psetArray r, int addName, int depth )
#else
char * print_subsets( psetArray r, int addName )
#endif
{
	char *outbuff = NULL;
	char *t = NULL;
	char data[DATAMAX];
	int index = 0;
	int ei = 0;
#ifdef PATCHED
    if (depth > 10) {
        return NULL;
    }
#endif 

	if ( r == NULL ) {
		return NULL;
	}

	bzero( data, DATAMAX);

	if (addName != 0 ) {
		index = copymem( data, r->varName, index, strlen(r->varName) );
		index = copymem( data, " = ", index, 3 );
	}

	data[index++] = '|';

	for ( ei = 0; ei < r->varCount; ei++) {
		if ( r->sElems[ei]->type == VALUE ) {
#ifdef PATCHED
			if ( index < DATAMAX-1 )
#endif
				data[index++] = '"';

			t = r->sElems[ei]->value;

#ifdef PATCHED
			if ( index + strlen(t) >= DATAMAX-1 ) {
				goto end;
			}
#endif
			index = copymem( data, t, index, strlen(t));

#ifdef PATCHED
			if ( index < DATAMAX-1 )
#endif
				data[index++] = '"';
		} else {
			psetArray tp = retrieve_set( r->sElems[ei]->value);
#ifdef PATCHED
            t = print_subsets( tp, 0, depth + 1);
#else
			t = print_subsets( tp, 0 );
#endif

			if ( t == NULL ) {
				outbuff = NULL;
				goto end;
			}

#ifdef PATCHED
			if ( index + strlen(t) >= DATAMAX-1 ) {
				deallocate(t, strlen(t) + 1 );
				goto end;
			}
#endif

			index = copymem( data, t, index, strlen(t));
			deallocate(t, strlen(t) + 1 );	
		}

#ifdef PATCHED
		if ( index < DATAMAX - 1 )
#endif
			data[index++] = ',';
	}

#ifdef PATCHED
	if ( index < DATAMAX-2 )
#endif
	{
		if ( data[index-1] == ',' ) {
			data[index-1] = '|';
			data[index] = 0x00;
		} else {
			data[index] = '|';
			data[index+1] = 0x00;
		}
	}

	if ( allocate( strlen(data) + 1, 0, (void*)&outbuff) != 0 ) {
		outbuff = NULL;
		goto end;
	}

	bzero( outbuff, strlen(data) + 1 );

	copymem( outbuff, data, 0, strlen(data) );

end:
	return outbuff;
}

int memcmp( const char *s1, const char *s2, int n )
{
	int index = 0;

	while ( index < n ) {
		if ( (s1[index] != s2[index] ) ) {
			return (s1[index] - s2[index]);
		}
		index++;
	}

	return 0;
}

/**
 * Function to handle command line meta commands
 * @param cmd Pointer to the command line
 * @return Returns nothing
 **/
void exec_command( char *cmd )
{
    char *ps = NULL;
    int index = 0;
    psetArray psa = NULL;

    if ( cmd == NULL ) {
        goto end;
    }

    if ( strcmp( cmd, ".l") == 0 ) {
        _terminate(0);
    } else if ( strcmp( cmd, ".h") == 0 ) {
        printf("setx = |\"data\", sety|\tInitialize a set\n");
	printf("setx = seta+setb\tunion\n");
	printf("setx = seta^setb\tintersect\n");
	printf("setx = seta-setb\tset difference\n");
	printf("setx = seta~setb\tsymmetric difference\n");
	printf("seta @@ setb\t\tsubset. Returns TRUE or FALSE\n");
	printf(".h\t\tPrint this menu\n");
	printf(".l\t\tExit the program\n");
	printf(".p\t\tPrint sets and their elements\n");
	printf(".ps <setvar>\tPrint an expanded set\n");
    } else if ( memcmp( cmd, ".ps", 3) == 0 ) {
	cmd += 3;

        /// Skip any spaces
	while( *cmd == ' ' ) { ++cmd; }

        /// Skip to the end of the argument
	while( isalnum(cmd[index]) ) { index++; }

        /// Add a null
	cmd[index] = 0x00;
	
	psa = retrieve_set( cmd );

	if ( psa == NULL ) {
            printf("!!Failed to find set: @s\n", cmd );
            goto end;
        }
#ifdef PATCHED
        ps = print_subsets( psa, 1, 0);
#else
        ps = print_subsets( psa, 1 );
#endif 
        if ( ps != NULL ) {
        	printf("@s\n", ps);
		deallocate(ps, strlen(ps)+1);
	}
    } else if ( strcmp( cmd, ".p") == 0 ) {
        print_sets();
    } else {
        printf("!!Unrecognized command: @s\n", cmd);
        goto end;
    }

end:
    return;
}

/**
 * Function to retrieve an existing set structure from the list
 * @param varName Pointer to the name of the set to retrieve
 * @return Returns a pointer to the setArray structure or NULL if not found
 **/
psetArray retrieve_set( char *varname )
{
    psetArray set = NULL;

    if (varname == NULL ) {
        goto end;
    }

    set = root;

    while ( set ) {
        if (strcmp( varname, set->varName ) == 0 ) {
            goto end;
        }

        set = set->next;

        /// This means we went through the whole list
        if ( set == root ) {
            set = NULL;
            goto end;
        }
    }

end:
    return set;
}

/**
 * Add a new set to the list
 * @param set Pointer to the new set
 * @return Does not return anything
 **/
void add_set( psetArray newset )
{
    if ( newset == NULL ) {
        goto end;
    }
    
    /// Handle the initial case
    if (root == NULL ) {
        root = newset;
        newset->next = newset;
        newset->prev = newset;
    }

    // Add the set at the end
    newset->next = root;
    newset->prev = root->prev;
    root->prev->next = newset;
    root->prev = newset;

end:
    return;
}

/**
 * Parses a new set variable
 * @param Pointer to a string where the new set starts
 * @return Returns a set structure with the values populated
 **/
psetArray parse_set( char *setstring)
{
    psetArray psa = NULL;
    char *right = NULL;
    char *var_start = NULL;
    char *var_end = NULL;
    setState state = start;
    psetElement se = NULL;
    psetArray t = NULL;

    char temp[0x100];

    if ( setstring == NULL ) {
        goto end;
    }

    // Allocate the new set array
    if ( allocate( sizeof(setArray), 0, (void**)&psa) != 0 ) {
        psa = NULL;
        goto end;
    }

    bzero( psa, sizeof(setArray) );

    right = setstring;

    while ( *right && state != error && state != close_set ) {
        if ( *right == '|' ) {
            switch (state) {
                case start:
                    state = open_set;
                    break;
                case open_double:
                    break;
                case new_var:
                    state = error;
                    printf("!!Additional variable expected\n");
                    break;
                case set_var:
                    bzero(temp, 0x100);

                    // Max value length of 10
                    if ( right-var_start > 10 ) {
                        printf("!!Invalid set data length\n");
                        state = error;
                        goto end;
                    }

                    memcpy( temp, var_start, right-var_start);
                    t = retrieve_set( temp );

                    if ( t == NULL ) {
                        printf("!!Cannot have a non-existant set as an element\n");
                        state = error;
                        break;
                    }

                    se = create_element( temp, SET );

                    if ( se == NULL ) {
                        printf("!!Failed to create element\n");
                        state = error;
                        break;
                    }

                    if ( element_in_set( psa, se ) ) {
                        printf("!!Elements must be unique\n");
                        free_element(se);
                        free_set_array( psa );
                        se = NULL;
                        psa = NULL;
                        state = error;
                        goto end;
                    }

                    if ( add_element_to_set( psa, se ) ) {
                        printf("Failed to ad el\n");
                        state = error;
                        goto end;
                    }
                default:
                    state = close_set;
                    break;    
            };
        } else if ( *right == '"' ) {
            switch ( state ) {
                case open_double:
                    state = close_double;
                    bzero(temp, 0x100);

                    // Max value length of 10
                    if ( right-var_start > 10 ) {
                        printf("!!Invalid set data length\n");
                        state = error;
                        goto end;
                    }

                    memcpy( temp, var_start, right-var_start);
                    se = create_element( temp, VALUE );

                    if ( se == NULL ) {
                        printf("Failed to cel\n");
                        state = error;
                        goto end;
                    }

                    if ( element_in_set( psa, se ) ) {
                        printf("!!Elements must be unique\n");
                        free_element(se);
                        free_set_array( psa );
                        se = NULL;
                        psa = NULL;
                        state = error;
                        goto end;
                    }

                    if ( add_element_to_set( psa, se ) ) {
                        printf("Failed to ad el\n");
                        state = error;
                        goto end;
                    }
                    break;
                case set_end:
                case set_var:
                case close_double:
                    state = error;
                    printf("!!Malformed set\n");
                    break;
                default:
                    state = open_double;
                    var_start = right+1;
                    break;
            };
        } else if ( *right == ' ') {
            switch ( state ) {
                case set_var:
                    var_end = right;
                    bzero( temp, 0x100 );

                    // Max set name is 15
                    if ( right-var_start > 15 ) {
                        printf("!!Invalid set name length\n");
                        state = error;
                        goto end;
                    }

                    memcpy( temp, var_start, right-var_start);
                    se = create_element( temp, SET );

                    if ( se == NULL ) {
                        printf("!!Create element failed\n");
                        state = error;
                        goto end;
                    }

                    if ( element_in_set( psa, se ) ) {
                        printf("!!Elements must be unique\n");
                        free_element(se);
                        free_set_array( psa );
                        se = NULL;
                        psa = NULL;
                        state = error;
                        goto end;
                    }

                    if ( add_element_to_set( psa, se ) ) {
                        printf("!!Failed to add element\n");
                        state = error;
                        goto end;
                    }
                    state = set_end;
                    break;
                default:
                    break;
            };
        } else if ( *right == ',') {
            switch ( state ) {
                case open_set:
                    state = error;
                    printf("!!Malformed set\n");
                    break;
                case set_var:
                    bzero( temp, 0x100 );

                    // Max set name is 15
                    if ( right-var_start > 15 ) {
                        printf("!!Invalid set name length\n");
                        state = error;
                        goto end;
                    }

                    memcpy( temp, var_start, right-var_start);
                    se = create_element( temp, SET );

                    if ( se == NULL ) {
                        printf("!!Failed to create element\n");
                        state = error;
                        goto end;
                    }

                    if ( element_in_set( psa, se ) ) {
                        printf("!!Elements must be unique\n");
                        free_element(se);
                        free_set_array( psa );
                        se = NULL;
                        psa = NULL;
                        state = error;
                        goto end;
                    }

                    if ( add_element_to_set( psa, se ) ) {
                        printf("!!Failed to add element\n");
                        state = error;
                        goto end;
                    }
                    state = new_var;
                    break;
		case open_double:
                    printf("!!Improperly formated set\n");
                    state = error;
                    goto end;
                    break;
			
                default:
                    state = new_var;
                    break;
            };

        } else {
            switch( state ) {
                case open_set:
                case new_var:
                    state = set_var;
                    var_start = right;
                    break;
                case close_double:
                    state = error;
                    printf("!!Invalid character\n");
                    goto end;
                default:
                    break;
            }
        }
        right++;
    }

end:
    if ( state != close_set ) {
        free_set_array( psa );
        psa = NULL;
    }

    return psa; 
}

/**
 * Performs the symmetric difference between two sets
 * In english it is the set of elements which are in one and only one
 *	of a group of sets. In notation it is (A-B)U(B-A)
 * @param setone First set
 * @param settwo Second set
 * @return The symmetric difference of the two sets.
 **/
psetArray symmetric_difference( psetArray setone, psetArray settwo )
{
	psetArray final = NULL;
	psetArray diffone = NULL;
	psetArray difftwo = NULL;
	int index = 0;

	if ( setone == NULL || settwo == NULL ) {
		goto end;
	}

	diffone = set_difference( setone, settwo );

	if ( diffone == NULL ) {
		goto end;
	}

	difftwo = set_difference( settwo, setone );

	if ( difftwo == NULL ) {
		free_set_array( diffone );
		diffone = NULL;
		goto end;
	}

	final = unionset( diffone, difftwo );

	free_set_array(diffone);
	free_set_array(difftwo);

end:
	return final;
}

/**
 * Performs the set difference between two sets
 *  For example: seta = |"one","two", "three"|
 *  setb = |"three", "four"|
 * |"one", "two" | = seta - setb
 * @param setone First set
 * @param settwo Second set
 * @return The set difference of the two sets.
 **/
psetArray set_difference( psetArray setone, psetArray settwo )
{
    psetArray final = NULL;
    int index = 0;
    int res = 0;

    if ( setone == NULL || settwo == NULL ) {
        goto end;
    }

    if ( allocate( sizeof(setArray), 0, (void**)&final ) != 0 ) {
        final = NULL;
        goto end;
    }

    bzero( final, sizeof(setArray) );

    while ( index < setone->varCount ) {
        res = element_in_set( settwo, setone->sElems[index] );

        if ( res == -1 ) {
            free_set_array( final );
            final = NULL;
            goto end;
        }

        if ( res == 0 ) {
            if ( add_element_to_set( final, copy_element( setone->sElems[index])) != 0 ) {
                free_set_array(final);
                final = NULL;
                goto end;
            }
        }                

        index++;
    }

end:
    return final;
}

/**
 * Performs an intersect on two sets
 * @param setone First set
 * @param settwo Second set
 * @return The intersect of the two sets
 **/
psetArray intersect( psetArray setone, psetArray settwo )
{
    psetArray newset = NULL;
    int index = 0;
    int res = 0;

    if ( setone == NULL || settwo == NULL ) {
        goto end;
    }

    if ( allocate( sizeof(setArray), 0, (void**)&newset) != 0 ) {
        printf("!!Failed to allocate newset\n");
        newset = NULL;
        goto end;
    }

    bzero( newset, sizeof(setArray) );

    /// Only those elements in both are put into the newset
    while ( index < setone->varCount ) {
        res = element_in_set( settwo, setone->sElems[index] );

        if ( res == -1 ) {
            printf("!!Unknown error\n");
            free_set_array( newset );
            newset = NULL;
            goto end;
        } else if ( res == 1 ) {
            if ( add_element_to_set( newset, copy_element(setone->sElems[index])) != 0 ) {
                printf("!!Error adding element in intersect\n");
                free_set_array( newset);
                newset = NULL;
                goto end;
            }
        }

        index++;
    }    

end:
    return newset;
}

/**
 * Performs an union on two sets
 * @param setone First set
 * @param settwo Second set
 * @return The union of the two sets
 **/
psetArray unionset( psetArray setone, psetArray settwo )
{
    psetArray newset = NULL;
    int index = 0;
    int res = 0;

    if ( setone == NULL || settwo == NULL ) {
        goto end;
    }

    if ( allocate( sizeof(setArray), 0, (void**)&newset) != 0 ) {
        printf("!!Failed to allocate new nset\n");
        newset = NULL;
        goto end;
    }

    bzero( newset, sizeof(setArray) );

    /// All elements of the first set will be in the union
    while ( index < setone->varCount ) {
        if ( add_element_to_set( newset, copy_element( setone->sElems[index]) ) != 0 ) {
            printf("!!Failed to add element in union\n");
            free_set_array( newset );
            newset = NULL;
            goto end;
        }
        index++;
    }
    
    index = 0;

    /// Only elements from the second not already in the first will be copied
    while ( index < settwo->varCount ) {
        res = element_in_set( newset, settwo->sElems[index] );

        if ( res == -1 ) {
            printf("!!!Error in intersect\n");
            free_set_array( newset );
            newset = NULL;
            goto end;
        } else if ( res == 0 ) {
            if ( add_element_to_set( newset, copy_element( settwo->sElems[index]) ) != 0 ) {
                printf("!!!Failed to add element in intersect\n");
                free_set_array( newset );
                newset = NULL;
                goto end;
            }
        }

        index++;
    }

end:
    return newset;
}

/**
 * Parses the right side of a set equation and creates the resulting set
 * @param setName Pointer to the name of the new set
 * @param setData Data to parse
 * @return Returns the newly created set
 **/
psetArray parse_operations( char *setName, char *setData )
{
    psetArray setone = NULL;
    int set_one_is_new = 0;
    psetArray settwo = NULL;
    int set_two_is_new = 0;
    char setval[0x10];
    int operation = 0;
    int nlen = 0;
    psetArray final = NULL;

    if ( setName == NULL || setData == NULL ) {
        goto end;
    }

    while ( *setData ) {
        if ( *setData == '|' ) {

            /// Only two sets can be referenced per command
            if ( setone == NULL ) {
                setone = parse_set( setData );

                /// Skip the opening "|"
                setData++;

                if ( setone != NULL ) {
                    /// Skip to the end of the set
                    while(*setData != '|') { setData++;}

                    // This is for the later freeing operation
                    set_one_is_new = 1;
                } else {
                    printf("!!Set parsing failed\n");
                    goto end;
                }

            } else if ( settwo == NULL ) {
                settwo = parse_set( setData );

                /// This is to pass the '|'
                setData++;
                if ( settwo != NULL ) {
                    while(*setData != '|') { setData++;}

                    set_two_is_new = 1;
                } else {
                    printf("!!Set parsing failed\n");
                    goto end;
                }
            } else {
                printf("!!Too many sets\n");
                goto end;
            }
        } else if (*setData == '^' || *setData == '+' || *setData == '-'
			|| *setData == '~') {
            if ( operation != 0 ) {
                printf("!!Only one operation allowed.\n");
                goto end;
            }

            operation = *setData;
        } else if ( isalnum(*setData) ) {
            char *setstart = setData;

            /// Get to the end of the set value
            while( isalnum(*setData) ) { setData++; }

            bzero( setval, 0x10);
            nlen = setData-setstart;

            /// Because there is a later increment of setData the value
            ///   must be decremented by one to ensure no skipped characters
            --setData;            

            if ( nlen > 0x0f ) {
                printf("!!Invalid set name length\n");
                goto end;
            }

            memcpy( setval, setstart, nlen );

            if ( setone == NULL ) {
                setone = retrieve_set( setval );
                if ( setone == NULL ) {
                    printf("!!Nonexistant set: @s\n", setval);
                    goto end;
                }
            } else if ( settwo == NULL ) {
                settwo = retrieve_set( setval );
                if ( settwo == NULL ) {
                    printf("!!Nonexistant set: @s\n", setval);
                    goto end;
                }
            } else {
                printf("!!Too many sets\n");
                goto end;
            }
        } else if ( *setData == ' ' ) {
            setData++;
            continue;
        } else {
            printf("!!Invalid sets\n");
            goto end;
        }

        setData++;
    }

    /// Handle operation
    if ( operation == '+' ) {
        final = unionset( setone, settwo );
    } else if ( operation == '^' ) {
        final = intersect( setone, settwo );
    } else if ( operation == '-' ) {
        final = set_difference(setone, settwo );
    } else if ( operation == '~' ) {
        final = symmetric_difference( setone, settwo );
    } else {
        // If it is just a new set being initialized then do not
        //      free it.
        final = copy_set( setone );

	if ( final == NULL ) {
		printf("!!Copy failed\n");
		goto end;
	}
    }
  
    if (final == NULL ) {
        goto end;
    }
 
    strncpy( final->varName, setName, 15 );

    // Ensure that final will not contain itself as a set
    int index = 0;
    for (index = 0; index < final->varCount; index++ ) {
        if ( final->sElems[index]->type == SET ) {
            if ( strcmp( final->sElems[index]->value, final->varName ) == 0 ) {
                printf("!!A set cannot contain itself\n");
                free_set_array(final);
                final = NULL;
                goto end;
            }
        }
    }
 
end:
    if ( settwo && set_two_is_new) {
        free_set_array( settwo );
        settwo = NULL;
    }

    if ( setone && set_one_is_new) {
        free_set_array( setone );
        setone = NULL;
    }

    return final;
}

/**
 * Function to handle the modification/initiation of sets
 * @param psc Pointer to a split command line structure
 * @return Returns 0 on success, non zero on failure
 **/
int handle_set_var( psplitCommand psc )
{
    int retval = -1;
    psetArray psa = NULL;
    psetArray existing_sa = NULL;

    if ( psc == NULL ) {
        goto end;
    }

    if ( psc->left == NULL ) {
        goto end;
    }

    if ( psc->right == NULL ) {
        goto end;
    }

    psa = parse_operations( psc->left, psc->right );

    if (psa == NULL) {
        printf("!!Error parsing sets\n");
        goto end;
    }

    existing_sa = retrieve_set( psa->varName );

    if ( existing_sa == NULL ) {
	/// If the set is not yet in the list then add it
        add_set( psa );        
    } else {
        /// Free existing set elements
        for ( retval = 0; retval < existing_sa->varCount; retval++) {
            free_element( existing_sa->sElems[retval] );
            existing_sa->sElems[retval] = NULL;
        }

	/// Add the elements to the old set
        for ( retval = 0; retval < psa->varCount; retval++) {
            existing_sa->sElems[retval] = psa->sElems[retval];
        }

	/// Update to the correct element count
        existing_sa->varCount = psa->varCount;

	/// deallocate is used instead of free_set_array to prevent
	///	the elements from being freed as well.
        deallocate(psa, sizeof(setArray));
    }

    retval = 0;

end:
    return retval;
}

void issubset( char *left, char* right )
{
	int index = 0;
	psetArray sub = NULL;
	psetArray super = NULL;
	char * setone = NULL;
	char * settwo = NULL;

	if (left == NULL || right == NULL ) {
		goto end;
	}

	while (*left && *left == ' ') {
		++left;
	}

	if ( left[0] == '|' ) {
		sub = parse_set( left );
	} else {
		while ( left[index] != ' ' && left[index] != 0x00 ) {
			index++;
		}
		left[index] = 0x00;
		sub = retrieve_set( left );
	}

	if ( sub == NULL ) {
		printf("!!Failed to parse left set\n");
		goto end;
	}

	while (*right && *right == ' ') {
		++right;
	}

	if ( right[0] == '|' ) {
		super = parse_set( right );
	} else {
		index = 0;
		while ( right[index] != ' ' && right[index] != 0x00 ) {
			index++;
		}
		right[index] = 0x00;
		super = retrieve_set( right );
	}

	if ( super == NULL ) {
		printf("!!Failed to parse right set\n");
		goto end;
	}

	index = 0;
	while ( index < sub->varCount ) {
		if ( !element_in_set( super, sub->sElems[index] ) ) {
			printf("FALSE\n");
			goto end;
		}
		index++;
	}	
	
	printf("TRUE\n");
end:
	if ( super ) {
		// If the next pointer is null it means it was a new set
		if ( super->next == NULL ) {
			free_set_array( super );
			super = NULL;
		}
	}

	return;
}

/**
 * Function to handle the command line interface and accept input
 * @return Return indicates the end of the program.
 **/
void command_loop( void )
{
    int result = 0;
    char cmd[0x100];
    psplitCommand psc = NULL;

    while ( 1 ) {
        bzero( cmd, 0x100 );
        printf("> ");
        
        result = receive_until( cmd, '\n', 0xff );

        if ( cmd[0] == '.' ) {
            exec_command( cmd );
        } else {
            psc = parse_command_line( cmd );

            /// If command line parsing failed then exit
            if ( psc == NULL ) {
		_terminate(0);
                continue;
            }

            if ( psc->mid == '=' ) {
                handle_set_var( psc );
            } else if ( psc->mid == '@' ) {
                issubset( psc->left, psc->right );
            }

            deallocate( psc, sizeof( splitCommand ) );
        }
    }
end:
    return;
}

int main(void)
{
    command_loop();
    return 0;
}
