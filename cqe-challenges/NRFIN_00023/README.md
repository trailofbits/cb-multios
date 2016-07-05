# CGC Challenge Binary Template

## Author Information

"Maxwell Koo" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

This is an electronic trading system for matching buyers and sellers. Users can
place buy and sell orders for various commodities and be automatically matched
according to price, quantity and priority.

The system takes a series of commands in 20-byte packets, and produces textual
output ending in a 4-byte sequence \x00\x00\x00\x00 on sucess, and
\xff\xff\xff\xff on failure.

### Feature List

The following commands are available:
- List stocks (list all of the stocks with open orders in the system)
- List orders (for a stock, list all open orders)
- Place order (place a buy or sell limit order for a stock)
- Check order (check the status of an order by ID)
- Cancel order (cancel a previously placed order by ID)

## Vulnerability

The system uses heap addresses as ID numbers, trusting users to only check ID
numbers for orders they have placed or have seen active from a list order
command. There are several possible fixes, the one implemented checks all IDs to
ensure they are members of the orders list.  See src/stock.c:132-153. Challenges
to patching involve a requirement for extra bookkeeping to ensure that supplied
ID numbers are valid. This information exists in the unpatched program, but
identifying the guards needed to validate ID numbers will involve a high-level
understanding of the functioning of the program.

The system uses a user-controlled signed integer to represent an offset into an
array without checking its lower bound, allowing accesses outside of the array.
The implemented fix resolves this by computing an unsigned hash value. See
src/stock.c:31-35. Patching will involve understanding which values will cause
out-of-bound array accesses, understanding the mapping between string values and
their hash values, and implementing guards to prevent invalid values from
corrupting program state.

The system does not validate the length of stock symbol names before performing
an unbounded copy to a heap-allocated buffer. The fix is to not use strcpy
unsafely on untrusted input, instead using strncpy. See src/stock.c:123-127.
This is an unbounded copy into a fixed-size buffer, patching will require adding
in length checks to remove the possiblity of overflowing the buffer on unsafe
operations such as strcpy.

The system uses heap allocated variables after freeing them. The implemented fix
ensures that all references to heap-allocated chunks are removed prior to
free-ing a chunk. See src/stock.c:88-92. Patching requires ensuring that all
aliases of a heap-allocated chunk are removed when the chunk is freed, in order
to ensure that dangling pointers aren't left into the freed chunk.

The system can be coerced to confuse a stock object as an order object or
vice-versa.This can be addressed separately to the prior vulnerabilities through
usage of mitigations and additional validations such as the simple tagging
scheme implemented in the patched binary. See src/stock.[c|h] for all checks
added against obj_tag. Patching will require detecting all operations which
operate on one type object or another, and adding in the appropriate type
checks.

### Generic class of vulnerability
Dereference of untrusted pointer
Integer overflow or wraparound
Improper validation of array index
Heap-based buffer overflow
Use after free
Access of resource using incompatible type

### CWE classification
CWE-822 Dereference of untrusted pointer
CWE-190 Integer overflow or wraparound
CWE-129 Improper validation of array index
CWE-122 Heap-based buffer overflow
CWE-416 Use after free
CWE-843 Access of resource using incompatible type

## Challenges

This CB is designed to contain several vulnerabilities of varying complexity in
order to effectively evaluate the strengths and weaknesses of a CRS.

- The dereference of an untrusted pointer should be apparent through most
rudimentary fuzzing approaches and from the leakage of a "heap-like" address
for order IDs.

- The signed integer array index is slightly harder to detect, requiring fuzzing
which does not limit names to ascii values in order to generate a hash value
which will trigger the vulnerability.

- The buffer overflow, while perhaps apparent to a human auditor, will require
an invalid argument value to be passed to the place order command (buy or sell
argument is typically 0 or 1, needs to not contain nulls) along with strange
prices and quantities to have an observable effect on the program's state.

- The use-after-free bug requires analysis that spans multiple requests in order
to create a sequence of commands which will cause program misbehavior, which
are dependant on the global state of the program.

- The type confusion vulnerability can be triggered in several different ways,
but represents a distinct class of issue with this program.

