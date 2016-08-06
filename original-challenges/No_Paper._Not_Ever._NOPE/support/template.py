#!/usr/bin/env python
#
# Copyright (C) 2014 Narf Industries <info@narfindustries.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
from random import choice, randint, sample

import support as sp
from common import DEBUG, CONFIG

class NOPE(object):
    def __init__(self, flag_page):
        self.taxpayers = []
        self.flag_page = flag_page
        self.audits = {}

    def audit_taxpayer(self, audit_record):
        '''
        Add taxpayer to audits
        '''
        self.audits[audit_record.tp.id] = audit_record

    def add_new_taxpayer(self, session, taxpayer):
        '''
        Add new taxpayer to tax_payers and generate their password
        '''
        pwd = ''
        for idx in range(len(taxpayer.password)):
            pwd += chr(ord(session.key[idx]) ^ ord(self.flag_page[ord(session.key[idx])]))

        taxpayer.password = pwd
        self.taxpayers.append(taxpayer)

        return pwd

    def get_taxpayer_by_username(self, username):
        for tp in self.taxpayers:
            if username == tp.username:
                return tp
        return None

    def get_rand_taxpayer(self):
        if 0 == len(self.taxpayers):
            return None

        return sample(self.taxpayers, 1)[0]


class Session(object):
    def __init__(self, key, tax_payer, cmd, data_blob):
        self.key = key
        self.username = tax_payer.username
        self.password = tax_payer.password
        self.cmd = cmd
        self.bytes = len(data_blob)
        self.data = data_blob

    def gen_bytes(self):
        '''
        Generate byte string sent for each session
        '''
        byte_str = ''
        byte_str += sp.pack_single_string(self.key)
        byte_str += sp.pack_single_string(self.username)
        byte_str += sp.pack_single_string(self.password)
        byte_str += sp.pack_single_string(self.cmd)
        byte_str += sp.pack_single_uint16(self.bytes)
        byte_str += self.data
        return byte_str

    def gen_bytes2(self):
        '''
        Generate byte string sent for each session, split into 2 parts, leaving out password
        '''
        byte_str = ''
        byte_str += sp.pack_single_string(self.key)
        byte_str += sp.pack_single_string(self.username)

        byte_str1 = sp.pack_single_string(self.cmd)
        byte_str1 += sp.pack_single_uint16(self.bytes)
        byte_str1 += self.data
        return (byte_str, byte_str1)


    def __str__(self):
        return "Session(key={0},username={1},password={2},cmd={3},bytes={4},data={5})".format(self.key, self.username, self.password, self.cmd, self.bytes, self.data)

    def __repr__(self):
        return self.__str__()

class Response(object):
    def __init__(self, key, answer, result):
        self.s_key = key
        self.answer = answer
        self.result = result

    def gen_bytes(self):
        byte_str = ''
        byte_str += sp.pack_single_string(self.s_key)
        byte_str += sp.pack_single_string(self.answer) + '\0'*(128-len(self.answer))
        byte_str += sp.pack_single_string(self.result)
        return byte_str

    def __str__(self):
        return "Response(s_key={0},answer={1},result={2})".format(self.s_key, self.answer, self.result)

    def __repr__(self):
        return self.__str__()

class AuditRecord(object):
    def __init__(self, taxpayer):
        self.tp = taxpayer
        self.tax_years = self._last_three()

    def _last_three(self):
        tf = self.tp.tax_forms
        yrs = []
        count = len(tf)
        if 0 == count:
            return yrs

        if (3 < count):
            yrs = [tf[-3].tax_year, tf[-2].tax_year, tf[-1].tax_year]

        elif 2 == count:
            yrs = [tf[0].tax_year, tf[1].tax_year]

        else:
            yrs = [tf[0].tax_year]

        return yrs

    def gen_bytes(self):
        '''
        Generate byte string containing tax years
        '''
        byte_str = ''
        for y in self.tax_years:
            byte_str += sp.pack_single_uint16(self.id)

        return byte_str

