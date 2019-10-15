# ShoutCTF

### DARPA performer group
Kaprica Security (KPRCA)

## Description

ShoutCTF is a CTF platform where a user can register to either start a new team or join an existing team to play CTF. When creating a team, the leader (the first user who creates the team) can specify a shoutout that shows up when the team profile is looked up. Just like any other CTFs, the system goes down at random and new challenges are added/opened randomly. ShoutCTF provides a universal flag submission, where you can just submit the flag for any challenge in main CTF menu instead of submitting for a specific challenge.


### Feature List


```
- Register User
  - Register Team
  - Join Team
- Login User
- Scoreboard
  - View challenges list
  - View challenge detail
  - View ranking
    - “Scroll” through the teams (Max of 5 teams per page)
  - Ticker with most recent solves and team info for the logged-in user.
  - View team profile
  - Submit flags
- Quit
```

## Vulnerability

### Vuln 1

In `handle_register_user` function, there is a trivial stack-based buffer overflow in team creation mode. The `shoutout` section of the team information is read into a buffer (`shout`) with a larger size (`sizeof(buf)`) than the buffer's size.

#### Generic class of vulnerability

Stack-based Buffer Overflow

#### CWE classification

CWE-121: Stack-based Buffer Overflow

#### Challenges

 - Randomness (service outage) needs to be handled to consistently exploit the bug.

#### Difficulty

 - **Discovery**: easy
 - **Proving**: easy
 - **Patching**: easy
