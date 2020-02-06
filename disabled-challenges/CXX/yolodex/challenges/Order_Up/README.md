# Order_Up

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description:

The hottest new thing in restaurants is to place your order at a fancy little computer at your table and have your food magically be delivered by robots.

To help assist future restaurants with their roll out of this technology, we've created Order Up. Order up can handle all of the table, customer, and order functionality that you need to run a restaurant. All you have to do is put a nifty computer at each table, one at the front entrance, and one in the kitchen.

## Feature List:

Each table has a 3 course dinner. It starts with an appetizer, then the main course, then the dessert.

When a table either gets newly seated customers or the customers have finished their current course, they are presented with the menu to choose their next food items.

This CB Set is designed such that cb\_1 represents the hostess and waitress and cb\_2 - cb\_10 are the tables. The client connects to cb\_1 to issue commands. Then cb\_1 will dispatch the hostess or waitress to the proper tables to handle each command. There are several standard commands that cb\_1 will accept from a client, as listed here:

Add Customers - When new customers arrive at the restaurant, they are placed on a waiting list. As seats open up, they are seated.

Table Status - Check the status of each table in the restaurant.

Get Orders - Collect orders from all customers at every table that is ready to place another order.

Order Up - Deliver all orders to all customers at every table that has an order outstanding.

Bus Tables - At every table where the customers are finished eating, clear the table and reset it.

Each of cb\_2 through cb\_10 functions identically, except that they can have a different number of seats at each table, which is determined at run-time.

## Vulnerability 1

In give\_food\_to\_customer() in table.c:300ish cb\_2, there exists the ability for the client input to cause type confusion.

This function uses the ftype paramter provided by the client to determine the size of the food buffer. It then uses a different parameter, table.status, to determine which food buffer to write into. If the table.status does not match the o->ftype, then the wrong food will be written to the customer's food buffer associted with the current table.status. This is a problem, because the Meal food type is much larger than both the Appetizer or Dessert food types.

To exploit, send a Meal when the table.status is expecting a Dessert. This will cause the call to accept_food() to overwrite the Customer.fi ptr and the Customer.next ptr with the Meal.main data, it will also corrupt the heap data with the remainder of Meal.main, as well as Meal.veggies, Meal.side, and Meal.next (which is NULL) data.

Then when the food inspection function is called c->fi(), the fi pointer has been overwritten by client provided data and will cause TYPE 1 POV.

Since, the inspect\_*() functions pass its parameters via registers, the Customer.id for the customer currently being fed resides in EDX.

There are a number of ways to patch this vulnerability. The easiest is to remove the ability for the buf location and bufsz to get out of sync, by removing the call to get\_delivery\_foodtype\_from\_table\_status() at table.c:300. An equally simple solution is to move that function assignment to the top of the give\_food\_to\_customer() function. Either change will result in the bufsz matching the size of buf and thus prevent POV.

### Generic Class of Vulnerability

Heap Buffer Overflow
Type Confusion


### CWE Classification

CWE-122: Heap-Based Buffer Overflow
CWE-131: Incorrect Calculation of Buffer Size
CWE-704: Incorrect Type Conversion or Cast
CWE-787: Out-of-bounds Write
CWE-788: Access of Memory Location After End of Buffer
CWE-805: Buffer Access with Incorrect Length Value

### Challenges

* The biggest challenge this CB was designed to test was how well a CRS can handle a CB Set with many CBs in it. The max number of CBs that are allowed in a CB Set is 10, so this CB has 10 CBs in it.
* Next, this vulnerability exists in 9 of the 10 CBs. So, while each provided POV will only test one of them, they can still be POV'd if that one is patched, but the others 8 are not. Each POV 1-9 is targeted at cb\_2 - cb\_10 respectively.
* Next, this CB Set will challenge a CRS to notice that multiple CBs are the same. This will determine if/how they can transition the patch from one CB to the others. As well as test if the CRS will patch each CB on their own, but in a different way.
* The I/O between the poller/pov and cb\_1 is not too difficult, which should allow for some successful exploration with fuzzers and solvers.
* The improper buffer size length calculation can be fixed in a few ways that are not too difficult.

### Difficulty

* Discovering is easy
* Proving is medium
* Fixing is easy

## Vulnerability 2

In give\_food\_to\_customer() in table.c:300ish cb\_3, there exists the ability for the client input to cause type confusion.

