# CGC Challenge Binary Template

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

H20 Flow Inc brings you the hottest technology in programmable logic controllers (PLCs) used in the water distribution industry. We know how important it is for your water distrubition PLCs to do exactly what you tell them to do and nothing more. H2FLOW is our latest generation water flow valve controller.

### Feature List

The H2FLOW CB is a simple flow controller that manages the valves for the fill lines of several water tanks, based on commands provided by the intelligent PLC (the remote user).

Each water tank has a defined capacity. Each tank also has a minimum fill level. If the fill level drops below the minimum fill level, an emergency circuit will activate the backup fill pump until the level returns to the minimum fill level. If the fill level drops below 5 units of volume, a critical fill level alarm is raised.

Each water tank has a random rate that water is flowing out of it (drain rate). This simulates periodic water usage by an end user or device.

There are a fixed number of tanks, their ID numbers are sequential starting from 0, the capacities are defined by the TANK\_CAP value, and initial fill level is defined by the INIT\_LEVEL value.

To simulate time and water flowing in and out of tanks, H2FLOW uses a sleep timer. During the sleep timer, the service is simulating execution of all received commands and the filling/emptying of tanks. 

Between sleep timers, the service will iterate through the tanks. For each tank, it will send the remote user the tank status and then accept a command to apply to the valves for that tank.

During each iteration, the drain and fill functions will remove water from tanks based on a random outflow rate and add water to tanks based on valve position and a fixed inflow rate. Finally, each tank will be tested for under fill.

H2FLOW has a very simple protocol. It accepts the following commands:
- OPEN\_VALVE           : open fill valve
- CLOSE\_VALVE          : close fill valve
- NO\_CHANGE            : no valve changes
- SET\_IN\_SERVICE      : for a tank that is OUT\_OF\_SERVICE, set the fill rate and allow tank to supply water to users
- SET\_OUT\_OF\_SERVICE : close input valve, set fill\_rate and drain\_rate to 0
- SET\_END\_OF\_LIFE    : same as SET\_OUT\_OF\_SERVICE, but is permanant

## Vulnerability

Two things need to happen to trigger the POV.

First, a tank needs to be filled beyond capacity. Due to the tank level being an unsigned char, when it reach 255, the next unit of H2O added will cause the value to overflow to 0. The function tank.c:add_water() does not check the bounds on t->level to prevent overflow.

Second, after both the combined fill and drain operation, the level of the tank must be in the range [0-5]. This will ensure the test for critically low level at operation.c:88 returns TRUE. Note, the update\_water\_levels function (drain and fill operations) is run before the low level tests are run. Thus, it is required for the drain + fill to cause a net int overflow. Also, it is possible for the int overflow to overflow to a level greater than 5, resulting in a value that is not in the range [0-5], and thus will not trigger the critical low level alert.

When the syslog function is called in operation.c:93, the tank number variable access has a coding mistake where the array index is the TANK\_QTY, instead of idx, which causes an out of bounds access and a null pointer dereference. This will trigger SIGSEGV.

### Generic class of vulnerability

Null pointer dereference

Improper checking of loop invariant

Improper array bounds checking

Integer Overflow

Access memory beyond buffer

### CWE classification

Improper Input Validation
CWE-20

Wrap-around Error
CWE-128

Improper Validation of Array Index
CWE-129

Integer Overflow or Wraparound
CWE-190

Access of Memory Location After End of Buffer
CWE-788

Buffer Access with Incorrect Length Value
CWE-805

Access of Uninitialized Pointer
CWE-824

## Challenges
* The protocol is pretty simple, but the first hurdle is to know that the tanks all start in the OUT\_OF\_SERVICE status. So, continued communication with the CB requires the first commands to be SET\_IN\_SERVICE to place tanks in service. After that, some of the other commands will work. A dumb random fuzzer will have problems with this because the order of commands used on a given tank matters.

* To make the POV harder to exploit, the sleep() function is run once per iteration through the tanks. This makes the POV harder to exploit, because sending random commands will eventually trigger the poller timeout before it will have enough time to overflow the tank level and trigger the POV. The sleep value was chosen specifically to make so it is only possible to overflow the tank level if sending the first command as SET\_IN\_SERVICE followed by OPEN\_VALVE for every subsequent iteration. Other sequences have a high probability of ending due to timeout before they can fill the tank. To get N iterations in 15 seconds, want a sleep of 15/N. In testing we found the following results:
** with fill_rate 10, it takes 39 iterations -> sleep 15/39 = .385s
** with fill_rate 11, it takes 33 iterations -> sleep 15/33 = .454s
** will fill_rate 12, it takes 26 iterations -> sleep 15/26 = .577s
** with fill_rate 15, it takes 17 iterations -> sleep 15/17 = .882s

* Additionally, to make the POV harder to reach by fuzzing, we added commands that place the tank either out-of-service or in an end-of-life state. When the tank is in the end-of-life state it can no longer be brought back into service. When the tank is in the out-of-service state, it requires the SET\_IN\_SERVICE command to bring it back into service.

* One more thing that makes this more challenging is the lack of for-release pollers. This series of challenges should help to show distinctions between how CRS's use fuzzing.

