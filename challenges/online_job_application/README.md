# KPRCA-00021

## DARPA performer group
Kaprica Security (KPRCA)

## Description:

This CB emulates an online job application form. An applicant moves through several pages of grouped questions (Candiate Info, Education, Address, etc etc) and is forced to enter each question on the form before continuing to the next page. The pages are seqential and, once completed, can be revisited using the "prev" command. Completed pages can have indivial questions updated with new answers or an applicant can simply review his or her answers. 

Once the form is completed the user can "submit" the form by exiting, or "discard" by using ctrl-c. The two are functionally equivalent, but we would hate to feel like someone didn't have a chance to throw their application away.

The code attempts to model a web interface. Each input has a textfield, a buffer to hold the response, and a verification function that makes sure the input is valid. 

### Feature List

And applicant can enter input when asked a question, or navigate accross the application with the following commands:

All commands begin with '**' and may be entered at any time during the CB
**prev 
    <Return to the previous page>\n);
**next 
    <Move to the next page>\n);
**update [id] 
    <Update field, ex: \Update First Name\>
**help 
    <Print this dialogue>
**exit 
    <Exit application>

## Vulnerability

Certain questions have predefined allowed responses. For example when asking an applicant to enter a Suffix for his or her name, valid options include "Jr, Sr, III" etc etc. For entering address information, 2 letter postal codes are used for states "AK, VA, IA" etc etc. The function that verifies these choices has a bug where it doesn't compare the length of the two strings, but instead compares the user inputted string against a valid choice. Because it never checks the user's inputted string you can overflow the buffer by entering the appropriate string and then appending whatever input you want to overflow. Ex: JrAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA will be accepted as a valid input in the vulnerable version.

### CWE classification

CWE-120: Buffer Copy without Checking Size of Input ('Classic Buffer Overflow')

## Challenges

This problem is meant to allow competitors to test their capabilities to systematically check bounding contraints and determine vulnerable input a little smarter than just utilizing random fuzzing, but instead utizling the static strings available in the binary.
