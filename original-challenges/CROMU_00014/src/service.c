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
#include "stdlib.h"
#include "service.h"
#include "menu.h"

logbook_type logbook;

int main(void) {
    
    menu_item menu[] = {

    	{"Change Diver Info","Cc", edit_diver },
   		{"Log a New Dive","Ll", log_dives },
   		{"Download Dive Data","Dd", download_dive },
   		{"Edit Dives", "Ee", edit_dives },
   		{"Print Dive Logs","Pp", print_dives },
   		{"Remove Dives", "Rr", remove_dives },
   		{"Diver Statistics","Ss", dive_statistics },
   		{"Exit Application", "Xx", exit_app}

   };


  	bzero((void *)&logbook, sizeof(logbook));

  	process_menu(menu, sizeof(menu)/ sizeof(menu_item));

 
}  // main  


int exit_app(int ret_code)
{

	_terminate(ret_code);

}
