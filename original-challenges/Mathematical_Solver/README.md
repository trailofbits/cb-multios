# CROMU_00017 - Mathematical Solver

## Author Information
"James Nuttall" <james@cromulence.co>

### DARPA performer group
Cromulence

## Description
This service is a basic mathematical expression solver. It generates expressions for the CRS to solve, evaluates CRS generated expressions, and presents basic shapes and asks the CRS to provide parameters.  

### Feature List
Upon connection, the CRS is asked to provide a buffer of data to seed the pseudo-random number generator. This allows the POV to create a deterministic program flow.

After the seed is set, the CRS can select from several different solver options. The service keeps statistics on how many problems are answered correctly by the CRS.  

	1. Solve Equation
	2. Create Equation
	3. Solve Area
	4. Solve Perimeter
	5. Solve Volume
	6. View Statistics
	7. Exit


Solve Equation will generate a random equation for the CRS to solve. 
For example:
	(198-(83+(165*(6+(120-92)-169)/119)*171)+160)

The solver supports the following operators:
	()	Parenthesis
	+ 	Addition
	- 	Subtraction
	/	Division
	*	Multiplication

Create Equation will generate a random rule set for the CRS to follow in generating their own equation. 
For example:
	Enter an equation that has 4 sets of parenthesis
	It must evaluate to 25449 and contain the + operator
	and must use the numbers: 25 236 155 and 123

Solve Area presents a word problem for calculating the area of a shape. 
For example:
	find area of circle with radius 8294

Solve Perimeter presents a word problem for calculating the perimeter of a shape.
For example:
	find perimeter of object with 726 sides of length 16852

Solve Volume presents a word problem involving the volume of a shape. 
For example:
	find height of rectangular prism with a volume of 244910160, and side of 330

View Statistics will show the statistics gathered so far about the number and type of problems solved correctly and incorrectly.

## Vulnerability
There are three vulnerabilities in this challenge.
The vulnerabile functions are located in the print_statistics() function, which is accessed simply by selecting option 6. View Statistics from the main menu.

The first vulnerability is located in service.c:81 and is only accessible after solving 10 of the 2. Create Equation menu option. After solving exactly 10 of these equations, and selecting 6. View Statistics, the CRS is presented with an option to enter a buffer, which can overflow the allocated space. This will cause a buffer overflow.

The second vulnerability is located in service.c:94 and is only accessible after solving 10 of the 1. Solve Equation menu option. After solving exactly 10 of these equations, and selecting 6. View Statistics, the CRS is presented with an option to enter a buffer, which can overflow the allocated space. This will cause a buffer overflow.

The third vulnerability (with the lowest difficulty) is located in service.c:107 and is only accessible after solving 10 of the 3. Solve Area menu option. After solving exactly 10 of these equations, and selecting 6. View Statistics, the CRS is presented with an option to enter a buffer, which can overflow the allocated space. This will cause a buffer overflow.
 

### Generic class of vulnerability 
Stack-based overflow from CRS input. The CRS is able to directly enter a buffer that is stored in a fixed buffer on the stack.

### CWE classification 
CWE-121 Stack-based Buffer Overflow

## Challenges 
The three vulnerabilities presented in this challenge require the CRS to successfully parse and respond with intelligent input ten times per vulnerability. Each vulnerability requires a differing amount of parsing, input generation, and computation. The intent of this format is to reduce the efficacy of random input and exhaustive solvers and to force the CRS to implement a sufficently deep graph for each vulnerability.
