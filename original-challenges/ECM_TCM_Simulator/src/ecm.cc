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
extern "C"
{
#include <stdlib.h>
#include <stdio.h>
}

#include "ecm.h"

CECM::CECM( CLANBus *pLANBus, uint64_t equipmentID )
	: CSimulationComponent( pLANBus ), m_equipmentID( equipmentID )
{
	m_bRunning = false;
	m_bLastRunningState = false;
	
	m_engineRPM = 0;
	m_engineEGT = 0;
	m_engineIAT = 75;
	m_engineTemp = 75;
	m_engineTorque = 0;
	m_engineThrottlePos = 0;	// 10%
	m_engineO2_1 = 0;	// 0%
	m_engineO2_2 = 0;	// 0%
}

CECM::~CECM()
{

}

void CECM::Run( void )
{
	uint8_t destList[] = { ECM_LANBUS_ID, 0xFF };

	CLANMessage *pMsg = m_pLANBus->RecvMessage( destList, sizeof(destList) );

	for ( ; pMsg; pMsg = m_pLANBus->RecvMessage( destList, sizeof(destList), pMsg ) )
	{

		if ( pMsg->GetDestID() == ECM_LANBUS_ID )
			ProcessMessage( pMsg );
		else if ( pMsg->GetDestID() == 0xFF )
			ProcessBroadcastMessage( pMsg );
	}

	// Run engine routines
	EngineTick();
}

void CECM::ProcessBroadcastMessage( CLANMessage *pMessage )
{
	// ECM does not handle any broadcast messages
	return;
}

void CECM::ProcessMessage( CLANMessage *pMessage )
{
	uint8_t *pData = pMessage->GetMessageData();
	uint16_t dataLen = pMessage->GetMessageLen();

	uint8_t srcID = pMessage->GetSourceID();
	uint8_t destID = pMessage->GetDestID();

	// Handle ECM messages
	if ( dataLen == 0 )
		return;

	// Process messages
	CResponse oResponse;
	
	do
	{
		if ( dataLen < 3 )
		{
			// Send failure response
			uint8_t failureResponse[4];
			failureResponse[0] = FAILURE_RESPONSE_TYPE;
			*((uint16_t*)(failureResponse+1)) = 1;	
			failureResponse[3] = FAILURE_INVALID_DATA;

			oResponse.AddResponse( failureResponse, 4 );
			break;
		}

		uint8_t messageTypeID = pData[0];
		uint16_t messageLength = *((uint16_t *)(pData+1));

		if ( dataLen < (messageLength+3) )
		{
			// Send failure response
			uint8_t failureResponse[4];
			failureResponse[0] = FAILURE_RESPONSE_TYPE;
			*((uint16_t*)(failureResponse+1)) = 1;	
			failureResponse[3] = FAILURE_INVALID_DATA;

			oResponse.AddResponse( failureResponse, 4 );
			break;
		}

		// Handle a TLV message
		HandleTLVMessage( messageTypeID, messageLength, pData+3, &oResponse );

		// Continue to next TLV field
		dataLen -= (messageLength+3);
		pData += (messageLength+3);	
	}
	while ( dataLen > 0 );

	// Get response
	uint16_t responseLength = oResponse.GetResponseLength();

	if ( responseLength > 0 )
	{
		uint8_t *pResponseData = new uint8_t[responseLength];

		if ( oResponse.GetResponseData( pResponseData, responseLength ) )
			m_pLANBus->SendMessage( destID, srcID, pResponseData, responseLength );

		delete [] pResponseData;
	}
}

void CECM::HandleTLVMessage( uint8_t typeID, uint16_t length, uint8_t *pData, CResponse *pResponse )
{
	if ( pResponse == NULL )
		return;

	if ( pData == NULL )
		return;

	if ( length == 0 )
		return;

	// Begin parsing message
	switch( typeID )
	{
	case READ_DATA_TYPE:
		HandleReadDataMessage( pData, length, pResponse );
		break;

	case SET_DATA_TYPE:
		HandleSetDataMessage( pData, length, pResponse );
		break;

	case ACTION_DATA_TYPE:
		HandleActionMessage( pData, length, pResponse );
		break;

	case CHECK_EQUIPMENT_TYPE:
		if ( length < 8 )
		{
			// Fail
			uint8_t setResponse[4];
			setResponse[0] = CHECK_RESPONSE_TYPE;
			*((uint16_t*)(setResponse+1)) = 1;	
			setResponse[3] = CHECK_RESPONSE_INVALID_LENGTH;

			pResponse->AddResponse( setResponse, 4 );
		}
		else
		{
			uint64_t checkID = *((uint64_t*)(pData));

			uint8_t checkResponse[4];
			checkResponse[0] = CHECK_RESPONSE_TYPE;
			*((uint16_t*)(checkResponse+1)) = 1;	
			if ( checkID == m_equipmentID )
				checkResponse[3] = 1;	
			else
				checkResponse[3] = 0;

			pResponse->AddResponse( checkResponse, 4 );
		}
		break;

	default:
		// Unknown...
		return;
	}
}

