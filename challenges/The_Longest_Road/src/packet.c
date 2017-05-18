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

#include "cgc_packet.h"
#include "cgc_math_lib.h"
#include "cgc_game.h"

// reads user-sent string and saves it into a Packet struct
int cgc_populate_packet(Packet *pkt, char* data, int len)
{
	if (len != sizeof(Packet))
	{
		cgc_printf("not proper packet length: got @d, should be @d\n", len, sizeof(Packet));
		return FAIL;
	}

	cgc_memcpy(pkt, data, len);

	int content_len = pkt->length - '0';
	if (content_len > MAX_CONTENT || content_len < 0)
	{
		cgc_printf("length field outside valid range\n");
		return FAIL;
	}

	return SUCCESS;
}

// determine if this is a valid packet
int cgc_validate_packet(Packet *pkt)
{
	int ret = SUCCESS;

	// check TYPE
	if (pkt->type < CONTROL && pkt->type > DATA)
	{
		cgc_printf("type is out of range (@c)\n", pkt->type);
		ret = FAIL;
	}

	// check SUBTYPE
	if (pkt->type != DATA)
	{
		if (pkt->subtype > NACK || pkt->subtype < ASSREQ)
		{
			cgc_printf("subtype is out of range (@c)\n", pkt->subtype);
			ret = FAIL;
		}
	}
	else
	{
		if (pkt->subtype > PLCPCE || pkt->subtype < DCDPCE)
		{
			cgc_printf("data subtype is out of range (@c)\n", pkt->subtype);
			ret = FAIL;
		}
	}
	int len = pkt->length - '0';
	// validate length
	if (len > MAX_CONTENT || len < 0)
	{
		cgc_printf("length is out of range (@c)\n", pkt->length);
		ret = FAIL;
	}

	if (pkt->subtype != ASSREQ)
	{
		// verify connection number
		if ((pkt->conn_number - '0') != current_connection_number)
		{
			cgc_printf("connection number not valid: @c vs @c\n", pkt->conn_number, current_connection_number+'0');
			ret = FAIL;
		}
	}

	char checksum = cgc_get_checksum(pkt);
	if (pkt->checksum != checksum)
	{
		cgc_printf("checksum does not match @c vs @d", checksum, pkt->checksum);
		cgc_printf("@s\n", (char*)pkt);
		ret = FAIL;
	}

	return ret;
}


