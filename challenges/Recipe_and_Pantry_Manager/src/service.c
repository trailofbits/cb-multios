#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_malloc.h"
#include "cgc_ctype.h"

#define OUNCES	1
#define GRAMS	2

#define PANTRY_COUNT 128
#define RECIPE_COUNT 512

typedef struct instruction {
	char text[128];

	/// 4 byte cookie from magic page
	cgc_size_t cookie;

	struct instruction *next;
} instruction, *pinstruction;

typedef struct ingredient {
	double amount;
	double cost_per_unit;

	// Ounces or grams
	int type;

	char name[16];

	/// 4 byte cookie from magic page
	cgc_size_t cookie;

	struct ingredient *next;
} ingredient, *pingredient;

typedef struct pantry {
	char name[16];
	cgc_size_t cookie;

	pingredient grocery_list;
} pantry, *ppantry;

typedef struct recipe {
	char name[16];

	/// 4 byte cookie from magic page
	cgc_size_t cookie;

	pingredient ing_list;
	pinstruction ins_list;
} recipe, *precipe;

/// This is done to force ordering
typedef struct global {
	pantry pantry_g[PANTRY_COUNT];
	recipe recipe_list_g[RECIPE_COUNT];
} global, *pglobal;

global g;


cgc_size_t magic_index_g;
char *magic_page_g;

int cgc_read_selection( void )
{
	int value = 2;
	char data[2];
	cgc_size_t bytes = 0;
	cgc_size_t index = 0;

	while ( value ) {
		if ( cgc_receive( STDIN, data + index, value, &bytes) != 0 ) {
			cgc_printf("[ERROR] Failed to read data\n");
			cgc__terminate(-1);
		}

		if ( bytes == 0 ) {
			cgc_printf("[ERROR] Error with reading selection\n");
			cgc__terminate(-2);
		}

		index += bytes;
		value -= bytes;
	}

	if ( !cgc_isdigit(data[0]) ) {
		cgc_printf("[ERROR] Selection must be a digit\n");
		return 0;
	}

	if ( data[1] != '\n') {
		cgc_printf("[ERROR] Only single digits allowed in the selection\n");
		return 0;
	}

	value = cgc_atoi( data );

	return value;
}

int cgc_read_string( char *dest, cgc_size_t maxlen ) 
{
	cgc_size_t index = 0;
	cgc_size_t bytes_read = 0;
	char c = 0;

	if ( dest == NULL ) {
		return index;
	}

	while ( index < maxlen ) {
		if ( cgc_receive( STDIN, &c, 1, &bytes_read) != 0 ) {
			cgc_printf("[ERROR] Failed to read string\n");
			cgc__terminate(-3);
		}

		if ( bytes_read == 0 ) {
			cgc_printf("[ERROR] String read failure\n");
			cgc__terminate(-4);
		}

		if ( c == '\n') {
			return index;
		}

		dest[index] = c;
		index++;
	}

	return index;
}

cgc_size_t cgc_read_cookie( )
{
	cgc_size_t cookie;

	cookie = ((int *)magic_page_g)[magic_index_g/4];

	magic_index_g += 4;

	return cookie;
}

