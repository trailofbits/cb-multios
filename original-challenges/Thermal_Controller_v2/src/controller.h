/*

Author: James Nuttall <james@cromulence.com>

Copyright (c) 2016 Cromulence LLC

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

#ifndef CONTROLLER_H
#define CONTROLLER_H

extern "C"
{
	#include <libcgc.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <prng.h>
}
#include "cutil_list.h" // custom linked list
#include "cutil_string.h"
#include "common.h"
#include "sensor.h"
#include "comms.h"

#define BAD_SENSOR 6

#define MAX_PROGRAM_STEPS 10

#define VERSION 0x10a

#define MAX_SENSORS 10

#define AMBIENT_TEMP 75

class ControllerProgram
{
private:
	int32_t m_step_type;
	int32_t m_sensor_id;
	int32_t m_set_temp;
	int32_t m_duration;

public:
	int32_t getStepType() { return m_step_type; }
	int32_t getSensorId() { return m_sensor_id; }
	int32_t getSetTemp() { return m_set_temp; }
	int32_t getDuration() { return m_duration; }

	void setStepType( int32_t val ) { m_step_type = val; }
	void setSensorId( int32_t val ) { m_sensor_id = val; }
	void setSetTemp( int32_t val ) { m_set_temp = val; }
	void setDuration( int32_t val ) { m_duration = val; }
};

class Controller
{
private:
	// Sensor list vars
	CUtil::DLL_LIST( Sensor, m_sensorLink ) m_sensor_list; // use this doubly linked list
	
	uint16_t m_current_sensor_count;

	// Controller vars
	
	int32_t m_currentProgramStep;
	bool m_powerOn;
	bool m_heaterOn;
	double m_currentTemp;
	int32_t m_version;
	int32_t m_set_temp;
	bool m_smokeSensorPresent;

	Sensor m_smokeSensor;

	OutgoingMessage msg_out;
	IncomingMessage msg_in;


public:
	Controller();
	~Controller();



	OutgoingMessage* GetMsgOut() { return &msg_out; }
	IncomingMessage* GetMsgIn() { return &msg_in; }

	// Programs
	ControllerProgram m_controllerProgram[10];
	ControllerProgram m_controllerProgramBackup[10];

	void RevertProgram();
	void BackupProgram();
	void ClearBackupProgram();
	void ClearProgram();
	void PrintPrograms(); // test only

	// GET / SET
	double getCurrentTemp() { return m_currentTemp; }
	void setCurrentTemp( double val ) { m_currentTemp = val; }

	int32_t getCurrentProgramStep() { return m_currentProgramStep; }
	void setCurrentProgramStep( int32_t val ) { m_currentProgramStep = val; }
	
	bool getPowerOn() { return m_powerOn; }
	void setPowerOn( bool val );
	
	bool getHeaterOn() { return m_heaterOn; }
	void setHeaterOn( bool val ) { m_heaterOn = val; }

	int32_t getSetTemp() { return m_set_temp; }
	bool setSetTemp( int32_t val );


	// Sensors
	bool AddSensor( Sensor* );
	bool IsSensorInList ( uint16_t id );
	bool RemoveSensor( uint16_t sensor_id );
	uint16_t GetSensorCount();
	bool SetSensor( uint16_t sensor_type, bool val );

	void PrintSensorList();

	uint16_t GetVersion() { return m_version; }

	// firmware
	//  get?
	//  validate
	bool ValidateFirmware();


	// Smoke sensor
	bool IsSmokeSensorEnabled() { return m_smokeSensor.GetEnabled(); }
	void EnableSmokeSensor() { m_smokeSensor.SetEnabled( true ); }
	void DisableSmokeSensor() { m_smokeSensor.SetEnabled( false ); }

	//
	// Send a response back with the following code
	//
	void SendBasicResponse( CUtil::String code );
	void SendExtendedResponse( uint16_t code, CUtil::String desc );
};



#endif