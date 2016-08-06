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

#include <libcgc.h>
#include "libc.h"
#include "common.h"
#include "tank.h"
#include "h2o.h"

struct tank *create_tank(uint8_t id, uint8_t capacity) {
	struct tank *t = calloc(sizeof(struct tank) + capacity * sizeof(struct h2o *));

	t->id = id;
	t->fill_rate = 0;
	t->valve_position = CLOSED;
	t->capacity = capacity;

	for (uint8_t i = 0; i < INIT_LEVEL; i++) {
		t->contents[i] = create_h2o();
		t->level++;
	}

	t->status = OUT_OF_SERVICE;
	t->eol = FALSE;

	return t;
}

int set_fill_rate(struct tank *t, uint8_t fr) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}
	int ret = 0;
	if (0 > (ret = is_end_of_life(t))) {return ret;}
	if (FALSE == ret) {
		if (OUT_OF_SERVICE == t->status) {
			t->fill_rate = 0;
		} else {
			t->fill_rate = fr;
		}
	} else {
		return ERR_END_OF_LIFE;
	}
	return SUCCESS;
}

int set_drain_rate(struct tank *t, uint8_t dr) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}
	int ret = 0;
	if (0 > (ret = is_end_of_life(t))) {return ret;}
	if (FALSE == ret) {
		if (OUT_OF_SERVICE == t->status) {
			t->drain_rate = 0;
		} else {
			t->drain_rate = dr;
		}		
	} else {
		return ERR_END_OF_LIFE;
	}
	return SUCCESS;
}

int open_valve(struct tank *t) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}
	int ret = 0;
	if (0 > (ret = is_end_of_life(t))) {return ret;}
	if (FALSE == ret) {
		t->valve_position = OPEN;
	} else {
		return ERR_END_OF_LIFE;
	}
	return SUCCESS;
}

int close_valve(struct tank *t) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}
	int ret = 0;
	if (0 > (ret = is_end_of_life(t))) {return ret;}
	if (FALSE == ret) {
		t->valve_position = CLOSED;
	} else {
		return ERR_END_OF_LIFE;
	}
	return SUCCESS;
}

int set_status(struct tank *t, uint8_t s) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}
	t->status = s;
	return SUCCESS;
}

int set_in_service(struct tank *t) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}
	int ret = 0;
	if (0 > (ret = is_end_of_life(t))) {return ret;}
	if (FALSE == ret) {
		FAILBAIL(set_status(t, IN_SERVICE));
		FAILBAIL(set_fill_rate(t, FILL_RATE));
	} else {
		return ERR_END_OF_LIFE;
	}

	return SUCCESS;
}

int set_out_of_service(struct tank *t) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}
	int ret = 0;
	if (0 > (ret = is_end_of_life(t))) {return ret;}
	if (FALSE == ret) {
		FAILBAIL(set_status(t, OUT_OF_SERVICE));
		FAILBAIL(set_fill_rate(t, 0));
		FAILBAIL(set_drain_rate(t, 0));
		FAILBAIL(close_valve(t));
	} else {
		return ERR_END_OF_LIFE;
	}

	return SUCCESS;
}

int is_in_service(struct tank *t) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}
	if (IN_SERVICE == t->status) {
		return TRUE;
	} else {
		return FALSE;
	}
}

int set_end_of_life(struct tank *t) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}
	if (TRUE == t->eol) {
		return ERR_END_OF_LIFE;
	}
	set_out_of_service(t);
	t->eol = TRUE;

	return SUCCESS;
}

int is_end_of_life(struct tank *t) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}
	if (TRUE == t->eol) {
		return TRUE;
	} else {
		return FALSE;
	}
}

int add_water(struct tank *t, uint8_t qty) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}

#if PATCHED
	if (t->level > (t->level + qty)) {
		return ERR_TANK_FULL;
	}
#endif

	// VULN: no verification of qty to prevent
	// tank from overfilling and thus t->level
	// int overflow.

	for (uint8_t i = 0; i < qty; i++) {
		t->contents[t->level++] = create_h2o();
	}

	return SUCCESS;
}

int rm_water(struct tank *t, uint8_t qty) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}

	struct h2o *h = NULL;

	for (uint8_t i = 0; i < qty; i++) {
		if (0 == t->level) {
			return ERR_TANK_EMPTY;
		}
		t->level--;
		h = t->contents[t->level];
		t->contents[t->level] = NULL;
		destroy_h2o(h);
	}

	return SUCCESS;
}

int do_fill(struct tank *t) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}
	int ret = 0;
	if (0 > (ret = is_end_of_life(t))) {return ret;}

	if (FALSE == ret) {
		if ((OPEN == t->valve_position) && (IN_SERVICE == t->status)) {
			FAILBAIL(add_water(t, t->fill_rate));
		}		
	} else {
		return ERR_END_OF_LIFE;
	}
	return SUCCESS;
}

int do_drain(struct tank *t) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}
	int ret = 0;
	if (0 > (ret = is_end_of_life(t))) {return ret;}

	if (FALSE == ret) {
		if (IN_SERVICE == t->status) {
			FAILBAIL(rm_water(t, t->drain_rate));
		}
	} else {
		return ERR_END_OF_LIFE;
	}
	return SUCCESS;
}

int is_level_low(struct tank *t) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}
	int ret = 0;
	if (0 > (ret = is_end_of_life(t))) {return ret;}

	if (FALSE == ret) {
		if (LOW_LEVEL >= t->level) {
			return TRUE;
		} else {
			return FALSE;
		}
	} else {
		return ERR_END_OF_LIFE;
	}
}

int is_level_crit_low(struct tank *t) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}
	int ret = 0;
	if (0 > (ret = is_end_of_life(t))) {return ret;}

	if (FALSE == ret) {
		if (CRIT_LEVEL >= t->level) {
			return TRUE;
		} else {
			return FALSE;
		}
	} else {
		return ERR_END_OF_LIFE;
	}
}
