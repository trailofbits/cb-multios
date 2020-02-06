# XStore

### DARPA performer group
Kaprica Security (KPRCA)

## Description

XStore is a data storage system using XPACK as a serialization/deserialization layer. XPACK is a binary data serialization spec that supports the encoding of many commonly used types, such as boolean, integer, string, raw bytes, array, and map. XStore provides APIs to store, lookup, and delete the entry to/from the storage. In order to make it easier to debug, it also supports to turn on and off the debug mode, when provided the correct debug key, to allow the admin to print the items currently in the system.


### Feature List


```
- Store
  - IN: map(string => _, string => _, ...)
  - OUT: array(string, ...)
  - Store key-value pairs and return an array of keys that are added to the system.
  
- Lookup
  - IN: array(string, string, ...)
  - OUT: map(string => _, string => _, ...)
  - Retrieve the values associated with the given keys. The value is None, if not found.
  
- Delete
  - IN: array(string, string, ...)
  - OUT: map(string => _, string => _, ...)
  - Similar input/output behavior as lookup, but delete the pairs that are found.
  
- (Debug)
  - IN: array(bool, debug_key)
  - OUT: bool
  - Turns on or off the debug mode.
  
- (Print - Only activated when debug mode is on)
  - IN: UINT64 (number of elements to print, 0 means everything)
  - OUT: N/A
  - Prints out elements in the system.
```

## Vulnerability

### Vuln 1

In `print_bytes` function in `service.c`, the BYTES-type data are escaped for the bytes that are not alpha-numeric. In doing so, 1 raw byte becomes 3 bytes (\XX), resulting a possible stack buffer overflow of `escaped` buffer.

#### Generic class of vulnerability

Stack-based Buffer Overflow

#### CWE classification

CWE-121: Stack-based Buffer Overflow

#### Challenges

 - Interesting/uncommon data structure (treap)
 - Lots of recursion (for both serialization and underlying treap data structure)
 - Vulnerability not immediately triggerable (Must go through DEBUG => PRINT)

#### Difficulty

 - **Discovery**: easy
 - **Proving**: hard
 - **Patching**: easy
