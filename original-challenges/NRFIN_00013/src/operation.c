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
#include "operation.h"
#include "math_fun.h"

typedef enum {
	MEAN = 0,	// * Average/Mean - The average of the numbers in the list.
	MEDIAN,		// * Median - The median of the numbers in the list.
	MODE,		// * Mode - The list of numbers that occur most frequently (one or more).
	RANGE,		// * Range - The difference between the maximum and minimum numbers in the list.
	SUM,		// * Sum - The sum of the numbers in the list.
	PRODUCT,	// * Product - The product of the numbers in the list.
	MIN,		// * Minimum - The minimum number in the list.
	MAX,		// * Maximum - The maximum number in the list.
	SORT,		// * Sort - The list sorted ascending.
	RSORT,		// * Reverse Sort - The list sorted descending.
	ODDS,		// * Odds - The odd numbers in the list.
	EVENS,		// * Evens - The even numbers in the list.
	num_math_ops
} MATH_OPS;

typedef enum {
	INT32 = 0,
	DBL64,
	list_types
} NUM_TYPE;


list_t * num_list = NULL;
list_t * sorted_asc_num_list = NULL;
NUM_TYPE nt;

/*
 Read in the list type and store it in nt.
*/
int get_list_type() {
	// read list type (uint8_t)
	uint8_t l_type = 0;
    RECV(&l_type, sizeof(uint8_t));

    if (l_type < list_types) {
    	nt = l_type;
    	return 0;
    } else {
    	return -30;
    }
}

/*
 Read in the count and return it in count.
*/
void get_num_count(uint32_t * count) {
	// read number count (uint32_t)
    RECV(count, sizeof(uint32_t));
}

/*
 Read in the op_code and return it in op_code
*/
int get_op_code(MATH_OPS * op_code) {
	// read op_code (uint8_t)
	uint8_t oc = 0;
	RECV(&oc, sizeof(uint8_t));
	if (oc < num_math_ops) {
		*op_code = oc;
		return 0;
	} else {
		return -80;
	}
}

/*
 Create a node and store the received double into it.
 Success: &node
 Failure: terminate
*/
node_t * read_double_into_node() {
	dbl64_data_t * data = NULL;
	ALLOC(sizeof(dbl64_data_t), &data);
	// allocate(sizeof(dbl64_data_t), 0, (void **)&data);

	// read next number as double
    RECV(data, sizeof(double));

	// create node with number
	return node_create(data);
}

/*
 Create a node and store the received int32 into it.
 Success: &node
 Failure: terminate
*/
node_t * read_int_into_node() {
	int32_data_t * data = NULL;
	ALLOC(sizeof(int32_data_t), &data);
	// allocate(sizeof(int32_data_t), 0, (void **)&data);

	// read next number
    RECV(data, sizeof(int32_t));

	// create node with number
	return node_create(data);
}

/*
 Create a copy of a node
 Success: &node
 Failure: terminate
*/
node_t * dup_double_node(node_t * nd) {
	dbl64_data_t * data = NULL;
	ALLOC(sizeof(dbl64_data_t), &data);
	// allocate(sizeof(dbl64_data_t), 0, (void **)&data);

	// copy nodes' data into new data struct
	dbl64_data_t * data2 = (dbl64_data_t *)nd->data;
	data->val = data2->val;

	// create node with number
	return node_create(data);
}

/*
 Create a copy of a node
 Success: &node
 Failure: terminate
*/
node_t * dup_int_node(node_t * nd) {
	int32_data_t * data = NULL;
	ALLOC(sizeof(int32_data_t), &data);
	// allocate(sizeof(int32_data_t), 0, (void **)&data);
	ALLOC(sizeof(int32_data_t), &data);

	// copy nodes' data into new data struct
	int32_data_t * data2 = (int32_data_t *)nd->data;
	data->val = data2->val;

	// create node with number
	return node_create(data);
}

/*
 Comparison function for int32_data_t nodes.
 if nd1->data->val < nd2->data->val, return -1
 if nd1->data->val > nd2->data->val, return 1
 else, return 0

 node->data == int32_data_t *
 typedef struct int32_data {
	int32_t val;
 } int32_data_t;
*/
int int32_node_compare(node_t * nd1, node_t * nd2) {
	int32_t v1 = ((int32_data_t *)nd1->data)->val;
	int32_t v2 = ((int32_data_t *)nd2->data)->val;

	if (v1 < v2) {return -1;}
	else if (v1 > v2) {return 1;}
	else {return 0;}
}

/*
 Comparison function for dbl64_data_t nodes.
 if nd1->data->val < nd2->data->val, return -1
 if nd1->data->val > nd2->data->val, return 1
 else, return 0

 node->data == dbl64_data_t * 
 typedef struct dbl64_data {
	double val;
 } dbl64_data_t;
*/
int dbl64_node_compare(node_t * nd1, node_t * nd2) {
	double v1 = ((dbl64_data_t *)nd1->data)->val;
	double v2 = ((dbl64_data_t *)nd2->data)->val;

	if (v1 < v2) {return -1;}
	else if (v1 > v2) {return 1;}
	else {return 0;}
}

