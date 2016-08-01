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
#include <stdint.h>
#include <stdlib.h>
}

#include "gps.h"
#include "workerprng.h"

#define PI	(3.1415926536)

CGPSCoordinates::CGPSCoordinates( )
	: m_latDegrees( 0 ), m_latMinutes( 0 ), m_latSeconds( 0 ), m_longDegrees( 0 ), m_longMinutes( 0 ), m_longSeconds( 0 )
{

}
	
CGPSCoordinates::CGPSCoordinates( uint16_t latDegrees, uint8_t latMinutes, uint8_t latSeconds, uint16_t longDegrees, uint8_t longMinutes, uint8_t longSeconds )
	: m_latDegrees( latDegrees ), m_latMinutes( latMinutes ), m_latSeconds( latSeconds ), m_longDegrees( longDegrees ), m_longMinutes( longMinutes ), m_longSeconds( longSeconds )
{

}

CGPSCoordinates::~CGPSCoordinates( )
{

}

uint32_t CGPSCoordinates::GetSerializedSize( void )
{
	return (6);
}

uint32_t CGPSCoordinates::Serialize( uint8_t *pDest, uint32_t destLen )
{
	if ( !pDest )
		return (0);

	if ( destLen < GetSerializedSize() )
		return (0);	// Not enough data

	// Pack into 24-bits each
	uint32_t packedLat = 0;
	packedLat = (m_latDegrees * (60*60)) + (m_latMinutes * 60) + m_latSeconds;
	
	uint32_t packedLong = 0;
	packedLong = (m_longDegrees * (60*60)) + (m_longMinutes * 60) + m_longSeconds;

	// Serialize
	pDest[0] = (packedLat >> 16) & 0xFF;
	pDest[1] = (packedLat >> 8) & 0xFF;
	pDest[2] = (packedLat) & 0xFF;

	pDest[3] = (packedLong >> 16) & 0xFF;
	pDest[4] = (packedLong >> 8) & 0xFF;
	pDest[5] = (packedLong) & 0xFF; 

	return (GetSerializedSize());	
}

uint32_t CGPSCoordinates::Deserialize( uint8_t *pSource, uint32_t sourceLen )
{
	if ( !pSource )
		return (0);

	if ( sourceLen < GetSerializedSize() )
		return (0);

	uint32_t packedLat = 0;
	uint32_t packedLong = 0;

	packedLat = (pSource[0] << 16) | (pSource[1] << 8) | pSource[2];
	packedLong = (pSource[3] << 16) | (pSource[4] << 8) | pSource[5];

	m_latDegrees = packedLat / 3600;
	packedLat -= (m_latDegrees * 3600);

	m_latMinutes = packedLat / 60;
	packedLat -= (m_latMinutes * 60);

	m_latSeconds = packedLat;

	m_longDegrees = packedLong / 3600;
	packedLong -= (m_longDegrees * 3600);

	m_longMinutes = packedLong / 60;
	packedLong -= (m_longMinutes * 60);

	m_longSeconds = packedLong;

	return (GetSerializedSize()); 
}

double CGPSCoordinates::GetLatRadians( void )
{
	double radians = 0.0;

	uint16_t latDegrees = GetLatitudeDegrees();
	if ( latDegrees < 90 )
		radians = -(90 - latDegrees);
	else
		radians = (latDegrees - 90);

	radians += (GetLatitudeMinutes() / 60.0);
	radians += (GetLatitudeSeconds() / 3600.0);

	return ((radians * PI) / 180.0);
}

double CGPSCoordinates::GetLongRadians( void )
{
	double radians = 0.0;

	uint16_t longDegrees = GetLongitudeDegrees();
	if ( longDegrees < 180 )
		radians = -(180 - longDegrees);
	else
		radians = (longDegrees - 180);

	radians += (GetLongitudeMinutes() / 60.0);
	radians += (GetLongitudeSeconds() / 3600.0);

	return ((radians * PI) / 180.0);
}

CGPS::CGPS( )
	: m_bLocked( false ), m_lastCoordinates( 0, 0, 0, 0, 0, 0 )
{

}

CGPS::~CGPS( )
{

}

bool CGPS::SetCoordinates( CGPSCoordinates &newCoords )
{
	m_bLocked = true;

	m_lastCoordinates = newCoords;

	return (true);	
}

uint32_t CGPS::GetDistanceMeters( CGPSCoordinates &coord1, CGPSCoordinates &coord2 )
{
	// Spherical earth model
	double R = 6371000.0;
	double lat1Radians = coord1.GetLatRadians();
	double lat2Radians = coord2.GetLatRadians();

	double long1Radians = coord1.GetLongRadians();
	double long2Radians = coord2.GetLongRadians();

	double deltaLat = lat2Radians - lat1Radians;
	double deltaLong = long2Radians - long1Radians;

	double S = sin(deltaLat/2.0) * sin(deltaLat/2.0) + cos( lat1Radians ) * cos(lat2Radians) * sin( deltaLong/2.0 ) * sin( deltaLong/2.0 );
	double C = 2.0*atan2(sqrt(S), sqrt(1.0-S));

	return (R * C);
}
