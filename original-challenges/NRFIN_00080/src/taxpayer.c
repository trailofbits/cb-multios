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
#include <stdint.h>
#include <errno.h>
#include "libc.h"
#include "memcmp.h"
#include "memcpy.h"

#ifdef DEBUG
#include "sendall.h"
#include "int2str.h"
#endif


#include "taxpayer.h"

/**
 * Append a taxpayer to the taxpayer list
 *
 * @param tp_list 		Pointer to list of taxpayers
 * @param tp 			Pointer to taxpayer to add
 */
void taxpayer_append(TaxPayer **tp_list, TaxPayer *tp) {
	TaxPayer *tmp = *tp_list;
	TaxPayer *prev = *tp_list;
	if (NULL == tmp) {
		*tp_list = tp;
	} else {
		while (NULL != tmp) {
			prev = tmp;
			tmp = tmp->next;
		}
		prev->next = tp;
	}
}

/**
 * Create a new taxpayer using the data from the Session
 *
 * @param s 		Pointer to session
 * @param r 		Pointer to response
 * @param tp_list 	Pointer to list of taxpayers
 */
void taxpayer_new(Session *s, Response *r, TaxPayer **tp_list) {

	char *fp = (char *)FLAG_PAGE;

	// alloc new tp
	TaxPayer *tp = calloc(sizeof(TaxPayer));
	MALLOC_OK(tp);

	// copy data from s->request->data into tp->ident
	memcpy(&tp->ident, s->request.data, sizeof(Ident));

	// copy username from s->login->username into tp
	memcpy(&tp->auth.username, s->login.username, sizeof(s->login.username));

	// generate pwd into tp->auth->password
	for (uint8_t i = 0; i < sizeof(s->login.key); i++) {
		tp->auth.password[i] = s->login.key[i] ^ fp[(uint8_t)s->login.key[i]];
	}
	// add password to r->answer to send back to user
	memcpy(r->answer, tp->auth.password, sizeof(tp->auth.password));

	// add tp to tp_list
	taxpayer_append(tp_list, tp);
}

/**
 * Find the taxpayer in the taxpayer list with a given username
 *
 * @param tp_list 		Pointer to taxpayer list
 * @param s 			Pointer to session
 * @return Pointer to taxpayer or NULL if not found.
 */
TaxPayer *taxpayer_get_by_username(TaxPayer *tp_list, Session *s) {
    TaxPayer *tp = NULL;
    TaxPayer *tmp = tp_list;
	while (NULL != tmp) {
	    if (0 == memcmp(s->login.username, tmp->auth.username, sizeof(tmp->auth.username))) {
	    	tp = tmp;
			break;
	    }

		tmp = tmp->next;
    }
    return tp;
}

/**
 * Compare the credentials between a given taxpayer and those in a session
 *
 * @param tp 		Pointer to taxpayer
 * @param s 		Pointer to session
 * @return SUCCESS on success, else -1
 */
int taxpayer_compare_creds(TaxPayer *tp, Session *s) {
    if ((0 == memcmp(tp->auth.username, s->login.username, sizeof(s->login.username))) &&
        (0 == memcmp(tp->auth.password, s->login.password, sizeof(s->login.password)))) {
        return SUCCESS;
	}

    return -1;
}

/**
 * Add a TenFourD to a taxpayer
 *
 * @param tp 		Pointer to taxpayer
 * @param s 		Pointer to session
 * @param data_sz 	Amount of data that should be ingested as the TenFourD
 * @return SUCCESS on success, else -1
 */
int taxpayer_add_tenfourdee(TaxPayer *tp, Session *s, size_t data_sz) {

	// parse data to create TenFourD
	TenFourD *t4d = tenfourd_ingest(s, data_sz);
	if (NULL == t4d) {
		return -1;
	}

    // verify TenFourd.ident matches info in taxpayer.ident
    // and verify calculations for tax_due/tax_refund.
    int ret = tenfourd_validate(t4d, tp);
    if (SUCCESS == ret) {
	    // add form to taxpayer
		tenfourd_append(&tp->tax_forms, t4d);
		return SUCCESS;
    }

#ifdef DEBUG
    const char uf[] = "ERROR: INVALID TENFOURD TAXYEAR: ";
    const char c[]  = " ERR CODE: ";

    uint16_t yr = t4d->tax_year;
    uint32_t yr32 = yr;

    char tmp[6] = {0};
    int2str(tmp, sizeof(tmp), yr32);
    char tmp1[6] = {0};
    int2str(tmp1, sizeof(tmp1), ret);

    sendall(2, uf, sizeof(uf)-1);
    sendall(2, tmp, sizeof(tmp)-1);

    sendall(2, c, sizeof(c)-1);
    sendall(2, tmp1, sizeof(tmp1)-1);
    sendall(2, "\n", 1);
#endif
    free (t4d);
	return -1;
}

