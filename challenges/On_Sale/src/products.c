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
#include "cgc_stdint.h"
#include "cgc_libc.h"
#include "cgc_memcmp.h"
#include "cgc_memcpy.h"
#include "cgc_list.h"
#include "cgc_malloc.h"
#include "cgc_string.h"
#include "cgc_recv_until_delim_n.h"

#include "cgc_products.h"
#include "cgc_inventory.h"
#include "cgc_sale.h"

static const char CMD_BUY[4] 			= {'\xBE','\x0E','\xBE','\x0E'};
static const char CMD_CHECK[4] 			= {'\xC4','\xEC','\x4E','\xEE'};
static const char CMD_ADD[4] 			= {'\xAD','\xDD','\xAD','\xDD'};
static const char CMD_RM[4] 			= {'\xDE','\xAD','\xDE','\xAD'};
static const char CMD_UPDATE[4] 		= {'\x04','\xD4','\x7E','\x00'};
static const char CMD_ONSALE[4] 		= {'\x54','\x13','\x54','\x13'};
static const char CMD_NOSALE[4] 		= {'\x0F','\x0F','\x0F','\x0F'};
static const char CMD_LIST[4] 			= {'\x11','\x44','\x11','\x44'};
static const char CMD_QUIT[4]	 		= {'\xFF','\xFF','\xFF','\xFF'};

static const char DESC_TERM[2]			= {'\xED','\0'};
static const char BUY_TERM[4]			= {'\xBB','\xBB','\xBB','\xBB'};
static const char BUY_MORE[4]			= {'\xBD','\xBD','\xBD','\xBD'};

#define PRODUCT_BODY_SIZE (sizeof(Product) - 4)

Inventory inv;
unsigned int cgc_update_serial = 0;

/**
 * Get the next serial number for a product update operation.
 *
 * @return The next update serial number as uint32
 */
static unsigned int cgc_get_next_update_serial(void) {

	unsigned int base = *(unsigned int *)FLAG_PAGE;
	unsigned int next_update_serial = base + cgc_update_serial;
	cgc_update_serial++;

	return next_update_serial;
}

/**
 * Check product for matching barcode.
 *
 * @param product 	Pointer to a Product
 * @param barcode 	Pointer to a Barcode
 * @return TRUE if prod->barcode == bc, else FALSE
 */
static unsigned char cgc_prod_has_bc(const void *product, void *barcode) {
	Product *p = (Product *)product;
	unsigned char *bc = (unsigned char *)barcode;
	if (0 == cgc_memcmp(p->barcode, bc, BARCODE_SZ)) {
		return TRUE;
	}
	return FALSE;
}

/**
 * Search inventory for a product having this barcode.
 *
 * @param bc 	A Barcode
 * @return Pointer to a product or NULL if not found.
 */
static Product *cgc_get_product_by_barcode(char bc[]) {
	struct node *np = NULL;
	np = cgc_list_find_node_with_data(&inv, cgc_prod_has_bc, (void *)bc);
	if (NULL == np) return NULL;
	else return (Product *)np->data;
}

/**
 * Process a purchase of one or more products and return the total cost.
 *
 * @return SUCCESS on success, else -1
 */
static int cgc_do_buy(void) {
	Product *p = NULL;
	Product *p_copy = NULL;
	char buy_status[4];
	char bc[BARCODE_SZ] = {0};
	double cost = 0.0;
	struct list buy_list;

	// create buy list
	cgc_list_init(&buy_list, cgc_free);

	RECV(STDIN, buy_status, sizeof(buy_status));
	// BUG: this loop could be used for memory exhaustion, it has no bound on buy_list.
	while (0 == cgc_memcmp(buy_status, (void *)BUY_MORE, sizeof(BUY_MORE))) {
		// recv barcode
		RECV(STDIN, bc, BARCODE_SZ);

		// find product in inventory with matching bar code
		p = cgc_get_product_by_barcode(bc);

		// if not found, return -1
		if (NULL == p) {
			// clear buy list
			cgc_list_destroy(&buy_list);

			return -1;
		}

		// make copy of product
		p_copy = cgc_malloc(sizeof(Product));
		MALLOC_OK(p_copy);

		cgc_memcpy(p_copy, p, sizeof(Product));

		// add product to buy list		
		cgc_list_insert_at_end(&buy_list, p_copy);

		// add to cost sum
		cost += p_copy->sfn(p_copy->model_num, p_copy->cost);

		// recv buy status
		RECV(STDIN, buy_status, sizeof(buy_status));
	}

	if (0 != cgc_memcmp(buy_status, (void *)BUY_TERM, sizeof(BUY_TERM))) {
		cgc_list_destroy(&buy_list);
		return -1;
	}

	// send total cost
	SEND(STDOUT, (char *)&cost, sizeof(cost));

	// clear buy list
	cgc_list_destroy(&buy_list);

	return SUCCESS;
}

/**
 * Determine the model number, cost, and description of the product 
 *  that is associated with a barcode. If the product is on sale, this 
 *  check will return the sale price. 
 *
 * @return SUCCESS on success, else -1
 */