// given a packet, pkt, determine what will happen with the game
// handles control, management, and data packets
// if data, it will decrypt the packet and call game functions to handle user commands
// retuns TRUE if
// returns FALSE if 
int cgc_packet_handler(Packet* pkt)//, Game *game)
{
	if (pkt->type == MGMT)
	{
		if (pkt->subtype == ASSREQ)
		{
			// verify requested connection number is next number
			// if so, send response: association accepted
			// if not, send response: no
			cgc_send_assoc_response(pkt->content[0] - '0');

			return SUCCESS;
		}
		else if (pkt->subtype == ASSRESP)
		{
			// we should not receive this type of packet
			return FAIL;
		}
		else if (pkt->subtype == AUTHREQ)
		{
			cgc_send_auth_response(pkt->content);
			return SUCCESS;
		}
		else if (pkt->subtype == AUTHRESP)
		{
			// we should not receive this type of packet
			return FAIL;
		}
		else if (pkt->subtype == AUTHCHALRESP)
		{
			cgc_handle_auth_challenge_resp(pkt->content);
			return SUCCESS;
		}
		else if (pkt->subtype == DISREQ)
		{
			if (cgc_handle_disass_req(pkt->content[0]) == FAIL) // disass reason
			{
				cgc_printf("Failed disass\n");
				return 2; // quit the program
			}
			return SUCCESS;
		}
		else if (pkt->subtype == DISRESP)
		{
			// we should not receive this type of packet
			cgc_printf("Dissasociation response received\n");
			return FAIL;
		}
		else if (pkt->subtype == DEAUTHREQ)
		{
			if (cgc_handle_deauth_req(pkt->content[0]) == FAIL) // deauth reason
			{
				cgc_printf("failed deauth...leaving\n");
				return 2; // quit the program
			}
			return SUCCESS;
		}
		else if (pkt->subtype == DEAUTHRESP)
		{
			// we should not receive this type of packet
			cgc_printf("Dissasociation response received\n");
			return FAIL;
		}
	}
	else if (pkt->type == DATA)
	{
		Packet tmp_pkt;

		if (pkt->packet_number - '0' != current_packet_count_recvd+1)
		{
			cgc_printf("packet number incorrect: @c vs @c\n", pkt->packet_number, current_packet_count_recvd+1+'0');
			cgc_send_nack(pkt->packet_number, ERR_OUT_OF_SEQUENCE);
			return FAIL;
		}
		else
		{
			cgc_send_ack(pkt->packet_number);

			// handle game mechanics here
			if (pkt->subtype == NXTPCE)
			{
				Piece piece;

				// try to create a new piece
				int rtn = cgc_create_random_piece(&piece);
				if (rtn != SUCCESS)
				{
					// nope, can't create a new piece
					if (rtn == 33)
					{
						char *t = "nfull";
						// stack is full. game over
						tmp_pkt.type = DATA;
						tmp_pkt.subtype = NXTPCE;
						cgc_strncpy(tmp_pkt.content, t, cgc_strlen(t));

						cgc_send_packet_new(&tmp_pkt, cgc_strlen(t));
						return SUCCESS;
					}
					else if (rtn == 22)
					{
						// top piece already there. tell user there is already a piece to be used
						Packet tmp;
						tmp.type = DATA;
						tmp.subtype = NXTPCE;
						cgc_strncpy(tmp.content, "nusetop", 7);

						cgc_send_packet_new(&tmp, 7);
						return SUCCESS;
					}
					else
					{
						// not sure why it failed
						// print failure
						Packet tmp;
						tmp.type = DATA;
						tmp.subtype = NXTPCE;
						cgc_strncpy(tmp.content, "nconfused", 9);

						cgc_send_packet_new(&tmp, 9);
						return SUCCESS;
					}
				}
				else
				{
					// we just create a new piece. send it to the user
					char ss[9];
					cgc_piece_to_pkt(&piece, ss); // put piece info into packet format

					tmp_pkt.type = DATA;
					tmp_pkt.subtype = NXTPCE;
					cgc_memcpy(tmp_pkt.content, ss, 9);
					tmp_pkt.content[9] = '0';

					cgc_encrypt_data(tmp_pkt.content, 10, current_encryption);

					cgc_send_packet_new(&tmp_pkt, 9);
					return SUCCESS;
				}
			}
			else if (pkt->subtype == PLCPCE)
			{
				// check encryption is valid
				if (current_encryption == ENC_ONE)
				{
					// verify that data is properly encrypted
					cgc_decrypt_packet(pkt->content, pkt->length - '0', ENC_ONE);
				}
				else if (current_encryption == ENC_TWO)
				{
					// saves the decrypted content overtop the pkt->content pointer (same length)
					cgc_decrypt_packet(pkt->content, pkt->length - '0', ENC_TWO);
				}
				else
				{
					// encryption is required
					return FAIL;
				}

				// if the road was placed on another road, update max length
				// the pkt->content will say which two pieces are to be connected
				// format: <pieceA #><sideA>:<pieceB #><sideB>
				if ((pkt->length - '0') != 5)
				{
					return FAIL; // wrong length for placing a piece
				}
				if (game_stack.top_element < 1)
				{
					char *ss = "NO,PCE";
					// error, must get another piece first
					tmp_pkt.type = DATA;
					tmp_pkt.subtype = PLCPCE;
					cgc_memcpy(tmp_pkt.content, ss, 6);

					cgc_send_packet_new(&tmp_pkt, 6);
					return SUCCESS;
				}

				char sideA = pkt->content[1];
				// pkt->content[2] is a colon
				char sideB = pkt->content[4];
				int indexA = cgc_get_piece(pkt->content[0] - '0');
				if (indexA == -1)
				{
					cgc_printf("Out of bounds piece requested A: @d vs @d...\n", pkt->content[0] - '0', game_stack.top_element);
					return FAIL;
				}
				int indexB = cgc_get_piece(pkt->content[3] - '0');
				if (indexB == -1)
				{
					cgc_printf("Out of bounds piece requested B: @d vs @d...\n", pkt->content[3] - '0', game_stack.top_element);
					return FAIL;
				}
				if (cgc_connect_pieces(&game_stack.stack[indexA], sideA - '0', &game_stack.stack[indexB], sideB - '0') == FAIL)
				{
					// failed to connect pieces
					char *ss = "NO,ERROR";
					// user may have asked to connect two sides that don't both have roads
					Packet tmp;
					tmp.type = DATA;
					tmp.subtype = PLCPCE;
					cgc_memcpy(tmp.content, ss, 8);

					cgc_send_packet_new(&tmp, 8);
					return SUCCESS;
				}
				else
				{
					// successful placement
					tmp_pkt.type = DATA;
					tmp_pkt.subtype = PLCPCE;
					tmp_pkt.content[0] = '0' + cgc_current_max_road_len;

					cgc_encrypt_data(tmp_pkt.content, 10, current_encryption);

					cgc_send_packet_new(&tmp_pkt, 1);
					return SUCCESS;
				}
			}
			else if (pkt->subtype == GETLEN)
			{
				tmp_pkt.type = DATA;
				tmp_pkt.subtype = GETLEN;
				tmp_pkt.content[0] = '0' + cgc_current_max_road_len;

				cgc_encrypt_data(tmp_pkt.content, 10, current_encryption); 

				cgc_send_packet_new(&tmp_pkt, 1);
				return SUCCESS;
			}
			else if (pkt->subtype == DCDPCE)
			{
				// discard the top piece
				if (cgc_discard_piece() == SUCCESS)
				{
					tmp_pkt.type = DATA;
					tmp_pkt.subtype = DCDPCE;
					tmp_pkt.content[0] = 'y';

					cgc_send_packet_new(&tmp_pkt, 1);
					return SUCCESS;
				}
				else
				{
					tmp_pkt.type = DATA;
					tmp_pkt.subtype = DCDPCE;
					cgc_strncpy(tmp_pkt.content, "nplaced", 7);

					cgc_send_packet_new(&tmp_pkt, 7);
					return SUCCESS;
				}
			}
		}
	}

	return SUCCESS;
}

