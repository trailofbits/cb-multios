#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_malloc.h"
#include "cgc_monster_names.h"

#define TREE 	'#'
#define EXIT 	'X'
#define PERSON	'@'
#define MAX_MONSTER_LIFE	10
#define MAX_MONSTER_POWER	6
#define MAX_CAPTURE		5

typedef struct queue {
	cgc_size_t x;
	cgc_size_t y;
	struct queue *next;
} queue, *pqueue;

typedef struct map {
	cgc_size_t width;
	cgc_size_t height;
	cgc_size_t start_x;
	cgc_size_t start_y;
	cgc_size_t end_x;
	cgc_size_t end_y;

	cgc_size_t current_x;
	cgc_size_t current_y;

	/// Last x where a marker was placed. Used to reverse on failure
	cgc_size_t last_x;

	/// Last y where a marker was placed
	cgc_size_t last_y;

	/// Map data
	char *data;
} map, *pmap;

typedef struct monster {
	char *type;
	int health;
	cgc_size_t hitpoints;
	cgc_size_t power;
	cgc_size_t experience;
	cgc_size_t level;
} monster, *pmonster;

typedef struct player {
	char name[16];
	cgc_size_t level;
	cgc_size_t mcnt;
	pmonster mons[MAX_CAPTURE];
} player, *pplayer;

/// Index to use for the secret page
cgc_size_t cgc_page_index = 0;
unsigned char *secret_page;

/// queue list
pqueue root;

char *queue_matrix;

/// Variables for the easter egg
char easteregg[] = "easta egg";
cgc_size_t eggindex;

pmonster cgc_generate_monster( void );
char *cgc_select_name( void );

void cgc_check_egg( pplayer pp, char c ) {
	if ( easteregg[ eggindex ] == c ) {
		eggindex += 1;
	} else { 
		eggindex = 0;
	}

	if ( easteregg[eggindex] == 0 ) {
		cgc_printf("YOU FOUND THE EGG!!!! Have a prize.\n");
		pp->mons[0]->hitpoints = 99;
		pp->mons[0]->health = 99;
		pp->mons[0]->power = 99;

		eggindex = 0;
	}

	return;
}

cgc_size_t cgc_read_line( char *outbuf, cgc_size_t length )
{
	char c = '\0';
	cgc_size_t index = 0;
	cgc_size_t rx_bytes = 0;

	if ( outbuf == NULL ) {
		cgc_printf("[ERROR] invalid arg\n");
		cgc__terminate(-1);
		return 0;
	}

	while ( index < length && c != '\n') {
		if ( cgc_receive( STDIN, &c, 1, &rx_bytes) != 0 ) {
			cgc_printf("[ERROR] Failed to read byte\n");
			cgc__terminate(-3);
		}

		if ( rx_bytes == 0 ) {
			cgc_printf("[ERROR] Error in receive\n");
			cgc__terminate(-4);
		}

		if ( c == '\n') {
			return index;
		}

		outbuf[index] = c;
		index++;
	}

	return index;
}

cgc_size_t cgc_read_line_u( char *outbuf )
{
	char c = '\0';
	cgc_size_t index = 0;
	cgc_size_t rx_bytes = 0;

	if ( outbuf == NULL ) {
		return 0;
	}

	while ( c != '\n' ) {
		if ( cgc_receive( STDIN, &c, 1, &rx_bytes) != 0 ) {
			cgc_printf("[ERROR] Failed to read byte\n");
			cgc__terminate(0);
		}

		if ( rx_bytes == 0 ) {
			cgc_printf("[ERROR] Error in receive\n");
			cgc__terminate(0);
		}

		if ( c == '\n') {
			continue;
		}

		outbuf[index] = c;
		index++;
	}

	return index;
}

