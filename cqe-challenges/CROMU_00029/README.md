# CROMU-00029: Material Temperature Simulation

## Author Information

“Joe Rogers” <joe@cromulence.co>

### DARPA performer group
Cromulence (CROMU)

## Description

This challenge binary implements a material temperature simulation.  It calculates temperature changes in a given material over time.  

### Feature List

The CB supports three pre-defined materials (air, aluminum, and copper) as well as a custom-defined material which requires the user to provide thermal conductivities and heat capacities of the target material over a range of temperatures.  

Once the size of the material is defined, the user is given the opportunity to define the temperature of each cubic meter of material, or to make the material isothermic.  If desired, the user may also define constant heat sources in each cubic meter of the material.  If defined, those cells remain at the constant temperature specified by the user while other surrounding cells are affected according to the characteristics of the material.

Once the simulation starts, the program outputs the temperatures for the material at each time step.  The time step is automatically calculated to make sure the simulation remains stable given the input parameters.  

The program assumes that the boundary of the material is perfectly insulated.  No heat is lost or gained at the material boundary.

## Vulnerability
This CB contains multiple vulnerabilities.

- The CB allocates a 3 dimensional array to store temperature and heat source values after the program is told the size of the material under study.  The calculation is made using this formula: X * Y * Z * sizeof(double).  However, the result of this calculation is stored in a 32-bit unsigned integer which can be easily overflowed resulting in an allocation smaller than the necessary size.  The CB will then attempt to read in the full array resulting in a heap-based buffer overflow.

- Several pre-defined material types are built into the CB along with the option to define custom thermal conductivities and heat capacities of the material under study.  Thermal conductivities should always be positive values.  Otherwise, heat flows towards the larger heat source defying the laws of physics.  But, the CB does not carefully check these thermal conductivity values, so the user is allowed to enter a negative value.  Under normal circumstances, a given cell of material can not rise in temperature above 373 degrees celsius.  The thermal conductivities and heat capacities are stored in eight element arrays indexed based on the current temperature of the cell being referenced.  With a negative thermal conductivity, it is possible to have a temperature higher than 373 degrees which will result in an overrun of that 8-element array causing at best invalid conductivity values to be used and at worst a segmentation violation. 

### Generic class of vulnerability

Vulnerability #1 - Integer overflow leading to an incorrect calculation of buffer size
Vulnerability #2 - Improperly controlled array index

### CWE classification

Vulnerability #1 - CWE-190: Integer Overflow or Wraparound and CWE-131: Incorrect Calculation of Buffer Size
Vulnerability #2 - CWE-129: Improper Validation of Array Index

## Challenges

For the first vulnerability, the CRS must identify that the allocation size can be overflowed and then identify a material dimension which will overflow it but still remain less than the maximum allocation size for the overflowed value. 

For the second vulnerability, the CRS must define negative thermal conductivities for the material and provide a temperature gradient in the material for the bug to be realized.  And, it takes more than just a small negative thermal conductivity to actually crash the program.
