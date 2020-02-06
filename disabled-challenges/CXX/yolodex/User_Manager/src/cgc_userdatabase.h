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
#ifndef __USER_DATABASE_H__
#define __USER_DATABASE_H__

class CUserEntry
{
public:
    CUserEntry( const String &sUserName, const String &sPassword );
    ~CUserEntry( );

    const String &GetPassword( void ) const
    {
        return m_sPassword;
    }

    const String &GetUserName( void ) const
    {
        return m_sUserName;
    }

    void SetPassword( String sPassword )
    {
        m_sPassword = sPassword;
    }

    bool AddMessage( CUserMessage *pNewMessage );

    bool DeleteMessage( CUserMessage *pMessage );

    uint32_t GetMessageCount( void );
    uint32_t GetUnreadMessageCount( void );

    CUserMessage *GetFirstMessage( void );
    CUserMessage *GetNextMessage( CUserMessage *pCur );

    CUserMessage *GetFirstUnreadMessage( void );
    CUserMessage *GetLastUnreadMessage( void );
    CUserMessage *GetNextUnreadMessage( CUserMessage *pCur );

    CUserMessage *GetMessageByIndex( uint32_t index );

    void ClearUnreadMessages( void );

private:
    String m_sUserName;
    String m_sPassword;

    CUserMessage *m_pLastUnreadMessage;
    CDoubleQueue m_oMessageQueue;
};

class CUserDatabase
{
public:
    static const uint32_t MAX_USER_ENTRIES = 64;

public:
    CUserDatabase();
    ~CUserDatabase();

    bool CreateUser( const String &sUserName, const String &sPassword );

    CUserEntry *FindUserByName( const String &sUserName ) const;
    CUserEntry *GetUserForIndex( uint32_t idx ) const;

    bool DeleteUserByName( const String &sUserName );

    uint32_t GetUserCount( void ) const;


private:
    CUserEntry *m_userTable[MAX_USER_ENTRIES];
};

#endif // __USER_DATABASE_H__
