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
#ifndef __MESSAGE_HANDLER_H__
#define __MESSAGE_HANDLER_H__

class CFullMessage;

class CMessageFragmentList
{
public:
    CMessageFragmentList( void )
    {
        m_fragmentCount = 0;
    }

    ~CMessageFragmentList( )
    {
        m_fragmentList.DeleteAll();
    }

    bool AddFragment( CMessagePacket *pPacket, CFullMessage *&pNewFullMessage );

private:
    class CFragmentData : public CDoubleListElement
    {
    public:
        CFragmentData( uint16_t sequenceNumber ) : CDoubleListElement( ), m_sequenceNumber( sequenceNumber )
        {
            m_fragmentTotalCount = 0;

            for ( uint16_t i = 0; i < MAX_MESSAGE_FRAGMENTS; i++ )
                m_pMessageFragments[i] = NULL;
        }

        ~CFragmentData( )
        {
            for ( uint16_t i = 0; i < MAX_MESSAGE_FRAGMENTS; i++ )
            {
                if ( m_pMessageFragments[i] )
                    delete m_pMessageFragments[i];
            }
        }

        uint16_t GetSequenceNumber( void ) const { return m_sequenceNumber; };

        bool SetTotalFragmentCount( uint8_t fragmentTotalCount )
        {
            if ( fragmentTotalCount > MAX_MESSAGE_FRAGMENTS )
                return (false);

            m_fragmentTotalCount = fragmentTotalCount;

            return (true);
        }

        bool AddFragmentData( CMessagePacket *pPacket, uint8_t fragmentIndex )
        {
            if ( fragmentIndex >= MAX_MESSAGE_FRAGMENTS )
                return (false);

            if ( m_pMessageFragments[fragmentIndex] != NULL )
                return (false);     // Don't add in fragments we already have??

            m_pMessageFragments[fragmentIndex] = pPacket;

            return (true);
        }

        bool HasAllFragments( void ) const
        {
            uint32_t fragmentCount = 0;

            if ( m_fragmentTotalCount == 0 )
                return (false);

            for ( uint32_t i = 0; i < m_fragmentTotalCount; i++ )
            {
                if ( m_pMessageFragments[i] )
                    fragmentCount++;
            }

            return (fragmentCount == m_fragmentTotalCount);
        }

        uint32_t GetAssembledMessageSize( void ) const;
        CFullMessage *AssembleFragments( void ) const;

    private:
        CMessagePacket *m_pMessageFragments[MAX_MESSAGE_FRAGMENTS];
        uint8_t m_fragmentTotalCount;
        uint16_t m_sequenceNumber;
    };

    CFragmentData *GetFragmentForSequenceNumber( uint16_t sequenceNumber );

private:
    uint32_t m_fragmentCount;
    CDoubleList m_fragmentList;
};

class CFullMessage : public CDoubleListElement
{
public:
    CFullMessage( uint8_t *pMessageData, uint32_t messageLen, bool bCopyData = false );
    ~CFullMessage( );

    uint8_t *GetData( void ) const { return m_pMessageData; };
    uint32_t GetLength( void ) const { return m_messageLen; };

private:
    uint8_t *m_pMessageData;
    uint32_t m_messageLen;
};

// Receives message packets and assembles them into parsed messages
// to send to the message renderer
class CMessageHandler
{
public:
    CMessageHandler();
    ~CMessageHandler();

    void ReceivePacket( CMessagePacket *pPacket );

    bool IsMsgAvailable( void );

    CFullMessage *PopFirstMessage( void );

private:
    CMessageFragmentList m_messageFragmentList;
    CDoubleList m_fullMessageList;
};

#endif // __MESSAGE_HANDLER_H__
