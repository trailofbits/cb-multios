# Sample Shipgame

@Author: Lok Yan <Lok.Yan@us.af.mil>
@Group: AFRL

## Description:

This is a simple implementation of a familiar 2 player shipgame. The logic is a bit on the quirky side, but it does resemble the game.

It was designed to be easy to solve for automated systems - whether it is indeed easy remains to be seen.

##Vulnerability Class: 

This CB uses a classic stack buffer overflow/overrun. [CWE-121: Stack-based Buffer Overflow](http://cwe.mitre.org/data/definitions/121.html)

##Challenges: 

This CB should not present any major challenges. It was designed to be "easy". The following is a list of basic design principles as well as some commentary on why its chosen.

1. We chose the classic stack overflow since it is one of the most studied vulnerabilities out there. *Thus, we assume that participants know how to handle them* 
2. We tried our best to make the determination of "reachability" simple.
  1. We tried to use very simple operations (addition, subtraction, equality) for branch conditions. This should make any constraint solving easy. The down side is that the resulting control flow graph is quite deep.
  2. We made heavy use of if-elseif-else blocks (we did this in lieu of switch statements in particular). This not only helps with dependencies, but it should also create a neat tree structure.
  3. We also tried to limit the use of loops when we can or if we can't, then make the vulnerability reachable after a couple of unrolls.
3. We sought to make data and control dependencies clear
  1. We used Global Constants in lieu of #define constants. The idea is that, #define will be turned into literals. Take the following test case:

    ```
    #define SHIP2 '2';
    if (x == SHIP2)
    {
      y = SHIP2;
    }
    ```

    In the code above, we should expect the resulting low level code to look like in a made up pseudo language:

    ```
    CMP(x, 0x32)
    JNE(OUT)
    MOV(y, 0x32)
    :OUT
    ```

    If we now contrast this where `#define SHIP2 2` with `const char SHIP2='2'` then the code *SHOULD* look like:

    ```
    CMP(x, SHIP2)
    JNE(OUT)
    MOV(y, SHIP2)
    :OUT
    ```

    The control flow and data flow dependencies in the second case should be much more clearer than the first. E.g. The value of y depends on x in the first case, and both x and SHIP2 on the second. While this might seem like a bad thing (i.e. now we have an extra dependency) it might actually be more helpful in the long run since it should help segment the code (CFG subgraphs). 

  2. Related to 2.2 and 3.1 above, is how we use if-else blocks instead of switch statements since switch statements require literals. It also helps with the CFG as described above.
  3. This game doesn't require a lot of computations. Most variables are "defined" (as in def-use) based on assignments or very simple computations (e.g., base + offset vs)
4. We limited the use of complex data structures. We do define two structures though: Command and PlayerState. We don't think that this will be an issue because
  1. Command has the same layout as a string (it contains 5 chars) and is in the same order as the protocol suggests. 
  2. The PlayerState is a little bit more complex with the 2D array, but it should not be a problem. The operations on the fields should be consistent enough so that the types can be recovered. Even if they can't, it doesn't have any bearing on the vulnerability anyways.
5. We use a very simple 5 byte (char) protocol Command,Row,Column,Direction,Ship Number with a lot of don't-cares. By don't care we mean that N, NH and NHH and NH1 are all equivalent since we look at the first character first and if that is all the command requires, it doesn't care about the other characters.
  1. (N) Reinitializes to a New Game
  2. (H) Prints out a not so helpful message
  3. (M) Prints out the map for the current player
  4. (E) Tries to exit the game
  5. (Prcd#) Tries to Place ship number # starting at Row r and Column c towards the Right or Down directions. For example P0AR2 will place ship 2 (size of 2) at the first two spots on the first row of the map. P0AD5 will place ship 5 at the first 5 spots in the first column.
  6. (S) Starts the current game after all of the players are done placing their ships.
  7. (Trc) Tries to target Row r and Column c. 
6. We also tried to implement one function per command.
7. We tried to simplify the actual x86 instructions used by using very simple C operations (related to 2.1). A recent count shows that only 33 x86 instructions are actually used in the binary.
8. We tried to make "patching" the vulnerability simple (as long as the compiler behaves). The idea is to have the "unpatched" version have one single additional C assignment (and hopefully one single assembly instruction) that leads to the overflow. We chose this so we can have many options for patching: NOPing this extra instruction, changing the constant value of the assignment from 0x7fffffff to the size of the buffer (note that the size of the buffer in this case is static so it can be identified), changing it into jmp over the faulty instruction or what not. A recent test shows only one single instruction difference between the patched and unpatched binaries. The unpatched binary has an extra "mov" instruction that can be NOPed out to obtain a patched binary.

