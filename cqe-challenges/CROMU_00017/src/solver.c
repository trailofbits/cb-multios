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
#include "solver.h"
#include "string.h"

// test input
char *tests[] = {"(4+2)*3",
				 "3*(4+2)",
				 "2+2*(16/8)-40",
				 "1-3*(2+7)+26",
				 "2*(2+(1+3)*2)-15", // 5
				 "1+2+3+4+5-5-4-3-2-1",
				 "(1*2*3*4)/3+10",
				 "(1+2)*4-22/(5+6)",
				 "(77/7-2-3)*2",
				 "2*((8*2+2)/3)", // 10
				 "(2+3)",
				 "(12345)"};

// after each test, verify its truthiness
int answers[] = {18,18,-34,0,5,0,18,10,12,12,5,12345};


// Runs an internal set of tests
void run_tests()
{
	int answer = 0;

	char tmp[66];
	char *ptr;
	ptr = tmp;
	int runs = 0;
	while(runs < 1000)
	{
		char equation[256];
		int answer = generate_one_equation(equation);
		printf("r: @d @s = @d\n", runs, equation, answer);
		runs++;
	}

	for (int i = 0; i < TEST_LEN; i++)
	{ 
		solve_equation(tests[i], &answer);
		printf("equation: @s = @d \n", tests[i], answer);
		printf((answer == answers[i]) ? "correct\n" : "wrong\n");
		printf("-----------------\n");
	}

}

// returns a ** b
int get_pow(int a, int b)
{
	int ret = 0;
	int i;
	if (b == 0)
		return 0;

	for (i = 1; i <= b; i++)
	{
		ret += a * a;
	}
	return ret;
}


// Evaluates a single mathemetical operation
int evaluate(int a, char op, int b, int *answer)
{


	debug_print("Evaluate: @d @c @d\n", a, op, b);
	if (op == '+')
	{
		// check for overflow/underflow
		if ((a > 0 && b > MAX_INT - a) ||
			(a < 0 && b < (-1*MAX_INT) - a))
		{
			return FAIL; // overflow would happen
		}
		*answer = a+b;
		return SUCCESS;
	}
	else if (op == '-')
	{
		// check for overflow/underflow
		if ((a > 0 && b < (-1*MAX_INT) + a) ||
			(a < 0 && b > MAX_INT + a))
		{
			debug_print("Overflow detected on subtract\n", 0);
			return FAIL; // overflow would happen
		} 
		*answer = a - b;
		return SUCCESS;
	}
		
	else if (op == '*')
	{
		int64_t x = (int64_t)a*b;
		// check for overflow/underflow
		if ((x > 0x7fffffff) || (x < -0x7fffffff))
		{
			return FAIL;
		}
		*answer = a*b;
		return SUCCESS;
	}
		
	else if (op == '/')
	{
		if (b == 0)
			return FAIL; // divide by zero

		*answer = a/b;
		return SUCCESS;
	}
		
	return FAIL;
}


// Solves the equation within a set of parenthesis 
// returns SUCCESS or FAIL
int satisfy_paren()
{
	char op;
	int larg;
	int rarg;
	int answer;
	int ret;

	ret = peek_op(&op);
	while (op != '(' && ret == SUCCESS)
	{
		
		// evaluate everything inside of the parens
		if (pop_num(&rarg) != SUCCESS) return FAIL;
		if (pop_num(&larg) != SUCCESS) return FAIL;
		if (pop_op(&op) != SUCCESS) return FAIL;
		if (evaluate(larg, op, rarg, &answer) != SUCCESS) return FAIL;
		
		debug_print("inside paren loop: @d@c@d=@d\n", larg, op, rarg, answer);
		
		push_num(answer);
		ret = peek_op(&op);
	}
	if (op == '(')
	{
		pop_op(&op); // consume the open paren
	}
	return ret;
}



// Solves the equation in 'str'
// returns SUCCESS if equation was solved
// returns FAIL if equation couldn't be solved
// Solution returned in 'answer'
int solve_equation(char* str, int *answer)
{
	int j = 0;
	int ret;
	char curr;

	// intialize stack
	curr_num_stack = -1;
	curr_op_stack = -1;

	while (str[j] != 0)
	{
		curr = str[j];
		// walk through the equation
		if (curr <= '9' && curr >= '0')
		{
			char t;
			int is_neg = 0;
			int val;
			// get the number (could be any number of spots)
			// this is a number, push it on the stack

			ret = peek_op(&t);
			if (ret == SUCCESS && t == '-')
			{
				if(pop_op(&t) != SUCCESS) return FAIL;
				push_op('+');
				is_neg = 1;
			}
			int moved = 0;
			val = stoi(str+j, &moved);
	
			if (is_neg)
				val *= -1;
			is_neg = 0;

			push_num(val);
			//tmp = get_str_end(str+j);
			j += moved; 
			continue;		
		}
		if (curr == '(')
		{
			push_op(str[j]);
			j++;
			continue;
		}
		if (curr == ')')
		{
			if (satisfy_paren() != SUCCESS) return FAIL;
			j++;
			continue;
		}
		if (curr == '+' || curr == '-')
		{
			char p_op;
			ret = peek_op(&p_op);
			if (ret == SUCCESS && (p_op == '+' || p_op == '-' || p_op == '*' || p_op == '/'))
			{
				char prev_op;
				int larg, rarg, answer = 0;
				if (pop_num(&rarg)!= SUCCESS) return FAIL;
				if (pop_num(&larg)!= SUCCESS) return FAIL;
				if (pop_op(&prev_op)!= SUCCESS) return FAIL;
				if (evaluate(larg, prev_op, rarg, &answer) != SUCCESS) return FAIL;
				push_num(answer);
			}
			push_op(str[j]);
			j++;
			continue;
		}
		if (curr == '*' || curr == '/')
		{
			char prev_op;
			ret = peek_op(&prev_op);
			if (ret == SUCCESS && (prev_op == '*' || prev_op == '/'))
			{
				int larg, rarg, answer = 0;
				if (pop_num(&rarg)!= SUCCESS) return FAIL;
				if (pop_num(&larg)!= SUCCESS) return FAIL;
				if (pop_op(&prev_op)!= SUCCESS) return FAIL;
				if (evaluate(larg, prev_op, rarg, &answer) != SUCCESS) return FAIL;
				push_num(answer);
			}
			push_op(str[j]);
			j++;
			continue;
		}
		return FAIL; // Invalid input. 
			
	}

	int b,a, tmp;
	pop_num(&b);
	while(curr_op_stack != -1)
	{
		if (pop_num(&a)!= SUCCESS) return FAIL;
		if (pop_op(&curr)!= SUCCESS) return FAIL;
		if (evaluate(a,curr,b, &tmp)!= SUCCESS) return FAIL;
		b = tmp;
	}
	*answer = b;
		
	return SUCCESS;
}
