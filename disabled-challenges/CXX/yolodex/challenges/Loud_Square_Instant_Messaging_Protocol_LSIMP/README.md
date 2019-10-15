# CGC Challenge Binary (KPRCA\_00033): Loud Square Instant Messaging Protocol (LSIMP)

### DARPA performer group
Kaprica Security (KPRCA)

## Description

This service is an implementation of the LSIMP message parsing, which is used in
White Phones. The protocol is very simple, but fast and secure by employing a binary data protocol and obfuscation techniques.

### Feature List

**Funtionality**

- Secure mode through key'd XOR
- Out-of-order data transmission for secure messages
- Guard value for detecting packet corruption
- Batch process for queued messages

**Protocol**

- Operation Types:
  - QUEUE queues a message
  - PROCESS processes the message queue
  - QUIT closes connection
- Message Types:
  - HELO initializes the connection
    - version: protocol version
    - secure_mode: flag specifying obfuscated mode
    - ttl: number of valid messages after this message
  - KEYX exchanges the key; only used for secure messages
    - key: variable length key
    - key_len: length of the key
    - option: flag specifying how the key should be used
  - DATA only used for secure messages; should come after KEYX
    - seq: sequence number
    - data: variable length data
    - data_len: length of the data
  - TEXT used for clear text messages
    - msg: variable length text message
    - msg_len: length of the text message

HELO message must come first. Then, following messages up to 'ttl' is parsed. If the number of messages reaches 'ttl', new HELO message needs to be processed. Only one 'mode' can be used for one HELO session.

Option field in the key exchange message defines two modes:

  - prepend/append: In order to make it more 'secure', 4 byte dummy data is either prepended or appended to the original data.
  - inverted/as-is: The key used for secure mode is either (bit-wise) inverted or used as-is.

## Vulnerability

- One operation 'packet' may contain multiple messages; Although, it results in one message (last seen).
- When parsing a message, it updates the message object data, including the message type
- With a different message type, different offset of the message object is set (with user-controlled data)
- By making it back to the original type (but not supplying data), manipulation of field is possible

### Generic class of vulnerability

Type confusion error

### CWE classification

CWE-843: Access of Resource Using Incompatible Type 'Type Confusion'

## Challenges

- Must figure out how to initiate and interact with the protocol
- Must realize that modifying the type and data for the internal object is possible
- Cause a type confusion to overwrite the pointer to a buffer
- Trigger the bug by making it to process the message