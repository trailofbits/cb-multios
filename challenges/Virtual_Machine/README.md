# Virtual_Machine

## Author Information

"Jason Williams" <jdw@cromulence.com>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This service is a simple implementation of a virtual system simulator. It includes a simple flat model Memory Management Unit (MMU), Central Processing Unit (CPU) and Direct Memory Access (DMA) controller. The CPU is simple 16-bit processor with 16 general purpose registers, registers 0-15, with 15 being permanently dedicated as the Program Counter (PC). DMA devices include two peripherals a read and write peripheral for sending data via transmit/receive.

### Feature List

This service features 3 central components. A CPU, MMU, and DMA controller. In addition a simple CLF (Cromu Loader File) loader is implemented for loading the virtual subsystem. Upon initial connection to the service it expects a 4-byte 32-bit value indicating the file size of the incoming CLF file. The file is then loaded into memory by parsing the load sections in the file and loading them into the MMU controller. Simple page protections is supported including READ/WRITE/EXECUTE page protections. The DMA controller supports two peripheral devices a CReadDevice and CSendDevice, one for sending data out over STDOUT and for reading data over STDIN. The DMA controller is setup using two registers, one for specifying the address for the DMA access and the next register for the DMA length. Basic CPU arithmetic supported includes: Addition, Subtraction, Multiplication and Division. Also supported is GetRand and GetSeedMaterial instructions that read data from a random number generator and GetSeedMaterial that partially uses magic page data.

## Vulnerability

There is 1 vulnerability in this service. 

This vulnerability is a rather simple failure to properly check the bounds of a memory array access. In the case of DMA operations it is possible to setup multiple DMA operations simultaneously. Each clock cycle of the simulator allows 1-byte of a DMA transfer to occur until the transfer is completed. The simulator has an array of active DMA transfers that is sized at 5 entries. Using the DMAInit, DMARead or DMAWrite instruction it is possible to initiate more than 5 DMA transfers, causing, an overflow of the array and a write out of bounds operation. The next consecutive address in memory to be clobbered by this operation is an array of pointers for the DMA peripherals. Each DMA peripheral is an overriden class of the base class CPeripheral. Each derived peripheral class overrides the Read and Write operations of the peripherals. It is possible to overwrite the DMA peripheral array and replace the class pointer with a fake class object that results in a virtual function pointer call controlled by user input. Next a push, pop, pop, ret trampoline can be found for setting a desired register for expressing a type 1 POV.

### Generic class of vulnerability
Vulnerability 1 of 1:
Improper bounds check on a memory buffer.
Heap based buffer overflow

### CWE classification
Vulnerability 1 of 1:
CWE-787: Out-of-bounds Write
CWE-122: Heap-based Buffer Overflow

## Challenges

Authors Subjective Challenge Difficulty:
Discovering: Medium/Hard
Proving: Easy
Fixing: Medium

This CB has 1 vulnerability and can be difficult for a CRS to discover due to the large number of instructions and states of the input. It is however possible that a fuzzer using a proper polling input could duplicate a DMARead or DMAWrite call under the right circumstances and uncover the overflow.
