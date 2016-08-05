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

#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

extern "C"
{
	#include <libcgc.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include "string.h"
}
#include "cutil_list.h"
#include "common.h"
#include "sensor.h"
#include "user.h"

#define RET_USER_ADDED 0
#define RET_USER_REDUNDANT 1
#define RET_USER_FULL 2

#define MAX_SENSORS_PER_USER 3
#define MAX_USERS 7

class SensorManager
{
private:
	CUtil::DLL_LIST( FitnessSensor, m_sensorLink ) m_sensorList;

	uint16_t m_currentUser;
	CUtil::DLL_LIST( User, m_userLink ) m_userList;
	
	//
	// Is this a proper fitness sensor?
	//
	bool Validate ( FitnessSensor );

public:
	SensorManager() {}
	~SensorManager();

	// SENSOR management
	int AddSensor( FitnessSensor *sensor );
	FitnessSensor* GetSensor( uint16_t id );

	bool RemoveSensor( uint16_t id, uint16_t user );
	bool VerifySensor( uint16_t id );
	void PrintSensors(); // TEST ONLY
	uint8_t *ListSensors( uint16_t &len );
	bool ListHwIds( uint16_t &len, uint8_t* buff );


	// USER management
	uint16_t GetCurrentUser() { return m_currentUser; }
	uint8_t SetCurrentUser( uint16_t user );
	uint8_t AddUser( User* new_user );

	bool AddDistance( uint16_t new_dist, uint16_t user );
};

#endif