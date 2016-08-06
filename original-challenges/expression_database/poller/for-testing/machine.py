#!/usr/bin/env python

from generator.actions import Actions
from random import randint
import random
import string
import math
import numpy

# Maximum number of records in the database
MAX_DDAP_RECORDS    = 64
MAX_STRING_LENGTH   = 128

def generate_name( string_size ):

    char_list = string.uppercase + string.lowercase + string.digits + "!& "
    name = "".join( random.choice( char_list ) for x in range( string_size ) )

    return name

def generate_birthdate():
    year = random.randint( 0, 99 )

    if ( year < 28 ):
        year += 100

    return (random.randint( 1, 12 ), random.randint( 1, 31 ), year, random.randint( 0, 23 ), random.randint( 0, 59 ), random.randint( 0, 59 ))

def sanitize_string( instr ):

    outstr = ""
    for char in instr:
        if ( char in (string.uppercase + string.lowercase + string.digits) ):
            outstr += char
        else:
            outstr += '_'

    return outstr

def compare_birthdate( lval, rval ):
    # Compare years
    if ( lval[2] < rval[2] ):
        return -1

    if ( lval[2] > rval[2] ):
        return 1

    # Compare months
    if ( lval[0] < rval[0] ):
        return -1

    if ( lval[0] > rval[0] ):
        return 1

    # Compare days
    if ( lval[1] < rval[1] ):
        return -1

    if ( lval[1] > rval[1] ):
        return 1

    # Compare hours
    if ( lval[3] < rval[3] ):
        return -1

    if ( lval[3] > rval[3] ):
        return 1

    # Compare minutes
    if ( lval[4] < rval[4] ):
        return -1

    if ( lval[4] > rval[4] ):
        return 1

    # Compare seconds
    if ( lval[5] < rval[5] ):
        return -1

    if ( lval[5] > rval[5] ):
        return 1

    # They are equal
    return 0

def get_display_birthdate( birthdate ):
    month = birthdate[0]
    day = birthdate[1]
    year = birthdate[2]

    hour = birthdate[3]
    minute = birthdate[4]
    second = birthdate[5]

    return ("%d/%d/%d %d:%d:%d" % (month, day, (year+1900), hour, minute, second) )

def get_write_birthdate( birthdate ):
    month = birthdate[0]
    day = birthdate[1]
    year = birthdate[2]

    if ( year >= 100 ):
        year -= 100

    hour = birthdate[3]
    minute = birthdate[4]
    second = birthdate[5]

    return ("%d/%d/%d %d:%d:%d" % (month, day, year, hour, minute, second) )

class DDAPRecord():
    def __init__(self, firstname, lastname, username, birthdate ):
        self.firstname = firstname
        self.lastname = lastname
        self.username = username
        self.birthdate = birthdate


