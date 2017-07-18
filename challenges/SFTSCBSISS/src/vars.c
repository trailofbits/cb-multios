/*

Author: Joe Rogers <joe@cromulence.co>

Copyright (c) 2015 Cromulence LLC

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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_stdint.h"
#include "cgc_vars.h"

vars_t *cgc_pVARS = NULL;

// Init VARS
int32_t cgc_InitVARS(void) {

	if ((cgc_pVARS = cgc_CreateVARSObject("system.name", STRING, "CGC CB")) == NULL) {
		return(0);
	}

	return(1);
}

// Destroy VARS
int32_t cgc_DestroyVARS(void) {
	vars_t *pm;
	vars_t *pm_next;

	// make sure we have a VARS
	if (!cgc_pVARS) {
		return(0);
	}

	// walk the vars and free everything
	pm = cgc_pVARS;
	while (pm) {
		pm_next = pm->next;
		cgc_free(pm);
		pm = pm_next;
	}
	
	return(1);
		
}

// Search VARS
vars_t *cgc_SearchVARS(char *target_name) {
	vars_t *pm;

	// if we have no VARS
	if (!cgc_pVARS || !target_name) 
		return(NULL);

	// walk the VARS and find the target	
	pm = cgc_pVARS;
	while (pm) {
		if (cgc_strcmp(pm->name, target_name) == 0) {
			return(pm);
		}	

		pm = pm->next;
	}

	// didn't find a matching name
	return(NULL);
}

// Create a new VARS object
vars_t *cgc_CreateVARSObject(char *name, uint8_t type, void *value) {
	vars_t *pm;
	char *c;

	// check inputs
	if (!name || !value || !(type == STRING || type == INT32)) {
		return(NULL);
	}

	// create the object
	if ((pm = cgc_calloc(1, sizeof(vars_t))) == NULL) {
		cgc__terminate(-1);
	}

	// Copy the data into the object
	cgc_strncpy(pm->name, name, MAX_NAME_LEN-1);

	pm->type = type;
	if (type == STRING) {
		cgc_strncpy((char *)pm->value, value, MAX_VALUE_LEN-1);
	} else if (type == INT32) {
		cgc_memcpy(pm->value, value, 4);
	}

	return(pm);

}

// Insert new VARS object
int32_t cgc_InsertVARSObject(vars_t *pm) {

	if (!cgc_pVARS || !pm) {
		return(0);
	}

	pm->prev = NULL;
	pm->next = cgc_pVARS;
	cgc_pVARS->prev = pm;
	cgc_pVARS = pm;

	return(1);
}

// Delete VARS object
int32_t cgc_DeleteVARSObject(vars_t *target) {
	vars_t *pm;

	if (!cgc_pVARS || !target) {
		return(0);
	}

	pm = cgc_pVARS;
	while (pm) {
		if (cgc_strcmp(pm->name, target->name) != 0) {
			continue;
		}

		// handle case where target is head object
		if (pm == cgc_pVARS) {
			cgc_pVARS = pm->next;
			cgc_free(pm);
			return(1);
		}

		// handle everything else
		pm->prev->next = pm->next;
		if (pm->next) {
			pm->next->prev = pm->prev;
		}
		cgc_free(pm);

		return(1);
	}

	return(0);

}

// Update VARS object
vars_t *cgc_UpdateVARSObject(char *name, uint8_t type, void *value) {
	vars_t *pm;

	if (!name || !value || !(type == STRING || type == INT32)) {
		return(NULL);
	}

	// find the object we're updating
	if ((pm = cgc_SearchVARS(name)) == NULL) {
		// not found, create it
		if ((pm = cgc_CreateVARSObject(name, type, value)) == NULL) {
			return(NULL);
		} else {
			if (!cgc_InsertVARSObject(pm)) {
				return(NULL);
			}
		}
		return(pm);
	}

	// make sure it's of the correct type
	if (pm->type != type) {
		return(NULL);
	}

	if (type == STRING) {
		cgc_strncpy((char *)pm->value, value, MAX_VALUE_LEN-1);

	} else if (type == INT32) {
		cgc_memcpy(pm->value, value, 4);
	}

	return(pm);
}