This function uses the ftype paramter provided by the client to determine the size of the food buffer. It then uses a different parameter, table.status, to determine which food buffer to write into. If the table.status does not match the o->ftype, then the wrong food will be written to the customer's food buffer associted with the current table.status. This is a problem, because the Meal food type is much larger than both the Appetizer or Dessert food types.

To exploit, send a Meal when the table.status is expecting a Dessert. This will cause the call to accept_food() to overwrite the Customer.fi ptr and the Customer.next ptr with the Meal.main data, it will also corrupt the heap data with the remainder of Meal.main, as well as Meal.veggies, Meal.side, and Meal.next (which is NULL) data.

Then when the food inspection function is called c->fi(), the fi pointer has been overwritten by client provided data and will cause TYPE 1 POV.

Since, the inspect\_*() functions pass its parameters via registers, the Customer.id for the customer currently being fed resides in EDX.

There are a number of ways to patch this vulnerability. The easiest is to remove the ability for the buf location and bufsz to get out of sync, by removing the call to get\_delivery\_foodtype\_from\_table\_status() at table.c:300. An equally simple solution is to move that function assignment to the top of the give\_food\_to\_customer() function. Either change will result in the bufsz matching the size of buf and thus prevent POV.

### Generic Class of Vulnerability

Heap Buffer Overflow
Type Confusion


### CWE Classification

CWE-122: Heap-Based Buffer Overflow
CWE-131: Incorrect Calculation of Buffer Size
CWE-704: Incorrect Type Conversion or Cast
CWE-787: Out-of-bounds Write
CWE-788: Access of Memory Location After End of Buffer
CWE-805: Buffer Access with Incorrect Length Value

### Challenges

* The biggest challenge this CB was designed to test was how well a CRS can handle a CB Set with many CBs in it. The max number of CBs that are allowed in a CB Set is 10, so this CB has 10 CBs in it.
* Next, this vulnerability exists in 9 of the 10 CBs. So, while each provided POV will only test one of them, they can still be POV'd if that one is patched, but the others 8 are not. Each POV 1-9 is targeted at cb\_2 - cb\_10 respectively.
* Next, this CB Set will challenge a CRS to notice that multiple CBs are the same. This will determine if/how they can transition the patch from one CB to the others. As well as test if the CRS will patch each CB on their own, but in a different way.
* The I/O between the poller/pov and cb\_1 is not too difficult, which should allow for some successful exploration with fuzzers and solvers.
* The improper buffer size length calculation can be fixed in a few ways that are not too difficult.

### Difficulty

* Discovering is easy
* Proving is medium
* Fixing is easy

## Vulnerability 3

In give\_food\_to\_customer() in table.c:300ish cb\_4, there exists the ability for the client input to cause type confusion.

This function uses the ftype paramter provided by the client to determine the size of the food buffer. It then uses a different parameter, table.status, to determine which food buffer to write into. If the table.status does not match the o->ftype, then the wrong food will be written to the customer's food buffer associted with the current table.status. This is a problem, because the Meal food type is much larger than both the Appetizer or Dessert food types.

To exploit, send a Meal when the table.status is expecting a Dessert. This will cause the call to accept_food() to overwrite the Customer.fi ptr and the Customer.next ptr with the Meal.main data, it will also corrupt the heap data with the remainder of Meal.main, as well as Meal.veggies, Meal.side, and Meal.next (which is NULL) data.

Then when the food inspection function is called c->fi(), the fi pointer has been overwritten by client provided data and will cause TYPE 1 POV.

Since, the inspect\_*() functions pass its parameters via registers, the Customer.id for the customer currently being fed resides in EDX.

There are a number of ways to patch this vulnerability. The easiest is to remove the ability for the buf location and bufsz to get out of sync, by removing the call to get\_delivery\_foodtype\_from\_table\_status() at table.c:300. An equally simple solution is to move that function assignment to the top of the give\_food\_to\_customer() function. Either change will result in the bufsz matching the size of buf and thus prevent POV.

### Generic Class of Vulnerability

Heap Buffer Overflow
Type Confusion


### CWE Classification

CWE-122: Heap-Based Buffer Overflow
CWE-131: Incorrect Calculation of Buffer Size
CWE-704: Incorrect Type Conversion or Cast
CWE-787: Out-of-bounds Write
CWE-788: Access of Memory Location After End of Buffer
CWE-805: Buffer Access with Incorrect Length Value

