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


Recipe_Type *recipe_book=0;

int main(void) {
    
size_t size;
char buffer[10];
int command;
char buffer1[100];
char buffer2[100];


    // loop forever receiving command strings from STDIN.
    while (1) {

        print_main_menu();

        size=getline(buffer, sizeof(buffer));

        // ignore that a blank line was entered
        if (size==0)
            continue;

        command=atoi(buffer);

        switch (command) {


            case 1:

                new_recipe(&recipe_book);
                break;

            case 2:

                find_recipe(recipe_book);
                break;

            case 3:

                print_all_tagged(recipe_book);
                break;

            case 4:

                print_shopping_list(recipe_book);
                break;
            case 5:

                _terminate(0);
                break;

            default:

                printf("Invalid command\n");


        } // switch

      
    }  // while(1)

 
}  // main  

