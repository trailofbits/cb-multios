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

#ifndef TAXPAYER_H
#define TAXPAYER_H 1

#include <libcgc.h>

#include "comms.h"

typedef enum {NONE, BLUE, GREEN, RED, PURPLE, PARTY_COUNT} PARTY_T;
typedef struct tenfourdee TenFourD;
typedef struct taxpayer TaxPayer;
typedef struct ident Ident;
typedef struct daterange DateRange;

struct tenfourdee {
	uint16_t tax_year;
	struct {
		char fname[128];
		char mname[128];
		char lname[128];
		char addy[128];		// street addy
		char csz[128]; 		// city state zip
		uint32_t id_num;
	} PACKED ident;
	struct {
		uint8_t donate;
		uint32_t amount;
		PARTY_T party;
	} PACKED funding;
	struct {
		uint32_t wages;
		uint32_t interest;
		uint32_t biz_income;
		uint32_t retirement_income;
	} PACKED income;
	struct {
		uint32_t biz_expenses;
		uint32_t edu_expenses;
		uint32_t self_employ_expenses;
	} PACKED expenses;
	struct {
		uint32_t edu_credits;
		uint32_t child_credits;
		uint32_t retirement_credits;
		uint32_t home_buyer_credits;
	} PACKED credits;
	struct {
		uint32_t tax_withheld;
		uint32_t tax_paid_non_taxable_income;
	} PACKED payments;
	char digital_signature[24];
	char submission_date[8];
	uint32_t tax_due;
	uint32_t tax_refund;
	uint32_t tax_paid_refunded;
	TenFourD *next;
} PACKED;

struct ident {
	char fname[128];
	char mname[128];
	char lname[128];
	char addy[128];		// street addy
	char csz[128]; 		// city state zip
	uint32_t dob;
	uint32_t id_num;
} PACKED;

struct taxpayer {
	Ident ident;
	struct {
		char username[12];
		char password[12];
	} PACKED auth;
	TenFourD *tax_forms;
	TaxPayer *next;
} PACKED;

struct daterange {
	uint16_t start_date;
	uint16_t end_date;
};

typedef void (*copy_yr_fn)(Response *, char *, size_t);

void taxpayer_new(Session *s, Response *r, TaxPayer **tp_list);
TaxPayer *taxpayer_get_by_username(TaxPayer *tp_list, Session *s);
int taxpayer_compare_creds(TaxPayer *tp, Session *s);
int taxpayer_add_tenfourdee(TaxPayer *tp, Session *s, size_t data_sz);
int32_t taxpayer_sum_taxes_due(TaxPayer *tp, Session *s, int32_t *sum);
int32_t taxpayer_list_submitted_tax_years(TaxPayer *tp, Session *s, char *year_buf, size_t *bytes_written);
int32_t taxpayer_pay_taxes(TaxPayer *tp, Session *s, char *year_buf, size_t *bytes_written);
int32_t taxpayer_get_refund(TaxPayer *tp, Session *s, char *year_buf, size_t *bytes_written);
uint32_t taxpayer_count_submitted_tax_years(TaxPayer *tp);

void tenfourd_append(TenFourD **t4d_list, TenFourD *t4d);
void tenfourd_get_last_three_from_list(TenFourD *t4d_list, uint32_t list_length, uint16_t tax_years[3]);
int tenfourd_validate(TenFourD *t4d, TaxPayer *tp);
TenFourD *tenfourd_ingest(Session *s, size_t data_sz);

#endif