void cgc_add_queue( cgc_size_t x, cgc_size_t y, cgc_size_t max_x, cgc_size_t max_y )
{
	pqueue pq = NULL;
	pqueue walker = NULL;
	cgc_size_t index = ( (max_x+1) * y ) + x;

	/// If it has already been queued then don't requeue it
	if ( queue_matrix[index] == 1 ) {
		return;
	}

	pq = cgc_malloc( sizeof(queue) );

	if ( pq == NULL ) {
		cgc_printf("[ERROR] malloc() queue structure failed.\n");
		cgc__terminate(-1);
	}

	cgc_bzero( pq, sizeof( queue ) );

	pq->x = x;
	pq->y = y;

	// base case
	if ( root == NULL ) {
		root = pq;
	} else {
		walker = root;

		while ( walker->next != NULL ) {
			walker = walker->next;
		}

		walker->next = pq;
	}

	queue_matrix[index] = 1;

	return;
}

pqueue cgc_dequeue( )
{
	pqueue pq = root;

	if ( root != NULL ) {
		root = root->next;
	}

	return pq;
}

/// Determine if they are adjacent
int cgc_check_adjacent( sx, sy, dx, dy )
{
	if ( sx == dx ) {
		if ( (( sy + 1 ) == dy) || ( (sy - 1 ) == dy ) ) {
			return 1;
		}
	} else if ( sy == dy ) {
		if ( (( sx + 1 ) == dx) || ( (sx - 1 ) == dx ) ) {
			return 1;
		}
	}

	return 0;
}

void cgc_print_map( pmap pm )
{
	cgc_size_t index;
	cgc_size_t max;
	cgc_size_t map_index = 0;

	char *data = NULL;

	index = 0;
	max = pm->height * pm->width;

	/// 1 byte for each block, height bytes for the new lines 1 byte for the NULL
	data = cgc_malloc( max + pm->height + 1 );

	if ( data == NULL ) {
		cgc_printf("[ERROR] Failed to allocate map.\n");
		cgc__terminate(-5);
	}

	cgc_bzero( data, max + pm->height + 1);

	while ( index < max ) {
		if ( 0 < index && (index % pm->width)==0 ) {
			data[map_index++] = '\n';
		}

		if ( pm->data[index] == '\0') {
			data[map_index] = '.';
		} else {
			data[map_index] = pm->data[index];
		}

		index++;
		map_index++;
	}

	data[map_index] = '\n';
	
	cgc_printf("$s", data);

	cgc_free(data);

}

/// Algorithm
/// Given source(x,y) and dest(x,y) does there exist a path between the two
/// Returns 0 if a path does not exist and 1 if it does
cgc_size_t cgc_find_path( cgc_size_t sx, cgc_size_t sy, pmap pm)
{
	pqueue pq = NULL;
	cgc_size_t retval = 0;

	if ( pm == NULL ) {
		return 0;
	}

	/// Look up, down, left, right if destination is adjacent then success
	if ( cgc_check_adjacent( sx, sy, pm->end_x, pm->end_y ) == 1 ) {
		return 1;
	}

	/// Else queue up, down, left, right

	// Up
	if ( sy > 0 ) {
		cgc_add_queue( sx, sy - 1, pm->width-1, pm->height-1 );
	}
	
	// Right
	if ( sx < pm->width-1 ) {
		cgc_add_queue( sx + 1, sy, pm->width-1, pm->height-1 );
	}

	// Down
	if ( sy < pm->height-1 ) {
		cgc_add_queue( sx, sy + 1, pm->width-1, pm->height-1);
	}

	// Left
	if ( sx > 0 ) {
		cgc_add_queue( sx - 1, sy, pm->width-1, pm->height-1 );
	}

	pq = cgc_dequeue();

	while ( pq != NULL ) {
		retval = cgc_find_path( pq->x, pq->y, pm);

		if ( retval == 1 ) {
			cgc_free(pq);
			return 1;
		} else {
			cgc_free(pq);
			pq = cgc_dequeue();
		}
	}

	return 0;
}