void CECM::HandleReadDataMessage( uint8_t *pData, uint16_t length, CResponse *pResponse )
{
	if ( length < 1 )
		return;

	uint8_t fieldID = pData[0];

	switch( fieldID )
	{
	case READ_EGT_COMMAND:
		{
			uint8_t readResponse[6];
			readResponse[0] = READ_RESPONSE_TYPE;
			*((uint16_t*)(readResponse+1)) = 3;	
			readResponse[3] = READ_RESPONSE_EGT;
			*((uint16_t*)(readResponse+4)) = m_engineEGT;

			pResponse->AddResponse( readResponse, 6 );
		}
		break;

	case READ_RPM_COMMAND:
		{

			uint8_t readResponse[6];
			readResponse[0] = READ_RESPONSE_TYPE;
			*((uint16_t*)(readResponse+1)) = 3;	
			readResponse[3] = READ_RESPONSE_RPM;
			*((uint16_t*)(readResponse+4)) = m_engineRPM;

			pResponse->AddResponse( readResponse, 6 );
		}
		break;
	
	case READ_IAT_COMMAND:
		{

			uint8_t readResponse[6];
			readResponse[0] = READ_RESPONSE_TYPE;
			*((uint16_t*)(readResponse+1)) = 3;	
			readResponse[3] = READ_RESPONSE_IAT;
			*((uint16_t*)(readResponse+4)) = m_engineIAT;

			pResponse->AddResponse( readResponse, 6 );
		}
		break;

	case READ_O2_COMMAND:
		{
			if ( length < 2 )
			{
				// Send failure response
				uint8_t failureResponse[4];
				failureResponse[0] = FAILURE_RESPONSE_TYPE;
				*((uint16_t*)(failureResponse+1)) = 1;	
				failureResponse[3] = FAILURE_INVALID_DATA;

				pResponse->AddResponse( failureResponse, 4 );
			}
			else
			{
				uint8_t readResponse[7];
				readResponse[0] = READ_RESPONSE_TYPE;
				*((uint16_t*)(readResponse+1)) = 4;	
				readResponse[3] = READ_RESPONSE_O2;
				readResponse[4] = pData[1];

				if ( pData[1] == 0 )
					*((uint16_t*)(readResponse+5)) = m_engineO2_1;
				else
					*((uint16_t*)(readResponse+5)) = m_engineO2_2;

				pResponse->AddResponse( readResponse, 7 );
			}
		}
		break;

	case READ_TEMP_COMMAND:
		{
			uint8_t readResponse[6];
			readResponse[0] = READ_RESPONSE_TYPE;
			*((uint16_t*)(readResponse+1)) = 3;	
			readResponse[3] = READ_RESPONSE_TEMP;
			*((uint16_t*)(readResponse+4)) = m_engineTemp;

			pResponse->AddResponse( readResponse, 6 );
		}
		break;

	case READ_TORQUE_COMMAND:
		{
			uint8_t readResponse[6];
			readResponse[0] = READ_RESPONSE_TYPE;
			*((uint16_t*)(readResponse+1)) = 3;	
			readResponse[3] = READ_RESPONSE_TORQUE;
			*((uint16_t*)(readResponse+4)) = m_engineTorque;

			pResponse->AddResponse( readResponse, 6 );
		}
		break;

	case READ_THROTTLEPOS_COMMAND:
		{
			uint8_t readResponse[6];
			readResponse[0] = READ_RESPONSE_TYPE;
			*((uint16_t*)(readResponse+1)) = 3;	
			readResponse[3] = READ_RESPONSE_THROTTLEPOS;
			*((uint16_t*)(readResponse+4)) = m_engineThrottlePos;

			pResponse->AddResponse( readResponse, 6 );
		}
		break;

	default:
		{
			uint8_t readResponse[5];
			readResponse[0] = READ_RESPONSE_TYPE;
			*((uint16_t*)(readResponse+1)) = 2;	
			readResponse[3] = READ_RESPONSE_INVALID_FIELD;
			readResponse[4] = fieldID;

			pResponse->AddResponse( readResponse, 5 );
		}
		break;

	}
}

