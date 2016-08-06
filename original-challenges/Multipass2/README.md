# CGC Challenge Binary Template

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

This is Multi-Pass transaction processing and storage environment.

A Multi-Pass is an RFID enabled card used to make purchases at gas stations, restaurants, vending machines, convenience stores; pay transit fares; and rent movies and cars.

### Feature List

The following transactions are available:
- Make purchase (use multi-pass card to make a purchase from a vendor)
- Refund purchase (use multi-pass card to refund a previous purchase)
- Balance inquiry (use multi-pass card to query its balance)
- List transaction history (use multi-pass card to query the list of recent transactions)
- Issue new Multi-Pass (request a new multi-pass card)
- Add funds to Multi-Pass (use multi-pass card to add funds to the balance)

## Vulnerability

This environment is not ACID compliant, so some transactions are composed of multiple parts: two or three of the following list: (Initiation, Authentication, Operations, Finalization). And each transaction ends with a completion message (Finalization), leaving open the possibility for other transactions to take place between the time that a previous operation completes the Operations phase and starts the Finalization stage.

For the first vuln:
All purchases are stored in memory along with the transaction. The transaction is created in the Initiation or Authentication phase. The purchase is added to the transaction during the Operations phase of a purchase. When a Refund purchase transaction is processed, the purchase data for a previous transaction is deleted from the transaction and its memory is deallocated. If the pointer in the transaction that used to point to the purchase data, is accessed before the Finalization phase, it will result in a Null pointer dereference.

By making a purchase and then sometime later processing a refund for that purchase (Authorization and Operation only), it is possible to perform a transaction history listing (Authorization, Operation, and Finalization) before the refund transaction Finalization phase is processed. This results in a null pointer access attempt during the Operation phase of the history listing transaction.

Specifically, in service.c, the refund_purchase() function starting at line 183 is called during the Operation phase of a refund transaction. The transaction_destory() function should be called from refund_purchase() around line 223, as it is in the patched version. The vulnerable version of the CB, calls transaction_destroy() instead from process_fin() at line 280. process_fin() is called during the Finalization phase of each transaction type. Having transaction_destory() called outside of refund_purchase() opens up the possibility for other transactions to read the transaction history which queries all transactions, including the transaction that is in the middle of being destoryed.

For the second/third vuln:
These two vulns occur for the same reason, but are reached through different paths. The fundamental problem is that the HISTORY command will return the transaction history, and it does not check the state of the transaction prior to sending the transaction. In the case of the PURCHASE or RECHARGE transactions, the details pointer is NULL until the OPS phase is completed. Thus, if either of those transactions has completed the AUTH phase, and then the HISTORY transaction's OPS phase is processed, a null pointer access will be attempted.

Specifically, in mp.c, the transaction_send_details() function did not check whether a transaction has details before it tries to send the details. The solution is to skip sending of details when a transaction is in the AUTH state.

### Generic class of vulnerability

Use after Free
NULL Pointer Dereference

### CWE classification

NULL Pointer Dereference
CWE-476

## Challenges
* Understand the multi-phase binary protocol that is slghtly different for the ISSUE operation vs the rest of the operations.
* Understand the collection of operations available to the system.
* Learn that the AUTH, OPS, and FIN components of a transaction can have parts or all of other transactions interspersed between them. 


