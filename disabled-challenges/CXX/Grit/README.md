# Grit

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A C++ audio editor and synthesizer

### Feature List

The audio editor provides the ability to generate audio, import/export audio, amplify and pan the audio, and add a reverb effect. The generated audio can be derived from a sine wave, square wave, or white noise. It supports three formats for import and export: uncompressed 32-bit samples, compressed 8-bit samples, and compressed 4-bit samples, with all formats supporting 1 or 2 channels.

The number of tracks is limited only by the available memory. Each track's gain and pan can be individually set. During export, all of the tracks will be mixed together using the appropriate gain.

## Vulnerability
### Vuln 1
In Interface::importAudio, the attacker supplied number of samples is not checked against the number of bytes sent by the attacker. This may result in the decompression functions accessing memory that is beyond the input buffer. A trivial example can be constructed by providing an input size of 32 bytes and an input header that specifies 64 samples. Using the white noise functionality, an attacker can cause data derived from the secret page to be on the heap and easily converted back to bytes from the secret page.

#### Generic class of vulnerability

Buffer Over-read

#### CWE classification

CWE-126: Buffer Over-read

#### Challenges

 - Once the bug is discovered, the CRS must be able to layout the heap so that they get enough bytes that are derived from the secret page
 - The only bytes that are derived from the secret page are the bytes used as entropy for the RNG, which have been obfuscated with XOR and must be un-obfuscated to get the secret page bytes	

#### Difficulty

 - **Discovery**: medium
 - **Proving**: medium
 - **Patching**: medium
