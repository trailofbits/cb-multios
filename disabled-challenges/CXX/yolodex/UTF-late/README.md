# CGC Challenge Binary Template

## Author Information

"Maxwell Koo" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

I'm so UTF-8, you so UTF-late. This is a network-enabled file server, which
keeps all user files in memory for blazing-quick access. The API exposes a
public dropbox folder, while preventing access to the protected admin area. The
filesystem is UTF-8 aware, allowing arbitrary unicode filenames of a fixed
length.

Commands take the form of a 4-byte command identifier, followed by optional
arguments. Commands may produce output, but will always end in a 4-byte success
code, 0 on success or -1 on failure.

### Feature List

The following features are available:
 - Read file, accepts a filename and returns the contents of that file
 - Write file, accepts a filename and a size, writes the contents to a file
 - List files, lists all files in the dropbox folder

## Vulnerability

The UTF-8 decoding function does not properly handle overlong encodings, so it
is possible to defeat the input validation protecting the admin area and write
to files in that area. Files in the admin area contain a user-controlled pointer
value, which allows arbitrary write access to a large portion of the process'
address space.

### Generic class of vulnerability

Improper handling of unicode encoding

### CWE classification

CWE-20 Improper input validation
CWE-22 Improper limitation of a pathname to a restricted directory
CWE-176 Improper handling of unicode encoding
CWE-822 Untrusted pointer dereference

## Challenges

This CB is designed to test the ability for a CRS to comprehend complex string
functions and stateful processes spanning multiple invocations of a function.
UTF-8 is a complex variable-width encoding with many possible invalid byte
sequences. The decoder implemented in this CB handles this by running each
character through a state machine, invoking a function on each byte which
records its state into a output variable and its return code. Reasoning over
separate invocations of the decoder function is necessary in order to determine
an input which will lead to triggering the vulnerability. This CB is inspired by
several real-world path traversal and unicode vulnerabilities, including
CVE-2000-0884 in Microsoft IIS.

