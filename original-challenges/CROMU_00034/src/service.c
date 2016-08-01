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

#include <libcgc.h>
#include "service.h"

uint16_t entry_count;
uint16_t chapter_count;

uint16_t read_short()
{
	uint16_t val;
	//size_t rx;

	//if ( receive( STDIN, &val, sizeof(val), &rx ) != 0 ) 
	if (receive_bytes( (uint8_t*)&val, sizeof(val) ) != 2 )
	{
        return 0;
    }
    return val;
}

void populate_entry(int entry, int num, char* str, int str_len, uint8_t req, uint8_t mult, uint8_t type)
{
	entry_info_table[entry][num] = (Entry_Info*)malloc(sizeof(Entry_Info));
	entry_info_table[entry][num]->format = type;
	entry_info_table[entry][num]->mult_ok = mult;
	entry_info_table[entry][num]->required = req;
	entry_info_table[entry][num]->str_len = str_len;
	strncpy(entry_info_table[entry][num]->entry_str, str, str_len);
	bzero(str, NAME_LEN_MAX);	
}

void populate_sub_entry(int entry, int num, char* str, int str_len, uint8_t req, uint8_t mult, uint8_t type)
{
	sub_entry_info_list[entry][num] = (Entry_Info*)malloc(sizeof(Entry_Info));
	sub_entry_info_list[entry][num]->format = type;
	sub_entry_info_list[entry][num]->mult_ok = mult;
	sub_entry_info_list[entry][num]->required = req;
	sub_entry_info_list[entry][num]->str_len = str_len;
	strncpy(sub_entry_info_list[entry][num]->entry_str, str, str_len);
	bzero(str, NAME_LEN_MAX);	
}

#define REQ 1
#define REQ_NO 0
#define MULT_OK 1
#define MULT_NO 0
// populate the entry_info_table with valid fields
void populateEntryInfo()
{
	char ss[NAME_LEN_MAX];
	bzero(ss, NAME_LEN_MAX);
	int num, entry;

// IDENTITY
	num = 0;
	entry = IDENTITY;

	strcpy(ss, "first name");
	populate_entry(entry, num++, ss, strlen(ss), REQ, 0, STR);

	strcpy(ss, "middle name");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, STR);

	strcpy(ss, "last name");
	populate_entry(entry, num++, ss, strlen(ss), REQ, 0, STR);

	strcpy(ss, "age");
	populate_entry(entry, num++, ss, strlen(ss), REQ, 0, CHAR);

	strcpy(ss, "weight");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, SHORT);

	strcpy(ss, "birth country");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, STR);

	strcpy(ss, "birth state");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, STR);

	strcpy(ss, "birth city");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, STR);

	strcpy(ss, "married");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, BOOL);

// MOVIE
	num = 0;
	entry = MOVIES;
	strcpy(ss, "title");
	populate_entry(entry, num++, ss, strlen(ss), REQ, 0, STR);

	strcpy(ss, "actor");
	populate_entry(entry, num++, ss, strlen(ss), 0, MULT_OK, STR);

	strcpy(ss, "director");
	populate_entry(entry, num++, ss, strlen(ss), 0, MULT_OK, STR);

	strcpy(ss, "producer");
	populate_entry(entry, num++, ss, strlen(ss), 0, MULT_OK, STR);

	strcpy(ss, "year released");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, SHORT);

	strcpy(ss, "plot summary");
	populate_entry(entry, num++, ss, strlen(ss), REQ, 0, STR);

// VEHICLES
	num = 0;
	entry = VEHICLES;

	strcpy(ss, "make");
	populate_entry(entry, num++, ss, strlen(ss), REQ, 0, STR);

	strcpy(ss, "model");
	populate_entry(entry, num++, ss, strlen(ss), REQ, 0, STR);

	strcpy(ss, "color");
	populate_entry(entry, num++, ss, strlen(ss), 0, MULT_OK, STR);

	strcpy(ss, "displacement");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, SHORT);

	strcpy(ss, "displacement units");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, CHAR);

	strcpy(ss, "doors");
	populate_entry(entry, num++, ss, strlen(ss), REQ, 0, CHAR);	

// BOOKS
	num = 0;
	entry = BOOKS;

	strcpy(ss, "author");
	populate_entry(entry, num++, ss, strlen(ss), REQ, MULT_OK, STR);

	strcpy(ss, "year");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, CHAR);

	strcpy(ss, "summary");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, STR);

	strcpy(ss, "publisher");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, STR);

	strcpy(ss, "character");
	populate_entry(entry, num++, ss, strlen(ss), 0, MULT_OK, STR);

	strcpy(ss, "made into a movie");
	populate_entry(entry, num++, ss, strlen(ss), REQ, 0, BOOL);	