void cgc_display_banner( void )
{
	cgc_size_t month = 0;
	cgc_size_t year = 0;
	cgc_size_t day = 0;
	cgc_size_t hour = 0;
	cgc_size_t minute = 0;
	cgc_size_t second = 0;

	month = ((unsigned char*)magic_page_g)[0] % 12;
	year = 2016;

	switch (month) {
		case 1:
			day = ((unsigned char*)magic_page_g)[10] %29;
			break;
		case 3:
		case 6:
		case 9:
		case 11:
			day = ((unsigned char*)magic_page_g)[10] %30;
			break;
		default:
			day = ((unsigned char*)magic_page_g)[10] % 31;
			break;
	};

	hour = ((unsigned char*)magic_page_g)[20] % 24;
	minute = ((unsigned char*)magic_page_g)[30] % 60;
	second = ((unsigned char*)magic_page_g)[40] % 60;

	cgc_printf("Today: ");

	switch ( ((unsigned char*)magic_page_g)[50] %7 ) {
		case 0:
			cgc_printf("Sun ");
			break;
		case 1:
			cgc_printf("Mon ");
			break;
		case 2:
			cgc_printf("Tue ");
			break;
		case 3:
			cgc_printf("Wed ");
			break;
		case 4:
			cgc_printf("Thu ");
			break;
		case 5:
			cgc_printf("Fri ");
			break;
		case 6:
			cgc_printf("Sat ");
			break;
	}

	switch (month) {
		case 0:
			cgc_printf("Jan ");
			break;
		case 1:
			cgc_printf("Feb ");
			break;
		case 2:
			cgc_printf("Mar ");
			break;
		case 3:
			cgc_printf("Apr ");
			break;
		case 4:
			cgc_printf("May ");
			break;
		case 5:
			cgc_printf("Jun ");
			break;
		case 6:
			cgc_printf("Jul ");
			break;
		case 7:
			cgc_printf("Aug ");
			break;
		case 8:
			cgc_printf("Sep ");
			break;
		case 9:
			cgc_printf("Oct ");
			break;
		case 10:
			cgc_printf("Nov ");
			break;
		case 11:
			cgc_printf("Dec ");
			break;
	}

	cgc_printf("$.2d:$.2d:$.2d $d\n\n", hour, minute, second, year);

	return;
}

pinstruction cgc_instruction_prompt()
{
	pinstruction pins = NULL;

	pins = (pinstruction)cgc_malloc( sizeof( instruction) );

	if ( pins == NULL ) {
		return pins;
	}

	cgc_bzero( pins, sizeof(instruction));

	cgc_printf("Enter Instruction: ");
	if ( cgc_read_string( pins->text, 127) == 0 ) {
		cgc_free(pins);
		return NULL;
	}

	if ( cgc_strcmp( pins->text, "done") == 0 ) {
		cgc_free(pins);
		return NULL;
	}

	pins->cookie = cgc_read_cookie();

	return pins;
}

void cgc_recipe_menu( )
{
	cgc_printf("1) Add Recipe\n");
	cgc_printf("2) Remove Recipe\n");
	cgc_printf("3) List Recipe\n");
	cgc_printf("4) List All\n");
	cgc_printf("5) Print Name\n");
	cgc_printf("6) Recipe Costs\n");
	cgc_printf("7) Leave Menu\n");
	cgc_printf("-> ");

	return;
}

pingredient cgc_ingredient_prompt( )
{
	pingredient ping = NULL;
	char data[6];

	ping = ( pingredient )cgc_malloc( sizeof( ingredient) );

	if ( ping == NULL ) {
		return ping;
	}

	cgc_bzero( ping, sizeof(ingredient) );

	cgc_printf("Enter ingredient name or a \"done\" to quit.\n");
	cgc_printf(": ");

	if ( cgc_read_string( ping->name, 15) == 0 ) {
		cgc_free( ping );
		return NULL;
	}

	if ( cgc_strcmp( ping->name, "done") == 0 ) {
		cgc_free(ping);
		return NULL;
	}

	cgc_bzero( data, 6);

	cgc_printf("Enter the amount: ");
	if ( cgc_read_string( data, 5) == 0 ) {
		cgc_printf("[ERROR] Invalid amount\n");
		cgc_free(ping);
		return NULL;
	}

	ping->amount = cgc_atof( data );

	cgc_bzero( data, 6);

	cgc_printf("Enter the cost per unit: ");
	if ( cgc_read_string( data, 5) == 0 ) {
		cgc_printf("[ERROR] Invalid cost\n");
		cgc_free(ping);
		return NULL;
	}

	ping->cost_per_unit = cgc_atof( data );

	cgc_printf("Enter the type (oz/gram): ");

	cgc_bzero( data, 6 );
	if ( cgc_read_string( data, 5 ) == 0 ) {
		cgc_printf("[ERROR] Failed to read the measurement type.\n");
		cgc_free(ping);
		return NULL;
	}

	if ( cgc_strcmp( data, "oz" ) == 0 ) {
		ping->type = OUNCES;
	} else if ( cgc_strcmp( data, "gram") == 0 ) {
		ping->type = GRAMS;
	} else { 
		cgc_printf("[ERROR] Invalid type\n");
		cgc_free(ping);
		return NULL;
	}

	return ping;
}

