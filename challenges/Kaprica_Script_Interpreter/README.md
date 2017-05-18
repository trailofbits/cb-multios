# KPRCA-00038

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements a scripting language that is designed for processing text files. The script is executed on every record, where every line in the text file is processed as an independent record. Every record is then parsed into fields automatically according to the current script state.

### Feature List

The only input to the script is the current record. Parsing of the record can be controlled via field seperator and record seperator variables. Output can be either a print statement or a printf with a script provided format string.

The expressions support variable assignment, arithmetic and logical operators, and regular expression matching. The regular expression support is implemented using a variation of the Thompson NFA algorithm, so its run-time is O(nm) as opposed to competing algorithms that have an exponential run-time.

## Vulnerability

The first vulnerability, **eprintf.c:81**, is a classic printf vulnerability where an attacker can control a format string. The arguments to printf are script variables and there is inadequate verification of the type of the script variables. This allows an attacker to control a *char* pointer resulting in a memory leak or crash by providing the **#c** format with a number argument. Additionally, an attacker could leak a pointer by providing the **#x** format with a string argument.

The secord vulnerability is stack overflow via uncontrolled recursion in **regexp_parse**. By constructing a large expression with many unterminated open parentheses, the attacker can cause a crash via stack overflow with a small input.

The third vulnerability is a NULL pointer dereference in do\_print when get\_field returns NULL. This situation can occur when the length of field0 would be greater than 4096 bytes when appending the fields together.

The fourth vulnerability is a NULL pointer dereference in simplify when the input node is NULL. This can occur when the input string to regexp\_init is empty.

The fifth vulnerability is a NULL pointer dereference in eval_expression when the input expression is NULL. This can occur if an operator is missing an argument or a for loop is missing a post-condition expression.

The sixth vulnerability is a NULL pointer dereference in parse_statements when the program contains an empty code scope with a statement before and after it. This causes a NULL pointer to be inserted into the linked list of statements.

### Generic class of vulnerability
Arbitrary format string
Stack overflow

### CWE classification
CWE-134: Uncontrolled Format Sting
CWE-476: NULL Pointer Dereference
CWE-674: Uncontrolled Recursion

## Challenges

This challenge set implements a non-trivial scripting language; which is comparable to modern programs which usually include scripting languages. The scripting language is not as complex as JavaScript, but it is expected that the techniques to fuzz JavaScript interpreters would also be effective for this challenge set. Automatic patching of the vulnerabilities will be a significant challenge.
