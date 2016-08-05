/*

Author: Steve Wood <swood@cromulence.com>

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

#ifndef COMMANDS_H
#define COMMANDS_H

#define TERMINATE 			0xDEAD
#define CREATE_PRODUCT  	0x101
#define CREATE_PBI  		0x102
#define CREATE_SPRINT  		0x103
#define MOVE_PBI_TO_SPRINT	0x201
#define MOVE_SBI_TO_PBI 	0x202
#define LIST_PRODUCTS 		0x301
#define LIST_PBI 			0x302
#define LIST_SPRINTS 		0x303
#define LIST_ALL_PRODUCTS	0x304
#define DELETE_PBI 			0x401
#define DELETE_SPRINT 		0x402
#define DELETE_PRODUCT 		0x403
#define UPDATE_SBI_STATUS	0x501
#define UPDATE_SBI_POINTS   0x502
#define UPDATE_SBI_DESCR 	0x503

#define COMMAND_MAX_LEN 1024

typedef struct {

	unsigned int prefix;
	unsigned short command_length;
	unsigned short command_type;
	unsigned char command[COMMAND_MAX_LEN]; 

} commandMessageType;

typedef struct {

	unsigned int prefix;
	int command_response;


} commandResponseType;

typedef struct {

	unsigned short ID;
	char  title;

} newProductMessageType;

typedef struct {

	unsigned short ID;

} messageIDType;


typedef struct {

	unsigned short productID;
	unsigned short sprintID;
	char title;

} newSprintMessageType;


typedef struct {

	unsigned short productID;
	unsigned short sprintID;

} deleteSprintMessageType;

typedef struct {

	unsigned short productID;
	unsigned short pbItemID;
	unsigned short user_story_points;
	char title;

} newPBIMessageType;

typedef struct {

	unsigned short productID;
	unsigned short pbItemID;
	unsigned short sprintID;


} movePBIMessageType;

typedef struct {

	unsigned short productID;
	unsigned short pbItemID;
	unsigned short sprintID;

} moveToPBIMessageType;

typedef struct {

	unsigned short productID;
	unsigned short pbItemID;

} deletePBIMessageType;

typedef struct {

	unsigned short productID;
	unsigned short pbItemID;
	unsigned short sprintID;
	unsigned short status;

} updateSBIMessageType;


typedef struct {

	unsigned short productID;
	unsigned short pbItemID;
	unsigned short sprintID;
	char desc;

} updateSBIDescMessageType;


int create_product( productDefType **database, void *command_data );
int delete_product( productDefType **database, messageIDType *message );
int list_product( productDefType *database, messageIDType *message );
int create_sprint( productDefType *database, newSprintMessageType *message);
int delete_sprint( productDefType *database, deleteSprintMessageType *message);
int create_pbi( productDefType *database, newPBIMessageType *message );
int move_pbi_to_sprint( productDefType *database, movePBIMessageType *message );
int delete_pbi( productDefType *database, deletePBIMessageType *message);
int update_sbi_status( productDefType *database, updateSBIMessageType *message );
int update_sbi_points( productDefType *database, updateSBIMessageType *message );
int move_sbi_to_pbl( productDefType *database, moveToPBIMessageType *message );
int update_sbi_description( productDefType *database, updateSBIDescMessageType *message );
int list_all_products( productDefType *database );

int send_response( int response_code );

#endif

