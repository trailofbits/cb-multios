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

#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_service.h"
#include "cgc_menu.h"

logbook_type cgc_logbook;

int main(int cgc_argc, char *cgc_argv[]) {
    
    menu_item menu[] = {

    	{"Change Diver Info","Cc", cgc_edit_diver },
   		{"Log a New Dive","Ll", cgc_log_dives },
   		{"Download Dive Data","Dd", cgc_download_dive },
   		{"Edit Dives", "Ee", cgc_edit_dives },
   		{"Print Dive Logs","Pp", cgc_print_dives },
   		{"Remove Dives", "Rr", cgc_remove_dives },
   		{"Diver Statistics","Ss", cgc_dive_statistics },
   		{"Exit Application", "Xx", cgc_exit_app}

   };


  	cgc_bzero((void *)&cgc_logbook, sizeof(cgc_logbook));

  	cgc_process_menu(menu, sizeof(menu)/ sizeof(menu_item));

 
}  // main  


int cgc_exit_app(int ret_code)
{

	cgc__terminate(ret_code);

}
