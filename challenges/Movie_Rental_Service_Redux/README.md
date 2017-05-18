# CGC Challenge Binary (KPRCA\_00042): Movie Rental Service Redux

### DARPA performer group
Kaprica Security (KPRCA)

## Description

This is a simple movie rental service where the user can list available movies in the inventory and rent the ones that are not rented already. The user is also able to return the movie. There is also an interface for privileged user (admin) when successfully logged in. This interface allows the admin to add, remove, or update movies in the inventory. The movie rental service also allows a debug mode for allowing an admin to test adding genres and movie ratings.

### Feature List

This service supports the following "documented" features:

In normal mode,

  1. **List movies**: lists a full movie list as well as a rental list (i.e. the movies that are currently rented).
  2. **Rent movie**: allows the user to rent a movie from the list (movies that are not currently rented can be rented).
  3. **Return movie**: allows the user to return the movie that was rented.
  4. **Admin mode (login)**: verifies username and password to provide privileged menus.
  5. **Exit**: quits the program.

In admin mode,

  1. **Add movie**: adds a new movie to the list.
  2. **Remove movie**: removes a movie from the list.
  3. **Update movie**: updates information about a movie.
  4. **Quit admin mode**: quits the admin mode and goes back to the normal mode.

The service supports the following "undocumented" features:

In admin mode,
    Send byte array \x29\x78\x31\x16\x00\x29\x78\x31\x16\x00 to enter debug mode

In debug mode,
   1. **Debug Add Genre**: Send integer 1294579383 appended with a string, 
                            adds appended string to the list of Genres
   2. **Debug Add Rating**: Send integer 388502 appended with a string, 
                            adds appended string to the list of Movie Ratings

## Vulnerability

The vulnerability is a format string vulnerability triggered by a special debug function. Once in debug mode if the user sends the integer: 1294579383 (sent as a little endian byte array: \x4D\x29\xB6\xB7) The user can append a genre title to the integer. Since the user has complete control over the string they can trivially crash the program.

Getting to the vulenrable state requires -> logging in as admin -> passing the debug sequence \x29\x78\x31\x16\x00\x29\x78\x31\x16\x00 to enable debug mode -> passing the debug code \x4D\x29\xB6\xB7<VULNERABLE STRING> -> exit debug mode -> add/update a movie

### Generic class of vulnerability

Format String

### CWE classification

CWE-134: Uncontrolled Format String

## Challenges

The CB generates a small random password stored in the heap which is meant to be bruce forceable. The more challenging part is determining the "undocumented" byte sequence (hardcoded in the binary) that enables debug mode. Once in debug mode a user must send the "undocumented" integer codes that call the debug functions, dag (debug add genre) and dar (debug add rating). Specifically the vulnerability is enabled by calling dag with a vulnerable string.

Once a competitor determines how to call the dag function and add a vulnerable string to the movie genre list, crashing the program requires the competitor use the admin mode function to add or update a movie. When it gets to the part that lists the "genres" the bug can be triggered.
