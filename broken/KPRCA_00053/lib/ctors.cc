extern "C" {
    #include <libcgc.h>
    #include <stdlib.h>
};

extern "C" {
	extern void (*__init_array_start[])(void) __attribute__((__visibility__("hidden")));
	extern void (*__init_array_end[])(void) __attribute__((__visibility__("hidden")));
};

void call_ctors(void) {
	size_t len, i;

	for (len = __init_array_end - __init_array_start, i = 0; i < len; i++) {
		 __init_array_start[i]();
	}
}
