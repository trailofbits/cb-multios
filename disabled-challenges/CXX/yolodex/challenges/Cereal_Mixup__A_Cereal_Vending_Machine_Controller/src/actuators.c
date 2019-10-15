/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "libcgc.h"
#include "cgc_libc.h"
#include "cgc_actuators.h"

unsigned char cgc_ready = 0;
unsigned char cgc_units = 0;
unsigned char cgc_bowl_set = 0;

void cgc_init_dispenser(void) {
	cgc_bowl_set = 0;
	cgc_units = 0;
	cgc_ready = 1;
}

void cgc_dispense_bowl(void) {
	cgc_bowl_set = 1;
}

void cgc_completion_buzzer(void) {
	cgc_ready = 0;
}

// liquids
void cgc_dispense_dairy_milk(void) {
	cgc_units++;
}
void cgc_dispense_dairy_cream(void) {
	cgc_units++;
}
void cgc_dispense_water(void) {
	cgc_units++;
}
void cgc_dispense_soy_milk(void) {
	cgc_units++;
}
void cgc_dispense_almond_milk(void) {
	cgc_units++;
}

// cereals
void cgc_dispense_sugar_loops(void) {
	cgc_units++;
}
void cgc_dispense_maize_flakes(void) {
	cgc_units++;
}
void cgc_dispense_marshmallow_figuringes(void) {
	cgc_units++;
}
void cgc_dispense_chocolate_rice_pellets(void) {
	cgc_units++;
}
void cgc_dispense_oohs_of_oats(void) {
	cgc_units++;
}
void cgc_dispense_crunchy_puffs(void) {
	cgc_units++;
}
void cgc_dispense_frutiz_n_nuts(void) {
	cgc_units++;
}

// toppings
void cgc_dispense_chocolate_drops(void) {
	cgc_units++;
}
void cgc_dispense_blueberries(void) {
	cgc_units++;
}
void cgc_dispense_berry_medley(void) {
	cgc_units++;
}
void cgc_dispense_sugar_cube(void) {
	cgc_units++;
}
void cgc_dispense_strawberries(void) {
	cgc_units++;
}