void cgc_update_page_index( )
{
	cgc_page_index += 3;

	cgc_page_index = cgc_page_index % 0x1000;
	return;
}

void cgc_place_marker( pmap pm )
{
	cgc_size_t index = 0;
	cgc_size_t count = 0;
	cgc_size_t max = 0;

	pm->last_x = secret_page[ cgc_page_index ] % pm->width;
	cgc_update_page_index();

	pm->last_y = secret_page[ cgc_page_index ] % pm->height;
	cgc_update_page_index();

	index = ( pm->width * pm->last_y ) + pm->last_x;

	while ( pm->data[index] != '\0' && count < 100 ) {
		pm->last_x = secret_page[ cgc_page_index ] % pm->width;
		cgc_update_page_index();

		pm->last_y = secret_page[ cgc_page_index ] % pm->height;
		cgc_update_page_index();

		index = ( pm->width * pm->last_y ) + pm->last_x;

		count++;
	}

	max = pm->width * pm->height;

	/// Just loop until one is found
	if ( count == 100 ) {
		index = 0;

		while ( pm->data[index] != '\0' && index < max ) {
			index++;
		}

		if ( index == max ) {
			cgc_printf("FAILED\n");
			cgc_print_map( pm );
			cgc__terminate(0);
		}

		pm->last_y = index / pm->width;
		pm->last_x = index % pm->width;
	}

	pm->data[index] = '#';

	return;
}

void cgc_set_marker( cgc_size_t x, cgc_size_t y, pmap pm, char c )
{
	cgc_size_t index = ( (pm->width) * y ) + x;

	pm->data[index] = c;
}

/// Clear the map data
/// Select the start and end coords and place them on the map
void cgc_initialize_map( pmap pm )
{
	if ( pm == NULL ) {
		cgc_printf("[ERROR] initialize_map() invalid argumenet.\n");
		cgc__terminate(0);
	}

	pm->data = cgc_malloc( pm->width * pm->height );

	if ( pm->data == NULL ) {
		cgc_printf("[ERROR] Failed to allocate map.\n");
		cgc__terminate(0);
	}

	cgc_bzero( pm->data, pm->width * pm->height);

	pm->start_x = 0;
	pm->start_y = 0;
	pm->end_x = 0;
	pm->end_y = 0;

	while ( (pm->start_x==pm->end_x) || ( pm->start_x-1 == pm->end_x) || (pm->start_x+1 == pm->end_x)
				|| (pm->start_y == pm->end_y) || ( pm->start_y+1 == pm->end_y) || (pm->start_y - 1 == pm->end_y) ) {

		/// Decide on the start and the end position
		pm->start_x = secret_page[cgc_page_index] % pm->width;
		cgc_update_page_index();

		pm->start_y = secret_page[cgc_page_index] % pm->height;
		cgc_update_page_index();

		pm->end_x = secret_page[cgc_page_index] % pm->width;
		cgc_update_page_index();

		pm->end_y = secret_page[cgc_page_index] % pm->height;
		cgc_update_page_index();
	}

	cgc_set_marker( pm->start_x, pm->start_y, pm, PERSON);
	cgc_set_marker( pm->end_x, pm->end_y, pm, EXIT);

	pm->current_x = pm->start_x;
	pm->current_y = pm->start_y;

	return;
}

/// Initialize the queue matrix
void cgc_initialize_queue_matrix( pmap pm )
{
	cgc_size_t index;

	if (queue_matrix != NULL ) {
		cgc_free( queue_matrix);
	}

	queue_matrix = cgc_malloc( pm->width * pm->height );

	if ( queue_matrix == NULL ) {
		cgc_printf("[ERROR] Failed to allocate queue matrix\n");
		cgc__terminate(0);
	}

	cgc_bzero( queue_matrix, pm->width * pm->height );

	/// If the map contains an obstruction then mirror that in the matrix
	for ( index = 0; index < pm->width * pm->height; index ++ ) {
		if ( pm->data[index] != 0x00 ) {
			queue_matrix[index] = 1;
		}
	}

	return;
}

