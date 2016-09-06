#include <libcgc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "monster_names.h"

#define TREE 	'#'
#define EXIT 	'X'
#define PERSON	'@'
#define MAX_MONSTER_LIFE	10
#define MAX_MONSTER_POWER	6
#define MAX_CAPTURE		5

typedef struct queue {
	size_t x;
	size_t y;
	struct queue *next;
} queue, *pqueue;

typedef struct map {
	size_t width;
	size_t height;
	size_t start_x;
	size_t start_y;
	size_t end_x;
	size_t end_y;

	size_t current_x;
	size_t current_y;

	/// Last x where a marker was placed. Used to reverse on failure
	size_t last_x;

	/// Last y where a marker was placed
	size_t last_y;

	/// Map data
	char *data;
} map, *pmap;

typedef struct monster {
	char *type;
	int health;
	size_t hitpoints;
	size_t power;
	size_t experience;
	size_t level;
} monster, *pmonster;

typedef struct player {
	char name[16];
	size_t level;
	size_t mcnt;
	pmonster mons[MAX_CAPTURE];
} player, *pplayer;

/// Index to use for the secret page
size_t page_index = 0;
unsigned char *secret_page;

/// queue list
pqueue root;

char *queue_matrix;

/// Variables for the easter egg
char easteregg[] = "easta egg";
size_t eggindex;

pmonster generate_monster( void );
char *select_name( void );

void check_egg( pplayer pp, char c ) {
	if ( easteregg[ eggindex ] == c ) {
		eggindex += 1;
	} else { 
		eggindex = 0;
	}

	if ( easteregg[eggindex] == 0 ) {
		printf("YOU FOUND THE EGG!!!! Have a prize.\n");
		pp->mons[0]->hitpoints = 99;
		pp->mons[0]->health = 99;
		pp->mons[0]->power = 99;

		eggindex = 0;
	}

	return;
}

size_t read_line( char *outbuf, size_t length )
{
	char c = '\0';
	size_t index = 0;
	size_t rx_bytes = 0;

	if ( outbuf == NULL ) {
		printf("[ERROR] invalid arg\n");
		_terminate(-1);
		return 0;
	}

	while ( index < length && c != '\n') {
		if ( receive( STDIN, &c, 1, &rx_bytes) != 0 ) {
			printf("[ERROR] Failed to read byte\n");
			_terminate(-3);
		}

		if ( rx_bytes == 0 ) {
			printf("[ERROR] Error in receive\n");
			_terminate(-4);
		}

		if ( c == '\n') {
			return index;
		}

		outbuf[index] = c;
		index++;
	}

	return index;
}

size_t read_line_u( char *outbuf )
{
	char c = '\0';
	size_t index = 0;
	size_t rx_bytes = 0;

	if ( outbuf == NULL ) {
		return 0;
	}

	while ( c != '\n' ) {
		if ( receive( STDIN, &c, 1, &rx_bytes) != 0 ) {
			printf("[ERROR] Failed to read byte\n");
			_terminate(0);
		}

		if ( rx_bytes == 0 ) {
			printf("[ERROR] Error in receive\n");
			_terminate(0);
		}

		if ( c == '\n') {
			continue;
		}

		outbuf[index] = c;
		index++;
	}

	return index;
}

