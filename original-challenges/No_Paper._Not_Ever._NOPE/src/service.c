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
#include "recv_all.h"
#include "send.h"
#include "memcmp.h"
#include "memcpy.h"

#ifdef DEBUG
#include "sendall.h"
#include "int2str.h"
#endif

#include "comms.h"
#include "taxpayer.h"

typedef struct auditrecord AuditRecord;
struct auditrecord {
    TaxPayer *tp;
    uint16_t tax_years[3];
    AuditRecord *next;
};


const char CREATE_ACCOUNT[8]    =   {'\xa0','\xa1','\xa2','\xa3','\xa0','\xa1','\xa2','\xa3'};
const char LOGIN[8]             =   {'\xbc','\xbc','\xbc','\xbc','\xbc','\xbc','\xbc','\xbc'};
const char LOGOUT[8]            =   {'\xac','\xac','\xac','\xac','\xac','\xac','\xac','\xac'};
const char UPLOAD_FORM[8]       =   {'\xf0','\xf1','\xf2','\xf3','\xf0','\xf1','\xf2','\xf3'};
const char TAXES_DUE[8]         =   {'\xde','\xce','\xde','\xce','\xde','\xce','\xde','\xce'};
const char TAXES_SUBMITTED[8]   =   {'\x50','\x11','\x50','\x11','\x50','\x11','\x50','\x11'};
const char PAY_TAXES[8]         =   {'\xa0','\xce','\xf2','\xce','\xbc','\xac','\xa2','\x11'};
const char GET_REFUND[8]        =   {'\xa0','\xbc','\xa3','\xf2','\xf0','\xde','\xde','\xf1'};

const char TRIGGER_AUDIT[8]     =   {'\xAA','\xAA','\xAA','\xAA','\xAA','\xAA','\xAA','\xAA'};
const char TRIGGER_AUDIT2[8]    =   {'\x00','\x00','\x00','\x00','\x00','\x00','\x00','\x00'};

const char OK[8]                =   {'\xa0','\xa1','\xbc','\xbc','\xac','\xac','\xf0','\xf1'};
const char ERR[8]               =   {'\xa2','\xa3','\x50','\x11','\xde','\xce','\xf2','\xf3'};

const char NICE_TRY[9]              = "NICE_TRY";
const char LOGIN_OK[9]              = "LOGIN_OK";
const char LOGIN_FAIL[11]           = "LOGIN_FAIL";
const char LOGOUT_OK[10]            = "LOGOUT_OK";
const char UPLOAD_OK[10]            = "UPLOAD_OK";
const char UPLOAD_FAIL[12]          = "UPLOAD_FAIL";
const char TAXES_DUE_OK[13]         = "TAXES_DUE_OK";
const char TAXES_DUE_FAIL[15]       = "TAXES_DUE_FAIL";
const char TAXES_SUBMITTED_OK[19]   = "TAXES_SUBMITTED_OK";
const char TAXES_SUBMITTED_FAIL[22] = "TAXES_SUBMITTED_FAIL";
const char PAY_TAXES_OK[13]         = "PAY_TAXES_OK";
const char PAY_TAXES_FAIL[15]       = "PAY_TAXES_FAIL";
const char GET_REFUND_OK[14]        = "GET_REFUND_OK";
const char GET_REFUND_FAIL[16]      = "GET_REFUND_FAIL";
const char YOU_WIN[21]              = "YOU WON A NEW AUDIT!";
const char LUCKY_DAY[11]            = "LUCKY DAY!";
const char AUDIT_FAIL[11]           = "AUDIT_FAIL";


Session *s_list = NULL;
TaxPayer *tp_list = NULL;
AuditRecord *audit_list = NULL;

/**
 * Get a new empty AuditRecord
 *
 * @return Pointer to AuditRecord
 */
AuditRecord *get_new_audit_record(void) {
    AuditRecord *rec = calloc(sizeof(AuditRecord));
    MALLOC_OK(rec);
    return rec;
}

/**
 * Append an audit record to the audit list
 *
 * @param rec       AuditRecord to add to list
 */
void add_auditrecord_to_audit_list(AuditRecord *rec) {
    AuditRecord *tmp = audit_list;
    AuditRecord *prev = audit_list;
    if (NULL == tmp) {
        audit_list = rec;
    } else {
        while (NULL != tmp) {
            prev = tmp;
            tmp = tmp->next;
        }
        prev->next = rec;
    }
}