class DDAPSimulator(Actions):

    # Contains the login state of the user
    logged_in = False

    # Database items
    db_items = list()

    # Lookup tables for find expression
    lookup_element = ( "firstname", "lastname", "username", "birthdate" )
    lookup_operator = ( "==", "!=", ">", "<" )

    def print_item(self, record_num):
        record_number_string = "Record [%d]\n" % record_num
        firstname_string = "First name: %s\n" % self.db_items[record_num].firstname
        lastname_string = "Last name: %s\n" % self.db_items[record_num].lastname
        username_string = "User name: %s\n" % self.db_items[record_num].username
        birthdate_string = "Birthdate: %s\n" % get_display_birthdate( self.db_items[record_num].birthdate )

        self.read( delim='\n', expect=record_number_string )
        self.read( delim='\n', expect=firstname_string )
        self.read( delim='\n', expect=lastname_string )
        self.read( delim='\n', expect=username_string )
        self.read( delim='\n', expect=birthdate_string )

    def print_all_items(self):
        record_print_amount = "Printing all %d records.\n" % len(self.db_items)

        self.read( delim='\n', expect=record_print_amount )

        record_num = 0
        for cur_item in self.db_items:
            record_number_string = "Record [%d]\n" % record_num
            firstname_string = "First name: %s\n" % cur_item.firstname
            lastname_string = "Last name: %s\n" % cur_item.lastname
            username_string = "User name: %s\n" % cur_item.username
            birthdate_string = "Birthdate: %s\n" % get_display_birthdate( cur_item.birthdate )

            record_num += 1

            self.read( delim='\n', expect=record_number_string )
            self.read( delim='\n', expect=firstname_string )
            self.read( delim='\n', expect=lastname_string )
            self.read( delim='\n', expect=username_string )
            self.read( delim='\n', expect=birthdate_string )

    def start(self):
        self.logged_in = False

        del self.db_items[:]

        # Expect prompt
        self.prompt()

    def login(self):
        # Send login
        self.write('login\n')

        # Expect result (dependent on state)
        if ( self.logged_in == True ):
            self.read(delim='\n', expect='You are already logged in.\n')
        else:
            self.read(delim='\n', expect='You logged in.\n')
            self.logged_in = True

    def logout(self):
        # Send logout
        self.write( 'logout\n' )

        if ( self.logged_in == False ):
            self.read( delim='\n', expect='Authentication required. Try login\n' )
        else:
            # Reset login state
            self.logged_in = False

            # Expect result
            self.read(delim='\n', expect='You logged out.\n')

    def exit(self):
        # Send exit
        self.write( 'exit\n' )

        # Expect goodbye
        self.read(delim='\n', expect='Disconnecting.\n')

    def prompt(self):
        # Expect prompt
        self.read(delim=' ', expect='> ')

    def insert(self):
        # Send insert
        self.write( 'insert\n' )

        # Check login state
        if ( self.logged_in == False ):
            self.read( delim='\n', expect='Authentication required. Try login\n' )
            return

        # Generate data
        firstname = generate_name( random.randint( 1, 20 ) )
        lastname = generate_name( random.randint( 1, 20 ) )
        username = generate_name( random.randint( 1, 20 ) )
        birthdate = generate_birthdate()

        # Sanitize information
        firstname_added = sanitize_string( firstname )
        lastname_added = sanitize_string( lastname )
        username_added = sanitize_string( username )
        birthdate_added = birthdate


        # Send information
        self.read(delim=': ', expect='First name: ')
        self.write( firstname+'\n' )
        self.read(delim=': ', expect='Last name: ')
        self.write( lastname+'\n' )
        self.read(delim=': ', expect='User name: ')
        self.write( username+'\n' )
        self.read( delim=': ', expect='Birthdate (mm/dd/yy hh:mm:ss): ')
        self.write( get_write_birthdate(birthdate)+'\n' )

        # Read back birthdate
        self.read( delim='\n', expect=("Date is: %s\n" % get_display_birthdate(birthdate) ) )


        if ( len( self.db_items ) < MAX_DDAP_RECORDS ):
            item_index = len( self.db_items )

            # Add item
            self.db_items.append( DDAPRecord( firstname_added, lastname_added, username_added, birthdate_added ) )

            # Read
            record_add_string = "Data added, record %d\n" % item_index
            self.read( delim='\n', expect=record_add_string )
        else:
            # Record update failed
            self.read( delim='\n', expect='Database full.\n' )

    def update_record(self):
        # Send update
        self.write( 'update\n' )

        # Check login state
        if ( self.logged_in == False ):
            self.read( delim='\n', expect='Authentication required. Try login\n' )
            return


        # Expect
        self.read( delim=': ', expect='Enter record number to update: ' )

        # Small chance of attempting to remove an item that isn't in the list
        if ( random.randint( 0, 10 ) < 8 and len(self.db_items) > 0 ):

            record_to_update = random.randint( 0, len(self.db_items)-1 )
            self.write( ("%d\n" % record_to_update) )

            # Expect

            # First name
            self.read( delim=': ', expect=("Update first name (%s): " % self.db_items[record_to_update].firstname) )
            update_firstname = generate_name( random.randint( 1, 20 ) )
            update_firstname = sanitize_string( update_firstname )

            self.write( update_firstname + '\n' )

            # Last name
            self.read( delim=': ', expect=("Update last name (%s): " % self.db_items[record_to_update].lastname) )
            update_lastname = generate_name( random.randint( 1, 20 ) )
            update_lastname = sanitize_string( update_lastname )

            self.write( update_lastname + '\n' )

            # User name
            self.read( delim=': ', expect=("Update user name (%s): " % self.db_items[record_to_update].username) )
            update_username = generate_name( random.randint( 1, 20 ) )
            update_username = sanitize_string( update_username )

            self.write( update_username + '\n' )

            # Birthdate
            self.read( delim=': ', expect=("Update birthdate (%s): " % get_display_birthdate(self.db_items[record_to_update].birthdate)) )
            update_birthdate = generate_birthdate()

            self.write( get_write_birthdate(update_birthdate) + '\n' )

            # Read back birthdate
            self.read( delim='\n', expect=("Date is: %s\n" % get_display_birthdate(update_birthdate) ) )

            # Update record in DB
            self.db_items[record_to_update].firstname = update_firstname
            self.db_items[record_to_update].lastname = update_lastname
            self.db_items[record_to_update].username = update_username
            self.db_items[record_to_update].birthdate = update_birthdate

            remove_string = "Record %d updated.\n" % record_to_update
            self.read( delim='\n', expect=remove_string )

        else:
            start_record = len(self.db_items)

            if ( start_record >= 1000 ):
                start_record = 100

            self.write( ("%d\n" % random.randint( start_record, 1000 )) )

            # Expect error
            self.read( delim='\n', expect='Record not found.\n' )

    def remove(self):
        # Send remove
        self.write( 'remove\n' )

        # Check login state
        if ( self.logged_in == False ):
            self.read( delim='\n', expect='Authentication required. Try login\n' )
            return

        # Process
        self.read( delim=': ', expect='Enter record number to remove: ' )

        # Small chance of attempting to remove an item that isn't in the list
        if ( random.randint( 0, 10 ) < 8 and len(self.db_items) > 0 ):

            record_to_remove = random.randint( 0, len(self.db_items)-1 )
            self.write( ("%d\n" % record_to_remove) )

            # Expect
            remove_string = "Record %d removed.\n" % record_to_remove
            self.read( delim='\n', expect=remove_string )

            self.db_items.pop( record_to_remove )

        else:
            start_record = len(self.db_items)

            if ( start_record >= 1000 ):
                start_record = 100

            self.write( ("%d\n" % random.randint( start_record, 1000 )) )

            # Expect error
            self.read( delim='\n', expect='Record not found.\n' )

    def print_record(self):
        # Send print
        self.write( 'print\n' )

        # Check login state
        if ( self.logged_in == False ):
            self.read( delim='\n', expect='Authentication required. Try login\n' )
            return

        # Process
        self.read( delim=': ', expect='Enter record number to print (or "all" for all records): ' )

        # Generate a random chance of all, valid, or invalid
        random_choice = random.randint( 0, 10 )

        # Small chance of attempting to remove an item that isn't in the list
        if ( random_choice < 8 and len(self.db_items) > 0 ):

            record_to_print = random.randint( 0, len(self.db_items)-1 )
            self.write( ("%d\n" % record_to_print) )

            # Expect
            self.print_item( record_to_print )

        elif ( random_choice == 8 ):
            # Send all
            self.write( 'all\n' )

            # Print all
            self.print_all_items()

        else:
            start_record = len(self.db_items)
            if ( start_record >= 1000 ):
                start_record = 100

            self.write( ("%d\n" % random.randint( start_record, 1000 )) )

            # Expect error
            self.read( delim='\n', expect='Record not found.\n' )

    def bad_command(self):
        bad_command_lookup = ( "bad", "asdf", "error", "^#&$^!" )

        self.write( bad_command_lookup[ random.randint( 0, 3 ) ] + '\n' )

        # Expect bad command
        self.read( delim='\n', expect='Command not found.\n' )

    def find(self):
        # Send find
        self.write( 'find\n' )

        # Check login state
        if ( self.logged_in == False ):
            self.read( delim='\n', expect='Authentication required. Try login\n' )
            return

        if ( len( self.db_items ) == 0 ):
            # Inform empty database
            self.read( delim='\n', expect='Database empty. No records to find.\n' )

            return


        # Generate a search expression
        self.read( delim='\n', expect='Enter search express (firstname or fn, lastname or ln, username or un, birthdate or bd, operators ==, !=, >, <, AND and OR):\n' )

        # Generate expression
        expression_count = random.randint( 1, 3 )

        search_expression = ""

        final_result_list = list()
        last_result_operator = None

        if ( random.randint( 0, 10 ) == 0 ):
            do_bad_find = True
        else:
            do_bad_find = False

        while ( expression_count > 0 ):
            if ( last_result_operator != None ):
                search_expression += last_result_operator + " "

            element_type = random.randint( 0, 3 )
            operator_type = random.randint( 0, 3 )

            search_expression += self.lookup_element[element_type]
            search_expression += " " + self.lookup_operator[operator_type]

            # Clear result list
            result_list = list()

            if ( element_type < 3 ):
                rval = generate_name( random.randint( 1, 20 ) )
                search_expression += '"' + rval + '" '

                result_list = self.search_by_name( element_type, operator_type, rval )
            else:
                rval = generate_birthdate()
                search_expression += get_write_birthdate( rval )

                result_list = self.search_by_birthdate( operator_type, rval )

            # Was there a previous result operator
            if ( last_result_operator == "AND" ):
                temp_list = list()

                for item1 in final_result_list:
                    for item2 in result_list:
                        if ( item1 == item2 ):
                            temp_list.append( item1 )
                            break

                del final_result_list[:]
                final_result_list = temp_list

            elif ( last_result_operator == "OR" ):
                temp_list = list()

                for item1 in final_result_list:
                    found = 0
                    for item2 in temp_list:
                        if ( item1 == item2 ):
                            found = 1
                            break

                    if ( found == 0 ):
                        temp_list.append( item1 )

                for item1 in result_list:
                    found = 0
                    for item2 in temp_list:
                        if ( item1 == item2 ):
                            found = 1
                            break

                    if ( found == 0 ):
                        temp_list.append( item1 )

                del final_result_list[:]
                final_result_list = temp_list

            # Result list is empty, populate it
            else:
                final_result_list = result_list


            # Setup the next result operator
            if ( random.randint( 0, 1 ) == 0 ):
                last_result_operator = "AND"
            else:
                last_result_operator = "OR"

            expression_count -= 1

        if ( do_bad_find == True ):
            bad_expression_lookup = ( '())', 'badtoken', 'error', '^#*@@(@' )

            search_expression += bad_expression_lookup[ random.randint( 0, 3 ) ]

            self.write( search_expression + '\n' )

            # Expect syntax error
            self.read( delim='\n', expect='Syntax error\n' )

        else:
            # Good expression

            # Print expression results
            self.write( search_expression + '\n' )

            # Expect results
            self.read( delim='\n', expect=("Search results, %d items found:\n" % len(final_result_list)) )

            for item in final_result_list:
                self.print_item( item )

        # Done

    def search_by_name( self, element_type, operator_type, rval ):

        result_list = list()
        index = 0
        for cur_item in self.db_items:

            if ( element_type == 0 ):
                lval = cur_item.firstname
            elif ( element_type == 1 ):
                lval = cur_item.lastname
            elif ( element_type == 2 ):
                lval = cur_item.username

            add_item = 0
            if ( operator_type == 0 ):
                if ( lval == rval ):
                    add_item = 1
            elif ( operator_type == 1 ):
                if ( lval != rval ):
                    add_item = 1
            elif ( operator_type == 2 ):
                if ( lval > rval ):
                    add_item = 1
            elif ( operator_type == 3 ):
                if ( lval < rval ):
                    add_item = 1

            if ( add_item == 1 ):
                result_list.append( index )

            index += 1

        # Return result list
        return result_list

    def search_by_birthdate( self, operator_type, rval ):
        result_list = list()
        index = 0
        for cur_item in self.db_items:

            lval = cur_item.birthdate

            comparison_result = compare_birthdate( lval, rval )

            add_item = 0
            if ( operator_type == 0 ):
                if ( comparison_result == 0 ):
                    add_item = 1
            elif ( operator_type == 1 ):
                if ( comparison_result != 0 ):
                    add_item = 1
            elif ( operator_type == 2 ):
                if ( comparison_result == 1 ):
                    add_item = 1
            elif ( operator_type == 3 ):
                if ( comparison_result == -1 ):
                    add_item = 1

            if ( add_item == 1 ):
                result_list.append( index )

            index += 1

        # Return result list
        return result_list

    def do_test(self):
        print "Length of db_items: %d\n" % len(self.db_items)

        print ("aaaaa" < "aaaaa")

if __name__ == "__main__":
    sim = DDAPSimulator()
    sim.do_test()