/**
 * Find the taxpayers TenFourD for a given taxyear
 *
 * @param tp 		Pointer to taxpayer
 * @param tax_year 	Tax year to find
 * @return Pointer to TenFourD if found, else NULL if not.
 */
TenFourD *taxpayer_get_tenfourd_by_taxyear(TaxPayer *tp, uint16_t tax_year) {
	TenFourD *t4d = tp->tax_forms;
	while (NULL != t4d) {
		if (tax_year == t4d->tax_year) return t4d;
		t4d = t4d->next;
	}

	return NULL;
}

/**
 * Taxes due is the sum of the taxes the taxpayer owes (+) or will be refunded (-)
 * for all tax forms having tax year within the range specified in DateRange.
 *
 * @param tp 	Pointer to TaxPayer
 * @param s 	Pointer to Session
 * @param sum 	Pointer to sum
 * @return SUCCESS on success, else -1
 */
int32_t taxpayer_sum_taxes_due(TaxPayer *tp, Session *s, int32_t *sum) {
	DateRange *tdo = (DateRange *)s->request.data;

	if (tdo->end_date < tdo->start_date) return -1;

	TenFourD *t4d = tp->tax_forms;
	while (NULL != t4d) {
		if ((tdo->start_date <= t4d->tax_year) && (t4d->tax_year <= tdo->end_date)) {
			if (0 == t4d->tax_due) {
				// no tax due, may be refund (negative value for sum)
				*sum -= (t4d->tax_refund - t4d->tax_paid_refunded);
			} else {
				// tax due, no refund (positive value for sum)
				*sum += (t4d->tax_due - t4d->tax_paid_refunded);
			}
		}
		t4d = t4d->next;
	}

	return SUCCESS;
}

/**
 * Create a list of the years in which this taxpayer submitted a TenFourD.
 *
 * "list" meaning a buffer with the year concatenated in order they were received.
 *
 * @param tp 			Pointer to TaxPayer
 * @param s 			Pointer to Session
 * @param year_buf 		Pointer to buffer to store years
 * @param bytes_written Pointer to store number of bytes written to year_buf
 * @return SUCCESS on success, else -1
 */
