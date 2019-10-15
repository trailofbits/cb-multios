# Lazybox

## Author Information

"Joe Rogers" <joe@cromulence.com>

### DARPA performer group
Cromulence (CROMU)

## Description

This CB implements a basic shell and command line environment similar to busybox.  It supports a single directory file system, the ability to create, delete and change between users, change user passwords, create files, and display their contents.

ShortDescription: A basic linux shell and command line environment

### Feature List

The CB provides these features:

- Basic shell with command history accessible through up/down arrows
- Basic filesystem (single directory, list files, dump file contents)
- User management (change user, change password, create new user, delete a user)
- exit

## Vulnerability
Vulnerability #1:
The shell has a command history buffer with 16 entries. But, the PrependCommandHistory() function has an off-by-one error which allows 17 entries to be written.  The CommandHistory buffer is stored in a structure directly adjacent to the User variable which determines the currently logged in user.  If the CRS makes its first command one of the other defined users in the pre-confgiured password file (user 'root' or 'secure'), and then runs 16 more commands, the User variable will be overwritten with the username of their choosing.  It's not immediately obvious that the username has been updated since the command history is prepended after the 17th command is entered.  

Vulnerability #2:
':' characters are used as the field delimiter for the password file in the CB with the fields being "password:username:group".  The 'passwd' command fails to check for ':' characters in user supplied passwords.  So, it's possible to craft a fake 'root' user password file entry by changing the 'crs' user password to 'asdf:root:root' which will make the resulting password file entry "asdf:root:root:crs:crs".  The extra fields at the end of the line are ignored by the 'su' command.

### Generic class of vulnerability
Vulnerability #1: Incorrect array size calculation
Vulnerability #2: Unchecked user input

### CWE classification
Vulnerability #1: CWE-193 Off-by-one Error
Vulnerability #2: CWE-20 Improper Input Validation

## Challenges
The first vulnerability should be relatively easy to identify if the CRS sends more than 16 commands to the CB and correctly parses the CLI prompt which will change when the user name is overwritten.  The CRS will then need to identify that the four bytes of secret flag data are stored in the 'secure' user's file and that the 'cat' command is the proper way to view that file's contents.  Discovery: easy, Proving: easy, Fixing: easy.

The second vulnerability requires the CRS to identify the lack of input validation, understand the password file format, and figure out that the root user has the necessary access rights to the 'confidential' file even though it's owned by the 'secure' user.  Discovery: medium, Proving: medium, Fixing: easy.
