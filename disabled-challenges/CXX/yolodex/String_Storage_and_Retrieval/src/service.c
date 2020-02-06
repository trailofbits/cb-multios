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
#include "cgc_bst.h"


int main(int cgc_argc, char *cgc_argv[]) {
    
    bst_node_type *head;
    data_item_type *item;
    bst_stats_type stats;
    long value;
    char buffer[2048];  
    cgc_size_t size;
    char **args;
    int arg_count;
    int i;



    // loop forever receiving command strings from STDIN.
    while (1) {

        size=cgc_getline(buffer, sizeof(buffer));

        // ignore that a blank line was entered
        if (size==0)
            continue;

        // break the command into an array 
        arg_count=cgc_parse_command(buffer, '/', &args);

        if (arg_count == -1)
            continue;
        
        // add a new element to the database
        if (args[0][0]=='a' && arg_count==2 ) {

            // if the string to add is less than 10 chars, ignore the add command
            if (cgc_strlen(args[1]) < 10) {

                cgc_free(args);
                continue;
            }

            item=cgc_calloc(1, sizeof(data_item_type));

            if (!item) {

                cgc_printf("Unable to allocate memory\n");
                return(-1);
            }

            cgc_strncpy(item->name, args[1], sizeof(item->name)-1);
            item->next = 0;

            cgc_insert_node(&head, item, cgc_make_key_from_name);

        }
        // search for elements of the database
        else if (args[0][0]=='f' && arg_count==2) {

            cgc_find_matches(head, arg_count, args);

        }
        // delete an element from the database
        else if (args[0][0]=='d' && arg_count==2) {

            cgc_delete_matches(&head, arg_count, args);

        }
        // time to cgc_exit
        else if (args[0][0]=='x') {

            return(0);
        }
        // walk the database and show all entries
        else if (args[0][0]=='w' ) {

            cgc_walk_tree(head);
        }
        else if (args[0][0]=='s' ) {

            // clear the stats
            cgc_bzero(&stats, sizeof(stats));

            cgc_count_bst_stats(head, &stats);

            cgc_printf("# of Nodes: @d\n", stats.node_count);
            cgc_printf("\% left nodes: @d\n", stats.percent_left);
            cgc_printf("\% right nodes: @d\n", stats.percent_right);

        }
        
        cgc_free(args);
    }

 
}  // main  

