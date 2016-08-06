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
void init_dispenser(void);

/**
 * Set a new bowl onto the platform
 */
void dispense_bowl(void);

/**
 * Sound buzzer to user knows the machines is finished
 */
void completion_buzzer(void);

/**
 * The following functions operate all of the internal actuators that 
 * 	move / open / close / etc. to dispense the breakfast
 */

// liquids
void dispense_dairy_milk(void);
void dispense_dairy_cream(void);
void dispense_water(void);
void dispense_soy_milk(void);
void dispense_almond_milk(void);
// cereals
void dispense_sugar_loops(void);
void dispense_maize_flakes(void);
void dispense_marshmallow_figuringes(void);
void dispense_chocolate_rice_pellets(void);
void dispense_oohs_of_oats(void);
void dispense_crunchy_puffs(void);
void dispense_frutiz_n_nuts(void);
// toppings
void dispense_chocolate_drops(void);
void dispense_blueberries(void);
void dispense_berry_medley(void);
void dispense_sugar_cube(void);
void dispense_strawberries(void);


#endif