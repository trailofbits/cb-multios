# Water_Treatment_Facility_Simulator

## Author Information

"Joe Rogers" <joe@cromulence.com>

### DARPA performer group
Cromulence (CROMU)

## Description

This CB simulates the operation of a waste water treatment facility.

### Feature List

The simulation includes the following keys systems: Headworks, Activated Sludge Process, Filters, Disinfection Chambers, and several Valves controlling flow between these systems.  The CB provides an operator interface to the simulated plant describing the current state of the various plant systems and allows the operator to make adjustments to plant parameters.  After the operator is given an opportunity to adjust the parameters, the CB simulates an hour of operation using the configured parameters.  It then assesses the effluent water quality and keeps track of any levels which don't meet pre-set standards.  After 24 hours of operation, the simulation ends and an overall pass/fail result is given.  

Also, at the end of each simulated hour, new influent values are provided requiring the operator to adjust plant parameters before the next simulation cycle.  These new values might indicate changes in flow, CBOD (carbonaceous biochemical oxygen demand) levels, TSS (Total Suspended Solids), Total Nitrogen, and Total Phosphorous coming into the treatment plant.  

## Vulnerability
Vulnerability #1: 
The CB allows the various plant systems to be renamed by the operator.  The code to rename Valve #4 has unsigned to signed conversion error which allows a buffer overflow.  The system name variable is positioned in the data structure before an array of pointers to valve outputs and before several system parameters such as the flow rate.  Normally this valve's first output would point to the Effluent system.  The output pointer is later used in the SimulateEffluent function to calculate values such as flow rates in that system's structure.  The function uses the flow rate from the valve along with the output pointer to update the effluent data structure's flow rate.

EBP and EIP can be controlled using these steps:
- Run the plant successfully for 24 hours
- Choose to rename valve 4
- Use the buffer overflow to overwrite the valve output pointer setting it to a stack address aligned over the stack of the SimulateEffluent function
- Set the valve 4 flow rate to a value of the CRS' choosing
- End the simulation which will cause one last SimulateEffluent to be called and saved EBP and EIP of that function to be overwritten.

### Generic class of vulnerability
Vulnerability #1:
Unsigned to Signed Conversion Error
Buffer Overflow

### CWE classification
CWE-196: Unsigned to Signed Conversion Error
CWE-131: Incorrect Calculation of Buffer Size

## Challenges
Vulnerability #1: 
A type 1 PoV for this CB is challenging because the CRS must successfully operate the simulated plant for 24 hours.  This requires a thorough understanding of the formulas and floating-point math used to calculate the plant's operation and the proper setting of plant controls each simulated hour so that the resulting effluent meets the pre-set water quality standards.

Subjective Quantification:
Discovering - Medium
Proving - Hard
Fixing - Easy
