# Neural_House

### DARPA performer group
Kaprica Security (KPRCA)

## Description

House price suggestion / prediction service using cutting-edge neural network machine learning algorithm.

### Feature List

Given a sufficient training data set, the service can suggest a reasonable price for the house. The user can query with the following features:

  - Number of bedrooms
  - Number of bathrooms
  - Sq. Ft. of the house
  - Number of crimes per town

The size of training data set can be between 500 and 1000, for the time being.

## Vulnerability
### Vuln 1
In main function in service.cc, the service reads in user-controlled amount of data into a statically sized stack buffer when the predicted price of the house is $13,370,000. The attacker can train specifically such that one can get deterministic output.

#### Generic class of vulnerability

Stack buffer overflow

#### CWE classification

CWE-121: Stack-based Buffer Overflow

#### Challenges

 - Lots of floating point math computations

#### Difficulty

 - **Discovery**: easy
 - **Proving**: medium
 - **Patching**: easy
