# WordCompletion

@Author: Lok Yan <Lok.Yan@us.af.mil>
@Group: AFRL

## Description:

This is a word completion game with 10 initial rounds and a final round. During each round, the user is given an occluded word. The user then needs to provide the full word in order to pass. Once the user completes 10 of these word completion tasks, they will be presented with a final word that must also be solved.
 
## Vulnerability Class: 

The vulnerability is an [CWE-125: Out of Bounds Read](http://cwe.mitre.org/data/definitions/125.html) on an array.

## Additional Notes:

This CB is designed to help CRSes determine how well they handle dynamically generated data. That is the word completion list is created dynamically using a static list of words that are provided as part of the program itself. 