### Challenges

* The biggest challenge this CB was designed to test was how well a CRS can handle a CB Set with many CBs in it. The max number of CBs that are allowed in a CB Set is 10, so this CB has 10 CBs in it.
* Next, this vulnerability exists in 9 of the 10 CBs. So, while each provided POV will only test one of them, they can still be POV'd if that one is patched, but the others 8 are not. Each POV 1-9 is targeted at cb\_2 - cb\_10 respectively.
* Next, this CB Set will challenge a CRS to notice that multiple CBs are the same. This will determine if/how they can transition the patch from one CB to the others. As well as test if the CRS will patch each CB on their own, but in a different way.
* The I/O between the poller/pov and cb\_1 is not too difficult, which should allow for some successful exploration with fuzzers and solvers.
* The improper buffer size length calculation can be fixed in a few ways that are not too difficult.

### Difficulty

* Discovering is easy
* Proving is medium
* Fixing is easy

## Vulnerability 4

In give\_food\_to\_customer() in table.c:300ish cb\_5, there exists the ability for the client input to cause type confusion.

This function uses the ftype paramter provided by the client to determine the size of the food buffer. It then uses a different parameter, table.status, to determine which food buffer to write into. If the table.status does not match the o->ftype, then the wrong food will be written to the customer's food buffer associted with the current table.status. This is a problem, because the Meal food type is much larger than both the Appetizer or Dessert food types.

To exploit, send a Meal when the table.status is expecting a Dessert. This will cause the call to accept_food() to overwrite the Customer.fi ptr and the Customer.next ptr with the Meal.main data, it will also corrupt the heap data with the remainder of Meal.main, as well as Meal.veggies, Meal.side, and Meal.next (which is NULL) data.

Then when the food inspection function is called c->fi(), the fi pointer has been overwritten by client provided data and will cause TYPE 1 POV.

Since, the inspect\_*() functions pass its parameters via registers, the Customer.id for the customer currently being fed resides in EDX.

There are a number of ways to patch this vulnerability. The easiest is to remove the ability for the buf location and bufsz to get out of sync, by removing the call to get\_delivery\_foodtype\_from\_table\_status() at table.c:300. An equally simple solution is to move that function assignment to the top of the give\_food\_to\_customer() function. Either change will result in the bufsz matching the size of buf and thus prevent POV.

### Generic Class of Vulnerability

Heap Buffer Overflow
Type Confusion


### CWE Classification

CWE-122: Heap-Based Buffer Overflow
CWE-131: Incorrect Calculation of Buffer Size
CWE-704: Incorrect Type Conversion or Cast
CWE-787: Out-of-bounds Write
CWE-788: Access of Memory Location After End of Buffer
CWE-805: Buffer Access with Incorrect Length Value

### Challenges

* The biggest challenge this CB was designed to test was how well a CRS can handle a CB Set with many CBs in it. The max number of CBs that are allowed in a CB Set is 10, so this CB has 10 CBs in it.
* Next, this vulnerability exists in 9 of the 10 CBs. So, while each provided POV will only test one of them, they can still be POV'd if that one is patched, but the others 8 are not. Each POV 1-9 is targeted at cb\_2 - cb\_10 respectively.
* Next, this CB Set will challenge a CRS to notice that multiple CBs are the same. This will determine if/how they can transition the patch from one CB to the others. As well as test if the CRS will patch each CB on their own, but in a different way.
* The I/O between the poller/pov and cb\_1 is not too difficult, which should allow for some successful exploration with fuzzers and solvers.
* The improper buffer size length calculation can be fixed in a few ways that are not too difficult.

### Difficulty

* Discovering is easy
* Proving is medium
* Fixing is easy

## Vulnerability 5

In give\_food\_to\_customer() in table.c:300ish cb\_6, there exists the ability for the client input to cause type confusion.

This function uses the ftype paramter provided by the client to determine the size of the food buffer. It then uses a different parameter, table.status, to determine which food buffer to write into. If the table.status does not match the o->ftype, then the wrong food will be written to the customer's food buffer associted with the current table.status. This is a problem, because the Meal food type is much larger than both the Appetizer or Dessert food types.

To exploit, send a Meal when the table.status is expecting a Dessert. This will cause the call to accept_food() to overwrite the Customer.fi ptr and the Customer.next ptr with the Meal.main data, it will also corrupt the heap data with the remainder of Meal.main, as well as Meal.veggies, Meal.side, and Meal.next (which is NULL) data.