/**
 * Determine if a taxpayer is already on the audit list
 *
 * @param tp        Pointer to TaxPayer
 * @return TRUE if on list, else FALSE
 */
uint32_t is_taxpayer_scheduled_for_audit(TaxPayer *tp) {
    AuditRecord *tmp = audit_list;

    while (NULL != tmp) {
        if (tp == tmp->tp) {
            return TRUE;
        }

        tmp = tmp->next;
    }

    return FALSE;
}

/**
 * Find up to 3 tax_years to audit for taxpayer and populate audit record
 *
 * @param tp        Pointer to Taxpayer
 * @return Pointer to AuditRecord if taxpayer has at least 1 year of tax forms, else NULL
 */
AuditRecord *find_three_tax_years_for_audit(TaxPayer *tp) {
    AuditRecord *rec = NULL;
    uint32_t tf_count = 0;

    tf_count = taxpayer_count_submitted_tax_years(tp);
    if (0 != tf_count) {
        // have 1 or more tax forms to audit, find last 3
        rec = get_new_audit_record();
        rec->tp = tp;
        tenfourd_get_last_three_from_list(tp->tax_forms, tf_count, rec->tax_years);

        return rec;
    } 

    // have 0 tax forms to audit
    return NULL;
}

/**
 * Trigger this taxpayer for an audit. Today is their lucky day!
 *
 * @param s     Pointer to a Session
 * @param r     Pointer to a Response
 */
int we_have_a_winner(Session *s, Response *r) {
    TaxPayer *tp;
    int ret = SUCCESS;
    int year_count = 0;
    AuditRecord *rec = NULL;

    tp = taxpayer_get_by_username(tp_list, s);
    if ((NULL != tp) && (FALSE == is_taxpayer_scheduled_for_audit(tp))) {
        rec = find_three_tax_years_for_audit(tp);
        if (NULL != rec) {
            rec->tp = tp;
            add_auditrecord_to_audit_list(rec);
            // have 1 or more tax forms to audit YOU WIN
            memcpy(r->answer, YOU_WIN, sizeof(YOU_WIN)-1);
            memcpy(r->answer + sizeof(YOU_WIN)-1, rec->tax_years, sizeof(rec->tax_years));
        } else {
            // have no tax forms to audit, LUCKY DAY!
            memcpy(r->answer, LUCKY_DAY, sizeof(LUCKY_DAY)-1);
        }

        return SUCCESS;
    }

    memcpy(r->answer, AUDIT_FAIL, sizeof(AUDIT_FAIL)-1);
    return -1;
}

/*
 * Receive the data buffer for each command
 *
 * @param s                 Pointer to session which has an element to store the data buffer
 * @param expected_bytes    Number of bytes to read and store in data buffer
 * @return SUCCESS on success, else -1
 */
int recv_cmd_data(Session *s, size_t expected_bytes) {
    if (expected_bytes == s->request.bytes) {
        if (0 < expected_bytes) {
            s->request.data = calloc(expected_bytes);
            MALLOC_OK(s->request.data);

            RECV(s->request.data, expected_bytes);
        }    
        return SUCCESS;
    }

    return -1;
}

/**
 * Authenticate this session
 *
 * @param s     Session to authenticate
 * @param r     Response
 * @return SUCCESS if authenticated, else -1
 */
int session_auth(Session *s, Response *r) {
    Session *s_orig = session_get_by_username(s_list, s);
    if (NULL != s_orig) {
        // validate session data with stored session data (session key and password)
        if ((0 == memcmp(s->login.key, s_orig->login.key, sizeof(s_orig->login.key))) &&
            (0 == memcmp(s->login.password, s_orig->login.password, sizeof(s_orig->login.password)))) {
            return SUCCESS;
        }
    } 
    // starting a new session, no auth

    return -1;
}

/**
 * Set the session key in the response
 *
 * @param s     Pointer to a Session
 * @param r     Pointer to a Response
 */
void response_set_key(Session *s, Response *r) {
    // copy session key to response
    memcpy(r->session_key, s->login.key, sizeof(s->login.key));
}


/**
 * Process the get refund command
 *
 * @param s     Pointer to a Session
 * @param r     Pointer to a Response
 * @return SUCCESS on success, else -1
 */
