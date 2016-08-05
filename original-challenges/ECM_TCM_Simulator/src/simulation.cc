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
#include "common.h"
#include "simulation.h"
#include "ecm.h"

extern "C"
{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

bool CSimulationComponent::SendMessage( uint8_t srcID, uint8_t destID, uint8_t *pMessageData, uint16_t messageLen )
{
	if ( !m_pLANBus )
		return (false);

	return m_pLANBus->SendMessage( srcID, destID, pMessageData, messageLen );
}

CSimulationCommand::CSimulationCommand( uint8_t srcID, uint8_t destID, uint32_t cmdTime, uint8_t *pCmdData, uint16_t cmdLength )
	: m_srcID( srcID ), m_destID( destID ), m_runTime( cmdTime ), m_dataLen( cmdLength )
{
	m_pData = new uint8_t[cmdLength];

	memcpy( m_pData, pCmdData, cmdLength );
}

CSimulationCommand::~CSimulationCommand( ) 
{
	if ( m_pData )
		delete [] m_pData;

	m_pData = NULL;
}

void CSimulation::AddSimulationComponent( CSimulationComponent *pItem )
{
	if ( !pItem )
		return;

	m_componentList.AddLast( pItem );
}

void CSimulation::SetupSimulation( void )
{
	// Get user simulation commands
	printf( "Enter number of simulation commands: " );

	CUtil::String sLine = ReadLine( );	

	uint32_t cmd_count;

	sLine.ToInt( cmd_count );

	for ( uint32_t i = 0; i < cmd_count; i++ )
	{
		uint32_t value;

		uint8_t srcID, destID;

		printf( "Enter Source ID: " );

		sLine = ReadLine();

		sLine.ToInt( value );

		if ( value > 255 )
		{
			printf( "Invalid source ID. Setting to 255\n" );
			srcID = 255;
		}
		else
			srcID = value;

		printf( "Enter Dest ID: " );

		sLine = ReadLine();

		sLine.ToInt( value );

		if ( value > 255 )
		{
			printf( "Invalid dest ID. Setting to 255\n" );
			destID = 255;
		}
		else
			destID = value;

		printf( "Enter Command Type:\n" );
		printf( "0 - Read EGT\n" );
		printf( "1 - Read RPM\n" );
		printf( "2 - Read IAT\n" );
		printf( "3 - Read O2_1\n" );
		printf( "4 - Read O2_2\n" );
		printf( "5 - Read Engine Temp\n" );
		printf( "6 - Read Engine Torque\n" );
		printf( "7 - Start Engine\n" );
		printf( "8 - Stop Engine\n" );
		printf( "9 - Set Throttle Position\n" );
		printf( "10 - Set Engine Load\n" );
		printf( "11 - Send Binary Message\n" );
		
		uint32_t cmd_type;

		sLine = ReadLine();

		sLine.ToInt( cmd_type );

		printf( "Enter command time (in ms):\n" );
		printf( "Simulation will send this command at the specified time in the simulation (max 2 minutes of simulation time):\n" );

		uint32_t cmd_time_ms;

		sLine = ReadLine();

		sLine.ToInt( cmd_time_ms );

		switch( cmd_type )
		{
		case 0:
			// Read EGT
			ReadEGT( cmd_time_ms, srcID, destID );
			break;

		case 1:
			// Read RPM
			ReadRPM( cmd_time_ms, srcID, destID );
			break;

		case 2:
			// Read IAT
			ReadIAT( cmd_time_ms, srcID, destID );
			break;

		case 3:
			// Read 02_1
			ReadO2( cmd_time_ms, srcID, destID, 1 );
			break;

		case 4:
			// Read O2_2
			ReadO2( cmd_time_ms, srcID, destID, 2 );
	 		break;

		case 5:
			// Read Engine Temp
			ReadEngineTemp( cmd_time_ms, srcID, destID );
			break;

		case 6:
			// Read Engine Torque
			ReadEngineTorque( cmd_time_ms, srcID, destID );
			break;

		case 7:
			// Start Engine
			StartEngine( cmd_time_ms, srcID, destID );
			break;

		case 8:
			// Stop Engine
			StopEngine( cmd_time_ms, srcID, destID );
			break;

		case 9:
			// Set Throttle Position
			SetThrottlePosition( cmd_time_ms, srcID, destID );
			break;

		case 10:
			// Set Engine Load
			SetEngineLoad( cmd_time_ms, srcID, destID );
			break;

		case 11:
			// Send Binary Message
			SendBinaryMessage( cmd_time_ms, srcID, destID );
			break;	

		default:
			// Unknown
			break;
		}
	}
}

void CSimulation::RunSimulation( void )
{
	printf( "Running simulation:\n" );

	if ( m_componentList.IsEmpty() )
	{
		printf( "0 components for simulation.\n" );
		return;
	}	

	uint32_t lastTick = 0;

	CSimulationCommand *pCommand;

	if ( (pCommand = m_commandList.GetLast()) )
	{
		lastTick = pCommand->GetRunTime() / SIMULATION_TICK_COUNT_MS;

		lastTick++;
	}
	else
	{
		printf( "0 commands for simulation.\n" );
		return;
	}

	// Run simulation ticks
	uint32_t nextTick = SIMULATION_TICK_COUNT_MS;

	// Reset pCommand
	pCommand = m_commandList.GetFirst();

	for ( uint32_t curTick = 0; curTick < lastTick; curTick++ )
	{
		// Only display the tick counter if an event has occurred
		bool bDidDisplayTick = false;


		// Send commands first...
		while ( pCommand && pCommand->GetRunTime() < nextTick )
		{
			if ( !bDidDisplayTick )
			{
				printf( "[TICK][$d]:\n", curTick );
				
				bDidDisplayTick = true;
			}

			printf( "[SENDCMD][TIME=$d][LENGTH=$d][SRC=$d][DEST=$d]\n", pCommand->GetRunTime(), pCommand->GetDataLength(), pCommand->GetSrcID(), pCommand->GetDestID() );
			m_lanBus.InjectSimulationMessage( pCommand->GetSrcID(), pCommand->GetDestID(), pCommand->GetData(), pCommand->GetDataLength() );			

			pCommand = m_commandList.GetNext( pCommand );
		}

		// Now run the tick for every component
		for ( CSimulationComponent *pComponent = m_componentList.GetFirst(); pComponent; pComponent = m_componentList.GetNext( pComponent ) )
			pComponent->Run();

		// Move messages
		m_lanBus.NextTick();
		
		// Get any messages destined back to us!
		uint8_t destList[] = { 0xFF, 0x0 };
		
		CLANMessage *pMsg = m_lanBus.RecvMessage( destList, sizeof(destList) );

		for ( ; pMsg; pMsg = m_lanBus.RecvMessage( destList, sizeof(destList), pMsg ) )
		{
			if ( !bDidDisplayTick )
			{
				printf( "[TICK][$d]:\n", curTick );
				
				bDidDisplayTick = true;
			}

			printf( "[MESSAGE][SRC=$d][DEST=$d][LENGTH=$d]\n", pMsg->GetSourceID(), pMsg->GetDestID(), pMsg->GetMessageLen() );

			PrintHexBytes( pMsg->GetMessageData(), pMsg->GetMessageLen() );
		}

		nextTick += SIMULATION_TICK_COUNT_MS;
	}

	// Destroy simulation components
	m_commandList.DeleteAll();
	m_componentList.DeleteAll();

	printf( "Simulation complete.\n" );
}

bool CSimulation::SendComponentCommand( uint8_t srcID, uint8_t destID, uint32_t cmdTime, uint8_t *pCmdData, uint16_t cmdLength )
{
	if ( pCmdData == NULL )
		return (false);

	if ( cmdLength == 0 )
		return (false);

	if ( cmdTime > MAX_SIMULATION_TIME_MS )
		return (false);

	// Order by command time
	CSimulationCommand *pBefore = NULL;
	CSimulationCommand *pCur = NULL;

	for ( pCur = m_commandList.GetFirst(); pCur; pCur = m_commandList.GetNext( pCur ) )
	{
		if ( pCur->GetRunTime() > cmdTime )
			break;

		pBefore = pCur;
	}	

	if ( pBefore == NULL )
	{
		// Add to the front...
		m_commandList.AddFirst( new CSimulationCommand( srcID, destID, cmdTime, pCmdData, cmdLength ) );		
	}
	else if ( pCur == NULL )
	{
		// Add at the end...
		m_commandList.AddLast( new CSimulationCommand( srcID, destID, cmdTime, pCmdData, cmdLength ) );
	}
	else
	{
		// Add after
		m_commandList.AddAfter( pBefore, new CSimulationCommand( srcID, destID, cmdTime, pCmdData, cmdLength ) );
	}

	// Successfully added
	return (true);
}

void CSimulation::ReadEGT( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID )
{
	// Force dest ID
	destID = CECM::ECM_LANBUS_ID;

	uint8_t egtCommand[4];
	egtCommand[0] = CECM::READ_DATA_TYPE;
	*((uint16_t*)(egtCommand+1)) = 1;
	egtCommand[3] = CECM::READ_EGT_COMMAND;
	
	SendComponentCommand( srcID, destID, cmd_time_ms, egtCommand, 4 );
}

void CSimulation::ReadRPM( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID )
{
	// Force dest ID
	destID = CECM::ECM_LANBUS_ID;
	
	uint8_t egtCommand[4];
	egtCommand[0] = CECM::READ_DATA_TYPE;
	*((uint16_t*)(egtCommand+1)) = 1;
	egtCommand[3] = CECM::READ_RPM_COMMAND;

	SendComponentCommand( srcID, destID, cmd_time_ms, egtCommand, 4 );
}

void CSimulation::ReadIAT( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID )
{
	// Force dest ID
	destID = CECM::ECM_LANBUS_ID;
	
	uint8_t egtCommand[4];
	egtCommand[0] = CECM::READ_DATA_TYPE;
	*((uint16_t*)(egtCommand+1)) = 1;	
	egtCommand[3] = CECM::READ_IAT_COMMAND;

	SendComponentCommand( srcID, destID, cmd_time_ms, egtCommand, 4 );
}

void CSimulation::ReadO2( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID, uint8_t o2_num )
{
	// Force dest ID
	destID = CECM::ECM_LANBUS_ID;
	
	uint8_t egtCommand[5];
	egtCommand[0] = CECM::READ_DATA_TYPE;
	*((uint16_t*)(egtCommand+1)) = 2;	
	egtCommand[3] = CECM::READ_O2_COMMAND;
	egtCommand[4] = o2_num;

	SendComponentCommand( srcID, destID, cmd_time_ms, egtCommand, 5 );
}

void CSimulation::ReadEngineTemp( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID )
{
	// Force dest ID
	destID = CECM::ECM_LANBUS_ID;
	
	uint8_t egtCommand[4];
	egtCommand[0] = CECM::READ_DATA_TYPE;
	*((uint16_t*)(egtCommand+1)) = 1;	
	egtCommand[3] = CECM::READ_TEMP_COMMAND;

	SendComponentCommand( srcID, destID, cmd_time_ms, egtCommand, 4 );
}

void CSimulation::ReadEngineTorque( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID )
{
	// Force dest ID
	destID = CECM::ECM_LANBUS_ID;
	
	uint8_t egtCommand[4];
	egtCommand[0] = CECM::READ_DATA_TYPE;
	*((uint16_t*)(egtCommand+1)) = 1;	
	egtCommand[3] = CECM::READ_TORQUE_COMMAND;

	SendComponentCommand( srcID, destID, cmd_time_ms, egtCommand, 4 );
}

void CSimulation::StartEngine( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID )
{
	// Force dest ID
	destID = CECM::ECM_LANBUS_ID;
	
	uint8_t egtCommand[4];
	egtCommand[0] = CECM::ACTION_DATA_TYPE;
	*((uint16_t*)(egtCommand+1)) = 1;	
	egtCommand[3] = CECM::START_ENGINE_COMMAND;

	SendComponentCommand( srcID, destID, cmd_time_ms, egtCommand, 4 );
}

void CSimulation::StopEngine( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID )
{
	// Force dest ID
	destID = CECM::ECM_LANBUS_ID;
	
	uint8_t egtCommand[4];
	egtCommand[0] = CECM::ACTION_DATA_TYPE;
	*((uint16_t*)(egtCommand+1)) = 1;	
	egtCommand[3] = CECM::STOP_ENGINE_COMMAND;

	SendComponentCommand( srcID, destID, cmd_time_ms, egtCommand, 4 );
}

void CSimulation::SetThrottlePosition( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID )
{
	printf( "Enter throttle position: " );
	uint32_t value;

	CUtil::String sLine = ReadLine();

	sLine.ToInt( value );
	
	// Force dest ID
	destID = CECM::ECM_LANBUS_ID;

	uint8_t egtCommand[6];
	egtCommand[0] = CECM::SET_DATA_TYPE;
	*((uint16_t*)(egtCommand+1)) = 3;	
	egtCommand[3] = CECM::SET_THROTTLEPOS_COMMAND;
	*((uint16_t*)(egtCommand+4)) = (uint16_t)value;

	SendComponentCommand( srcID, destID, cmd_time_ms, egtCommand, 6 );
}

void CSimulation::SetEngineLoad( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID )
{
	printf( "Set Engine Load: " );
	uint32_t value;

	CUtil::String sLine = ReadLine();

	sLine.ToInt( value );

	// Force dest ID
	destID = CECM::ECM_LANBUS_ID;
	
	uint8_t egtCommand[6];
	egtCommand[0] = CECM::SET_DATA_TYPE;
	*((uint16_t*)(egtCommand+1)) = 3;	
	egtCommand[3] = CECM::SET_TORQUE_COMMAND;
	*((uint16_t*)(egtCommand+4)) = (uint16_t)value;

	SendComponentCommand( srcID, destID, cmd_time_ms, egtCommand, 6 );
}

void CSimulation::SendBinaryMessage( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID )
{
	printf( "Enter Binary Message (in hex): " );

	CUtil::String sLine = ReadLine();

	if ( sLine.IsEmpty() )
	{
		printf( "Message data empty. Not sending.\n" );
		return;
	}

	if ( sLine.GetLength() % 2 != 0 )
	{
		printf( "Invalid hex message, must be 2-byte aligned.\n" );
		return;
	}

	uint32_t messageLength = (sLine.GetLength() / 2);
	
	if ( messageLength > 1024 )
	{
		printf( "Invalid hex message, max message length exceeded.\n" );
		return;
	}	
	
	uint8_t *pMessageData = new uint8_t[messageLength];

	memset( pMessageData, 0, messageLength );

	uint32_t binaryPos = 0;
	for ( size_t pos = 0; pos < sLine.GetLength(); )
	{
		uint8_t temp;

		if ( !HexCharToInt( sLine[pos], temp ) )
		{
			printf( "Invalid character at position $d, not a hex character -- discarding message.\n", pos );
			
			// Memory leak here -- leave it	
			return;
		}

		pos++;
		pMessageData[binaryPos] = (temp & 0xF) << 4;

		if ( !HexCharToInt( sLine[pos], temp ) )
		{
			printf( "Invalid character at position $d, not a hex character -- discarding message.\n", pos );
			
			// Memory leak here -- leave it	
			return;
		}

		pos++;
		pMessageData[binaryPos] |= (temp & 0xF);	

		binaryPos++;
	}

	// Send custom component command	
	SendComponentCommand( srcID, destID, cmd_time_ms, pMessageData, binaryPos );

	// Free temporary message
	delete [] pMessageData;
}
