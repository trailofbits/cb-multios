/*

Author: Jason Williams

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
#include <libcgc.h>
#include <stdlib.h>
#include <stdint.h>
}

#include "packagetracker.h"
#include "comms.h"

#ifdef NULL
#undef NULL
#define NULL (0)
#endif

CPackageTracker::CPackageTracker( void *pMagicPage )
	: m_pMagicPage( pMagicPage ), m_bDeviceSleep( false ), m_bGPSOn( false ), m_bInternalError( false ), m_internalErrorCode( 0 ), m_batteryLevel( 0 ), m_geofencePointCount( 0 )
{

}

CPackageTracker::~CPackageTracker( )
{

}

void CPackageTracker::SeedSimulation( CPRNG *pRNG )
{
	m_deviceID = pRNG->GetRandomU32();

	m_batteryLevel = pRNG->GetRandomRange( 10, 50 );

	CGPSCoordinates oCoords( pRNG->GetRandomRange( 30, 160 ), pRNG->GetRandomRange( 0, 59 ), pRNG->GetRandomRange( 0, 59 ), pRNG->GetRandomRange( 0, 359 ), pRNG->GetRandomRange( 0, 59 ), pRNG->GetRandomRange( 0, 59 ) );

	m_oGPS.SetCoordinates( oCoords );
}

void CPackageTracker::Run( void )
{
	typedef struct MESSAGE_HEADER_STRUCT
	{
		uint8_t cmdNum;
		uint16_t cmdLength;
	} __attribute__((packed)) tMessageHeader;

	typedef struct MESSAGE_FOOTER_STRUCT
	{
		uint8_t checksum;
	} __attribute__((packed)) tMessageFooter;

	bool bDone = false;
		
	uint8_t *pCommandData = new uint8_t[ 65536 ];

	while ( !bDone )
	{
		tMessageHeader oMessageHeader;
		tMessageFooter oMessageFooter;
	
		uint8_t checksumData = 0;

		// Read command header
		if ( CommReadBytes( (uint8_t*)&oMessageHeader, sizeof(oMessageHeader) ) != sizeof(oMessageHeader) )
			break;

		checksumData = UpdateChecksum( (uint8_t*)&oMessageHeader, sizeof(oMessageHeader), checksumData );

		// Read command data
		uint32_t cmdLen = oMessageHeader.cmdLength;

		if ( CommReadBytes( pCommandData, oMessageHeader.cmdLength ) != oMessageHeader.cmdLength )
			break;

		checksumData = UpdateChecksum( (uint8_t*)pCommandData, cmdLen, checksumData );

		// Read footer
		if ( CommReadBytes( (uint8_t*)&oMessageFooter, sizeof(oMessageFooter) ) != sizeof(oMessageFooter) )
			break;

		// Check checksum
		if ( checksumData != oMessageFooter.checksum )
		{
			SendResponse( oMessageHeader.cmdNum, COMMAND_RESPONSE_BAD_CHECKSUM, NULL, 0 );
			continue;
		}
		
		if ( m_bDeviceSleep && oMessageHeader.cmdNum != COMMAND_WAKEUP && oMessageHeader.cmdNum != COMMAND_SHUTDOWN )
		{
			SendResponse( oMessageHeader.cmdNum, COMMAND_RESPONSE_SLEEP, NULL, 0 );
			continue;		
		}

		switch ( oMessageHeader.cmdNum )
		{
		case COMMAND_INFO:
			DoInfo( pCommandData, cmdLen );
			break;

		case COMMAND_SHUTDOWN:
			DoShutdown( pCommandData, cmdLen );
			bDone = true;
			break;

		case COMMAND_DEBUG:
			DoDebug( pCommandData, cmdLen );
			break;

		case COMMAND_UPDATE_GEOFENCE:
			DoUpdateGeofence( pCommandData, cmdLen );
			break;

		case COMMAND_POSITION:
			DoPosition( pCommandData, cmdLen );
			break;

		case COMMAND_GPS_OFF:
			DoGPSOff( pCommandData, cmdLen );
			break;
	
		case COMMAND_GPS_ON:
			DoGPSOn( pCommandData, cmdLen );
			break;

		case COMMAND_SLEEP:
			DoSleep( pCommandData, cmdLen );
			break;

		case COMMAND_WAKEUP:
			DoWakeup( pCommandData, cmdLen );
			break;

		default:
			// Unknown command
			SendResponse( oMessageHeader.cmdNum, COMMAND_RESPONSE_INVALID, NULL, 0 );
			break;
		}

		// Check for unrecoverable error
		if ( HasError() )
			break;	
	}

	// Delete command buffer		
	delete pCommandData;
}

void CPackageTracker::SendResponse( uint8_t cmdNum, uint8_t cmdResponse, uint8_t *pResponseData, uint16_t responseLength )
{
	typedef struct RESPONSE_MESSAGE_HEADER
	{
		uint8_t cmdNum;
		uint8_t cmdResponse;
		uint16_t responseLen;
	} __attribute__((packed)) tResponseHeader;

	typedef struct RESPONSE_MESSAGE_FOOTER
	{
		uint8_t checksum;
	} __attribute__((packed)) tResponseFooter;

	tResponseHeader oResponseHeader;
	tResponseFooter oResponseFooter;

	oResponseHeader.cmdNum = cmdNum;
	oResponseHeader.cmdResponse = cmdResponse;
	oResponseHeader.responseLen = responseLength;

	oResponseFooter.checksum = 0;

	if ( CommSendBytes( (uint8_t*)&oResponseHeader, sizeof(oResponseHeader) ) != sizeof(oResponseHeader) )
	{
		SetError( INTERNAL_ERROR_COMMS );
		return;
	}

	// Update checksum
	oResponseFooter.checksum = UpdateChecksum( (uint8_t*)&oResponseHeader, sizeof(oResponseHeader), oResponseFooter.checksum );

	// Check for response data and send it
	if ( oResponseHeader.responseLen > 0 )
	{
		if ( !pResponseData )
		{
			SetError( INTERNAL_ERROR_BAD_DATA );
			return;
		}

		if ( CommSendBytes( (uint8_t*)pResponseData, responseLength ) != responseLength )
		{
			SetError( INTERNAL_ERROR_COMMS );
			return;
		}
	
		oResponseFooter.checksum = UpdateChecksum( (uint8_t*)pResponseData, responseLength, oResponseFooter.checksum );
	}

	// Send footer
	if ( CommSendBytes( (uint8_t*)&oResponseFooter, sizeof(oResponseFooter) ) != sizeof(oResponseFooter) )
	{
		SetError( INTERNAL_ERROR_COMMS );
		return;
	}
}

uint8_t CPackageTracker::UpdateChecksum( uint8_t *pData, uint32_t dataLen, uint8_t inputChecksum )
{
	for ( uint32_t i = 0; i < dataLen; i++ )
	{
		inputChecksum += pData[i];
	}	

	return (inputChecksum);
}

void CPackageTracker::DoInfo( uint8_t *pData, uint32_t dataLen )
{
	typedef struct INFO_RESPONSE_STRUCT
	{
		uint8_t deviceState;
		uint8_t batteryLevel;
		uint32_t deviceID;
	} __attribute__((packed)) tInfoResponse;

	tInfoResponse oResponse;

	oResponse.batteryLevel = GetBatteryLevel();
	oResponse.deviceID = GetDeviceID();

	// Set device state
	if ( m_bGPSOn )
	{
		if ( m_oGPS.IsLocked() )
			oResponse.deviceState = GPS_STATE_ON;
		else
			oResponse.deviceState = GPS_STATE_NOT_LOCKED;
	}
	else
		oResponse.deviceState = GPS_STATE_OFF;

	// Send INFO response	
	SendResponse( COMMAND_INFO, COMMAND_RESPONSE_OK, (uint8_t*)&oResponse, sizeof(oResponse) ); 	
}

void CPackageTracker::DoShutdown( uint8_t *pData, uint32_t dataLen )
{
	// Just shutdown
	SendResponse( COMMAND_SHUTDOWN, COMMAND_RESPONSE_OK, NULL, 0 );
}

void CPackageTracker::DoUpdateGeofence( uint8_t *pData, uint32_t dataLen )
{
	typedef struct UPDATE_GEOFENCE_STRUCT
	{
		uint8_t updateAction;
		uint8_t pointCount;
	} __attribute__((packed)) tUpdateGeofence;

	typedef struct GEOFENCE_POINT_DATA
	{
		uint32_t distance;
		uint8_t coordData[6];
	} __attribute__((packed)) tGeofencePointData;
		
	typedef struct GEOFENCE_RESPONSE_DATA
	{
		uint8_t responseStatus;
		uint8_t coordData[6];
		uint32_t distanceMeters;
	} __attribute__((packed)) tGeofenceResponseData;

	tGeofenceResponseData oResponse;

	tUpdateGeofence oUpdateData;

	if ( dataLen < sizeof(oUpdateData) )
	{
		SetError( INTERNAL_ERROR_COMMS );
		return;
	}

	uint32_t commandPos = 0;
	memcpy( &oUpdateData, pData+commandPos, sizeof(oUpdateData) );
	commandPos += sizeof(oUpdateData);

	switch ( oUpdateData.updateAction )
	{
	case GEOFENCE_UPDATE_NEW:
		// Add points
		if ( oUpdateData.pointCount > MAX_GEOFENCE_POINTS )
		{
			SendResponse( COMMAND_UPDATE_GEOFENCE, COMMAND_RESPONSE_MAX_POINTS, NULL, 0 );
			return;
		}

		// Reset points
		for ( uint8_t i = 0; i < oUpdateData.pointCount; i++ )
		{
			tGeofencePointData oPointData;

			if ( (dataLen - commandPos) < sizeof(oPointData) )
			{
				SetError( INTERNAL_ERROR_COMMS );	
				return;
			}

			memcpy( &oPointData, pData+commandPos, sizeof(oPointData) );
			commandPos += sizeof(oPointData);

			m_geofencePoints[i].SetDistance( oPointData.distance );
			m_geofencePoints[i].GetCoords().Deserialize( oPointData.coordData, 6 );
		}

		// Set point count
		m_geofencePointCount = oUpdateData.pointCount;

		break;

	case GEOFENCE_UPDATE_ADD:
		{
			// Add to existing points
			if ( oUpdateData.pointCount > MAX_GEOFENCE_POINTS )
			{
				SendResponse( COMMAND_UPDATE_GEOFENCE, COMMAND_RESPONSE_MAX_POINTS, NULL, 0 );
				return;
			}

#ifdef PATCHED_1
			// Catch vulnerability where we failed to check the addition of the new points to the GeofencePoint array
			if ( m_geofencePointCount + oUpdateData.pointCount > MAX_GEOFENCE_POINTS )
			{
				SendResponse( COMMAND_UPDATE_GEOFENCE, COMMAND_RESPONSE_MAX_POINTS, NULL, 0 );
				return;
			}
#endif

			// Update points
			uint32_t maxPointCounts = m_geofencePointCount + oUpdateData.pointCount;
			for ( uint32_t i = m_geofencePointCount; i < maxPointCounts; i++ )
			{
				tGeofencePointData oPointData;

				if ( (dataLen - commandPos) < sizeof(oPointData) )
				{
					SetError( INTERNAL_ERROR_COMMS );
					return;
				}

				memcpy( &oPointData, pData+commandPos, sizeof(oPointData) );
				commandPos += sizeof(oPointData);

				m_geofencePoints[i].SetDistance( oPointData.distance );
				m_geofencePoints[i].GetCoords().Deserialize( oPointData.coordData, 6 );
			}

			// Set point count
			m_geofencePointCount = maxPointCounts;
		}
		break;

	case GEOFENCE_UPDATE_CLEAR:
		m_geofencePointCount = 0;
		SendResponse( COMMAND_UPDATE_GEOFENCE, COMMAND_RESPONSE_OK, NULL, 0 );
		return;
		break;

	default:
		SendResponse( COMMAND_UPDATE_GEOFENCE, COMMAND_RESPONSE_INVALID, NULL, 0 );
		return;
		break;
	}	

	// Check Geo Fencing -- IF GPS is ACTIVE
	if ( m_bGPSOn )
	{
		CGPSCoordinates oMyCoords;

		m_oGPS.GetLastCoordinates( oMyCoords );


		for ( uint8_t i = 0; i < m_geofencePointCount; i++ )
		{
			// CHECK if they leave any of the geofenced points
			uint32_t distanceFromPoint = CGPS::GetDistanceMeters( oMyCoords, m_geofencePoints[i].GetCoords() );

			if ( distanceFromPoint > m_geofencePoints[i].GetDistance() )
			{
				// Error outside of geofence
				oResponse.responseStatus = GEOFENCE_RESPONSE_OUT_OF_BOUNDS;
				oResponse.distanceMeters = distanceFromPoint;
				
				m_geofencePoints[i].GetCoords().Serialize( oResponse.coordData, 6 );

				SendResponse( COMMAND_UPDATE_GEOFENCE, COMMAND_RESPONSE_OK, (uint8_t*)&oResponse, sizeof(oResponse) );
				return;	
			}			
		}

		// Not outside of bounds
		oResponse.distanceMeters = 0;
		oResponse.responseStatus = GEOFENCE_RESPONSE_IN_BOUNDS;

#ifdef PATCHED_2
		// Prevent an uninitialized variable from leaking data back
		memset( oResponse.coordData, 0, 6 );
#endif
			
		// Send response data	
		SendResponse( COMMAND_UPDATE_GEOFENCE, COMMAND_RESPONSE_OK, (uint8_t*)&oResponse, sizeof(oResponse) );
		return;	
	}
	else
	{
		SendResponse( COMMAND_UPDATE_GEOFENCE, COMMAND_RESPONSE_GPS_OFF, NULL, 0 );
	}
}

void CPackageTracker::DoDebug( uint8_t *pData, uint32_t dataLen )
{
	typedef struct DEBUG_COMMAND_STRUCT
	{
		uint64_t debugAuthToken;
		uint8_t debugCommand;
		uint8_t debugCommandLen;
	} __attribute__((packed)) tDebugCommand;


	tDebugCommand oDebugCommand;

	if ( dataLen < sizeof(oDebugCommand) )
	{
		SetError( INTERNAL_ERROR_COMMS );
		return;
	}

	uint64_t expectedAuthToken = *((uint64_t*)m_pMagicPage) ^ 0xDEB4370331337A7F;
	
	uint32_t commandPos = 0;	
	memcpy( &oDebugCommand, pData+commandPos, sizeof(oDebugCommand) );
	commandPos += sizeof(oDebugCommand);

	
	// Check inner length
	if ( oDebugCommand.debugCommandLen+sizeof(oDebugCommand) != dataLen )
	{
		SendResponse( COMMAND_DEBUG, COMMAND_RESPONSE_INVALID, NULL, 0 );
		return;
	}

	if ( oDebugCommand.debugAuthToken != expectedAuthToken )
	{
		SendResponse( COMMAND_DEBUG, COMMAND_RESPONSE_INVALID, NULL, 0 );
		return;
	}

	// Enter debug mode
	// Accept a few debug commands
	
	switch ( oDebugCommand.debugCommand )
	{
	case DEBUG_SET_BATTERY_LEVEL:
		if ( oDebugCommand.debugCommandLen != 1 )
		{
			SendResponse( COMMAND_DEBUG, COMMAND_RESPONSE_INVALID, NULL, 0 );
			return;
		}

		m_batteryLevel = *((uint8_t*)(pData+commandPos));
		break;

	case DEBUG_SET_COORDINATES:
		if ( oDebugCommand.debugCommandLen != 6 )
		{
			SendResponse( COMMAND_DEBUG, COMMAND_RESPONSE_INVALID, NULL, 0 );
			return;
		}

		{
			CGPSCoordinates oCoords;

			oCoords.Deserialize( (pData+commandPos), 6 );

			m_oGPS.SetCoordinates( oCoords );
		}
		break;

	case DEBUG_SET_DEVICE_ID:
		if ( oDebugCommand.debugCommandLen != 4 )
		{
			SendResponse( COMMAND_DEBUG, COMMAND_RESPONSE_INVALID, NULL, 0 );
			return;
		}

		m_deviceID = *((uint32_t*)(pData+commandPos));
		break;
	
	default:		
		SendResponse( COMMAND_DEBUG, COMMAND_RESPONSE_INVALID, NULL, 0 );
		return;
	}

	SendResponse( COMMAND_DEBUG, COMMAND_RESPONSE_OK, NULL, 0 );
}

void CPackageTracker::DoPosition( uint8_t *pData, uint32_t dataLen )
{
	typedef struct POSITION_RESPONSE_STRUCT
	{
		uint8_t gpsState;
		uint8_t positionData[6];
	} __attribute__((packed)) tPositionResponse;
	
	tPositionResponse oResponse;

	CGPSCoordinates oCoords;

	if ( !m_bGPSOn )
		oResponse.gpsState = GPS_STATE_OFF;
	else
	{
		if ( !m_oGPS.GetLastCoordinates( oCoords ) )
			oResponse.gpsState = GPS_STATE_NOT_LOCKED;
		else
		{
			oResponse.gpsState = GPS_STATE_ON;

			// Serialize coordinates
			oCoords.Serialize( oResponse.positionData, 6 );
		}	
	}

	SendResponse( COMMAND_POSITION, COMMAND_RESPONSE_OK, (uint8_t*)&oResponse, sizeof(oResponse) );
}

void CPackageTracker::DoGPSOff( uint8_t *pData, uint32_t dataLen )
{
	// Turn off GPS
	m_bGPSOn = false;
	
	SendResponse( COMMAND_GPS_OFF, COMMAND_RESPONSE_OK, NULL, 0 );	
}

void CPackageTracker::DoGPSOn( uint8_t *pData, uint32_t dataLen )
{
	// Turn on GPS
	m_bGPSOn = true;

	SendResponse( COMMAND_GPS_ON, COMMAND_RESPONSE_OK, NULL, 0 );
}

void CPackageTracker::DoSleep( uint8_t *pData, uint32_t dataLen )
{
	// Sleep
	m_bDeviceSleep = true;
	
	SendResponse( COMMAND_SLEEP, COMMAND_RESPONSE_OK, NULL, 0 );
}

void CPackageTracker::DoWakeup( uint8_t *pData, uint32_t dataLen )
{
	// Wake
	m_bDeviceSleep = false;

	SendResponse( COMMAND_WAKEUP, COMMAND_RESPONSE_OK, NULL, 0 );
}
