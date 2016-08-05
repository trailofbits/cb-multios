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
#ifndef __ECM_H__
#define __ECM_H__

#include "simulation.h"
#include "lanbus.h"
#include "response.h"

class CECM : public CSimulationComponent
{
public:
	// Broadcast message type
	const static uint8_t ENGINE_STATE_CHANGE = 0x1;

	const static uint8_t ECM_LANBUS_ID = 0x13;

	const static uint8_t READ_DATA_TYPE = 0x1;
	const static uint8_t SET_DATA_TYPE = 0x2;
	const static uint8_t ACTION_DATA_TYPE = 0x3;
	const static uint8_t CHECK_EQUIPMENT_TYPE = 0x4;

	const static uint8_t READ_EGT_COMMAND = 0x1;
	const static uint8_t READ_RPM_COMMAND = 0x2;
	const static uint8_t READ_IAT_COMMAND = 0x3;
	const static uint8_t READ_O2_COMMAND = 0x4;
	const static uint8_t READ_TEMP_COMMAND = 0x5;
	const static uint8_t READ_TORQUE_COMMAND = 0x6;
	const static uint8_t READ_THROTTLEPOS_COMMAND = 0x7;

	const static uint8_t SET_THROTTLEPOS_COMMAND = 0x1;
	const static uint8_t SET_TORQUE_COMMAND = 0x2;

	const static uint8_t SET_RESPONSE_INVALID_FIELD = 0xFD;
	const static uint8_t SET_RESPONSE_ENGINE_OFF = 0xFE;
	const static uint8_t SET_RESPONSE_INVALID_LENGTH = 0xFF;

	const static uint8_t START_ENGINE_COMMAND = 0x1;
	const static uint8_t STOP_ENGINE_COMMAND = 0x2;

	const static uint8_t READ_RESPONSE_TYPE = 0x1;
	const static uint8_t SET_RESPONSE_TYPE = 0x2;
	const static uint8_t ACTION_RESPONSE_TYPE = 0x3;
	const static uint8_t CHECK_RESPONSE_TYPE = 0x4;
	const static uint8_t FAILURE_RESPONSE_TYPE = 0x5;

	const static uint8_t READ_RESPONSE_EGT = 0x1;
	const static uint8_t READ_RESPONSE_RPM = 0x2;
	const static uint8_t READ_RESPONSE_IAT = 0x3;
	const static uint8_t READ_RESPONSE_O2 = 0x4;
	const static uint8_t READ_RESPONSE_TEMP = 0x5;
	const static uint8_t READ_RESPONSE_TORQUE = 0x6;
	const static uint8_t READ_RESPONSE_THROTTLEPOS = 0x7;
	const static uint8_t READ_RESPONSE_INVALID_FIELD = 0xFF;

	const static uint8_t ACTION_ENGINE_OFF = 0x0;
	const static uint8_t ACTION_ENGINE_ON = 0x1;

	const static uint8_t CHECK_RESPONSE_INVALID_LENGTH = 0xFF;

	const static uint8_t FAILURE_INVALID_DATA = 0x1;

	const static uint16_t ENGINE_MAX_TORQUE = 400;	// 400 lb-ft

public:
	CECM( CLANBus *pLANBus, uint64_t equipmentID );
	~CECM();

	void Run( void );	// Runs simulation

	void ProcessMessage( CLANMessage *pMessage );
	void ProcessBroadcastMessage( CLANMessage *pMessage );

	void HandleTLVMessage( uint8_t typeID, uint16_t length, uint8_t *pData, CResponse *pResponse );
	
	void HandleReadDataMessage( uint8_t *pData, uint16_t length, CResponse *pResponse );
	void HandleSetDataMessage( uint8_t *pData, uint16_t length, CResponse *pResponse );
	void HandleActionMessage( uint8_t *pData, uint16_t length, CResponse *pResponse );

	bool IsEngineRunning( void ) const { return m_bRunning; };
	uint16_t GetEngineRPM( void ) const { return m_engineRPM; };
	uint16_t GetEngineEGT( void ) const { return m_engineEGT; };
	uint16_t GetEngineIAT( void ) const { return m_engineIAT; };
	uint16_t GetEngineO2_1( void ) const { return m_engineO2_1; };
	uint16_t GetEngineO2_2( void ) const { return m_engineO2_2; };
	uint16_t GetEngineTemp( void ) const { return m_engineTemp; };	
	uint16_t GetEngineTorque( void ) const { return m_engineTorque; };
	uint16_t GetThrottlePos( void ) const { return m_engineThrottlePos; };

	void StartEngine( CResponse *pResponse );
	void StopEngine( CResponse *pResponse );

	uint64_t GetEquipmentID( void ) const { return m_equipmentID; };

private:
	void CommandTorque( uint16_t newTorqueValue );
	void EngineTick( void );

	uint16_t m_engineRPM;		// Engine RPM
	uint16_t m_engineEGT;		// Engine Exhaust Gas Temperature
	uint16_t m_engineIAT;		// Engine Incoming Air Temperature
	uint16_t m_engineO2_1;		// Engine O2 sensor 1
	uint16_t m_engineO2_2;		// Engine O2 sensor 2
	uint16_t m_engineTemp; 		// Engine Temperature
	uint16_t m_engineThrottlePos;	// ENgine Throttle Position
	uint16_t m_engineTorque;	// Engine calculated torque
	bool m_bRunning;		// Engine running (true or false)
	bool m_bLastRunningState;	// Engine last state... for turn on sequencing

	uint64_t m_equipmentID;		// Equipment Identifier
};

#endif // __ECM_H__