int get_refund(Session *s, Response *r) {
    TaxPayer *tp;
    int ret = SUCCESS;
    char year_buf[128] = {0}; // 128bytes == 64 tax_years
    size_t bytes_written = sizeof(year_buf) - sizeof(GET_REFUND_OK) - 1;

    tp = taxpayer_get_by_username(tp_list, s);
    if (NULL != tp) {
        ret = taxpayer_get_refund(tp, s, year_buf, &bytes_written);

        if ((SUCCESS == ret) && (bytes_written < (sizeof(year_buf) - sizeof(GET_REFUND_OK) - 1))) {
            memcpy(r->answer, GET_REFUND_OK, sizeof(GET_REFUND_OK)-1);
            memcpy(r->answer + sizeof(GET_REFUND_OK)-1, year_buf, bytes_written);
            return SUCCESS;
        }
    }

    memcpy(r->answer, GET_REFUND_FAIL, sizeof(GET_REFUND_FAIL)-1);
    return -1;
}

/**
 * Process the pay taxes command
 *
 * @param s     Pointer to a Session
 * @param r     Pointer to a Response
 * @return SUCCESS on success, else -1
 */
int pay_taxes(Session *s, Response *r) {
    TaxPayer *tp;
    int ret = SUCCESS;
    char year_buf[128] = {0}; // 128bytes == 64 tax_years
    size_t bytes_written = sizeof(year_buf) - sizeof(PAY_TAXES_OK) - 1;

    ret = recv_cmd_data(s, sizeof(uint32_t));
    if (SUCCESS == ret) {
        tp = taxpayer_get_by_username(tp_list, s);
        if (NULL != tp) {
            ret = taxpayer_pay_taxes(tp, s, year_buf, &bytes_written);

            if ((SUCCESS == ret) && (bytes_written < (sizeof(year_buf) - sizeof(PAY_TAXES_OK) - 1))) {
                memcpy(r->answer, PAY_TAXES_OK, sizeof(PAY_TAXES_OK)-1);
                // VULN: year_buf is 128 and so is r->answer
                // memcpy will go OOB if bytes_written > 128-sizeof(TAXES_SUBMITTED_OK)-1
                // Would that do any harm?
                memcpy(r->answer + sizeof(PAY_TAXES_OK)-1, year_buf, bytes_written);
                return SUCCESS;
            }
        }
    }

    memcpy(r->answer, PAY_TAXES_FAIL, sizeof(PAY_TAXES_FAIL)-1);
    return -1;
}

/**
 * Copy the list of submitted tax years into the Response.answer buffer.
 *
 * @param r             Pointer to a Response
 * @param year_buf      Pointer to buffer of tax years
 * @param bytes_written Number of bytes to copy from year_buf into r.answer
 */
void copy_yr_list_into_answer(Response *r, char *year_buf, size_t bytes_written) {
    memcpy(r->answer, TAXES_SUBMITTED_OK, sizeof(TAXES_SUBMITTED_OK)-1);
    // VULN: year_buf is 128 and so is r->answer
    // memcpy will go OOB if bytes_written > 128-sizeof(TAXES_SUBMITTED_OK)-1
    // Not POV-able because it will write into Session struct which doesn't hurt anything.
    memcpy(r->answer + sizeof(TAXES_SUBMITTED_OK)-1, year_buf, bytes_written);
}

/**
 * Process the taxes submitted command
 *
 * @param s     Pointer to a Session
 * @param r     Pointer to a Response
 * @return SUCCESS on success, else -1
 */
int taxes_submitted(Session *s, Response *r) {
    TaxPayer *tp;
    int ret = SUCCESS;
    copy_yr_fn do_copy = copy_yr_list_into_answer;
    char year_buf[128] = {0}; // 128bytes == 64 tax_years

#ifdef PATCHED_2
    size_t bytes_written = 128-sizeof(TAXES_SUBMITTED_OK)-1;
#else
    size_t bytes_written = 0;
#endif

    ret = recv_cmd_data(s, sizeof(DateRange));
    if (SUCCESS == ret) {
        tp = taxpayer_get_by_username(tp_list, s);
        if (NULL != tp) {
            // VULN: year_buf has no protection from OOB write
            ret = taxpayer_list_submitted_tax_years(tp, s, year_buf, &bytes_written);

            if (SUCCESS == ret) {
                do_copy(r, year_buf, bytes_written);
                return SUCCESS;
            }
        }
    }

    memcpy(r->answer, TAXES_SUBMITTED_FAIL, sizeof(TAXES_SUBMITTED_FAIL)-1);
    return -1;
}