void add_queue( size_t x, size_t y, size_t max_x, size_t max_y )
{
	pqueue pq = NULL;
	pqueue walker = NULL;
	size_t index = ( (max_x+1) * y ) + x;

	/// If it has already been queued then don't requeue it
	if ( queue_matrix[index] == 1 ) {
		return;
	}

	pq = malloc( sizeof(queue) );

	if ( pq == NULL ) {
		printf("[ERROR] malloc() queue structure failed.\n");
		_terminate(-1);
	}

	bzero( pq, sizeof( queue ) );

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

pqueue dequeue( )
{
	pqueue pq = root;

	if ( root != NULL ) {
		root = root->next;
	}

	return pq;
}

/// Determine if they are adjacent
int check_adjacent( sx, sy, dx, dy )
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

void print_map( pmap pm )
{
	size_t index;
	size_t max;
	size_t map_index = 0;

	char *data = NULL;

	index = 0;
	max = pm->height * pm->width;

	/// 1 byte for each block, height bytes for the new lines 1 byte for the NULL
	data = malloc( max + pm->height + 1 );

	if ( data == NULL ) {
		printf("[ERROR] Failed to allocate map.\n");
		_terminate(-5);
	}

	bzero( data, max + pm->height + 1);

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
	
	printf("$s", data);

	free(data);

}

/// Algorithm
/// Given source(x,y) and dest(x,y) does there exist a path between the two
/// Returns 0 if a path does not exist and 1 if it does
size_t find_path( size_t sx, size_t sy, pmap pm)
{
	pqueue pq = NULL;
	size_t retval = 0;

	if ( pm == NULL ) {
		return 0;
	}

	/// Look up, down, left, right if destination is adjacent then success
	if ( check_adjacent( sx, sy, pm->end_x, pm->end_y ) == 1 ) {
		return 1;
	}

	/// Else queue up, down, left, right

	// Up
	if ( sy > 0 ) {
		add_queue( sx, sy - 1, pm->width-1, pm->height-1 );
	}
	
	// Right
	if ( sx < pm->width-1 ) {
		add_queue( sx + 1, sy, pm->width-1, pm->height-1 );
	}

	// Down
	if ( sy < pm->height-1 ) {
		add_queue( sx, sy + 1, pm->width-1, pm->height-1);
	}

	// Left
	if ( sx > 0 ) {
		add_queue( sx - 1, sy, pm->width-1, pm->height-1 );
	}

	pq = dequeue();

	while ( pq != NULL ) {
		retval = find_path( pq->x, pq->y, pm);

		if ( retval == 1 ) {
			free(pq);
			return 1;
		} else {
			free(pq);
			pq = dequeue();
		}
	}

	return 0;
}

void update_page_index( )
{
	page_index += 3;

	page_index = page_index % 0x1000;
	return;
}

void place_marker( pmap pm )
{
	size_t index = 0;
	size_t count = 0;
	size_t max = 0;

	pm->last_x = secret_page[ page_index ] % pm->width;
	update_page_index();

	pm->last_y = secret_page[ page_index ] % pm->height;
	update_page_index();

	index = ( pm->width * pm->last_y ) + pm->last_x;

	while ( pm->data[index] != '\0' && count < 100 ) {
		pm->last_x = secret_page[ page_index ] % pm->width;
		update_page_index();

		pm->last_y = secret_page[ page_index ] % pm->height;
		update_page_index();

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
			printf("FAILED\n");
			print_map( pm );
			_terminate(0);
		}

		pm->last_y = index / pm->width;
		pm->last_x = index % pm->width;
	}

	pm->data[index] = '#';

	return;
}

void set_marker( size_t x, size_t y, pmap pm, char c )
{
	size_t index = ( (pm->width) * y ) + x;

	pm->data[index] = c;
}

/// Clear the map data
/// Select the start and end coords and place them on the map
void initialize_map( pmap pm )
{
	if ( pm == NULL ) {
		printf("[ERROR] initialize_map() invalid argumenet.\n");
		_terminate(0);
	}

	pm->data = malloc( pm->width * pm->height );

	if ( pm->data == NULL ) {
		printf("[ERROR] Failed to allocate map.\n");
		_terminate(0);
	}

	bzero( pm->data, pm->width * pm->height);

	pm->start_x = 0;
	pm->start_y = 0;
	pm->end_x = 0;
	pm->end_y = 0;

	while ( (pm->start_x==pm->end_x) || ( pm->start_x-1 == pm->end_x) || (pm->start_x+1 == pm->end_x)
				|| (pm->start_y == pm->end_y) || ( pm->start_y+1 == pm->end_y) || (pm->start_y - 1 == pm->end_y) ) {

		/// Decide on the start and the end position
		pm->start_x = secret_page[page_index] % pm->width;
		update_page_index();

		pm->start_y = secret_page[page_index] % pm->height;
		update_page_index();

		pm->end_x = secret_page[page_index] % pm->width;
		update_page_index();

		pm->end_y = secret_page[page_index] % pm->height;
		update_page_index();
	}

	set_marker( pm->start_x, pm->start_y, pm, PERSON);
	set_marker( pm->end_x, pm->end_y, pm, EXIT);

	pm->current_x = pm->start_x;
	pm->current_y = pm->start_y;

	return;
}

