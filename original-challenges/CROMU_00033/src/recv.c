#include "recv.h"

int recv( char *dest, int length )
{
	int total = 0;
	size_t read = 0;
	int left = length;

	if ( dest == NULL ) {
		return total;
	}

	while ( total < length ) {
		if ( receive( 0, dest+total, left, &read) != 0 ) {
			printf("[ERROR] Failed to receive data\n");
			return 0;
		}

        if (read == 0) {
			printf("[ERROR] Failed to receive data\n");
			return 0;
        }

		total += read;
		left -= read;
	}

	return total;
}
