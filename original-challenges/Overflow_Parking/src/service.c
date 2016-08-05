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
#include <libc.h>
#include "malloc.h"
#include "list.h"

#define STARTSTR "INITSTART"
#define DONESTR "done."
#define LOGFMT "LogMessage - Type:@i, Size:@i"
#define RESULTFMT "\nPayments made: @i\nTickets given: @i\nCoupons used: @i\nGross revenue: @i\nOperating costs: @i\nNet revenue: @i\n\n"
#define TICKETPRICE 5

typedef enum {
    ADDTRANS,
    ADDCOUPON,
    STATS,
    LOG,
    FINISH,
} instrtype;

typedef enum {
    PAY,
    ADDTICKET,
    REMOVETICKET,
    USECOUPON,
} cmdtype;

typedef enum {
   INIT,
   LOGMSG,
   RESULTS,
   DONE,
} resptype;

struct parkcmd {
    cmdtype type;
    size_t size;
    char *cmdbuf; //this is cast to various structs 
} typedef parkcmd_t;

struct parkinstr {
    instrtype type;
    parkcmd_t cmd;
} typedef parkinstr_t;

struct parkresp {
    resptype type;
    char resptext[256];
} typedef parkresp_t;

struct parkstats {
    uint32_t payments;
    uint32_t tickets;
    uint32_t coupons;
    uint16_t unknown;
    uint32_t expenses;
    uint32_t paid_fees;
    uint16_t paid_fines;
    uint16_t unpaid_fines;
    uint32_t paid_fines_value;
    uint32_t unpaid_fines_value;
    uint32_t coupon_losses;
    void (*do_stats)(struct parkstats* stats);
} typedef parkstats_t;

struct ticket {
    uint32_t id;
    uint32_t value;
} typedef ticket_t;

struct payment {
    uint32_t id;
    uint32_t value;
} typedef payment_t;

struct ticketpay {
    uint32_t id;
    uint32_t paid;
} typedef ticketpay_t;

struct coupon {
    uint32_t value;
    char cid[128];
} typedef coupon_t;

parkstats_t stats;
parkstats_t *statsp;
struct list parkl;
struct list ticketl;
struct list couponl;
size_t count;

void free_parking(void *node) {
    parkcmd_t *cmd = (parkcmd_t*)node;
    free(cmd->cmdbuf);
    free((char*)cmd-sizeof(instrtype)); //such hack, ow
}

void dontfree(void *node) {
    //stub function to avoid free'ing data that's still in use
}

unsigned char compare_ticket(void *d1, void *d2) {
    ticket_t *t = (ticket_t*)d1;
    uint32_t id = *(uint32_t*)d2;

    return t->id == id;
}

unsigned char compare_coupon(void *d1, void *d2) {
    coupon_t *c = (coupon_t*)d1;
    char *id = (char *)d2;

    return streq(c->cid, id);
}

int send_resp(resptype type, char *txt) {
    parkresp_t resp = {0};

    resp.type = type;
    strcpy(resp.resptext, txt);

    if (!SENDDATA(resp))
        return 1;
    return 0;
}

void do_pay(void *cmd) {
    payment_t *p = (payment_t *)cmd;
    stats.payments++;
    stats.paid_fees += p->value;
    stats.expenses += p->value/2;
}

void do_add_ticket(void *cmd) {
    ticket_t *t = (ticket_t*)cmd;
    stats.tickets++;
    stats.expenses++;
    if (list_find_node_with_data(&ticketl, compare_ticket, &t->id))
        return;
    list_insert_at_end(&ticketl, t);
    stats.unpaid_fines++;
    stats.unpaid_fines_value += t->value;
}

void do_pay_ticket(void *cmd) {
    ticketpay_t *pay = (ticketpay_t*)cmd;
    struct node* n;
    ticket_t *t;
    stats.paid_fines_value += pay->paid;
    stats.paid_fees += pay->paid;
    stats.unpaid_fines_value -= pay->paid;

    if ((n = list_find_node_with_data(&ticketl, compare_ticket, &pay->id))) {
        t = (ticket_t*)n->data;
        if (t->id == pay->id && t->value <= pay->paid) {
            stats.paid_fines++;
            stats.unpaid_fines--;
            list_remove_node(&ticketl, n);
        }
    }
}

