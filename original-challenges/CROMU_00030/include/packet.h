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

#ifndef __PACKET_H__
#define __PACKET_H__

// packet types
#define CONTROL 'a'
#define MGMT 'b'
#define DATA 'c' 

// management subtypes
#define ASSREQ 'd' // needs to be 'lowest' letter
#define ASSRESP 'e'
#define AUTHREQ 'f'
#define AUTHCHALREQ 'g' // server to client
#define AUTHCHALRESP 'h' // client to server
#define AUTHRESP 'i'
#define DISREQ 'j'
#define DISRESP 'k'
#define DEAUTHREQ 'l'
#define DEAUTHRESP 'm'

// control packet subtypes
#define RTS 'n'
#define CTS 'o'
#define ACK 'p' 
#define NACK 'q' // needs to be 'highest' letter

/*
Data packet contents:
*/
#define DCDPCE 'v' // discard top piece 
#define GETLEN 'w' // get current max road length
#define NXTPCE 'x' // get next piece
#define PLCPCE 'z' // place piece

#define GOOD_DISRESP '3'
#define GOOD_DEAUTHRESP '7'
// GAME PACKET DATA
// these only go in the content field


#define ENC_ONE 1
#define ENC_TWO 2

// NACK reasons
#define ERR_OUT_OF_SEQUENCE 1
#define ERR_NO_CONNECTION 2
#define ERR_BAD_ENCRYPTION 3

#define MAX_CONTENT 10

#pragma pack(1)
// all numbers are from '0' to '9', ascii
typedef struct 
{
	char type; // a,b,c
	char subtype; // d-q, v-z
	char packet_number; // DATA packets only. increments current_packet_count_recvd
	char conn_number; // incremented after each successful association response (successful assoc)
	char length; // length of used content area
	char content[MAX_CONTENT]; // fixed-length content area
	char checksum; // 1 byte checksum of rest of packet (5-byte header + 10-byte content)
} Packet;


typedef struct
{
	int pending;
	char answer[5];
	int enc_type;
} Enc_Chal;

int seed_crypt;

int seed_length;

Enc_Chal enc_chal;

// these count for DATA packets only
int current_packet_count_recvd; // last incoming packet number
int current_packet_count_sent;  // last outgoing packet number

// tracks which game connection this is
// connections survive for 9 data packets, then need to be reestablished
// incremented each time a new association is made
int last_connection_number;
int current_connection_number;

// what type of encryption are we currently using?
int current_encryption;
int encryption_confirmed; // set to TRUE after AUTHCHALRESP is correctly received

int validate_packet(Packet *pkt);
int populate_packet(Packet *pkt, char* data, int len);
void print_packet(Packet *pkt);
int packet_handler(Packet* pkt);//, Game* game);
void print_status();

void send_ack(char pkt_num);
void send_nack(char pktnum, int reason);
void send_assoc_response(char req_conn);
void send_auth_response(char* req_enc);

void send_auth_challenge(int enc);
int handle_auth_challenge_resp(char* answer);

int handle_disass_req(char reason);
int handle_deauth_req(char reason);

void set_checksum(Packet *pkt); // pointer to packet and the number of bytes to include in the checksum calculation
char get_checksum(Packet *pkt);

void send_packet(Packet *pkt);
void send_packet_new(Packet *pkt, int data_len);
int decrypt_packet(char *packet, int len, int type);
int encrypt_data(char *packet, int len, int type);

int check_win(int);

#endif