
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

// Generates a word problem for solving the perimeter of various shapes.
// Returns SUCCESS if the user enters a correct answer
// Returns FAIL if the user enters an incorrect answer
int request_perimeter()
{
	// randomly choose which shape to use
	int rnum = random_in_range(0,2);
	switch (rnum)
	{
		case 0:
		{
			// circle
			// select radius 
			int radius = random_in_range(0,34567); 
			
			// peri = 2*PI*r
			int peri = 2 * PI * radius;

			// print values to user
			printf("find perimeter of circle with radius @d\n", radius);
			// ask user for answer
			int answer = 0;
			int ret = get_user_answer(&answer);
			if (ret != SUCCESS)
				return FAIL;

			if (answer == peri)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
		case 1:
		{
			// rectangle
			// select side, base
			int side = random_in_range(0,34567); 
			int base = random_in_range(0,34567); 

			// peri = 2 * side + 2 * base
			int peri = 2 * side + 2 * base;

			// print values to user
			printf("find perimeter of rectangle with a base of @d and sides of @d\n", base, side);
			// ask user for answer
			int answer = 0;
			int ret = get_user_answer(&answer);
			if (ret != SUCCESS)
				return FAIL;
			if (answer == peri)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
		case 2:
		{
			// boxy
			// select side, base
			int num_sides = random_in_range(0,1234); 
			int length_of_side = random_in_range(0,34567); 

			int peri = num_sides * length_of_side;

			// print values to user
			printf("find perimeter of object with @d sides of length @d\n", num_sides, length_of_side);
			// ask user for answer
			int answer = 0;
			int ret = get_user_answer(&answer);
			if (ret != SUCCESS)
				return FAIL;
			if (answer == peri)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
	}
	return SUCCESS;
}

// Generates a word problem for solving various elements of different shapes involving perimeter.
// Returns SUCCESS if the user enters a correct answer
// Returns FAIL if the user enters an incorrect answer
int request_2d_peri_dim()
{
	// select type of shape (rectangle, circle, arbitrary-sided shape)
	int rnum = random_in_range(0,2);
	switch (rnum)
	{
		case 0:
		{
			// circle
			// select radius 
			int radius = random_in_range(0,34567); 

			// peri = 2*PI*r
			int peri = 2 * PI * radius;

			// print question to user
			int requested_value = 0;
			int ran = random_in_range(0,1);
			if (ran == 0)
			{
				printf("find perimeter of circle with radius @d\n", radius);
				requested_value = peri;
			}
			else if (ran == 1)
			{
				printf("find radius of circle with perimeter @d\n", peri);
				requested_value = radius;
			}

			// ask user for answer
			int answer = 0;
			int ret = get_user_answer(&answer);
			if (ret != SUCCESS)
				return FAIL;
			if (answer == requested_value)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
		case 1:
		{
			// rectangle
			// select side, base
			int side = random_in_range(0,34567); 
			int base = random_in_range(0,34567); 

			// peri = 2 * side + 2 * base
			int peri = 2 * side + 2 * base;

			// print question to user
			int requested_value = 0;
			int ran = random_in_range(0,2);
			if (ran == 0)
			{
				printf("find perimeter of rectangle with a base of @d and sides of @d\n", base, side);
				requested_value = peri;
			}
			else if (ran == 1)
			{
				printf("find side of rectangle with a base of @d and perimeter of @d\n", base, peri);
				requested_value = side;
			}
			else if (ran == 2)
			{
				printf("find base of rectangle with a side of @d and perimeter of @d\n", side, peri);
				requested_value = base;
			}

			// ask user for answer
			int answer = 0;
			int ret = get_user_answer(&answer);
			if (ret != SUCCESS)
				return FAIL;
			if (answer == requested_value)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
		case 2:
		{
			// boxy
			// select side, base
			int num_sides = random_in_range(0,1234); 
			int length_of_side = random_in_range(0,34567); 

			// peri = 2 * side + 2 * base
			int peri = num_sides * length_of_side;

			// print question to user
			int requested_value = 0;
			int ran = random_in_range(0,2);
			if (ran == 0)
			{
				printf("find perimeter of object with @d sides of length @d\n", num_sides, length_of_side);
				requested_value = peri;
			}
			else if (ran == 1)
			{
				printf("find the number of sides of object with @d perimeter and the sides are of length @d\n", peri, length_of_side);
				requested_value = num_sides;
			}
			else if (ran == 2)
			{
				printf("find length of the sides of object with @d perimeter with @d sides\n", peri, num_sides);
				requested_value = length_of_side;
			}

			// ask user for answer
			int answer = 0;
			if (get_user_answer(&answer) != SUCCESS)
				return FAIL;

			if (answer == requested_value)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
	}
	return SUCCESS;
}


// Generates a word problem for solving the area of different shapes.
// Returns SUCCESS if the user enters a correct answer
// Returns FAIL if the user enters an incorrect answer
int request_area()
{
	// select the type of shape (circle, rectangle, square)
	int rnum = random_in_range(0,2);
	switch (rnum)
	{
		case 0:
		{
			// circle

			// select radius
			int radius = random_in_range(0,15000); 

			// area = PI*r*r
			int area = PI * radius * radius;

			// print values to user
			printf("find area of circle with radius @d\n", radius);

			// ask user for answer
			int answer = 0;
			if (get_user_answer(&answer) != SUCCESS)
				return FAIL;
			if (answer == area)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
		case 1:
		{
			// rectangle

			// select side, base
			int side = random_in_range(0,34567); 
			int base = random_in_range(0,34567); 

			// area = side * base
			int area = side * base;

			// print values to user
			printf("find area of rectangle with a base of @d and sides of @d\n", base, side);

			// ask user for answer
			int answer = 0;
			if (get_user_answer(&answer) != SUCCESS)
				return FAIL;
			if (answer == area)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
		case 2:
		{
			// square

			// select side
			int side = random_in_range(0,34567); 

			// area = side * side
			int area = side * side;

			// print values to user
			printf("find area of square with sides of @d\n", side);

			// ask user for answer
			int answer = 0;
			if (get_user_answer(&answer) != SUCCESS)
				return FAIL;
			if (answer == area)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
	}
	return SUCCESS;
}

// Generates a word problem for solving various elements of different shapes involving area.
// Returns SUCCESS if the user enters a correct answer
// Returns FAIL if the user enters an incorrect answer
int request_2d_area_dim()
{
	
	int rnum = random_in_range(0,1);
	switch (rnum)
	{
		case 0:
		{
			// circle
			// select radius 
			int radius = random_in_range(0,15000);

			int area = PI * radius * radius;

			// print question to user
			int requested_value = 0;
			int ran = random_in_range(0,1);
			if (ran == 0)
			{
				printf("find area of circle with radius @d\n", radius);
				requested_value = area;
			}
			else if (ran == 1)
			{
				printf("find radius of circle with area @d\n", area);
				requested_value = radius;
			}

			// ask user for answer
			int answer = 0;
			if (get_user_answer(&answer) != SUCCESS)
				return FAIL;
			if (answer == requested_value)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
		case 1:
		{
			// rectangle
			// select side, base
			int side = random_in_range(0,34567); 
			int base = random_in_range(0,34567); 

			int area = side * base;

			// print question to user
			int requested_value = 0;
			int ran = random_in_range(0,2);
			if (ran == 0)
			{
				printf("find area of rectangle with a base of @d and sides of @d\n", base, side);
				requested_value = area;
			}
			else if (ran == 1)
			{
				printf("find side of rectangle with a base of @d and area of @d\n", base, area);
				requested_value = side;
			}
			else if (ran == 2)
			{
				printf("find base of rectangle with a side of @d and area of @d\n", side, area);
				requested_value = base;
			}

			// ask user for answer
			int answer = 0;
			if (get_user_answer(&answer) != SUCCESS)
				return FAIL;
			if (answer == requested_value)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
	}
	return SUCCESS;
}

// Generates a word problem for solving the volume of various shapes.
// Returns SUCCESS if the user enters a correct answer
// Returns FAIL if the user enters an incorrect answer
int request_volume()
{
	// select the type of shape (sphere, rectangular prism, cube)
	int rnum = random_in_range(0,2);
	switch (rnum)
	{
		case 0:
		{
			// sphere
			int radius = random_in_range(0,430); 

			// vol = (4/3) * PI * r * r * r
			int vol = 4*PI*(radius * radius * radius / 3);

			// print values to user
			printf("find volume of sphere with radius @d\n", radius);
			// ask user for answer
			int answer = 0;
			if (get_user_answer(&answer) != SUCCESS)
				return FAIL;
			if (answer == vol)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
		case 1:
		{
			// rectangular prism

			// select side, base, height
			int side = random_in_range(0,1288); 
			int base = random_in_range(0,1288); 
			int height = random_in_range(0,1288); 

			int vol = side * base * height;

			// print values to user
			printf("find volume of rectangular prism with a base of @d, side of @d, and height of @d\n", base, side, height);
			// ask user for answer
			int answer = 0;
			if (get_user_answer(&answer) != SUCCESS)
				return FAIL;
			if (answer == vol)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
		case 2:
		{
			// cube

			// select side
			int side = random_in_range(0,1288); 

			int vol = side * side * side;

			// print values to user
			printf("find volume of cube with sides of @d\n", side);
			// ask user for answer
			int answer = 0;
			if (get_user_answer(&answer) != SUCCESS)
				return FAIL;
			if (answer == vol)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
	}

	return SUCCESS;
}

// Generates a word problem for solving various elements of different shapes involving volume.
// Returns SUCCESS if the user enters a correct answer
// Returns FAIL if the user enters an incorrect answer
int request_3d_dim_vol()
{
	// print type of shape (sphere, rectangular prism, cube)
	int rnum = random_in_range(0,2);
	switch (rnum)
	{
		case 0:
		{
			// sphere
			int radius = random_in_range(0,430);

			// vol = (4/3) * PI * r * r * r
			int vol = 4*PI*(radius * radius * radius / 3);

			// print question to user
			int requested_value = 0;
			int ran = random_in_range(0,1);
			if (ran == 0)
			{
				printf("find volume of sphere with radius @d\n", radius);
				requested_value = vol;
			}
			else if (ran == 1)
			{
				printf("find radius of sphere with volume @d\n", vol);
				requested_value = radius;
			}
			// ask user for answer
			int answer = 0;
			if (get_user_answer(&answer) != SUCCESS)
				return FAIL;
			if (answer == requested_value)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
		case 1:
		{
			// rectangular prism

			// select side, base, height
			int side = random_in_range(0,1288); 
			int base = random_in_range(0,1288); 
			int height = random_in_range(0,1288);

			int vol = side * base * height;

			// print question to user
			int requested_value = 0;
			int ran = random_in_range(0,3);
			if (ran == 0)
			{
				printf("find volume of rectangular prism with a base of @d, side of @d, and height of @d\n", base, side, height);
				requested_value = vol;
			}
			else if (ran == 1)
			{
				printf("find side of rectangular prism with a base of @d, volume of @d, and height of @d\n", base, vol, height);
				requested_value = side;
			}
			else if (ran == 2)
			{
				printf("find base of rectangular prism with a volume of @d, side of @d, and height of @d\n", vol, side, height);
				requested_value = base;
			}
			else if (ran == 3)
			{
				printf("find height of rectangular prism with a volume of @d, side of @d, and base of @d\n", vol, side, base);
				requested_value = height;
			}
			// ask user for answer
			int answer = 0;
			if (get_user_answer(&answer) != SUCCESS)
				return FAIL;
			if (answer == requested_value)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
		case 2:
		{
			// cube

			// select side
			int side = random_in_range(0,1288); 

			int vol = side * side * side;

			// print question to user
			int requested_value = 0;
			int ran = random_in_range(0,1);
			if (ran == 0)
			{
				printf("find volume of cube with a side of @d\n", side);
				requested_value = vol;
			}
			else if (ran == 1)
			{
				printf("find side of cube with a volume of @d\n", vol);
				requested_value = side;
			}
			// ask user for answer
			int answer = 0;
			if (get_user_answer(&answer) != SUCCESS)
				return FAIL;
			if (answer == requested_value)
			{
				printf("you got it\n");
				return SUCCESS;
			}
			else
			{
				printf("incorrect\n");
				return FAIL;
			}
			break;
		}
	}
	return SUCCESS;
}