void do_coupon(void *cmd) {
    coupon_t *coupon = (coupon_t*)cmd;
    struct node* n;
    coupon_t *match; 
    stats.coupons++;
    stats.paid_fees += coupon->value;
    
    if ((n = list_find_node_with_data(&couponl, compare_coupon, &coupon->cid))) {
        match = (coupon_t*)n->data;
        stats.coupon_losses -= match->value;
        stats.expenses += match->value;
    }
}

void do_unknown(void *cmd) {
    stats.unknown += 1;
}

void add_to_stats(void *d) {
    parkcmd_t *cmd = (parkcmd_t*)d;
    switch(cmd->type) { 
        case PAY:
            do_pay(cmd->cmdbuf);
            break;
        case ADDTICKET:
            do_add_ticket(cmd->cmdbuf);
            break;
        case REMOVETICKET:
            do_pay_ticket(cmd->cmdbuf);
            break;
        case USECOUPON:
            do_coupon(cmd->cmdbuf);
            break;
        default:
            do_unknown(cmd->cmdbuf);
    }
}

void do_stats(parkstats_t *stats) {
    parkresp_t resp = {0};

    memset(stats, '\0', sizeof(*stats));
    stats->do_stats = do_stats;

    list_init(&ticketl, dontfree);
    list_foreach(&parkl, add_to_stats);
    list_destroy(&ticketl);

    resp.type = RESULTS;
    sprintf(resp.resptext, RESULTFMT, stats->payments, stats->tickets, stats->coupons,
            stats->paid_fees, stats->expenses, stats->paid_fees-stats->expenses);

    if (!SENDDATA(resp))
        _terminate(35);
}

void print_cmd(void *d) {
    parkresp_t resp = {0};
    parkcmd_t *cmd = (parkcmd_t*)d;

    resp.type = LOGMSG;
    sprintf(resp.resptext, LOGFMT, cmd->type, cmd->size);
    if (!SENDDATA(resp))
        _terminate(34);
}


parkinstr_t *read_instr() {
    size_t res;
    parkinstr_t *instr = calloc(sizeof(parkinstr_t));

    if (!instr)
        return NULL;

    res = fread(instr, sizeof(*instr) - sizeof(char*), stdin);
    if (res != sizeof(*instr)-sizeof(char*)) {
        free(instr);
        return NULL;
    }

    if (instr->cmd.size == UINT_MAX || !(instr->cmd.cmdbuf = malloc(instr->cmd.size + 1))) {
        free(instr);
        return NULL;
    }

    int ret = 0;
    if ((ret = fread_until(instr->cmd.cmdbuf, NEWLINE, instr->cmd.size + 1, stdin)) != instr->cmd.size) {
        free(instr->cmd.cmdbuf);
        free(instr);
        return NULL;
    }
    return instr;
}

int main(void) {
    stats.do_stats = do_stats;
    statsp = &stats;
    parkinstr_t *instr;

    list_init(&parkl, free_parking);
    list_init(&couponl, free);

    if (send_resp(INIT,STARTSTR))
        return 1;

    while ((instr = read_instr())) {
        switch(instr->type) {
            case ADDTRANS:
                if (instr->cmd.size < sizeof(ticket_t)) {
                    break;
                }
                list_insert_at_end(&parkl, &instr->cmd);
                break;
            case ADDCOUPON:
                if (instr->cmd.size < sizeof(coupon_t))
                    break;
                *((char*)(instr->cmd.cmdbuf)+sizeof(coupon_t)-1) = '\0';
                list_insert_at_end(&couponl, instr->cmd.cmdbuf);
                free(instr);
                break;
            case STATS:
                //this is silly, but intended to make proving somewhat less difficult
                stats.do_stats(statsp);
                free(instr->cmd.cmdbuf);
                free(instr);
                break;
            case LOG:
                list_foreach(&parkl, print_cmd);
                free(instr->cmd.cmdbuf);
                free(instr);
                break;
            case FINISH:
                free(instr->cmd.cmdbuf);
                free(instr);
                goto done;
        }
    }

    done:
        stats.do_stats(statsp);
        list_destroy(&parkl);
        list_destroy(&couponl);

        if (send_resp(DONE,DONESTR))
            return 1;

        return 0;
}
