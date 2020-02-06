# CGC Challenge Binary (KPRCA\_00045): Sad Face Template Engine (SFTE)

### DARPA performer group
Kaprica Security (KPRCA)

## Description

Sad Face Template Engine provides a tempalte rendering service, where a user defines variables with values and submits a templated text to be rendered. The default tag identifier is **:(...):**

### Feature List

**Features**

- Define variables
  - Add new variables
  - Undefine variables
- View variables
- Submit templated text
- Render text

There are 4 supported types for a variable: _String_, _Integer_, _Float_, and _Bool_.

Template engine understands 3 tag types:

- Variable
  - `:(name):`
- Conditional Section
  - `:(@is_valid):Rendered only when is_valid is true!:(/is_valid):`
- Comment
  - `:(#sad comment):`


**Protocol**

- User-interactive interface (aka menu selection)

## Vulnerability

- There are 2 exploitable bugs in _sadface_render_ function.
- When the engine renders a given template, it fails to check for a buffer overflow.
- Specifically, when copying normal/static text from the input, the total length isn't checked to see that it will lead to a heap-based buffer overflow.
- When handling variable substitution, it also suffers the problem where the total length isn't validated against the maximum buffer size, leading to a heap-based buffer overflow.

### Generic class of vulnerability

Heap-based Buffer Overflow

### CWE classification

CWE-122: Heap-based Buffer Overflow

## Challenges

- Input is not directly used to generate the output. One must realize that, by carefully crafting the variables, it is possible to manimpulate the output to an exploitable condition.