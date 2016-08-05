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
#ifndef __RESPONSE_H__
#define __RESPONSE_H__

#include <cutil_list.h>

extern "C"
{
#include <stdio.h>
#include <stdlib.h>
}

class CResponse
{
public:
	CResponse( );
	~CResponse( );

	uint16_t GetResponseLength( void ) const { return m_responseLen; };

	uint16_t AddResponse( uint8_t *pData, uint16_t dataLen );
	uint16_t GetResponseData( uint8_t *pDest, uint16_t destLen );

	void ClearResponse( void );

private:
	class CResponseElement
	{
	public:
		CResponseElement( uint8_t *pData, uint16_t dataLen )
		{
			m_pData = new uint8_t[dataLen];

			memcpy( m_pData, pData, dataLen );
			m_dataLen = dataLen;
		}

		~CResponseElement( )
		{
			if ( m_pData )
				delete [] m_pData;
		}

		uint8_t *GetData( void ) const { return m_pData; };
		uint16_t GetDataLength( void ) const { return m_dataLen; };

	public:
		CUtil::DLL_LINK( CResponseElement ) m_responseLink;

	private:
		uint8_t *m_pData;
		uint16_t m_dataLen;

	};

private:
	CUtil::DLL_LIST( CResponseElement, m_responseLink ) m_responseList;
	uint16_t m_responseLen;	
};

#endif // __RESPONSE_H__
