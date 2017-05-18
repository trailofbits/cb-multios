#!/usr/bin/env python

from generator.actions import Actions
import random
from struct import pack

class Message():
    def __init__(self, from_user, message ):
        self.from_user = from_user
        self.message = message

class User():
    def __init__(self, username, password):
        self.username = username
        self.password = password
        self.messages = []
        self.last_unread_message = None

    def DeleteMessageNumber(self, message_number):
        self.messages.remove( self.GetMessageNumber( message_number ))

    def GetMessageNumber(self, message_number):
        cur_pos = 0

        for message in self.messages:
            if ( message_number == cur_pos ):
                return message

            cur_pos += 1

        return None

    def AddMessage(self, from_user, new_message ):
        new_message = Message( from_user, new_message )

        self.messages.insert( 0, new_message )
        if ( self.last_unread_message is None ):
            self.last_unread_message = new_message

    def HasUnreadMessages(self):
        if ( self.last_unread_message is not None ):
            return True
        else:
            return False

    def GetUnreadMessages(self):
        unread_list = list()

        for message in self.messages:
            unread_list.append( message )
            if ( message == self.last_unread_message ):
                break

        return unread_list

    def GetMessageList(self):
        return self.messages

    def ClearUnreadMessages(self):
        self.last_unread_message = None

    def GetMessageCount(self):
        return len(self.messages)

