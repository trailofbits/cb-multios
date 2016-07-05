/*

Author: Steve Wood <swood@cromulence.co>

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

#include <libcgc.h>
#include "menu.h"
#include "stdlib.h"
#include "service.h"

extern logbook_type logbook;

int process_menu(menu_item *menu, int num_items)  {
	
	int i;
	int rcv_cnt;
	char buf[24];

    // start the main menu loop
     while (1) {

		printf("\n");
		
		// print the menu items
		for (i=0;i< num_items;++i)  {

			printf("@c - @s\n", menu[i].command[0], menu[i].prompt);

		}

		printf(":");
		
	    rcv_cnt=getline(buf, sizeof(buf));
		
		if (rcv_cnt==0)
		    continue;

	    printf("\n");

	    // find entry associated with the ccommand char entered and execute it
		for (i=0;i< num_items;++i) {

			if (find_char(buf[0], menu[i].command))  {
				
				if (menu[i].Action==0)
					return 0;
		
				menu[i].Action(&logbook);
				break;

			}
		}


    }  // while


return 0;

}


int find_char(char c, char *string)  {

	int i;

	for (i=0; i< strlen(string); ++i) {

		if (string[i]== c)
			return 1;
	}

	return 0;

}