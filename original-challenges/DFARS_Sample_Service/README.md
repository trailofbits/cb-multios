# DFARS Sample Service

## Description

This service implements a FAR section lookup service, including a niave
compression, dynamic skip searching, and prefix tree searching for commands.

## Vulnerabilities

The vulnerability is out-of-bounds memory corruption vulnerability triggered
during path canonicalization.  The vulnerable condition is triggered by
erroniously searching for a for path delimiter outside the bounds of the
supplied buffer.

The function's intent is to normalize "|foo|++|" into "|".  The method is to
identify a traversal marker "++|", and seek backwards until the previous marker
"|" is identified, then replace from that location until the next marker "|" is
found.

If the input does not begin with the marker "|", then the program will continue
the search into unspecified memory regions.  If the marker is found elsewhere,
the program will write the input after the traversal marker "++|" at the found
location.

By placing a a marker "|" in a known location, a specified input may be able to
leverage the marker "|" to modify memory in a fashion that can be leveraged
gain execution control.

The out-of-bounds memory access has multiple prerequisites before a PoV can
prove the vulnerability is identified.

1. The canonicalization process allows for at most only 2 canonicalizations per
   input.
   
   This requires the identification of path delimiters in memory prior to an
   "interesting" area, and setting them to something other than the delimiter.
   
   Immediately prior to the buffer in question is a counter specifying the
   number of FAR sections are currently in the service.  The number, in byte
   representation, is the path delimiter.  In order to access interesting
   memory, the PoV must add an additional section to the FAR sections.  This
   may be accomplished via the "put" command.
   
   Example: "put foo bar\x00\n"

2. In order to add an additional section, the service needs to have a current
   directory set.  By setting the current directory, there is now a known "|"
   prior to the beginning of the buffer.

   Example: "ch_sec |\n"

3. The canonicalization process requires the buffer begin with a delimiter,
   making at least two canonicalization reductions be supplied by the input to
   search before the beginning of the buffer.  The vulnerable condition can be
   triggered with "ch_sec |A|++|++|AAAAAAAAAA"  
   
4. The input buffer is smaller than the buffer size to get to area of interest,
   In order to overwrite memory that will identify a PoV the the vulnerable
   condition, a function pointer after the directory must be overwritten, and
   then used.  This requires multiple triggering conditions, ending the input
   with a delimiter.  This requires repeated calls to ch_sec, with the argument
   including a trailing delimiter.

   Example: "ch_sec |A|++|++|AAAAAAAAAA|\n"

## Notes
* This vulnerability mirrors a critical vulnerability in multiple Microsoft products, MS08-067.
* The content for the lookup service is from the US Government's Federal Acquisition Regulation website:

    http://www.acquisition.gov/far/current/html/farhtml.zip