class UserManager(Actions):

    def GetUserCount(self):
        count = 0
        for i in range(64):
            if ( self.users[i] is not None ):
                count += 1

        return count

    def GetRandomUser(self):
        user_number = random.randint( 0, self.GetUserCount()-1 )

        cur_number = 0
        for i in range(64):
            if ( self.users[i] is not None ):
                if ( user_number == cur_number ):
                    return self.users[i]

                cur_number += 1

        return None

    def FindUserByName(self, search_user_name):
        for i in range(64):
            if ( self.users[i] is not None ):
                if ( self.users[i].username == search_user_name ):
                    return self.users[i]

        return None

    def AddUser(self, username, password ):
        for i in range(64):
            if ( self.users[i] is None ):
                self.users[i] = User( username, password )
                return

    def DeleteUser(self, user_to_delete ):
        for i in range(64):
            if ( self.users[i] == user_to_delete ):
                self.users[i] = None
                return

    def LoginUser(self, user):
        self.logged_in_user = user

    def LogoutUser(self):
        self.logged_in_user = None

    def start(self):
        self.logged_in_user = None
        self.users = list()

        for i in range(64):
            self.users.append( None )

        self.read(delim='\n', expect='User Manager Console:\n')


    def read_main_menu_text(self):
        self.read(delim='\n', expect='1) Create User\n')
        self.read(delim='\n', expect='2) User Login\n')
        self.read(delim='\n', expect='3) Admin Login\n')
        self.read(delim='\n', expect='4) Exit\n')

    def menu(self):
        self.read_main_menu_text()
        pass

    def exit(self):
        self.write('4\n')
        self.read(delim='\n', expect='Exiting\n')

    def user_manager_create_user(self):
        self.write('1\n')
        self.read(delim=': ', expect='Username: ')

        new_username = ''.join(random.choice('abcdefghijklmnopqrstuvwxyz') for _ in range(10))

        self.write(new_username + '\n')

        self.read( delim=': ', expect='Password: ' )

        new_password = ''.join(random.choice('abcdefghijklmnopqrstuvwxyz') for _ in range(10))

        self.write(new_password + '\n')

        if ( self.GetUserCount() >= 64 ):
            self.read(delim='\n', expect='Failed to create user -- user already exists.\n' )
            return

        if ( self.FindUserByName( new_username ) is not None ):
            self.read(delim='\n', expect='Failed to create user -- user already exists.\n' )
            return

        self.AddUser( new_username, new_password )
        self.read(delim='\n', expect='User created successfully.\n' )

    def admin_login(self):
        self.write('3\n')
        self.read(delim=': ', expect='Admin Password: ' )

    def admin_bad_login(self):
        bad_password = ''.join(random.choice('abcdefghijklmnopqrstuvwxyz') for _ in range(10))

        self.write( bad_password + '\n' )

        self.read( delim='\n', expect='Invalid Password.\n' )

    def admin_good_login(self):
        good_password = '$admin$77'

        self.write( good_password + '\n' )

    def admin_console(self):
        self.read( delim='\n', expect='Admin Commands:\n' )
        self.read( delim='\n', expect='1) List Users\n' )
        self.read( delim='\n', expect='2) Delete User\n' )
        self.read( delim='\n', expect='3) Change User Password\n' )
        self.read( delim='\n', expect='4) Logout\n' )

    def admin_logout(self):
        self.write( '4\n' )

        self.read( delim='\n', expect='Logging out\n' )

    def admin_list_users(self):
        self.write( '1\n' )

        self.read( delim='\n', expect='Listing users in database:\n' )

        cur_pos = 0
        for i in range(64):
            if ( self.users[i] is not None ):
                read_line = "%d: %s\n" % (cur_pos, self.users[i].username)
                self.read( delim='\n', expect=read_line )

                cur_pos += 1

    def admin_delete_user(self):
        self.write( '2\n' )

        self.read( delim=': ', expect='Username to delete: ' )

        if ( self.GetUserCount() == 0 or random.randint( 0, 10 ) == 0):
            # Do bad username
            bad_username = "1" + ''.join(random.choice('abcdefghijklmnop') for _ in range(10))

            self.write( bad_username + '\n' )

            self.read( delim='\n', expect='User not found, failed to delete.\n' )

        else:
            user_to_delete = self.GetRandomUser()

            self.write( user_to_delete.username + '\n' )

            self.read( delim='\n', expect='User deleted.' )

            self.DeleteUser( user_to_delete )

    def admin_change_user_password(self):
        self.write( '3\n' )

        self.read( delim=': ', expect='Username to change password: ' )

        if ( self.GetUserCount() == 0 or random.randint( 0, 10 ) == 0 ):
            # Do bad username
            bad_username = "1" + ''.join(random.choice('abcdefghijklmnop') for _ in range(10))

            self.write( bad_username + '\n' )

            self.read( delim='\n', expect='User not found in database.\n' )

        else:
            user_to_change_password = self.GetRandomUser()

            self.write( user_to_change_password.username + '\n' )

            self.read( delim=': ', expect='New password: ' )

            new_password = ''.join(random.choice('abcdefghijklmnop') for _ in range(10))

            self.write( new_password + '\n' )

            user_to_change_password.password = new_password

            self.read( delim='\n', expect='Password set for user.\n' )

    def create_user_and_login(self):

        if ( self.GetUserCount() == 0 ):
            self.write('1\n')
            self.read(delim=': ', expect='Username: ')

            new_username = ''.join(random.choice('abcdefghijklmnopqrstuvwxyz') for _ in range(10))

            self.write(new_username + '\n')

            self.read( delim=': ', expect='Password: ' )

            new_password = ''.join(random.choice('abcdefghijklmnopqrstuvwxyz') for _ in range(10))

            self.write(new_password + '\n')

            self.AddUser( new_username, new_password )
            self.read(delim='\n', expect='User created successfully.\n' )

            self.menu()


        self.write( '2\n' )
        self.read( delim=': ', expect='Enter Username: ' )

        user_to_login = self.GetRandomUser()

        self.write( user_to_login.username + '\n' )

        self.read( delim=': ', expect='Enter Password: ' )

        self.write( user_to_login.password + '\n' )

        self.read( delim='\n', expect='Login success.\n' )

        self.LoginUser( user_to_login )

    def user_bad_login(self):
        self.write( '2\n' )

        self.read( delim=': ', expect='Enter Username: ' )
        # Bad login anyways!
        bad_username = "1" + ''.join(random.choice('abcdefghijklmnop') for _ in range(10))

        self.write( bad_username + '\n' )

        self.read( delim=': ', expect='Enter Password: ' )

        bad_password = ''.join(random.choice('123456789abcdefghijklmnop') for _ in range(10))

        self.write( bad_password + '\n' )

        self.read( delim='\n', expect='Login failed. Invalid username or password.\n' )

    def user_menu(self):
        self.read( delim='\n', expect='1) Send Message\n' )
        self.read( delim='\n', expect='2) Read Message\n' )
        self.read( delim='\n', expect='3) List Messages\n' )
        self.read( delim='\n', expect='4) Delete Message\n' )
        self.read( delim='\n', expect='5) Logout\n' )
        self.read( delim='\n', expect='6) Exit\n' )

    def user_send_message(self):
        # Option 1 send message to user
        self.write( '1\n' )

        self.read( delim=': ', expect='Username to send to: ' )

        if ( self.GetUserCount() == 0 or random.randint( 0, 10 ) == 0 ):
            # Bad username to send to
            bad_username = "1" + ''.join(random.choice('abcdefghijklmnop') for _ in range(10))

            self.write( bad_username + '\n' )

            self.read( delim='\n', expect='User not found.\n' )

        else:
            user_to_send_to = self.GetRandomUser()

            self.write( user_to_send_to.username + '\n' )

            self.read( delim=': ', expect='Enter Message: ' )

            message_to_send = ''.join( random.choice( '0123456789abcdefghijklmnopqrstuvwxyz' ) for _ in range(32))

            self.write( message_to_send + '\n' )

            self.read( delim='\n', expect='Message sent.\n' )

            # Add message
            user_to_send_to.AddMessage( self.logged_in_user.username, message_to_send )

    def user_read_message(self):
        # Option 2 read message
        self.write( '2\n' )

        if ( self.logged_in_user.GetMessageCount() == 0 ):
            self.read( delim='\n', expect='No messages.\n' )

            return

        if ( self.logged_in_user.HasUnreadMessages() ):
            unread_message_list = self.logged_in_user.GetUnreadMessages()
            unread_message_count = len(unread_message_list)

            self.read( delim='\n', expect=('%d unread messages available. Last unread message:\n' % unread_message_count) )

            self.read( delim='\n', expect=('From: %s\n' % unread_message_list[unread_message_count-1].from_user) )
            self.read( delim='\n', expect=('Message: %s\n' % unread_message_list[unread_message_count-1].message) )

            # Clear unread messages
            self.logged_in_user.ClearUnreadMessages()

        self.read( delim=': ', expect=('%d total messages available, enter number to read: ' % self.logged_in_user.GetMessageCount()) )

        message_number_to_read = random.randint( 0, self.logged_in_user.GetMessageCount()-1 )

        # Write out the number to read
        self.write( ('%d\n' % message_number_to_read) )

        message_to_read = self.logged_in_user.GetMessageNumber( message_number_to_read )

        self.read( delim='\n', expect=('Message %d:\n' % message_number_to_read) )
        self.read( delim='\n', expect=('From: %s\n' % message_to_read.from_user) )
        self.read( delim='\n', expect=('Message: %s\n' % message_to_read.message) )

    def user_list_messages(self):
        # Option 3 list messages
        self.write( '3\n' )

        if ( self.logged_in_user.GetMessageCount() == 0 ):
            self.read( delim='\n', expect='No messages.\n' )

            return

        self.read( delim='\n', expect=("Listing %d messages:\n" % self.logged_in_user.GetMessageCount()) )

        cur_pos = 0
        for message in self.logged_in_user.GetMessageList():
            self.read( delim='\n', expect=('Message %d:\n' % cur_pos) )
            self.read( delim='\n', expect=('From: %s\n' % message.from_user) )
            self.read( delim='\n', expect=('Message: %s\n' % message.message) )

            cur_pos += 1

    def user_delete_message(self):
        # Option 4 delete message
        self.write( '4\n' )

        if ( self.logged_in_user.GetMessageCount() == 0 ):
            self.read( delim='\n', expect='No messages to delete.\n' )

            return

        # Delete prompt
        self.read( delim=': ', expect=('%d messages available. Enter number to delete: ' % self.logged_in_user.GetMessageCount()) )

        if ( self.logged_in_user.HasUnreadMessages() ):
            # Avoid the bug -- by not attempting to delete messages when there are unread messages
            message_to_delete = random.randint( self.logged_in_user.GetMessageCount()+1, 1000 )

            self.write( ('%d\n' % message_to_delete) )

            self.read( delim='\n', expect='Invalid message number.\n' )

            return

        message_to_delete = random.randint( 0, self.logged_in_user.GetMessageCount()-1 )

        self.write( ('%d\n' % message_to_delete) )

        self.read( delim='\n', expect='Message deleted.\n' )

        # Delete it
        self.logged_in_user.DeleteMessageNumber( message_to_delete )

    def user_logout(self):
        # Option 5 logout
        self.write( '5\n' )

        self.read( delim='\n', expect='Logged out.\n' )

        self.LogoutUser()

    def user_exit(self):
        # Option 6 exit
        self.write( '6\n' )

        # Exiting banner
        self.read(delim='\n', expect='Exiting\n')
