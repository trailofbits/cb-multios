/*

Author: Bryce Kerley <bk@cromulence.co>

Copyright (c) 2014-2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include "cgc_scramble.h"
#include "cgc_scramble_gen.h"

#define TARGET 21
#define STATE_BITS 8
#define TARGET_MASK 0xff

uint8 cgc_scramble_steps = 0;
scramble_item state;

uint8 cgc_scramble_done() {
  return cgc_scramble_steps >= PHASE_COUNT;
}

void cgc_scramble_add(uint16 payload) {
  scramble_item current;
  current.i = payload;

  if (cgc_scramble_steps == 0) {
    state.i = 0;
  }

  switch (cgc_scramble_steps) {
  case 0:
    state = cgc_phase_0(current, state);
    break;
  case 1:
    state = cgc_phase_1(state, current);
    break;
  case 2:
    state = cgc_phase_2(current, state);
    break;
  case 3:
    state = cgc_phase_3(state, current);
    break;
  case 4:
    state = cgc_phase_4(current, state);
    break;
  case 5:
    state = cgc_phase_5(state, current);
    break;
  case 6:
    state = cgc_phase_6(current, state);
    break;
  case 7:
    state = cgc_phase_7(state, current);
    break;
  default:
    cgc__terminate(-1);
  }

  state.i &= TARGET_MASK;

  cgc_scramble_steps++;
}

uint8 cgc_scramble_okay() {
  return (state.i & TARGET_MASK) == TARGET;
}

#ifdef REVERSER
#include "cgc_stdlib.h"

int main(int cgc_argc, char *cgc_argv[]) {
  uint16 desired = TARGET;
  scramble_item mst, current;
  uint8 found;

  for (int i = 7; i >= 0; i--) {
    cgc_printf("phase @d: desired @x\n", i, desired);
    found = 0;

    for (uint32 j = 0; j <= UINT16_MAX; j++) {
        current.i = j >> STATE_BITS;
        mst.i = j & TARGET_MASK;

        switch (i) {
        case 0:
          mst = phase_0(current, mst);
          break;
        case 1:
          mst = phase_1(mst, current);
          break;
        case 2:
          mst = phase_2(current, mst);
          break;
        case 3:
          mst = phase_3(mst, current);
          break;
        case 4:
          mst = phase_4(current, mst);
          break;
        case 5:
          mst = phase_5(mst, current);
          break;
        case 6:
          mst = phase_6(current, mst);
          break;
        case 7:
          mst = phase_7(mst, current);
          break;
        default:
          _terminate(-1);
        }

        mst.i &= TARGET_MASK;
        cgc_printf("\r@x", mst.i);

        if (mst.i == desired) {
          cgc_printf("\rinput @x instate @x\n", current.i, j & TARGET_MASK);
          found = 1;
          desired = j & TARGET_MASK;
          break;
        }
    }

    if (!found) {
      cgc_printf("\ndidn't find :( :( :( \n");
      _terminate(-1);
    }
  }
}
#endif
