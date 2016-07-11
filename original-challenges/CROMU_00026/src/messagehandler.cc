/*

Author: Jason Williams <jdw@cromulence.com>

Copyright (c) 2014 Cromulence LLC

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

CMessageFragmentList::CFragmentData *CMessageFragmentList::GetFragmentForSequenceNumber( uint16_t sequenceNumber )
{
    CFragmentData *pCur;

    for ( pCur = (CFragmentData *)m_fragmentList.GetFirst(); pCur; pCur = (CFragmentData *)pCur->GetNext() )
    {
        if ( pCur->GetSequenceNumber() == sequenceNumber )
            return (pCur);
    }

    return (NULL);
}

uint32_t CMessageFragmentList::CFragmentData::GetAssembledMessageSize( void ) const
{
    // Assemble size
    uint32_t messageFullSize = 0;
    for ( uint32_t i = 0; i < m_fragmentTotalCount; i++ )
    {
        if ( m_pMessageFragments[i] )
            messageFullSize += m_pMessageFragments[i]->GetDataLength( );
    }

    return (messageFullSize);
}

CFullMessage *CMessageFragmentList::CFragmentData::AssembleFragments( void ) const
{
    // Allocate buffer for full message
    uint8_t *pFullMessageData = new uint8_t[GetAssembledMessageSize()];

    uint32_t fullMessagePos = 0;

    // BUG:: Message full size was calculated using only up to m_fragmentCount where as this will count fragments that were ABOVE the last fragment number
#ifdef PATCHED
    for ( uint32_t i = 0; i < m_fragmentTotalCount; i++ )
#else
    for ( uint32_t i = 0; i < MAX_MESSAGE_FRAGMENTS; i++ )
#endif
    {
        if ( m_pMessageFragments[i] )
        {
            // Copy data
            memcpy( pFullMessageData+fullMessagePos, (void *)m_pMessageFragments[i]->GetData(), m_pMessageFragments[i]->GetDataLength() );

            // Update full message position
            fullMessagePos += m_pMessageFragments[i]->GetDataLength();
        }
    }

    // In this case don't pass true to third argument of constructor (so it will not copy full data)
    CFullMessage *pNewFullMessage = new CFullMessage( pFullMessageData, fullMessagePos );

    return (pNewFullMessage);
}

bool CMessageFragmentList::AddFragment( CMessagePacket *pPacket, CFullMessage *&pNewFullMessage )
{
    // This will be set if all the fragments are assembled
    pNewFullMessage = NULL;

    // Check for NULL -- false means a new message has not been assembled yet
    if ( pPacket == NULL )
        return (false);

    // Add message into circular list
    if ( m_fragmentCount >= MESSAGE_FRAGMENT_LIST_MAX )
        return (false);

    if ( !pPacket->IsFragmented() )
        return (false);

    // Get sequence number
    uint16_t currentSeqNumber = pPacket->GetSequenceNumber();

    CFragmentData *pOtherFragments = GetFragmentForSequenceNumber( currentSeqNumber );
    if ( pOtherFragments == NULL )
    {
        // No other fragments -- lets add a new one at the tail of the list
        CFragmentData *pNewFragmentData = new CFragmentData( currentSeqNumber );

        if ( pPacket->IsLastFragment() )
        {
            // Last fragment -- set the total count
            pNewFragmentData->SetTotalFragmentCount( pPacket->GetFragmentNumber()+1 );
        }

        pNewFragmentData->AddFragmentData( pPacket, pPacket->GetFragmentNumber() );

        // Check if all fragments are available (this is a special case where only 1 packet is received that is the last fragment...)
        if ( pNewFragmentData->HasAllFragments() )
        {
            // Assemble message
            pNewFullMessage = pNewFragmentData->AssembleFragments( );

            // Free memory
            delete pNewFragmentData;
        }
        else
        {
            // More fragments needed -- add it to the fragment list
            m_fragmentList.InsertTail( pNewFragmentData );

            // Update the list tracking the number of sequence numbers we are tracking in fragments
            m_fragmentCount++;
        }
    }
    else
    {
        // Other fragments present -- add onto the list (add possibly assemble)

        if ( pPacket->IsLastFragment() )
        {
            // Last fragment -- set total count
            pOtherFragments->SetTotalFragmentCount( pPacket->GetFragmentNumber()+1 );
        }

        pOtherFragments->AddFragmentData( pPacket, pPacket->GetFragmentNumber() );

        if ( pOtherFragments->HasAllFragments() )
        {
            // Build a new assembled message, unlink from fragment list, and delete the fragment data
            pNewFullMessage = pOtherFragments->AssembleFragments( );

            // Remove from fragment list
            m_fragmentList.Unlink( pOtherFragments );

            // Free memory
            delete pOtherFragments;

            // Keep track of fragment count in list (to limit this list size)
            m_fragmentCount--;
        }
    }

    return (true);
}

CFullMessage::CFullMessage( uint8_t *pMessageData, uint32_t messageLength, bool bDataCopy )
{
    if ( bDataCopy )
    {
        m_pMessageData = new uint8_t[messageLength];

        memcpy( m_pMessageData, pMessageData, messageLength );
    }
    else
        m_pMessageData = pMessageData;

    m_messageLen = messageLength;
}

CFullMessage::~CFullMessage( )
{
    if ( m_pMessageData )
        delete m_pMessageData;
}

CMessageHandler::CMessageHandler( )
{

}

CMessageHandler::~CMessageHandler( )
{

}

void CMessageHandler::ReceivePacket( CMessagePacket *pPacket )
{
    if ( pPacket == NULL )
        return;

    if ( pPacket->IsFragmented() )
    {
        CFullMessage *pFullMessage = NULL;

        if ( !m_messageFragmentList.AddFragment( pPacket, pFullMessage ) )
        {
            // Fragment reassembly failed -- drop message
            delete pPacket;

            return;
        }

        if ( pFullMessage )
        {
            // Add full message into list for processing
            m_fullMessageList.InsertTail( pFullMessage );
        }
    }
    else
    {
        // Generate a full message
        CFullMessage *pNewFullMessage = new CFullMessage( (uint8_t *)pPacket->GetData(), pPacket->GetDataLength(), true );

        // Delete packet
        delete pPacket;

        m_fullMessageList.InsertTail( pNewFullMessage );
    }
}

bool CMessageHandler::IsMsgAvailable( void )
{
    return (m_fullMessageList.GetFirst() != NULL);
}

CFullMessage *CMessageHandler::PopFirstMessage( void )
{
    if ( !IsMsgAvailable() )
        return (NULL);

    CFullMessage *pFirstMsg = (CFullMessage *)m_fullMessageList.GetFirst();

    m_fullMessageList.Unlink( pFirstMsg );

    return (pFirstMsg);
}
