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

#ifndef SERVICE_H
#define SERVICE_H

typedef struct Ingredient {

	char measurement[20];
	char item[100];
	struct Ingredient *next;

} Ingredient_Type;


typedef struct Recipe {

	char Title[200];
	int Tagged;
	Ingredient_Type *Ingredient_List;
	char **Instructions;
	struct Recipe *next;

} Recipe_Type;


typedef struct List {

	char *item;
	struct List *next;

} Shopping_List_Type;


void print_main_menu(void);
int new_recipe(Recipe_Type **);
int get_ingredients(Recipe_Type *);
void get_instructions(Recipe_Type *);
void print_all_tagged(Recipe_Type *);
void find_recipe(Recipe_Type *);
void print_recipe(Recipe_Type *);
void print_shopping_list(Recipe_Type *);
Shopping_List_Type *build_shopping_list(Recipe_Type *);
int match_str(char *search, char *);
int validate_measurement(char *);
void sort_shopping_list(Shopping_List_Type *);
int compare_strings(char *, char *);
int split_ingredient(char *, char *, int, char *, int);

//int parse_command(char *buffer, char separator, char ***args);
//void find_matches(bst_node_type *head, int arg_count, char **args);
#endif
