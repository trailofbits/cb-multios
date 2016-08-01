### DARPA performer group
Kaprica Security (KPRCA)

## Description

This application is a pizza ordering system. It is deisnged to help employees 
at a restaurant track order requests.

### Feature List

The service allows an employee to input an order into the tracking system. To prove that
a user is trusted he or she must first authenticate into the system. Once Authenticated the user may:

1. Input Order
    Allows an employee to input an order, add toppings to a pizza, remove a pizza from an order
2. Update Order
    Remove and add new pizzas to an order
3. View One Orders
4. View All Orders
5. Delete Order
6. Clear All Orders
7. Logout


## Vulnerability

The ordering system assumes all orders will always have at least one pizza. It uses this assumption
to try and properly estimate a wait time. In order.cc:19 the initial max wait time is set to the 
0th index pizza's prep time. 

The bug is due to a missing check when removing a pizza from an in progress order. The 
text that suggests a user can remove a pizza from his or her order is missing.
In the unpatched version the command parser will still allow you to enter the delete option
and create an order with no pizzas. Printing the order causes the null pointer deference.

### Generic class of vulnerability

Null Pointer Dereference

### CWE classification

Null Pointer Dereference (CWE-476)

## Challenges

This challenge will test a system's cabability against a C++ binary. The binary tries to include
as many C++ paradigms as possible. Including namespaces, templates, multiple subclasses, etc.
The bug itself is not specific to C++.
