# CROMU-00002: Particle Simulator

## Author Information

"Jason Williams" <jdw@cromulence.com>

### DARPA performer group
Cromulence LLC (CROMU)

## Description

This service implements a simple particle physics simulator. The service utilizes double precision floating point arithmetic and attempts to simulate collisions within a simulation grid. The simulation runs over 10 seconds and calculates the resultant final locations of the particles and attempts to render them to the screen in an ASCII render grid. Output information also consists of the number of collisions that occurred during the simulation and the number of frames that the simulation ran.

### Feature List

A particle physics simulator that utilizes double precision floating point math and runs for 10 seconds with a simulation grid.

## Vulnerability

The render grid is a 2-D array that contains the number of particles centered within that grid location. It is possible with appropriate simulation data to make a scenario whereby the outcome of the simulation causes particles to clip outside of the walls of the simulation. If this event occurs at the last frame of the simulation the rendering will attempt to calculate the location of the particle and it will lie outside of the render grid resulting in a buffer overflow.

In order to trigger this vulnerability the resultant collisions must cause a particle to be translated outside of one of the clipping walls. This doesn't always result in a buffer overflow in the event a particle clips outside of the bounds of the simulation grid due to the manner in which 2-D array offsets are calculated. An assumption made in the clipping code makes this vulnerability possible. It is assumed during the collision detection when iterating through the particles in the simulation that wall collisions can also be calculated in this pass. The manner in which this is done yields an interesting scenario where a collision can occur between 1 of 2 particles after the wall collision detection is performed thereby allowing the particle to translate outside of the collision grid. If this is at a sufficiently large enough 2-D offset this will cause a buffer overflow when the render grid attempts to update the particles in that location.

### Generic class of vulnerability

Buffer Overflow

### CWE classification

CWE-787: Out-of-bounds Write

## Challenges

This CB presents numerous challenges to automated analysis tools. For one this CB heavily utilizes floating point arithmetic and relies upon the accurate calculation of floating point arithmetic for the vulnerability to be reasoned over. Second the challenge binary has a nearly unbounded initial state for the automated analysis frameworks to reason over. Systems that employ unintelligent analysis schemes will have a statistically small chance of discovering the input conditions necessary to trigger the vulnerability.

The expected solver is a symbolic analysis tool with excellent performance characteristics, accurate floating point analysis and the ability to limit depth first searches and breadth first searching due to the likelihood of state explosion. Tools that employ hybrid modes of searching the solution space will most likely yield the highest chances of success.