// send an ack for the pkt_num
// these are only for DATA packets
void cgc_send_ack(char pkt_num)
{	
	Packet tmp;
	tmp.type = CONTROL;
	tmp.subtype = ACK;
	tmp.content[0] = pkt_num;
	
	current_packet_count_recvd++;

	cgc_send_packet_new(&tmp,1);
}

// send NACK for pkt_num packet
// attach reason to content
void cgc_send_nack(char pktnum, int reason)
{
	Packet tmp;
	tmp.type = CONTROL;
	tmp.subtype = NACK;
	tmp.content[0] = pktnum;
	tmp.content[1] = reason + '0';
	
	current_packet_count_recvd++;

	cgc_send_packet_new(&tmp, 2);
}

// requested connection passed in as number
void cgc_send_assoc_response(char req_conn)
{
	if (req_conn == last_connection_number+1)
	{
		// reset packet counts for this new connection
		last_connection_number += 1;
		current_packet_count_recvd = UNINITIALIZED;
		current_connection_number = req_conn;

		// successful association
		Packet tmp;
		tmp.type = MGMT;
		tmp.subtype = ASSRESP;
		tmp.content[0] = '1';
		
		cgc_send_packet_new(&tmp, 1);
		cgc_printf("SUCCESSFUL association\n");
	}
	else 
	{
		// unsuccessful association
		Packet tmp;
		tmp.type = MGMT;
		tmp.subtype = ASSRESP;
		tmp.content[0] = '0';
		
		cgc_send_packet_new(&tmp, 1);
	}
}

// send an authentication response
// pass in the authentication type requested
void cgc_send_auth_response(char* req_enc)
{
	// pick from valid authentication types
	if (req_enc[0] == 'a')
	{
		cgc_send_auth_challenge(ENC_ONE);
	}
	else if (req_enc[0] == 'x')
	{	
		cgc_send_auth_challenge(ENC_TWO);
	}
	else
	{
		// unsuccessful association
		cgc_printf("AUTH RESP sent: fail\n");
		cgc_printf("requested: @s, next: @c\n", req_enc);
	}
}

int offset = 3;
void cgc_send_auth_challenge(int enc)
{
	enc_chal.pending = TRUE;

	// Generate a random string to send the user
	char chall_val[5];
	for (int i = 0; i < 5; i++) 
	{
		chall_val[i] = cgc_random_in_range('a', 'p'); 
	}

	enc_chal.enc_type = enc;

	Packet tmp;
	tmp.type = MGMT;
	tmp.subtype = AUTHCHALREQ;
	cgc_memcpy(tmp.content, chall_val, 5);
	
	cgc_send_packet_new(&tmp, 5);

	cgc_encrypt_data(chall_val, 5, enc);
	cgc_memcpy(enc_chal.answer, chall_val, 5);
}

