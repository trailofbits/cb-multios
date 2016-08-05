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

#ifndef service_h
#define service_h
#define TRUE 1
#define FALSE 0
#define ON 1
#define OFF 0
#define MAX_SENSOR	10
#define HISTSIZE 400




typedef struct Sensor_s{
	struct Sensor_s *prev;
	struct Sensor_s *next;
	unsigned short sensorID;
	unsigned int sensorAddr;
	unsigned int sensorCoef;
	double sensorTemp;

} sSensor, *pSensor;

typedef struct Step_s{
	unsigned int type;
	union {
		unsigned int sensorID;
		unsigned int timeVal;
	};
	unsigned int temp;	
} sStep, *pStep;

typedef struct Program_s{
	struct Program_s *prev;
	struct Program_s *next;
	sStep step;
} sProgram, *pProgram;

typedef struct State_s {
	unsigned int smoke;
	unsigned int power;
	unsigned int history[HISTSIZE];
	double currentTemp;
	unsigned int setTemp;
	unsigned int sensorCount;
	pSensor sensorList;
	short int numSteps;
	unsigned int heater;
	unsigned int ambientTemp;
	signed short currentStep;
	unsigned int currentTime;
	unsigned int historyPosition;
	unsigned char finished;
	pProgram programList;
} sState, *pState;



pState init_state();
void new_state(pState state);
int power_on(pState state);
int power_off(pState state);
int smoke_on(pState state);
int smoke_off(pState state);
int set_ambient_temp(pState, int ambientTemp );
int set_temp(pState state, unsigned short int temp);
int add_sensor(pState state, unsigned short int sensorID, unsigned int sensorAddr, unsigned int coeff, unsigned int sensorTemp);
pSensor find_sensor(pState state, unsigned short int sensorID);
int remove_sensor(pState state, unsigned short int sensorID);
void free_program(pState state);
int add_steps(pState state, unsigned int numSteps, pStep steps );
int add_step(pState state, unsigned int type, unsigned int val, unsigned int temp);
unsigned int get_program(pState state, unsigned int *size, unsigned int *buf);
unsigned int get_status(pState state,unsigned int *);
void get_sensors(pState state,unsigned int *);
void update_sensors(pState state);
void reset_sensors(pState state);
pProgram get_step(pState state, int step);
void check_program(pState state);
void add_history(pState state);
int simulate_seconds(pState state, int seconds);

unsigned int validate_fw(pState state);
int check_val(unsigned char *buf,unsigned short size);
int exit_normal();
#endif