pmap cgc_generate_map( cgc_size_t width, cgc_size_t height )
{
	pmap pm = NULL;
	pqueue t = NULL;
	cgc_size_t start_x = 0;
	cgc_size_t start_y = 0;

	cgc_size_t end_x = 0;
	cgc_size_t end_y = 0;
	cgc_size_t success = 1;

	pm = cgc_malloc( sizeof(map) );

	if ( pm == NULL ) {
		cgc_printf("[ERROR] Failed to allocate map strucure\n");
		cgc__terminate(0);
	}

	cgc_bzero( pm, sizeof(map) );

	pm->height = height;
	pm->width = width;

	cgc_initialize_map ( pm );

	cgc_printf("Width: $d Height: $d\nStartX: $d StartY: $d\nEndX: $d EndY: $d\n\n", width, height, pm->start_x, pm->start_y, pm->end_x, pm->end_y);

	while ( success) {

		/// place a new marker
		cgc_place_marker(pm);

		/// Initialize a new queue matrix
		cgc_initialize_queue_matrix( pm );

		if ( cgc_find_path( pm->start_x, pm->start_y, pm) != 1 ) {
			/// Reverse the last marker
			pm->data[ ( pm->width * pm->last_y) + pm->last_x ]  = 0x00;

			success = 0;
		}

		/// Free any remaining queue structures
		while ( root ) {
			t = root;
			root = root->next;

			cgc_free ( t );
		}

		root = NULL;

	}

	/// Free the matrix
	cgc_free( queue_matrix );

	cgc_print_map( pm );
	

	return pm;
}

pmonster cgc_select_monster( pplayer pp )
{
	cgc_size_t index;
	cgc_size_t choice = 0;
	cgc_size_t success = 0;

	int ac = 0;

	if ( pp == NULL ) {
		return NULL;
	}

	for ( index = 0; index < pp->mcnt; index++ ) {
		if ( pp->mons[index]->health > 0 ) {
			success = 1;
		}
	}

	if ( success == 0 ) {
		return NULL;
	}

	success = 0;

	cgc_printf("Monsters: \n");
	for ( index = 0; index < pp->mcnt; index++ ) {
		cgc_printf("\t$d} \n", index+1);
		cgc_printf("\tType: $s\n", pp->mons[index]->type);
		cgc_printf("\tLevel: $d\n", pp->mons[index]->level);
		cgc_printf("\tHealth: $d\n", pp->mons[index]->health);
		cgc_printf("\tPower: $d\n\n", pp->mons[index]->power);
	}

	while ( !success ) {
		cgc_printf("Selection: ");

		choice = 0;
		cgc_read_line( (char*)&choice, 2);

		ac = cgc_atoi( (char*)&choice );

		if ( ac <= 0 || ac > pp->mcnt ) {
			cgc_printf("bad choice: $x\n", choice);
		} else if ( pp->mons[ac-1] == NULL ) {
			cgc_printf("bad choice: $x\n", choice);
		} else if ( pp->mons[ac-1]->health <= 0 ) {
			cgc_printf("he dead\n");
		} else {
			success = 1;
		}
	}

	return pp->mons[ac-1];
}

void cgc_reset_monsters( pplayer pp )
{
	cgc_size_t index = 0;

	if ( pp == NULL ) {
		return;
	}

	/// Reset the hit points of each monster
	for ( index = 0; index < pp->mcnt; index++ ) {
		pp->mons[index]->health = pp->mons[index]->hitpoints;
	}


	return;
}

void cgc_print_monster( pmonster pm )
{
	if ( pm == NULL ) {
		return;
	}

	cgc_printf("\tType: $s\n", pm->type);
	cgc_printf("\tLevel: $d\n", pm->level);
	cgc_printf("\tHealth: $d\n", pm->health);
	cgc_printf("\tHit Points: $d\n", pm->hitpoints);
	cgc_printf("\tPower: $d\n\n", pm->power);

	return;
}