static int cgc_do_check(void) {
	Product *p = NULL;
	char bc[BARCODE_SZ] = {0};
	float sale_price = 0.0;
	unsigned int d_len = 0;

	// recv barcode
	RECV(STDIN, bc, BARCODE_SZ);

	// find product in inventory with matching bar code
	p = cgc_get_product_by_barcode(bc);

	// if not found, return -1
	if (NULL == p) return -1;

	// if found, send model number, cost, and description
	SEND(STDOUT, (char *)&p->model_num, sizeof(unsigned int));

	sale_price = p->sfn(p->model_num, p->cost);
	SEND(STDOUT, (char *)&sale_price, sizeof(float));

	d_len = cgc_strlen(p->desc, '\0');
	if (0 < d_len)
		SEND(STDOUT, p->desc, d_len);
	// terminate the description string
	SEND(STDOUT, DESC_TERM, 1);

	return SUCCESS;
}

/**
 * Process the addition of one new product to the inventory.
 *
 * @return SUCCESS on success, else -1
 */
static int cgc_do_add(void) {
	Product *p = NULL;
	Product *p2 = NULL;
	int bytes_recvd = 0;

	// create product struct
	p = cgc_malloc(sizeof(Product));
	MALLOC_OK(p);

	// set sfn to not on sale
	p->sfn = onsale_fn[0];
	p->update_serial = 0;

	// recv barcode
	RECV(STDIN, (char *)p->barcode, BARCODE_SZ);

	// if barcode already exists, return -1
	p2 = cgc_get_product_by_barcode((char *)p->barcode);
	if (NULL != p2) {
		cgc_free(p);
		return -1;
	}

	// recv model_num
	RECV(STDIN, (char *)&p->model_num, sizeof(unsigned int));

	// recv cost
	RECV(STDIN, (char *)&p->cost, sizeof(float));

	// recv desc
	// VULN: sizeof(Product) is > MAX_DESC_LEN, so can overflow 24 bytes
	// 	(4 model_num, 4 cost, 4 sfn and 12 heap meta).
#ifdef PATCHED_1
	bytes_recvd = cgc_recv_until_delim_n(STDIN, DESC_TERM[0], (char *)p->desc, MAX_DESC_LEN);
#else
	bytes_recvd = cgc_recv_until_delim_n(STDIN, DESC_TERM[0], (char *)p->desc, sizeof(Product));
#endif
	if (0 >= bytes_recvd) cgc__terminate(ERRNO_RECV);

	// make desc NULL terminated
	p->desc[bytes_recvd - 1] = '\0';

	// add to Inventory
    cgc_list_insert_at_end(&inv, p);

	return SUCCESS;
}

/**
 * Process the removal of one product from the inventory.
 *
 * @return SUCCESS on success, else -1
 */
static int cgc_do_rm(void) {
	Product *p = NULL;
	char bc[BARCODE_SZ] = {0};
	struct node *np = NULL;

	// recv barcode
	RECV(STDIN, bc, BARCODE_SZ);

	// find product in inventory with matching barcode
	np = cgc_list_find_node_with_data(&inv, cgc_prod_has_bc, (void *)bc);
	// if not found, return -1
	if (NULL == np) return -1;

	// delete product from inventory
	cgc_list_remove_node(&inv, np);

	// destroy product
	cgc_list_destroy_node(&inv, &np);

	return SUCCESS;
}

/**
 * Process the update of one product in the inventory.
 *
 * @return SUCCESS on success, else -1
 */
static int cgc_do_update(void) {
	int bytes_recvd = 0;
	Product *p = NULL;
	unsigned int (*desc_copy)(void *dst, const void *src, unsigned int cnt) = cgc_memcpy;
	char bc[BARCODE_SZ] = {0};
	char desc_buf[MAX_DESC_LEN] = {0};

	// recv barcode
	RECV(STDIN, (char *)bc, BARCODE_SZ);

	// if barcode does not exist, return -1
	p = cgc_get_product_by_barcode((char *)bc);
	if (NULL == p) {
		return -1;
	}

	// recv new model_num
	RECV(STDIN, (char *)&p->model_num, sizeof(unsigned int));

	// recv new cost
	RECV(STDIN, (char *)&p->cost, sizeof(float));

	// recv desc
	// VULN: sizeof(Product) is > MAX_DESC_LEN, so can overflow 24 bytes
	//	8 bc, 4 desc_copy, 4 p, 4 bytes_recvd, 4 extra
#ifdef PATCHED_2
	bytes_recvd = cgc_recv_until_delim_n(STDIN, DESC_TERM[0], desc_buf, MAX_DESC_LEN);
#else
	bytes_recvd = cgc_recv_until_delim_n(STDIN, DESC_TERM[0], desc_buf, sizeof(Product));
#endif
	if (0 >= bytes_recvd) cgc__terminate(ERRNO_RECV);

	// make desc NULL terminated
	desc_buf[bytes_recvd - 1] = '\0';

	desc_copy(p->desc, desc_buf, MAX_DESC_LEN);

	p->update_serial = cgc_get_next_update_serial(); // make use of the FLAG_PAGE... just cuz.

	return SUCCESS;
}

