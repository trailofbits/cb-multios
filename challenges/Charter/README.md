# Charter

## Author Information

"Bryce Kerley" <bk@cromulence.co>

### DARPA performer group
Cromulence (CROMU)

## Description

This service generates charts for numeric data, including horizontal bar charts,
sparklines, amd also produces random numbers.

### Feature List

* Bar charts, with different scale factors
* Sparklines using UTF-32 characters
* Echo back data
* A seedable PRNG

### State Chart

* Start: decide on quantity and qualities of data
* Send data: load data after connection
* Menu: receive a "ready" message, along with the count of data received; choose
  a function.
* Sparks: sparkline, send some sparks, get a sparkline chart
* Bars: bar chart, send some scale factors, get a bar chart
* Echo: send a character count, receive that many random words
* Seed: send a 32-bit number, seed the PRNG
* Noise: dump out a bunch of PRNG state
* Terminate: disconnect

After the PRNG has been seeded, the state chart loses the ability to predict
bar chart sizes: this is `tainted` mode.

## Input

The input format is mostly unsigned 32-bit integers. Integers are always big-
endian.

### Send data

1. Send unsigned 32-bit integer of how many data you will send.
2. Send that many unsigned 32-bit integers

### Menu

1. Send unsigned 32-bit integer for the desired option.

### Sparks

1. Send number of different sparks.
2. Send each spark as a 32-bit integer (represenging a Unicode codepoint)

### Bars

1. Send `max_value`: Maximum value of a single datum
2. Send `column_count`: Number of columns to use when drawing
3. Send `bar_character`: code point to use as bar (will only use the least-significant
   8 bits)

### Echo

1. Send number of 32-bit integers to echo back
2. Send that many 32-bit integers.

### Seed

1. Send one 32-bit integer

### Noise

1. Send one 32-bit integer for how many bytes of noise you want. Will be
   truncated to next-smallest amount divisible by 4.

### Replacer

1. No input

## Output

### Sparks

Given sparks in the range of 0x2581 to 0x2588 and data 0-7, sparkline mode
should output the sparks verbatim.

### Bars

Given a `max_value` of 16, `column_count` of 16, a `bar_character` of 'X', and
data 0, 4, 8, 12, 16, 15, 14:

```

XXXX
XXXXXXXX
XXXXXXXXXXXX
XXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXX
XXXXXXXXXXXXXX
```

If the `column_count` and `max_value` are dissimilar, the column length will
be truncated to the lower value.

Given `max_value` of 16, `column_count` of 10, and data 4, 5, 6, 7, and 8:

```
XX
XXX
XXX
XXXX
XXXXX
```

Given `max_value` of 16, `column_count` of 32, and the same data:

```
XXXXXXXX
XXXXXXXXXX
XXXXXXXXXXXX
XXXXXXXXXXXXXX
XXXXXXXXXXXXXXXX
```

### Echo

Echo repeats 32-bit integers back verbatim.

### Seed

Seed has no output.

### Noise

Given a quantity N, noise outputs N - (N % 4) bytes of pseudorandom data.

### Replacer

Replacer has no output.

## Vulnerability
When the PRNG has been seeded, it multiplies the bar chart lengths by 1, 2, 3,
or 4, which can cause a maximum-length bar to overflow.

The second vulnerability exists due to an incorrect allocation size based upon user input. A user supplies the number of sparkles and a buffer is allocated with that size. However in the loop reading  the sparkle data sparle count uint32s are read which is 4 times larger than the actually allocated size.

### CWE classification
CWE-120 Stack-based Buffer Overflow
CWE-122 Heap-based Buffer Overflow

## Challenges

The attacker must find a random seed that allows bars to overflow their buffer.