/// Initialize the queue matrix
void initialize_queue_matrix( pmap pm )
{
	size_t index;

	if (queue_matrix != NULL ) {
		free( queue_matrix);
	}

	queue_matrix = malloc( pm->width * pm->height );

	if ( queue_matrix == NULL ) {
		printf("[ERROR] Failed to allocate queue matrix\n");
		_terminate(0);
	}

	bzero( queue_matrix, pm->width * pm->height );

	/// If the map contains an obstruction then mirror that in the matrix
	for ( index = 0; index < pm->width * pm->height; index ++ ) {
		if ( pm->data[index] != 0x00 ) {
			queue_matrix[index] = 1;
		}
	}

	return;
}

pmap generate_map( size_t width, size_t height )
{
	pmap pm = NULL;
	pqueue t = NULL;
	size_t start_x = 0;
	size_t start_y = 0;

	size_t end_x = 0;
	size_t end_y = 0;
	size_t success = 1;

	pm = malloc( sizeof(map) );

	if ( pm == NULL ) {
		printf("[ERROR] Failed to allocate map strucure\n");
		_terminate(0);
	}

	bzero( pm, sizeof(map) );

	pm->height = height;
	pm->width = width;

	initialize_map ( pm );

	printf("Width: $d Height: $d\nStartX: $d StartY: $d\nEndX: $d EndY: $d\n\n", width, height, pm->start_x, pm->start_y, pm->end_x, pm->end_y);

	while ( success) {

		/// place a new marker
		place_marker(pm);

		/// Initialize a new queue matrix
		initialize_queue_matrix( pm );

		if ( find_path( pm->start_x, pm->start_y, pm) != 1 ) {
			/// Reverse the last marker
			pm->data[ ( pm->width * pm->last_y) + pm->last_x ]  = 0x00;

			success = 0;
		}

		/// Free any remaining queue structures
		while ( root ) {
			t = root;
			root = root->next;

			free ( t );
		}

		root = NULL;

	}

	/// Free the matrix
	free( queue_matrix );

	print_map( pm );
	

	return pm;
}

pmonster select_monster( pplayer pp )
{
	size_t index;
	size_t choice = 0;
	size_t success = 0;

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

	printf("Monsters: \n");
	for ( index = 0; index < pp->mcnt; index++ ) {
		printf("\t$d} \n", index+1);
		printf("\tType: $s\n", pp->mons[index]->type);
		printf("\tLevel: $d\n", pp->mons[index]->level);
		printf("\tHealth: $d\n", pp->mons[index]->health);
		printf("\tPower: $d\n\n", pp->mons[index]->power);
	}

	while ( !success ) {
		printf("Selection: ");

		choice = 0;
		read_line( (char*)&choice, 2);

		ac = atoi( (char*)&choice );

		if ( ac <= 0 || ac > pp->mcnt ) {
			printf("bad choice: $x\n", choice);
		} else if ( pp->mons[ac-1] == NULL ) {
			printf("bad choice: $x\n", choice);
		} else if ( pp->mons[ac-1]->health <= 0 ) {
			printf("he dead\n");
		} else {
			success = 1;
		}
	}

	return pp->mons[ac-1];
}

void reset_monsters( pplayer pp )
{
	size_t index = 0;

	if ( pp == NULL ) {
		return;
	}

	/// Reset the hit points of each monster
	for ( index = 0; index < pp->mcnt; index++ ) {
		pp->mons[index]->health = pp->mons[index]->hitpoints;
	}


	return;
}

void print_monster( pmonster pm )
{
	if ( pm == NULL ) {
		return;
	}

	printf("\tType: $s\n", pm->type);
	printf("\tLevel: $d\n", pm->level);
	printf("\tHealth: $d\n", pm->health);
	printf("\tHit Points: $d\n", pm->hitpoints);
	printf("\tPower: $d\n\n", pm->power);

	return;
}

int oneup_monster( pmonster pm )
{
	if ( pm == NULL ) {
		return 0;
	}

	pm->experience += 1;

	if ( (pm->experience % 15) == 0 ) {
		printf("$s gained a level\n", pm->type);
		pm->hitpoints += 1;
		pm->power += 1;
		pm->health = pm->hitpoints;
		pm->level += 1;

		pm->experience = 0;
	}

	return 1;
}

