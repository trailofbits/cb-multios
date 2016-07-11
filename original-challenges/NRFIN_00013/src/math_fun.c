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
#include "math_fun.h"
#include "operation.h"

/*
 Average/Mean - The average of the numbers in the list.
 do sum / count using signed int division
 - expect int overflow/underflow
*/
void do_int_mean(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	int32_t sum = 0;
	while(curr != get_list_tail(num_list)) {
		int32_data_t * d = (int32_data_t *)curr->data;
		sum += d->val;

		curr = curr->next;
	}

	int32_t mean = 0;
	if (num_list->count > 0) {
		// yes. that's int division
		// and C's int division truncates toward 0.
		mean = sum / (int32_t)num_list->count;
	}

	SENDSI(mean);
}

/*
 Median - The median of the numbers in the list.
  if length of list is odd, it's the center item of a sorted list
  if length is even, it is the mean of the 2 center items of a sorted list
 - Expect int overflow/underflow
 -
*/
void do_int_median(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	uint32_t middle = num_list->count / 2; // should truncate toward 0
	while(curr != get_list_tail(num_list) && middle) {
		curr = curr->next;
		middle--;
	}

	int32_t median = 0;
	if (num_list->count % 2 == 0) { // if even length
		int32_t cur_val = 0;
		int32_t prev_val = 0;
		int32_data_t * d = (int32_data_t *)curr->data;
		cur_val = d->val;
		int32_data_t * d2 = (int32_data_t *)curr->prev->data;
		prev_val = d2->val;
		median = (cur_val + prev_val) / 2; // should truncate toward 0

	} else { // if odd length
		int32_data_t * d = (int32_data_t *)curr->data;
		median = d->val;
	}

	SENDSI(median);
}

/*
 Mode - The list of the most frequently occuring number(s).
 - If all numbers occur the same number of time, the list is empty
 - Else the list has one or more elements.
*/
void do_int_mode(list_t * num_list) {
	uint32_t max_count = 0;
	uint32_t num_with_max_count = 0;
	uint32_t cur_count = 0;
	int32_t cur_val = 0;

	// find max_count (max count of any number in the list)
	node_t * curr = get_first_node(num_list);
	while(curr != get_list_tail(num_list)) {
		int32_data_t * d = (int32_data_t *)curr->data;
		if (cur_val == d->val) { // another val same as cur_val
			cur_count++;
		} else { // new val
			cur_val = d->val;
			cur_count = 1;
		}

		if (cur_count > max_count) {
			max_count = cur_count;
			num_with_max_count = 1;
		} else if (cur_count == max_count) {
			num_with_max_count++;
		}

		curr = curr->next;
	}

	// no mode if all numbers have equal count or the list is empty
	if (max_count <= 1) {
		max_count = 0;
		SENDUI(max_count);
	} else { // have a mode
		SENDUI(num_with_max_count);

		// send values having max_count
		curr = get_first_node(num_list);
		while(curr != get_list_tail(num_list)) {
			int32_data_t * d = (int32_data_t *)curr->data;
			if (cur_val == d->val) { // another val same as cur_val
				cur_count++;
			} else { // new val
				cur_val = d->val;
				cur_count = 1;
			}

			if (cur_count == max_count) {
				SENDSI(cur_val);
			}

			curr = curr->next;
		}
	}
}

/*
 Calculate the difference between the min and max values in the list
 num_list is sorted ascending, so it's the difference between the last
 and first elements in the list.
*/
void do_int_range(list_t * num_list) {
	node_t * head = get_first_node(num_list);
	node_t * tail = get_last_node(num_list);

	int32_t range = 0;
	int32_data_t * d1 = (int32_data_t *)tail->data;
	range = d1->val;
	int32_data_t * d = (int32_data_t *)head->data;
	range -= d->val;

	SENDSI(range);
}

/*
 Calculate the sum of all int values in the list
 - Expect int overflow/underflow
*/
void do_int_sum(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	int32_t sum = 0;
	while(curr != get_list_tail(num_list)) {
		int32_data_t * d = (int32_data_t *)curr->data;
		sum += d->val;

		curr = curr->next;
	}

	SENDSI(sum);
}

/*
 Calculate the product of all int values in the list
 - Expect lots of int overflow/underflow
*/
void do_int_product(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	int32_t product = 1;
	while(curr != get_list_tail(num_list)) {
		int32_data_t * d = (int32_data_t *)curr->data;
		product *= d->val;

		curr = curr->next;
	}

	SENDSI(product);
}

/*
 Calculate the min of all values in the list
*/
void do_int_min(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	int32_t min = 2147483647;
	while(curr != get_list_tail(num_list)) {
		int32_data_t * d = (int32_data_t *)curr->data;
		if (d->val < min) {
			min = d->val;
		}

		curr = curr->next;
	}

	SENDSI(min);
}