void CECM::HandleSetDataMessage( uint8_t *pData, uint16_t length, CResponse *pResponse )
{
	if ( length < 3 )
	{
		uint8_t setResponse[4];
		setResponse[0] = SET_RESPONSE_TYPE;
		*((uint16_t*)(setResponse+1)) = 1;	
		setResponse[3] = SET_RESPONSE_INVALID_LENGTH;

		pResponse->AddResponse( setResponse, 4 );
		return;
	}

	uint8_t fieldID = pData[0];
	uint16_t setValue = *((uint16_t*)(pData+1));

	switch( fieldID )
	{
	case SET_THROTTLEPOS_COMMAND:
		{
			if ( !m_bRunning )
			{
				uint8_t setResponse[4];
				setResponse[0] = SET_RESPONSE_TYPE;
				*((uint16_t*)(setResponse+1)) = 1;	
				setResponse[3] = SET_RESPONSE_ENGINE_OFF;

				pResponse->AddResponse( setResponse, 4 );

				break;
			}

			if ( setValue > 100 )
				setValue = 100;

			if ( setValue < 10 )
				setValue = 10;

			// Set throttle position
			m_engineThrottlePos = setValue;

			uint8_t setResponse[6];
			setResponse[0] = SET_RESPONSE_TYPE;
			*((uint16_t*)(setResponse+1)) = 3;	
			setResponse[3] = SET_THROTTLEPOS_COMMAND;
			*((uint16_t*)(setResponse+4)) = setValue;

			pResponse->AddResponse( setResponse, 6 );
		}
		break;
	
	case SET_TORQUE_COMMAND:
		{
			if ( !m_bRunning )
			{
				uint8_t setResponse[4];
				setResponse[0] = SET_RESPONSE_TYPE;
				*((uint16_t*)(setResponse+1)) = 1;	
				setResponse[3] = SET_RESPONSE_ENGINE_OFF;

				pResponse->AddResponse( setResponse, 4 );

				break;
			}

			if ( setValue > ENGINE_MAX_TORQUE )
				setValue = ENGINE_MAX_TORQUE;

			// Ask engine for this much torque
			CommandTorque( setValue );

			// Response with the current torque value of the engine!
			uint8_t setResponse[6];
			setResponse[0] = SET_RESPONSE_TYPE;
			*((uint16_t*)(setResponse+1)) = 3;	
			setResponse[3] = SET_TORQUE_COMMAND;
			*((uint16_t*)(setResponse+4)) = m_engineTorque;

			pResponse->AddResponse( setResponse, 6 );
		}
		break;

	default:
		{
			uint8_t setResponse[5];
			setResponse[0] = SET_RESPONSE_TYPE;
			*((uint16_t*)(setResponse+1)) = 2;	
			setResponse[3] = SET_RESPONSE_INVALID_FIELD;
			setResponse[4] = fieldID;

			pResponse->AddResponse( setResponse, 5 );
		}
		break;
	}
}

void CECM::HandleActionMessage( uint8_t *pData, uint16_t length, CResponse *pResponse )
{
	if ( length < 1 )
		return;

	uint8_t fieldID = pData[0];

	switch( fieldID )
	{
	case START_ENGINE_COMMAND:
		{	
			if ( !m_bRunning )
				StartEngine( pResponse );
		
			uint8_t actionResponse[4];
			actionResponse[0] = ACTION_RESPONSE_TYPE;
			*((uint16_t*)(actionResponse+1)) = 1;	
			actionResponse[3] = ACTION_ENGINE_ON;

			pResponse->AddResponse( actionResponse, 4 );
		}

		break;

	case STOP_ENGINE_COMMAND:
		{
			if ( m_bRunning )
				StopEngine( pResponse );

			uint8_t actionResponse[4];
			actionResponse[0] = ACTION_RESPONSE_TYPE;
			*((uint16_t*)(actionResponse+1)) = 1;	
			actionResponse[3] = ACTION_ENGINE_OFF;

			pResponse->AddResponse( actionResponse, 4 );
		}
		break;
	}
}

void CECM::StartEngine( CResponse *pResponse )
{
	if ( m_bRunning )
		return;

	m_bRunning = true;

	m_engineRPM = 700;
	m_engineEGT = 90;
	m_engineIAT = 75;
	m_engineTemp = 90;
	m_engineTorque = 0;
	m_engineThrottlePos = 10;	// 10%
	m_engineO2_1 = 17;	// 17%
	m_engineO2_2 = 17;	// 17%
}

void CECM::StopEngine( CResponse *pResponse )
{
	if ( !m_bRunning )
		return;

	m_bRunning = false;

	m_engineRPM = 0;
	m_engineEGT = 0;
	m_engineIAT = 75;
	m_engineTemp = 75;
	m_engineTorque = 0;
	m_engineThrottlePos = 0;	// 10%
	m_engineO2_1 = 0;	// 0%
	m_engineO2_2 = 0;	// 0%
}

void CECM::CommandTorque( uint16_t newTorque )
{
	uint16_t deltaTorque;
	bool bTorqueDecrease = false;

	if ( newTorque < m_engineTorque )
	{
		deltaTorque = m_engineTorque - newTorque;
		bTorqueDecrease = true;
	}
	else
	{
		deltaTorque = newTorque - m_engineTorque;
	}

	if ( bTorqueDecrease )
		m_engineRPM -= (deltaTorque * 10);
	else
		m_engineRPM += (deltaTorque * 10);

	m_engineTorque = newTorque;
}

void CECM::EngineTick( void )
{
	// Check engine state
	if ( m_bLastRunningState != m_bRunning )
	{	
		uint8_t ecmBroadcastMessage[5];

		ecmBroadcastMessage[0] = ENGINE_STATE_CHANGE;
		*((uint16_t*)(ecmBroadcastMessage+1)) = 1;

		if ( m_bRunning )
			ecmBroadcastMessage[3] = 1;
		else
			ecmBroadcastMessage[3] = 0;

		// Inform everyone the engine is on
		m_pLANBus->SendMessage( ECM_LANBUS_ID, 0xFF, ecmBroadcastMessage, 4 );
	}

	// Record last state
	m_bLastRunningState = m_bRunning;
}
