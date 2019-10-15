# Recipe_and_Pantry_Manager

## Author Information

"John Berry" <hj@cromulence.com>

### DARPA performer group
Cromulence

## Description

The user can add and remove recipes as well as pantries containing ingredients.

### Feature List

The main menu presents the user with the option to go into the Recipe, Pantry or Query menu.

The Recipe menu allows a user to add and remove recipes, list all or just a single recipe or print the cost of each recipe.

The Pantry menu allows a user to create and delete pantries, print all or just a single pantry or modify items in the grocery list.

The Query menu allows a user to select a pantry and print all recipes that can be made with items in that list. They can also query for recipes that they can make given an amount of money. Finally, they can print the cheapest and most expensive recipe.

## Vulnerability

When printing an individual recipe the user is prompted to enter the index. This value is not validated and can be negative. Since each pantry structure has a 4 byte cookieand the array of pantries is stored at a lower address than the array of recipes, a user can provide a negative index to begin reading the data from the pantry structures. 

There is some error checking done and the data that is read must be aligned properly so some setup of the pantry array is required to succeed.

### Generic class of vulnerability

The CB fails to correcly validate the array index.

### CWE classification
CWE-129: Improper Validation of Array Index

## Challenges

Discovery:
Locating the vulnerability is not too difficult. If the CRS can detect the bounds of the global recipe array using the usage of the bzero() function then they should be able to detect an out of bounds indexing. 

PoV Generation:
This is going to be relatively difficult because the chances of correctly creating pantries and then correctly indexing the recipe array in a way that passes the error checks is a little complex.

Patching:
Once discovered, patching is a matter of changing the data to unsigned or correctly adding in bounds checks, neither of which are too difficult.
