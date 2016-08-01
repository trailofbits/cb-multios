# CGC Planet Markup Language Parser

## Author Information

"John Berry" <hj@cromulence.co>

### DARPA performer group
Cromulence

## Description

A user is able to submit a Planet Markup Language (PML). This will be parsed and presented to the user via menu driven options that allow the elements to be modified.

This CB was designed to push the limits of the CRS' capability to handle the state space explosion problem. While this is not as complex as someting such as a browser or media player, it is large enough to serve as a milestone for CRS'. While the state space is large, the two vulnerabilities are straight forward. 

### Feature List

PML Format:

Generic format:

Each element opens with {ElementId} and closes with {#ElementId}.
No element will have itself as a sub element.

Top level Planet element:
        {Planet}        -- This is the top level id indicating a new planet descriptor
                {Name}  AlphaNumeric  {#Name}           -- Indicate the name of the planet
                {Period} Float {#Period}                -- Orbital period in days
                {OrbitSpeed} Float {#OrbitSpeed}        -- Average orbital speed in km/s
                {Aphelion} Float {#Aphelion}            -- Aphelion in km
                {Perihelion} Float {#Perihelion}        -- Perihelion in km
                {Radius} Float {#Radius}                -- Mean radius in km
                {ERadius} Float {#ERadius}              -- Equatorial radius in km
                {Mass} Float {#Mass}                    -- Mass in kg
                {Gravity} Float {#Gravity}              -- Surface gravity in m/s
                {Population} Integer {#Population}      -- Global population as a positive integer
                {Country} Country Format {#Country}     -- Country sub information. For full description see the
                                                                Country subelement formatting. Multiple country
								Subelements are allowed
        {#Planet}

Country Element:
        {Country}
                {Name} AlphaNumeric {#Name}             -- Name of the country
                {Capitol} Alphabetic {#Captiol}         -- Capitol City
                {Population} Integer {#Population}      -- Country population as an integer
                {Language} Alphabetic {#Language}       -- Language spoken within the country. Multiple
								languages can be specified.
                {Border} Lat Long start/end {#Border}   -- This indicates the start/end via latitude/longitude
                                                                pair of coordinates. It is necessary to use multiple
                                                                Border elements to construct a complete border. [*]
                                                                Ex. {Border} 45.012 34.123 080.123 20.000 {#Border}
                {Territory} Territory Format {#Territory} -- Used to define territories within a country
        {#Country}

Territory Element:
        {Territory}
                {Name} AlphaNumeric {#Name}
                {Population} Integer {#Population}
                {Established} Integer {#Established}    -- Year the county was established. Can be negavive
                {Founder} AlphaNum+Spaces {#Founder}    -- Founder of the territory
                {Border} Lat Long start/end {#Border}
                {County} County Format {#County}        -- County within a territory
        {#Territory}

County Element:
        {County}
                {Name} AlphaNumeric {#Name}
                {Population} Integer{#Population}
                {Border} Lat Long start/end {#Border}
                {Seat} Alpha {#Seat}	                -- County seat
                {Area} Float {#Area}                    -- Total area in square kilometers
                {Density} Float {#Density}              -- Population density in people per km^2
                {City} City Format {#City}              -- City within a county
        {#County}

City Element:
        {City}
                {Name} Alphanumeric {#Name}
                {Mayor} AlphaNum+Spaces {#Mayor}	-- Mayor of the city
                {Url} City Website {#Url}		-- City website
                {Population} Integer {#Population}
                {Border} Lat Long start/end {#Border}
        {#City}

## Vulnerability

There are seven vulnerabilities in this CB.

The first vulnerability is relatively simple and is found high in the state space.
The size of the capitol element of a Country structure is 20 bytes.
However, in the countryMenu() function it is possible to overflow this buffer with
	40 total bytes. This corrupts other fields of the structure. One method of
	causing a crash after the overflow is by selecing "1" to display the country
	information.

The second vulnerability is also very straight forward but it is much deeper in the PML
parsing code. The City structure is able to store the name of the Mayor in a 20 byte
buffer but the function strcpy() is used without bounds checking to copy the value
from the PML element into the field. This results in a basic heap based buffer
overflow.

The third vulnerability exists in the float_to_str() function where a large floating point value will result in a stack based buffer overflow.

The fourth vulnerability is a NULL dereference when parsing a malformed Border field in the PML.

The fifth vulnerability is a NULL dereference when parsing a malformed Planet mass field in the PML.

The sixth vulnerability is a NULL dereference when parsing a malformed Planet period field in the PML.

The seventh vulnerability is a NULL dereference when parsing a malformed name field in the PML.

### Generic class of vulnerability
The first two vulnerabilities are heap-based buffer overflows
The third is a heap based buffer overflow
The Fourth through seventh are null pointer dereferences.

### CWE classification
CWE-120 Buffer copy without checking size of input
CWE-122 Heap-based buffer overflow
CWE-476 NULL Pointer Dereference

## Challenges

The primary difficulty with this challenge is handling the large number of possible combinations of element data. While the potential state space for this CB is no where near that of a standard browser, it will be useful in separating those who can more effectively manages a larger space.
