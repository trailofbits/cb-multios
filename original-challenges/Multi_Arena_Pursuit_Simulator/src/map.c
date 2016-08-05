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
#include "map.h"
#include "malloc.h"
#include <libcgc.h>

/**
 * Create a new square map with a bottom left and top right boundary
 * @param  bottomLeft The bottom most left most coordinate of the map
 * @param  topRight   The top most right most coordinate of the map
 * @return            A pointer of the newly created map
 */
Map* newMap(Coordinate bottomLeft, Coordinate topRight) {
	Map* map;
	int minX, maxX;
	int minY, maxY;
	int xWidth, yWidth;

	minX = bottomLeft.x;
	maxX = topRight.x;
	minY = bottomLeft.y;
	maxY = topRight.y;

	if(!(map = malloc(sizeof(Map))))
		_terminate(ALLOCATE_ERROR);

	map->bottomLeft = bottomLeft;
	map->topRight = topRight;

	xWidth = maxX - minX + 1;
	yWidth = maxY - minY + 1;

	if(!(map->data = malloc(xWidth * yWidth * sizeof(unsigned int)))) 
		_terminate(ALLOCATE_ERROR);

	for(int c=0; c<=xWidth; c++) {
		for(int r=0; r<=yWidth; r++) {
			*(map->data + r*xWidth + c) = -1;
		}
	}

	map->columns = xWidth;
	map->rows = yWidth;

	return map;
}

/**
 * Free all memory for a Map 
 * @param map_ptr Pointer to the Map pointer containing the Map
 */
void freeMap(Map **map_ptr) {
	Map *map;

	map = *map_ptr;
	map->columns = 0;
	map->rows = 0;
	free(map->data);
	map->data = NULL;
	map->topRight.x = 0;
	map->topRight.y = 0;
	map->bottomLeft.x = 0;
	map->bottomLeft.y = 0;
	free(map);
	map = NULL;
}

/**
 * Determine if the coordinate (x,y) is within the existing map
 * @param  map The Map to be tested
 * @param  x   The X-coordinate of the coordinate to find
 * @param  y   The Y-coordinate of the coordinate to find
 * @return     1 if coordinate is in Map, 0 if not
 */
int inBounds(Map* map, int x, int y) {
	if(x < map->bottomLeft.x || x > map->topRight.x || y < map->bottomLeft.y || y > map->topRight.y)
		return 0;

	return 1;
}

/**
 * Make a copy of a Map from srcMap to dstMap
 * @param destMap The destination of the Map to copy
 * @param srcMap  The source of the Map to copy
 */
void copyMap(Map* destMap, Map* srcMap) {
	unsigned int value;

	for(int x=srcMap->bottomLeft.x; x<=srcMap->topRight.x; x++) {
		for(int y=srcMap->bottomLeft.y; y<=srcMap->topRight.y; y++) {
			value = getCoordinate(srcMap, x, y);
			setCoordinate(&destMap, x, y, value);
		}
	}
}

/**
 * Add a new coordinate to a Map.
 * Note: If Map is not big enough, create a new Map that is
 * and copy old Map to new Map
 * 
 * @param map_ptr [description]
 * @param x       [description]
 * @param y       [description]
 */
void addCoordinate(Map** map_ptr, int x, int y) {
	Coordinate bottomLeft, topRight;
	Map *nMap, *map;

	map = *map_ptr;
	if(map == NULL) {
		bottomLeft.x = x;
		bottomLeft.y = y;
		topRight.x = x;
		topRight.y = y;
		*map_ptr = newMap(bottomLeft, topRight);
		return;
	}

	if(inBounds(map, x,y))
		return;

	if(x < map->bottomLeft.x) {
		bottomLeft.x = x;
		topRight.x = map->topRight.x;
	} else if(x > map->topRight.x) {
		topRight.x = x;
		bottomLeft.x = map->bottomLeft.x;
	} else {
		bottomLeft.x = map->bottomLeft.x;
		topRight.x = map->topRight.x;
	}

	if(y < map->bottomLeft.y) {
		bottomLeft.y = y;
		topRight.y = map->topRight.y;
	} else if(y > map->topRight.y) {
		topRight.y = y;
		bottomLeft.y = map->bottomLeft.y;
	} else {
		bottomLeft.y = map->bottomLeft.y;
		topRight.y = map->topRight.y;
	}

	nMap = newMap(bottomLeft, topRight);
	copyMap(nMap, *map_ptr);
	freeMap(map_ptr);
	*map_ptr = nMap;
}

/**
 * Set the value of a Coordinate
 * Note: If the coordinate does not exit in the Map, the coordinate will be added
 * @param map_ptr The address of the Map containing the Coordinate
 * @param x       The X-coordinate of the coordinate to set
 * @param y       The Y-coordinate of the coordinate to set
 * @param value   The value to set the coordinate to
 */
void setCoordinate(Map** map_ptr, int x, int y, unsigned int value) {
	unsigned int column, row;
	Map *map;

	if(*map_ptr == NULL || !inBounds(*map_ptr, x, y))
		addCoordinate(map_ptr, x, y);

	map = *map_ptr;
	column = x - map->bottomLeft.x + 1;
	row = y - map->bottomLeft.y + 1;

	*(map->data + row*map->columns + column) = value;
}

/**
 * Get the value at a specific coordinate in a Map
 * Note: All values at valid coordinates should be greater than zero
 * @param  map The Map to search
 * @param  x   The X-coordinate of the coordinate to find
 * @param  y   The Y-coordinate of the coordinate to find
 * @return     The value at the coordinate, or -1 if the coordinate is not in bounds
 */
unsigned int getCoordinate(Map* map, int x, int y) {
	unsigned int column, row;

	if(!inBounds(map, x, y))
		return -1;

	column = x - map->bottomLeft.x + 1;
	row = y - map->bottomLeft.y + 1;

	return *(map->data + row*map->columns + column);
}
