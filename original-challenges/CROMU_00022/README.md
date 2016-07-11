# CROMU-00022: Dive Logger

## Author Information

“James Connor” <jymbo@cromulence.co>

### DARPA performer group
Cromulence (CROMU)

## Description
This service records dive events and accepts a list of data points for a given dive event.

### Feature List
It validates date and time values, performs epoch to ascii time and date conversion,
and calculates metrics for a given dive as well as all dives.   


## Vulnerability
1.
More than MAXDIVES can be entered via the DownloadDives function.
This failure to limit the dive count enables the vulnerability, which is and an out-of-bounds write in SelectDive.
If the dive list contains greater then MAXDIVES, calling SelectDive will smash count. 
This invalidates the bounds check on which dive is selected, allowing an arbitrary read (using print dive) or write (using edit dive) 
This could be mitigated by preventing downloaddives from exceeding MAXDIVES, by properly bounds checking selectDive or by increasing the
size of the buffer to accomodate 1 additional dive.
2.
There is a vulnerability in the sanity check on time values.  String times are converted to signed int, which are only checked for upperbound
(assumed unsigned).  This vulnerability can be exercised by entering in negative values which exceed the bounds of the string buffer used to 
store the sanitized time value. This could be mitigated using a bounded snprintf, a sufficiently large tempString buffer, or a proper lower bounds check.

### Generic class of vulnerability
1.
Improper restriction of operations within the bounds of a memory buffer
Out-of-bounds write
2.
Numeric range comparison without minimum check
out-of-bounds write
### CWE classification
CWE-787 
CWE-839
## Challenges