int cgc_oneup_monster( pmonster pm )
{
	if ( pm == NULL ) {
		return 0;
	}

	pm->experience += 1;

	if ( (pm->experience % 15) == 0 ) {
		cgc_printf("$s gained a level\n", pm->type);
		pm->hitpoints += 1;
		pm->power += 1;
		pm->health = pm->hitpoints;
		pm->level += 1;

		pm->experience = 0;
	}

	return 1;
}

pmonster cgc_generate_boss( )
{
	pmonster pm = NULL;

	pm = cgc_malloc( sizeof(monster) );

	if ( pm == NULL ) {
		cgc_printf("[ERROR] Failed to allocate boss monster structure\n");
		cgc__terminate(0);
	}

	cgc_bzero( pm, sizeof( monster ) );

	pm->type = cgc_select_name();

	/// Minimum life 4
	pm->health = (secret_page[ cgc_page_index ] % MAX_MONSTER_LIFE+5) + 4;
	pm->hitpoints = pm->health;
	cgc_update_page_index();

	// Minimum power 2
	pm->power = (secret_page[cgc_page_index] % MAX_MONSTER_POWER+2) + 2;
	cgc_update_page_index();

	pm->level = 4;

	return pm;
}

int cgc_change_monster_name( pmonster pm )
{
	char new_name[32];
	cgc_size_t index = 0;
	char *final = NULL;

	cgc_bzero( new_name, 32);

	cgc_printf("New name: ");
#ifdef PATCHED_1
	index = cgc_read_line( new_name, 31 );
#else
	index = cgc_read_line_u( new_name );
#endif

	final = cgc_malloc( index + 1 );

	if ( final == NULL ) {
		cgc_printf("[ERROR] Failed to malloc name buffer\n");
		cgc__terminate(0);
	}

	cgc_bzero( final, index+1);
	cgc_memcpy( final, new_name, index );

	pm->type = final;

	return 1;
}

int cgc_capture_boss( pmonster pm, pplayer pp )
{
	char sel[3];
	cgc_size_t choice = 0;

	if ( pm == NULL || pp == NULL ) {
		return 0;
	}

	cgc_printf("capture monster? (y\\n): ");

	cgc_bzero( sel, 3 );

	cgc_read_line( sel, 2);

	if ( sel[0] != 'y' ) {
		cgc_free(pm);
		return 0;
	}

	cgc_printf("update boss name? (y\\n): ");
	cgc_bzero( sel, 3 );
	cgc_read_line( sel, 2 );

	if ( sel[0] == 'y') {
		cgc_change_monster_name( pm );
	}

	if ( pp->mcnt < MAX_CAPTURE ) {
		pp->mons[ pp->mcnt++] = pm;
		return 1;
	}

	cgc_printf("your cart is full.\n");
	for ( choice = 0; choice < MAX_CAPTURE; choice++ ) {
		cgc_printf("$d} \n", choice+1);
		cgc_print_monster(pp->mons[choice]);
	}

	cgc_printf("*********************************\n");
	/// Reset the health before printing.
	pm->health = pm->hitpoints;
	cgc_print_monster( pm);
	cgc_printf("*********************************\n");

	cgc_printf("replace one of yours? (y\\n): ");
	cgc_bzero(sel, 3);
	cgc_read_line( sel, 2 );

	if ( sel[0] != 'y') {
		cgc_free(pm);
		return 0;
	}

	cgc_bzero(sel, 3 );
	cgc_printf("which one: ");
	cgc_read_line( sel, 3);

	choice = cgc_atoi( sel );

	if ( choice <= 0 || choice > MAX_CAPTURE ) {
		cgc_printf("invalid\n");
		cgc_free( pm );
		return 0;
	}

	cgc_free( pp->mons[choice-1]);
	pp->mons[choice-1] = pm;

	return 1;
}