// SONG
	num = 0;
	entry = SONGS;

	strcpy(ss, "writer");
	populate_entry(entry, num++, ss, strlen(ss), REQ, MULT_OK, STR);

	strcpy(ss, "year");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, CHAR);

	strcpy(ss, "genre");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, STR);

	strcpy(ss, "publisher");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, STR);

	strcpy(ss, "free online");
	populate_entry(entry, num++, ss, strlen(ss), REQ, 0, BOOL);	

// JOB
	num = 0;
	entry = JOBS;

	strcpy(ss, "title");
	populate_entry(entry, num++, ss, strlen(ss), REQ, MULT_OK, STR);

	strcpy(ss, "years");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, CHAR);

	strcpy(ss, "job category");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, STR);

	strcpy(ss, "company");
	populate_entry(entry, num++, ss, strlen(ss), REQ, 0, STR);

	strcpy(ss, "have a best friend");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, BOOL);

	strcpy(ss, "salary");
	populate_entry(entry, num++, ss, strlen(ss), REQ, 0, INT);

	num = 0;
	entry = HOBBIES;

	strcpy(ss, "");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, PTR);

	strcpy(ss, "");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, PTR);

	strcpy(ss, "");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, PTR);

	strcpy(ss, "");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, PTR);

	strcpy(ss, "");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, PTR);

	strcpy(ss, "");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, PTR);

	num = 0;
	entry = PETS;

	strcpy(ss, "name");
	populate_entry(entry, num++, ss, strlen(ss), REQ, MULT_OK, STR);

	strcpy(ss, "species");
	populate_entry(entry, num++, ss, strlen(ss), REQ, 0, STR);

	strcpy(ss, "legs");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, CHAR);

	strcpy(ss, "inside only");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, BOOL);

	strcpy(ss, "age");
	populate_entry(entry, num++, ss, strlen(ss), 0, 0, CHAR);

	strcpy(ss, "shots updated");
	populate_entry(entry, num++, ss, strlen(ss), REQ, 0, BOOL);
}

void populateSubEntryInfo()
{
	char ss[NAME_LEN_MAX];
	bzero(ss, NAME_LEN_MAX);
	int num, entry;

// HOBBIES

// SHOOTING
	num = 0;
	entry = SHOOTING;
	strcpy(ss, "make");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, MULT_OK, STR);

	strcpy(ss, "model");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, MULT_OK, STR);

	strcpy(ss, "league");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, STR);

	strcpy(ss, "length");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, CHAR);

	strcpy(ss, "length units");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, STR);

	strcpy(ss, "years experience");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, CHAR);

	strcpy(ss, "injury");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, BOOL);

// KNIVES
	num = 0;
	entry = KNIVES;
	strcpy(ss, "make");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, STR);

	strcpy(ss, "model");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, STR);

	strcpy(ss, "value");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, SHORT);

	strcpy(ss, "style");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, STR);

	strcpy(ss, "blade length");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, CHAR);

	strcpy(ss, "length units");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, STR);

	strcpy(ss, "comes with sheath");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, BOOL);

	strcpy(ss, "injury");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, BOOL);

// STAMPS
	num = 0;
	entry = STAMPS;
	strcpy(ss, "name");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, STR);

	strcpy(ss, "value");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, SHORT);

	strcpy(ss, "seller");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, STR);

	strcpy(ss, "mint");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, BOOL);

	strcpy(ss, "count");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, CHAR);

// KAYAKING
	num = 0;
	entry = KAYAKING;
	strcpy(ss, "make");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, STR);

	strcpy(ss, "model");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, STR);

	strcpy(ss, "length");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, CHAR);

	strcpy(ss, "style");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, STR);

	strcpy(ss, "initial stability");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, CHAR);

	strcpy(ss, "years experience");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, CHAR);

	strcpy(ss, "highest class");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, CHAR);

	strcpy(ss, "touring");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, BOOL);

	strcpy(ss, "surfing");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, BOOL);

	strcpy(ss, "tricking");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, BOOL);

	strcpy(ss, "injury");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, BOOL);

// COINS
	num = 0;
	entry = COINS;
	strcpy(ss, "name");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, STR);

	strcpy(ss, "seller");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, STR);

	strcpy(ss, "value");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, INT);

	strcpy(ss, "mint");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, BOOL);

	strcpy(ss, "count");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, CHAR);

