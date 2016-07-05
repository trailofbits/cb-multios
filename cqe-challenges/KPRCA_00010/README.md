# KPRCA\_00010: Audio Visualizer

## Author Information
"Sagar Momin" <sagar.momin@kapricasecurity.com>

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This servcie implements a PCM audio visualizer. It is limited to uncompressed PCM 
audio files, 8 or 16 bits per sample, 1 or 2 channels, and 8000, 11025, 16000, 
22050, 32000, 44100, or 48000 samples per second. 

The visualizer displays the audio in both the time domain, or by running an FFT 
(fast fourier transform) on the data and visualizing it in the frequency domain. 

### Feature List:

The visualizer initially has 2 options, load a file or quit. Once a valid file is 
loaded into the system the service exposes 9 options for a user to execute.
  
1. Load a new file - removes the current file from memory and loads a new file
2. Wave Visualizer - displays the raw bytes for an audio file. Turns out this looks
                     like a wave.
3. EQ Visualizer - displays graph of frequency by relative percentages (bar graph form)
                   per second
4. Power Visualizer - Displays average power usage per second
5. Enable Low Pass Filter - Filters out the top 1/3 frequencies with the EQ Vis
6. Enable High Pass Filter - Filters out the bottom 1/3 frequencies with the EQ Vis
7. Disable Filter
8. Set visualization speed - slows down the speed of the visualization for human viewing
9. Quit

## Vulnerability

The vulnerability is enabled due to an unchecked header field. THe uwfc file is split into 3 header "chunks".
The first chunk size is the overall file size (minus 8 bytes, because the value doesn't include the chunk id or the 
chunk size, which are both integers). The header then contains two "sub chunks", the first sub chunk describes the
audio format (bit rate, sample rate, number of channels, etc) and the second sub chunk contains the audio data.

Sub chunk1's size field should always be 16, because that is the only acceptable value for a PCM audio file, 
but the header validation function fails to check this in the unpatched version.

The formula for chunk size = 4 + (8 + sub chunk1 size) + (8 + sub chunk2 size)
Since the unpatched version assumes sub chunk1's size will always be 16, this allows for an overflow because
of how the track is malloc'd vs how it is indexed.

The header validation function returns the file size of the audio file, and by using this the program mallocs
(file size - header size) bytes. This value should be exactly equal to sub chunk2's size, but the programmer's
logic is by using the returned file size, which is stored as a signed int, he first checks to make sure this
value is >= 0 before calling malloc. The program does not support allocating very large files, and this is how 
the programmer thought to enforce this limitation.

Throughout the rest of the program since (file size - header size) is assumed to be exactly equal to 
sub chunk2's size, the programmer indexes the malloc'd buffer via sub chunk2's size. 

If sub chunk1's size > 16, the program will allocate a buffer larger than it will be able to index, which 
wouldn't cause any problems, besides probably getting some unintended results.
If sub chunk1's size < 16, the program will allocate a buffer smaller than its intended indexed size, and will
allow the user to arbitrarily write data into the heap. 

The math works out to be something like this:
allocated heap buffer size = chunk size + 8 (file size) - 44 (header size)
chunk size = 20 + sub chunk1 size + sub chunk2 size
allocated heap buffer size = 20 + sc1s + sc2s + 8 - 44
allocated heap buffer size = sc1s + scs2 - 16

From this formula if sc1s != 16, this lets you arbitrarily control how much you allocate (make scs1 > 16)
and how much you can write (make sc1s < 16).

The validation does check the chunk size, so (16 - sc1s) must be proportional to scs2.

One way to fix this is to simply return the sub chunk2 size after the validate header call, another would
have been to continue returning the file size, but add a check for the sub chunk1 size. The fix in place 
is the former, so that the pov poller works for both binaries.

### Generic class of vulnerability
Heap buffer overflow

### CWE classification
CWE-122: Heap-based Buffer Overflow

## Challenges

The challenge is meant to show that even when doing file processing, a programmer's assumptions may
bias his or her functions. What a programmer may assume to be trivially obvious, may end up being
the difference between a vulnerable and properly functioning program.

The vulnerability is meant to test a system's ability to reason through the values allocating vs indexing
a buffer.
