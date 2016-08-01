/*

Author: James Nuttall (james@cromulence.co)

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
#ifndef __service_h__
#define __service_h__

#include "stdlib.h"
#include "stdint.h"

#define MAX_ENTRY_PER_TITLE 15 // The most Entries a Chapter can have 
#define MAX_NUM_ENTRIES 15
#define NAME_LEN_MAX 26
#define NUM_SUBTITLES 7

enum Title {IDENTITY, MOVIES, VEHICLES, BOOKS, SONGS, JOBS, HOBBIES, PETS, TITLE_COUNT};
enum sub_hobbies {SHOOTING, KNIVES, STAMPS, KAYAKING, COINS, EXERCISES, SPORTS, LAST_HOBBY};
char *titles[TITLE_COUNT] = {"identity", "movies", "vehicles", "books", "songs", "jobs", "hobbies", "pets"};
char *subtitles[NUM_SUBTITLES] = {"shooting", "knives", "stamps", "kayaking", "coins", "exercises", "sports"};
enum Format {CHAR, SHORT, INT, STR, BOOL, PTR};
// PTR: offset into the entry_info_table for another entry


#pragma pack(1)
// One Header, with pointer to first Dir
typedef struct 
{
	uint16_t magic_number;				// always 4242
	uint16_t future;					// not used yet
	uint32_t offset_to_first_chapter;	// offset from start of file to the first chapter
}Header;

#pragma pack(1)
typedef struct 
{
	/* owned by chapter */
	uint8_t entry;						// what type of entry is this? name, birth date
	uint8_t format;						// format of offset_data
	uint8_t len; // # bytes read from data_offset. if 0, data IS the data_offset value, of type 'format'
	uint16_t offset_data;				// either holds data or an offset to the data
	uint16_t offset_next_entry;			// file offset to next entry
}Entry;

#pragma pack(1)
typedef struct 
{
	/* owned by book */
	/* owns entries */
	uint8_t title;
	uint8_t entry_count;
	uint16_t offset_first_entry;
	uint16_t offset_next_chapter;
}Chapter;

// this struct is used in a table to look up these fields for each entry
typedef struct 
{
	/* data */
	uint8_t format;
	uint8_t str_len;
	uint8_t mult_ok;
	uint8_t required;
	char entry_str[NAME_LEN_MAX];
}Entry_Info;

// [titles][entries]
Entry_Info* entry_info_table[MAX_NUM_ENTRIES][MAX_ENTRY_PER_TITLE];
Entry_Info* sub_entry_info_list[MAX_NUM_ENTRIES][MAX_ENTRY_PER_TITLE];

uint8_t required_entries[MAX_ENTRY_PER_TITLE];  // store all required entries for this chapter, to be ticked off as they are received
uint8_t prev_read_entries[MAX_ENTRY_PER_TITLE]; // keep track of which entries have been read in this chapter

int8_t successful[5];
uint16_t success_info[5][2];
/*
	0: married?
	1: other ID married?
	2: kid? (ID with age < 10)
	3: 2 or more pets
	4: has a job for > 20yrs
*/

#endif
