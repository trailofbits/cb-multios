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

#include "controller.h"

//#define RESPONSE_HEADER "5AA5"
#define VERSION 0x10a
#define BASIC_RESPONSE "00"
#define BASIC_RESPONSE_CODE "00"
#define EXTENDED_RESPONSE "01"

#define ON 1
#define OFF 0



Controller::Controller() 
{
	m_current_sensor_count = 0;
	m_version = VERSION;
	m_currentProgramStep = -1;
	m_powerOn = false;
	m_heaterOn = false;
	m_currentTemp = AMBIENT_TEMP;
	m_set_temp = 0;
	m_smokeSensorPresent = false;

	ClearBackupProgram();
	ClearProgram();
}

Controller::~Controller() 
{
	m_sensor_list.DeleteAll();
}

//
// Add a sensor to the sensor list
//
bool Controller::AddSensor( Sensor *s ) 
{
	// already full?
	if ( m_current_sensor_count >= 10 )
		return false; 

	m_sensor_list.AddLast( s );

	m_current_sensor_count += 1;

	return true;
}

bool Controller::SetSensor( uint16_t sensor_type, bool val )
{
	for ( Sensor *pCur = m_sensor_list.GetFirst(); pCur; pCur = m_sensor_list.GetNext( pCur ) )
	{
		if ( pCur->GetType() == sensor_type )
		{
			pCur->SetEnabled( ( bool )val );

			return true;
		}
	}
	return false;
}

//
// Remove a sensor to the sensor list
//
bool Controller::RemoveSensor( uint16_t id )
{
	for ( Sensor *pCur = m_sensor_list.GetFirst(); pCur; pCur = m_sensor_list.GetNext( pCur ) )
	{
		if ( pCur->GetType() == id )
		{
			delete pCur;

			m_current_sensor_count -= 1;
			
			return true;
		}
	}
	return false;
}

uint16_t Controller::GetSensorCount()
{
	return m_current_sensor_count;
}

void Controller::PrintSensorList()
{
	printf( "sl:");
	for ( Sensor *pCur = m_sensor_list.GetFirst(); pCur; pCur = m_sensor_list.GetNext( pCur ) )
	{
		printf( "$d ", pCur->GetType() );
	}
	printf("\n");
}

//
// Set power to on or off
// When system is turned off, heater turns off and programmer resets
//
void Controller::setPowerOn( bool val )
{
	m_powerOn = val;
	if ( val == false )
	{
		m_heaterOn = false;
		m_currentProgramStep = -1;
	}
}

//
// Set temperature, as long is it's in valid range (175 - 350)
//
bool Controller::setSetTemp( int32_t val )
{
	if ( val > 350 || val < 175 )
		return false;
	else
		m_set_temp = val;

	return true;
}

// TODO: search list and return true if found
bool Controller::IsSensorInList( uint16_t id )
{
	for ( Sensor *pCur = m_sensor_list.GetFirst(); pCur; pCur = m_sensor_list.GetNext( pCur ) )
	{
		if ( pCur->GetType() == id )
		{
			return true;
		}
	}
	return false;
}

//
// Back up current program to temp storage
//
void Controller::BackupProgram()
{
	for ( int i = 0; i < 10; i++ )
	{
		m_controllerProgramBackup[i] = m_controllerProgram[i];
	}
}

//
// Overwite current programs with backup
//
void Controller::RevertProgram()
{
	for ( int i = 0; i < 10; i++ )
	{
		m_controllerProgram[i] = m_controllerProgramBackup[i];
	}
}

void Controller::ClearBackupProgram()
{
	for ( int i = 0; i < 10; i++ )
	{
		m_controllerProgramBackup[i].setStepType( 0 );
		m_controllerProgramBackup[i].setSensorId( 0 );
		m_controllerProgramBackup[i].setSetTemp( 0 );
		m_controllerProgramBackup[i].setDuration( 0 );
	}
}

void Controller::ClearProgram()
{
	for ( int i = 0; i < 10; i++ )
	{
		m_controllerProgram[i].setStepType( 0 );
		m_controllerProgram[i].setSensorId( 0 );
		m_controllerProgram[i].setSetTemp( 0 );
		m_controllerProgram[i].setDuration( 0 );
	}
}

// test only
void Controller::PrintPrograms()
{
	for ( int i = 0; i < 10; i++ )
	{
		printf("Program: $x $x $x $x\n", m_controllerProgram[i].getStepType(), m_controllerProgram[i].getSensorId(), m_controllerProgram[i].getSetTemp(), m_controllerProgram[i].getDuration() );
	}
}