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
#include <stdio.h>
#include <stdlib.h>
}

#include "lanbus.h"

CLANMessage::CLANMessage( uint8_t srcID, uint8_t destID, uint8_t *pMessageData, uint16_t messageLen )
	: m_srcID( srcID ), m_destID( destID ), m_messageLen( messageLen )
{
	m_pMessageData = new uint8_t[m_messageLen];

	memcpy( m_pMessageData, pMessageData, messageLen );
}

CLANMessage::~CLANMessage( )
{
	if ( m_pMessageData )
		delete [] m_pMessageData;

	m_pMessageData = NULL;
}

CLANBus::CLANBus( )
{

}

CLANBus::~CLANBus( )
{

}

bool CLANBus::SendMessage( uint8_t srcID, uint8_t destID, uint8_t *pMessageData, uint16_t messageLen )
{
	CLANMessage *pNewMessage = new CLANMessage( srcID, destID, pMessageData, messageLen );

	m_oSentList.AddLast( pNewMessage );

	return (true);
}

bool CLANBus::InjectSimulationMessage( uint8_t srcID, uint8_t destID, uint8_t *pMessageData, uint16_t messageLen )
{
	CLANMessage *pNewMessage = new CLANMessage( srcID, destID, pMessageData, messageLen );

	m_oReceiveList.AddLast( pNewMessage );

	return (true);
}

CLANMessage *CLANBus::RecvMessage( uint8_t *pDestIDList, uint8_t idCount, CLANMessage *pLastMessage )
{
	CLANMessage *pCur;
	bool bFound = false;

	// Check for message
	if ( pLastMessage == NULL )
		pCur = m_oReceiveList.GetFirst();
	else
		pCur = m_oReceiveList.GetNext( pLastMessage );

	for ( ; pCur; pCur = m_oReceiveList.GetNext( pCur ) )
	{
		for ( uint8_t i = 0; i < idCount; i++ )
		{
			if ( pCur->GetDestID() == pDestIDList[i] )
			{
				bFound = true;
				break;
			}
		}

		if ( bFound )
			break;
	}

	if ( bFound )
		return (pCur);
	else
		return (NULL);
}

void CLANBus::NextTick( void )
{
	// Clear out old messages that are already parsed
	m_oReceiveList.DeleteAll();

	// Move sent messages to messages to be received
	CLANMessage *pMessage;

	// Move them preserving order
	while ( (pMessage = m_oSentList.GetFirst()) )
	{
		pMessage->m_lanbusLink.Unlink();

		m_oReceiveList.AddLast( pMessage );
	}
}
