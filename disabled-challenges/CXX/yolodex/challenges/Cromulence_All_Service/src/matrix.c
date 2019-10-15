/*

Author: Joe Rogers <joe@cromulence.co>

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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_stdint.h"

#define pM(matrix,x,y) (matrix + x + y*X)
#define MAX_X (20)
#define MAX_Y (20)
#define MAX_MATRIX_SIZE (255)
uint8_t X;
uint8_t Y;

void cgc_Add(int32_t *m1, int32_t *m2, int32_t *result) {
	uint8_t x, y;

	for (x = 0; x < X; x++) {
		for (y = 0; y < Y; y++) {
			*pM(result,x,y) = *pM(m1,x,y) + *pM(m2,x,y);
		}
	}
}

void cgc_Sub(int32_t *m1, int32_t *m2, int32_t *result) {
	uint8_t x, y;

	for (x = 0; x < X; x++) {
		for (y = 0; y < Y; y++) {
			*pM(result,x,y) = *pM(m1,x,y) - *pM(m2,x,y);
		}
	}
}

void cgc_ScalerMultiply(int32_t *m1, int32_t multiplier, int32_t *result) {
	uint8_t x, y;

	for (x = 0; x < X; x++) {
		for (y = 0; y < Y; y++) {
			*pM(result,x,y) = *pM(m1,x,y) * multiplier;
		}
	}
}

void cgc_PrintMenu(void) {
	cgc_puts("Matrix Calculator");
	cgc_puts("1. Add two matrices");
	cgc_puts("2. Subtract two matrices");
	cgc_puts("3. Scalar multiply a matrix");
	cgc_puts("4. Return to main menu");
	cgc_printf("Choice: ");

}

int32_t cgc_ReadMatrix(int32_t *m) {
	uint8_t x, y;
	char buf[8];

	if (X == 0) {
		// X
		cgc_printf("X: ");
		if (cgc_receive_until(buf, '\n', 7) == 0) {
			return(0);
		}
		x = cgc_atoi(buf);	
		if (x < 1 || x > MAX_X) {
			cgc_puts("invalid");
			return(0);
		}
	
		// Y
		cgc_printf("Y: ");
		if (cgc_receive_until(buf, '\n', 7) == 0) {
			return(0);
		}
		y = cgc_atoi(buf);	
		if (y < 1 || y > MAX_Y) {
			cgc_puts("invalid");
			return(0);
		}

		// set the globals for later use
		X = x;
		Y = y;
	}
	
#ifdef PATCHED
	uint16_t matrix_size;
#else
	// BUG: 8-bit integer overflow possible
	uint8_t matrix_size;
#endif
	matrix_size = x * y;
	if (matrix_size > MAX_MATRIX_SIZE) {
		cgc_puts("matrix too large");
		return(0);
	}
		

	// Read in the matrix values
	cgc_puts("Enter the matrix values");
	for (x = 0; x < X; x++) {
		for (y = 0; y < Y; y++) {
			cgc_printf("@d,@d: ", x, y);
			if (cgc_receive_until(buf, '\n', 7) == 0) {
				return(0);
			}
			*pM(m, x, y) = cgc_atoi(buf);
		}
	}

	return(1);
}

void cgc_PrintMatrix(int32_t *m) {
	uint8_t x, y;

	for (x = 0; x < X; x++) {
		for (y = 0; y < Y; y++) {
			cgc_printf("@d ", *pM(m, x, y));
		}
		cgc_puts("");
	}

}

int32_t cgc_matrix_add(void) {
	int32_t m1[MAX_MATRIX_SIZE];
	int32_t m2[MAX_MATRIX_SIZE];
	int32_t result[MAX_MATRIX_SIZE];
	uint8_t x, y;

	X = 0;
	Y = 0;
	cgc_puts("First matrix");
	cgc_puts("Provide the matrix dimensions");
	if (!cgc_ReadMatrix(m1)) {
		return(0);
	}	
	cgc_puts("Second matrix");
	if (!cgc_ReadMatrix(m2)) {
		return(0);
	}	
	cgc_Add(m1, m2, result);
	cgc_puts("Result");
	cgc_PrintMatrix(result);

	return(1);
}
	
int32_t cgc_matrix_sub(void) {
	int32_t m1[MAX_MATRIX_SIZE];
	int32_t m2[MAX_MATRIX_SIZE];
	int32_t result[MAX_MATRIX_SIZE];
	uint8_t x, y;

	X = 0;
	Y = 0;
	cgc_puts("First matrix");
	cgc_puts("Provide the matrix dimensions");
	if (!cgc_ReadMatrix(m1)) {
		return(0);
	}	
	cgc_puts("Second matrix");
	if (!cgc_ReadMatrix(m2)) {
		return(0);
	}	
	cgc_Sub(m1, m2, result);
	cgc_puts("Result");
	cgc_PrintMatrix(result);

	return(1);
}
	
int32_t cgc_matrix_smul(void) {
	int32_t m1[MAX_MATRIX_SIZE];
	int32_t result[MAX_MATRIX_SIZE];
	uint8_t x, y;
	int32_t multiplier;
	char buf[8];

	X = 0;
	Y = 0;
	cgc_puts("Provide the matrix dimensions");
	if (!cgc_ReadMatrix(m1)) {
		return(0);
	}	
	cgc_printf("Multiplier: ");
	if (cgc_receive_until(buf, '\n', 7) == 0) {
		return(0);
	}
	multiplier = cgc_atoi(buf);	
	cgc_ScalerMultiply(m1, multiplier, result);
	cgc_puts("Result");
	cgc_PrintMatrix(result);

	return(1);
}
	
int32_t cgc_matrix_command(char *t) {
	char buf[8];
	uint8_t choice;
	
	while (1) {
		cgc_PrintMenu();
		if (cgc_receive_until(buf, '\n', 7) == 0) {
			return(0);
		}
		choice = cgc_atoi(buf);
		if (choice < 1 || choice > 4) {
			continue;
		}

		switch (choice) {
			case 1:
				cgc_matrix_add();
				break;
			case 2:
				cgc_matrix_sub();
				break;
			case 3:
				cgc_matrix_smul();
				break;
			case 4:
				return(0);
		}
	}
}
