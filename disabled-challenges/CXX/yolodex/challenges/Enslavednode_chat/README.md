# KPRCA-00031

### DARPA performer group
Kaprica Security (KPRCA)

## Description:

This service implements a fictitious chat channel on the Enslavednode chat
server. There are two bots in the channel named "case" and "molly". They are
both markov chain bots that chat in the channel when the user enters text.
They only respond a certain percentage of the time and since they are markov
bots their responses are purely based off the input of the user and a small
initial corpus of text that is fed into the system upon initialization. Case
generates a response whenever the user enters text. This response is always
sent to molly who uses it to build her markov chain and it is occasionally sent
back to the user. Molly's generated text is only sent back to the user with
some probability.

### Feature List

The bots implement a set of separate bot functions that can be activated if the
input they are sent triggers them. They are listed below:

  * case:
    * `/hello` - Responds with a kind greeting to the user.
    * `/rev` - Reverses the users input string
    * `/howsmart` - Gives a metric on the bots "intelligence".

  * molly:
    * `/pont` - Pontificates about the topic at hand.

The user can also quit with the `/part` command.

## Vulnerability

The vulnerability for this service is in the `/pont` command for molly. She constructs
a response and initialiez a new string with the response before returning it to
the user. The string constructor however does not check the size of the string
it is copying into itself at initialization. This results in a heap overflow.

### Generic class of vulnerability
Heap-based Buffer Overflow

### CWE classification
CWE-122: Heap-based Buffer Overflow

## Challenges

The vulnerability in this service is simple enough, but is guarded behind
a fairly complex layer of logic. I.e. the markov chain text generation. An
attacker must be able to corrently insert text into the system that will result
in a vulnerability triggering emission for the `/pont` command. This will
require a fairly decent dataflow analysis system.