void cgc_link_recipe_ingredient( precipe pr, pingredient ping )
{
	if ( ping == NULL || pr == NULL ) {
		return;
	}

	ping->next = pr->ing_list;
	pr->ing_list = ping;

	return;
}

int cgc_check_ingredient_exists( pingredient head, pingredient new)
{
	pingredient walker = NULL;

	if ( head == NULL || new == NULL ) {
		return 0;
	}

	walker = head;

	while ( walker ) {
		if ( cgc_strcmp( walker->name, new->name) == 0) {
			cgc_printf("Ingredient already exists. Adding the additional amount.");
			walker->amount += new->amount;
			return 1;
		}

		walker = walker->next;
	}

	return 0;
}

void cgc_link_recipe_instruction( precipe pr, pinstruction pins )
{
	pinstruction walker = NULL;

	if ( pins == NULL || pr == NULL ) {
		return;
	}

	/// Base case
	if ( pr->ins_list == NULL ) {
		pr->ins_list = pins;
		return;
	}

	walker = pr->ins_list;

	while ( walker->next ) {
		walker = walker->next;
	}

	walker->next = pins;

	return;
}

void cgc_add_recipe( void )
{
	int index = 0;
	precipe pr = NULL;
	pingredient ping = NULL;
	pinstruction pins = NULL;
	cgc_size_t t;

	while ( g.recipe_list_g[index].cookie != 0 && index < RECIPE_COUNT) {
		index++;
	}

	if ( index == RECIPE_COUNT ) {
		cgc_printf("[ERROR] Recipe List is full\n");
		return;
	}

	pr = &g.recipe_list_g[index];

	cgc_bzero( pr, sizeof(recipe) );

	cgc_printf("Enter recipe name: ");

	if ( cgc_read_string( pr->name, 15 ) == 0 ) {
		cgc_printf("[ERROR] Invalid recipe name\n");
		return;
	}

	t = index;

	/// Ensure that the recipe name does not already exist
	for ( index = 0; index < RECIPE_COUNT; index++) {
		if ( index == t ) {
			continue;
		}

		if ( g.recipe_list_g[index].cookie == 0 ) {
			continue;
		}

		if ( cgc_strcmp( g.recipe_list_g[index].name, g.recipe_list_g[t].name) == 0 ) {
			cgc_printf("[ERROR] Recipe already exists with that name.\n");
			cgc_bzero(pr->name, 16);
			return;
		}
	}

	pr->cookie = cgc_read_cookie();

	do {
		ping = cgc_ingredient_prompt();

		if ( cgc_check_ingredient_exists( pr->ing_list, ping ) ) {
			cgc_free( ping );
		} else {
			cgc_link_recipe_ingredient( pr, ping );
		}
	} while ( ping != NULL );


	do {
		pins = cgc_instruction_prompt();
		cgc_link_recipe_instruction(pr, pins);

	} while ( pins != NULL );

	return;
}


