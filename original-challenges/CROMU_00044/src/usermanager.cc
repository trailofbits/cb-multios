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

CUserManager::CUserManager()
{
    m_sAdminPassword = "$admin$77";
}

CUserManager::~CUserManager()
{

}

void CUserManager::Run( void )
{
    // Action string
    String sAction;

    // Print banner
    printf( "User Manager Console:\n" );

    // Enter command loop
    bool bRunning = true;
    do
    {
        // Main console
        printf( "1) Create User\n" );
        printf( "2) User Login\n" );
        printf( "3) Admin Login\n" );
        printf( "4) Exit\n" );

        // Get user input
        ReadLine( sAction );

        int32_t actionIntValue;

        // Get action value as an integer
        if ( !sAction.ToInteger( actionIntValue ) )
            actionIntValue = -1;

        // Perform action
        switch ( actionIntValue )
        {
        case 1:     // Create User
            bRunning = RunCreateUser();
            break;

        case 2:     // User Login
            bRunning = RunUserLogin();
            break;

        case 3:     // Admin Login
            bRunning = RunAdminLogin();
            break;

        case 4:     // Exit
            bRunning = false;
            break;

        default:    // Invalid entry
            printf( "Invalid choice\n" );
            break;
        }
    } while ( bRunning );

    // Exit banner
    printf( "Exiting\n" );
}

bool CUserManager::RunCreateUser( void )
{
    String sUserName;
    String sPassword;

    bool bGoodUserName = true;
    do
    {
        printf( "Username: " );

        ReadLine( sUserName );

        if ( sUserName.length() > MAX_USERNAME_LENGTH )
        {
            printf( "Username too long, only @d characters allowed.\n", MAX_USERNAME_LENGTH );
            bGoodUserName = false;
        }
        else
            bGoodUserName = true;

    } while ( !bGoodUserName );

    bool bGoodPassword = false;
    do
    {
        printf( "Password: " );
        ReadLine( sPassword );

        if ( sPassword.length() > MAX_PASSWORD_LENGTH )
        {
            printf( "Password too long, only @d characters allowed.\n", MAX_PASSWORD_LENGTH );
            bGoodPassword = false;
        }
        else
            bGoodPassword = true;

    } while ( !bGoodPassword );

    if ( !m_userDB.CreateUser( sUserName, sPassword ) )
        printf( "Failed to create user -- user already exists.\n" );
    else
        printf( "User created successfully.\n" );

    // True -- indicates continue running command loop
    return (true);
}

bool CUserManager::RunUserLogin( void )
{
    String sUserName;
    String sPassword;
    String sAction;

    printf( "Enter Username: " );

    ReadLine( sUserName );

    printf( "Enter Password: " );

    ReadLine( sPassword );

    // Verify user credentials
    CUserEntry *pUserData = m_userDB.FindUserByName( sUserName );

    if ( !pUserData )
    {
        printf( "Login failed. Invalid username or password.\n" );
        return (true);
    }

    if ( pUserData->GetPassword() != sPassword )
    {
        printf( "Login failed. Invalid username or password.\n" );
        return (true);
    }

    printf( "Login success.\n" );

    bool bUserLoggedIn = true;
    do
    {
        printf( "1) Send Message\n" );
        printf( "2) Read Message\n" );
        printf( "3) List Messages\n" );
        printf( "4) Delete Message\n" );
        printf( "5) Logout\n" );
        printf( "6) Exit\n" );

        ReadLine( sAction );

        int32_t actionIntValue;

        // Get action value as an integer
        if ( !sAction.ToInteger( actionIntValue ) )
            actionIntValue = -1;

        // Perform action
        switch ( actionIntValue )
        {
        case 1: // Send message
            DoUserSendMessage( pUserData );
            break;

        case 2: // Read messages
            DoUserReadMessages( pUserData );
            break;

        case 3: // List messages
            DoUserListMessages( pUserData );
            break;

        case 4: // Delete message
            DoUserDeleteMessage( pUserData );
            break;

        case 5: // Log out this user
            bUserLoggedIn = false;
            break;

        case 6: // Exit application
            return (false);
            break;

        default:
            printf( "Invalid command\n" );
            break;
        }

    } while ( bUserLoggedIn );

    printf( "Logged out.\n" );

    // True -- indicates continue running command loop
    return (true);
}

bool CUserManager::RunAdminLogin( void )
{
    String sAction;
    String sAdminPassword;

    printf( "Admin Password: " );

    ReadLine( sAdminPassword );

    if ( sAdminPassword != m_sAdminPassword )
    {
        printf( "Invalid Password.\n" );
        return (true);
    }

    bool bExitAdmin = false;
    do
    {
        printf( "Admin Commands:\n" );
        printf( "1) List Users\n" );
        printf( "2) Delete User\n" );
        printf( "3) Change User Password\n" );
        printf( "4) Logout\n" );

        // Get user input
        ReadLine( sAction );

        int32_t actionIntValue;

        // Get action value as an integer
        if ( !sAction.ToInteger( actionIntValue ) )
            actionIntValue = -1;

        // Perform action
        switch ( actionIntValue )
        {
        case 1:
            DoAdminListUsers();
            break;

        case 2:
            DoAdminDeleteUser();
            break;

        case 3:
            DoAdminChangePassword();
            break;

        case 4:
            printf( "Logging out\n" );
            bExitAdmin = true;
            break;
        }
    } while ( !bExitAdmin );

    // True -- indicates continue running command loop
    return (true);
}

