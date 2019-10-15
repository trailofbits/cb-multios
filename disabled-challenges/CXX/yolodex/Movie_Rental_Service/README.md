# CGC Challenge Binary (KPRCA\_00011): Movie Rental Service

## Author Information

"Brian Pak" <brian.pak@kapricasecurity.com>

### DARPA performer group
Kaprica Security (KPRCA)

## Description

This is a simple movie rental service where the user can list available movies in the inventory and rent the ones that are not rented already. The user is also able to return the movie. There is also an interface for privileged user (admin) when successfully logged in. This interface allows the admin to add, remove, or update movies in the inventory.

### Feature List

This service supports the following features:

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


## Vulnerability

Upon specific sequence of actions (and appropriate input), it is possible to cause a use-after-free (UAF) bug and crash the program. With specially crafted input, arbitrary code execution is also possible.

There are actually 2 bugs in the service. The first bug allows the attacker to get into admin mode without knowing the correct password. There exists a stack buffer overflow which results in the overwrite of the return status local variable that determines if the login was successful. However, this bug is not enough to crash the service. The second bug is a UAF bug with the movie lists, where the rental list holds a stale pointer to the free'd movie entry. 

Specifically, in main.c:445, when the movie is removed (in admin menu), it is removed only from the full list, not the rented list. Then, by allocating memory of size equivalent of the movie object, it is possible to control the contents of the stale movie pointer, which has a function pointer in it. By setting the function pointer, EIP control is possible.

### Generic class of vulnerability

Stack Buffer Overflow

Use-After-Free

### CWE classification
Stack-based Buffer Overflow (CWE-121)

Use-After-Free (CWE-416)

## Challenges

This CB tests if the competitors can chain two vulnerabilities to perform a successful attack. Since the password for the admin account is randomly generated each time the program is run, the stack buffer overflow needs to be used to bypass the login validation. It requires a good understanding of how the memory allocation and free work. Also, in order to successfully crash the program, one needs to use both modes (normal & admin) in a specific order to manipulate the layout of the heap.