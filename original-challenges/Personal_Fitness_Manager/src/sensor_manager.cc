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

#include "sensor_manager.h"


SensorManager::~SensorManager() 
{
	m_userList.DeleteAll();
	m_userList.DeleteAll();
}

void SensorManager::PrintSensors()
{
	printf( "  print sensors for user: $x\n", m_currentUser );
	for ( FitnessSensor *pCur = m_sensorList.GetFirst(); pCur; pCur = m_sensorList.GetNext( pCur ) )
	{
		pCur->Print();
	}
	printf("\n");
}

uint8_t *SensorManager::ListSensors( uint16_t &buffer_len)
{
	buffer_len = 0;
				
// each sensor is 2b ID, 4b mac: 6B
	uint8_t data[ 6 * MAX_SENSORS_PER_USER * MAX_USERS ];
	bzero( data, 6 * MAX_SENSORS_PER_USER * MAX_USERS );

	uint8_t *buff = (uint8_t *)&data;

	int count_users = 0;
	
	// for each user, list the first MAX_SENSORS_PER_USER
	for ( User *pUser = m_userList.GetFirst(); pUser; pUser = m_userList.GetNext( pUser ) )
	{
#ifdef PATCHED_1
		if ( count_users >= MAX_USERS )
			break;
#endif
		count_users++;

		int count_per_user = 0;
		for ( FitnessSensor *pSensor = m_sensorList.GetFirst(); pSensor; pSensor = m_sensorList.GetNext( pSensor ) )
		{

			if ( pSensor->GetUser() == pUser->GetId() )
			{

				if ( count_per_user >= MAX_SENSORS_PER_USER )
					break;

				count_per_user++;
				uint16_t id = pSensor->GetID();
				uint32_t mac = pSensor->GetMacAsInt();
				memcpy( &buff[buffer_len], &id, sizeof( uint16_t ) );

				buffer_len += sizeof( uint16_t );
				memcpy( &buff[buffer_len], &mac, sizeof( uint32_t ) );
				buffer_len += sizeof( uint32_t );

				if (pSensor->GetType() == BIKE)
				{
					uint8_t *data = pSensor->GetData();

					if (data)
					{
						uint32_t len = strlen((char *)data);
#ifdef PATCHED_1		
						if ( buffer_len < ( 6 * MAX_SENSORS_PER_USER * MAX_USERS - len + 1) )
						{
							memcpy(&buff[buffer_len], data, len);
							buffer_len += len;
						}
#else
						memcpy(&buff[buffer_len], data, len);

						return NULL;
#endif
					}
				}
			}
		}
	}
	uint8_t *rbuf = new uint8_t[buffer_len];
	memcpy(rbuf, data, buffer_len);
	return rbuf;
}

bool SensorManager::ListHwIds( uint16_t &buffer_len, uint8_t* buff )
{
	buffer_len = 0;
	for ( int i = 0; i < MAX_SENSOR_VALUE; i ++ )
	{
		buff[i] = FitnessSensor::m_sensorArray[i];
		buffer_len++;
	}
	return true;
}

bool MacsAreSame( SensorMacFormat a, SensorMacFormat b )
{
	if ( a.Type == b.Type &&
		 a.Val_1 == b.Val_1 && 
		 a.Val_2 == b.Val_2 && 
		 a.Val_3 == b.Val_3)
		return true;
	return false;
}

//
// Returns pointer to sensor if ID matches AND this is a sensor for the current user
//
FitnessSensor* SensorManager::GetSensor( uint16_t id )
{
	// given the sensor id, return a pointer to the sensor
	for ( FitnessSensor *pCur = m_sensorList.GetFirst(); pCur; pCur = m_sensorList.GetNext( pCur ) )
	{
		if ( pCur->GetID() == id && pCur->GetUser() == m_currentUser )
		{
			return pCur;
		}
	}
	return NULL;
}



//
// Add this sensor to the list under the current user's name
//
int SensorManager::AddSensor( FitnessSensor *sensor )
{
	// Check if this sensor's ID is already in the list for this user
	for ( FitnessSensor *pCur = m_sensorList.GetFirst(); pCur; pCur = m_sensorList.GetNext( pCur ) )
	{
		if ( pCur->GetUser() == sensor->GetUser() && MacsAreSame( sensor->GetMAC(), pCur->GetMAC() ) )
		{
			// this sensor ID is already in the sensor list, don't add it again
			return 1;
		}
		if ( pCur->GetUser() == sensor->GetUser() && sensor->GetID() == pCur->GetID() )
		{
			// this sensor ID is already in the sensor list, don't add it again
			return 1;
		}
	}

	int count = 0;
	for ( FitnessSensor *pCur = m_sensorList.GetFirst(); pCur; pCur = m_sensorList.GetNext( pCur ) )
	{
		if ( pCur->GetUser() == sensor->GetUser() )
		{
			count += 1;
		}
	}

	// check if we're already maxed out on sensors for this user
	if ( count >= MAX_SENSORS_PER_USER )
	{
		return 2;
	}

	m_sensorList.AddLast( sensor );
	return 0;
}

//
// Remove a sensor from the sensor list
//
bool SensorManager::RemoveSensor( uint16_t id, uint16_t user )
{
	for ( FitnessSensor *pCur = m_sensorList.GetFirst(); pCur; pCur = m_sensorList.GetNext( pCur ) )
	{
		if ( pCur->GetID() == id && pCur->GetUser() == user )
		{
			delete pCur;
			return true;
		}
	}
	return false;
}

//
// Set the current user to the given user_id
// If user_id isn't in the list, add them
// Return 0 is success (current user is set)
// Return RET_USER_FULL if this new user couldn't be added
//
uint8_t SensorManager::SetCurrentUser( uint16_t user_id )
{
	if ( user_id == INVALID_USER )
	{
		m_currentUser = INVALID_USER;
		return 0;
	}

	for ( User *pCur = m_userList.GetFirst(); pCur; pCur = m_userList.GetNext( pCur ) )
	{
		if ( pCur->GetId() == user_id )
		{
			m_currentUser = user_id;
			return 0;
		}
	}

	return -1;
}

//
// Return 0 if this user_id is added
// Return 1 if this user_id is already in the list
// Return 2 if add failed (too many users)
//
uint8_t SensorManager::AddUser( User* new_user )
{
	int count = 0;
	// Is this user already in the list?
	for ( User *pCur = m_userList.GetFirst(); pCur; pCur = m_userList.GetNext( pCur ) )
	{
		count++;
		if ( pCur->GetId() == new_user->GetId() )
		{
			return RET_USER_REDUNDANT;
		}
	}
	// If user list is full, return error
	if ( count >= MAX_USERS )
		return RET_USER_FULL;

	// Add user to list
	m_userList.AddLast( new_user );

	return RET_USER_ADDED;
}

//
// Return true if this id is registered with the current user
//
bool SensorManager::VerifySensor( uint16_t id )
{
	for ( FitnessSensor *pCur = m_sensorList.GetFirst(); pCur; pCur = m_sensorList.GetNext( pCur ) )
	{
		if ( pCur->GetID() == id && pCur->GetUser() == this->m_currentUser )
		{
			return true;
		}
	}
	return false;
}

//
// Add new distance to a user's total distance
//
bool SensorManager::AddDistance( uint16_t new_dist, uint16_t user )
{
	User *thisUser;
	for ( thisUser = m_userList.GetFirst(); thisUser; thisUser = m_userList.GetNext( thisUser ) )
	{
		if ( thisUser->GetId() == user )
		{
			goto found;
		}
	}
	return false;

found:
	thisUser->AddTotalDistance( new_dist );

	return true;
} 



