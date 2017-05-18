# Cereal Mixup - A Cereal Vending Machine Controller

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description:

The hottest new thing in the beverage industry is the vending machine with a touch screen that lets a customer mix and match their favorite beverages into one drink.

What we are bringing to the table is the same hotness, but for breakfast cereal. Cereal Mixup is a breakfast cereal vending machine controller board. This magical board accepts the mix choices from the touch screen and directs the internal machinery to fill the user's bowl with the desired contents.

But, wait, this gets even more exciting!! We also provide an API over wifi, so you can use our unpatentable smartphone app to make your super yummy breakfast mixture selections from the palm of your clammy hand.

The poller/pov/CRS play the role of the touch screen and Wifi API that are sending commands to this controller.

The vulnerabilities in this CB simulate some of the most common object serialization bugs found in Java.

## Feature List:

A bowl of cereal can be made by selecting one or more liquids, cereals, and toppings.

The touch screen has the following options and sub-options that the Cereal Mixup controller can process:

- Add liquids
    - Dairy Milk
    - Dairy Cream
    - Water
    - Soy Milk
    - Almond Milk
- Add cereal
    - Sugar Loops
    - Maize Flakes
    - Marshmallow Figurines
    - Chocolate Rice Pellets
    - Ohhs of Oats
    - Crunchy Puffs
    - Fruitz-n-Nutz
- Add topping
    - Chocolate Drops
    - Blue Berries
    - Berry Medley
    - Sugar Cube
    - Strawberries

The API provided over Wifi accepts the same options and sub-options and the transmission is in a custom serialized format.

## Vulnerability 1

The serialized stream can contain types other than what are needed to make a breakfast. These types represent built-in objects/classes that may exist in imported libraries or default namespace. If one of the other types is de-serialized, its existence and instantiation is outside of the expectations of the Cereal Mixing code and can lead to unexpected operations.

In this case, one of those other objects 'CommandRunner' is an object that will execute the command as given on the command line. It takes a function address and 1 - 3 arguments. It calls the function at the given address and passes the 3 arguments to it.

To POV this CB, the function address is the IP Value and the second argument is the REG value. The first and third arguments are also passed via registers, but the POV itself uses the 2nd argument.

### Generic Class of Vulnerability

Deserialization of Untrusted Data

### CWE Classification

CWE-502: Deserialization of Untrusted Data
CWE-822: Untrusted Pointer Dereference

### Challenges

* This CB was designed to test how well a CRS can determine which input is required for functionality of the CB/polls and which input is superfluous. And further if the CRS is capable of putting in any checks that NOP out or prevent the access to the superfluous functionality.
* There are a significant number of ways to cause this CB to crash/SEGFAULT, so the challenge for a CRS will be to determine which of those crashes are actually useful to prove POV.


### Difficulty

* Discovering is medium
* Proving is medium
* Fixing is hard
