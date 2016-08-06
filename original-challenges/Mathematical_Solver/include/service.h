/*

Author: James Nuttall (james@cromulence.co)

Copyright (c) 2014 Cromulence LLC

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

#include "math_lib.h"

#define FAIL 0
#define SUCCESS 1

#define MAX_NUM_COUNT 64
#define MAX_OP_COUNT 64

// keep track of the last and next correct answers
typedef struct 
{
	int next_correct_answer; // used to compare the user's next answer
	int last_correct_answer; // TODO how use this?
	char *next_correct_equation; // used to compare the user's next equation
} Game_Info;

typedef struct
{
	// Total Won/Lost
	int num_won_total;
	int num_lost_total;
	// Solved Equations total
	int num_won_solved_equation;
	int num_lost_solved_equation;
	// Solved Equations with words
	int num_won_words; // equations won that had a spelled out number in it
	int num_lost_words; // equations won that had a spelled out number in it
	// Created Equations results
	int num_won_created_equations;
	int num_lost_created_equations;
	// perimeter correct
	int num_won_perimeter;
	int num_lost_perimeter;
	// volume correct
	int num_won_volume;
	int num_lost_volume;
	// area correct
	int num_won_area;
	int num_lost_area;
} Statistics;

extern Statistics game_stats;
extern Game_Info game_info;

void print_statistics();
int print_menu();