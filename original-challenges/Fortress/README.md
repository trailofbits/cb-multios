# Fortress

### DARPA performer group
Kaprica Security (KPRCA)

## Description

Fortress is a mini-game where the player hires and sends their explorers to various missions. The player can hire up to 15 explorers at any time. Each explorer can learn up to 2 skills to counter specific types of the missions. There are total of 6 operation types: Ground, Aerial, Naval, Intel, Special, and Rescue. Each mission requires one or more explorers to perform these operations with the corresponding skills. Explorers can switch out currently learned skills with new skills. However, each skill training costs some supplies. The player can earn extra supplies and experience points for the explorers by successfully completing the mission. When the requirement for a mission is satisfied, it will be successfully completed after N days that is specified in the mission description. If any of the requirement is not met, there will be a penalty which yields lower success rate of the mission. Each mission costs some supplies. The goal is to level up explorers as fast as possible. Also, there are some easter-eggs to make it even more fun to play!


### Feature List


```
- Next day: Advance the day (for daily supplies and mission progression)
- Missions
	- Send mission
	- View current missions
- Explorers
    - Hire explorer
    - View current explorers
    - Remove explorer
    - Learn skills
    - Change explorer name (hidden/special)
```

## Vulnerability

### Vuln 1
- In `HandleChangeName` function, the new name for the explorer is not validated and is allowed to be longer than the static-sized buffer for the explorer's name, which is 17 bytes.
- In `CExplorer::ChangeName()` function, the buffer that was passed in is `strcpy`'d straight into the static buffer.
- With an overflow of this buffer, it is possible to corrupt another `CExplorer` object on the heap that is followed by the current one.
- The corruption can lead to the control of virtual function table pointer, which may yield to arbitrary code execution.

#### Generic class of vulnerability

Heap buffer overflow

#### CWE classification

CWE-122: Heap-based Buffer Overflow

#### Challenges

- Various comopnents with its own state.
- C++
- Same behavior in input parsing, but different ways to do so.
- The initial game state is randomized.

#### Difficulty

 - **Discovery**: easy
 - **Proving**: medium
 - **Patching**: easy
