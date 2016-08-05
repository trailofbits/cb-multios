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
#include "service.h"
#include "ui.h"

int main(){
	ui_main();
	return 0;
}

pState init_state(){
	pState state = malloc (sizeof(sState));
	bzero(state,sizeof(sState));
	//initialize
	state->currentTemp = 75;
	state->sensorCount = 0;
	state->setTemp = 175;
	state->power = OFF;
	state->heater = OFF;
	state->currentStep = -1;
	state->smoke = OFF;
	state->ambientTemp = 75;
	bzero(state->history, sizeof(unsigned short int) * HISTSIZE);
	state->historyPosition = 0;
	state->finished = FALSE;
	state->currentTime = 0;
	return state;
}


//frees old state and inits a new state
void new_state(pState state){
	free_program(state);
	state->currentTemp = 75;
	state->setTemp = 175;
	state->power = OFF;
	state->heater = OFF;
	state->currentStep = -1;
	state->smoke = OFF;
	state->ambientTemp = 75;
	// bzero(state->history, sizeof(unsigned short int) * HISTSIZE);
	state->historyPosition = 0;
	state->finished = FALSE;
	state->currentTime = 0;
	reset_sensors(state);
	return;
}


int power_on(pState state){
	if (state == NULL){return 1;}	
//	if (state->power == ON){return 2;}
	state->power = ON;
	return 0;
}

int power_off(pState state){
	if (state == NULL){return 1;}	
//	if (state->power == OFF){return 2;}
	new_state(state);
	return 0;
}

int smoke_on(pState state){
	if (state == NULL){return 1;}	
	if (state->smoke == ON){return 2;}
	state->smoke = ON;
	return 0;
}

int smoke_off(pState state){
	if (state == NULL){return 1;}	
	if (state->smoke == OFF){return 2;}
	state->smoke = OFF;
	return 0;
}

int set_ambient_temp(pState state, int temp){
	if (state == NULL){return 1;}
	if ( temp > 175 ){return 2;}
	state->ambientTemp = temp;
	return 0;
}

int set_temp(pState state, unsigned short int temp){
	if (state == NULL){return 1;}
	if (  ( temp < 175 ) || ( temp > 350 )  ){return 2;}
	state->setTemp = temp;
	return 0;
}

int add_sensor(pState state, unsigned short int sensorID, unsigned int sensorAddr, unsigned int coeff, unsigned int sensorTemp){
	if (state == NULL){return 1;}
	if (find_sensor(state, sensorID) != NULL){
		return 2;
	}//sensorID exists already}
	if (state->sensorCount > (MAX_SENSOR-1)){
		return 3;
	}//max sensor count
	pSensor tempSensor = state->sensorList;
	pSensor thisSensor = state->sensorList;

	if (tempSensor == NULL){//no sensors
		thisSensor = malloc(sizeof(sSensor));
		state->sensorList = thisSensor;//set list head
		thisSensor->prev = NULL;//prev of list head is null

	} else {//walk to the end of the list

		while (tempSensor != NULL){
			thisSensor = tempSensor;
			tempSensor = tempSensor->next;
		}//write next and prev, then set thisSensor

		thisSensor->next = malloc(sizeof(sSensor));
		thisSensor->next->prev =  thisSensor;
		thisSensor = thisSensor->next;
	}
	thisSensor->next = NULL;
	thisSensor->sensorTemp = (double) state->ambientTemp;
	thisSensor->sensorID = sensorID;
	thisSensor->sensorAddr = sensorAddr;
	thisSensor->sensorCoef = coeff;
	state->sensorCount = state->sensorCount + 1;
	return 0;
}

pSensor find_sensor(pState state, unsigned short sensorID){
	//return pointer to sensor with ID or 0;
	if (state == NULL){return NULL;}	//no state
	if (state->sensorList == NULL){
		return NULL;
	}//no sensors in list
	pSensor tempSensor = state->sensorList;
	pSensor thisSensor = state->sensorList;
	while ( (tempSensor != NULL) && (thisSensor->sensorID != sensorID) ){
		thisSensor = tempSensor;
		tempSensor = tempSensor->next;
	}
	//thisSensor is now last or match
	if (thisSensor->sensorID != sensorID){
		return NULL;
	}//sensorID not found	
	return thisSensor;
}

//reminder if sensor count is decremented on an empty remove, list can grow too large
int remove_sensor(pState state, unsigned short sensorID){
	pSensor thisSensor = find_sensor(state, sensorID);

	if (thisSensor == NULL){
		return 1;
	}//sensorID not found

	if (thisSensor->prev == NULL){//first element
		state->sensorList = thisSensor->next;//point head to next if necessary
	}
	if (thisSensor->next != NULL){//if there is a next, fix its prev
		thisSensor->next->prev = thisSensor->prev;
	}	
	if (thisSensor->prev != NULL){//if there is a prev, fix its next
		thisSensor->prev->next = thisSensor->next;
	}
	state->sensorCount = state->sensorCount - 1;
	free(thisSensor);

	return 0;
}