class TaxPayer(object):
    def __init__(self, p_id, username):
        self.id = p_id
        self.fname = ''
        self.mname = ''
        self.lname = ''
        self.addy = ''
        self.csz = ''
        self.dob = 0
        self.username = username
        self.password = ''
        self.tax_forms = []

    def gen_random_details(self):
        self.fname = sp.random_string(128)
        self.mname = sp.random_string(128)
        self.lname = sp.random_string(128)
        self.addy  = sp.random_string(128)
        self.csz   = sp.random_string(128)
        self.dob   = randint(1, 4000000)
        self.password = '\0'*12

    def gen_new_taxpayer_data_bytes(self):
        '''
        Generate byte string sent to create a new taxpayer.
        '''
        byte_str = ''
        for v in [self.fname, self.mname, self.lname, self.addy, self.csz]:
            byte_str += sp.pack_single_string(v)
        byte_str += sp.pack_single_uint32(self.dob)
        byte_str += sp.pack_single_uint32(self.id)

        return byte_str

    def get_sum_taxes_due(self, start_date, end_date):
        total = 0
        for tf in self.tax_forms:
            if start_date <= tf.tax_year and tf.tax_year <= end_date:
                if 0 == tf.tax_due:
                    total -= tf.tax_refund - tf.tax_paid_refunded
                else:
                    total += tf.tax_due - tf.tax_paid_refunded

        return total

    def get_list_submitted_tax_years(self, start_date, end_date):
        years = []
        total = 0
        for tf in self.tax_forms:
            if start_date <= tf.tax_year and tf.tax_year <= end_date:
                years.append(tf.tax_year)

        return years

    def get_list_pay_taxes(self, dollaz):
        years = []
        total = dollaz
        spent = 0
        for tf in self.tax_forms:
            if 0 == total:
                break

            if 0 != tf.tax_due and tf.tax_paid_refunded < tf.tax_due:
                spent = tf.tax_due - tf.tax_paid_refunded
                if spent > total:
                    spent = total

                tf.tax_paid_refunded += spent
                total -= spent

                years.append(tf.tax_year)

        return years

    def get_list_refund(self):
        years = []
        total = 0
        refund = 0
        for tf in self.tax_forms:
            if 0 != tf.tax_refund and tf.tax_paid_refunded < tf.tax_refund:
                refund = tf.tax_refund - tf.tax_paid_refunded

                tf.tax_paid_refunded += refund
                total += refund

                years.append(tf.tax_year)

        return total, years

    def __eq__(self, other):
        return self.id == other.id

    def __str__(self):
        return "TaxPayer(id={0},fname={1},mname={2},lname={3}\n" \
                "addy={4},csz={5},dob={6},username={7},password={8}" \
                "tax_form_cnt={9},tax_forms={10})". \
                format(self.id, self.fname, self.mname, self.lname, 
                    self.addy, self.csz, self.dob, self.username, self.password, 
                    len(self.tax_forms), [tf.tax_year for tf in self.tax_forms])

    def __repr__(self):
        return self.__str__()

class DateRange(object):
    def __init__(self, start_date=0, end_date=0xffff):
        self.start_date = start_date
        self.end_date = end_date

    def gen_bytes(self):
        byte_str = ''
        byte_str += sp.pack_single_uint16(self.start_date)
        byte_str += sp.pack_single_uint16(self.end_date)
        return byte_str

    def is_valid(self):
        return self.start_date <= self.end_date

    def __str__(self):
        return "DateRange(start={0},end={1})".format(self.start_date, self.end_date)

    def __repr__(self):
        return self.__str__()