int32_t taxpayer_list_submitted_tax_years(TaxPayer *tp, Session *s, char *year_buf, size_t *bytes_written) {
	DateRange *tdo = (DateRange *)s->request.data;

	if (tdo->end_date < tdo->start_date) {

#ifdef DEBUG
	    const char uf[] = "ERROR: END DATE AFTER START DATE\n";
	    sendall(2, uf, sizeof(uf)-1);
#endif

		return -1;
	}

	TenFourD *t4d = tp->tax_forms;
	uint16_t *yb_idx = (uint16_t *)year_buf;
	size_t byte_count = 0;

#ifdef PATCHED_2
	size_t max_bytes = *bytes_written;
	while ((NULL != t4d) && (byte_count < max_bytes-2)) {
#else
	while (NULL != t4d) {
#endif
		// VULN: no protection from overflowing year_buf!!
		if ((tdo->start_date <= t4d->tax_year) && (t4d->tax_year <= tdo->end_date)) {
			*yb_idx++ = t4d->tax_year;
			byte_count += sizeof(uint16_t);

#ifdef DEBUG
		    const char uf[] = "WARNING: ADDED TAXYEAR TO LIST: ";

		    uint16_t yr = t4d->tax_year;
		    uint32_t yr32 = yr;

		    char tmp[6] = {0};
		    int2str(tmp, sizeof(tmp), yr32);

		    sendall(2, uf, sizeof(uf)-1);
		    sendall(2, tmp, sizeof(tmp)-1);
		    sendall(2, "\n", 1);
#endif

		}
		t4d = t4d->next;
	}

	*bytes_written = byte_count;

#ifdef DEBUG
    const char uf[] = "WARNING: ADDED TAXYEARS TO LIST: ";

    uint32_t yr32 = byte_count / 2;

    char tmp[6] = {0};
    int2str(tmp, sizeof(tmp), yr32);

    sendall(2, uf, sizeof(uf)-1);
    sendall(2, tmp, sizeof(tmp)-1);
    sendall(2, "\n", 1);
#endif


	return SUCCESS;
}

/**
 * Count the number of tax years the Taxpayer has submitted a TenFourD
 *
 * @param tp 	Pointer to TaxPayer
 * @return number of tax years >= 0
 */
uint32_t taxpayer_count_submitted_tax_years(TaxPayer *tp) {
	TenFourD *t4d = tp->tax_forms;
	uint32_t yr_count = 0;

	while (NULL != t4d) {
		yr_count++;
		t4d = t4d->next;
	}

	return yr_count;
}

/**
 * Apply funds to all tax years where taxpayer owes money. Record the years that have
 * been updated.
 *
 * "list" meaning a buffer with the year concatenated in order they were received.
 *
 * @param tp 			Pointer to TaxPayer
 * @param s 			Pointer to Session
 * @param year_buf 		Pointer to buffer to store years
 * @param bytes_written Pointer to store number of bytes written to year_buf
 * @return SUCCESS on success, else -1
 */
int32_t taxpayer_get_refund(TaxPayer *tp, Session *s, char *year_buf, size_t *bytes_written) {

	TenFourD *t4d = tp->tax_forms;
	uint16_t *yb_idx = (uint16_t *)year_buf;
	size_t max_bytes = *bytes_written - 4;
	size_t byte_count = 0;
	uint32_t refund = 0;
	uint32_t total_refund = 0;

	// leave 4 bytes for refund amount at start of buffer
	yb_idx++;
	yb_idx++;
	while ((NULL != t4d) && (byte_count < max_bytes-2)) {
		if ((0 != t4d->tax_refund) && (t4d->tax_paid_refunded < t4d->tax_refund)) {
			refund = t4d->tax_refund - t4d->tax_paid_refunded;

			t4d->tax_paid_refunded += refund;
			total_refund += refund;

			*yb_idx++ = t4d->tax_year;
			byte_count += sizeof(uint16_t);
		}
		t4d = t4d->next;
	}

	// didn't owe any taxes
	if (0 == total_refund)
		return -1;

	*(uint32_t *)year_buf = total_refund;
	*bytes_written = byte_count + sizeof(uint32_t);
	return SUCCESS;
}

/**
 * Apply funds to all tax years where taxpayer owes money. Record the years that have
 * been updated.
 *
 * "list" meaning a buffer with the year concatenated in order they were received.
 *
 * @param tp 			Pointer to TaxPayer
 * @param s 			Pointer to Session
 * @param year_buf 		Pointer to buffer to store years
 * @param bytes_written Pointer to store number of bytes written to year_buf
 * @return SUCCESS on success, else -1
 */
int32_t taxpayer_pay_taxes(TaxPayer *tp, Session *s, char *year_buf, size_t *bytes_written) {
	uint32_t dollaz = *(uint32_t *)s->request.data;

	if (0 == dollaz) return -1;

	TenFourD *t4d = tp->tax_forms;
	uint16_t *yb_idx = (uint16_t *)year_buf;
	size_t max_bytes = *bytes_written;
	size_t byte_count = 0;
	uint32_t dollaz_spent = 0;

	while ((NULL != t4d) && (byte_count < max_bytes) & (0 < dollaz)) {
		if ((0 != t4d->tax_due) && (t4d->tax_paid_refunded < t4d->tax_due)) {
			dollaz_spent = t4d->tax_due - t4d->tax_paid_refunded;
			if (dollaz_spent > dollaz) {
				dollaz_spent = dollaz;
			}
			t4d->tax_paid_refunded += dollaz_spent;
			dollaz -= dollaz_spent;

			*yb_idx++ = t4d->tax_year;
			byte_count += sizeof(uint16_t);
		}
		t4d = t4d->next;
	}

	// didn't owe any taxes
	if (0 == dollaz_spent)
		return -1;

	*bytes_written = byte_count;
	return SUCCESS;
}

/**
 * Append a TenFourD to the taxpayers TenFourD list
 *
 * @param t4d_list 	Pointer to list of TenFourD's
 * @param t4d 		TenFourD to append
 */
void tenfourd_append(TenFourD **t4d_list, TenFourD *t4d) {
	TenFourD *tmp = *t4d_list;
	TenFourD *prev = *t4d_list;
	if (NULL == tmp) {
		*t4d_list = t4d;
	} else {
		while (NULL != tmp) {
			prev = tmp;
			tmp = tmp->next;
		}
		prev->next = t4d;
	}
}

/**
 * Get the tax years of the last 3 TenFourD's in the list
 *
 * @param t4d_list 		Pointer of TenFourD's
 * @param list_length	Number of TenFourD's in list
 * @param tax_years 	Buffer to store up to 3 tax years
 */
void tenfourd_get_last_three_from_list(TenFourD *t4d_list, uint32_t list_length, uint16_t tax_years[3]) {

	TenFourD *t4d_p = t4d_list;
	uint32_t idx = 0;
	uint32_t year_count = list_length;

	while (3 < year_count) { // get pointer to 3rd from end
		t4d_p = t4d_p->next;
		year_count--;
	}

	while (idx < year_count) {
		tax_years[idx++] = t4d_p->tax_year;
		t4d_p = t4d_p->next;
	}
}

/**
 * Convert raw session data to a TenFourD
 *
 * @param s 	Pointer to Session
 * @return Pointer to a TenFourD on success, NULL on error.
 */
TenFourD *tenfourd_ingest(Session *s, size_t data_sz) {
	TenFourD *t4d = calloc(sizeof(TenFourD));
	MALLOC_OK(t4d);

	memcpy(t4d, s->request.data, data_sz);

	return t4d;
}

/**
 * Valid the content of the TenFourD with respect to the taxpayer
 *
 * @param t4d 	Pointer to TenFourD
 * @param tp 	Pointer to TaxPayer
 * @return SUCCESS on success, else ERR_CODE (<0)
 */
int tenfourd_validate(TenFourD *t4d, TaxPayer *tp) {
	char digital_signature[24] = {0};
	int32_t ret = 0;

	if (NULL != taxpayer_get_tenfourd_by_taxyear(tp, t4d->tax_year)) {
		ret = -1;
		goto fail_validate;
	}

	// ident
    if ((0 != memcmp(tp->ident.fname, t4d->ident.fname, sizeof(t4d->ident.fname))) ||
        (0 != memcmp(tp->ident.mname, t4d->ident.mname, sizeof(t4d->ident.mname))) ||
        (0 != memcmp(tp->ident.lname, t4d->ident.lname, sizeof(t4d->ident.lname))) ||
        (0 != memcmp(tp->ident.addy,  t4d->ident.addy,  sizeof(t4d->ident.addy)))  ||
        (0 != memcmp(tp->ident.csz,   t4d->ident.csz,   sizeof(t4d->ident.csz)))   ||
        (tp->ident.id_num != t4d->ident.id_num)) {
    	ret = -2;
		goto fail_validate;
	}
	uint32_t ident = tp->ident.id_num;
	char *p_ident = (char *)&ident;
	digital_signature[0] = p_ident[0] ^ t4d->ident.fname[0];
	digital_signature[1] = p_ident[1] ^ t4d->ident.mname[0];
	digital_signature[2] = p_ident[2] ^ t4d->ident.lname[1];
	digital_signature[3] = p_ident[3] ^ t4d->ident.addy[1];
	digital_signature[4] = t4d->ident.csz[0]  ^ t4d->ident.fname[1];
	digital_signature[5] = t4d->ident.csz[1]  ^ t4d->ident.mname[1];
	digital_signature[6] = t4d->ident.csz[2]  ^ t4d->ident.lname[2];
	digital_signature[7] = t4d->ident.csz[3]  ^ t4d->ident.addy[2];

	// funding
	int64_t party_funds = 0;
	if (('N' == t4d->funding.donate) && (0 != t4d->funding.amount)) {
		ret = -3;
		goto fail_validate;
	} else if (('Y' == t4d->funding.donate) && 
				((0 == t4d->funding.amount) ||
			     (NONE == t4d->funding.party) ||
			     (PARTY_COUNT <= t4d->funding.party))) {
		ret = -4;
		goto fail_validate;
	} else {
		party_funds = (int64_t)t4d->funding.amount;
	}

	// income
	int64_t income = 0;
	char *p_income = (char *)&income;

	income += (int64_t)t4d->income.wages;
	income += (int64_t)t4d->income.interest;
	income += (int64_t)t4d->income.biz_income;
	income += (int64_t)t4d->income.retirement_income;

	digital_signature[4]  ^= p_income[0];
	digital_signature[5]  ^= p_income[1];
	digital_signature[6]  ^= p_income[2];
	digital_signature[7]  ^= p_income[3];
	digital_signature[8]  = p_income[4];
	digital_signature[9]  = p_income[5];
	digital_signature[10] = p_income[6];
	digital_signature[11] = p_income[7];

	// expenses
	int64_t expenses = 0;
	char *p_expenses = (char *)&expenses;

	expenses += (int64_t)t4d->expenses.biz_expenses;
	expenses += (int64_t)t4d->expenses.edu_expenses;
	expenses += (int64_t)t4d->expenses.self_employ_expenses;

	digital_signature[8]  ^= p_expenses[0];
	digital_signature[9]  ^= p_expenses[1];
	digital_signature[10] ^= p_expenses[2];
	digital_signature[11] ^= p_expenses[3];
	digital_signature[12] = p_expenses[4];
	digital_signature[13] = p_expenses[5];
	digital_signature[14] = p_expenses[6];
	digital_signature[15] = p_expenses[7];

	// credits
	int64_t credits = 0;
	char *p_credits = (char *)&credits;

	credits += (int64_t)t4d->credits.edu_credits;
	credits += (int64_t)t4d->credits.child_credits;
	credits += (int64_t)t4d->credits.retirement_credits;
	credits += (int64_t)t4d->credits.home_buyer_credits;

	digital_signature[12] ^= p_credits[0];
	digital_signature[13] ^= p_credits[1];
	digital_signature[14] ^= p_credits[2];
	digital_signature[15] ^= p_credits[3];
	digital_signature[16] = p_credits[4];
	digital_signature[17] = p_credits[5];
	digital_signature[18] = p_credits[6];
	digital_signature[19] = p_credits[7];

	// payments
	int64_t payments = 0;
	char *p_payments = (char *)&payments;

	payments += (int64_t)t4d->payments.tax_withheld;
	payments += (int64_t)t4d->payments.tax_paid_non_taxable_income;

	digital_signature[16] ^= p_payments[0];
	digital_signature[17] ^= p_payments[1];
	digital_signature[18] ^= p_payments[2];
	digital_signature[19] ^= p_payments[3];
	digital_signature[20] = p_payments[4] ^ t4d->ident.fname[3];
	digital_signature[21] = p_payments[5] ^ t4d->ident.mname[4];
	digital_signature[22] = p_payments[6] ^ t4d->ident.lname[5];
	digital_signature[23] = p_payments[7] ^ t4d->ident.addy[6];

	if (0 != memcmp(digital_signature, t4d->digital_signature, sizeof(digital_signature)))  {
		ret = -5;
		goto fail_validate;
	}

	uint32_t date = 0;
	for (uint8_t i = 0; i < sizeof(t4d->submission_date); i++) {
		date += t4d->submission_date[i];
	}
	if (0 == date)  {
		ret = -6;
		goto fail_validate;
	}

	// one or both of tax_due and tax_refund should be 0
	if ((0 != t4d->tax_due) && (0 != t4d->tax_refund)) {
		ret = -7;
		goto fail_validate;
	}

	// calculate taxes
	int64_t base_tax = 12345;
	int64_t taxable_income = (income >> 3); // 12.5% of income is taxable
	int64_t expense_deduction = (expenses >> 4); // 6% of expenses are deductable
	int64_t credit_deduction = (credits >> 2); // 25% of credits are deductable
	int64_t total_tax_owed = base_tax + party_funds + taxable_income - expense_deduction - credit_deduction - payments;

	if ((0 < total_tax_owed) && ((int64_t)t4d->tax_due != total_tax_owed)) {
		ret = -8;
		goto fail_validate;
	}
	if ((0 > total_tax_owed) && ((int64_t)t4d->tax_refund != -total_tax_owed)) {
		ret = -9;
		goto fail_validate;
	}
	if ((0 == total_tax_owed) && (0 != t4d->tax_due) && (0 != t4d->tax_refund)) {
		ret = -10;
		goto fail_validate;
	}

	return SUCCESS;

fail_validate:

	return ret;


}