int cgc_daboss( pplayer pp )
{
	pmonster boss = NULL;
	pmonster player_current = NULL;
	cgc_size_t player_hit;
	cgc_size_t target_hit;

	if ( pp == NULL ) {
		return 0;
	}

	boss = cgc_generate_boss( );
	cgc_reset_monsters( pp );

	cgc_printf("\nDUN DUN DUUUUUUUUUUUUUUN\n");
	cgc_printf("You have reached the boss!!!!!\n\n");
	cgc_print_monster( boss );

	while ( boss->health > 0 ) {
		player_current = cgc_select_monster(pp);

		if ( player_current == NULL ) {
			cgc_printf("You have no living monsters. You lose.\n");
			return 0;
		}

		player_hit = secret_page[cgc_page_index] % player_current->power;
		cgc_update_page_index();

		boss->health -= player_hit;
		cgc_printf("You hit for $d. $d left\n", player_hit, boss->health);

		cgc_oneup_monster( player_current );

		if ( boss->health <= 0 ) {
			cgc_printf("You destroyed the boss!!!!\n");
			cgc_reset_monsters(pp);
			cgc_capture_boss( boss, pp);
			return 1;
		}

		target_hit = secret_page[cgc_page_index] % boss->power;
		cgc_update_page_index();

		cgc_printf("$s hits $s for $d\n", boss->type, player_current->type, target_hit);

		player_current->health -= target_hit;

		if ( player_current->health <= 0 ) {
			cgc_printf("$s was knocked out\n", player_current->type);
		}

	}
	return 1;
}

int cgc_capture_monster( pmonster pm, pplayer pp )
{
	char sel[3];
	cgc_size_t choice = 0;

	if ( pm == NULL || pp == NULL ) {
		return 0;
	}

	cgc_printf("capture monster? (y\\n): ");

	cgc_bzero( sel, 3 );

	cgc_read_line( sel, 2);

	if ( sel[0] != 'y' ) {
		cgc_free(pm);
		return 0;
	}

	if ( pp->mcnt < MAX_CAPTURE ) {
		pp->mons[ pp->mcnt++] = pm;
		return 1;
	}

	cgc_printf("your cart is full.\n");
	for ( choice = 0; choice < MAX_CAPTURE; choice++ ) {
		cgc_printf("$d} \n", choice+1);
		cgc_print_monster(pp->mons[choice]);
	}

	cgc_printf("*********************************\n");
	/// Reset the health before printing.
	cgc_print_monster( pm);
	cgc_printf("*********************************\n");

	cgc_printf("replace one of yours? (y\\n): ");
	cgc_bzero(sel, 3);
	cgc_read_line( sel, 2 );

	if ( sel[0] != 'y') {
		cgc_free(pm);
		return 0;
	}

	cgc_bzero(sel, 3 );
	cgc_printf("which one: ");
	cgc_read_line( sel, 3);

	choice = cgc_atoi( sel );

	if ( choice <= 0 || choice > MAX_CAPTURE ) {
		cgc_printf("invalid\n");
		cgc_free( pm );
		return 0;
	}

	cgc_free( pp->mons[choice-1]);
	pp->mons[choice-1] = pm;

	return 1;
}