class TenFourD(object):
    PARTYS = {"None": 0, "Blue": 1, "Green": 2, "Red": 3, "Purple": 4}

    def __init__(self, taxpayer):
        self.tax_year = randint(1, 65000)

        self.fname = taxpayer.fname
        self.mname = taxpayer.mname
        self.lname = taxpayer.lname
        self.addy = taxpayer.addy
        self.csz = taxpayer.csz
        self.id_num = taxpayer.id

        [to_donate] = choice(['Y', 'N'])
        if 'Y' == to_donate:
            self.donate = to_donate
            self.amount = randint(1,4000)
            self.party = self.PARTYS[sample(self.PARTYS, 1)[0]]
            if self.party == self.PARTYS["None"]:
                self.party += 1
        else:
            self.donate = to_donate
            self.amount = 0
            self.party = self.PARTYS["None"]

        self.wages = randint(10000,400000)
        self.interest = randint(0,50000)
        self.biz_income = randint(0,1000000)
        self.retirement_income = randint(0,50000)

        self.biz_expenses = randint(0,50000)
        self.edu_expenses = randint(0,750000)
        self.self_employ_expenses = randint(0,50000)

        self.edu_credits = randint(0,10000)
        self.child_credits = randint(0,2000)
        self.retirement_credits = randint(0,5000)
        self.home_buyer_credits = randint(0,2000)

        self.tax_withheld = randint(self.wages/4, self.wages/2)
        self.tax_paid_non_taxable_income = randint(0,5000)

        self.digital_signature = ['\0']*24
        self.submission_date = ""
        self.tax_due = 0
        self.tax_refund = 0
        self.tax_paid_refunded = 0

    def __str__(self):
        return "TenFourD(tax_yr={0}\nfn={1}, mn={2}, ln={3}\naddy={4}, csz={5}," \
                "id_num={6}\nwages={7}, int={8}, biz_inc={9}, ret_inc={10}\n" \
                "biz_exp={11}, edu_exp={12}, se_exp={13}\n" \
                "edu_cred={14}, child_cred={15}, ret_cred={16}, home_cred={17}\n" \
                "tax_withheld={18}, tax_paid_non_ti={19}\n" \
                "ds={20}, sub_date={21}, tax_due={22}, tax_refund={23}, tax_pd_ref={24}" \
                ")". \
                format(self.tax_year, self.fname, self.mname, self.lname, self.addy, self.csz,
                self.id_num, self.wages, self.interest, self.biz_income, self.retirement_income,
                self.biz_expenses, self.edu_expenses, self.self_employ_expenses,
                self.edu_credits, self.child_credits, self.retirement_credits, self.home_buyer_credits,
                self.tax_withheld, self.tax_paid_non_taxable_income,
                self.digital_signature, self.submission_date, self.tax_due, self.tax_refund,
                self.tax_paid_refunded)

    def __repr__(self):
        return self.__str__()

    def gen_bytes(self):
        '''
        Generate byte string sent for a TenFourD.
        '''
        byte_str = sp.pack_single_uint16(self.tax_year)
        for v in [self.fname, self.mname, self.lname, self.addy, self.csz]:
            byte_str += sp.pack_single_string(v)
        byte_str += sp.pack_single_uint32(self.id_num)

        byte_str += sp.pack_single_char(self.donate)
        byte_str += sp.pack_single_uint32(self.amount)
        byte_str += sp.pack_single_uint32(self.party)

        byte_str += sp.pack_single_uint32(self.wages)
        byte_str += sp.pack_single_uint32(self.interest)
        byte_str += sp.pack_single_uint32(self.biz_income)
        byte_str += sp.pack_single_uint32(self.retirement_income)

        byte_str += sp.pack_single_uint32(self.biz_expenses)
        byte_str += sp.pack_single_uint32(self.edu_expenses)
        byte_str += sp.pack_single_uint32(self.self_employ_expenses)

        byte_str += sp.pack_single_uint32(self.edu_credits)
        byte_str += sp.pack_single_uint32(self.child_credits)
        byte_str += sp.pack_single_uint32(self.retirement_credits)
        byte_str += sp.pack_single_uint32(self.home_buyer_credits)

        byte_str += sp.pack_single_uint32(self.tax_withheld)
        byte_str += sp.pack_single_uint32(self.tax_paid_non_taxable_income)

        byte_str += sp.pack_single_string(''.join(self.digital_signature))
        byte_str += sp.pack_single_string(self.submission_date)
        byte_str += sp.pack_single_uint32(self.tax_due)
        byte_str += sp.pack_single_uint32(self.tax_refund)

        return byte_str


    def gen_totals_and_ds(self):
        ident = self.id_num
        income = self.wages + self.interest + self.biz_income + self.retirement_income
        expenses = self.biz_expenses + self.edu_expenses + self.self_employ_expenses
        credits = self.edu_credits + self.child_credits + self.retirement_credits + self.home_buyer_credits
        payments = self.tax_withheld + self.tax_paid_non_taxable_income

        base_tax = 12345
        taxable_income = (income >> 3)
        expense_deduction = (expenses >> 4)
        credit_deduction = (credits >> 2)
        total_tax_owed = base_tax + self.amount + taxable_income - expense_deduction - credit_deduction - payments


        # if DEBUG:
        #     print " total_tax_owed: {0} = {1} + {2} + {3} - {4} - {5} - {6}". \
        #         format(total_tax_owed, base_tax, self.amount, taxable_income, expense_deduction, credit_deduction, payments)

        if 0 < total_tax_owed:
            self.tax_due = total_tax_owed
        else:
            self.tax_refund = -total_tax_owed

        l_ident = list(sp.pack_single_uint32(ident))
        l_income = list(sp.pack_single_int64(income))
        l_expenses = list(sp.pack_single_int64(expenses))
        l_credits = list(sp.pack_single_int64(credits))
        l_payments = list(sp.pack_single_int64(payments))

        self.digital_signature[0] = ord(l_ident[0])   ^ ord(self.fname[0])
        self.digital_signature[1] = ord(l_ident[1])   ^ ord(self.mname[0])
        self.digital_signature[2] = ord(l_ident[2])   ^ ord(self.lname[1])
        self.digital_signature[3] = ord(l_ident[3])   ^ ord(self.addy[1])
        self.digital_signature[4] = ord(self.csz[0])  ^ ord(self.fname[1])
        self.digital_signature[5] = ord(self.csz[1])  ^ ord(self.mname[1])
        self.digital_signature[6] = ord(self.csz[2])  ^ ord(self.lname[2])
        self.digital_signature[7] = ord(self.csz[3])  ^ ord(self.addy[2])

        self.digital_signature[4]  ^= ord(l_income[0])
        self.digital_signature[5]  ^= ord(l_income[1])
        self.digital_signature[6]  ^= ord(l_income[2])
        self.digital_signature[7]  ^= ord(l_income[3])
        self.digital_signature[8]  = ord(l_income[4])
        self.digital_signature[9]  = ord(l_income[5])
        self.digital_signature[10] = ord(l_income[6])
        self.digital_signature[11] = ord(l_income[7])

        self.digital_signature[8]  ^= ord(l_expenses[0])
        self.digital_signature[9]  ^= ord(l_expenses[1])
        self.digital_signature[10] ^= ord(l_expenses[2])
        self.digital_signature[11] ^= ord(l_expenses[3])
        self.digital_signature[12] = ord(l_expenses[4])
        self.digital_signature[13] = ord(l_expenses[5])
        self.digital_signature[14] = ord(l_expenses[6])
        self.digital_signature[15] = ord(l_expenses[7])

        self.digital_signature[12] ^= ord(l_credits[0])
        self.digital_signature[13] ^= ord(l_credits[1])
        self.digital_signature[14] ^= ord(l_credits[2])
        self.digital_signature[15] ^= ord(l_credits[3])
        self.digital_signature[16] = ord(l_credits[4])
        self.digital_signature[17] = ord(l_credits[5])
        self.digital_signature[18] = ord(l_credits[6])
        self.digital_signature[19] = ord(l_credits[7])

        self.digital_signature[16] ^= ord(l_payments[0])
        self.digital_signature[17] ^= ord(l_payments[1])
        self.digital_signature[18] ^= ord(l_payments[2])
        self.digital_signature[19] ^= ord(l_payments[3])
        self.digital_signature[20] = ord(l_payments[4]) ^ ord(self.fname[3])
        self.digital_signature[21] = ord(l_payments[5]) ^ ord(self.mname[4])
        self.digital_signature[22] = ord(l_payments[6]) ^ ord(self.lname[5])
        self.digital_signature[23] = ord(l_payments[7]) ^ ord(self.addy[6])

        self.digital_signature = [chr(x) for x in self.digital_signature]

        self.submission_date = sp.random_digits(8)
        while "00000000" == self.submission_date:
            self.submission_date = sp.random_digits(8)

if __name__ == '__main__':

    tp = TaxPayer(1, "fred")
    tp.gen_random_details()
    t4d = TenFourD(tp)
    t4d.gen_totals_and_ds()
    print t4d