void cgc_print_recipe( int index )
{
	pingredient ing_walker = NULL;
	pinstruction ins_walker = NULL;
	cgc_size_t item = 1;

	if ( RECIPE_COUNT <= index ) {
		cgc_printf("[ERROR] Invalid index: $d\n", index);
		return;
	}

	if ( g.recipe_list_g[index].cookie == 0 ) {
		cgc_printf("[ERROR] Empty recipe: $d\n", index+1);
		return;
	}

	cgc_printf("Name: $s\n", g.recipe_list_g[index].name);
	cgc_printf("Ingredients:\n");

	ing_walker = g.recipe_list_g[index].ing_list;

	while ( ing_walker ) {
		cgc_printf("\t$f ", ing_walker->amount);
		if ( ing_walker->type == OUNCES ) {
			cgc_printf("oz\t");
		} else {
			cgc_printf("g\t");
		}

		cgc_printf("$s\n", ing_walker->name);

		ing_walker = ing_walker->next;
	}

	ins_walker = g.recipe_list_g[index].ins_list;

	cgc_printf("\nInstructions:\n");
	while ( ins_walker ) {
		cgc_printf("\t$d) $s\n", item, ins_walker->text);

		item++;
		ins_walker = ins_walker->next;
	}

	cgc_printf("\n\n");

	return;
}

void cgc_list_recipe( void )
{
	char data[5];
	int choice = 0;

	cgc_bzero(data, 5 );

	cgc_printf("Recipe Index [1..512]: ");
	if ( cgc_read_string( data, 5 ) == 0 ) {
		return;
	}

	choice = cgc_atoi( data );

	if ( choice <= 0 || RECIPE_COUNT < choice)
	{
		cgc_printf( "[ERROR] Must be between 1 and 512\n");
		return;
	}

	cgc_print_recipe( choice-1 );

	return;
}

void cgc_list_all( void )
{
	int i = 0;

	for ( i = 0; i < RECIPE_COUNT; i++) {
		if ( g.recipe_list_g[i].cookie != 0 ) {
			cgc_printf("Index: $d\n", i+1);
			cgc_print_recipe( i );
		}
	}

	return;
}

void cgc_remove_recipe( )
{
	char data[4];
	int choice = 0;

	cgc_bzero(data, 4 );

	cgc_list_all();

	cgc_printf("Recipe Index [1..512]: ");
	if ( cgc_read_string( data, 4 ) == 0 ) {
		return;
	}

	choice = cgc_atoi( data );

	if ( choice <= 0 || RECIPE_COUNT < choice ) {
		cgc_printf( "[ERROR] Must be between 1 and 512\n");
		return;
	}

	if ( g.recipe_list_g[choice-1].cookie == 0 ) {
		cgc_printf("[ERROR] Empty recipe\n");
		return;
	}

	cgc_bzero( &(g.recipe_list_g[choice-1]), sizeof(recipe) );

	return;

}

void cgc_print_recipe_costs( void )
{
	double total = 0.0;
	cgc_size_t index = 0;
	pingredient walker = NULL;

	cgc_printf("Recipe Costs:\n");

	for ( index = 0; index < RECIPE_COUNT; index++) {
		total = 0.0;

		if ( g.recipe_list_g[index].cookie == 0 ) {
			continue;
		}

		for ( walker = g.recipe_list_g[index].ing_list; walker != NULL; walker = walker->next) {
			total += walker->cost_per_unit * walker->amount;
		}

		cgc_printf("\t$d) $s - $$.5f\n", index+1, g.recipe_list_g[index].name, total);
	}


	return;
}

void cgc_print_recipe_name( void )
{
	char data[5];
	int choice = 0;

	cgc_bzero(data, 5 );

	cgc_printf("Recipe Index [1..512]: ");
	if ( cgc_read_string( data, 5 ) == 0 ) {
		return;
	}

	choice = cgc_atoi( data );

#ifdef PATCHED_1
	if ( choice <= 0 || RECIPE_COUNT < choice)
#else
	if ( RECIPE_COUNT < choice )
#endif
	{
		cgc_printf("[ERROR] Invalid index: $d\n", choice);
		return;
	}

	if ( g.recipe_list_g[choice-1].cookie == 0 ) {
		cgc_printf("[ERROR] Empty recipe: $d\n", choice);
		return;
	}

	cgc_printf("Single Name: $s\n", g.recipe_list_g[choice-1].name);

	return;
}

