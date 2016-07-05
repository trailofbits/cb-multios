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

#include <libcgc.h>
#include "math_lib.h"
#include "stack.h"
#include "stdlib.h"
#include "prng.h"
#include "string.h"
#include "solver.h"

// for random selection choosing
char operator_list[] = {'+','-','*','/'};

// acceptable input for user input
char acceptable_char[] = {"1234567890()*-+/"};

// receives an integer
int get_user_answer(int *answer)
{
	char buf[15];
	bzero(buf, 15);

	int status;
	status = receive(STDIN, buf, sizeof(buf) - 1, NULL);
	if (status != 0)
	{
		// Error on receive
		return FAIL;
	}
	int str_len = strlen(buf);
	if (buf[str_len-1] == '\n')
	{
		str_len -= 1;
	}
	for (int i = 0; i < str_len; i++) 
	{
		if (!isdigit(buf[i])&&!(buf[i]=='-'))
		{
			printf("incorrect item entered\n");
			return FAIL;
		}
	}
	*answer = atoi(buf);
	return SUCCESS;
}

int get_user_equation(char *equation)
{
	char buf[256];
	bzero(buf, sizeof(buf));

	int status;
	status = receive(STDIN, buf, sizeof(buf) - 1, NULL);
	if (status != 0)
	{
		// Error on receive
		return FAIL;
	}

	if (buf[strlen(buf)-1]=='\n')
	{
		strncpy(equation, buf, strlen(buf) - 1);
	}
	else
	{
		strncpy(equation, buf, strlen(buf));
	}
	return SUCCESS;

}

// return SUCCESS or FAIL
// checks char c against acceptable_char list
int isValidChar(char c)
{
	int i;
	for (i = 0; i < sizeof(acceptable_char); i++)
	{
		if (acceptable_char[i] == c)
			return SUCCESS;
	}
	return FAIL;
}

// return whether user input is formatted correctly
int parse_input(char *input)
{
	// iterate over string and ensure that they are valid numbers and operators
	int str_len = get_str_end(input);

	for (int i = 0; i < str_len; i++)
	{
		if (!isValidChar(input[i]))
			return FAIL;
	}

	return SUCCESS;
}


// Generate a single equation that will pass validity checks
// Returns answer to that equation
int generate_one_equation(char *equation)
{
	int success, answer;
	do
	{
		char last_op = '\0';
		int last_num = 1;
		int eq_it = 0; // iterator for the equation

		// number of operands
		int num_ops = random_in_range(4,15);

		// number of numbers in this equation
		int num_nums = num_ops + 1; 

		// number of parens
		int num_parens = random_in_range(0,num_ops); 
		// simplest way to add parens is to put all opening parens in the first half of the equation
		//  and the closing parens in the second half of the equation

		// keep track of how many parens we've inserted already
		int opening_parens_inserted = 0; 
		int closing_parens_inserted = 0;

		// alternate between placing a number and an operator
		int turn = 0; // 0: num, 1: operator

		int curr_num = 0; // track how many numbers written

		// construct the equation
		// go for the number of numbers in the equation
		for (curr_num = 0; curr_num < num_nums;)
		{
			if (turn == 0)
			{
				// insert a number
				if (curr_num < num_nums/2)// put them in the first half
				{
					// when adding number in first half, do this
					if (opening_parens_inserted < num_parens)
					{
						// add opening paren before a number
						equation[eq_it++] = '(';
						opening_parens_inserted++;
					}
				}

				// insert number here
				int num = random_in_range(1,256);
				if (last_op == '/')
				{
					num = random_in_range(1,last_num);
				}
				last_num = num;
				char s_num[15]; 
				itos(num, s_num);
	
				int len = get_str_end(s_num);
				for (int z = 0; z < len; z++)
				{
					equation[eq_it++] = s_num[z];
				}

				if (curr_num + 1 > num_nums/2)// put them in the second half
				{
					// when adding number in second half, do this
					if (closing_parens_inserted < opening_parens_inserted)
					{
						// add closing paren after a number
						equation[eq_it++] = ')';
						closing_parens_inserted++;
					}
				}

				turn = 1; // switch to operator
				curr_num++;
			}
			else
			{
				// insert random operator here from operator_list
				int sel = random_in_range(0,3);
				char op = operator_list[sel];
				last_op = op;
				equation[eq_it++] = op;
				turn = 0; // switch to number
			}
		}
		while(closing_parens_inserted < opening_parens_inserted)
		{
			equation[eq_it++] = ')';
			closing_parens_inserted++;
		}
		equation[eq_it] = '\0';

		debug_print("GENERATE EQUATION:\n", 0);

		debug_print("# ops: @d\n# nums: @d\n# parens: @d\n", num_ops, num_nums, num_parens);

		debug_print("Equation: @s\n", equation);

		answer = 0;
		success = solve_equation(equation, &answer);
		if (success != SUCCESS)
		{
			debug_print("Invalid equation generated, trying again...\n", 0);
		}
	} while ((success != SUCCESS) || (answer == 0));
	return answer;
}


