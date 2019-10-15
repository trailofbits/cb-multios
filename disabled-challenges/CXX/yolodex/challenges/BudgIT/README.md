# CGC Challenge Binary Template

## Author Information

"Jason Rogers" <info@narfindustries.com>

### DARPA performer group
Narf Industries (NRFIN)

## Description

Not sure where all your money is going? Having trouble staying with in your limits? Try BudgIT, the new personal finance management tool. BudgIT will alow you to set a budget, track your expenses, and let you know when you OVER BUDGET! So get started today on the road to financial success. 


### Feature List

To begin, provide BudgIT with a budget category, e.g. Groceries, followed by your spending goal for the month. Then, each time you spend money on a budget category, enter the transaction into BudgIT. BudgIT will let you know when you have reached or surpassed your budget. If at any time you are unsure of how much you have left, BudgIT can provide you a simple report that shows all your budget categories, their remaining budgets, and a total of all budgets. 


## Vulnerability
This service has two vulnerabilities. 

The first vulnerability is an off-by-one error that results in an out-of-bounds write. The service will create a buffer on the heap that is large enough for 128 budget categories. The check in the setMap function allows the creation of 129 categories, leading to the out-of-bounds write.

The second vulnerability is a use of pointer subtraction to determine size vulnerability that causes an out-of-bounds read. The getSize function uses a loop to find the last budget entry in the list, and then subtracts its address from the start of the list to calculate the size. By selectively removing a budget entry and creating a new budget entry, one can control the output of the getSize call in sendReport to read memory outside the bounds of the buffer.

### Generic class of vulnerability
Heap-based Buffer Overflow
Out-of-bounds Read
Incorrect Calculation of Buffer Size
Off-by-one Error
Use of Pointer Subtraction to Determine Size
Out-of-bounds Write

### CWE classification
CWE-122: Heap-based Buffer Overflow
CWE-125: Out-of-bounds Read
CWE-131: Incorrect Calculation of Buffer Size
CWE-193: Off-by-one Error
CWE-469: Use of Pointer Subtraction to Determine Size
CWE-787: Out-of-bounds Write

## Challenge

1) Determine how budget entries are created, stored, and removed by interacting with the service.

2) Understand how the getSize call can be manipulated by creating and removing specific budget entries.
