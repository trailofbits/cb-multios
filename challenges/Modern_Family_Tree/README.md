# Modern Family Tree

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description:

In our society, family structures have changed such that traditional Family Tree software cannot properly model all current family structures. In response to this diverse environment, Family Relations Inc. brings to you our latest app, Modern Family Tree. It is the premier family tree building software for today's society.

## Feature List:

- Add Person: Add a new person to the family tree
- Biological Child: Define the biological child relation between a child and 1 or 2 parents
- Union: Mark Define Union relationship between 2 people.
- Separation: Remove the Union relationship between 2 people.
- Adopted Child: Define the adopted child relation between a child and 1 or 2 parents.
- Deceased: Mark a person a being deceased.
- Is related: Determine if 2 people are related.
- Degrees of separation: Determine if 2 people are related and if so, how many degrees of separation there are between them.

## Vulnerability 1

This vulnerability is a classic mistake where the author started indexing the buffer from 1 instead of 0. In service.c:separate\_two\_persons() the former partner buffer holds 2 values. The mistake here is that the buffer uses indexes 1 and 2 instead of 0 and 1. So, when the second value is written to the buffer, the data is written beyond the end of the buffer. Due to the alignment of the data in the struct, writing a Relation after the end of the former partners buffer will overwrite the shift function pointer and the next Person pointer. The shift function pointer will be the person\_id from the relation, while the next Person pointer will be the Person pointer from the relation.

To trigger this vulnerability, a sequence of operations needs to happen that achieves the following. First, person1 and person2 have to enter a union relationship. Next person1 and person2 have to adopt a child. And then person1 and person2 have to separate. Then person1 and person3 have to enter a union and then separate. At this point, the Relation for person3 will have overwritten the shift pointer and the next pointer in person1. Then person1 needs to re-adopt the same child. This will trigger the call to unset\_adopted\_child, the overwritten shift function pointer, resulting in TYPE 1 POV.

person3's ID will be the function pointer (IP\_VAL) and person1's ID will be the value in the registry (REG\_VAL)

### Generic Class of Vulnerability

Heap buffer overflow
Indexing beyond end of buffer
Off-by-one error

### CWE Classification

CWE-122 Heap-based Buffer Overflow
CWE-129 Improper Validation of Array Index
CWE-193 Off-by-one Error
CWE-788 Access of Memory Location After End of Buffer

### Challenges

* A static analysis tool should be able to easily detect the write beyond the end of the static former partners buffer.
* A fuzzer will have a harder time finding the POV, because it's not the content of any values that matter as much as the specific sequence of operations between a set of 3 people.
* It will be challenging for the automated system to determine the correct sequence of operations to trigger the POV. Additionally, the sequence of operations has to be applied to the same person and child to trigger the vulnerable path.

### Difficulty

* Discovering is easy
* Proving is hard
* Fixing is easy

## Vulnerability 2

This vulnerability is caused by the same problem as Vulnerability 1, except it is triggered in a different block of code.

This vulnerability is a classic mistake where the author started indexing the buffer from 1 instead of 0. In service.c:separate\_two\_persons() the former partner buffer holds 2 values. The mistake here is that the buffer uses indexes 1 and 2 instead of 0 and 1. So, when the second value is written to the buffer, the data is written beyond the end of the buffer. Due to the alignment of the data in the struct, writing a Relation after the end of the former partners buffer will overwrite the shift function pointer and the next Person pointer. The shift function pointer will be the person\_id from the relation, while the next Person pointer will be the Person pointer from the relation.

To trigger this vulnerability, a sequence of operations needs to happen that achieves the following. First, person1 and person2 have to enter a union relationship. Next person1 and person2 have to adopt a child. And then person1 and person2 have to separate. Thus far, it's the same as Vulnerability 1. However, this time, person2 and person3 have to enter a union and then separate. At this point, the Relation for person3 will have overwritten the shift pointer and the next pointer in person2. Then person2 needs to re-adopt the same child AND person2 must be the second person in the list of parent IDs passed to the function, so the get idx == 2 when calling set\_adopting\_parent(). This will trigger the call to unset\_adopted\_child on parent2 and thus the overwritten shift function pointer, resulting in TYPE 1 POV.

person3's ID will be the function pointer (IP\_VAL) and person2's ID will be the value in the registry (REG\_VAL)

### Generic Class of Vulnerability

Heap buffer overflow
Indexing beyond end of buffer
Off-by-one error

### CWE Classification

CWE-122 Heap-based Buffer Overflow
CWE-129 Improper Validation of Array Index
CWE-193 Off-by-one Error
CWE-788 Access of Memory Location After End of Buffer

### Challenges
* The additional challenge beyond Vulnerability 1 is that the parent2 ID must be the second ID in the list of parent IDs during the second call to set\_adopted\_child(), such that their shift function is triggered in the unset\_adopted\_child() function.
* A static analysis tool should be able to easily detect the write beyond the end of the static former partners buffer.
* A fuzzer will have a harder time finding the POV, because it's not the content of values that matter as much as the specific sequence of operations involving a set of 3 people.
* It will be challenging for the automated system to determine the correct sequence of operations to trigger the POV. Additionally, the sequence of operations has to be applied to the same person and child to trigger the vulnerable path.

### Difficulty

* Discovering is easy
* Proving is hard
* Fixing is easy