void CUserManager::DoAdminListUsers( void )
{
    printf( "Listing users in database:\n" );

    uint32_t userIdx;
    uint32_t userCount = m_userDB.GetUserCount();

    for ( userIdx = 0; userIdx < userCount; userIdx++ )
    {
        CUserEntry *pUserData = m_userDB.GetUserForIndex( userIdx );

        printf( "@d: @s\n", userIdx, pUserData->GetUserName().c_str() );
    }
}

void CUserManager::DoAdminDeleteUser( void )
{
    String sUserName;

    printf( "Username to delete: " );

    ReadLine( sUserName );

    if ( m_userDB.DeleteUserByName( sUserName ) )
        printf( "User deleted.\n" );
    else
        printf( "User not found, failed to delete.\n" );
}

void CUserManager::DoAdminChangePassword( void )
{
    String sUserName;
    String sPassword;

    printf( "Username to change password: " );

    ReadLine( sUserName );

    CUserEntry *pUserData = m_userDB.FindUserByName( sUserName );

    if ( pUserData == NULL )
    {
        printf( "User not found in database.\n" );
        return;
    }

    printf( "New password: " );

    ReadLine( sPassword );

    if ( sPassword.length() > MAX_PASSWORD_LENGTH )
    {
        printf( "Password too long. Failed to change password.\n" );
        return;
    }

    // Now set users password
    pUserData->SetPassword( sPassword );

    printf( "Password set for user.\n" );

    return;
}


void CUserManager::DoUserSendMessage( CUserEntry *pUser )
{
    String sUserName;
    String sMessage;

    printf( "Username to send to: " );

    ReadLine( sUserName );

    CUserEntry *pUserData = m_userDB.FindUserByName( sUserName );

    if ( pUserData == NULL )
    {
        printf( "User not found.\n" );
        return;
    }

    printf( "Enter Message: " );

    ReadLine( sMessage );

    if ( sMessage.length() > 128 )
    {
        printf( "Message too long, truncating.\n" );
        sMessage.Trim( 128 );
    }

    if ( !pUserData->AddMessage( new CUserMessage( pUser->GetUserName(), sMessage ) ) )
        printf( "Message not sent.\n" );
    else
        printf( "Message sent.\n" );
}

void CUserManager::DoUserReadMessages( CUserEntry *pUser )
{
    if ( pUser->GetMessageCount() == 0 )
    {
        printf( "No messages.\n" );
        return;
    }

    // Print new messages
    if ( pUser->GetUnreadMessageCount() > 0 )
    {
        CUserMessage *pCur;

        printf( "@d unread messages available. Last unread message:\n", pUser->GetUnreadMessageCount() );

        // Display last unread message
        pCur = pUser->GetLastUnreadMessage();

        printf( "From: @s\n", pCur->GetFrom().c_str() );
        printf( "Message: @s\n", pCur->GetMessage().c_str() );

        pUser->ClearUnreadMessages( );
    }

    printf( "@d total messages available, enter number to read: ", pUser->GetMessageCount() );

    String sAction;

    int32_t messageNumber;

    ReadLine( sAction );

    if ( !sAction.ToInteger( messageNumber ) )
    {
        printf( "Invalid message number.\n" );
        return;
    }

    if ( messageNumber < 0 || messageNumber >= pUser->GetMessageCount() )
    {
        printf( "Invalid message number.\n" );
        return;
    }

    CUserMessage *pCurMessage = pUser->GetMessageByIndex( messageNumber );

    if ( !pCurMessage )
        return;

    printf( "Message @d:\n", messageNumber );
    printf( "From: @s\n", pCurMessage->GetFrom().c_str() );
    printf( "Message: @s\n", pCurMessage->GetMessage().c_str() );

    return;
}

void CUserManager::DoUserListMessages( CUserEntry *pUser )
{
    if ( pUser->GetMessageCount() == 0 )
    {
        printf( "No messages.\n" );
        return;
    }

    printf( "Listing @d messages:\n", pUser->GetMessageCount() );

    uint32_t idx = 0;
    for ( CUserMessage *pCur = pUser->GetFirstMessage(); pCur; pCur = pUser->GetNextMessage( pCur ) )
    {
        printf( "Message @d:\n", idx );
        printf( "From: @s\n", pCur->GetFrom().c_str() );
        printf( "Message: @s\n", pCur->GetMessage().c_str() );

        idx++;
    }
}

void CUserManager::DoUserDeleteMessage( CUserEntry *pUser )
{
    if ( pUser->GetMessageCount() == 0 )
    {
        printf( "No messages to delete.\n" );
        return;
    }

    printf( "@d messages available. Enter number to delete: ", pUser->GetMessageCount() );

    String sAction;

    int32_t messageNumber;

    ReadLine( sAction );

    if ( !sAction.ToInteger( messageNumber ) )
    {
        printf( "Invalid message number.\n" );
        return;
    }

    if ( messageNumber < 0 || messageNumber >= pUser->GetMessageCount() )
    {
        printf( "Invalid message number.\n" );
        return;
    }

    CUserMessage *pCurMessage = pUser->GetMessageByIndex( messageNumber );

    if ( !pUser->DeleteMessage( pCurMessage ) )
        printf( "Failed to delete message.\n" );
    else
        printf( "Message deleted.\n" );
}