/**
 * Process the taxes due command
 *
 * Taxes due is the sum of the taxes the taxpayer owes (+) or will be refunded (-).
 *
 * @param s     Pointer to a Session
 * @param r     Pointer to a Response
 * @return SUCCESS on success, else -1
 */
int taxes_due(Session *s, Response *r) {
    TaxPayer *tp;
    int ret = SUCCESS;
    int32_t sum = 0;

    ret = recv_cmd_data(s, sizeof(DateRange));
    if (SUCCESS == ret) {
        tp = taxpayer_get_by_username(tp_list, s);
        if (NULL != tp) {
            ret = taxpayer_sum_taxes_due(tp, s, &sum);

            if (SUCCESS == ret) {
                memcpy(r->answer, TAXES_DUE_OK, sizeof(TAXES_DUE_OK)-1);
                memcpy(r->answer + sizeof(TAXES_DUE_OK)-1, &sum, sizeof(int32_t));
                return SUCCESS;
            }
        }
    }

    memcpy(r->answer, TAXES_DUE_FAIL, sizeof(TAXES_DUE_FAIL)-1);
    memcpy(r->answer + sizeof(TAXES_DUE_FAIL)-1, &sum, sizeof(int32_t));
    return -1;
}

/**
 * Process the upload form command
 *
 * @param s     Pointer to a Session
 * @param r     Pointer to a Response
 * @return SUCCESS on success, else -1
 */
int upload_form(Session *s, Response *r) {
    TaxPayer *tp;
    int ret = SUCCESS;
    size_t data_sz = sizeof(TenFourD) - sizeof(uint32_t) - sizeof(char *);

    ret = recv_cmd_data(s, data_sz);
    if (SUCCESS == ret) {
        tp = taxpayer_get_by_username(tp_list, s);
        if (NULL != tp) {
            ret = taxpayer_add_tenfourdee(tp, s, data_sz);

            if (SUCCESS == ret) {
                memcpy(r->answer, UPLOAD_OK, sizeof(UPLOAD_OK)-1);
                return SUCCESS;
            }
        }
    }

#ifdef DEBUG
    const char uf[] = "ERROR: UPLOAD FAILED FOR YEAR: ";

    uint16_t yr = *(uint16_t *)s->request.data;
    uint32_t yr32 = yr;

    char tmp[6] = {0};
    int2str(tmp, sizeof(tmp), yr32);

    sendall(2, uf, sizeof(uf)-1);
    sendall(2, tmp, sizeof(tmp)-1);
    sendall(2, "\n", 1);
#endif

    memcpy(r->answer, UPLOAD_FAIL, sizeof(UPLOAD_FAIL)-1);
    return -1;
}

/**
 * Process the login command
 *
 * @param s     Pointer to a Session
 * @param r     Pointer to a Response
 * @return SUCCESS on success, else -1
 */
int login(Session *s, Response *r) {
    // existing taxpayer
    TaxPayer *tp = taxpayer_get_by_username(tp_list, s);

    if ((NULL != tp) &&
        (SUCCESS == taxpayer_compare_creds(tp, s))) {

        // don't login the same taxpayer multiple times
        Session *s_orig = session_get_by_username(s_list, s);
        if ((NULL != s_orig) &&
            (0 != memcmp(s->login.key, s_orig->login.key, sizeof(s_orig->login.key)))) {
                goto l_fail;
        }

        // save session to s_list
        session_append(&s_list, s);

        // add LOGIN_OK to r->answer to send back to user
        memcpy(r->answer, LOGIN_OK, sizeof(LOGIN_OK)-1);

        return SUCCESS;
    }
l_fail:
    // add LOGIN_FAIL to r->answer to send back to user
    memcpy(r->answer, LOGIN_FAIL, sizeof(LOGIN_FAIL)-1);

    return -1;
}

/**
 * Process the logout command
 *
 * User is already auth'd and has validated session before calling this,
 * so just remove the session and free it.
 *
 * @param s     Pointer to a Session
 * @param r     Pointer to a Response
 * @return SUCCESS on success
 */
int logout(Session *s_cur, Response *r) {
    Session *s = session_remove(&s_list, s_cur);
    if (NULL != s) {
        if (NULL != s->request.data) {
            free(s->request.data);
        }
        free(s);
    }

    // add LOGOUT_OK to r->answer to send back to user
    memcpy(r->answer, LOGOUT_OK, sizeof(LOGOUT_OK)-1);

    return SUCCESS;
}

