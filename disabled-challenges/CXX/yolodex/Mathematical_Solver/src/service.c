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

#include "libcgc.h"
#include "cgc_service.h"
#include "cgc_stdlib.h"
#include "cgc_shapes.h"
#include "cgc_stack.h"
#include "cgc_prng.h"
#include "cgc_string.h"
#include "cgc_solver.h"


// Globals
Statistics game_stats;
Game_Info game_info;


int cgc_print_menu()
{
	int ret;
	cgc_printf("1. Solve Equation\n");
	cgc_printf("2. Create Equation\n");
	cgc_printf("3. Solve Area\n");
	cgc_printf("4. Solve Perimeter\n");
	cgc_printf("5. Solve Volume\n");
	cgc_printf("6. View Statistics\n");
	cgc_printf("7. Exit\n");

	cgc_get_user_answer(&ret);
	return ret;
}

void cgc_print_statistics()
{
	char name[32];
	cgc_printf("Total won: @d\n", game_stats.num_won_total);
	cgc_printf("Total lost: @d\n", game_stats.num_lost_total);
	cgc_printf("Equations solved correctly: @d\n", game_stats.num_won_solved_equation);
	cgc_printf("Equations solved incorrectly: @d\n", game_stats.num_lost_solved_equation);
	cgc_printf("Equations created correctly: @d\n", game_stats.num_won_created_equations);
	cgc_printf("Equations created incorrectly: @d\n", game_stats.num_lost_created_equations);
	cgc_printf("Solved perimeter problems @d\n", game_stats.num_won_perimeter);
	cgc_printf("Unsolved perimeter problems @d\n", game_stats.num_lost_perimeter);
	cgc_printf("Solved volume problems @d\n", game_stats.num_won_volume);
	cgc_printf("Unsolved volume problems @d\n", game_stats.num_lost_volume);
	cgc_printf("Solved area problems @d\n", game_stats.num_won_area);
	cgc_printf("Unsolved area problems @d\n", game_stats.num_lost_area);
	
// Vulnerability 1
	if (game_stats.num_won_created_equations == 20)
	{
		cgc_printf("Wow, you created 20 equations! What's your name?:");
		cgc_bzero(name, sizeof(name));
		#ifdef PATCHED
			cgc_receive(STDIN, name, sizeof(name) -1 , NULL);
		#else
			cgc_receive(STDIN, name, sizeof(name) + 45, NULL);
		#endif
		cgc_printf("Good job, @s!\n", name);
	}

// Vulnerability 2
	if (game_stats.num_won_solved_equation == 20)
	{
		cgc_printf("Wow, you solved 20 equations! What's your name?:");
		cgc_bzero(name, sizeof(name));
		#ifdef PATCHED
			cgc_receive(STDIN, name, sizeof(name) -1 , NULL);
		#else
			cgc_receive(STDIN, name, sizeof(name) + 45, NULL);
		#endif
		cgc_printf("Good job, @s!\n", name);
	}

// Vulnerability 3
	if (game_stats.num_won_area == 20)
	{
		cgc_printf("Wow, you solved 20 area problems! What's your name?:");
		cgc_bzero(name, sizeof(name));
		#ifdef PATCHED
			cgc_receive(STDIN, name, sizeof(name) -1 , NULL);
		#else
			cgc_receive(STDIN, name, sizeof(name) + 45, NULL);
		#endif
		cgc_printf("Good job, @s!\n", name);
	}
}

int main(int cgc_argc, char *cgc_argv[])
{
	int ret;

	// zero out structs
	game_stats = (const Statistics){0};
	game_info = (const Game_Info){0};


	if (cgc_seed_prng() != SUCCESS)
	{
		debug_print("didn't succeed in seeding prng()");
		return 1;
	}

	while (1)
	{
		ret = cgc_print_menu();
		switch(ret)
		{
			case 1:
				// Solve Equation
				// generate an equation and make the user solve it
				if (cgc_generate_equation() == SUCCESS)
				{
					game_stats.num_won_solved_equation++;
				}
				else
				{
					game_stats.num_lost_solved_equation++;
				}
				break;
			case 2:
				// create equation
				// prompt user to enter an equation that satisfies the given parameters
				if (cgc_prompt_for_equation() == SUCCESS)
				{
					game_stats.num_won_created_equations++;
				}
				else
				{
					game_stats.num_lost_created_equations++;
				}
				break;
			case 3:
				// area
				if (cgc_random_in_range(0,1) == 0)
				{
					if (cgc_request_area() == SUCCESS)
					{
						game_stats.num_won_area++;
					}
					else
					{
						game_stats.num_lost_area++;
					}
				}
				else
				{
					if (cgc_request_2d_area_dim() == SUCCESS)
					{
						game_stats.num_won_area++;
					}
					else
					{
						game_stats.num_lost_area++;
					}
				}
				break;
			case 4:
				// perimeter
				if (cgc_random_in_range(676,677) == 676)
				{
					if (cgc_request_perimeter() == SUCCESS)
					{
						game_stats.num_won_perimeter++;
					}
					else
					{
						game_stats.num_lost_perimeter++;
					}
				}
				else
				{
					if (cgc_request_2d_peri_dim() == SUCCESS)
					{
						game_stats.num_won_perimeter++;
					}
					else
					{
						game_stats.num_lost_perimeter++;
					}
				}
				break;
			case 5:
				// volume
				if (cgc_random_in_range(44,45) == 45)
				{
					if (cgc_request_volume() == SUCCESS)
					{
						game_stats.num_won_volume++;
					}
					else
					{
						game_stats.num_lost_volume++;
					}
				}
				else
				{	
					if (cgc_request_3d_dim_vol() == SUCCESS)
					{
						game_stats.num_won_volume++;
					}
					else
					{
						game_stats.num_lost_volume++;
					}
				}
				break;
			case 6:
				// View Statistics
				cgc_print_statistics();
				break;
			case 7:
				// Exit
				return 0;
			default:
				cgc_printf("improper input. exiting\n");
				return 0;
		}
	}

	return 0;
}
