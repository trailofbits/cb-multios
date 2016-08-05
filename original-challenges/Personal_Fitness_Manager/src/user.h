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
#ifndef __USER_H__
#define __USER_H__

#include "cutil_list.h"

#define BLOOD_PRESSURE_MIN 20
#define BLOOD_PRESSURE_MAX 150

#define INVALID_USER 0xff

enum
{
	ID = 0,
	WEIGHT,
	HEIGHT,
	AGE,
	BODYFAT,
	BLOODPRESSURE,
	SEX
} USER_FIELD_TYPES;

class User
{
private:
	uint16_t m_id;   // KEY. unique
	uint16_t m_weight; // kg
	uint16_t m_height; // cm	
	uint16_t m_age;    // years
	uint16_t m_bodyFat; // percentage 0 - 100
	uint16_t m_bloodPressure;
	uint32_t m_totalDist;

	
public:
	User( uint16_t id );

	void SetId( uint16_t id ) { m_id = id; }
	uint16_t GetId() { return m_id; }

	void SetWeight( uint16_t w ) { m_weight = w; }
	uint16_t GetWeight() { return m_weight; }

	void SetHeight( uint16_t h ) { m_height = h; }
	uint16_t GetHeight() { return m_height; }

	void SetAge( uint16_t a ) { m_age = a; }
	uint16_t GetAge() { return m_age; }

	void AddTotalDistance( uint16_t new_dist ) { m_totalDist += new_dist; }
	uint16_t GetTotalDistance() { return m_totalDist; }

	bool SetBodyFat( uint16_t bf );
	uint16_t GetBodyFat() { return m_bodyFat; }

	bool SetBloodPressure( uint16_t bp );
	uint16_t GetBloodPressure() { return m_bloodPressure; }

	// used for linked list in SensorManager
	CUtil::DLL_LINK( User ) m_userLink;
};

#endif