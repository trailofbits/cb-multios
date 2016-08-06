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
#ifndef __GPS_H__
#define __GPS_H__

#include "workerprng.h"

// Longitude 0-360, latitude 0-180
class CGPSCoordinates
{
public:
	CGPSCoordinates( );
	CGPSCoordinates( uint16_t latDegrees, uint8_t latMinutes, uint8_t latSeconds, uint16_t longDegrees, uint8_t longMinutes, uint8_t longSeconds );
	~CGPSCoordinates( );

	uint16_t GetLatitudeDegrees( void ) const { return m_latDegrees; };
	uint8_t GetLatitudeMinutes( void ) const { return m_latMinutes; };
	uint8_t GetLatitudeSeconds( void ) const { return m_latSeconds; };

	uint16_t GetLongitudeDegrees( void ) const { return m_longDegrees; };
	uint8_t GetLongitudeMinutes( void ) const { return m_longMinutes; };
	uint8_t GetLongitudeSeconds( void ) const { return m_longSeconds; };

	uint32_t GetSerializedSize( void );

	uint32_t Serialize( uint8_t *pDest, uint32_t destLen );
	uint32_t Deserialize( uint8_t *pSource, uint32_t sourceLen );

	double GetLatRadians( void );
	double GetLongRadians( void );

private:
	uint16_t m_latDegrees;
	uint8_t m_latMinutes;
	uint8_t m_latSeconds;

	uint16_t m_longDegrees;
	uint8_t m_longMinutes;
	uint8_t m_longSeconds;
};

class CGPS
{
public:
	CGPS( );
	~CGPS( );

	bool SetCoordinates( CGPSCoordinates &newCoords );

	bool GetLastCoordinates( CGPSCoordinates &coords )
	{
		if ( !m_bLocked )
			return (false);

		coords = m_lastCoordinates;
		
		return (true);	
	}

	bool IsLocked( void ) const { return m_bLocked; };

	static uint32_t GetDistanceMeters( CGPSCoordinates &coord1, CGPSCoordinates &coord2 );

private:
	bool m_bLocked;
	CGPSCoordinates m_lastCoordinates;
};

#endif // __GPS_H__
