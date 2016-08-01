# Document Rendering Engine

## Author Information

"Jason Rogers" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

You've done your research and written your paper, and now it's the tough part: formatting the document. If only someone could take all your hard work and turn it into a beautifully formatted document. 

If this is you, then the new Document Rendering Engine by DocuSoft is the product for you! With its state-of-art document macro engine you can focus on the content while it takes care of the presentation.

### Feature List

Using DocuSoft's Document Markup Language, you specify the structure of your document using the following elements:

1. Pages: You can specify the length, width and the number of columns per page.
2. Paragraphs: They act as container for text, lists and tables.
3. Lists: You can add elements to lists, including sublists. You may also specify the numbering type which includes numerals, bullets, roman numerals, upper case characters, and lower case characters.
4. Tables: You can specify the number of rows and fields per row. Also specify either line or star border types. Each Field can contain either text or lists.

Using the Document Markup Language, you may also specify custom macros. Custom macros allow you to create your own custom layouts that can be applied to documents. The product comes preloaded with common custom macros including,

* Outlines
* Bulleted Lists
* 4x4 and 5x5 Tables

## Vulnerability 1

The first vulnerability in this CB is a Type 2 caused by an incorrect calculation of the buffer size in the romanNumeral function. By not allocating enough room for the romanNumeralString a buffer overflow can occur which overwrites the null-terminator of the character string. This will cause an out-of-bounds read of the adjacent memory address when strcat is called. If the out-of-bounds read is triggered when the flag value is in the adjacent memory chunk, the flag will be sent to the user. To cause the overflow the unsigned integer sent to romanNumeral must be such, that it creates a roman numeral that overflows the buffer.

### Generic class of vulnerability

Incorrect Calculation of Buffer Size
Heap-based Buffer Overflow
Out-of-bounds Read

### CWE classification

CWE-131: Incorrect Calculation of Buffer Size
CWE-122: Heap-based Buffer Overflow
CWE-125: Out-of-bounds Read
CWE-788: Access of Memory Location After End of Buffer

### Challenges

1. Detecting the miscalculation will require understanding how the roman numeral string construction depends on the value passed to it. For example, the value 8 creates a larger string than the value 9.

2. The Roman numeral function is called when a list object with its 'type' set to 'roman' is rendered. A successful attack will require understanding how to create a valid document with a sufficient number of list elements to create a roman numeral string that is capable of overflowing the buffer. 

### Difficulty
- Discovering is medium
- Proving is medium
- Patching is easy

## Vulnerability 2

The second vulnerability is a Type 1 that requires exploiting two different vulnerabilities. The first is a incorrect calculation of the buffer size that leads to a buffer overflow in the getObject function. When the getObject function is called the first time it allocates a heap-based buffer that is adjacent to the 'element' macro. Overflowing the buffer can overflow the 'body' field of the macro, which is a function pointer. This will permit controlling the value of the instruction pointer when the 'element' macro function is called.

The second part is in the list function where a custom list type is allowed. By providing a list type name that is greater than 3 characters, you can overwrite a stack-based buffer adjacent to the 'macros' variable that contains the list of macros that is passed to the 'element' macro. This will permit controlling the value of the ecx register with the 'element' macro is called. 


### Generic class of vulnerability

Incorrect Calculation of Buffer Size
Stack-based Buffer Overflow
Out-of-bounds Write
Access of Memory Location After End of Buffer

### CWE classification

CWE-131: Incorrect Calculation of Buffer Size
CWE-121: Stack-based Buffer Overflow
CWE-787: Out-of-bounds Write
CWE-788: Access of Memory Location After End of Buffer

### Challenges
1. The vulnerability only overwrites a function pointer the first time getObject is called. So this requires understanding the alignment of the allocated buffer in memory.

2. The 'getObject' function must complete and produce a valid document Object to be rendered later. This will require understanding how to submit the payload in a object tag that still creates a valid renderable object.

3. The 'list' function is called when a list object is rendered. In this case the 'list' object must include a custom type long enough to overflow the buffer. So a valid document with a list containing a custom type long enough to cause the buffer overflow must be written in the markup language.

### Difficulty
- Discovering is easy
- Proving is medium
- Patching is easy

