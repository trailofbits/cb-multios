# ECM_TCM_Simulator

## Author Information

"Jason Williams" <jdw@cromulence.com>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This service is a simulator for an ECM and TCM controller modules. The Engine Computer Module and Traction Controller Module reside on a common shared LAN bus. The simulation allows the user to send preformatted messages or custom binary messages on the shared bus during the simulation. This service is written in C++ and leverages two new CUtil classes a doubly linked list and string class.

ShortDescription: Simulator for an ECM (Engine Computer Module) and TCM (Traction Controller Module).

### Feature List

This service accepts a set of message bus commands that will be sent at specified command times to any simulation components on the message bus. This message bus is a shared bus between all components. The standard components on the message bus are the ECM and TCM modules at 0x13 and 0x14 addresses respectively. Broadcast messages can be sent to address 0xFF and all components will receive it. The simulation also will relay response messages sent to either address 0x0 or 0xFF during the simulation and ascii hex display the output of the simulation. The ECM module supports engine off/on commands, torque commands, Incoming Air Temperature (IAT), EGR Temperature, and a host of other parameters. The Traction Controller Module supports off/on commands and wheel speed set and read commands. All items on the component bus support an equipment ID, a unique 64-bit number set from the magic page. It is possible to verify the Equipment ID but not read it. Once a simulation is setup and all messages configured the simulation runs a tick counter at 50ms intervals for up to 2 minutes and sends the setup commands over the bus at their specified times and prints any received messages on the shared bus.

## Vulnerability

There is one type 2 vulnerability in this service. This vulnerability is in the TCM module on a read wheel speed command. To reach this vulnerability first the ECM and TCM must both be enabled. To do this it is required to turn on the engine on the ECM before sending the enable TCM command. At this point it is possible to issue a read wheel speed. Any read commands sent to the TCM without both being enabled and the engine on will not be processed. The TCM read wheel speed command consists of TLV field specifying the number and index of the wheel to read. Up to 4 wheel indexes can be read. A failure to check the index position allows a read outside the bounds of the array and allows the equipment ID to be read back 16-bits at a time. If the proper indexes are specified: 6,7,8, and 9 the entire 64-bits of the equipment ID can be read back. This will disclose up to 8-bytes from the magic page.

### Generic class of vulnerability
Vulnerability 1 of 1:
Improper bounds check on a memory buffer.
Memory disclosure

### CWE classification
Vulnerability 1 of 1:
CWE-125: Out-of-bounds Read
CWE-200: Information disclosure

## Challenges

Authors Subjective Challenge Difficulty:
Discovering: Medium (due to resistance to fuzzing and near infinite possible state depth)
Proving: Easy
Fixing: Easy (add bounds checking)

This CB presents a moderate difficulty in discovery due preliminary to the large surface area to attack and the near infinite state exploration that can occur. This is due to the nature of the service as a simulator and the ability to input a large number of commands into the system. It also requires the ordering of the commands to turn on the engine and enable traction control before it is possible to send the read wheel speed command to disclose the secret page memory.
