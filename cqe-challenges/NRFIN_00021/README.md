# CGC Challenge Binary Template

## Author Information

"Jason Rogers" <info@narfindustries.com>

### DARPA performer group
Narf Industries (NRFIN)

## Description

Double your money with our High Frequency Trading Algo. We unleash the power of pair trading at cyber speed to work the margins and deliver returns. 


### Feature List

To begin a trading session, provide our Algo with an initial trading deposit. Our Algo will integrate with all standard real-time quote feeds, looking for statistical arbitrage in the historically correlated stocks that you select. Once we've doubled your money, a notification will be sent. 


## Vulnerability
This service has two vulnerabilities. 

The first vulnerability is a null pointer dereference due to an assumption that memory has already been allocated to a pointer. Once enough records have been sent to move the service out of learning mode, the updateStockValues function will be called to iterate through the array of purchased stocks and update their current price. If a "Balance" record was never sent, this array will not be initialized yet, causing a null pointer dereference. To patch this vulnerability, all for loops that iterate through the portfolio->stocks array should ensure that the array has been initialized.  (CWE-476 Null Pointer Dereference)

The second vulnerability occurs the second time the portfolio->stocks array is enlarged in the getNextFreeEntry function to accommodate more stock purchases. In order to purchase a stock, the pair trading algorithm must receive a quote for two stocks such that their price relative is greater than or less than a standard deviation away from the mean of all price relative computations that have been received over the course of the session. When the portfolio->stock array is enlarged the second time the new size will be less than the old size due to an integer overflow. When the old array is copied into the new array it will go beyond the length of the new array, leading to an out-of-bounds write. To patch this vulnerability the overflow should be detected, and the service should terminate. 

### Generic class of vulnerability
NULL Pointer Dereference
Integer Overflow or Wraparound
Out-of-bounds Write

### CWE classification
CWE-476: Null Pointer Dereference
CWE-787: Out-of-bounds Write
CWE-190: Integer Overflow

## Challenge

1) Determine how the service expects the user to interact with the service.

2) Understand how the input provided to the service is used to determine when a stock should be bought or sold.  
