# CGC Challenge Binary Template

## Author Information

"Nick Davis" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

This is the power testing module that was missing from the Griswold's decorative light display design software.

This module takes the electrical components of the decorative light display design, models the loads, and checks for hazardous situations. All hazardous situations are reported back to the design software, so that it can present indications and warnings to the designer.

If you have seen the movie National Lampoon's Christmas Vacation, you know who the Griswold's are and the epic importance of a power testing application for decorative lighting displays. If you have not seen the movie, you are missing out on a classic!

### Feature List

The module operates on a client/server model. The client is the design software and the server is the power testing module.

The client provides to the server the electrical elements of the design and how they are connected together. The electrical elements are:
- load center
    + 100 amp 8 spaces
    + 100 amp 16 spaces
    + 100 amp 20 spaces
    + 150 amp 20 spaces
    + 150 amp 24 spaces
    + 150 amp 30 spaces
    + 200 amp 20 spaces
    + 200 amp 30 spaces
    + 200 amp 40 spaces
    + 200 amp 42 spaces
    + 400 amp 20 spaces
    + 400 amp 30 spaces
    + 400 amp 40 spaces
    + 400 amp 42 spaces
- circuit breakers (single pole, 1 circuit)
    + 15 amp breaker
    + 20 amp breaker
- electrical outlets (each having 2 receptacles)
    + 15 amp outlet
    + 20 amp outlet
- n-way power splitters (each supporting 15 amps total and 15 amps per receptacle)
    + 3-way splitter
    + 6-way splitter
    + 8-way splitter
- light strings (residential with 22 gauge wire)
    + M5 bulb style, 100 incandescent bulbs, 40.8W
    + C9 bulb style, 25 incandescent bulbs, 120W
    + C7 bulb style, 25 incandescent bulbs, 165.6W
    + C6 bulb style, 150 LED bulbs, 12W


All of the electrical elements are powered by a single 120V residential electric service. All of the circuit breakers are loaded into a single electric load center. Each outlet has 2 receptacles and is associated with a specific circuit breaker. Each n-way power splitter has n receptacles and is associated with a receptacle on a specific electrical outlet or light string. Each light string is associated with a single receptacle on either an electrical outlet or a n-way power splitter.

The server uses the client's input to build a model of the electrical connectivity and loading.

The server is then able to process queries from the client to look for hazardous situations. Those hazard situations are as follows:
- overloaded electrical panel
    + too much total load (>100% amp rating)
- overloaded breaker(s)
    + too many outlets (>8 on 15 amp, >10 on 20 amp)
    + too much load (>80% amp rating)
- overloaded electrical outlet(s)
    + too much total load (>80% amp rating)
    + too much load on one receptacle (>80% amp rating)
- overloaded power splitter(s)
    + too much total load (>80% amp rating)
    + too much load on one receptacle (>80% amp rating)
- overloaded light string(s)
    + too much load (>210W including that string and all downstream)

This tool does not support checking for excess current through the in-home wiring, which is a major fire hazard. It is assumed that the circuit breakers are properly sized to protect the in-home wiring. It also assumes that the only loads on the electrical panel are light strings.

Electrical rules of thumb:
* Breaker should trip on sustained draw of >80% amp rating
* Max 8 outlets per 15 amp breaker
* Max 10 outlets per 20 amp breaker
* Avg 1.5 amp load per outlet used to define max outlets per breaker.
* Max 210W on 22 gauge wire (residential light strings)
* Max 420W on 20 gauge wire (commercial light strings)

Power equation:
* Amps = Watts / Volts 


## Vulnerability

First vuln:

assemble.c:get_breaker_by_id around line 390, doesn't check the upper bound on breaker_id, which is used as an index into the breakers array. breaker_id is unsigned, so negative isn't a concern, but bounding on the high end is. There are multiple ways to approach this vuln and not all will cause a POV.
- add_outlet_to_breaker() with breaker_id out of range: If the breaker id is associated with an empty breaker space, it will return an error unrelated to the invalid breaker id (outlet amps exceed breaker amps). However, if the breaker_id is greater than the set of valid spaces, it returns error with breaker id up to 340; segfaults with breaker id >= 341. 