void cgc_handle_recipe( )
{
	int choice = 0;

	while ( 1 ) {
		cgc_recipe_menu();

		choice = cgc_read_selection();

		switch ( choice ) {
			case 1:
				cgc_add_recipe();
				break;
			case 2:
				cgc_remove_recipe();
				break;
			case 3:
				cgc_list_recipe();
				break;
			case 4:
				cgc_list_all();
				break;
			case 5:
				cgc_print_recipe_name();
				break;
			case 6:
				cgc_print_recipe_costs();
				break;
			case 7:
				cgc_printf("Leave\n");
				return;
				break;
			default:
				cgc_printf("Invalid selection.\n");
		};
	}

}

void cgc_pantry_menu( )
{
	cgc_printf( "1) Create Pantry\n");
	cgc_printf( "2) Delete Pantry\n");
	cgc_printf( "3) Print Pantry\n");
	cgc_printf( "4) Print All Pantries\n");
	cgc_printf( "5) Update Pantry\n");
	cgc_printf( "6) Leave Menu\n");
	cgc_printf("-> ");

	return;
}

void cgc_init_globals( char *secret_page )
{
	cgc_bzero( &g.pantry_g, sizeof(pantry) * PANTRY_COUNT);
	cgc_bzero( &g.recipe_list_g, sizeof(recipe) * RECIPE_COUNT);

	magic_index_g = 0;
	magic_page_g = secret_page;

	return;
}

void cgc_link_pantry_ingredient( ppantry pp, pingredient ping )
{
	if ( ping == NULL || pp == NULL ) {
		return;
	}

	ping->next = pp->grocery_list;
	pp->grocery_list = ping;

	return;
}

void cgc_print_single_pantry( cgc_size_t index )
{
	pingredient pw = NULL;
	cgc_size_t item = 1;

	if ( PANTRY_COUNT <= index ) {
		cgc_printf("[ERROR] Invalid index: $d\n", index);
		return;
	}

	if ( g.pantry_g[index].cookie == 0 ) {
		cgc_printf("[ERROR] Empty pantry: $d\n", index+1);
		return;
	}

	cgc_printf("Name: $s\n", g.pantry_g[index].name);
	cgc_printf("Item:\n");

	pw = g.pantry_g[index].grocery_list;

	while ( pw ) {
		cgc_printf("\t$f ", pw->amount);
		if ( pw->type == OUNCES ) {
			cgc_printf("oz\t");
		} else {
			cgc_printf("g\t");
		}

		cgc_printf("$s\n", pw->name);

		pw = pw->next;
	}

	cgc_printf("\n\n");

	return;

}

void cgc_print_pantry( void )
{
	char data[4];
	int choice = 0;

	cgc_bzero(data, 4 );

	cgc_printf("Pantry Index [1..128]: ");
	if ( cgc_read_string( data, 4 ) == 0 ) {
		return;
	}

	choice = cgc_atoi( data );

	if ( choice <= 0 || PANTRY_COUNT < choice ) {
		cgc_printf( "[ERROR] Must be between 1 and 128\n");
		return;
	}

	cgc_print_single_pantry( choice-1 );

	return;
}