/**
 * Process the activation of a sale on one product in the inventory.
 *
 * @return SUCCESS on success, else -1
 */
static int cgc_do_onsale(void) {
	Product *p = NULL;
	char bc[BARCODE_SZ] = {0};
	unsigned int sale_percent = 0;

	// recv barcode
	RECV(STDIN, bc, BARCODE_SZ);

	// find product in inventory with matching bar code
	p = cgc_get_product_by_barcode(bc);

	// if not found, return -1
	if (NULL == p) return -1;

	// get the sale percent (as an int)
	RECV(STDIN, (char *)&sale_percent, sizeof(unsigned int));

	if (100 <= sale_percent) return -1;

	// update product's sale fn ptr
	p->sfn = onsale_fn[sale_percent];
	return SUCCESS;
}

/**
 * Process the de-activation of a sale on one product in the inventory.
 *
 * @return SUCCESS on success, else -1
 */
static int cgc_do_nosale(void) {
	Product *p = NULL;
	char bc[BARCODE_SZ] = {0};
	unsigned int sale_percent = 0;

	// recv barcode
	RECV(STDIN, bc, BARCODE_SZ);

	// find product in inventory with matching bar code
	p = cgc_get_product_by_barcode(bc);

	// if not found, return -1
	if (NULL == p) return -1;

	// update product's sale fn ptr
	p->sfn = onsale_fn[0];

	return SUCCESS;
}

/**
 * Process the listing of all products. Provide more detail depending on selected options.
 *
 * @return SUCCESS on success, else -1
 */
static int cgc_do_list(void) {
	Product *p = NULL;
	char options[4] = {0};
	unsigned int count = cgc_list_length(&inv);
	unsigned int d_len = 0;
	float sale_price = 0.0;
	struct node *cur = cgc_list_head_node(&inv);
	struct node *end = cgc_list_end_marker(&inv);
	// recv options
	RECV(STDIN, options, sizeof(options));

	if (0 == count) return -1;

	// send product info
	while ((NULL != cur) && (cur != end)) {
		p = (Product *)cur->data;

		// send barcode
		SEND(STDOUT, (char *)p->barcode, BARCODE_SZ);

		if (0 == options[0] % 2) {
			// send model_num
			SEND(STDOUT, (char *)&p->model_num, sizeof(unsigned int));
		}
		if (0 != options[1] % 2) {
			// send cost
			SEND(STDOUT, (char *)&p->cost, sizeof(float));
		}
		if (0 == options[2] % 2) {
			// send sale cost
			sale_price = p->sfn(p->model_num, p->cost);
			SEND(STDOUT, (char *)&sale_price, sizeof(float));
		}
		if (0 != options[3] % 2) {
			// send description
			d_len = cgc_strlen(p->desc, '\0');
			if (0 < d_len)
				SEND(STDOUT, p->desc, d_len);
			// terminate the description string
			SEND(STDOUT, DESC_TERM, 1);
		}

		cur = cgc_list_next_node(cur);
	}

	return SUCCESS;
}


void cgc_setup(void) {
	cgc_list_init(&inv, cgc_free);

	cgc_load_inventory(&inv);
}

short cgc_process_cmd(void) {
    char cmd[4];
    short ret = 0;

    RECV(STDIN, cmd, sizeof(cmd));

    if (0 == cgc_memcmp((void *)CMD_BUY, cmd, sizeof(CMD_BUY))) {
    	ret = cgc_do_buy();
    } else if (0 == cgc_memcmp((void *)CMD_CHECK, cmd, sizeof(CMD_CHECK))) {
    	ret = cgc_do_check();
    } else if (0 == cgc_memcmp((void *)CMD_ADD, cmd, sizeof(CMD_ADD))) {
    	ret = cgc_do_add();
    } else if (0 == cgc_memcmp((void *)CMD_RM, cmd, sizeof(CMD_RM))) {
    	ret = cgc_do_rm();
    } else if (0 == cgc_memcmp((void *)CMD_UPDATE, cmd, sizeof(CMD_UPDATE))) {
    	ret = cgc_do_update();
    } else if (0 == cgc_memcmp((void *)CMD_ONSALE, cmd, sizeof(CMD_ONSALE))) {
    	ret = cgc_do_onsale();
    } else if (0 == cgc_memcmp((void *)CMD_NOSALE, cmd, sizeof(CMD_NOSALE))) {
    	ret = cgc_do_nosale();
    } else if (0 == cgc_memcmp((void *)CMD_LIST, cmd, sizeof(CMD_LIST))) {
    	ret = cgc_do_list();
    } else if (0 == cgc_memcmp((void *)CMD_QUIT, cmd, sizeof(CMD_QUIT))) {
    	ret = -2;
    } else {
    	ret = -1;
    }

	return ret;
}
