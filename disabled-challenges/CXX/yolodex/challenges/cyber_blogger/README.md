### DARPA performer group
Kaprica Security (KPRCA)

## Description

This program is a small blogging site. It allows users to create content, add friends, and like posts. 
Once a user has accumlulated enough friends, and likes, he or she is upgraded to a full user and may
upload files to the blog post.

### Feature List

Unregistered users may:
1. Register
2. Log in
3. View a user's posts
4. View a user's profile
5. Quit

And once registered a user can add content, friends, or remove his or her content.
1. Add new blog post
2. Delete blog post
3. Update profile
4. Add a friend
5. View my friends
6. Unfriend someone
7. View my posts
8. View my profile
9. View a user's posts
10. View a user's profi
11. Log out.

## Vulnerability

The vulnerability is triggered by assigning a file to an extension that doesn't match the magic number.
The AsciiArtFile uses multiple inheritance, and by type casting it as a PictureFile it's possible to
overwrite the second inherited class' vtable. 

The second vulnerability is due to a order of operations error. It's possible to overwrite a byte during the 
input text function. The buffer size has a max of 4096 bytes, but can accept up to 4097.

### Generic class of vulnerability

Buffer Overflow
Incorrect Type Conversion

### CWE classification

Operator Precedence Logic Error (CWE-783)
Incorrect Type Conversion or Cast (CWE-704)

## Challenges

The goal of this program is to have challengers test their system against code using polymorphism.
Understanding how C++ sets up polymophic classes will be important in finding this vulnerability.

The buffer overflow is meant to test how large a team's input testing scales. In order for this bug to be triggered
it requires a buffer of exactly 4097 bytes to be sent 20+ times.