void cgc_create_pantry( void )
{
	int index = 0;
	ppantry pp = NULL;
	pingredient ping = NULL;
	int t = 0;

	while ( g.pantry_g[index].cookie != 0 && index < PANTRY_COUNT) {
		index++;
	}

	if ( index == PANTRY_COUNT ) {
		cgc_printf("[ERROR] Pantry List is full\n");
		return;
	}

	pp = &g.pantry_g[index];

	cgc_bzero( pp, sizeof(pantry) );

	cgc_printf("Enter pantry name: ");

	if ( cgc_read_string( pp->name, 15 ) == 0 ) {
		cgc_printf("[ERROR] Invalid pantry name\n");
		return;
	}

	t = index;

	/// Ensure that the pantry name does not already exist
	for ( index = 0; index < PANTRY_COUNT; index++) {
		if ( index == t ) {
			continue;
		}

		if ( g.pantry_g[index].cookie == 0 ) {
			continue;
		}

		if ( cgc_strcmp( g.pantry_g[index].name, g.pantry_g[t].name) == 0 ) {
			cgc_printf("[ERROR] Pantry already exists with that name.\n");
			cgc_bzero(pp->name, 16);
			return;
		}
	}

	pp->cookie = cgc_read_cookie();

	do {
		ping = cgc_ingredient_prompt();

		if ( cgc_check_ingredient_exists( pp->grocery_list, ping ) ) {
			cgc_free(ping);
		} else { 
			cgc_link_pantry_ingredient( pp, ping );
		}
	} while ( ping != NULL );

	return;
}

void cgc_list_all_pantries( void )
{
	int i = 0;

	for ( i = 0; i < PANTRY_COUNT; i++) {
		if ( g.pantry_g[i].cookie != 0 ) {
			cgc_printf("Index: $d\n", i+1);
			cgc_print_single_pantry( i );
		}
	}

	return;
}

void cgc_delete_pantry( void )
{
	char data[4];
	int choice = 0;

	cgc_bzero(data, 4 );

	cgc_list_all_pantries();

	cgc_printf("Pantry Index [1..128]: ");
	if ( cgc_read_string( data, 4 ) == 0 ) {
		return;
	}

	choice = cgc_atoi( data );

	if ( choice <= 0 || PANTRY_COUNT < choice ) {
		cgc_printf( "[ERROR] Must be between 1 and 128\n");
		return;
	}

	if ( g.pantry_g[choice-1].cookie == 0 ) {
		cgc_printf("[ERROR] Empty pantry\n");
		return;
	}

	cgc_bzero( &(g.pantry_g[choice-1]), sizeof(pantry) );

	return;
}

void cgc_update_pantry( void )
{
	char data[16];
	int choice = 0;
	ppantry pp = NULL;
	pingredient ing_walker = NULL;

	cgc_bzero(data, 16 );

	cgc_list_all_pantries();

	cgc_printf("Pantry Index [1..128]: ");
	if ( cgc_read_string( data, 4 ) == 0 ) {
		return;
	}

	choice = cgc_atoi( data );

	if ( choice <= 0 || PANTRY_COUNT < choice ) {
		cgc_printf( "[ERROR] Must be between 1 and 128\n");
		return;
	}

	if ( g.pantry_g[choice-1].cookie == 0 ) {
		cgc_printf("[ERROR] Empty pantry\n");
		return;
	}

	pp = &g.pantry_g[choice-1];

	cgc_print_single_pantry( choice-1 );

	cgc_printf("Which item to update: ");

	cgc_bzero( data, 16 );

	if ( cgc_read_string( data, 15) == 0 ) {
		return;
	}

	ing_walker = pp->grocery_list;

	while ( ing_walker ) {
		if ( cgc_strcmp( ing_walker->name, data ) != 0 ) {
			ing_walker = ing_walker->next;
		} else {
			break;
		}
	}

	if ( ing_walker == NULL ) {
		cgc_printf("This pantry does not have $s\n", data );
		return;
	}

	cgc_bzero( data, 16);

	cgc_printf("Enter the amount: ");
	if ( cgc_read_string( data, 5) == 0 ) {
		cgc_printf("[ERROR] Invalid amount\n");
		return;
	}

	ing_walker->amount = cgc_atof( data );

	cgc_printf("Enter the type (oz/gram): ");

	cgc_bzero( data, 16 );
	if ( cgc_read_string( data, 5 ) == 0 ) {
		cgc_printf("[ERROR] Failed to read the measurement type.\n");
		return;
	}

	if ( cgc_strcmp( data, "oz" ) == 0 ) {
		ing_walker->type = OUNCES;
	} else if ( cgc_strcmp( data, "gram") == 0 ) {
		ing_walker->type = GRAMS;
	} else { 
		cgc_printf("[ERROR] Invalid type\n");
	}

	return;

}