void free_program(pState state){
	//free each program node in programList
	if (state->programList == NULL){
		return;
	}
	pProgram nextProgram = state->programList;
	pProgram thisProgram = NULL;
	while (nextProgram != NULL){
		thisProgram = nextProgram;
		nextProgram = nextProgram->next;
		free(thisProgram);
	}
	state->programList = NULL;
	state->numSteps = 0;
	return;
}

int add_steps(pState state, unsigned int numSteps, pStep steps ){
	//steps is pointer to the program buf 


	if (numSteps>10){									
		return 5;
	}
	//each step for numSteps must be read, checked and added to pstate->programList
	for (unsigned int i=0;i<numSteps;i++){
		// int allows bad type that isn't checked for valid timeval, allowing the
		// program to run for indeterminated time, which writes off the end of history buffer
#ifdef PATCHED_1
		unsigned short int type = steps[i].type;
#else
		short int type = (short int)steps[i].type;
#endif

		unsigned int sensorID = steps[i].sensorID;
		unsigned int timeVal = steps[i].timeVal;
		unsigned int temp = steps[i].temp;
		//type and sensorID/timeval check
		if (type == 0 ){
			 //sensorID check

			if (sensorID > 12){
				return 3;
			}
			if (  (temp < 175 ) || (temp > 350)  ){
				return 1;	
			}
		}
		if ( type == 1 ){
			//timeval check
			if (  ( timeVal < (30*60) ) || ( timeVal > (240*60) )  ){
				return 2;
			}
			if (  (temp < 175 ) || (temp > 350)  ){
				return 1;
			}
		}
		if (type > 1 ){
			//bad type
			return 4;
		}
	}

	//if all is ok, add steps
	new_state(state);
	for (unsigned int i=0;i<numSteps;i++){
		unsigned int type = steps[i].type;
		unsigned int sensorID = steps[i].sensorID;
		unsigned int timeVal = steps[i].timeVal;
		unsigned int temp = steps[i].temp;
		int retval = add_step(state, type, sensorID, temp);
	}
	state->currentStep = 0;
	state->numSteps = numSteps;
	return 0;
}	

//adds a step to a program, return NULL if error
int add_step(pState state, unsigned int type, unsigned int val, unsigned int temp){//val is sensorID or timeval
	pProgram program = state->programList;
	pProgram tempProgram = program;
	if (program == NULL ){
		program = malloc(sizeof(sProgram));
		bzero(program,sizeof(sProgram));
		program->prev = NULL;
		state->programList = program;
	} else {
		while(tempProgram != NULL){
			program = tempProgram;
			tempProgram = tempProgram->next;
		}//go to end of list
		program->next = malloc(sizeof(sProgram));
		bzero(program->next,sizeof(sProgram));
		program = program->next;
	}
	program->next = NULL;
	program->step.type = type;
	if (type==0){//sensorID
		program->step.sensorID = val;
	} else {
		program->step.timeVal = val;
	}
	program->step.temp = temp;
	return 0;
} 


unsigned int get_program(pState state,unsigned int *size, unsigned int buf[30]){
	if (state == NULL){
		return 1;
	}
	if (state->programList == NULL){
		return 1;
	}	
	pProgram program = state->programList;

	unsigned int len = 0;
	while(program != NULL){
		buf[(len*3)+0] = program->step.type;
		buf[(len*3)+1] = program->step.sensorID;
		buf[(len*3)+2] = program->step.temp;
		len = len +1;
		program = program->next;
	}
	*size = len;
	return 0;
}

unsigned int get_status(pState state,unsigned int status[6]){
	if (state == NULL){
		return 1;
	}	
	//set temp, current temp, power on, heater on, smoke sensor present
	status[0] = (unsigned int)0x10a;
	status[1] = (unsigned int)state->setTemp;
	status[2] = (unsigned int)state->currentTemp;
	status[3] = (unsigned int)state->power;
	status[4] = (unsigned int)state->heater;
	status[5] = (unsigned int)state->smoke;		
	return 0;
}

void get_sensors(pState state,unsigned int sensors[40*sizeof(int)]){
	pSensor tempSensor = state->sensorList;
	unsigned int sensorCount = state->sensorCount;
	unsigned int i=0;
	unsigned int temp[40*sizeof(int)];
	while (tempSensor != NULL){
		temp[(i*4)+0] = (unsigned int)tempSensor->sensorID;
		temp[(i*4)+1] = (unsigned int)tempSensor->sensorAddr;
		temp[(i*4)+2] = (unsigned int)tempSensor->sensorCoef;
		temp[(i*4)+3] = (unsigned int)tempSensor->sensorTemp;
		tempSensor = tempSensor->next;
		i = i + 1;
	}
	memcpy(sensors,temp,(i*sizeof(int)*4));
}


