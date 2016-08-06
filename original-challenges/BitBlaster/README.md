# BitBlaster

@Author: Lok Yan <Lok.Yan@us.af.mil>
@Group: AFRL

## Description:

This is a simple puzzle game where the user is presented with a rectangular board of size 32x32. At the start of the game, the board is littered with 4*n bits (n <= 64) which are set positions. The goal of the game is to clear the board by moving the bits towards the bottom left of the board. When the lower left 2x2 grid is filled with bits, they will disappear. There are only two kinds of movements that are allowed - rotate right or rotate down.

For example the following puzzle (the ... represents a bunch of 0s)
1100 0000 0000 0000 ...
... 
1100 0000 0000 0000 ...

Has the solution: 0D x 31 and 1D x 31 (in any order).

## Vulnerability Class: 

The vulnerability is a an explicit NULL Pointer Dereference by calling NULL as a function. This vulnerability is triggered once a solution to the puzzle at hand is found. In essence, this CB should be easy to patch, but more difficult to POV. This vulnerability falls under [CWE-824: Access of Uninitialized Pointer](http://cwe.mitre.org/data/definitions/824.html) and [CWE-476: Null Pointer Derefernece](http://cwe.mitre.org/data/definitions/476.html)

## Additional Notes:

This CB is designed to help CRSes determine well they handle bit-wise operations include the bit-based protocol  as the ability to support bit-wise operations (mainly the rotate operations). There is the potential difficulty of the rotate down operation but the clear function boundaries should help with the behavior and logic recovery. The major challenge is in how a CRS might be able to find a "solution" to the puzzle at hand. To minimize this, we ensured that the default starting position is just the bottom two rows having all 1's. This means that only the right shift is needed to generate the POV. A user can change the code in the future accordingly.

