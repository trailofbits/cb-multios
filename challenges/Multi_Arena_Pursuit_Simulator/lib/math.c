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
#include "cgc_math.h"

double cgc_exponential(double x) {
	double sum = 1.0;

	for (int t = 1; t < EXP_NUM_TERMS; t++) {
		double numerator=1.0;
		for (int n = 0; n < t; n++) {
			numerator = numerator * x / (n+1);
		}

		sum = sum + numerator;
	}

	return sum;
}

double cgc_ln(double x) {
	double sum = 0.0;
	int powerOfTwos = 0;
	double ln2 = 0.69314718056;
	double sum2 = 1.0;

	while( x >= 2.0) {
		x = x/2.0;
		powerOfTwos++;
	}

	for (int t = 1; t < LN_NUM_TERMS+1; t++) {
		double numerator= 1.0;
		int sign = 1;
		for(int n = 0; n < t; n++) {
			sign = sign * -1;
			numerator = numerator * (x - 1);
		}
		sign = sign * -1;
		sum = sum + sign * numerator/t; 
	}

	sum = sum + powerOfTwos * ln2;

	return sum;
}

double cgc_pow(double x, double n) {
	int powerOfTwenty = 0;
	int two = 1;
	double sum = 1.0;
	double exp20 = 485165195.41;
	double e_exp = 0.0;

	e_exp = n*cgc_ln(x);

	while( e_exp >= 20.0) {
		e_exp = e_exp - 20.0;
		powerOfTwenty++;
	}

	for (int p=0; p < powerOfTwenty; p++) {
		sum = sum*exp20;
	}

	return sum * cgc_exponential(e_exp);
}

double cgc_cosine(double x) {
	double sum = 1.0;

	while(x >= 2*PI || x <= -2*PI) {
		if(x < 0)
			x = x + 2*PI;
		else
			x = x - 2*PI;
	}

	for (int t = 1; t < TRIG_NUM_TERMS; t++) {
		double numerator=1.0;
		for (int n = 0; n < 2*t; n++) {
			numerator = numerator * x / (n+1);
		}
		int sign = 1;
		for (int n = 0; n<t; n++) {
			sign = sign * -1;
		}

		sum = sum + sign * numerator; 

	}

	return sum;
}

double cgc_sine(double x) {
	double sum;

	while(x >= 2*PI || x <= -2*PI) {
		if(x < 0)
			x = x + 2*PI;
		else
			x = x - 2*PI;
	}

	sum = x;
	for (int t = 1; t < TRIG_NUM_TERMS; t++) {
		double numerator = 1.0;
		int sign = 1;

		for(int n = 0; n < 2*t + 1; n++) {
			numerator = numerator * x / (n+1);
		}

		for(int n = 0; n < t; n++) {
			sign = sign*-1;
		}

		sum = sum + sign * numerator;

	}

	return sum;
}

double cgc_atan(double x) {
	double sum = x;

	if(x >= 1.0 || x <= -1.0) {
		double arctanU = 0.732815102;
		double u = 0.9;
		double v;

		v = (x - u) / (1 + u*x);

		return arctanU+ cgc_atan(v);
	}

	for (int t = 1; t < TRIG_NUM_TERMS; t++) {
		double numerator = 1.0;
		int sign = 1;

		for(int n = 0; n < 2*t + 1; n++) {
			numerator = numerator * x;
		}

		for(int n = 0; n < t; n++) {
			sign = sign*-1;
		}

		sum = sum + sign * numerator / (2*t + 1);

	}

	return sum;
}

double cgc_atanTwo(double y, double x) {
	if( x > 0)
		return cgc_atan(y/x);
	if( x < 0) {
		if(y >= 0)
			return cgc_atan(y/x) + PI;
		else
			return cgc_atan(y/x) - PI;
	}
	if( x == 0) {
		if(y > 0)
			return PI/2;
		if(y < 0)
			return -PI/2;
	}

	return 99999999999;

}

double cgc_sqrt(const double x) {

	const double acc = .001;
	double upper, lower, guess;

	if (x < 1)
	{
		lower = x;
		upper = 1;
	} else {
		lower = 1;
		upper = x;
	}

	while((upper-lower) > acc) {
		guess = (lower + upper) / 2;
		if(guess*guess > x)
			upper = guess;
		else 
			lower = guess;
	}

	return (lower + upper) / 2;

}