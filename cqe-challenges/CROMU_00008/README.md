# CGC Challenge Binary Template

## Author Information

"Jason Williams" <jdw@cromulence.co>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This service attempts to mirror a database service with expression based searching. This implementation supports 4 database records (firstname, lastname, username, and birthdate) in the internal database. Various commands are allowed to insert, remove, print, update, and find records in the database. The find command supports a relatively lightweight expression parser allowing operators to formulate simple expressions to find entries in the database such as (lastname == "Will" AND firstname == "Bob") would be an example expression.

### Feature List

This service supports database access update, removal, printing, and finding via relatively simple expressions. The database supports 4 entries for each record: firstname, lastname, username and birthdate. Birthdates are stored as month/day/year hour:minute:second. The search expressions (initiated by the find command) allow the formulation of multiple expressions with adjoining operators such as (firstname == "Joe" AND birthdate < 1/3/1990 10:33:43) is an example expression. Operators supported are ==, !=, >, and < for the database elements and AND and OR for joining result lists.

## Vulnerability

The vulnerability in this service is centered around two points. Firstly a find expression can overflow the shift/reduce expression stack when utilizing long expressions that are adjoined with paranthesis (these will defer the expression parsing). This can cause an overwrite of the expression stack resulting in an overflow to the adjoining memory location. The memory is structured such that the adjoining memory location is another data structure which holds jmp_buf data used by an exception handler routine that is implemented with a combination of setjmp/longjmp. This allows a specially crafted expression to overwrite the jmp_buf data structure and cause a resultant crash when an exception (such as Syntax Error) is triggered by an improperly formatted find expression. The resulting crash occurs when longjmp attempts to load the register state out of memory that has been corrupted by overflowing the expression stack.

### Generic class of vulnerability

Out of bounds write

### CWE classification
CWE-119: Improper Restriction of Operations within the Bounds of a Memory Buffer

## Challenges

This CB presents multiple challenges for automated exploitation. Firstly there is a simple login/logout state machine in the command parser preventing access to the find command until the operator is logged in. Next the numerous state possibilities presented by the input commands (insert, remove, print, update, find) represents an exponential state graph for the reasoning system to explore. Therefore depth first search methods will likely never explore the state graph appropriately to discover the necessary find expression. Lastly in the event that the state graph exploration is successful in overflowing the expression stack a reasoning system will need to understand the details of the jmp_buf buffer itself. This will allow the reasoning system to determine a vulnerability will occur when the call to longjmp is made and an attempt to load errant data out of the jmp_buf structure results in a program crashing. In general it is this CB authors opinion this will exercise the ability of a CRS system to chain together multiple capabilities necessary to discover this vulnerability.
