# CGC Challenge Binary Template

## Author Information

"Ben Schmidt" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

RLEStream (pronounced "reallystream") is a video streaming service for the modern shell, committed to delivering quality content in a horribly inefficient way.

### Feature List

We here at RLEStream are dedicated to securely storing and delivering your favorite videos to a shell near you!
Using our patent-pending compression and content protection technology, RLE (Rick's Lulzy Encoding), we are able to provide lightning fast access and superior content protection that our competitors just can't provide.

With our service, you can:
1.) Upload your ASCII videos straight to our super cloud!
2.) Watch your videos right in your shell! 
3.) Manage all your videos conveniently from netcat!
4.) Share videos with your friends by giving them your personal access key!

With RLEStream, you're always a tty away from all your video files! Just download our client and get streaming!

## Vulnerability

Integer overflow when uploading extremely compressed data, leading to heap corruption.
These types of vulnerabilities are quite common in real-world compression libraries, and continue to be a problem today (see CVE-2014-4607 - 11).

To trigger the overflow, competitor PoV's must both add an overly compressed video and then play it with the proper key, causing it to actually be decompressed. 

All uploaded videos are expected to be run-length encoded, xored with a static key (0x42), with a very simple checksum of the run-length encoded data pre-xor.
This checksum, along with restrictive length requirements, should prevent attempts at blind fuzzing.

The overflow occurs when the resulting number of bytes from the decoding process is greater than 2^24 bytes, causing an overflow of the dlen variable, which is defined as a 24 bit bitfield.
Only inputs that have a compression ratio of at least ~127:1 will both trigger the overflow and be small enough to pass a prior length check.

### Generic class of vulnerability

Integer Overflow
Buffer Overflow

### CWE classification

CWE-680: Integer Overflow to Buffer Overflow

## Challenges

* Understanding the transforms necessary to successfully generate correct, highly compressed data. This requires the successful computation of a simple checksum, understanding and using a simple xor encoder, and proper generation of run-length encoded data.
* Utilizing primitive operations in decompression routine repeatedly to trigger overflow.
* Detecting integer overflow vulnerabilities, specificially one in a 3 byte bitfield.
* Breaking our excellent DRM.
