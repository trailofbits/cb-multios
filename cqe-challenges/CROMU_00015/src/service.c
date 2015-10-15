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

#include "service.h"
#include "planetParsers.h"

pPlanet solarSystem[10];

int main( void )
{
	int choice = 0;
	char selection[30];
	pstring tl = NULL;
	pPlanet pp = NULL;
	char *temp = NULL;

	bzero( solarSystem, sizeof(pPlanet) * 10 );

	while (1) {
		printf("\nPlanet Markup Language Main\n");
		printf("1) Print Planets\n");
		printf("2) Add PML\n");
		printf("3) Add Planet\n");
		printf("4) Select Planet\n");
		printf("5) Exit\n");
		printf("Selection: ");

		bzero(selection, 30);
		receive_until( selection, '\n', 4 );

		choice = atoi( selection );

		switch (choice) {
			case 1:
				for ( choice = 0; choice < 10; choice++ ) {
					if ( solarSystem[choice] != NULL ) {
						printPlanetInfo( solarSystem[choice] );
					}
				}
				break;
			case 2:
				if ( allocate( 4096, 0, (void**)&temp) != 0 ) {
					temp = NULL;
					continue;
				}
	
				printf("PML: ");
				bzero( temp, 4096);
				receive_until( temp, '\n', 4095);
				tl = initString( temp );
				deallocate(temp, 4096);

				if ( tl == NULL ) {
					continue;
				} else if ( tl->buffer == NULL ) {
					deallocate( tl, sizeof(string));
					continue;
				}

				choice = 0;
				while ( choice < 10 ) {
					if ( solarSystem[choice] != NULL ) {
						choice++;
						continue;
					}

					solarSystem[choice] = planetTopLevel(tl);

					if ( solarSystem[choice] == NULL ) {
						break;
					}

					choice++;
				}
				
				freeString(tl);
				break;
			case 3:
				printf("\n-> ");
				bzero(selection, 30);

				receive_until( selection, '\n', 29 );

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

				if ( allocate( sizeof(Planet), 0, (void**)&pp) != 0 ) {
					pp = NULL;
					break;
				}

				initPlanet(pp);


				solarSystem[choice] = pp;

				choice = 0;
				while ( isalnum(selection[choice]) ) {
					pp->name[choice] = selection[choice];
					choice++;
				}
					
				break;
			case 4:
				for (choice=0; choice < 10; choice++) {
					if ( solarSystem[choice] != NULL ) {
						printf("@d) @s\n", choice +1, solarSystem[choice]->name);
					}
				}

				bzero( selection, 30);
				printf("\n-> ");
				receive_until(selection, '\n', 4 );

				choice = atoi(selection);

				if ( choice < 1 || choice > 10 ) {
					printf("Invalid\n");
					continue;
				}

				if ( solarSystem[choice-1] == NULL ) {
					printf("Invalid\n");
					continue;
				}

				if ( planetMenu( solarSystem[choice-1] ) == 0 ) {
					solarSystem[choice-1] = NULL;
				}

				break;
			case 5:
				printf("Exitting..\n");
				return 0;
			default:
				printf("Invalid...\n");
				break;
		};
	}

	pPlanet pl = planetTopLevel( tl );

	planetMenu(pl);

	_terminate(0);
	return 0;
}
