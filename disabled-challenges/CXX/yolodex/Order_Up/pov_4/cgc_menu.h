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
#ifndef MENU_H
#define MENU_H 1

#define FOODSZ	20

#define APP_NAME_SZ 	FOODSZ

#define MEAL_NAME_SZ 	FOODSZ
#define MEAL_MAIN_SZ 	FOODSZ
#define MEAL_VEG_SZ 	FOODSZ
#define MEAL_SIDE_SZ 	FOODSZ

#define DES_NAME_SZ 	FOODSZ

typedef enum {
	APP_TYPE = 0,
	MEAL_TYPE = 1,
	DES_TYPE = 2,
	FOOD_TYPES = 3,
} FoodTypes;

typedef struct {
	FoodTypes ftype;
	char name[APP_NAME_SZ];
	void *next;
} Appetizer;

typedef struct {
	FoodTypes ftype;
	char name[MEAL_NAME_SZ];
	char main[MEAL_MAIN_SZ];
	char veggies[MEAL_VEG_SZ];
	char side[MEAL_SIDE_SZ];
	void *next;
} Meal;

typedef struct {
	FoodTypes ftype;
	char name[DES_NAME_SZ];
	void *next;
} Dessert;

typedef struct {
	Appetizer *appetizer_list;
	Meal *meal_list;
	Dessert *dessert_list;
} Menu;


#endif