/*
 Calculate the max of all values in the list
*/
void do_int_max(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	int32_t max = -2147483646;
	while(curr != get_list_tail(num_list)) {
		int32_data_t * d = (int32_data_t *)curr->data;
		if (max < d->val) {
			max = d->val;
		}

		curr = curr->next;
	}

	SENDSI(max);	
}

/*
 The list is sorted in ascending order by default during node insertion.
 Send each value back to client in sorted ascending order.
*/
void do_int_sort(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	while(curr != get_list_tail(num_list)) {
		int32_data_t * d = (int32_data_t *)curr->data;
		SENDSI(d->val);

		curr = curr->next;
	}
}

/*
 The list is sorted in ascending order by default during node insertion.
 Send each value back to client in sorted descending order.
*/
void do_int_rsort(list_t * num_list) {
	node_t * curr = get_last_node(num_list);

	while(curr != get_list_head(num_list)) {
		int32_data_t * d = (int32_data_t *)curr->data;
		SENDSI(d->val);

		curr = curr->prev; // reverse through list
	}
}

/*
 Search the list for odd numbers. Send to the client, first the count
 of odd numbers, then each odd number.
*/
void do_int_odds(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	// determine count and send it.
	uint32_t count = 0;
	while(curr != get_list_tail(num_list)) {
		int32_data_t * d = (int32_data_t *)curr->data;
		if (d->val % 2 != 0) {
			count++;
		}

		curr = curr->next;
	}
	SENDUI(count);

	// send each odd val
	if (count > 0) {

		curr = get_first_node(num_list);
		while(curr != get_list_tail(num_list)) {
			int32_data_t * d = (int32_data_t *)curr->data;
			if (d->val % 2 != 0) {
				SENDSI(d->val);
			}

			curr = curr->next;
		}
	}
}

/*
 Search the list of even numbers. Send to the client, first the count
 of even numbers, then each even number.
*/
void do_int_evens(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	// determine count and send it.
	uint32_t count = 0;
	while(curr != get_list_tail(num_list)) {
		int32_data_t * d = (int32_data_t *)curr->data;
		if (d->val % 2 == 0) {
			count++;
		}

		curr = curr->next;
	}
	SENDUI(count);

	// send each odd val
	if (count > 0) {
		curr = get_first_node(num_list);
		while(curr != get_list_tail(num_list)) {
			int32_data_t * d = (int32_data_t *)curr->data;
			if (d->val % 2 == 0) {
				SENDSI(d->val);
			}

			curr = curr->next;
		}		
	}
}

/*
 Average/Mean - The average of the numbers in the list.
 = sum / count using floating point division
*/
void do_dbl_mean(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	double sum = 0.0;
	while(curr != get_list_tail(num_list)) {
		dbl64_data_t * d = (dbl64_data_t *)curr->data;
		sum += d->val;

		curr = curr->next;
	}

	double mean = 0.0;
	if (num_list->count > 0) {
		mean = sum / num_list->count;
	}

	SENDD(mean);
}

/*
 Median - The median of the numbers in the list.
 if length of list is odd, it's the center item of a sorted list
 if length is even, it is the mean of the 2 center items of a sorted list
*/
void do_dbl_median(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	uint32_t middle = num_list->count / 2; // should truncate toward 0
	while(curr != get_list_tail(num_list) && middle) {
		curr = curr->next;
		middle--;
	}

	double median = 0.0;
	if (num_list->count % 2 == 0) { // if even length
		double cur_val = 0.0;
		double prev_val = 0.0;
		dbl64_data_t * d = (dbl64_data_t *)curr->data;
		cur_val = d->val;
		dbl64_data_t * d2 = (dbl64_data_t *)curr->prev->data;
		prev_val = d2->val;
		median = (cur_val + prev_val) / 2.0;

	} else { // if odd length
		dbl64_data_t * d = (dbl64_data_t *)curr->data;
		median = d->val;
	}

	SENDD(median);	
}

/*
 Mode - The list of the most frequently occuring number(s).
 - If all numbers occur the same number of time, the list is empty
 - Else the list has one or more elements.
*/
void do_dbl_mode(list_t * num_list) {
	uint32_t max_count = 0;
	uint32_t num_with_max_count = 0;
	uint32_t cur_count = 0;
	double cur_val = 0.0;

	// find max_count (max count of any number in the list)
	node_t * curr = get_first_node(num_list);
	while(curr != get_list_tail(num_list)) {
		dbl64_data_t * d = (dbl64_data_t *)curr->data;
		if (cur_val == d->val) { // another val same as cur_val
			cur_count++;
		} else { // new val
			cur_val = d->val;
			cur_count = 1;
		}

		if (cur_count > max_count) {
			max_count = cur_count;
			num_with_max_count = 1;
		} else if (cur_count == max_count) {
			num_with_max_count++;
		}

		curr = curr->next;
	}

	// no mode if all numbers have equal count or the list is empty
	if (max_count <= 1) {
		max_count = 0;
		SENDUI(max_count);
	} else { // have a mode
		SENDUI(num_with_max_count);

		// send values having max_count
		curr = get_first_node(num_list);
		while(curr != get_list_tail(num_list)) {
			dbl64_data_t * d = (dbl64_data_t *)curr->data;
			// yes, this is equality comparison of floats.
			if (cur_val == d->val) { // another val same as cur_val
				cur_count++;
			} else { // new val
				cur_val = d->val;
				cur_count = 1;
			}

			if (cur_count == max_count) {
				SENDD(cur_val);
			}

			curr = curr->next;
		}
	}
}