pmonster generate_boss( )
{
	pmonster pm = NULL;

	pm = malloc( sizeof(monster) );

	if ( pm == NULL ) {
		printf("[ERROR] Failed to allocate boss monster structure\n");
		_terminate(0);
	}

	bzero( pm, sizeof( monster ) );

	pm->type = select_name();

	/// Minimum life 4
	pm->health = (secret_page[ page_index ] % MAX_MONSTER_LIFE+5) + 4;
	pm->hitpoints = pm->health;
	update_page_index();

	// Minimum power 2
	pm->power = (secret_page[page_index] % MAX_MONSTER_POWER+2) + 2;
	update_page_index();

	pm->level = 4;

	return pm;
}

int change_monster_name( pmonster pm )
{
	char new_name[32];
	size_t index = 0;
	char *final = NULL;

	bzero( new_name, 32);

	printf("New name: ");
#ifdef PATCHED_1
	index = read_line( new_name, 31 );
#else
	index = read_line_u( new_name );
#endif

	final = malloc( index + 1 );

	if ( final == NULL ) {
		printf("[ERROR] Failed to malloc name buffer\n");
		_terminate(0);
	}

	bzero( final, index+1);
	memcpy( final, new_name, index );

	pm->type = final;

	return 1;
}

int capture_boss( pmonster pm, pplayer pp )
{
	char sel[3];
	size_t choice = 0;

	if ( pm == NULL || pp == NULL ) {
		return 0;
	}

	printf("capture monster? (y\\n): ");

	bzero( sel, 3 );

	read_line( sel, 2);

	if ( sel[0] != 'y' ) {
		free(pm);
		return 0;
	}

	printf("update boss name? (y\\n): ");
	bzero( sel, 3 );
	read_line( sel, 2 );

	if ( sel[0] == 'y') {
		change_monster_name( pm );
	}

	if ( pp->mcnt < MAX_CAPTURE ) {
		pp->mons[ pp->mcnt++] = pm;
		return 1;
	}

	printf("your cart is full.\n");
	for ( choice = 0; choice < MAX_CAPTURE; choice++ ) {
		printf("$d} \n", choice+1);
		print_monster(pp->mons[choice]);
	}

	printf("*********************************\n");
	/// Reset the health before printing.
	pm->health = pm->hitpoints;
	print_monster( pm);
	printf("*********************************\n");

	printf("replace one of yours? (y\\n): ");
	bzero(sel, 3);
	read_line( sel, 2 );

	if ( sel[0] != 'y') {
		free(pm);
		return 0;
	}

	bzero(sel, 3 );
	printf("which one: ");
	read_line( sel, 3);

	choice = atoi( sel );

	if ( choice <= 0 || choice > MAX_CAPTURE ) {
		printf("invalid\n");
		free( pm );
		return 0;
	}

	free( pp->mons[choice-1]);
	pp->mons[choice-1] = pm;

	return 1;
}

int daboss( pplayer pp )
{
	pmonster boss = NULL;
	pmonster player_current = NULL;
	size_t player_hit;
	size_t target_hit;

	if ( pp == NULL ) {
		return 0;
	}

	boss = generate_boss( );
	reset_monsters( pp );

	printf("\nDUN DUN DUUUUUUUUUUUUUUN\n");
	printf("You have reached the boss!!!!!\n\n");
	print_monster( boss );

	while ( boss->health > 0 ) {
		player_current = select_monster(pp);

		if ( player_current == NULL ) {
			printf("You have no living monsters. You lose.\n");
			return 0;
		}

		player_hit = secret_page[page_index] % player_current->power;
		update_page_index();

		boss->health -= player_hit;
		printf("You hit for $d. $d left\n", player_hit, boss->health);

		oneup_monster( player_current );

		if ( boss->health <= 0 ) {
			printf("You destroyed the boss!!!!\n");
			reset_monsters(pp);
			capture_boss( boss, pp);
			return 1;
		}

		target_hit = secret_page[page_index] % boss->power;
		update_page_index();

		printf("$s hits $s for $d\n", boss->type, player_current->type, target_hit);

		player_current->health -= target_hit;

		if ( player_current->health <= 0 ) {
			printf("$s was knocked out\n", player_current->type);
		}

	}
	return 1;
}

