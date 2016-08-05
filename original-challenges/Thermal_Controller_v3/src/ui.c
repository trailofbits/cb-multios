/*

Author: James Connor (jymbo@cromulence.com)

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
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <input.h>
#include "service.h"
#include "ui.h"

int ui_main(){
	register pState state = init_state();
	while(1){
		get_command(state);
	}
	return 0;
}

void get_bytes(unsigned char *buf, unsigned int num){
	if (receive_bytes(buf, num) == -1){
		_terminate(-1);
	}

	return;
}

void prime_buf(unsigned char *buf){
	bzero(buf, MAX_MESSAGE_LEN+8);
	unsigned char ok[12] = { 0xa5, 0x5a, 0x0a, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	memcpy(buf,ok,12);
	return;
}

unsigned short get_short(unsigned char *buf){
	return *(unsigned short *) buf;
}

unsigned int get_int(unsigned char *buf){
	return *(unsigned int *) buf;
}

int get_signed_int(unsigned char *buf){
	return *(int *)buf;
}

int get_command(pState state){
	//magic len command subcommand data checkval
	//message is len + 8 (2 magic, 2 len, 4 checkval)
	//magic = 0xa55a, short len, short command, var subcommand, var data, int checkval

	// unsigned char *buf = malloc(MAX_MESSAGE_LEN+8);
	unsigned char buf[MAX_MESSAGE_LEN+8];	
	unsigned int checkval = 0;
	unsigned int calc_checkval = 0;
	unsigned short magic = 0;
	unsigned short len = 0;
	unsigned short command = 0xaa;
	unsigned short subcommand = 0xffff;
	unsigned short sensorID = 0xffff;
	unsigned int sensor_address = 0xffff;
	unsigned int coefficient = 0xffff;
	unsigned short temp = 0xffff;
	unsigned short numSteps = 0xffff;
	unsigned short *tempP = NULL;
	unsigned short seconds = 0;
	pStep steps = NULL;
	int ret = -1;
	unsigned int fw = 0;
	bzero(buf,MAX_MESSAGE_LEN+8);

	//get magic
	get_bytes(buf ,2);
	magic = get_short(buf);
	if (magic != MAGIC){
		prime_buf(buf);
		send(buf,12);
		//free(buf);
		return 1;
	}

	//get len
	get_bytes(buf+2,2);
	len = get_short(buf+2);
	//check len
	if (len > MAX_MESSAGE_LEN){
		prime_buf(buf);
		send(buf,12);
		//free(buf);
		return 1;
	}

	//get the rest of message except checkval
	get_bytes(buf+4, len);
	//get checkval
	checkval = get_int(buf+len);
	//compare to calculated from message
	calc_checkval = check_val( buf, len);
	if (  checkval != calc_checkval  ){
		//bad check_val
		prime_buf(buf);
		send(buf,12);
		//free(buf);
		return 1;
	}

	//get command
	command = get_short(buf+4);
	switch (command) {
		case 1:{ //set power state
			subcommand = get_short(buf+6);
			prime_buf(buf);
			if (subcommand == 0x0000){
				power_off(state);
			}
			if (subcommand == 0x0001){
				power_on(state);
			}
			if (subcommand > 0x0001){
				//bad subcommand
			}

			send(buf, 12);
			break;
		}

		case 2:{//set temp
			temp = get_short(buf+6);
			prime_buf(buf);
			if (set_temp(state,temp) == 2){
				buf[6] = 1;
			}
			send(buf, 12);
			break;
		}

		case 3:{ //add sensor
			sensorID = get_short(buf+6);
			sensor_address = get_int(buf+8);
			coefficient = get_int(buf+12);
			unsigned int sensorTemp = get_int(buf+16);
			//check count < 10 buf[6] = 0x08, sensor_ID is unique/not in use buf[6] = 0x07, 
			ret = add_sensor(state, sensorID, sensor_address, coefficient, sensorTemp);
			prime_buf(buf);
			if (ret == 2){buf[6]=0x07;}
			if (ret == 3){buf[6]=0x08;}
			send(buf, 12);
			break;
		}

		case 4:{ //remove sensor
			sensorID = get_short(buf+6);
			ret = remove_sensor(state,sensorID);
			prime_buf(buf);
			if (ret == 1){buf[6]=0x06;}
			send(buf, 12);
			break;
		}

		case 5:{ //set smoke sensor
			subcommand = get_short(buf+6);
			prime_buf(buf);
			if (subcommand == 0x0000){
				smoke_off(state);
			}
			if (subcommand == 0x0001){
				smoke_on(state);
			}
			if (subcommand > 0x0001){
				//bad subcommand
				//no response
			}
			send(buf, 12);
			break;
		}

		case 6:{ //set program
			numSteps = get_short(buf+6);
			steps =  (pStep)(buf+8) ;
			ret = add_steps(state,numSteps,steps);
			prime_buf(buf);
			if (ret == 3){buf[6]=3;}
			if (ret == 2){buf[6]=2;}
			if (ret == 1){buf[6]=1;}
			send(buf, 12);
			break;
		}

		case 7:{//get program
			prime_buf(buf);
			unsigned int lenz = 0;
			unsigned int program[30];
			bzero(program,120);
			buf[4]=1;
			buf[6]=7;
			get_program(state, &lenz, program);
			lenz = lenz*3*sizeof(int);
			memcpy(buf+8,&lenz,sizeof(int));
			memcpy(buf+12,program,lenz);
			send(buf,lenz + 12);
			break;
		}

		case 8:{//get status
			prime_buf(buf);
			buf[4]=1;
			buf[6]=8;
			unsigned int status[6];
			int len = 24;
			ret = get_status(state,status);
			memcpy(buf+8,&len,sizeof(int));
			memcpy(buf+12,status,24); 
			send(buf,36);
			break;
		}

		case 9:{//simulate seconds
			seconds = get_short(buf+6);
			prime_buf(buf);
			unsigned int bufsize = 12;
			unsigned int histSize = 0;
			ret = simulate_seconds(state, seconds);
			unsigned int currentTime = state->currentTime;
			unsigned int setTemp = state->setTemp;
			if (ret == 0 ){
				buf[6] = 9;
				memcpy(buf+8, &currentTime ,sizeof(int));
				send(buf,12);
			}
			if(ret == 2){
				buf[4] = 1;
				buf[6] = 0xc;
				histSize = state->historyPosition*sizeof(int);
				unsigned int *pHistoryList = state->history;
				unsigned int historyListSize = state->historyPosition;
				unsigned int ambientTemp = state->ambientTemp;
				
				new_state(state);
				if (historyListSize > 0){
					memcpy(buf+8, &historyListSize, sizeof(historyListSize));
					memcpy(buf+12, pHistoryList, histSize);
					bufsize = histSize + 12;
				}
				memcpy(buf+bufsize, &ambientTemp, sizeof(unsigned int));
				bufsize+=4;
				memcpy(buf+bufsize, &setTemp, sizeof(unsigned int));
				bufsize+=4;
				send(buf, bufsize);
				//new_state(state);
			}

			break;
		}


		case 0xa:{ //validate firmware
			unsigned int fw = validate_fw(state);
			prime_buf(buf);
			buf[4]=1;
			buf[6]=0xa;
			buf[8]=4;
			memcpy(buf+12, &fw,sizeof(int) );
			send(buf, 16);
			break;
		}
		case 0xb:{//read sensor list
			prime_buf(buf);
			int len = 0;
			buf[4]=1;
			buf[6]=0xb;
			len = state->sensorCount * (sizeof(int)*4);
			//buff is filled with sensor bytes
			unsigned int sensorList[40*sizeof(int)];
			get_sensors(state,sensorList);
			memcpy(buf+8,&len,sizeof(int));
			memcpy(buf+12,sensorList,len);
			send(buf, len+12);
			break;
		}
		case 0xc:{//set ambient temp
			int ambientTemp = get_signed_int(buf+6);
			prime_buf(buf);
			if (set_ambient_temp(state,ambientTemp) == 2){
				buf[6] = 1;
			}
			send(buf, 12);
			break;
		}


		case 0xff:{
			//free(buf);
			exit_normal();

			break;
		}		

		default:{
			//bad command
			prime_buf(buf);
			buf[6]=5;
			send(buf,12);
			break;
		}


	}
	// free(buf);
	
	return 0;
}