assemble.c:add_outlet_to_breaker() calls get_breaker_by_id which returns a pointer. As long as the load center has been created and at least one breaker has been installed, get_breaker_by_id will return a pointer to an index in the breakers array. For any breaker_id greater than 340, the pointer is beyond the end of the allocated page. So, at assemble.c:975 the contents of the breaker are de-referenced causing a segfault.

- is_breaker_overloaded() with breaker_id out of range: If the breaker id is greater than the set of installed breaker ids, a de-reference of the breaker's outlets list count will cause segfault.

examine.c:is_breaker_overloaded eventually calls examine.c:is_too_many_outlets_on_breaker, which calls assemble.c:get_count_outlets_on_breaker, which calls get_breaker_by_id and then immediately de-references the count of the outlets list of the breaker. 
The test for breaker_id_is_installed() at the start of get_count_outlets_on_breaker() relies on a correct result from get_breaker_by_id, so it does not protect against breaker_id out of range.
Any breaker id > the set of installed breaker id's will segfault in assemble.c:get_count_outlets_on_breaker() when the breaker's outlets count is accessed on line 525.

There are other ways that the lack of an upper bounds check on breaker_id is a problem, but those are not reachable because is_too_many_outlets_on_breaker() is called before is_too_much_amp_load_on_breaker(), which will segfault and end execution. Those other vulns are also related to de-referencing the contents of a breaker pointer for a breaker id that is beyond the range of installed breaker ids.


Second vuln:

This vulnerability is a giant glowing flashing strobing light string decorating a freshly allocated page that is trivial to trigger through many paths. BOOM!

assemble.c:search_splitter_for_receptacle_id around line 170, has <= in the loop test instead of <. So, it will go one receptacle beyond the end of the splitter's receptacles array. The idx starts at 0, so negative isn't a concern, but bounding the high end is.

Anytime that the receptacles of a splitter are searched and one of the valid receptacles on that splitter do not match the search, the search will go one beyond the end of the receptacle array and lead to a segfault. There are several ways to make this happen:

- Install 1 splitter into the model onto one of the first receptacles (first outlet would work). Attempt to install any other component onto a receptacle beyond that first outlet that is also not on the splitter. (i.e. 1 outlet with splitter on 1st receptacle. attempt to install light string on second receptacle of outlet.)

There is a bit of trickery here. Freshly allocated memory is zero'd out. And, the enum for load types uses 0 as the LOAD TYPE for a SPLITTER:

typedef enum {
    SPLITTER = 0,
    LIGHT_STRING = 1,
    NO_LOAD = 2,
} LOAD_TYPE_T;

In assemble.c:search_receptacle_for_receptacle_id(), it tests for a load type to determine which search function to call to continue the recursion. This means that examining a non-valid receptacle that exists in zero'd memory will result in processing that receptacle as if it has a SPLITTER attached to it. Then, inside the call to search_splitter_for_receptacle_id, the for loop test needs to de-reference the splitter to get the receptacle_count, which is a null pointer dereference, thus segfault at assemble.c:170.


- Install 1 splitter into the model and search for an invalid receptacle id. (i.e. 1 outlet with splitter connected to one of its receptacles, perform a command using an invalid receptacle id -- any of the add_component() operations will work.)

The cause of this vuln is the same as the previous vuln, but it is reached for a different reason. When a new component is added, a search is performed to find the receptacle for the component to connect to. In this case, the receptacle does not exist, so again, the splitter's incorrect bounds checking causes the access to an invalid receptacle to lease to a null pointer believed to be a splitter. And de-referencing that splitter causes segfault at assemble.c:170.



### Generic class of vulnerability

Improper Input Validation
Improper Validation of Array Index
Off-by-one Error
NULL Pointer Dereference

### CWE classification

Improper Input Validation
CWE-20

Improper Validation of Array Index
CWE-129

Off-by-one Error
CWE-193

NULL Pointer Dereference
CWE-476

## Challenges

* From the fuzzing perspective, once they learn to replay the nonce, they will likely crash the service quite often. There are so many ways to crash it, that a fuzzer should do it regularly. The challenge will be patching the vulns in an optimal location. There are 2 primary vulns, but they are rechable through multiple paths and the POV doesn't necesarily occur where the code errors are located. Although, it is usually close.
* This is a larger service, in relation to quantity of code. So, static analysis methods will have more code to distract them. And code path analysis methods will have to store more data points which cause solvers to slow down. They need to learn what to ignore to solve efficiently.