// Presents the user with a valid randomly generated equation, prompts user for the answer, 
// and verifies user answer. 
// returns SUCCESS if the user answers correctly
// returns FAIL if the user doesn't
int generate_equation()
{
	// create equation
	char equation[256];
	int answer = generate_one_equation(equation);
	int user_answer = 0;
	printf("Equation: @s\n", equation);
	printf("gimme answer: ");
	if (get_user_answer(&user_answer) != SUCCESS)
	{
		printf("Bad input\n");
		return FAIL;
	}

	if (user_answer == answer)
	{
		printf("success!!\n");
		return SUCCESS;
	}
	else
	{
		printf("Incorrect answer\n");
		return FAIL;
	}

	return FAIL;
}

// Accepts user input to seed the prng
int seed_prng()
{
	char buf[256];
	bzero(buf, sizeof(buf));
 	int status;
 	size_t bytes_received;
 	printf("Enter some data\n");

	status = receive(STDIN, buf, sizeof(buf) - 1, &bytes_received);
	if (status != 0)
	{
		// Error on receive
		return FAIL;
	}

	// create the seed number here
	uint64_t seed = -1;
	for (int p = 0; p<bytes_received; p++)
	{
		seed = ((seed << 4) | (seed >> 60)) ^ buf[p];
	}
	sprng(seed);

	return SUCCESS;
}

// prompt user to enter an equation that satisfies the given parameters
int prompt_for_equation()
{
	char str[256]; 
	int ret = 0;
	bzero(str, sizeof(str));
	
	int goal_parens = random_in_range(0, 5);
	int goal_answer = random_in_range(0, 32768);
	char goal_operator = operator_list[random_in_range(0,3)];
	int goal_num_list[4];
	for (int i=0; i<4; i++)
	{
		goal_num_list[i] = random_in_range(1, 256);
	}

	printf("Enter an equation that has @d sets of parenthesis\n", goal_parens);
	printf("It must evaluate to @d and contain the @c operator\n", goal_answer, goal_operator);
	printf("and must use the numbers: @d @d @d and @d\n", goal_num_list[0], goal_num_list[1], goal_num_list[2], goal_num_list[3]);

	// this is where we parse their answer and make sure it passes our requirements
	int num_parens_found = 0; 
	int goal_operator_found = 0; 
	int goal_nums_found[4] = {0,0,0,0};

	if (get_user_equation(str) != SUCCESS)
		return FAIL;

	ret = parse_input(str);
	printf("string is formatted @s\n", (ret == 1 ? "correct":"incorrect"));

	// scan the user's string and check for each requirement
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == '(')
			num_parens_found++;
		if (str[i] == goal_operator)
			goal_operator_found++;
		if (str[i] <= '9' && str[i] >= '0')
		{
			int val;
			// extract number
			int moved = 0;
			val = stoi(&str[i], &moved);
			for (int j = 0; j<4; j++)
			{
				if (val == goal_num_list[j])
				{
					goal_nums_found[j]++;
				}
			}
			i += moved-1;
		}
	}

	if (num_parens_found != goal_parens)
	{
		printf("Incorrect number of parenthesis\n");
		return FAIL;
	}
	if (goal_operator_found == 0)
	{
		printf("Did not use @c operator\n", goal_operator);
		return FAIL;
	}
	for (int j = 0; j<4; j++)
	{
		if (goal_nums_found[j] == 0)
		{
			printf("Did not use number @d\n", goal_num_list[j]);
			return FAIL;
		}
	}

	// try to solve equation and see if it matches
	int answer = 0;
	int success = solve_equation(str, &answer);
	if (success != SUCCESS)
	{
		printf("Invalid equation format\n");
		return FAIL;
	}

	if (answer != goal_answer)
	{
		printf("incorrect answer: @d\n", answer);
		return FAIL;
	}

	printf("@s does resolve to @d, good!\n", str, answer);
	return SUCCESS;
	
}

