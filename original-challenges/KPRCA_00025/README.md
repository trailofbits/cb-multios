# KPRCA-00025

## Author Information

"Andrew Wesie" <andrew.wesie@kapricasecurity.com>

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements an adventure game where the user has a team of monsters that they use to battle other monsters. Throughout the map, there are trainers to fight and treasures to find, plus a lot of wild battles along the way. The goal is to collect as many monsters as you can and level them until you defeat your enemies.

### Feature List

The game features a 100x50 tile map that is procedurally generated using a random walk, with monsters that scale in difficulty as you move away from the starting location. You can have up to six monsters on your team at any one time, and all of your extra monsters are stored in the bank with can hold up to 99 monsters. As you explore the map, you will eventually find the name changer, who can change the name of any monster on your team. The standard features, such as saving and loading games, are also included.

## Vulnerability

The vulnerability is an overflow of the m_name member of the Monster object in Monster.c:70 (set_name). There are two exploitable paths to the vulnerable function, either generate a bad input for the load_game deserialization or get to the name change object on the map and provide a bad input. Both of these methods have challenges: load_game requires bypassing a simple checksum, whereas getting to the name change object requires playing the game.

The second vulnerability is an integer overflow when deserializing the Map RLE data. If count is large, then the check of count + i will not be sufficient, and memset will crash.

The third vulnerability is use of uninitialized map objects when deserializing Map data. The map may contain objects IDs that are not initialized, and this will cause a crash later when the map is displayed.

The fourth vulnerability is a heap-based buffer overflow when deserializing Map data and the width and height are greater than the original width and height because the map array is not reallocated.

### Generic class of vulnerability
Heap-based Buffer Overflow

### CWE classification
CWE-122: Heap-based Buffer Overflow
CWE-190: Integer Overflow or Wraparound
CWE-908: Use of Uninitialized Resource

## Challenges

The challenges involved in each exploitable path was explained above. Additionally, the service was written in a custom object-oriented "framework" where almost all functions are called indirectly. The virtual tables for the objects are initialized at run-time, which may make analysis more difficult.