void update_sensors(pState state){
	//for each sensor in sensorlist write sensor.currentTemp = (state.currentTemp - sensor.currentTemp) * (0.5 + (sensor.coeff/20000))
	pSensor tempSensor = state->sensorList;
	while (tempSensor != NULL){
		//sensor coeff of 10000 means sensor is not places in food
		double factor = (double)0.5 + (double)tempSensor->sensorCoef/(double)20000;
		double base = (double)state->currentTemp - (double)tempSensor->sensorTemp;
		double adjustment = ((double)base * (double)factor); 
		tempSensor->sensorTemp = (double)tempSensor->sensorTemp + (double)adjustment;
		tempSensor = tempSensor->next;
	}
	return;
}

void reset_sensors(pState state){
	pSensor tempSensor = state->sensorList;
	while (tempSensor != NULL){
		tempSensor->sensorTemp = state->ambientTemp;
		tempSensor = tempSensor->next;
	}
	return;

}

pProgram get_step(pState state, int step){
	pProgram thisStep = state->programList;
	for (int i=0;i<step;i++){
		if (thisStep == NULL){
			break;
		}
		thisStep = thisStep->next;
	}
	return thisStep;
}

void check_program(pState state){

	pProgram thisStep = get_step(state, state->currentStep);
	if (thisStep == NULL){
		state->finished = TRUE;
		return; 
	}
	if (thisStep->step.type == 0){
		pSensor thisSensor = find_sensor(state, thisStep->step.sensorID);
		//if no sensor corresponds to sensorID, go to next step
		if (thisSensor == NULL){
			state->currentStep = state->currentStep + 1;
			return;
		}
		//check temp, if sensortemp+5 > current temp, set net temp and go next step
		if (  ( (unsigned int) thisSensor->sensorTemp + 5 ) > (unsigned int) state->setTemp){
			//might need to break this.
			state->setTemp = thisStep->step.temp;
			state->currentStep = state->currentStep + 1;
			return;
		}
	} else {
		//if time passes trigger, set new temp and go to next step
		if ((unsigned int)state->currentTime > (unsigned int)thisStep->step.timeVal){
			state->setTemp = thisStep->step.temp;
			state->currentStep = state->currentStep + 1;
			return;
		}
	}
	return;
}

void add_history(pState state){
	state->history[state->historyPosition] = (unsigned int) state->currentTemp;
	state->historyPosition = state->historyPosition + 1;
}

int simulate_seconds(pState state, int seconds){
	if (state == NULL){
		return 1;
	}	
	if (  (seconds < 10 ) || (seconds > 8000)  ){
		return 1;
	}
	for (int i=0;i<seconds;++i){
		if (state->power == ON){
			if (state->heater == ON){
				state->currentTemp = (double)state->currentTemp + 1;
				if ((double)state->currentTemp > ((double)state->setTemp + 5) ){
					state->heater = OFF;
				}
			} else {
				if ((double)state->currentTemp > (double)state->ambientTemp){

					state->currentTemp = ((double)state->currentTemp - 0.25);
				}
				if (state->currentTemp < ((double)state->setTemp - 5)){
					state->heater = ON;
				}
			}
		}else {
			if (state->currentTemp > (double)state->ambientTemp){
				state->currentTemp = (double)state->currentTemp - 0.25;
			}
		}
		update_sensors(state);
//		only run program if there is a program.
		if (state->currentStep > -1){		
			check_program(state);
			if (state->finished){
				return 2;		
			}			
		}
		if (state->currentTime%60 == 0){
			add_history(state);
		}

		state->currentTime = state->currentTime + 1;
	}

	//end simulate seconds
	return 0;
}

unsigned int validate_fw(pState state){
	if (state == NULL){
		return 1;
	}	
	int MagicPageSize = 4096;
	unsigned char *magicpage = (unsigned char *)0x4347C000;
	unsigned int tempval = 0;
	for (unsigned short i=0;i<MagicPageSize;++i){
		tempval = (tempval + ( magicpage[i] * (i+1))) ;	
	}
	return tempval;		
	return check_val(magicpage,MagicPageSize);
}

int check_val(unsigned char *buf,unsigned short size){

	unsigned int tempval = 0;
	for (unsigned short i=0;i<size;++i){
		tempval = (tempval + ( buf[i] * (i+1))) ;	
	}
	return tempval;
}

int exit_normal(){

	_terminate(0);
}
