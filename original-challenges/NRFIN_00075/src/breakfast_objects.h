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

#ifndef BREAKFAST_OBJECTS_H
#define BREAKFAST_OBJECTS_H 1



// TODO: enable "other" types after the basic stuff is up and working.

typedef enum SerialVersionUID {LIQUID, CEREAL, TOPPINGS, GENERIC_STRING,
			PRINTER_STRING, COMMAND_RUNNER, SVU_COUNT} svu_t;

typedef enum LiquidsSubTypeID {DAIRY_MILK, DAIRY_CREAM,	WATER, SOY_MILK,
			ALMOND_MILK, L_STI_COUNT} l_sti_t;

typedef enum CerealsSubTypeID {SUGAR_LOOPS, MAIZE_FLAKES, MARSHMALLOW_FIGURINES,
			CHOCOLATE_RICE_PELLETS, OHHS_OF_OATS, CRUNCHY_PUFFS, FRUITZ_N_NUTZ,
			C_STI_COUNT} c_sti_t;

typedef enum ToppingsSubTypeID {CHOCOLATE_DROPS, BLUEBERRIES, BERRY_MEDLEY,
			SUGAR_CUBE,	STRAWBERRIES, T_STI_COUNT} t_sti_t;

extern const char *typeName[];

// Object types for the application

typedef struct liquids Liquids;
struct liquids {
	svu_t serialVersionUID;
	unsigned char typeName[8];
	l_sti_t subTypeID;
	int (*set_data)(Liquids *, svu_t, l_sti_t);
	void (*destroy)(Liquids *);
};

typedef struct cereals Cereals;
struct cereals {
	svu_t serialVersionUID;
	unsigned char typeName[8];
	c_sti_t subTypeID;
	int (*set_data)(Cereals *, svu_t, c_sti_t);
	void (*destroy)(Cereals *);
};

typedef struct toppings Toppings;
struct toppings {
	svu_t serialVersionUID;
	unsigned char typeName[9];
	t_sti_t subTypeID;
	int (*set_data)(Toppings *, svu_t, t_sti_t);
	void (*destroy)(Toppings *);
};

// Object types that come with the SDK (whether you ask for them or not)
typedef struct genericString GenericString;
struct genericString {
	svu_t serialVersionUID;
	unsigned char typeName[15];
	char *str;
	int (*set_data)(GenericString *, svu_t, char *);
	void (*destroy)(GenericString *);
};

typedef struct printerString PrinterString;
struct printerString {
	svu_t serialVersionUID;
	unsigned char typeName[15];
	char *str;
	int (*set_data)(PrinterString *, svu_t, char *);
	void (*destroy)(PrinterString *);
};

typedef __attribute__((regparm(2))) void (*run_fn)(int, int, int);

typedef struct commandRunner CommandRunner;
struct commandRunner {
	svu_t serialVersionUID;
	unsigned char typeName[15];
	run_fn fn;
	unsigned short argc;
	int argv[3];
	int (*set_data)(CommandRunner *, svu_t, unsigned short, char *);
	void (*destroy)(CommandRunner *);
};

/**
 * Construct an empty Liquids object
 *
 * @return VA of object or NULL on error
 */
Liquids *constructor_liquids(void);
/**
 * Construct an empty Cereals object
 *
 * @return VA of object or NULL on error
 */
Cereals *constructor_cereals(void);
/**
 * Construct an empty Toppings object
 *
 * @return VA of object or NULL on error
 */
Toppings *constructor_toppings(void);

/**
 * Deserialize a Liquids object from a given buffer
 *
 * @param in 	Pointer to input buffer
 * @return VA of deserialized object or NULL on error
 */
Liquids *deserialize_liquids(char **in);
/**
 * Deserialize a Cereals object from a given buffer
 *
 * @param in 	Pointer to input buffer
 * @return VA of deserialized object or NULL on error
 */
Cereals *deserialize_cereals(char **in);
/**
 * Deserialize a Toppings object from a given buffer
 *
 * @param in 	Pointer to input buffer
 * @return VA of deserialized object or NULL on error
 */
Toppings *deserialize_toppings(char **in);

/**
 * Check input buffer for serialized forms of inherited types
 *
 * @param serialVersionUID 	UID of serialized type to deserialized
 * @param cur 				Pointer to input buffer
 * @return SUCCESS if inherited type was found/deserialized, else -1
 */
ssize_t check_inherited_types(svu_t serialVersionUID, char **cur);

#endif