int cgc_fight ( pplayer pp )
{
	pmonster pm = NULL;
	pmonster player_current = NULL;
	cgc_size_t target_hit = 0;
	cgc_size_t player_hit = 0;

	if ( pp == NULL ) {
		return 0;
	}

	cgc_reset_monsters( pp );

	pm = cgc_generate_monster();

	cgc_printf("You are being attacked!!!\n");
	cgc_print_monster( pm );


	while ( pm->health > 0 ) {
		player_current = cgc_select_monster(pp);

		if ( player_current == NULL ) {
			cgc_printf("You have no living monsters. You lose.\n");
			return 0;
		}

		player_hit = secret_page[cgc_page_index] % player_current->power;
		cgc_update_page_index();

		pm->health -= player_hit;
		cgc_printf("You hit for $d. $d left\n", player_hit, pm->health);

		cgc_oneup_monster( player_current );

		if ( pm->health <= 0 ) {
			cgc_printf("You knocked out $s\n", pm->type);
			cgc_reset_monsters(pp);
			cgc_capture_monster( pm, pp);
			return 1;
		}

		target_hit = secret_page[cgc_page_index] % pm->power;
		cgc_update_page_index();

		cgc_printf("$s hits $s for $d\n", pm->type, player_current->type, target_hit);

		player_current->health -= target_hit;

		if ( player_current->health <= 0 ) {
			cgc_printf("$s was knocked out\n", player_current->type);
		}

	}

	return 1;
}

int cgc_movement_loop( pmap pm, pplayer pp ) 
{
	cgc_size_t success = 0;
	char movement[2];
	cgc_size_t rx_bytes;

	if ( pm == NULL ) {
		return 0;
	}

	while ( success == 0 ) {
		cgc_bzero( movement, 2 );

		cgc_printf(": ");
		rx_bytes = cgc_read_line( movement, 2 );

		if ( rx_bytes == 0 ) {
			cgc_printf("[ERROR] Failed to receive movement byte\n");
			cgc__terminate(-2);
		}

		cgc_check_egg( pp, movement[0]);

		switch ( movement[0] ) {
			case 'u':
				/// Check for the edge of the board
				if ( pm->current_y == 0 ) {
					cgc_printf("off map\n");
				} else if ( pm->data[ (pm->width * (pm->current_y-1)) + pm->current_x] == '#') {
					cgc_printf("blocked\n");
				} else {
					cgc_set_marker( pm->current_x, pm->current_y, pm, '\0');
					pm->current_y -= 1;
					cgc_set_marker( pm->current_x, pm->current_y, pm, PERSON);
				}
				break;
			case 'd':
				if ( pm->current_y == pm->height-1 ) {
					cgc_printf("off map\n");
				} else if ( pm->data[ (pm->width * (pm->current_y+1)) + pm->current_x] == '#') {
					cgc_printf("blocked\n");
				} else {
					cgc_set_marker( pm->current_x, pm->current_y, pm, '\0');
					pm->current_y += 1;
					cgc_set_marker( pm->current_x, pm->current_y, pm, PERSON);
				}
				break;
			case 'l':
				if ( pm->current_x == 0 ) {
					cgc_printf("off map\n");
				} else if ( pm->data[ (pm->width * (pm->current_y)) + pm->current_x-1] == '#') {
					cgc_printf("blocked\n");
				} else {
					cgc_set_marker( pm->current_x, pm->current_y, pm, '\0');
					pm->current_x -= 1;
					cgc_set_marker( pm->current_x, pm->current_y, pm, PERSON);
				}
				break;
			case 'r':
				if ( pm->current_x == pm->width-1 ) {
					cgc_printf("off map\n");
				} else if ( pm->data[ (pm->width * (pm->current_y)) + pm->current_x+1] == '#') {
					cgc_printf("blocked\n");
				} else {
					cgc_set_marker( pm->current_x, pm->current_y, pm, '\0');
					pm->current_x += 1;
					cgc_set_marker( pm->current_x, pm->current_y, pm, PERSON);
				}
				break;
			default:
				cgc_printf("[ERROR] Invalid direction: $x\n", movement[0]);
				continue;
		};

		cgc_print_map( pm );

		if ( pm->current_y == pm->end_y && pm->current_x == pm->end_x ) {
			//// Fight main boss
			cgc_printf("reached the end\n");
			
			if ( cgc_daboss( pp ) == 1 ) {
				cgc_printf("You won!!!\n");
			} else {
				cgc_printf("You failed!!!\n");
			}
			

			success = 1;
		} else {
			//// Randomly fight monster
			if ( (secret_page[cgc_page_index] % 100) < 10 ) {
				cgc_update_page_index();
				
				if ( cgc_fight( pp ) == 1 ) {
					pp->level += 1;
					cgc_printf("player gains a level. now $d\n", pp->level);
				}
				cgc_print_map( pm );
				
			} else {
				cgc_update_page_index();
			}

		}
	} 

	return 1;
}

