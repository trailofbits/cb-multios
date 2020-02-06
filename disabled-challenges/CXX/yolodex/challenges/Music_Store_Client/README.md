# CGC Challenge Binary Template

## Author Information

"Jason Rogers" <info@narfindustries.com>

### DARPA performer group
Narf Industries (NRFIN)

## Description

This service is a Music Store Client looking for a Music Store Server to purchase songs from. The client sends a gift card ID to obtain a balance from the Music Store. The client then begins searching the Music Store by artist, album, or song title. Once a list of songs that match the search critiria is returned, The Music Store Client selects a song to purchase. The Music Store Client continues searching and purchasing songs until the balance is zero. 

### Feature List

The client begins the session by providing the server with the gift card id in order to receive a starting balance. The client then queries the server for all songs up to a requested limit whose artist, album, or song matches a term. The client selects a song from the list returned by the server and requests to purchase it. The client continues to purchase songs until the blanance is below the minimum price for a song.

## Vulnerability
By providing a negative price for a song that is eventually purchased by the client, the balance is incremented instead of decremented. Eventually, more songs are purchased than can be stored on the heap resulting in a overflow.

In order to prevent trivial triggering of the vulnerability, the server must continue to provide valid responses to the client, such that the client purchases enough songs to overflow the buffer.

The service also has a heap overflow caused by sending songs with a zero price. The original buffer size is allocated based on the balance that is received. Since the balance is never decremented due to the zero prize the originally allocated heap-based buffer to hold the purchased songs can be exceeded.

### Generic class of vulnerability
Buffer Overflow
Heap-Based Buffer Overflow
Improper Input Validation
Numeric Range Comparison Without Minimum Check
Out-of-bounds Write

### CWE classification
Buffer Overflow
CWE-120
Heap-based Buffer Overflow
CWE-122
Improper Input Validation
CWE-20
Numeric Range Comparison Without Minimum Check
CWE-839
Out-of-bounds Write
CWE-787



## Challenges

The challenges for the automated system will be:
a) Be able to determine the structure of the client-server protocol. Invalid responses will be rejected, and no songs will be purchased.
b) Be able to understand how a negative price can influence the calculation of the balance. A negative price will result in the balance being incremented.
