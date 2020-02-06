#include "cgc_string.h"
#include "cgc_stdint.h"

cgc_size_t cgc_strlen( const char *str )
{
	cgc_size_t len = 0;
	while ( *str++ != '\0' )
		len++;

	return len;
}

void cgc_bzero(void *s, cgc_size_t n) {
        while (n) {
                ((char *)s)[--n] = '\0';
        }
        ((char *)s)[n] = '\0';
}

void *cgc_memset( void *ptr, int value, cgc_size_t num )
{
	void *ptr_temp = ptr;
	uint8_t set_value_byte = (uint8_t)value;
	uint32_t set_value_dword = (set_value_byte << 24) | (set_value_byte << 16) | (set_value_byte << 8) | set_value_byte;

	while ( num >= 4 )
	{
		*((uint32_t*)ptr++) = set_value_dword;	
		num-=4;	
	}

	while ( num > 0 )
	{
		*((uint8_t*)ptr++) = set_value_byte;	
		num--;
	}

	return (ptr_temp);
}
