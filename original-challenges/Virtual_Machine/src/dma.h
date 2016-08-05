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
#ifndef __DMA_H__
#define __DMA_H__

#include "peripheral.h"

class CMMU;

class CDMA
{
public:
	static const uint32_t MAX_DMA_WORKERS = 5;	// Max number of individual DMA workers
	static const uint32_t MAX_DMA_TRANSFER_COUNT = 4; // Max number of DMA transfers that can be serviced at a time

public:
	CDMA( );
	~CDMA( );

	void InitDMA( void );
	bool AddPeripheral( uint8_t deviceID, CPeripheral *pPeripheral );

	void ServiceDMA( CMMU *pMMU );

	bool InitReadWorker( uint8_t deviceID, uint16_t address, uint16_t length );
	bool InitWriteWorker( uint8_t deviceID, uint16_t address, uint16_t length );

private:
	typedef enum
	{
		DMA_WORKER_NONE = 0,
		DMA_WORKER_READ = 1,
		DMA_WORKER_WRITE = 2,
	} eDMAWorkerAction;

	class CDMAWorker
	{
	public:
		CDMAWorker( )
			: m_actionType( DMA_WORKER_NONE )
		{

		}

		CDMAWorker( eDMAWorkerAction actionType, uint8_t deviceID, uint16_t address, uint16_t length )
			: m_actionType( actionType ), m_deviceID( deviceID ), m_address( address ), m_length( length )
		{

		}

		~CDMAWorker( )
		{

		}

		eDMAWorkerAction GetType( void ) const { return m_actionType; };
		uint8_t GetDeviceID( void ) const { return m_deviceID; };
		uint16_t GetAddress( void ) const { return m_address; };
		uint16_t GetLength( void ) const { return m_length; };
		uint16_t GetPosition( void ) const { return m_curPos; };

		void AdvancePosition( uint16_t amount ) { m_curPos += amount; };

		void ClearWorker( void ) { m_actionType = DMA_WORKER_NONE; };

		void StartWorker( eDMAWorkerAction actionType, uint8_t deviceID, uint16_t address, uint16_t length )
		{
			m_actionType = actionType;
			m_address = address;
			m_deviceID = deviceID;
			m_length = length;

			m_curPos = 0;
		}

		bool IsWorkerAvailable( void ) const { return m_actionType != DMA_WORKER_NONE; };
		
	private:
		eDMAWorkerAction m_actionType;
		uint8_t m_deviceID;
		uint16_t m_curPos;
		uint16_t m_address;
		uint16_t m_length;
	};

	CDMAWorker m_dmaWorkers[MAX_DMA_WORKERS];
	uint8_t m_workerCount;
	uint8_t m_workerLast;

	CPeripheral *m_pPeripherals[256];
};

#endif // __DMA_H__
