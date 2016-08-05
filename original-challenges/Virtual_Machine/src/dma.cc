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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

#include "dma.h"
#include "mmu.h"

CDMA::CDMA( )
{
	for ( uint32_t i = 0; i < 256; i++ )
		m_pPeripherals[i] = NULL;
}

CDMA::~CDMA( )
{

}

void CDMA::InitDMA( void )
{
	for ( uint32_t i = 0; i < MAX_DMA_WORKERS; i++ )
		m_dmaWorkers[i].ClearWorker();

	m_workerLast = 0;
	m_workerCount = 0;
}

bool CDMA::AddPeripheral( uint8_t deviceID, CPeripheral *pPeripheral )
{
	if ( !pPeripheral )
		return (false);

	if ( m_pPeripherals[deviceID] )
		return (false);

	m_pPeripherals[deviceID] = pPeripheral;

	return (true);
}

bool CDMA::InitReadWorker( uint8_t deviceID, uint16_t address, uint16_t length  )
{
	uint32_t workerCur = m_workerCount++;

#ifdef PATCHED_1
	if ( workerCur >= MAX_DMA_WORKERS )
#else
	if ( workerCur > MAX_DMA_WORKERS )
#endif
		return (false);

	m_dmaWorkers[workerCur].StartWorker( DMA_WORKER_READ, deviceID, address, length );

	return (true);
}

bool CDMA::InitWriteWorker( uint8_t deviceID, uint16_t address, uint16_t length )
{
	uint32_t workerCur = m_workerCount++;

#ifdef PATCHED_1
	if ( workerCur >= MAX_DMA_WORKERS )
#else
	if ( workerCur > MAX_DMA_WORKERS )
#endif
		return (false);

	m_dmaWorkers[workerCur].StartWorker( DMA_WORKER_WRITE, deviceID, address, length );

	return (true);
}

void CDMA::ServiceDMA( CMMU *pMMU )
{
	if ( !pMMU )
		return;

	uint8_t dmaTransferCount = 0;

	for ( dmaTransferCount = 0; dmaTransferCount < m_workerCount; dmaTransferCount++ )
	{
		// Only allow a maximum number of transfers
		if ( dmaTransferCount >= MAX_DMA_TRANSFER_COUNT )
			break;

		// Round robin each DMA worker
		uint8_t workerCur = m_workerLast;

		// Find a worker to service
		bool bWorkersAvailable = false;

		uint32_t tryCount = 0;

		for ( tryCount = 0; tryCount < MAX_DMA_WORKERS; tryCount++ )
		{
			if ( workerCur >= MAX_DMA_WORKERS )
				workerCur = 0;

			if ( m_dmaWorkers[workerCur].IsWorkerAvailable() )
			{
				bWorkersAvailable = true;
				break;
			}

			workerCur++;
		}

		if ( bWorkersAvailable )
		{
			uint8_t deviceID = m_dmaWorkers[workerCur].GetDeviceID();
			uint16_t address = m_dmaWorkers[workerCur].GetAddress();
			uint16_t length = m_dmaWorkers[workerCur].GetLength();
			uint16_t position = m_dmaWorkers[workerCur].GetPosition();
			eDMAWorkerAction actionType = m_dmaWorkers[workerCur].GetType();

			uint32_t dmaAmount = (length - position);
			if ( dmaAmount > 4 )
				dmaAmount = 4;

			if ( dmaAmount == 0 )
			{
				// Remove worker
				m_workerCount--;

				// End transfer
				m_dmaWorkers[workerCur].ClearWorker();
			}
			else if ( m_pPeripherals[deviceID] )
			{
				uint8_t readValue[4];

				if ( actionType == DMA_WORKER_READ )
				{

					if ( m_pPeripherals[deviceID]->Read( readValue, dmaAmount ) )
						pMMU->WriteDMA( address+position, readValue, dmaAmount );
				}
				else
				{
					if ( pMMU->ReadDMA( address+position, readValue, dmaAmount ) )
						m_pPeripherals[deviceID]->Write( readValue, dmaAmount );
				}

				if ( position+dmaAmount >= length )
				{
					// Remove worker
					m_workerCount--;

					// End transfer
					m_dmaWorkers[workerCur].ClearWorker();
				}
				else
					m_dmaWorkers[workerCur].AdvancePosition( dmaAmount );
			}
			else
			{
				m_dmaWorkers[workerCur].ClearWorker();
				m_workerCount--;
			}

			// Advance to next worker	
			m_workerLast = workerCur++;
		}
		else
		{
			m_workerLast = 0;
			break;
		}
	}
}
