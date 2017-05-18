#include "cgc_recv.h"

int cgc_recv( char *dest, int length )
{
	int total = 0;
	cgc_size_t cgc_read = 0;
	int left = length;

	if ( dest == NULL ) {
		return total;
	}

	while ( total < length ) {
		if ( cgc_receive( 0, dest+total, left, &cgc_read) != 0 ) {
			cgc_printf("[ERROR] Failed to receive data\n");
			return 0;
		}

        if (cgc_read == 0) {
			cgc_printf("[ERROR] Failed to receive data\n");
			return 0;
        }

		total += cgc_read;
		left -= cgc_read;
	}

	return total;
}