// EXERCISES
	num = 0;
	entry = EXERCISES;
	strcpy(ss, "name");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, MULT_OK, STR);

	strcpy(ss, "max weight");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, SHORT);

	strcpy(ss, "reps");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, CHAR);

	strcpy(ss, "sets");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, CHAR);

	strcpy(ss, "injury");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, BOOL);

// SPORTS
	num = 0;
	entry = SPORTS;

	strcpy(ss, "name");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, STR);

	strcpy(ss, "position");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, MULT_OK, STR);

	strcpy(ss, "years experience");
	populate_sub_entry(entry, num++, ss, strlen(ss), REQ, 0, CHAR);

	strcpy(ss, "injury");
	populate_sub_entry(entry, num++, ss, strlen(ss), 0, 0, BOOL);
}


// return an entry_info with the proper title field name
uint8_t getEntryInfo(uint16_t title, uint8_t entry, uint8_t is_sub, Entry_Info *entry_info)
{
	if (is_sub) 
		#ifdef PATCHED 
			{
				if (sub_entry_info_list[title][entry] == NULL) {
					return 0;
				}
				memcpy(entry_info,sub_entry_info_list[title][entry], sizeof(Entry_Info));
			}
		#else
			memcpy(entry_info,sub_entry_info_list[title][entry], sizeof(Entry_Info));
		#endif
	else 
		#ifdef PATCHED
			{
				if (entry_info_table[title][entry] == NULL) {
					return 0;
				}
				memcpy(entry_info,entry_info_table[title][entry], sizeof(Entry_Info));
			}
		#else
			memcpy(entry_info,entry_info_table[title][entry], sizeof(Entry_Info));
		#endif
	if (entry_info->mult_ok > 1 || entry_info->required > 1)
	{
		printf("WRONG FORMAT in getEntryInfo\n");
	}


	return 1;
}

int buffer_length;

int verify_entry(Entry *entry)
{
	if (!entry)
		return 1;

	if (entry->entry > MAX_ENTRY_PER_TITLE)
		return 2;

	if (entry->format > PTR)
		return 3;

	if (entry->format == STR || entry->format == INT)
		if (entry->offset_data >= buffer_length)
			return 4;

	if (entry->len > NAME_LEN_MAX)
		return 5;

	if (entry->offset_next_entry >= buffer_length)
		return 6;

	return 0;
}

int verify_chapter(Chapter *chap)
{
	if (!chap)
		return 1;

	if (chap->title >= TITLE_COUNT)
		return 2;

	if (chap->entry_count > MAX_ENTRY_PER_TITLE)
		return 3;

	if (chap->offset_first_entry >= buffer_length)
		return 4;

	if (chap->offset_next_chapter >= buffer_length)
		return 5;

	return 0;
}