/**
 * Process the create account command
 *
 * @param s     Pointer to a Session
 * @param r     Pointer to a Response
 * @return SUCCESS on success, else -1
 */
int create_account(Session *s, Response *r) {
    TaxPayer *tp;
    int ret = SUCCESS;

    // get taxpayer.ident
    ret = recv_cmd_data(s, sizeof(Ident));
    if (SUCCESS == ret) {
        tp = taxpayer_get_by_username(tp_list, s);
        if (NULL == tp) {
            taxpayer_new(s, r, &tp_list);
            ret = SUCCESS;
        } else {
            ret = -1;
        }
    }
    return ret;
}


int main(void) {

    int ret = 0;
    size_t bytes = 0;

    while (TRUE) {
        Session s = {0};

        // VULN: r is not zero'd, so will have stale info from prev loop(s)
#ifdef PATCHED_1
        Response r = {0};
#else
        Response r;
#endif        

        RECV(&s, sizeof(Session) - 2*sizeof(char *));

        // auth
        ret = session_auth(&s, &r);

        // process auth'd commands
        if (SUCCESS == ret) {

            if (0 == memcmp(LOGOUT, (const char *)s.request.cmd, sizeof(LOGOUT))) {
                ret = logout(&s, &r);

            } else if (0 == memcmp(UPLOAD_FORM, (const char *)s.request.cmd, sizeof(UPLOAD_FORM))) {
                ret = upload_form(&s, &r);
#ifdef DEBUG
                const char uf[] = "INFO: UPLOAD FORM RET: ";

                char tmp[6] = {0};
                int2str(tmp, sizeof(tmp), ret);

                sendall(2, uf, sizeof(uf)-1);
                sendall(2, tmp, sizeof(tmp)-1);
                sendall(2, "\n", 1);
#endif

            } else if (0 == memcmp(TAXES_DUE, (const char *)s.request.cmd, sizeof(TAXES_DUE))) {
                ret = taxes_due(&s, &r);

            } else if (0 == memcmp(TAXES_SUBMITTED, (const char *)s.request.cmd, sizeof(TAXES_SUBMITTED))) {
                ret = taxes_submitted(&s, &r);

            } else if (0 == memcmp(PAY_TAXES, (const char *)s.request.cmd, sizeof(PAY_TAXES))) {
                ret = pay_taxes(&s, &r);

            } else if (0 == memcmp(GET_REFUND, (const char *)s.request.cmd, sizeof(GET_REFUND))) {
                ret = get_refund(&s, &r);

            } else if (0 == memcmp(TRIGGER_AUDIT, (const char *)s.request.cmd, sizeof(TRIGGER_AUDIT))) {
                ret = we_have_a_winner(&s, &r);

            } else if (0 == memcmp(TRIGGER_AUDIT2, (const char *)s.request.cmd, sizeof(TRIGGER_AUDIT2))) {
                ret = we_have_a_winner(&s, &r);

            } else {
                // add NICE_TRY to r->answer to send back to user
                memcpy(r.answer, NICE_TRY, sizeof(NICE_TRY)-1);
                ret = -1;
            }

        // auth failed, check if cmd is to login
        } else if (0 == memcmp(LOGIN, (const char *)s.request.cmd, sizeof(LOGIN))) {
            ret = login(&s, &r);

        // auth failed, check if cmd is to create account
        } else if (0 == memcmp(CREATE_ACCOUNT, (const char *)s.request.cmd, sizeof(CREATE_ACCOUNT))) {
            ret = create_account(&s, &r);

        // auth failed, not creating account, not login => junk
        } else {
            // add NICE_TRY to r->answer to send back to user
            memcpy(r.answer, NICE_TRY, sizeof(NICE_TRY)-1);
            ret = -1;
        }

        if (0 <= ret) {
            memcpy(r.result, OK, sizeof(OK));
            response_set_key(&s, &r);
        } else {
            memcpy(r.result, ERR, sizeof(ERR));
            // VULN: no setting of Response.key on error, so can get previous session keys if the
            // response isn't initialized to 0's.

#ifdef DEBUG
            const char uf[] = "ERROR: ERR RESULT\n";
            sendall(2, uf, sizeof(uf)-1);
#endif

        }

        // send response
        send((const char *)&r, sizeof(Response));

        if (NULL != s.request.data) {
            free(s.request.data);
        }

    }

    return 0;
}
