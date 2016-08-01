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

CUserEntry::CUserEntry( const String &sUserName, const String &sPassword )
    : m_pLastUnreadMessage( NULL ), m_sUserName( sUserName ), m_sPassword( sPassword )
{

}

CUserEntry::~CUserEntry( )
{

}

bool CUserEntry::DeleteMessage( CUserMessage *pCur )
{
    if ( !pCur )
        return (false);

#if PATCHED
    if ( m_pLastUnreadMessage == pCur )
        m_pLastUnreadMessage = (CUserMessage *)m_oMessageQueue.GetPrev( pCur );

    m_oMessageQueue.DeleteItem( pCur );

#else
    // BUG:: Update the last unread message if we need to
    m_oMessageQueue.DeleteItem( pCur );
#endif

    return (true);
}

CUserMessage *CUserEntry::GetFirstMessage( void )
{
    return (CUserMessage *)(m_oMessageQueue.GetFirst());
}

CUserMessage *CUserEntry::GetNextMessage( CUserMessage *pCur )
{
    if ( !pCur )
        return (NULL);

    return (CUserMessage *)(m_oMessageQueue.GetNext( pCur ));
}

CUserMessage *CUserEntry::GetFirstUnreadMessage( void )
{
    if ( m_pLastUnreadMessage == NULL )
        return (NULL);

    return (CUserMessage *)(m_oMessageQueue.GetFirst());
}

CUserMessage *CUserEntry::GetLastUnreadMessage( void )
{
    return (m_pLastUnreadMessage);
}

CUserMessage *CUserEntry::GetNextUnreadMessage( CUserMessage *pCur )
{
    if ( m_pLastUnreadMessage == NULL )
        return (NULL);

    if ( pCur == m_pLastUnreadMessage )
        return (NULL);

    return (CUserMessage *)(m_oMessageQueue.GetNext( pCur ));
}

void CUserEntry::ClearUnreadMessages( void )
{
    m_pLastUnreadMessage = NULL;
}

bool CUserEntry::AddMessage( CUserMessage *pNewMessage )
{
    if ( !pNewMessage )
        return (false);

    if ( m_pLastUnreadMessage == NULL )
        m_pLastUnreadMessage = pNewMessage;

    m_oMessageQueue.PushFront( pNewMessage );

    return (true);
}

uint32_t CUserEntry::GetMessageCount( void )
{
    return (m_oMessageQueue.GetCount());
}

uint32_t CUserEntry::GetUnreadMessageCount( void )
{
    if ( m_pLastUnreadMessage == NULL )
        return (0);

    uint32_t msgCount = 0;

    for ( CUserMessage *pCur = (CUserMessage *)m_oMessageQueue.GetFirst(); pCur; pCur = (CUserMessage *)m_oMessageQueue.GetNext( pCur ) )
    {
        msgCount++;

        if ( pCur == m_pLastUnreadMessage )
            break;
    }

    return (msgCount);
}

CUserMessage *CUserEntry::GetMessageByIndex( uint32_t idx )
{
    uint32_t cur_idx = 0;

    for ( CUserMessage *pCur = (CUserMessage *)m_oMessageQueue.GetFirst(); pCur; pCur = (CUserMessage *)m_oMessageQueue.GetNext( pCur ) )
    {
        if ( cur_idx == idx )
            return (pCur);

        cur_idx++;
    }

    return (NULL);
}

CUserDatabase::CUserDatabase()
{
    for ( uint32_t idx = 0; idx < MAX_USER_ENTRIES; idx++ )
    {
        m_userTable[idx] = NULL;
    }
}

CUserDatabase::~CUserDatabase()
{
    for ( uint32_t idx = 0; idx < MAX_USER_ENTRIES; idx++ )
    {
        if ( m_userTable[idx] )
            delete m_userTable[idx];
    }
}

bool CUserDatabase::CreateUser( const String &sUserName, const String &sUserPassword )
{
    // Do we have another user???
    if ( FindUserByName( sUserName ) )
        return (false);

    if ( GetUserCount() >= MAX_USER_ENTRIES )
        return (false);

    // Add User
    for ( uint32_t idx = 0; idx < MAX_USER_ENTRIES; idx++ )
    {
        if ( m_userTable[idx] == NULL )
        {
            m_userTable[idx] = new CUserEntry( sUserName, sUserPassword );

            return (true);
        }
    }

    return (false);
}

CUserEntry *CUserDatabase::FindUserByName( const String &sUserName ) const
{
    for ( uint32_t idx = 0; idx < MAX_USER_ENTRIES; idx++ )
    {
        if ( m_userTable[idx] )
        {
            if ( m_userTable[idx]->GetUserName() == sUserName )
                return (m_userTable[idx]);
        }
    }

    return (NULL);
}

CUserEntry *CUserDatabase::GetUserForIndex( uint32_t idx ) const
{
    uint32_t cur_idx = 0;
    for ( uint32_t cur = 0; cur < MAX_USER_ENTRIES; cur++ )
    {
        if ( m_userTable[cur] )
        {
            if ( idx == cur_idx )
                return (m_userTable[cur]);

            cur_idx++;
        }
    }

    return (NULL);
}

bool CUserDatabase::DeleteUserByName( const String &sUserName )
{
    uint32_t idx;

    for ( idx = 0; idx < MAX_USER_ENTRIES; idx++ )
    {
        if ( m_userTable[idx] )
        {
            if ( m_userTable[idx]->GetUserName() == sUserName )
            {
                delete m_userTable[idx];
                m_userTable[idx] = NULL;

                return (true);
            }
        }
    }

    return (false);
}

uint32_t CUserDatabase::GetUserCount( void ) const
{
    uint32_t userCount = 0;
    for ( uint32_t idx = 0; idx < MAX_USER_ENTRIES; idx++ )
    {
        if ( m_userTable[idx] )
            userCount++;
    }

    return (userCount);
}
