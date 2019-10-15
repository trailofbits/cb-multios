# On_Sale

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description:

Every vendor needs a point-of-sale product, so we have created the new and improved On Sale POS product featuring a package of predefined product sales options to make it easier for a vendor to put products on sale.

Upon installation of On Sale, the system is preloaded with all of the vendor's products. However, we know that product lines can change, so we've implemented features to update the product line with ease.

## Feature List:

Purchase - Process the purchase of one or more products to calculate the total owed by the customer.

Check - Determine the model number, cost, and description of the product that is associated with a barcode. If the product is on sale, this check will return the sale price. 

Add Product - Add a new product to the system

Remove Product - Remove a product from the system

Update Product - Update a product in the system

List Products - List all products. Only barcodes by default, but you can include other data depending on options provided.

On Sale - Set a product to be on sale using one of the options from the revolutionary sale package

Off Sale - Set a product back to full price and end the sale.

## Vulnerability 1

In the do\_add() function in products.c:240, the size of the recv\_until\_delim\_n() call is larger than the description buffer storing the received bytes. In the unpatched version, the size is sizeof(Product), which is 24 bytes larger than the buffer having size of MAX\_DESC\_LEN. When receiving the product description having more than MAX\_DESC\_LEN bytes, the extra bytes will overwrite the product's model\_num, cost, sfn pointer, and 12 bytes of the heap metadata in that order. For the POV, we overwrite the model\_num, cost, and sfn pointer. The sfn pointer points to the current sale function, which takes the model\_num and cost as parameters. And the sale functions pass those 2 parameters via registers. So, the next time do\_check() is called on this product and the sale price is read, the POV controls the sfn function pointer as well as it's 2 parameters. When the sfn() is called in do\_check(), it will crash and make a TYPE 1 POV.

### Generic Class of Vulnerability

Heap Buffer Overflow
Improper Bounds Checking

### CWE Classification

CWE-122: Heap-Based Buffer Overflow
CWE-131: Incorrect Calculation of Buffer Size
CWE-787: Out-of-bounds Write
CWE-788: Access of Memory Location After End of Buffer

### Challenges

* There are a large number of product preloaded into the inventory and there are 100 predefined sale functions. This was an effort to make the binary larger in case that causes problems for any analysis tools.
* The do\_add() function can be accessed by a fuzzer once the fuzzer learns the command to reach that function. A solver could do this easily as well. Also, it should be relatively easy to figure out where the buffer overflow is happening on the receive call.
* It will be more challenging to learn that the do\_check() function has to be called on the exact same product that was added in order to trigger the POV. The large number of products preloaded into the inventory adds distracting product barcodes when creating this POV.
* Fixing the overflow should be pretty easy.

### Difficulty

* Discovering is easy
* Proving is medium
* Fixing is easy

## Vulnerability 2

In the do\_update() function in products.c:312, the size of the recv\_until\_delim\_n() call is larger than the desc\_buf buffer storing the received bytes. In the unpatched version, the size is sizeof(Product), which is 24 bytes larger than the buffer having size of MAX\_DESC\_LEN. When receiving the product description having more than MAX\_DESC\_LEN bytes, the extra bytes will overwrite the function local variables and saved values on the stack. It overwrites, bc[], desc\_copy, p, bytes_recvd, and the next 4 bytes on the stack in that order. For the POV, we overwrite the bc, desc\_copy and p. The bc doesn't matter. The desc\_copy is a function pointer that is used to copy the new description buffer contents into the existing product's description buffer. The product pointer p is used in the first parameter to this function call because it requires the address of p->desc. So, this POV controls the desc\_copy() function pointer as well as it's first parameter. Since the desc\_copy() function passes its parameters via registers, this can be made to crash and make the TYPE 1 POV.

### Generic Class of Vulnerability
Stack Buffer Overflow
Improper Bounds Checking


### CWE Classification
CWE-120: Buffer Copy without Checking Size of Input
CWE-121: Stack-based Buffer Overflow
CWE-131: Incorrect Calculation of Buffer Size
CWE-787: Out-of-bounds Write
CWE-788: Access of Memory Location After End of Buffer

### Challenges
* There are a large number of products preloaded into the inventory and there are 100 predefined sale functions. This was an effort to make the binary larger in case that causes problems for any analysis tools.
* The do\_update() function can be accessed by a fuzzer once the fuzzer learns the command to reach that function. This should be relatively easy. 
* It should be relatively easy to figure out where the buffer overflow is happening on the receive call in do\_update().
* What is more challenging is that the analysis tools have to know to call the do\_list() function to get a list of valid barcodes that can then be used in the do\_update() function.
* Additionally, the do\_list() function takes a set of options. Those options determine how much data is returned for each product. When testing those options the code only checks to determine if they are odd or even. This will make a large number of valid inputs for these values that will give widely differing outputs. This should provide some distraction for analysis tools.
* Fixing the overflow should be pretty easy.

### Difficulty

* Discovering is easy
* Proving is medium
* Fixing is easy
