/*

Author: Jason Williams <jdw@cromulence.com>

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
#include "rx.h"
#include <libcgc.h>
#include <stdlib.h>

#define NOISE_POWER_AMP		20.0

double get_rand_uniform( void )
{
	// Rand returns 0 to RAND_MAX (which is 31-bits of resolution)
	double rand_1 = rand() >> 4;
	double rand_2 = rand() >> 5;

	return (((rand_1 * 67108864) + rand_2) * (1.0 / 9007199254740992));
}

int8_t add_awgn_to_sample( int8_t sample_in )
{
	// Use Box Muller method to apply a guassian distribution of noise at a specific amplitude to the channel
	double S;
	double V1;
	double V2;

	do
	{
		double U1 = get_rand_uniform();
		double U2 = get_rand_uniform();

		V1 = (2*U1) - 1.0;
		V2 = (2*U2) - 1.0;

		S = (V1 * V1) + (V2 * V2);
	} while ( S >= 1.0 );

	double X = sqrt( -2 * log(S) / S) * V1;
	double Y = sqrt( -2 * log(S) / S) * V2;

	int8_t noise = (int8_t)(X * sqrt(NOISE_POWER_AMP));

	// Apply clipping...
	int16_t new_value = (int16_t)noise + (int16_t)sample_in;
	sample_in = noise + sample_in;

	if ( new_value >= 128 )
		sample_in = 127;
	else if ( new_value <= -128 )
	       sample_in = -127;	

	return sample_in;	
}

uint8_t receive_sample( int8_t sample_in )
{
	// Apply AWGN (noise) to channel
	sample_in = add_awgn_to_sample( sample_in );

	// Receive 16-bit sample
	
	// Perform bandpass filter at 1200Hz, 3 order butterworth filter. 200Hz pass band.
	double gain_filter1200 = 4.048569625e+03;
	
	static double xv1200[7], yv1200[7];

	// Filter coefficients by mkfilter -Bu -Bp -o 3 -a 1.145833333e-01 1.354166667e-01
	xv1200[0] = xv1200[1];
	xv1200[1] = xv1200[2];
	xv1200[2] = xv1200[3];
	xv1200[3] = xv1200[4];
	xv1200[4] = xv1200[5];
	xv1200[5] = xv1200[6];
	xv1200[6] = ((double)sample_in) / gain_filter1200;	

	yv1200[0] = yv1200[1];
	yv1200[1] = yv1200[2];
	yv1200[2] = yv1200[3];
	yv1200[3] = yv1200[4];
	yv1200[4] = yv1200[5];
	yv1200[5] = yv1200[6];
	yv1200[6] = 	(xv1200[6] - xv1200[0]) + 3 * (xv1200[2] - xv1200[4])
		      + ( -0.7695209444 * yv1200[0]) + (  3.4144655490 * yv1200[1])
		      + ( -7.5648606090 * yv1200[2]) + (  9.9352637805 * yv1200[3])
		      + ( -8.2553097726 * yv1200[4]) + (  4.0663572642 * yv1200[5]);

	double bpf1200_out = yv1200[6];


	// Perform bandpass filter at 2400Hz, 3 order butterworth filter. 200Hz pass band.
	double gain_filter2400 = 4.048569627e+03;

	static double xv2400[7], yv2400[7];

	// Filter coefficients by mkfilter -Bu -Bp -o 3 -a 2.3958333333e-01 2.6041666667e-1
	xv2400[0] = xv2400[1];
	xv2400[1] = xv2400[2];
	xv2400[2] = xv2400[3];
	xv2400[3] = xv2400[4];
	xv2400[4] = xv2400[5];
	xv2400[5] = xv2400[6];
	xv2400[6] = ((double)sample_in) / gain_filter2400;	

	yv2400[0] = yv2400[1];
	yv2400[1] = yv2400[2];
	yv2400[2] = yv2400[3];
	yv2400[3] = yv2400[4];
	yv2400[4] = yv2400[5];
	yv2400[5] = yv2400[6];
	yv2400[6] = 	(xv2400[6] - xv2400[0]) + 3 * (xv2400[2] - xv2400[4])
		      + ( -0.7695209444 * yv2400[0]) + (  0.0000000000 * yv2400[1])
		      + ( -2.5098818583 * yv2400[2]) + (  0.0000000000 * yv2400[3])
		      + ( -2.7383849074 * yv2400[4]) + (  0.0000000000 * yv2400[5]);

	double bpf2400_out = yv2400[6];


	// Next envelope detectors for each of the bandpass filters (before going into comparator)
	// Envelope detector LPF filter set to 600Hz (600bps max)
	
	// Detector 1
	const double gain_lpf = 1.886646578e+02;

	static double xv_env1200[4], yv_env1200[4];
	
	// Filter coefficients by mkfilter -Bu -Lp -o 3 -a 6.2500000000e-02 0.0000000000e+00 -l
	xv_env1200[0] = xv_env1200[1];
	xv_env1200[1] = xv_env1200[2];
	xv_env1200[2] = xv_env1200[3];
	xv_env1200[3] = (bpf1200_out * bpf1200_out) / gain_lpf;
	
	yv_env1200[0] = yv_env1200[1];
	yv_env1200[1] = yv_env1200[2];
	yv_env1200[2] = yv_env1200[3];
	yv_env1200[3] =    (xv_env1200[0] + xv_env1200[3]) + 3 * (xv_env1200[1] + xv_env1200[2])
			 + (  0.4535459334 * yv_env1200[0]) + ( -1.7151178300 * yv_env1200[1])
		  	 + (  2.2191686183 * yv_env1200[2]);

	double env1200_out = yv_env1200[3];

	// Detector 2
	static double xv_env2400[4], yv_env2400[4];

	// Filter coefficients by mkfilter -Bu -Lp -o 3 -a 6.2500000000e-02 0.0000000000e+00 -l
	xv_env2400[0] = xv_env2400[1];
	xv_env2400[1] = xv_env2400[2];
	xv_env2400[2] = xv_env2400[3];
	xv_env2400[3] = (bpf2400_out * bpf2400_out) / gain_lpf;
	
	yv_env2400[0] = yv_env2400[1];
	yv_env2400[1] = yv_env2400[2];
	yv_env2400[2] = yv_env2400[3];
	yv_env2400[3] =    (xv_env2400[0] + xv_env2400[3]) + 3 * (xv_env2400[1] + xv_env2400[2])
			 + (  0.4535459334 * yv_env2400[0]) + ( -1.7151178300 * yv_env2400[1])
		  	 + (  2.2191686183 * yv_env2400[2]);

	double env2400_out = yv_env2400[3];
	
	if ( env2400_out > env1200_out )
		return FREQ_2400_IND;
	else
		return FREQ_1200_IND;	
}
