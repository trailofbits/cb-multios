# CROMU-00004: PCM Message decoder

## Author Information

“Joe Rogers” <joe@cromulence.co>

### DARPA performer group
Cromulence (CROMU)

## Description

This service reads in a morse code like language in the form of a PCM-encoded file,
decodes the data, and prints out the message.

### Feature List

This program supports the decoding of a PCM-based audio file format.  It expects a
sample rate of 44100 samples/sec with 16-bit samples.  It decodes the audio data
as a morse code like language, printing the decoded message as its output.

## Vulnerability
The PCM format contains two length specifiers. DataSize is the length of the PCM data
in the file.  NumSamples number of PCM samples.  The program can only handle 16-bit
samples, so it checks that DataSize*8/NumSamples == 16.  However it does this check
using integer division in the unpatched cb which allows DataSize*8 to be larger
than it should be.  For example 64*8/32 == 16 but 65*8/32 == 16 as well.  Since
the program uses the DataSize field for reading in the rest of the PCM file,
a stack-based overflow condition is created.

### Generic class of vulnerability
Unchecked user input leads to overrun of fixed size buffer allowing control of EIP.

### CWE classification
CWE-120 - Buffer Copy without Checking Size of Input

## Challenges
The attacker must be able to determine there's a mistake in the sample size
check and understand they can use that to send an overly large DataSize.
