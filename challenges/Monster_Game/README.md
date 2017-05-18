# Monster_Game

## Author Information

"John Berry" <hj@cromulence.com>

### DARPA performer group
Cromulence

## Description

This challenge allows a user to travel across a map fighting and capturing monsters.

### Feature List

When a user first connects they are prompted to enter a name. A blank response gives them the default "Player One".

Three monsters are generated with hit points between 4 and 9 and power between 2 and 5. Example output of this step is:

Name: Player One
Level: 1
Monsters:
	Type: Gamma Guardian
	Health: 9
	Power: 6

	Type: Wrathran Palpur
	Health: 12
	Power: 7

	Type: Angry Neutron
	Health: 12
	Power: 3


A map is then generated with height and width between 5 and 30. The player and boss are randomly placed at a starting position. The player is indicated by '@' and the boss is indicated by the 'X'. Following these two placements the map is then filled with obstacles. During the filling process it is always ensured that a path exists between the player and the boss using a breadth first searching algorithm.

Once the map is generated the player is prompted with ': '. Here they are able to enter a movement, either (u)p, (d)own, (l)eft, or (r)ight. If an obstacle is in their way they will receive an error. If they enter a character that is not u, d, l, or r then they will get an error. Otherwise the player will move to the indicated location. Here is an example prompt:

..##.#
.....#
#.....
#.#@.#
#.##..
#.#..#
......
......
.#....
..#.##
.#.##.
......
.#....
..#..#
......
X.....
: 

After each move there is a random chance that the user will encounter a monster. If this occurs the following will be displayed:

You are being attacked!!!
	Type: Rough Wizard
	Level: 1
	Health: 5
	Hit Points: 5
	Power: 7

Monsters:
	1}
	Type: Gamma Guardian
	Level: 1
	Health: 9
	Power: 6

	2}
	Type: Wrathran Palpur
	Level: 1
	Health: 12
	Power: 7

	3}
	Type: Angry Neutron
	Level: 1
	Health: 12
	Power: 3

Selection:

The player will be informed of the attack and the atacking monster's information along with all of the player's monsters' information will be displayed. The player is expected to select a valid entry corresponding to the monster with which they wish to attack. The monster will hit for a value between 0 and their power level.

After the selection hit value and the remaining health of the attacking monster will be displayed. If the monster is not knocked out then it will also attack the defending player's monster. If the defending monster's hitpoints is less than or equal to 0 then it can no longer be used to attack. If all defending monsters are less than or equal to 0 then the player loses the battle.

Selection: 1
You hit for 2. 3 left
Rough Wizard hits Gamma Guardian for 4
Monsters:
	1}
	Type: Gamma Guardian
	Level: 1
	Health: 5
	Power: 6

	2}
	Type: Wrathran Palpur
	Level: 1
	Health: 12
	Power: 7

	3}
	Type: Angry Neutron
	Level: 1
	Health: 12
	Power: 3

Selection:

The player attacks again but this time they successfully knock out the attacking monster.

Selection: 1
You hit for 3. 0 left
You knocked out Rough Wizard
capture monster? (y\n):

The player then has a choice to capture the monster. A maximum of only 5 monster can be held at one time. If the player chooses (y) and there are less than 5 monsters currently, then the next available slot is filled. However if the player already has 5 monsters then they are asked if they want to replace one of their current monsters. If they choose yes then they must enter the selection between 1-5.

After every 15 attacks performed by a monster that monster gains a level. This means that their max hitpoints and power increases by 1.

When the player reaches the boss they will see something like this:

DUN DUN DUUUUUUUUUUUUUUN
You have reached the boss!!!!!

	Type: The Barbarian
	Level: 4
	Health: 11
	Hit Points: 11
	Power: 8

The battle against the boss is the same as that of normal monsters except that the boss has a higher maximum power.
When the bosses health drops below or equal to 0 the player has the option to capture it.

You hit for 4. -3 left
You destroyed the boss!!!!
capture monster? (y\n):

After selecting (y)es the player is asked if they would like to update the bosses name.

update boss name? (y\n):

Here they are able to enter whatever name they wish.

In addition, there is an easter egg allowing a player to up the hitpoints and power of their first monster to 99.

"easta egg"

: e
[ERROR] Invalid direction: 65
: a
[ERROR] Invalid direction: 61
: s
[ERROR] Invalid direction: 73
: t
[ERROR] Invalid direction: 74
: a
[ERROR] Invalid direction: 61
:   <---- This is a space then newline
[ERROR] Invalid direction: 20
: e
[ERROR] Invalid direction: 65
: g
[ERROR] Invalid direction: 67
: g
YOU FOUND THE EGG!!!! Have a prize.
[ERROR] Invalid direction: 67
: 

## Vulnerability

The vulnerability is a simple stack based buffer overflow. The difficult part of the bug is reaching the vulnerable function. After the player defeats the boss they are allowed to enter the boss' new name. This functionality is handled in change_monster_name().

The player is able to enter data and the application will continue reading until a new line (0xa) is encountered. This data is read into a stack based buffer 32 bytes in size. An attacker providing greater than 32 bytes can create a Type 2 POV.


### Generic class of vulnerability
Stack Based Buffer Overflow

### CWE classification

CWE-120: Buffer Copy without Checking Size of Input

## Challenges

Locating the Vulnerability:

Location is difficult due to the CRS having to traverse the map to reach the boss. To do this in a timely fashion requires an algorithm to calculate the path between the two points. It is possible that a CRS could just move randomly and have success on smaller maps but it is unlikely to work on larger maps.

Patching the Vulnerability:

Patching is very straight forward for this bug. A stack canary or decreasing the size of the read would fix the issue.

Proving the Vulnerability:

Once found and assuming the change_monster_name() can be reliably reached then proving the vulnerability is very straight forward since it is a simple stack based buffer overflow.