int cgc_handle_auth_challenge_resp(char *answer)
{
	switch (enc_chal.enc_type)
	{
		case ENC_TWO:
		{
			char matches = SUCCESS;
			for (int i = 0; i < 5; i++)
			{
				if (answer[i] != enc_chal.answer[i])
					matches = FAIL; 
			}

			if (matches)
			{
				// user successfully answered the encryption challenge
				enc_chal.pending = FALSE;

				Packet tmp;
				tmp.type = MGMT;
				tmp.subtype = AUTHRESP;
				tmp.content[0] = '1'; // good auth
				cgc_send_packet_new(&tmp, 1);

				current_encryption = ENC_TWO;
				return TRUE;
			}
			else
			{
				cgc_printf("failed to match (@s)", enc_chal.answer);
				Packet tmp;
				tmp.type = MGMT;
				tmp.subtype = AUTHRESP;
				tmp.content[0] = '0'; // Failed authentication
				cgc_send_packet_new(&tmp, 1);

			}
			break;
		}
		case ENC_ONE:
		{
			char matches = SUCCESS;
			for (int i = 0; i < 5; i++)
			{
				if (answer[i] != enc_chal.answer[i])
					matches = FAIL; 
			}

			if (matches)
			{
				// user successfully answered the encryption challenge
				enc_chal.pending = FALSE;

				Packet tmp;
				tmp.type = MGMT;
				tmp.subtype = AUTHRESP;
				tmp.content[0] = '1'; // good auth
				cgc_send_packet_new(&tmp, 1);

				current_encryption = ENC_ONE;
				return TRUE;
			}
			else
			{
				cgc_printf("failed to match (@s)", enc_chal.answer);
				Packet tmp;
				tmp.type = MGMT;
				tmp.subtype = AUTHRESP;
				tmp.content[0] = '0'; // Failed authentication
				cgc_send_packet_new(&tmp, 1);

			}
			break;
		}
		default:
			return FALSE;
	}
	return FALSE;
}

int cgc_handle_disass_req(char reason)
{
	//cgc_printf("@c @c", current_encryption, encryption_confirmed);
	// if the user hasn't deauthenticated, then this is out of order, stop everything
	if (current_encryption != UNINITIALIZED || encryption_confirmed != FALSE)
	{
		cgc_printf("FAILED1\n");
		return FAIL;
	}

	// if reason is 'normal', just disass
	// if reason is anything else, stop program
	if (reason != GOOD_DISRESP)
	{
		Packet tmp;
		tmp.type = MGMT;
		tmp.subtype = DISRESP;
		tmp.content[0] = '0'; // Failed disassociation 
		cgc_send_packet_new(&tmp, 1);
		return FAIL; // quit program
	}
	else
	{
		// just disassociate
		Packet tmp;
		tmp.type = MGMT;
		tmp.subtype = DISRESP;
		tmp.content[0] = '1'; // Successful disassociation 
		cgc_send_packet_new(&tmp, 1);

		current_packet_count_recvd = UNINITIALIZED;
		current_packet_count_sent = UNINITIALIZED;
		last_connection_number = current_connection_number;
		current_connection_number = UNINITIALIZED;
	}
	return SUCCESS;
}

// User requested deauthentication 
int cgc_handle_deauth_req(char reason)
{
	// if reason is 'normal', just disass
	// if reason is anything else, stop program
	if (reason != GOOD_DEAUTHRESP)
	{
		// quit the program 
		Packet tmp;
		tmp.type = MGMT;
		tmp.subtype = DEAUTHRESP;
		tmp.content[0] = '0'; // Failed deauthentication

		cgc_send_packet_new(&tmp, 1);
		return FAIL; // cgc_exit
	}
	else
	{
		// just deauth
		Packet tmp;
		tmp.type = MGMT;
		tmp.subtype = DEAUTHRESP;
		tmp.content[0] = '1'; // Successful deauthentication
		cgc_send_packet_new(&tmp, 1);

		current_encryption = UNINITIALIZED;
		encryption_confirmed = FALSE;
	}
	return SUCCESS;
}

// pkt is a pointer to a Packet struct containing the type/subtype for this packet
// len is the number of characters being used in the content field
void cgc_send_packet(Packet *pkt)
{
	cgc_write((char*)pkt, sizeof(Packet));
	cgc_printf("\n");
}

// pkt is a pointer to a Packet struct containing the type/subtype for this packet
// len is the number of characters being used in the content field
void cgc_send_packet_new(Packet *pkt, int len)
{
	if (pkt->type == DATA) // data 
	{
		pkt->packet_number = ++current_packet_count_sent + '0';
	}
	else
		pkt->packet_number = '0';

	pkt->conn_number = current_connection_number + '0';

	for (int i = len; i < MAX_CONTENT; i++)
	{
		pkt->content[i] = '0';
	}
	pkt->length = len + '0';

	cgc_set_checksum(pkt);
	cgc_write((char*)pkt, sizeof(Packet));
	cgc_printf("\n");
}

