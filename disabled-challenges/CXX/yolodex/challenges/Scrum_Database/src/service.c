/*

Author: Steve Wood <swood@cromulence.com>

Copyright (c) 2015 Cromulence LLC

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
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_output_strings.h"

char *cgc_obf_strings(char *input_string);

extern char test[];

int main(int cgc_argc, char *cgc_argv[]) {

	unsigned int databaseCheck;
	productDefType *productDatabase;

	productDatabase = 0; 

	databaseCheck = cgc_calc_version();

	cgc_printf(cgc_obf_strings(cgc_Tool_Title), databaseCheck);

	// wait for commands
 	cgc_receive_commands(&productDatabase); 

	// clean up the data structures
   cgc_destroy_database( &productDatabase );

    cgc__terminate(0);

}  // main  