Then when the food inspection function is called c->fi(), the fi pointer has been overwritten by client provided data and will cause TYPE 1 POV.

Since, the inspect\_*() functions pass its parameters via registers, the Customer.id for the customer currently being fed resides in EDX.

There are a number of ways to patch this vulnerability. The easiest is to remove the ability for the buf location and bufsz to get out of sync, by removing the call to get\_delivery\_foodtype\_from\_table\_status() at table.c:300. An equally simple solution is to move that function assignment to the top of the give\_food\_to\_customer() function. Either change will result in the bufsz matching the size of buf and thus prevent POV.

### Generic Class of Vulnerability

Heap Buffer Overflow
Type Confusion


### CWE Classification

CWE-122: Heap-Based Buffer Overflow
CWE-131: Incorrect Calculation of Buffer Size
CWE-704: Incorrect Type Conversion or Cast
CWE-787: Out-of-bounds Write
CWE-788: Access of Memory Location After End of Buffer
CWE-805: Buffer Access with Incorrect Length Value

### Challenges

* The biggest challenge this CB was designed to test was how well a CRS can handle a CB Set with many CBs in it. The max number of CBs that are allowed in a CB Set is 10, so this CB has 10 CBs in it.
* Next, this vulnerability exists in 9 of the 10 CBs. So, while each provided POV will only test one of them, they can still be POV'd if that one is patched, but the others 8 are not. Each POV 1-9 is targeted at cb\_2 - cb\_10 respectively.
* Next, this CB Set will challenge a CRS to notice that multiple CBs are the same. This will determine if/how they can transition the patch from one CB to the others. As well as test if the CRS will patch each CB on their own, but in a different way.
* The I/O between the poller/pov and cb\_1 is not too difficult, which should allow for some successful exploration with fuzzers and solvers.
* The improper buffer size length calculation can be fixed in a few ways that are not too difficult.

### Difficulty

* Discovering is easy
* Proving is medium
* Fixing is easy

## Vulnerability 6

In give\_food\_to\_customer() in table.c:300ish cb\_7, there exists the ability for the client input to cause type confusion.

This function uses the ftype paramter provided by the client to determine the size of the food buffer. It then uses a different parameter, table.status, to determine which food buffer to write into. If the table.status does not match the o->ftype, then the wrong food will be written to the customer's food buffer associted with the current table.status. This is a problem, because the Meal food type is much larger than both the Appetizer or Dessert food types.

To exploit, send a Meal when the table.status is expecting a Dessert. This will cause the call to accept_food() to overwrite the Customer.fi ptr and the Customer.next ptr with the Meal.main data, it will also corrupt the heap data with the remainder of Meal.main, as well as Meal.veggies, Meal.side, and Meal.next (which is NULL) data.

Then when the food inspection function is called c->fi(), the fi pointer has been overwritten by client provided data and will cause TYPE 1 POV.

Since, the inspect\_*() functions pass its parameters via registers, the Customer.id for the customer currently being fed resides in EDX.

There are a number of ways to patch this vulnerability. The easiest is to remove the ability for the buf location and bufsz to get out of sync, by removing the call to get\_delivery\_foodtype\_from\_table\_status() at table.c:300. An equally simple solution is to move that function assignment to the top of the give\_food\_to\_customer() function. Either change will result in the bufsz matching the size of buf and thus prevent POV.

### Generic Class of Vulnerability

Heap Buffer Overflow
Type Confusion


### CWE Classification

CWE-122: Heap-Based Buffer Overflow
CWE-131: Incorrect Calculation of Buffer Size
CWE-704: Incorrect Type Conversion or Cast
CWE-787: Out-of-bounds Write
CWE-788: Access of Memory Location After End of Buffer
CWE-805: Buffer Access with Incorrect Length Value

### Challenges

* The biggest challenge this CB was designed to test was how well a CRS can handle a CB Set with many CBs in it. The max number of CBs that are allowed in a CB Set is 10, so this CB has 10 CBs in it.
* Next, this vulnerability exists in 9 of the 10 CBs. So, while each provided POV will only test one of them, they can still be POV'd if that one is patched, but the others 8 are not. Each POV 1-9 is targeted at cb\_2 - cb\_10 respectively.
* Next, this CB Set will challenge a CRS to notice that multiple CBs are the same. This will determine if/how they can transition the patch from one CB to the others. As well as test if the CRS will patch each CB on their own, but in a different way.
* The I/O between the poller/pov and cb\_1 is not too difficult, which should allow for some successful exploration with fuzzers and solvers.
* The improper buffer size length calculation can be fixed in a few ways that are not too difficult.

