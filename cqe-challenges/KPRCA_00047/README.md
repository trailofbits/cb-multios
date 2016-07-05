# KPRCA-00047

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements an optical character recognition engine. It takes in
simple drawings of letters and tries to determine what the drawing says. It
either returns to the user a successful result or an error message.

### Feature List

The OCR engine accepts only a predefined format for the images which it will
process. This format has a special header on the first line, the dimensions of
the image on the next line and the data comprising the image on the remaining
lines of the input file. The image data is an array of bytes. The OCR engine
walks over the image data attempting to match a subsection of the image data
against predefined character templates. The matching algorithm allows for some
fuzziness. If a character template is successfully matched against that
character is copied to a result buffer and the window is shifted past the
character. If no character is successfully matched against for the current
window then the window is simply shifted over one column and the matching
process begins again. When the window hits the end of the array the matching
process is finished. The concatenation of all successful matches are returned
to the user. If no successful matches occurred then an error message is
returned to the user.

## Vulnerability

The first vulnerability for this service occurs when the number of characters has
been matched exceeds a predefined size of the result buffer. When this happens
the remaining successfully matched characters are copied past the end of
a result buffer located on the stack.

The second vulnerability for this service occurs in the calloc for this
service. The user controls the size value that is passed to calloc and the
malloc here improperly checks the requested size which allows for an integer
overflow and for improper sizes. This results in malloc claiming to have
succeed when it in actuality did not allocate the requested size. calloc then
attempts to set the requested size of bytes on the returned buffer which
results in a segfault.

### Generic class of vulnerability
 * Buffer overflow
 * Unchecked array index
 * Integer Overflow

### CWE classification
  * CWE-121: Stack-based Buffer Overflow
  * CWE-787: Out-of-bounds Write
  * CWE-190: Integer Overflow or Wraparound

## Challenges

This service requires that the system attempting to identify flaws in it be
able to deal with the following obstacles.

  * Large input spaces
  * Large binary sizes
  * Ability to generate arbitrary data that fits a strict set of constraints.
