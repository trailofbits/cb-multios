# Snail_Mail

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description:

Sending paper by courier is pretty passe' these days, but we still find it valuable. Snail Mail is an application that can simulate the whole process of delivering paper mail.

## Feature List:

Add New Address - The mail clerk can input a new address into the system.

List Addresses - The mail clerk can view the list of valid addresses.

Receive Mail - The mail clerk recieves mail from the originating sender and puts the mail into the Received Mail box to be sorted. The originating sender must provide valid postage before the mail clerk will accept the mail.

Sorting - The mail clerk can send the box of mail through the mail sorting machine. The sorting machine will sort mail by address and if any are addressed to an unknown address, they will be dropped into the Undeliverable Mail box.

List Undeliverable Mail - The mail clerk can view the list of undeliverable mail.

Delivery - The mail carriers take the sorted mail and deliver it. This also includes re-delivery of mail returned to sender.

Return to Sender - The mail clerk can re-route the undeliverable mail back to the originating sender and put it in the Received Mail box. If the originating sender's address is also underliverable, the mail is put into the Lost Mail box.

List Lost Mail - The mail clerk can view the list of lost mail.

Destroy Lost Mail - The mail clerk can destory all lost mail.

Buy Postage - The mail clerk can sell postage to the customer.

## Vulnerability 1

In postage.c:get\_new\_stamp(), the serial number of each stamp is a series of 3 bytes from the flag page. Each consecutive stamp gets the next 3 bytes from the flag page. When it reaches the end of the flag page, it wraps back to the start.. If more than 1 stamp is purchaseed, the serial numbers can be concatenated to create longer sequences of bytes from the flag page. 

### Generic Class of Vulnerability

Information Leakage

### CWE Classification

CWE-201: Information Exposure Through Sent Data

### Challenges

* The information leakage only leaks 3 bytes at a time. This means the CRS has to learn which command leaks flag page bytes. After that, the CRS has to learn that the bytes being leaked in each subsequent stamp are consecutive. Then the CRS can concatenate the bytes from 2 consecutive stamps together to create a single POV TYPE2\_VALUE.

* All of the commands return 2, 3, or 8 byte buffers. So, the CRS will have to use taint tracking to determine which returned buffer contains leaked data and associate that returned buffer with a specific input command. Directly replaying the bytes returned from running a command in dumb fuzzing will not work.

* There are only 11 valid 4 byte command buffers. So, blind fuzzing will be of little use. Smart fuzzing that takes advantage of known command buffers can likely get some interaction with the CB. However, the result of each command depends on the internal state of the mailboxes. So, the CRS will have to model that internal state as well.

### Difficulty

* Discovering is easy
* Proving is medium
* Fixing is medium
