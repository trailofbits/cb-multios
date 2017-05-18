# CGC Challenge Binary (KPRCA\_00016): LulzChat

### DARPA performer group
Kaprica Security (KPRCA)

## Description

This is an instant messaging platform that allows users to sign up, log in, send and receive messages. There are two parts: server and client. The client provides the interface for users to interact with the system, and it talks to the server with a custom protocol. The client and the server communicate through IPC, and thus the server side interface isn't directly exposed. LulzChat supports 'protected' mode that uses Coffee algorithm for obfuscated communication.

### Feature List

This service supports the following features:

  1. **Register a new user**
  2. **Log in as a registered user**
  3. **Log out the current user**
  4. **List messages**
  5. **View a message**
  6. **Send a message**
  7. **Delete a message**

The server-side keeps track of users, queued messages, etc. whereas the client-side provides the interface for above-mentioned features. Each packet has a specific format containing the following:

  - Header
    - type: REQUEST or RESPONSE
    - command: register, login, list, view, send, delete
    - checksum
    - body length
  - Body
    - command body

Server responds with the following format:

  - Status code
  - Data length
  - Data
    - register: username, if successful
    - login: user_id + auth_code, if successful
    - list: list of messages (just metainfo, not contents)
    - view: message info (metainfo + content)
    - send: N/A
    - delete: remaining # of messages

The data structure used for each request command can be found in *request.h*.

Protected messages are obfuscated with Coffee algorithm that uses the key derived from each user's *auth_code* which is generated randomly when creating (registering) an account.

## Vulnerability

Since the server isn't directly exposed to users, the attack must utilize functions that are provided by the client-side challenge binary. The vulnerability is the comprison (for range checking) for the index when deleting a message from the queue. Using incorrect signedness for the integer comparison allows an invalid index to pass the check, resulting the linked list traversal to access invalid memory.

There is also an uninitialized memory vulnerability when message is created and text is not set due to an error.

### Generic class of vulnerability

Incorrect signedness conversion

NULL pointer dereference

Uninitialized memory

### CWE classification

Signed to Unsigned Conversion Error (CWE-195)

NULL Pointer Dereference (CWE-476)

Use of Uninitiailized Resource (CWE-908)

## Challenges

This CB tests if the competitors can perform the data-flow analysis across multiple CBs. The vulnerability doesn't seem immediately obvious since its affect to the server-side also needs to be reasoned before it's a crashable bug. In fact, the client-side doesn't need to perform the test if the server does the task correctly. There are also a lot of other components of the program including many functions and structs, which will complicate the program analysis. However, the bug itself shouldn't be too difficult to find and trigger.