char *cgc_select_name( )
{
	cgc_size_t index = 0;
	cgc_size_t value = secret_page[ cgc_page_index ];
	cgc_update_page_index();

	while ( value ) {
		index += 1;

		if ( names[index] == NULL ) {
			index = 0;
		}

		value -= 1;
	}

	return names[index];
}

pmonster cgc_generate_monster( )
{
	pmonster pm = NULL;

	pm = cgc_malloc( sizeof(monster) );

	if ( pm == NULL ) {
		cgc_printf("[ERROR] Failed to allocate monster structure\n");
		cgc__terminate(0);
	}

	cgc_bzero( pm, sizeof( monster ) );

	pm->type = cgc_select_name();

	/// Minimum life 4
	pm->health = (secret_page[ cgc_page_index ] % MAX_MONSTER_LIFE) + 4;
	pm->hitpoints = pm->health;
	cgc_update_page_index();

	// Minimum power 2
	pm->power = (secret_page[cgc_page_index] % MAX_MONSTER_POWER) + 2;
	cgc_update_page_index();

	pm->level = 1;

	return pm;
}

pplayer cgc_generate_player( )
{
	pplayer np = NULL;
	char player_one[16];
	cgc_size_t result = 0;

	cgc_printf("Enter your name|| ");

	cgc_bzero( player_one, 16);

	result = cgc_read_line( player_one, 15);

	/// If they just hit enter then they get a default
	if ( result == 0 ) {
		cgc_memcpy( player_one, "Player One", 10 );
	}

	np = cgc_malloc( sizeof( player ) );

	if ( np == NULL ) {
		cgc_printf("[ERROR] Failed to malloc player structure\n");
		cgc__terminate(0);
	}

	cgc_bzero( np, sizeof(player) );

	cgc_memcpy( np->name, player_one, 16 );

	/// Generate 3 monsters for the player to fight with
	for ( result = 0; result < 3; result++ ) {
		np->mons [ np->mcnt++ ] = cgc_generate_monster();
	}

	np->level = 1;

	return np;
}

void cgc_print_player( pplayer pp )
{
	cgc_size_t index = 0;

	if ( pp == NULL ) {
		return;
	}

	cgc_printf("Name: $s\n", pp->name);
	cgc_printf("Level: $d\n", pp->level);
	cgc_printf("Monsters: \n");

	for ( index = 0; index < pp->mcnt; index++ ) {
		cgc_printf("\tType: $s\n", pp->mons[index]->type);
		cgc_printf("\tHealth: $d\n", pp->mons[index]->health);
		cgc_printf("\tPower: $d\n\n", pp->mons[index]->power);
	}

	return;
}

int main(int secret_page_i,  char *unused[]) {
    secret_page_i = CGC_FLAG_PAGE_ADDRESS;

	pmap pm = NULL;
	pplayer pp = NULL;

	/// Initialized the secret page stuff
	secret_page = (unsigned char*)secret_page_i;
	cgc_page_index = 0;
	root = NULL;
	queue_matrix = NULL;

	pp = cgc_generate_player();

	cgc_print_player(pp);

	/// Random value between 5 and 30
	cgc_size_t w = (secret_page[cgc_page_index] % 31) + 5;
	cgc_update_page_index();

	/// Random height between 5 and 30
	cgc_size_t h = (secret_page[cgc_page_index] % 31) + 5;
	cgc_update_page_index();

	pm = cgc_generate_map( w, h);

	cgc_movement_loop ( pm, pp );


	return 0;
}
