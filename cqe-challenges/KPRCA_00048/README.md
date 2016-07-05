# KPRCA-00048

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements and command-line client challenge binary and server
challenge binary for a simple key-value store. The client reads input from the
users, performs some perfunctory validity checks on the user issued command,
encodes the command, passes it via IPC to the server challenge binary, and
finally displays the result to the user. If the command entered by the user is
unknown the user is adequately admonished and an error is returned. The keys
are stored in a binary search tree which allows for easy and efficient in-order
traversal, removal, and insertion.

### Feature List

The following commands are supported by the server.

  * append: Append a value to a key.

  * auth: Authorize the client to the server, this must be done before any
    other commands can be issued.

  * bitcount: Return the number of bits set in the value store at a key.

  * bitop: Perform XOR, OR, AND, or NOT between 2 or 1 keys, depending on the
    action, and store the result in another key.

  * decr: Convert the value at a key to an integer if it is not already one and
    decrease its value by 1.

  * del: Delete a key from the server if it exists.

  * exists: Return a boolean value that states whether or not a key exists in the server.

  * get: Return the value stored at a key.

  * incr: Convert the value at a key to an integer if it is not already one and
    increase its value by 1.

  * keys: Return a list of the keys currently stored in the server.

  * rename: Move the value stored at one key to another key.

  * set: Set the value of a key.

## Vulnerability

The first vulnerability for this service occurs in the server. When generating the
current list keys stored in the server the code that resizes the working-data
buffer when it grows to it's capacity incorrectly calculates the required size
that the buffer must grow to. The incorrect size is 4 bytes too small. Under
the right circumstances this can cause heap corruption and result in
a segmentation fault, i.e. if our `malloc()` implementation returns a block
that is exactly the requested size or if the black is later split.

The second vulnerability for this service occurs in the server. When performing
a bitop of type 'AND' to two keys, if one of the keys referenced by the command
given by the user does not exist as a key within the server then a null pointer
dereference will occur.


### Generic class of vulnerability

  * Buffer overflow
  * In correct buffer size calculation
  * Heap overflow
  * NULL pointer dereference

### CWE classification

  * CWE-122: Heap-based Buffer Overflow
  * CWE-131: Incorrect Calculation of Buffer Size
  * CWE-788: Access of Memory Location After End of Buffer
  * CWE-476: NULL Pointer Dereference

## Challenges

The challenge binary poses tests the following abilities of a system:

  * Ability to handle and reason about client-server modeled IPC.
  * Ability to handle nuanced dynamic memory allocation issues