int parse_book(uint8_t* buff, int rcv_len, int first_offset)
{
	Entry *entry;

	uint16_t next_offset = first_offset;

	int first = 1; // used for checking required entries in a chapter

	char is_subtitle = 0;
	uint16_t parent_of_subtitle = 0;
	
	char **names;
	char is_initial_subtitle = 0;

	Entry_Info *(*entry_table)[MAX_ENTRY_PER_TITLE];

	Chapter *chapter = NULL;
	do
	{
		// start parsing a new chapter
		if (chapter)
		{
			if (!chapter->offset_next_chapter && !is_initial_subtitle)
			{
				// this is the end of this chapter
				if (is_subtitle)
				{
					// reverting to chapter after hobby
					is_subtitle = 0;
					if (!parent_of_subtitle)
						continue;
					chapter = (Chapter*)(buff+parent_of_subtitle); 
				}
			}
			else
			{
				chapter = (Chapter*)(buff+next_offset); // normal flow after a chapter is done
				is_initial_subtitle = 0;
			}
		}
		else 
		{	
			// first chapter handled here
			chapter = (Chapter*)(buff+next_offset);
		}
		int t = 0;
		#ifdef PATCHED
		if ((uint8_t *)chapter + sizeof(Chapter) > buff + rcv_len) {
			printf("bad book.\n");
			return -1;
		}
		#endif

		//if (chapter->title >= NUM_TITLES-1 && !is_subtitle)
		if (chapter->title == HOBBIES && !is_subtitle)
		{ 	// we just found HOBBIES, change over
			printf("Title: @s\n", titles[chapter->title]);
			printf("Entry Count: 0x@x\n", chapter->entry_count);
			names = subtitles;
			entry_table = sub_entry_info_list;
			next_offset = (chapter->offset_first_entry);
			parent_of_subtitle = (chapter->offset_next_chapter);
			is_subtitle = 1;
			is_initial_subtitle = 1;
			// Problem: this chapter is over, need to point to the next chapter
			continue;
		}
		else if (!is_subtitle)
		{	// this is a normal chapter, so point to titles
			names = titles;
			entry_table = entry_info_table;

			#ifndef PATCHED

			if ((t = verify_chapter(chapter)) != 0)
			{
				printf("Malformed chapter found! @d Exiting.\n", t);
				_terminate(-2);
			}
		}
		#else
		}
		
		if ((t = verify_chapter(chapter)) != 0)
		{
			printf("Malformed chapter found! @d Exiting.\n", t);
			_terminate(-2);
		}
		#endif
		

		printf("Title: @s\n", names[chapter->title]);

		if (chapter->entry_count > MAX_NUM_ENTRIES)
		{
			printf("ERROR: Too many entries: @d\n", chapter->entry_count);
			_terminate(-1);
		}
		printf("Entry Count: 0x@x\n", chapter->entry_count);

		if (!chapter->offset_first_entry || !chapter->entry_count)
		{
			// go to the next chapter. no entries here
			next_offset = (chapter->offset_next_chapter);
			printf("NO entries found\n");
			continue;
		}

		int req_cnt = 1;
		int prev_read_counter = 0;
		first = 1;
		entry = (Entry*)(buff+((chapter->offset_first_entry)));
		//int t = 0;
		if ((t = verify_entry(entry)) != 0)
		{
			printf("Malformed entry found! @d Exiting.\n", t);
			_terminate(-1);
		}

		do
		{
			// parse a chapter. all of its entries
			int data_offset = 0;

			Entry_Info entry_info;
			if (names == subtitles)
				getEntryInfo(chapter->title, entry->entry, 1, &entry_info);
			else
				getEntryInfo(chapter->title, entry->entry, 0, &entry_info);

			// once per chapter, check the required entries
			if (first)
			{
				memset(prev_read_entries, -1, chapter->entry_count); 
				memset(required_entries, -1, MAX_ENTRY_PER_TITLE);

				// record the required entries for this chapter
				// later, make sure that these are populated 
				first = 0;
				prev_read_counter = 0;
				required_entries[0] = 0;
				for (int i = 0; i < MAX_ENTRY_PER_TITLE; i++)
				{
					if (entry_table[chapter->title][i] != NULL)
					{
						// check all entries for required entries
						if (entry_table[chapter->title][i]->required == 1)
						{
							// this is a required entry
							required_entries[req_cnt++] = i;
						}
					}
				}
				req_cnt--;
				required_entries[0] = req_cnt;
			}
  
			// if this entry was in the required_entry list, remove it (it has been satisfied)
			for (uint8_t i = 1; i <= req_cnt; i++)
			{
				if (entry->entry == required_entries[i])
				{
					// remove this from the required_entries list
					required_entries[i] = 70;
					required_entries[0] -= 1;
				}	
			}

			for (uint8_t i = 1; i <= prev_read_counter; i++)
			{
				if (entry->entry == prev_read_entries[i])
				{
					if (entry_info.mult_ok != MULT_OK)
					{
						// Duplicate! Not allowed.
						printf("Duplicate entry found! Exiting...\n");
						_terminate(-1);
					}
				}	
			}

			prev_read_entries[prev_read_counter++] = entry->entry;

			if (entry_info.format != entry->format)
			{
				// they sent us the wrong format. exit
				printf("WRONG FORMAT: @d vs @d\n", entry_info.format, entry->format);
				_terminate(-2);
			}

			if (chapter->title == PETS)
			{
				if (entry->entry == 0)
				{
					// 2 pets are required to set successful[3] to 1
					if (successful[3] == -1)
					{
						successful[3] = 1;
					}
					if (successful[3] == 0)
						successful[3] = -1;
				}
			}

			if (chapter->title == JOBS)
			{
				if (entry->entry == 1)
				{
					if (entry->offset_data > 20)
					{
						// more than 20 years on this job
						successful[4] = 1;
					}
				}
			}

			if (entry_info.format == STR)
			{
				// go to the offset and retrieve the string
				char str[NAME_LEN_MAX];
				memcpy(str, (char*)&buff[(entry->offset_data)], entry->len);
				if (entry->len < NAME_LEN_MAX)
					str[entry->len] = '\0';
				else
					str[NAME_LEN_MAX-1] = '\0';
				printf("@s: @s\n", entry_info.entry_str, str);
				data_offset += entry->len;
			}
			else if (entry_info.format == INT)
			{
				uint32_t num = *(uint32_t*)&buff[(entry->offset_data)];
				printf("@s: 0x@x\n", entry_info.entry_str, num);
				data_offset += 4;
			}
			else if (entry_info.format == BOOL)
			{
				short num = *(short*)&entry->offset_data;
				if (num == 1)
					printf("@s: true\n", entry_info.entry_str);
				else if (num == 0)
					printf("@s: false\n", entry_info.entry_str);
				else
					printf("@s!!: 0x@x\n", entry_info.entry_str, num);
				data_offset += 0;
			}
			else
				printf("@s: 0x@x\n", entry_info.entry_str, (entry->offset_data));

			if (chapter->title == IDENTITY)
			{
				if (entry->entry == 8)
				{
					// this ID is married
					if (successful[0] == 1)
					{
						success_info[1][0] = entry->offset_data;
						success_info[1][1] = entry->len;
						successful[1] = 1;
					}
					else
					{
						success_info[0][0] = entry->offset_data;
						success_info[0][1] = entry->len;
						successful[0] = 1;
					}
				}
				else
				{
					if (entry->entry == 3 && entry->offset_data < 11)
					{
						// ID with age less than 11
						successful[2] = 1;
						success_info[2][0] = entry->offset_data;
						success_info[2][1] = entry->len;
					}
				}
			}

			if ((entry->offset_next_entry) == 0)
				break;

			entry = (Entry*)(buff+((entry->offset_next_entry)));

			if ((t = verify_entry(entry)) != 0)
			{
				printf("Malformed entry found! @d @d Exiting..\n", t, entry->format);
				_terminate(-1);
			}
		} while (entry != NULL);

		next_offset = (chapter->offset_next_chapter);

		// if there are any left in 'required_entries', fail
		if (required_entries[0] != 0)
		{
			printf("DIDN'T SEND ME ALL THE REQUIRED ENTRIES! @c  ", required_entries[0]);
			return -1;
		}

	} while ((chapter->offset_next_chapter) || is_subtitle);

	return 1;
}

