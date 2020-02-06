# CGC Challenge Binary 00040 - Recipe Database

## Author Information

Steve Wood <swood@cromulence.co>

### DARPA performer group

Cromulence

## Description

The program is an application to collect food recipes and allow for searching for wanted recipes by title and ingredient.  Individual recipes can be tagged for later printing.  In addition, the ingredients from recipes that have been tagged can be combined into a sorted shopping list. 

### Feature List

New recipes can't be added.  Recipes can also be searched for by keyword including the use of wildcards that search the recipe title and ingredient list.  For example, all recipes that use artichoke hearts could be found and tagged.  A list of tagged recipes can be printed to STDOUT to create a menu for a dinner and finally a shopping list of the ingredients used in tagged recipes can be printed.

## Vulnerability

The vulnerability occurs in the way that recipes are captured and later displayed.  If the entry of ingredients is terminated without enterying any ingredient, the recipe is invalid and is deleted.  However, entering a recipe with no step by step instructions is allowed.  When being searched for and displayed for tagging, the program properly checks for the instructions to be a valid list.  However, when subsequently printing a tagged list of recipes, this check is not performed and a zero pointer dereference occurs causing a SEGFAULT.

The second vulnerability is an off by one error due to invalid validation of a length.

The third vulnerabilility exists in the traversing of the book structures without ensureing that the pointer is non-null.

### Generic class of vulnerability

Off by one overwrite
NULL Pointer Dereference.

### CWE classification

CWE-476 -- Null dref
CWE-193 - Off by one error

## Challenges

This vulnerability requires two steps to demonstrate it crashing the program.  First a recipe has to be entered with no step by step instructions, then the recipe has to be searched and tagged.  Finally, it must be displayed as part of the tagged list.





