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
#ifndef ACTUATORS_H
#define ACTUATORS_H 1

/**
 * Initialize the state of the machine
 */
void cgc_init_dispenser(void);

/**
 * Set a new bowl onto the platform
 */
void cgc_dispense_bowl(void);

/**
 * Sound buzzer to user knows the machines is finished
 */
void cgc_completion_buzzer(void);

/**
 * The following functions operate all of the internal actuators that 
 * 	move / open / close / etc. to dispense the breakfast
 */

// liquids
void cgc_dispense_dairy_milk(void);
void cgc_dispense_dairy_cream(void);
void cgc_dispense_water(void);
void cgc_dispense_soy_milk(void);
void cgc_dispense_almond_milk(void);
// cereals
void cgc_dispense_sugar_loops(void);
void cgc_dispense_maize_flakes(void);
void cgc_dispense_marshmallow_figuringes(void);
void cgc_dispense_chocolate_rice_pellets(void);
void cgc_dispense_oohs_of_oats(void);
void cgc_dispense_crunchy_puffs(void);
void cgc_dispense_frutiz_n_nuts(void);
// toppings
void cgc_dispense_chocolate_drops(void);
void cgc_dispense_blueberries(void);
void cgc_dispense_berry_medley(void);
void cgc_dispense_sugar_cube(void);
void cgc_dispense_strawberries(void);


#endif