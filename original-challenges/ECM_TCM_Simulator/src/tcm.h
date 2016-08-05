/*

Author: Jason Williams <jdw@cromulence.com>

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
#ifndef __TCM_H__
#define __TCM_H__

#include "simulation.h"
#include "lanbus.h"
#include "response.h"

class CTCM : public CSimulationComponent
{
public:
	const static uint8_t ECM_LANBUS_ID = 0x13;
	const static uint8_t TCM_LANBUS_ID = 0x14;

	const static uint8_t READ_DATA_TYPE = 0x1;
	const static uint8_t SET_DATA_TYPE = 0x2;
	const static uint8_t ACTION_DATA_TYPE = 0x3;
	const static uint8_t CHECK_EQUIPMENT_TYPE = 0x4;

	const static uint8_t READ_RESPONSE_TYPE = 0x1;
	const static uint8_t SET_RESPONSE_TYPE = 0x2;
	const static uint8_t ACTION_RESPONSE_TYPE = 0x3;
	const static uint8_t CHECK_RESPONSE_TYPE = 0x4;
	const static uint8_t FAILURE_RESPONSE_TYPE = 0x5;

	const static uint8_t READ_WHEELSPEED_COMMAND = 0x1;
	const static uint8_t READ_INVALID_COMMAND = 0xFF;

	const static uint8_t SET_WHEELSPEED_COMMAND = 0x1;
	const static uint8_t SET_INVALID_COMMAND = 0xFF;

	const static uint8_t TC_ON_COMMAND = 0x1;
	const static uint8_t TC_OFF_COMMAND = 0x2;
	const static uint8_t ACTION_INVALID_COMMAND = 0xFF;

	const static uint8_t READ_WHEELSPEED_RESPONSE = 0x1;
	const static uint8_t READ_FAILURE_TC_OFF_RESPONSE = 0xFF;

	const static uint8_t SET_WHEELSPEED_RESPONSE = 0x1;
	const static uint8_t SET_FAILURE_TC_OFF_RESPONSE = 0xFF;

	const static uint8_t ACTION_TC_ENABLE_RESPONSE = 0x1;

	const static uint8_t FAILURE_INVALID_DATA = 0x1;

	const static uint8_t CHECK_RESPONSE_INVALID_LENGTH = 0xFF;

public:
	CTCM( CLANBus *pLANBus, uint64_t equipmentID );
	~CTCM();

	void Run( void );	// Runs simulation

	void ProcessMessage( CLANMessage *pMsg );
	void ProcessBroadcastMessage( CLANMessage *pMsg );

	void HandleTLVMessage( uint8_t typeID, uint16_t length, uint8_t *pData, CResponse *pResponse );
	
	void HandleReadDataMessage( uint8_t *pData, uint16_t length, CResponse *pResponse );
	void HandleSetDataMessage( uint8_t *pData, uint16_t length, CResponse *pResponse );
	void HandleActionMessage( uint8_t *pData, uint16_t length, CResponse *pResponse );

	bool IsTCON( void ) const { return m_bEnableTC; };
	uint16_t GetWheelSpeed( uint8_t wheelNumber ) { return m_wheelSpeed[wheelNumber]; };
	void SetWheelSpeed( uint8_t wheelNumber, uint16_t value ) { m_wheelSpeed[wheelNumber] = value; };

	uint64_t GetEquipmentID( void ) const { return m_equipmentID; };

	void TCMTick( void );

private:
	uint16_t m_wheelSpeed[4];		// Wheel speed
	bool m_bEnableTC;		// Traction Control On (true or false)
	uint64_t m_equipmentID;		// Unique Equipment ID
	bool m_bEngineRunning;		// Engine State
};

#endif // __TCM_H__
