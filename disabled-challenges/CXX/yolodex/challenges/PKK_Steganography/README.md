# CGC Challenge Binary (KPRCA\_00012): PKK Steganography

## Author Information

"Brian Pak" <brian.pak@kapricasecurity.com>

### DARPA performer group
Kaprica Security (KPRCA)

## Description

This service performs Least Significant Bit (LSB) steganography on a PKK file. It supports two modes: embed and extract. The user can provide a PKK image and the secret text to be hidden in the image with a specific format, or provide a PKK image that has hidden message inside to extract the message. The program expects a specific format (encapsulation) for an input.

### Feature List

This service supports the following features:

  1. **Embed a secret message**
  2. **Extract the hidden message**

The service accepts an input of the following format:

  - STEG_TAG (4 byte)
  - Total size (4 byte) [includes STEG_TAG]
  - PKK file size (4 byte) == N
  - PKK file data (N byte)
  - MODE_TAG (4 byte)
  - mode (2 byte)
  - TEXT_TAG (4 byte)
  - text data size (2 byte) == M
  - text data (M byte)
  - END_TAG (4 byte)

In case the input is for the *extract* mode, the text data size should be 0 and text data should be an empty string.

When the secret message is embedded into the image, it is first encapsulated into a special format:

  - SECRET_TAG (4 byte)
  - original (extracted) text data size (2 byte) == M
  - text data (M byte)
  - SECRET_END_TAG (4 byte)

## Vulnerability

There is a maximum length limit for the secret text to be embedded, which is set to 1000 bytes. However, when extracting the hidden text, the service blindly trusts the size field without validation.

Then, with a carefully crafted input (PKK with a hidden text data size set to a value larger than 1000 along with long enough data), it is possible to overflow the stack-based buffer that is used to reconstruct the embedded message to cause a crash.

Also, there's an integer overflow with large widht or height.

### Generic class of vulnerability

Stack Buffer Overflow

Integer Overflow

### CWE classification

Stack-based Buffer Overflow (CWE-121)

Integer Overflow or Wraparound (CWE-190)

## Challenges

This CB tests if the competitors can reason about the data flow and bit operations performed upon the input, since the size field needs to be correctly encoded (using LSB) to be parsed by the service.
