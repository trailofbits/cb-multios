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

#ifndef FITNESS_SENSOR_H
#define FITNESS_SENSOR_H

#include "cutil_list.h" // custom linked list

#define INVALID_SENSOR_TYPE 0xff

// index values into the m_sensorArray... not used directly as values
enum
{
	HEART = 0,
	STEP,
	SCALE,
	RUN,
	BIKE,
	MAX_SENSOR_VALUE

} ValidSensorTypes;

typedef struct
{
	uint8_t Type;
	uint8_t Val_1;
	uint8_t Val_2;
	uint8_t Val_3;
} SensorMacFormat;

class FitnessSensor
{

private:
	uint16_t m_sensorID;
	uint8_t m_sensorType; // pulled from MAC
	SensorMacFormat m_sensorMAC;
	uint8_t *data;
	bool m_invalid;

	uint16_t m_owner; // user this sensor is registered for


public:
	FitnessSensor() {}
	FitnessSensor( uint16_t, uint32_t, uint8_t *, uint32_t);

	uint16_t GetID() { return m_sensorID; }
	SensorMacFormat GetMAC() { return m_sensorMAC; }
	uint32_t GetMacAsInt();
	uint8_t GetType() { return m_sensorType; }

	void SetID(uint16_t id) { m_sensorID = id; }
	bool SetMAC(uint32_t mac);

	bool IsInvalid() { return m_invalid; }

	uint8_t SetUser( uint16_t user );
	uint16_t GetUser() { return m_owner; }

	uint8_t *GetData() { return data; }

	static uint8_t m_sensorArray[ MAX_SENSOR_VALUE ];
	static bool GenerateTypeValues();
	static bool GetSensorTypeValue( uint8_t lookup, uint8_t &val );

	static uint16_t HandleBikeSensor( uint16_t );
	static uint16_t HandleHeartSensor( uint16_t );
	static uint16_t HandleScaleSensor( uint16_t );
	static uint16_t HandleStepSensor( uint16_t );
	static uint16_t HandleRunSensor( uint16_t );

	
	// Test only
	void Print();

	// used for linked list in SensorManager
	CUtil::DLL_LINK( FitnessSensor ) m_sensorLink; 
};

#endif