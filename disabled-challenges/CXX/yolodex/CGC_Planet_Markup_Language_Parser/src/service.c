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

#include "cgc_service.h"
#include "cgc_planetParsers.h"

pPlanet solarSystem[10];

int main(int cgc_argc, char *cgc_argv[])
{
	int choice = 0;
	char selection[30];
	pstring tl = NULL;
	pPlanet pp = NULL;
	char *temp = NULL;

	cgc_bzero( solarSystem, sizeof(pPlanet) * 10 );

	while (1) {
		cgc_printf("\nPlanet Markup Language Main\n");
		cgc_printf("1) Print Planets\n");
		cgc_printf("2) Add PML\n");
		cgc_printf("3) Add Planet\n");
		cgc_printf("4) Select Planet\n");
		cgc_printf("5) Exit\n");
		cgc_printf("Selection: ");

		cgc_bzero(selection, 30);
		cgc_receive_until( selection, '\n', 4 );

		choice = cgc_atoi( selection );

		switch (choice) {
			case 1:
				for ( choice = 0; choice < 10; choice++ ) {
					if ( solarSystem[choice] != NULL ) {
						cgc_printPlanetInfo( solarSystem[choice] );
					}
				}
				break;
			case 2:
				if ( cgc_allocate( 4096, 0, (void**)&temp) != 0 ) {
					temp = NULL;
					continue;
				}
	
				cgc_printf("PML: ");
				cgc_bzero( temp, 4096);
				cgc_receive_until( temp, '\n', 4095);
				tl = cgc_initString( temp );
				cgc_deallocate(temp, 4096);

				if ( tl == NULL ) {
					continue;
				} else if ( tl->buffer == NULL ) {
					cgc_deallocate( tl, sizeof(string));
					continue;
				}

				choice = 0;
				while ( choice < 10 ) {
					if ( solarSystem[choice] != NULL ) {
						choice++;
						continue;
					}

					solarSystem[choice] = cgc_planetTopLevel(tl);

					if ( solarSystem[choice] == NULL ) {
						break;
					}

					choice++;
				}
				
				cgc_freeString(tl);
				break;
			case 3:
				cgc_printf("\n-> ");
				cgc_bzero(selection, 30);

				cgc_receive_until( selection, '\n', 29 );

				choice = 0;
				while ( choice < 10 ) {
					if ( solarSystem[choice] == NULL ) {
						break;
					}
					choice ++;
				}

				if ( choice == 10 ) {
					continue;
				}

				if ( cgc_allocate( sizeof(Planet), 0, (void**)&pp) != 0 ) {
					pp = NULL;
					break;
				}

				cgc_initPlanet(pp);


				solarSystem[choice] = pp;

				choice = 0;
				while ( cgc_isalnum(selection[choice]) ) {
					pp->name[choice] = selection[choice];
					choice++;
				}
					
				break;
			case 4:
				for (choice=0; choice < 10; choice++) {
					if ( solarSystem[choice] != NULL ) {
						cgc_printf("@d) @s\n", choice +1, solarSystem[choice]->name);
					}
				}

				cgc_bzero( selection, 30);
				cgc_printf("\n-> ");
				cgc_receive_until(selection, '\n', 4 );

				choice = cgc_atoi(selection);

				if ( choice < 1 || choice > 10 ) {
					cgc_printf("Invalid\n");
					continue;
				}

				if ( solarSystem[choice-1] == NULL ) {
					cgc_printf("Invalid\n");
					continue;
				}

				if ( cgc_planetMenu( solarSystem[choice-1] ) == 0 ) {
					solarSystem[choice-1] = NULL;
				}

				break;
			case 5:
				cgc_printf("Exitting..\n");
				return 0;
			default:
				cgc_printf("Invalid...\n");
				break;
		};
	}

	pPlanet pl = cgc_planetTopLevel( tl );

	cgc_planetMenu(pl);

	cgc__terminate(0);
	return 0;
}