/*
 Calculate the difference between the min and max values in the list
 num_list is sorted ascending, so it's the difference between the last
 and first elements in the list.
*/
void do_dbl_range(list_t * num_list) {
	node_t * head = get_first_node(num_list);
	node_t * tail = get_last_node(num_list);

	double range = 0.0;
	dbl64_data_t * d1 = (dbl64_data_t *)tail->data;
	range = d1->val;
	dbl64_data_t * d = (dbl64_data_t *)head->data;
	range -= d->val;

	SENDD(range);
}

/*
 Sum of values in the list
*/
void do_dbl_sum(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	double sum = 0.0;
	while(curr != get_list_tail(num_list)) {
		dbl64_data_t * d = (dbl64_data_t *)curr->data;
		sum += d->val;

		curr = curr->next;
	}

	SENDD(sum);
}

/*
 Calculate the product of all double values in the list
 - Expect some -inf/+inf
*/
void do_dbl_product(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	double product = 1.0;
	while(curr != get_list_tail(num_list)) {
		dbl64_data_t * d = (dbl64_data_t *)curr->data;
		product *= d->val;

		curr = curr->next;
	}

	SENDD(product);
}

/*
 Calculate the min of all values in the list
*/
void do_dbl_min(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	double min = 1.7e308;
	while(curr != get_list_tail(num_list)) {
		dbl64_data_t * d = (dbl64_data_t *)curr->data;
		if (d->val < min) {
			min = d->val;
		}

		curr = curr->next;
	}

	SENDD(min);
}

/*
 Calculate the max of all values in the list
*/
void do_dbl_max(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	double max = -1.7e308;
	while(curr != get_list_tail(num_list)) {
		dbl64_data_t * d = (dbl64_data_t *)curr->data;
		if (max < d->val) {
			max = d->val;
		}

		curr = curr->next;
	}

	SENDD(max);	
}

/*
 The list is sorted in ascending order by default during node insertion.
 Send each value back to client in sorted ascending order.
*/
void do_dbl_sort(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	while(curr != get_list_tail(num_list)) {
		dbl64_data_t * d = (dbl64_data_t *)curr->data;
		SENDD(d->val);

		curr = curr->next;
	}
}

/*
 The list is sorted in ascending order by default during node insertion.
 Send each value back to client in sorted descending order.
*/
void do_dbl_rsort(list_t * num_list) {
	node_t * curr = get_last_node(num_list);

	while(curr != get_list_head(num_list)) {
		dbl64_data_t * d = (dbl64_data_t *)curr->data;
		SENDD(d->val);

		curr = curr->prev; // reverse through list
	}
}

/*
 Search the list for odd numbers. Send to the client, first the count
 of odd numbers, then each odd number.
 - In the land of fairies and Oz, even floats can be odd/even!
*/
void do_dbl_odds(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	// determine count and send it.
	uint32_t count = 0;
	int32_t temp = 0;
	while(curr != get_list_tail(num_list)) {
		dbl64_data_t * d = (dbl64_data_t *)curr->data;
		temp = (int32_t)d->val;
		if (temp % 2 != 0) {
			count++;
		}

		curr = curr->next;
	}
	SENDUI(count);

	// send each odd val
	if (count > 0) {

		curr = get_first_node(num_list);
		while(curr != get_list_tail(num_list)) {
			dbl64_data_t * d = (dbl64_data_t *)curr->data;
			temp = (int32_t)d->val;
			if (temp % 2 != 0) {
				SENDD(d->val);
			}

			curr = curr->next;
		}
	}
}

/*
 Search the list of even numbers. Send to the client, first the count
 of even numbers, then each even number.
 - yes, we have a fairy infestation!
*/
void do_dbl_evens(list_t * num_list) {
	node_t * curr = get_first_node(num_list);

	// determine count and send it.
	uint32_t count = 0;
	int32_t temp = 0;
	while(curr != get_list_tail(num_list)) {
		dbl64_data_t * d = (dbl64_data_t *)curr->data;
		temp = (int32_t)d->val;
		if (temp % 2 == 0) {
			count++;
		}

		curr = curr->next;
	}
	SENDUI(count);

	// send each odd val
	if (count > 0) {
		curr = get_first_node(num_list);
		while(curr != get_list_tail(num_list)) {
			dbl64_data_t * d = (dbl64_data_t *)curr->data;
			temp = (int32_t)d->val;
			if (temp % 2 == 0) {
				SENDD(d->val);
			}

			curr = curr->next;
		}
	}
}