/*
 Create the list. Then read in list of numbers and store them in the list.
 Success: 0
 Failure: < 0
*/
int load_list(uint32_t count) {
    // create list
    if((num_list = list_create_dup()) == NULL) {return ERRNO_ALLOC;}
    if((sorted_asc_num_list = list_create_dup()) == NULL) {return ERRNO_ALLOC;}

	node_t * nd = NULL;
	node_t * nd2 = NULL;
    // loop through numbers and add them as nodes
	// insert node into list (insertion sort, ascending)
    for(; count > 0; count--) {
    	// recv node
    	nd = NULL;
    	nd2 = NULL;
    	switch(nt) {
    		case INT32:
    			if((nd = read_int_into_node()) == NULL) {return ERRNO_ALLOC;}
    			if((nd2 = dup_int_node(nd)) == NULL) {return ERRNO_ALLOC;}
		    	list_insert_sort(sorted_asc_num_list, nd, int32_node_compare);
		    	list_append(num_list, nd2);
    			break;
    		case DBL64:
    			if((nd = read_double_into_node()) == NULL) {return ERRNO_ALLOC;}
    			if((nd2 = dup_double_node(nd)) == NULL) {return ERRNO_ALLOC;}
		    	list_insert_sort(sorted_asc_num_list, nd, dbl64_node_compare);
		    	list_append(num_list, nd2);		    	
    			break;
    		default:
    			return -1;
    	}
    }
    return 0;
}

/*
 Create the list and load the numbers into it.
 Success: 0
 Failure: < 0
*/
int do_create() {

	if (num_list != NULL) {
		return -9;
	}

	int ret = 0;
	if ((ret = get_list_type()) < 0) {return ret;}

    uint32_t num_count = 0;
    get_num_count(&num_count);

#ifdef PATCHED
    if (num_count == 0) {return -70;}
#else

#endif
    if (num_count > MAX_LIST_LEN) {return -70;}

	return load_list(num_count);
}

/*
 Read an op_code. Then process the operation on the list of numbers and return the result.
 Success: 0
 Failure: < 0
*/
int do_eval() {

	if (num_list == NULL) {
		return -10;
	}

	int ret = 0;
	MATH_OPS mo = 0;
	if ((ret = get_op_code(&mo)) < 0) {return ret;}

	switch(nt) {
		case INT32:
			switch(mo) {
				case MEAN:
					do_int_mean(num_list);
					break;
				case MEDIAN:
					do_int_median(sorted_asc_num_list);
					break;
				case MODE:
					do_int_mode(sorted_asc_num_list);
					break;
				case RANGE:
					do_int_range(sorted_asc_num_list);
					break;
				case SUM:
					do_int_sum(num_list);
					break;
				case PRODUCT:
					do_int_product(num_list);
					break;
				case MIN:
					do_int_min(num_list);
					break;
				case MAX:
					do_int_max(num_list);
					break;
				case SORT:
					do_int_sort(sorted_asc_num_list);
					break;
				case RSORT:
					do_int_rsort(sorted_asc_num_list);
					break;
				case ODDS:
					do_int_odds(num_list);
					break;
				case EVENS:
					do_int_evens(num_list);
					break;
				default:
					return -101;
			}
			break;

		case DBL64:
			switch(mo) {
				case MEAN:
					do_dbl_mean(num_list);
					break;
				case MEDIAN:
					do_dbl_median(sorted_asc_num_list);
					break;
				case MODE:
					do_dbl_mode(sorted_asc_num_list);
					break;
				case RANGE:
					do_dbl_range(sorted_asc_num_list);
					break;
				case SUM:
					do_dbl_sum(num_list);
					break;
				case PRODUCT:
					do_dbl_product(num_list);
					break;
				case MIN:
					do_dbl_min(num_list);
					break;
				case MAX:
					do_dbl_max(num_list);
					break;
				case SORT:
					do_dbl_sort(sorted_asc_num_list);
					break;
				case RSORT:
					do_dbl_rsort(sorted_asc_num_list);
					break;
				case ODDS:
					do_dbl_odds(num_list);
					break;
				case EVENS:
					do_dbl_evens(num_list);
					break;
				default:
					return -101;
			}
			break;

		default:
			return -122;
	}

	return 0;
}

/*
 Generate a random nonce and send it to the client.
 Read the value sent back from the client and verify that it matches the nonce.
 Success: 0
 Failure: < 0
*/
 int do_nonce() {
 	long long nonce[1];
 	long long nonce_reply[1];
 	size_t bytes = 0;
 	int ret = 0;
 	if((ret = rand((char *)nonce, 8)) != 0) {return -45;}

 	SENDLL(nonce);

    RECV(&nonce_reply, sizeof(long long));

    if (nonce[0] == nonce_reply[0]) {
    	return 0;
    } else {
    	return -44;
    }
 }