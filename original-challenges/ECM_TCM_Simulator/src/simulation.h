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
#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <cutil_list.h>
#include "lanbus.h"

class CSimulationComponent
{
public:
	CSimulationComponent( CLANBus *pLANBus ) : m_pLANBus( pLANBus ) { };
	virtual ~CSimulationComponent( ) { };

	virtual void Run( void ) = 0;

	virtual bool SendMessage( uint8_t srcID, uint8_t destID, uint8_t *pMessageData, uint16_t messageLen );

public:
	CUtil::DLL_LINK( CSimulationComponent ) m_simulationLink;

protected:
	CLANBus *m_pLANBus;

private:
};

class CSimulationCommand
{
public:
	CSimulationCommand( uint8_t srcID, uint8_t destID, uint32_t runTime, uint8_t *pData, uint16_t dataLen );
	~CSimulationCommand( );

	uint8_t GetSrcID( void ) const { return m_srcID; };
	uint8_t GetDestID( void ) const { return m_destID; };
	uint8_t *GetData( void ) const { return m_pData; };
	uint16_t GetDataLength( void ) const { return m_dataLen; };
	uint32_t GetRunTime( void ) const { return m_runTime; };

public:
	CUtil::DLL_LINK( CSimulationCommand ) m_simulationLink;

private:
	uint8_t		m_srcID;
	uint8_t 	m_destID;
	uint32_t	m_runTime;
	uint8_t		*m_pData;
	uint16_t	m_dataLen;
};

class CSimulation
{
public:
	const static uint32_t MAX_SIMULATION_TIME_MS = (1000 * 120);	// 5 minutes
	const static uint32_t SIMULATION_TICK_COUNT_MS = (50);		// Every 50 milliseconds (or 20x per second) run a tick
public:
	CSimulation( ) { };
	~CSimulation( ) { };

	void AddSimulationComponent( CSimulationComponent *pItem );
	void SetupSimulation( void );
	void RunSimulation( void );

	CLANBus *GetLanBus( void ) { return &m_lanBus; };

private:
	bool SendComponentCommand( uint8_t srcID, uint8_t destID, uint32_t cmdTime, uint8_t *pCmdData, uint16_t cmdLength );

	void ReadEGT( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID );
	void ReadRPM( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID );
	void ReadIAT( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID );
	void ReadO2( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID, uint8_t o2_num );
	void ReadEngineTemp( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID );
	void ReadEngineTorque( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID );
	void StartEngine( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID );
	void StopEngine( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID );
	void SetThrottlePosition( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID );
	void SetEngineLoad( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID );
	void SendBinaryMessage( uint32_t cmd_time_ms, uint8_t srcID, uint8_t destID );

private:
	// LAN Bus for simulation
	CLANBus m_lanBus;

	// List of commands for simulation run -- ordered
	CUtil::DLL_LIST( CSimulationCommand, m_simulationLink ) m_commandList;

	// List of components for simulation to run
	CUtil::DLL_LIST( CSimulationComponent, m_simulationLink ) m_componentList;
};

#endif // __SIMULATION_H__