void init()
{
	populateEntryInfo();
	populateSubEntryInfo();
}

void test_win()
{
	int success = 0;
	for (int i = 0; i < 5; i++)
	{
		if (successful[i] == 1)
			success += 1;
	}
	
	if (success == 5)
	{
		char buff[10];

		#ifndef PATCHED
		int max_len = 25;
		#else
		int max_len = 9;
		#endif

		// WIN
		printf("What is your family's last name?\n");
		int len = receive_until(buff, '\n', max_len);
		buff[len] = 0;

		// names of two parents and kid put together
		printf("Congratulations, @s family! You have a great diary!\n",buff);
	}
}

// read the file
// parse and print the content
int main()
{
	init();

	memset(successful, 0, 5);
	memset(success_info, 0, 10*sizeof(uint16_t));

	int current_buffer_offset = 0;
	printf("Welcome to the diary logger!\n");

	// read the size of the input (uint16)
	uint16_t buffer_size = read_short();

	buffer_length = buffer_size;

	if (buffer_size < 1)
	{
		printf("Buffer length is too small.\n");
		_terminate(-3);
	}

	// create a buffer of 'size' size
	uint8_t *buffer = (uint8_t*)malloc( buffer_size );

	if (buffer == NULL)
	{
		printf("Failed to allocate enough space for this buffer.\n");
		_terminate(-3);
	}

	int rcv_len = receive_bytes(buffer, buffer_size);

	if (rcv_len != buffer_size)
	{
		printf("Buffer received is not correct size.\n");
		_terminate(-3);
	}

	if (buffer_size < sizeof(Header))
	{
		printf("Buffer received is not correct size.\n");
		_terminate(-3);
	}

	// read in the HEADER
	Header *header = (Header*)(buffer+current_buffer_offset);
	current_buffer_offset += sizeof(Header);

	// print header info
	printf("Length: @d\n", buffer_size);	
	printf("Magic number: 0x@x\n", header->magic_number);
	printf("Future: 0x@x\n", header->future);
	printf("Offset: 0x@x\n", header->offset_to_first_chapter);

	int ret = parse_book(buffer, rcv_len, header->offset_to_first_chapter);
	if (ret == -1)
	{
		printf("bad book.\n");
		return -1;
	}
	test_win();
	

	free(buffer);
	printf("good book.\n");
	return 0;
}
