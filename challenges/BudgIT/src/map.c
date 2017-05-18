/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "libcgc.h"
#include "cgc_libc.h"
#include "cgc_map.h"

Map* cgc_initMap(Map* map) {
	int ret;
	Map* map_ptr;

	if(!map) {
		ret = cgc_allocate(sizeof(Map)*128, 0, (void **) &map_ptr);
		if(ret != 0)
			cgc__terminate(ALLOCATE_ERROR);
		map_ptr += 127;
		return map_ptr;
	} 

	for(map_ptr=map;*map_ptr->key!=0;map_ptr=map_ptr-1);


	return map_ptr;
}

int cgc_setMap(Map **map, char* key, int value)
{
	int ret;
	Map *map_ptr=NULL, *prev_map_ptr=NULL;

	for(map_ptr=*map;map_ptr!=NULL;map_ptr=map_ptr->next) {
		if(!cgc_strcmp(key, map_ptr->key)) {
			break;
		}
		prev_map_ptr = map_ptr;
	}

	if(map_ptr == NULL) {
		// Key not found
#ifdef PATCHED
		if(cgc_getSize(*map) == 128) {
#else
		if(cgc_getSize(*map) == 129) {
#endif
			return 0;
		}
		map_ptr = cgc_initMap(prev_map_ptr);
		map_ptr->next = *map;
		*map = map_ptr;
	}

	if(*map_ptr->key == 0) {
		cgc_strcpy(map_ptr->key, key); // Possible Vuln: key not null terminated
	}

	map_ptr->value = value;
	
	return 1;
}

int cgc_getValue(Map* map, char* key) {
	Map* map_ptr;
	for(map_ptr=map; map_ptr!=NULL; map_ptr=map_ptr->next) {
		if(map_ptr->key && !cgc_strcmp(key, map_ptr->key)) { // Possible vuln: remove map->key check
			return map_ptr->value;
		} 
	}

	return 0;
}


uint32_t cgc_getSize(Map* map) {
	Map* last;
	if(map == NULL)
		return 0;

#ifdef PATCHED
	int size = 1;
	for(last=map; last->next!=NULL; last=last->next, size++);

	return size;
#else
	for(last=map; last->next!=NULL; last=last->next);

	return ((void *) last - (void *)map) / sizeof(Map) + 1;
#endif
}

void cgc_removeMap(Map **map, char* key) {
	int ret;
	Map *map_ptr=NULL, *prev_map_ptr=NULL;

	for(map_ptr=*map;map_ptr!=NULL && *map_ptr->key != 0;map_ptr=map_ptr->next) {
		if(!cgc_strcmp(key, map_ptr->key)) {
			break;
		}
		prev_map_ptr = map_ptr;
	}

	if(!map_ptr)
		return;

	if(prev_map_ptr == NULL)
		*map = map_ptr->next;
	else
		prev_map_ptr->next = map_ptr->next;

	cgc_memset(map_ptr->key, 0, MAX_KEY_SIZE+1);
	map_ptr->value = 0;
	map_ptr->next = 0;

/*	ret = deallocate(map_ptr, sizeof(Map));
	if(ret != 0)
		cgc__terminate(DEALLOCATE_ERROR);*/

}