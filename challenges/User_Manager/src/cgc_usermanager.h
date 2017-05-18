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
#ifndef __USER_MANAGER_H__
#define __USER_MANAGER_H__

class CUserManager
{
public:
    static const uint32_t MAX_USERNAME_LENGTH = 12;
    static const uint32_t MAX_PASSWORD_LENGTH = 12;

public:
    CUserManager();
    ~CUserManager();

    void Run( void );

private:
    bool RunCreateUser( void );
    bool RunUserLogin( void );
    bool RunAdminLogin( void );

    void DoAdminListUsers( void );
    void DoAdminDeleteUser( void );
    void DoAdminChangePassword( void );

    void DoUserSendMessage( CUserEntry *pUser );
    void DoUserReadMessages( CUserEntry *pUser );
    void DoUserListMessages( CUserEntry *pUser );
    void DoUserDeleteMessage( CUserEntry *pUser );
    void DoUserChangePassword( CUserEntry *pUser );

private:
    String m_sAdminPassword;
    CUserDatabase m_userDB;
};

#endif // __USER_MANAGER_H__