int capture_monster( pmonster pm, pplayer pp )
{
	char sel[3];
	size_t choice = 0;

	if ( pm == NULL || pp == NULL ) {
		return 0;
	}

	printf("capture monster? (y\\n): ");

	bzero( sel, 3 );

	read_line( sel, 2);

	if ( sel[0] != 'y' ) {
		free(pm);
		return 0;
	}

	if ( pp->mcnt < MAX_CAPTURE ) {
		pp->mons[ pp->mcnt++] = pm;
		return 1;
	}

	printf("your cart is full.\n");
	for ( choice = 0; choice < MAX_CAPTURE; choice++ ) {
		printf("$d} \n", choice+1);
		print_monster(pp->mons[choice]);
	}

	printf("*********************************\n");
	/// Reset the health before printing.
	print_monster( pm);
	printf("*********************************\n");

	printf("replace one of yours? (y\\n): ");
	bzero(sel, 3);
	read_line( sel, 2 );

	if ( sel[0] != 'y') {
		free(pm);
		return 0;
	}

	bzero(sel, 3 );
	printf("which one: ");
	read_line( sel, 3);

	choice = atoi( sel );

	if ( choice <= 0 || choice > MAX_CAPTURE ) {
		printf("invalid\n");
		free( pm );
		return 0;
	}

	free( pp->mons[choice-1]);
	pp->mons[choice-1] = pm;

	return 1;
}

int fight ( pplayer pp )
{
	pmonster pm = NULL;
	pmonster player_current = NULL;
	size_t target_hit = 0;
	size_t player_hit = 0;

	if ( pp == NULL ) {
		return 0;
	}

	reset_monsters( pp );

	pm = generate_monster();

	printf("You are being attacked!!!\n");
	print_monster( pm );


	while ( pm->health > 0 ) {
		player_current = select_monster(pp);

		if ( player_current == NULL ) {
			printf("You have no living monsters. You lose.\n");
			return 0;
		}

		player_hit = secret_page[page_index] % player_current->power;
		update_page_index();

		pm->health -= player_hit;
		printf("You hit for $d. $d left\n", player_hit, pm->health);

		oneup_monster( player_current );

		if ( pm->health <= 0 ) {
			printf("You knocked out $s\n", pm->type);
			reset_monsters(pp);
			capture_monster( pm, pp);
			return 1;
		}

		target_hit = secret_page[page_index] % pm->power;
		update_page_index();

		printf("$s hits $s for $d\n", pm->type, player_current->type, target_hit);

		player_current->health -= target_hit;

		if ( player_current->health <= 0 ) {
			printf("$s was knocked out\n", player_current->type);
		}

	}

	return 1;
}

int movement_loop( pmap pm, pplayer pp ) 
{
	size_t success = 0;
	char movement[2];
	size_t rx_bytes;

	if ( pm == NULL ) {
		return 0;
	}

	while ( success == 0 ) {
		bzero( movement, 2 );

		printf(": ");
		rx_bytes = read_line( movement, 2 );

		if ( rx_bytes == 0 ) {
			printf("[ERROR] Failed to receive movement byte\n");
			_terminate(-2);
		}

		check_egg( pp, movement[0]);

		switch ( movement[0] ) {
			case 'u':
				/// Check for the edge of the board
				if ( pm->current_y == 0 ) {
					printf("off map\n");
				} else if ( pm->data[ (pm->width * (pm->current_y-1)) + pm->current_x] == '#') {
					printf("blocked\n");
				} else {
					set_marker( pm->current_x, pm->current_y, pm, '\0');
					pm->current_y -= 1;
					set_marker( pm->current_x, pm->current_y, pm, PERSON);
				}
				break;
			case 'd':
				if ( pm->current_y == pm->height-1 ) {
					printf("off map\n");
				} else if ( pm->data[ (pm->width * (pm->current_y+1)) + pm->current_x] == '#') {
					printf("blocked\n");
				} else {
					set_marker( pm->current_x, pm->current_y, pm, '\0');
					pm->current_y += 1;
					set_marker( pm->current_x, pm->current_y, pm, PERSON);
				}
				break;
			case 'l':
				if ( pm->current_x == 0 ) {
					printf("off map\n");
				} else if ( pm->data[ (pm->width * (pm->current_y)) + pm->current_x-1] == '#') {
					printf("blocked\n");
				} else {
					set_marker( pm->current_x, pm->current_y, pm, '\0');
					pm->current_x -= 1;
					set_marker( pm->current_x, pm->current_y, pm, PERSON);
				}
				break;
			case 'r':
				if ( pm->current_x == pm->width-1 ) {
					printf("off map\n");
				} else if ( pm->data[ (pm->width * (pm->current_y)) + pm->current_x+1] == '#') {
					printf("blocked\n");
				} else {
					set_marker( pm->current_x, pm->current_y, pm, '\0');
					pm->current_x += 1;
					set_marker( pm->current_x, pm->current_y, pm, PERSON);
				}
				break;
			default:
				printf("[ERROR] Invalid direction: $x\n", movement[0]);
				continue;
		};

		print_map( pm );

		if ( pm->current_y == pm->end_y && pm->current_x == pm->end_x ) {
			//// Fight main boss
			printf("reached the end\n");
			
			if ( daboss( pp ) == 1 ) {
				printf("You won!!!\n");
			} else {
				printf("You failed!!!\n");
			}
			

			success = 1;
		} else {
			//// Randomly fight monster
			if ( (secret_page[page_index] % 100) < 10 ) {
				update_page_index();
				
				if ( fight( pp ) == 1 ) {
					pp->level += 1;
					printf("player gains a level. now $d\n", pp->level);
				}
				print_map( pm );
				
			} else {
				update_page_index();
			}

		}
	} 

	return 1;
}