### Difficulty

* Discovering is easy
* Proving is medium
* Fixing is easy

## Vulnerability 7

In give\_food\_to\_customer() in table.c:300ish cb\_8, there exists the ability for the client input to cause type confusion.

This function uses the ftype paramter provided by the client to determine the size of the food buffer. It then uses a different parameter, table.status, to determine which food buffer to write into. If the table.status does not match the o->ftype, then the wrong food will be written to the customer's food buffer associted with the current table.status. This is a problem, because the Meal food type is much larger than both the Appetizer or Dessert food types.

To exploit, send a Meal when the table.status is expecting a Dessert. This will cause the call to accept_food() to overwrite the Customer.fi ptr and the Customer.next ptr with the Meal.main data, it will also corrupt the heap data with the remainder of Meal.main, as well as Meal.veggies, Meal.side, and Meal.next (which is NULL) data.

Then when the food inspection function is called c->fi(), the fi pointer has been overwritten by client provided data and will cause TYPE 1 POV.

Since, the inspect\_*() functions pass its parameters via registers, the Customer.id for the customer currently being fed resides in EDX.

There are a number of ways to patch this vulnerability. The easiest is to remove the ability for the buf location and bufsz to get out of sync, by removing the call to get\_delivery\_foodtype\_from\_table\_status() at table.c:300. An equally simple solution is to move that function assignment to the top of the give\_food\_to\_customer() function. Either change will result in the bufsz matching the size of buf and thus prevent POV.

### Generic Class of Vulnerability

Heap Buffer Overflow
Type Confusion


### CWE Classification

CWE-122: Heap-Based Buffer Overflow
CWE-131: Incorrect Calculation of Buffer Size
CWE-704: Incorrect Type Conversion or Cast
CWE-787: Out-of-bounds Write
CWE-788: Access of Memory Location After End of Buffer
CWE-805: Buffer Access with Incorrect Length Value

### Challenges

* The biggest challenge this CB was designed to test was how well a CRS can handle a CB Set with many CBs in it. The max number of CBs that are allowed in a CB Set is 10, so this CB has 10 CBs in it.
* Next, this vulnerability exists in 9 of the 10 CBs. So, while each provided POV will only test one of them, they can still be POV'd if that one is patched, but the others 8 are not. Each POV 1-9 is targeted at cb\_2 - cb\_10 respectively.
* Next, this CB Set will challenge a CRS to notice that multiple CBs are the same. This will determine if/how they can transition the patch from one CB to the others. As well as test if the CRS will patch each CB on their own, but in a different way.
* The I/O between the poller/pov and cb\_1 is not too difficult, which should allow for some successful exploration with fuzzers and solvers.
* The improper buffer size length calculation can be fixed in a few ways that are not too difficult.

### Difficulty

* Discovering is easy
* Proving is medium
* Fixing is easy

## Vulnerability 8

In give\_food\_to\_customer() in table.c:300ish cb\_9, there exists the ability for the client input to cause type confusion.

This function uses the ftype paramter provided by the client to determine the size of the food buffer. It then uses a different parameter, table.status, to determine which food buffer to write into. If the table.status does not match the o->ftype, then the wrong food will be written to the customer's food buffer associted with the current table.status. This is a problem, because the Meal food type is much larger than both the Appetizer or Dessert food types.

To exploit, send a Meal when the table.status is expecting a Dessert. This will cause the call to accept_food() to overwrite the Customer.fi ptr and the Customer.next ptr with the Meal.main data, it will also corrupt the heap data with the remainder of Meal.main, as well as Meal.veggies, Meal.side, and Meal.next (which is NULL) data.

Then when the food inspection function is called c->fi(), the fi pointer has been overwritten by client provided data and will cause TYPE 1 POV.

Since, the inspect\_*() functions pass its parameters via registers, the Customer.id for the customer currently being fed resides in EDX.