void cgc_handle_pantry( void )
{
	int choice = 0;

	while ( 1 ) {
		cgc_pantry_menu();

		choice = cgc_read_selection();

		switch (choice) {
			case 1:
				cgc_create_pantry();
				break;
			case 2:
				cgc_delete_pantry();
				break;
			case 3:
				cgc_print_pantry();
				break;
			case 4:
				cgc_list_all_pantries();
				break;
			case 5:
				cgc_update_pantry();
				break;
			case 6:
				cgc_printf("Leave.\n");
				return;
				break;
			default:
				cgc_printf("Invalid selection\n");
				break;
		};
	}

	return;
}

void cgc_query_recipes( void )
{
	cgc_size_t index;
	char data[16];
	cgc_size_t selection;
	int found;

	/// Recipe ingredient walker
	pingredient riw = NULL;

	/// Pantry ingredient walker
	pingredient piw = NULL;

	cgc_printf("Select a pantry:\n");

	for ( index = 0; index < PANTRY_COUNT; index++) {
		if ( g.pantry_g[index].cookie != 0 ) {
			cgc_printf("$d) $s\n", index+1, g.pantry_g[index].name);
		}
	}

	cgc_printf("-> ");

	if ( cgc_read_string( data, 4 ) == 0 ) {
		return;
	}

	selection = cgc_atoi( data );

	if ( selection <= 0 || PANTRY_COUNT < selection) {
		cgc_printf("[ERROR] Invalid selection\n");
		return;
	}

	if ( g.pantry_g[selection-1].cookie == 0 ) {
		cgc_printf("[ERROR] Empty pantry\n");
		return;
	}

	/// Loop through each recipe.
	/// For each ingredient loop through the grocery list of the pantry
	/// If the ingredient is found, check the amount.
	/// If there is enough then check the next ingredient
	///	If not then move on to the next recipe.
	for ( index = 0; index < RECIPE_COUNT; index ++ ) {
		if ( g.recipe_list_g[index].cookie == 0 ) {
			continue;
		}

		found = 0;

		for ( riw = g.recipe_list_g[index].ing_list; riw != NULL; riw = riw->next ) {

			found = 0;
			for ( piw = g.pantry_g[selection-1].grocery_list; piw != NULL && found == 0; piw = piw->next ) {
				if ( cgc_strcmp( piw->name, riw->name) != 0 ) {
					continue;
				}

				if ( piw->amount < riw->amount) {
					continue;
				}

				found = 1;
			}

			if ( found == 0 ) {
				break;
			}

		}

		if ( found != 0 ) {
			cgc_printf("You can make: $s\n", g.recipe_list_g[index].name);
		}

	}

	return;
}

void cgc_query_by_price( void )
{
	char data[10];
	double max = 0.0;
	cgc_size_t index = 0;
	pingredient walker = NULL;
	double total = 0.0;

	cgc_bzero( data, 10);

	cgc_printf("How much can you spend: ");

	if ( cgc_read_string( data, 9 ) == 0 ) {
		return;
	}

	max = cgc_atof( data );

	cgc_printf("You can make: \n");
	for ( index = 0; index < RECIPE_COUNT; index++) {
		total = 0.0;

		if ( g.recipe_list_g[index].cookie == 0 ) {
			continue;
		}

		for ( walker = g.recipe_list_g[index].ing_list; walker != NULL; walker = walker->next) {
			total += walker->cost_per_unit * walker->amount;
		}

		if ( total <= max ) {
			cgc_printf("\t$d) $s\n", index+1, g.recipe_list_g[index].name);
		}
	}
	return;
}

