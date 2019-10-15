# KPRCA-00023

## DARPA performer group
Kaprica Security (KPRCA)

## Description:

This CB emulates an online job application form. An applicant moves through
several pages of grouped questions (Candiate Info, Education, Address, etc etc)
and is forced to enter each question on the form before continuing to the next
page. The pages are seqential and, once completed, can be revisited using the
"prev" command. Completed pages can have indivial questions updated with new
answers or an applicant can simply review his or her answers. 

Once the form is completed the user can "submit" the form by exiting, or
"discard" by using ctrl-c. The two are functionally equivalent, but we would
hate to feel like someone didn't have a chance to throw their application away.

The code attempts to model a web interface. Each input has a textfield,
a buffer to hold the response, and a verification function that makes sure the
input is valid. 

### Feature List

And applicant can enter input when asked a question, or navigate accross the
application with the following commands:

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

When an entry is updated with the **update function a compare is made using
`strncmp` between the existing entry data and the data the entry is to be
updated with. If this check passes, the new data is copied over the old data
using `strcpy`. The logical flaw is that the length argument to `strncmp` is
the length of the old data, not the new data. Since entries are stored on the
heap, if the newer data is significantly bigger than the old data, a heap based
buffer overflow can occur.

## CWE classification

CWE-120: Buffer Copy without Checking Size of Input ('Classic Buffer Overflow')
CWE-122: Heap-based Buffer Overflow

## Challenges

This problem requires competitors to be able to pass all the data validation
checks to get to the vulnerable `update` function. If then requires them to
reason about associated with scommon issues tring manipulation functions and
issues associated with unbounded copies to data on the heap.
