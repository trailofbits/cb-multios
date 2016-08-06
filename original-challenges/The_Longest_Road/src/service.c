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
#include "math_lib.h"
#include "packet.h"
#include "game.h"

int goal_len = 9; // set target length to win game


int main()
{
	char packet_str[256];

	printf("go time\n");

	current_packet_count_recvd = UNINITIALIZED; 
	current_packet_count_sent = UNINITIALIZED;
	last_connection_number = UNINITIALIZED;
	current_connection_number = UNINITIALIZED;
	current_encryption = UNINITIALIZED;
	encryption_confirmed = FALSE;
	

	enc_chal = (const Enc_Chal){0};

	game_stack.top_element = UNINITIALIZED;

	Packet pkt;

	// how many incorrect packets received from user (after MAX_WRONG_MOVES, we quit)
	int cnt_incorrect = 0;

	int seed_len = seed_prng();
	if (seed_len == FAIL)
	{
		printf("didn't succeed in seeding prng()");
		return 1;
	}
	else
	{
		seed_length = seed_len;
	}

	// Loops and accepts user input over packet interface
	while (1)
	{
		printf("ready for next packet\n");

		if (check_win(goal_len) == 1)
		{
			printf("Good game\n");
			return 1;
		}

		// only allow MAX_WRONG_MOVES wrong packets
		if (cnt_incorrect >= MAX_WRONG_MOVES)
			break;

		int len = receive_until(packet_str, '\n', 255);
		if (strcmp(packet_str, "1212") == 0)
		{
			printf("good bye\n");
			return 1;
		}

		if (len != sizeof(Packet))
		{
			printf("not proper packet length: got @d, should be @d\n", len, sizeof(Packet));
			printf("I got: @s\n", packet_str);
			cnt_incorrect++;
			continue;
		}
		
		if (populate_packet(&pkt, packet_str, len) == FAIL)
		{
			cnt_incorrect++;
			continue;
		}
		int ret = validate_packet(&pkt);
		if (ret == FAIL)
		{
			printf("skipping packet processing due to malformed packet\n");
			cnt_incorrect++;
			continue;
		}

		// this is where we handle the packet and play the game
		ret = packet_handler(&pkt);
		if (ret == FAIL)
		{
			cnt_incorrect++;
			continue;
		}
		else if (ret == 2) // user requested exit
		{
			printf("exiting main loop\n");
			return 1;
		}
	}	
	printf("good bye\n");
	return 0;
}
