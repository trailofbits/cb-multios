# CGC Challenge Binary Template

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

This is an AIS message parser/decoder for the AIS Lite protocol(TM). The connecting client provides a proprerly structured AIS Lite sentence, and the service returns the English textual meaning of the encoded AIS Lite message.

AIS Lite is a protocol roughly based on NMEA 0183. When we say roughly based, we mean that we've refined it to remove all of the cruft that is not related to AIS messages. Additionally, we've removed all of the AIS messaging components that are rarely or never used.

To avoid concerns about this protocol being to similar to the actual NMEA sentence structure or AIS messages structure, we've taken the original NMEA/AIS protocols and altered their formats. So, the sentences used by this CB are not valid NMEA sentences and the encoded AIS messages are not valid AIS messages as decided by a standards-based NMEA/AIS protocol parsers.

### Feature List

This service supports 3 AIS messages types (1, 4, 5). These are the most common, so we decided to ignore all others.

Message types 1 and 4 are transported in a single sentence, so they will receive the English translation as an immediate response. Message type 5 requires 2 sentences to transport it, so the first message will recieve a notification that it received a partial AIS message. The second sentence, will result in the English translation being returned.

## Vulnerability

This CB has 1 vuln.

The vuln is a heap overflow that corrupts heap metadata, so calling free triggers SIGSEGV. The heap buffer for `ss->ais_msg` gets `MAX_SETNENCE_LEN` bytes of memory. And immediately following it in memory is the buffer for `buf`. Thus anything that can write more than `MAX_SENTENCE_LEN` chars to `ss->ais_msg` can overwrite the heap metadata between them. This occurs in sentence.c:104 on a type 5 message. The type 5 message requires 2 sentences to send the full message content. The second message may contain more chars than there is memory alloted, which the fieldncopy will directly copy into `ss->ais_msg` via the `ss->p_ais_msg` pointer.


### Generic class of vulnerability

Classic heap buffer overflow

Null pointer dereference

Improper array bounds checking

Access memory beyond buffer

### CWE classification

CWE-20 Improper Input Validation
CWE-120 Buffer Copy without Checking Size of Input
CWE-122 Heap-based Buffer Overflow
CWE-129 Improper Validation of Array Index
CWE-788 Access of Memory Location After End of Buffer


## Challenges
* The protocol is a very simple question/answer type protocol. However, the questions are very complex. The question is in the form of a string that has a defined format, length, and includes a checksum. Additionally, part of the question is encoded using 6bits per byte. The complexity of the string makes it difficult for an automated system to generate alternative input. This will make fuzzing incredibly difficult.




