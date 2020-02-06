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
#ifndef __MESSAGE_PACKET_H__
#define __MESSAGE_PACKET_H__

class CMessagePacket
{
public:
    static const uint8_t FRAGMENTED_BIT = 0x0;         // Indicates fragmented packet
    static const uint8_t LAST_FRAGMENT_BIT = 0x1;      // Indicates last fragment of fragmented packets
    static const uint8_t LARGE_CHECKSUM_BIT = 0x2;     // Indicates large checksum (32-bit instead of 16-bit)

    static const uint8_t HEADER_IDENTIFIER_BITS = 0xF0;       // Validates the packet header
    static const uint8_t HEADER_IDENTIFIER_VALUE = 0xB0;      // Validates the packet header
    static const uint8_t HEADER_PARITY_BIT = 0x3;             // Validates the packet header
    static const uint8_t HEADER_PARITY_BIT_MASK = 0xF7;       // Mask for parity bit analysis

    static const uint16_t MESSAGE_BYTE_ALIGN_SEQUENCE = 0xC3AC;    // 1100 0011 1010 1100
    static const uint16_t PREAMBLE_LOCK_COUNT = 15;                // Lock after 15 out of 32 bits have been received

public:
    CMessagePacket( uint8_t hdr, uint8_t len );
    ~CMessagePacket( );

    static CMessagePacket *ParseStream( CDataStream *pRxData );

    const uint8_t *GetData( void )
    {
        if ( IsFragmented() && m_messageHeader.len >= 2 )
            return (m_pMessageData+2);
        else
            return (m_pMessageData);
    }

    uint8_t GetDataLength( void ) const
    {
        if ( IsFragmented() )
        {
            if ( m_messageHeader.len >= 2 )
                return (m_messageHeader.len - 2);
            else
                return (0);
        }
        else
            return (m_messageHeader.len);
    }

    uint16_t GetSequenceNumber( void ) const
    {
        if ( IsFragmented() && m_messageHeader.len >= 2 )
            return (*((uint16_t *)m_pMessageData) >> 4);
        else
            return (0);
    }

    uint8_t GetFragmentNumber( void ) const
    {
        if ( IsFragmented() && m_messageHeader.len >= 2 )
            return (uint8_t)(*((uint16_t *)m_pMessageData) & 0xF);
        else
            return (0);
    }

    uint8_t GetHeader( void ) const
    {
        return (m_messageHeader.hdr);
    }

    bool IsFragmented( void ) const
    {
        if ( m_messageHeader.hdr & (1<<FRAGMENTED_BIT) )
            return (true);
        else
            return (false);
    }

    bool IsLastFragment( void ) const
    {
        if ( m_messageHeader.hdr & (1<<LAST_FRAGMENT_BIT) )
            return (true);
        else
            return (false);
    }

    bool IsLargeChecksum( void ) const
    {
        if ( m_messageHeader.hdr & (1<<LARGE_CHECKSUM_BIT) )
            return (true);
        else
            return (false);
    }

private:
    static uint8_t WaitForPreambleLock( CDataStream *pRxStream );

    void SetDataByteAt( uint8_t data_pos, uint8_t value );

    void SetChecksum32( uint32_t new_checksum )
    {
        m_messageHeader.check.checksum32 = new_checksum;
    }

    void SetChecksum16( uint16_t new_checksum )
    {
        m_messageHeader.check.checksum16 = new_checksum;
    }

private:
    typedef struct
    {
        uint8_t hdr;
        uint8_t len;
        union
        {
            uint32_t checksum32;
            uint16_t checksum16;
        } check;
    } tMessageHeader;

    tMessageHeader m_messageHeader;
    uint8_t *m_pMessageData;
};

#endif // __MESSAGE_PACKET_H__