char *select_name( )
{
	size_t index = 0;
	size_t value = secret_page[ page_index ];
	update_page_index();

	while ( value ) {
		index += 1;

		if ( names[index] == NULL ) {
			index = 0;
		}

		value -= 1;
	}

	return names[index];
}

pmonster generate_monster( )
{
	pmonster pm = NULL;

	pm = malloc( sizeof(monster) );

	if ( pm == NULL ) {
		printf("[ERROR] Failed to allocate monster structure\n");
		_terminate(0);
	}

	bzero( pm, sizeof( monster ) );

	pm->type = select_name();

	/// Minimum life 4
	pm->health = (secret_page[ page_index ] % MAX_MONSTER_LIFE) + 4;
	pm->hitpoints = pm->health;
	update_page_index();

	// Minimum power 2
	pm->power = (secret_page[page_index] % MAX_MONSTER_POWER) + 2;
	update_page_index();

	pm->level = 1;

	return pm;
}

pplayer generate_player( )
{
	pplayer np = NULL;
	char player_one[16];
	size_t result = 0;

	printf("Enter your name|| ");

	bzero( player_one, 16);

	result = read_line( player_one, 15);

	/// If they just hit enter then they get a default
	if ( result == 0 ) {
		memcpy( player_one, "Player One", 10 );
	}

	np = malloc( sizeof( player ) );

	if ( np == NULL ) {
		printf("[ERROR] Failed to malloc player structure\n");
		_terminate(0);
	}

	bzero( np, sizeof(player) );

	memcpy( np->name, player_one, 16 );

	/// Generate 3 monsters for the player to fight with
	for ( result = 0; result < 3; result++ ) {
		np->mons [ np->mcnt++ ] = generate_monster();
	}

	np->level = 1;

	return np;
}

void print_player( pplayer pp )
{
	size_t index = 0;

	if ( pp == NULL ) {
		return;
	}

	printf("Name: $s\n", pp->name);
	printf("Level: $d\n", pp->level);
	printf("Monsters: \n");

	for ( index = 0; index < pp->mcnt; index++ ) {
		printf("\tType: $s\n", pp->mons[index]->type);
		printf("\tHealth: $d\n", pp->mons[index]->health);
		printf("\tPower: $d\n\n", pp->mons[index]->power);
	}

	return;
}

int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
	pmap pm = NULL;
	pplayer pp = NULL;

	/// Initialized the secret page stuff
	secret_page = (unsigned char*)secret_page_i;
	page_index = 0;
	root = NULL;
	queue_matrix = NULL;

	pp = generate_player();

	print_player(pp);

	/// Random value between 5 and 30
	size_t w = (secret_page[page_index] % 31) + 5;
	update_page_index();

	/// Random height between 5 and 30
	size_t h = (secret_page[page_index] % 31) + 5;
	update_page_index();

	pm = generate_map( w, h);

	movement_loop ( pm, pp );


	return 0;
}
