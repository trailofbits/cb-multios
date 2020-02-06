# Stock_Exchange_Simulator

## Author Information

"Narf Industries" <info@narfindustries.com>

### DARPA performer group
Narf Industries (NRFIN)

## Description

An options exchange simulator that matches sell orders to buy attempts. 

### Feature List

This service supports posting sell orders for options holdings and account controls. All options order requests must be checksummed with a super-secret formula and XORd with a super-secret account key. A client can perform: buy, sell, and quotation options. His holdings are automatically managed by the service.

The binary also performs book keeping functions to make sure clients don't oversell their holdings or balances.

## Vulnerability 1
When a holding is maxed out (0xFFFFFFFF shares) there is an opportunity to trigger an error message. Attacker controlled values are directly used in the read location and write location during error handling to set an error code. The contents of this error code are transmitted back to the client and the program terminates on error. 

### Generic class of vulnerability
Untrusted pointer dereference.

### CWE classification
CWE-388 (Error Handling)
CWE-822 (Untrusted Pointer Deref)

### Challenges
The two challenges in this binary are (1) understanding and replicating the checksum algortihm for order types that are never seen in the poll traffic and (2) identifying accounts which will have overflowing holdings that trigger the error condition.

### Difficulty
- Discovering is easy
- Proving is medium
- Patching is easy