void cgc_print_cheapest( void )
{
	double cheapest_value = 0.0;
	cgc_size_t cheapest_index = 0;
	cgc_size_t index = 0;
	pingredient walker = NULL;
	double total = 0.0;

	for ( index = 0; index < RECIPE_COUNT; index++) {
		total = 0.0;

		if ( g.recipe_list_g[index].cookie == 0 ) {
			continue;
		}

		for ( walker = g.recipe_list_g[index].ing_list; walker != NULL; walker = walker->next) {
			total += walker->cost_per_unit * walker->amount;
		}

		/// If this is the first one then it is automatically the cheapest
		if ( cheapest_index == 0 ) {
			cheapest_index = index+1;
			cheapest_value = total;
		} else if ( total < cheapest_value ) {
			cheapest_value = total;
			cheapest_index = index+1;
		}
	}

	if ( cheapest_index == 0 ) {
		cgc_printf("No cheapest recipe found\n");
	} else {
		cgc_printf("Cheapest: $d at $f\n", cheapest_index, cheapest_value);
	}

	return;

}

void cgc_print_expensivest( void )
{
	double expensivest_value = 0.0;
	cgc_size_t expensivest_index = 0;
	cgc_size_t index = 0;
	pingredient walker = NULL;
	double total = 0.0;

	for ( index = 0; index < RECIPE_COUNT; index++) {
		total = 0.0;

		if ( g.recipe_list_g[index].cookie == 0 ) {
			continue;
		}

		for ( walker = g.recipe_list_g[index].ing_list; walker != NULL; walker = walker->next) {
			total += walker->cost_per_unit * walker->amount;
		}

		/// If this is the first one then it is automatically the most expensive
		if ( expensivest_index == 0 ) {
			expensivest_index = index + 1;
			expensivest_value = total;
		} else if ( expensivest_value < total ) {
			expensivest_value = total;
			expensivest_index = index+1;
		}
	}

	if ( expensivest_index == 0 ) {
		cgc_printf("The most expensive recipe was not found\n");
	} else {
		cgc_printf("Most expensive: $d at $f\n", expensivest_index, expensivest_value);
	}

	return;

}

void cgc_query_menu( void )
{
	int value = 0;

	while ( 1 ) {
		cgc_printf("1) List Doable Recipes by Pantry\n");
		cgc_printf("2) List Doable Recipes by Cost\n");
		cgc_printf("3) Print Cheapest Recipe\n");
		cgc_printf("4) Print Most Expensive Recipe\n");
		cgc_printf("5) Leave Menu\n");
		cgc_printf("-> ");

		value = cgc_read_selection();

		switch(value) {
			case 1:
				cgc_query_recipes();
				break;
			case 2:
				cgc_query_by_price();
				break;
			case 3:
				cgc_print_cheapest();
				break;
			case 4:
				cgc_print_expensivest();
				break;
			case 5:
				cgc_printf("Leaving..\n");
				return;
				break;
			default:
				cgc_printf("[ERROR] Invalid selection\n");
				break;
		};

	}

	return;
}

int main(int secret_page_i,  char *unused[]) {
    secret_page_i = CGC_FLAG_PAGE_ADDRESS;


	int value = 0;
	cgc_size_t eax;
	cgc_size_t eip;

	cgc_init_globals( (char*)secret_page_i);

	cgc_display_banner();

	while ( 1 ) {
		cgc_printf( "1) Recipe Menu\n");
		cgc_printf( "2) Pantry Menu\n");
		cgc_printf( "3) Query Recipe\n");
		cgc_printf( "4) Quit\n");
		cgc_printf( "-> ");
	
		value = cgc_read_selection( );

		switch (value) {
			case 1:
				cgc_handle_recipe();
				break;
			case 2:
				cgc_handle_pantry();
				break;
			case 3:
				cgc_query_menu();
				break;
			case 4:
				cgc_printf("Quit\n");
				cgc__terminate(0);
				break;
			default:
				cgc_printf("unknown\n");
				break;
		};
	}
	return 0;
}