char cgc_calculateCS(char *bytes, int len)
{
	char ret = 0;
	for (int i = 0; i < len; i++)
	{
		ret ^= bytes[i];
	}
	return ret;
}

void cgc_set_checksum(Packet *pkt)
{
	pkt->checksum = cgc_calculateCS((char*)pkt, sizeof(Packet) - 1); // don't count the checksum byte
}

char cgc_get_checksum(Packet *pkt)
{
	return cgc_calculateCS((char*)pkt, sizeof(Packet) - 1); // don't count the checksum byte
}

char *VALID_CHARS = "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz";
int LAST_CHAR_POS = 74; // zero-based last char index

// return offset into VALID_CHARS for character C
// return -1 if not found
int cgc_locate_char(char c)
{
	for (int i = 0; i < LAST_CHAR_POS; i++)
	{
		if (VALID_CHARS[i] == c)
			return i;
	}
	return -1;
}


// encrypt given characters
// return 0 if failure
// return 1 if success
int cgc_encrypt_data(char *data, int len, int type)
{
	if (type == ENC_TWO)
	{
		int i = 0;
		for (int i = 0; i < len; i++)
		{
			int char_index = cgc_locate_char(data[i]);
			if (char_index == -1)
			{
				// out of bounds character found
				return 0;
			}

			if (i %2 == 0)
			{
				// add the offset (wrap around)
				char x = VALID_CHARS[(char_index + offset) % (LAST_CHAR_POS)];
				data[i] = x;
			}
			else
			{
				// subtract the offset (wrap around)
				signed char x = char_index - offset;
				if (x < 0)
				{
					x = LAST_CHAR_POS - (offset-char_index);
				}
				data[i] = VALID_CHARS[x];
			}
		}
	}
	if (type == ENC_ONE)
	{
		int i = 0;
		for (int i = 0; i < len; i++)
		{
			int char_index = cgc_locate_char(data[i]);
			if (char_index == -1)
			{
				// out of bounds character found
				return 0;
			}

			if (i %2 == 0)
			{
				// subtract the offset (wrap around)
				signed char x = char_index - offset;
				if (x < 0)
				{
					x = LAST_CHAR_POS - (offset-char_index);
				}
				data[i] = VALID_CHARS[x];
				
			}
			else
			{
				// add the offset (wrap around)
				char x = VALID_CHARS[(char_index + offset) % (LAST_CHAR_POS)];
				data[i] = x;
			}
		}
	}
	return 1;
}

// this will decrypt the chars sent to it using XOR and save the result in the given packet
int cgc_decrypt_packet(char *data, int len, int type)
{
	if (type == ENC_TWO)
	{
		int i = 0;
		for (int i = 0; i < len; i++)
		{
			int char_index = cgc_locate_char(data[i]);
			if (char_index == -1)
			{
				// out of bounds character found
				return 0;
			}

			if (i %2 == 0)
			{
				// subtract the offset (wrap around)
				signed char x = char_index - offset;
				if (x < 0)
				{
					x = LAST_CHAR_POS - (offset-char_index);
				}
				data[i] = VALID_CHARS[x];
			}
			else
			{
				// add the offset (wrap around)
				char x = VALID_CHARS[(char_index + offset) % (LAST_CHAR_POS)];
				data[i] = x;
			}
		}
	}

	if (type == ENC_ONE)
	{
		int i = 0;
		for (int i = 0; i < len; i++)
		{
			int char_index = cgc_locate_char(data[i]);
			if (char_index == -1)
			{
				// out of bounds character found
				return 0;
			}

			if (i %2 == 0)
			{
				// add the offset (wrap around)
				char x = VALID_CHARS[(char_index + offset) % (LAST_CHAR_POS)];
				data[i] = x;
			}
			else
			{
				// subtract the offset (wrap around)
				signed char x = char_index - offset;
				if (x < 0)
				{
					x = LAST_CHAR_POS - (offset-char_index);
				}
				data[i] = VALID_CHARS[x];
			}
		}
	}
	return 1;
}

// return 1 if we won
// return 0 if we have not won yet
int cgc_check_win(int goal)
{
	char buff[5];
	if (cgc_get_max_road_len() >= goal)
	{
		cgc_printf("YOU WIN, what is your name?\n");
		#ifndef PATCHED
		int len = cgc_receive_until(buff, '\n', 25);
		#else
		int len = cgc_receive_until(buff, '\n', 5);
		#endif
		buff[len] = 0x00;
		cgc_printf("Well done, @s\n", buff);
		return 1;
	}
	return 0;
}