There are a number of ways to patch this vulnerability. The easiest is to remove the ability for the buf location and bufsz to get out of sync, by removing the call to get\_delivery\_foodtype\_from\_table\_status() at table.c:300. An equally simple solution is to move that function assignment to the top of the give\_food\_to\_customer() function. Either change will result in the bufsz matching the size of buf and thus prevent POV.

### Generic Class of Vulnerability

Heap Buffer Overflow
Type Confusion


### CWE Classification

CWE-122: Heap-Based Buffer Overflow
CWE-131: Incorrect Calculation of Buffer Size
CWE-704: Incorrect Type Conversion or Cast
CWE-787: Out-of-bounds Write
CWE-788: Access of Memory Location After End of Buffer
CWE-805: Buffer Access with Incorrect Length Value

### Challenges

* The biggest challenge this CB was designed to test was how well a CRS can handle a CB Set with many CBs in it. The max number of CBs that are allowed in a CB Set is 10, so this CB has 10 CBs in it.
* Next, this vulnerability exists in 9 of the 10 CBs. So, while each provided POV will only test one of them, they can still be POV'd if that one is patched, but the others 8 are not. Each POV 1-9 is targeted at cb\_2 - cb\_10 respectively.
* Next, this CB Set will challenge a CRS to notice that multiple CBs are the same. This will determine if/how they can transition the patch from one CB to the others. As well as test if the CRS will patch each CB on their own, but in a different way.
* The I/O between the poller/pov and cb\_1 is not too difficult, which should allow for some successful exploration with fuzzers and solvers.
* The improper buffer size length calculation can be fixed in a few ways that are not too difficult.

### Difficulty

* Discovering is easy
* Proving is medium
* Fixing is easy

## Vulnerability 9

In give\_food\_to\_customer() in table.c:300ish cb\_10, there exists the ability for the client input to cause type confusion.

This function uses the ftype paramter provided by the client to determine the size of the food buffer. It then uses a different parameter, table.status, to determine which food buffer to write into. If the table.status does not match the o->ftype, then the wrong food will be written to the customer's food buffer associted with the current table.status. This is a problem, because the Meal food type is much larger than both the Appetizer or Dessert food types.

To exploit, send a Meal when the table.status is expecting a Dessert. This will cause the call to accept_food() to overwrite the Customer.fi ptr and the Customer.next ptr with the Meal.main data, it will also corrupt the heap data with the remainder of Meal.main, as well as Meal.veggies, Meal.side, and Meal.next (which is NULL) data.

Then when the food inspection function is called c->fi(), the fi pointer has been overwritten by client provided data and will cause TYPE 1 POV.

Since, the inspect\_*() functions pass its parameters via registers, the Customer.id for the customer currently being fed resides in EDX.

There are a number of ways to patch this vulnerability. The easiest is to remove the ability for the buf location and bufsz to get out of sync, by removing the call to get\_delivery\_foodtype\_from\_table\_status() at table.c:300. An equally simple solution is to move that function assignment to the top of the give\_food\_to\_customer() function. Either change will result in the bufsz matching the size of buf and thus prevent POV.

### Generic Class of Vulnerability

Heap Buffer Overflow
Type Confusion


### CWE Classification

CWE-122: Heap-Based Buffer Overflow
CWE-131: Incorrect Calculation of Buffer Size
CWE-704: Incorrect Type Conversion or Cast
CWE-787: Out-of-bounds Write
CWE-788: Access of Memory Location After End of Buffer
CWE-805: Buffer Access with Incorrect Length Value

### Challenges

* The biggest challenge this CB was designed to test was how well a CRS can handle a CB Set with many CBs in it. The max number of CBs that are allowed in a CB Set is 10, so this CB has 10 CBs in it.
* Next, this vulnerability exists in 9 of the 10 CBs. So, while each provided POV will only test one of them, they can still be POV'd if that one is patched, but the others 8 are not. Each POV 1-9 is targeted at cb\_2 - cb\_10 respectively.
* Next, this CB Set will challenge a CRS to notice that multiple CBs are the same. This will determine if/how they can transition the patch from one CB to the others. As well as test if the CRS will patch each CB on their own, but in a different way.
* The I/O between the poller/pov and cb\_1 is not too difficult, which should allow for some successful exploration with fuzzers and solvers.
* The improper buffer size length calculation can be fixed in a few ways that are not too difficult.

### Difficulty

* Discovering is easy
* Proving is medium
* Fixing is easy
