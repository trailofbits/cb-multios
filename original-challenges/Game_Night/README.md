# Game_Night

## Author Information
"Maxwell Koo" <info@narfindustries.com>

### DARPA performer group
Narf Industries (NRFIN)

## Description
Game Night is a collection of games providing fun for the whole family! Play the
hottest new video games from our library, managing all your games in one place.
Stretch your vocabulary with Hugman, learn new tactics with Chess, practice
logic with Sudoku, chug along with Gallon Challenge, feel the thrill of the hunt
with Safari Zone, take a chance with Chance of Survival, and top it off with a
quick game of Lesson in Futility!

### Feature List
This service is a collection of text-based games providing easy access and
replayability from a central interface.

- Supports the following games:
    * Hugman
    * Chess
    * Sudoku
    * Gallon Challenge
    * Safari Zone
    * Chance of Survival
    * Lesson in Futility
- Memory-efficient data structure to minimize system requirements

## Vulnerability 1
The Hugman game uses a predictable algorithm for selecting its words using
entries from the flag page as its source of randomness. Analysis of the words
selected can leak bytes from the flag page to an attacker.

### Generic class of vulnerability
- Information Leak

### CWE classification
- CWE-201: Information Exposure Through Sent Data

### Challenges
In order to successfully prove this vulnerability, a CRS will need to understand
the word selection algorithm and successfully extract the ordered word list for
pattern matching from a PoV. It also will need to understand how to play the
Hugman game in such a way that it can successfully recover the word for each
round.

### Difficulty
- Discovering is easy
- Proving is medium
- Fixing is easy

## Vulnerability 2
When Lesson in Futility is activated at a DEFCON level of 2, it transfers
control to an attacker specified address. There is not normally a method in
which to elevate the game to this level, however a buffer overflow can be
triggered in the Gallon Challenge game after crafted input is provided to Sudoku
to overwrite the current level with a value of 2. This value is not protected by
a cookie like other sections of the game\_state structure.

### Generic class of vulnerability
- Buffer Overflow

### CWE classification
- CWE-119: Improper Restriction of Operations within the Bounds of a Memory Buffer

### Challenges
The shared game\_state structure has many overlapping fields in a union shared
between many games, which can confuse attempts to analyze accesses to it and
recover type information. The resulting aliasing poses a challenge to
discovering the proper way to trigger the buffer overflow and elevate the DEFCON
level to 2.

### Difficulty
- Discovering is medium
- Proving is hard
- Fixing is medium

## Vulnerability 3
When Missingno is encountered in the Safari Zone game it can be captured,
allowing an attacker to transfer control to a user-specified address. Missingno
cannot normally be encountered, however a buffer overflow can be triggered in
the Gallon Challenge game after crafted input is provided to Sudoku to overwrite
the encounter data with Missingno's index. This is made more difficult by a
cookie preventing an attacker from simply overwriting this value, this cookie
value can be leaked through the Chess game and reinserted using the same buffer
overflow in order to trigger the vulnerability.

### Generic class of vulnerability
- Buffer Overflow
- Information Leak

### CWE classification
- CWE-119: Improper Restriction of Operations within the Bounds of a Memory Buffer
- CWE-201: Information Exposure Through Sent Data

### Challenges
The shared game\_state structure has many overlapping fields in a union shared
between many games, which can confuse attempts to analyze accesses to it and
recover type information. The resulting aliasing poses a challenge to
discovering the proper way to trigger the buffer overflow and corrupt the Safari
Zone encounter data. The cookie value check poses a challenge as well, requiring
the overwrite primative to be understood well enough to perform the overwrite of
the encounter data and then restore the original cookie value. This also
requires understanding and identifying the leak of the cookie value in the Chess
game.

### Difficulty
- Discovering is medium
- Proving is hard
- Fixing is medium

## Vulnerability 4
If a user loses in Chance of Survival, the game will transfer control to a user
specified address. A user cannot usually lose Chance of Survival, however by
successfully encountering and capturing a Mewthree in the Safari Zone the state
of the Chance of Survival game can be corrupted to allow this. Mewthree cannot
normally be encountered, however a buffer overflow can be triggered in the
Gallon Challenge game after crafted input is provided to Sudoku to overwrite the
encounter data with Mewthree's index. This is made more difficult by a cookie
preventing an attacker from simply overwriting this value, this cookie value can
be leaked through the Chess game and reinserted using the same buffer overflow
in order to trigger the vulnerability.

### Generic class of vulnerability
- Buffer Overflow
- Information Leak

### CWE classification
- CWE-119: Improper Restriction of Operations within the Bounds of a Memory Buffer
- CWE-201: Information Exposure Through Sent Data
- CWE-665: Improper Initialization

### Challenges
The shared game\_state structure has many overlapping fields in a union shared
between many games, which can confuse attempts to analyze accesses to it and
recover type information. The resulting aliasing poses a challenge to
discovering the proper way to trigger the buffer overflow and corrupt the Safari
Zone encounter data, and the correct way to alter the Safari Zone party data to
corrupt the Chance of Survival chamber data. The cookie value check poses a
challenge as well, requiring the overwrite primative to be understood well
enough to perform the overwrite of the encounter data and then restore the
original cookie value. This also requires understanding and identifying the leak
of the cookie value in the Chess game.

### Difficulty
- Discovering is medium
- Proving is hard
- Fixing is medium


