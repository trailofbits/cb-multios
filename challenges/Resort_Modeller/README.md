# Resort Modeller

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description:

Ski resorts now have gates equipped with RFID sensors at every lift entrance that scan riders to verify their lift pass before the rider can board the lift. The side benefit of this technology is that resorts can accurately track rider numbers on each lift to glean important statistics.

Our exciting new software, Resort Modeller, works on the back-end to allow Resort staff to model different lift usage scenarios based on varying numbers of riders. This will help Resort owners make important planning and staffing decisions.

## Feature List:

The Resort Model is comprised of lifts, trails, and riders. Deciders are used as nodes to connect lifts and trails. Riders can be skiers or snowboarders and they are pre-defined to have a certain amount of energy, which simulates how many trails they will ride before quitting for the day. Lifts have a chair capacity of either 2 or 4 riders per chair and have a static number of chairs. Trails have a difficulty rating from 1 (Easiest) to 5 (Hardest), this will subtract 1-5 units from the riders energy when the rider completes the trail. Trails also have a length.

- Load Resort Digraph: A directed graph of lifts and trails is used to define the resort layout. If one already exists, it is replaced.

- Load Rider Group: A group of riders is loaded into the model.

- Load Rider Single: A single rider is loaded into the model.

- Unload Riders: All riders are unloaded from the model (deleted). This will also reset the simulation.

- Start Simulation: Start the simulation and run it for the specified number of steps. All riders will start via the queue of the first lift.

- Reset Simulation: Reset all stats. Move all Riders to the Resort's list of available riders.

- Lift Stats: Request the counts for how many total riders have boarded each lift.

- Trail Stats: Request the counts for how many total riders have completed each trail.

- Rider Stats: Request the counts for the number of trails each rider has completed and their energy level.


## Vulnerability 1

The code that performs a health check on the riders (rider.c:36) simulates code that was not finished during development or modification. If we make the assumption that the original code just checked every user and the new code was designed/updated to only check riders that are out of energy, we can see how this could happen. On line 43, there is an accidental incrementing of the results pointer. And on line 45 the developer forgot to delete the original line of code that checked every rider. The combination of those 2 lines results in overwritting the riders's health\_check function pointer with the health check result value. This value is user controlled along with the rider's ID, so the next time this rider enters the simulation (after reset\_simulation and then start\_simulation), and they run out of energy, the health\_check function will be an invalid pointer causing Type 1 POV.

### Generic Class of Vulnerability

Untrusted Pointer Dereference
Incorrect Pointer Scaling

### CWE Classification

CWE-468: Incorrect Pointer Scaling
CWE-822: Untrusted Pointer Dereference

### Challenges

* The biggest challenge in this CB will be discovering and proving the POV.
* The CRS has to determine that the pre-requisites to triggering the POV are loading a digraph, loading riders, running a long enough simulation to cause at least one rider to run out of energy, resetting the simulation, and running another simulation long enough to cause the same rider(s) to run out of energy.
* The input for riders and for the resort digraph is very structured, so fuzzing will only be useful if it is intelligent in some way.
* There is a lot of data within the riders, lifts, trails, and deciders that is user-provided, so that will be distracting for taint tracking tools.
* The calloc calls in resort.c around lines 448-455 do not validate the sizes for the allocations, so are wide open to int overflow issues. This will be a distraction to cause crashing, and may give the CRS opportunities for new POVs.

### Difficulty

* Discovering is medium
* Proving is medium
* Fixing is easy
