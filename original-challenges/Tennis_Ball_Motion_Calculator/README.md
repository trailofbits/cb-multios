# Tennis Ball Motion Calculator

@Author: Lok Yan <Lok.Yan@us.af.mil>
@Group: AFRL

## Description:

This is a very simple notional service where users can query the server to calculate and return the x and y coordinates (position in meters) of a tennis ball launged from the origin (0,0) given the initial x and y velocity components (in meters per second). Additionally, the user can request the calculations to start from a specific point in time instead of time zero. Time is incremented in 1/10 intervals. In short, if you plotted the (x,y) coordinates output from this service starting from time 0, then you should see a nice parabola. 

## Feature List:

The actual service itself is not as interesting as the error that it was modeled against. "On February 25, 1991, during the Gulf War, an American Patriot Missle battery in Dharan, Saudi Arabia, failed to track and intercept an incoming Iraqi Scub missile." (["The Patriot Missle Failure"](https://www.ima.umn.edu/~arnold/disasters/patriot.html")). As it turns out, the reason for the failure is due to a rounding error in the floating point calculations that accumulated enough overtime that resulted in the system making an incorrect prediction of where the missle will or should be (the "range gate"). More details can be found in the GAO Report from [Federation of American Scientists](http://www.fas.org/spp/starwars/gao/im92026.htm) in html or from the [Government Accountability Office](http://www.gao.gov/products/IMTEC-92-26) in pdf. 

In that particular case, an integer counter was used to keep track of the number of 10th of seconds that has elapsed since the system started and during the calculations, the current time was calculated as the counter * .1 which will give you the floating point representation of the current time. Since .1 does not have an exact representation in the [IEEE754 Standard for Floating-Point Arithmetic](http://ieeexplore.ieee.org/xpl/mostRecentIssue.jsp?punumber=4610933) (.1 is actually represented as 0.100000001490116119384765625 in the single precision floating point format (i.e. the C type of float)), if the number multiplied by .1 is large enough, the result will not be what the user expects. This particular CB has the same exact problem when it comes to the trajectory of a tennis ball - the x,y coordinates of the tennis ball will eventually be wrong if the time counter is large enough. 

The actual vulnerability in the CB surfaces from a slightly different rounding error though. It is mainly due to the fact that some integers can't be represented exactly in floating point either. So, not only fractions have a problem, but whole numbers can also be problematic.

## Vulnerabilities & Challenges:

The main weaknesses are: [CWE-787: Out-of-bounds write](http://cwe.mitre.org/data/definitions/787.html), [CWE-682: Incorrect Calculation](http://cwe.mitre.org/data/definitions/682.html), [CWE-681: Incorrect Conversion between Numeric Types](http://cwe.mitre.org/data/definitions/681.html). While the data generated will be incorrect (like in the Patriot Missle system), the main weakness in the CB is due to the fact that we are converting an int (32-bits) into a float (also 32-bits). Since single precision floating point only has 24 bits avialable for the mantissa, any number greater than 2^32 will be rounded off and approximated - it won't be the exact value. The following explains how everything works out. 

The trigger is due to the usage of a floating point number to index into an array which, under most circumstances might work out fine, but in this particular case the floating point number is converted from a larger int and then multiplied by .1.  
Delving into the code itself, the basic vulnerability is due to the following array access

	aData[base + j].x = v0_x * tempTime;

In this case, aData is defined as an array which fits exactly into a single page of memory. Since pages are 4096 bytes and sizeof(float) is 4 and coordinates contains 2 vfloats (one for x and one for y), there are a total of 512 elements in the array. This also means that (base +j) must be less than 512 otherwise we will have an array out of bounds access. Given this, we created a function that will calculate a page full of coordinates to a specific second. What this really means is that, fillPage will calculate the coordinates for the next 51 seconds taking up 510 entries in the array.

In the code, *base* is used to represent the current time being processed in seconds and *j* is used to represent the time in tenths of a second (just like in the Patriot Missle System where an integer counter is used to keep track of the number of tenths of seconds since system start) and the array is used as a notional representation of the "range gate" (a window that specifies where the missle system should look next - a miscalculation in where the system should look next leads to an array out of bounds access instead of a missed interception).

If we expanded the array index we will see that

	base = ((int)(tempTime - startTime) * countsPerSecond)

Since *countsPerSecond* is 10 and *j* ranges from 0 to 9 inclusive we will have the trigger condition of *(base > 510) OR ( (base == 510) AND (j > 1) )*. Let's focus on the first condition. Since countsPerSecond is an int, the condition reduces to *(int)(tempTime - startTime) > 51*. Then since

	startTime = (float)(startCount) / (float)countsPerSecond;
	tempTime = (float)(currentCount) / (float)countsPerSecond;

where *startCount* is the starting time counter (notice I changed \*pCount to the more descriptive names) for this particular iteration of the fillPage function, the whole calculate reduces to 
	
	((float)(currentCount) / (float)countsPerSecond) - ((float)(startCount) / (float)countsPerSecond)

Note that due to rounding errors, the above code is not necessarily equal to

	((float)(currentCount) - (float)(startCount)) / (float)countsPerSecond

We can use the following code as an illustrative test:

	int count = 167773670;
	int count_m_510 = count - 510;
	
	printf("COUNT = [%d], [%.20f]\nCOUNT - 510 = [%d], [%.20f]\n", count, (float)count, count_m_510, (float)(count - 510));
	printf("TEST 1 = %.20f\n", (float)(count - count_m_510) / (float)10);
	printf("TEST 2 = %.20f\n", ((float)(count) - (float)(count_m_510)) / (float)10);
	printf("TEST 3 = %.20f\n", ((float)(count) / (float)10) - ((float)(count_m_510) / (float)10));
	printf("COUNT / 10.0 = [%.20f]\n(COUNT - 510) / 10.0 = [%.20f]\n", (float)count / (float)10, (float)count_m_510 / (float)10);

The corresponding output is:

	COUNT = [167773670], [167773664.00000000000000000000]
	COUNT - 510 = [167773160], [167773152.00000000000000000000]
	TEST 1 = 51.00000000000000000000
	TEST 2 = 51.20000076293945312500
	TEST 3 = 50.00000000000000000000
	COUNT / 10.0 = [16777366.00000000000000000000]
	(COUNT - 510) / 10.0 = [16777316.00000000000000000000]	

As one can see, the large integer value of **167773670** has been rounded into **167773664** in single precision floating point representation and **167773160** has been converted to **167773152**. What is even more intruiging is that the output of 

	printf("%d, %d\n", (int)(float)count_m_510 / 10, (int)((float)count_m_510 / (float)10.0));

is

	16777315, 16777316

Meaning there was some more rounding errors during the floating point calculations.

All in all, this CB is plagued with different sources of rounding errors which eventually leads to an out of bounds array access that seg-faults.
