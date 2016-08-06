/*

Author: Steve Wood <swood@cromulence.co>

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
#include "stdlib.h"


unsigned char encoder_values[] = { 	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
							'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 
							'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 
							'y', 'z', '1', '2', '3', '4', '5', '6',
							'7', '8', '9', '0', 'A', 'B', 'C', 'D',
							'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
							'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
							'U', 'V', 'W', 'X', 'Y', 'Z', '-', '+' 
						};


unsigned char *My64Encode(size_t data_size, unsigned char *data, size_t *out_data_size) {

unsigned char *output_data;
unsigned char *padded_input_data;

size_t output_size;
size_t padded_input_size;

unsigned char byteA, byteB, byteC, byteD;

size_t i, j;


		switch (data_size%3) {


			case (2):

				padded_input_size = data_size + 1;
				output_size = (padded_input_size) * 4 / 3;
				break;

			case (1):

				padded_input_size = data_size + 2;
				output_size = (padded_input_size) * 4 / 3;
				break;

			case (0):

				padded_input_size = data_size;
				output_size = padded_input_size * 4 / 3;
				break;
		}	

		padded_input_data = malloc(padded_input_size);

		if (padded_input_data == 0) {

			printf("unable to malloc()\n");
			_terminate(-1);
		}

		bzero(padded_input_data, padded_input_size);

		memcpy(padded_input_data, data, data_size);

		output_data = malloc(output_size);

		if (output_data == 0) {

			printf("unable to malloc()\n");
			_terminate(-1);

		}

		bzero(output_data, output_size);

		for (i=0, j=0; i< padded_input_size; i+=3, j+=4) {

			byteA = padded_input_data[i]  >> 2;
			byteB = ((padded_input_data[i] & 0x3) << 4) | (padded_input_data[i+1]>>4);
			byteC = ((padded_input_data[i+1] & 0xf) <<2) | ((padded_input_data[i+2] & 0xc0)>> 6);
			byteD = (padded_input_data[i+2] & 0x3f);

			output_data[j] = encoder_values[byteA];
			output_data[j+1] = encoder_values[byteB];
			output_data[j+2] = encoder_values[byteC];
			output_data[j+3] = encoder_values[byteD];

		}

		free(padded_input_data);

		*out_data_size = output_size;

		return output_data;
}


void encode_command(char *cmd) {

char buffer[1024];
unsigned char *encoded;
size_t encoded_size;
size_t i;
int count;
unsigned char *input_data;

	printf("How many bytes of data:\n");

	getline( buffer, 100 );

	count = atoi(buffer);

	if (count > 0) {
	
		input_data = malloc(count);

		if (input_data == 0) {

			printf("unable to malloc()\n");
			_terminate(-1);
		}
	}
	else
		return;

	printf("Enter data to be encoded:\n");

	receive_bytes( input_data, count );

	encoded=My64Encode(count, input_data, &encoded_size);

	// this was added to keep an extra long input from being passed onto the routine that reads the main menu
	flush_input(STDIN);

	for (i=0; i< encoded_size; ++i)
			printf("@c", encoded[i]);

	printf("\n");

	free(encoded);


}