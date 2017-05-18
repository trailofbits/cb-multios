# FSK_Messaging_Service

## Author Information

"Jason Williams" <jdw@cromulence.com>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This is a service that implements a packet radio receiver with included FSK demodulation front-end, packet decoding, processing, and finally parsing it into a simple messenging service.

### Feature List

This service accepts 8-bit signed samples at 9600 bits/second for 4 seconds of sample data. The sample data is first subjected to AWGN (Additive White Gaussian Noise) generated with a Pseudo Random Number Generator and is then passed through two butterworth bandpass filters tuned for 1200 Hz and 2400 Hz respectively. The output is then passed through a comparator to compare power levels and lastly an envelope detector to provide the output symbols filtered for the symbol data rate (3dB cutoff set to 600 Hz). Data is then passed into a CDR stage (Clock Data Recovery) that reconstructs the clock using an edge transition detector and sample counter. Preamble locking occurs when the input transitions are within 12% deviation of the expected symbol rate of 300 symbols/second. After lock occurs the CDR begins a slow rate drift detection and feeds the baseband symbol recovery engine. Once preamble and CDR lock is complete sync word detection begins. This allows the CDR to align the bit/byte receiver. Finally packet processing begins with length, data, and 16-bit checksum. Once a packet is received the premable lock detection resets and begins again for the next packet.

Packets are then passed into a linked list of received packets based on type. A simple messenging protocol supporting 5 different packet types: Broadcast, Channel, Private, Connect, and Disconnect messages are supported. Once all data is received over the course of the 4 seconds worth of samples the packet data is displayed as output from the service.

## Vulnerability

There is only one vulnerability in this service and an included type 1 POV. Upon reception of a packet that exceeds the maximum packet size of 64-bytes improper length checking is done for the memcpy to the newly allocated packet structure. This allows a memory overwrite to occur on the heap. This data structure has a function pointer to the packet handler that can be overwritten and once the service executes this function pointer there is an opportunity for control flow execution by overwriting this function pointer.

### Generic class of vulnerability
Vulnerability 1 of 1:
Improper bounds check on a memory buffer.
Function Pointer overwrite.
Heap Overwrite.

### CWE classification
Vulnerability 1 of 1:
CWE-120: Buffer Copy without Checking Size of Input ('Classic Buffer Overflow')
CWE-122: Heap-based Buffer Overflow

## Challenges

Authors Subjective Challenge Difficulty:
Discovering: Hard (due to resistance to fuzzing and extremely complex solver equations)
Proving: Easy
Fixing: Easy (add bounds checking)

This CB presents a number of challenges to a computer reasoning system. The difficulty lies in the transformation of the input set into the processed data after the RF front-end.  Due to its very nature fuzzing will be ineffective as RF receivers are naturally subjected to noise and are particularly well suited to identifying signals in the presence of noise. Also the CB introduces naturally AWGN (Additive White Guassian Noise) to every received sample. This CRS is therefore subjectively considered to be hard and designed to test beyond state of the art input reasoning capabilities and solvers. 
