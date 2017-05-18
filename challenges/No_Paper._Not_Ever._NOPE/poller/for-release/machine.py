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

from generator.actions import Actions, Variable
from random import choice, randint, sample
from os.path import dirname, abspath, join
import sys

sys.path.append(join(dirname(dirname(dirname(abspath(__file__)))), "support"))
import support as sp
from common import DEBUG, CONFIG
from template import NOPE, TaxPayer, Session, Response, TenFourD, DateRange, AuditRecord

class TemplatePoller(Actions):

    CREATE_ACCOUNT    =  '\xa0\xa1\xa2\xa3\xa0\xa1\xa2\xa3'
    LOGIN             =  '\xbc\xbc\xbc\xbc\xbc\xbc\xbc\xbc'
    LOGOUT            =  '\xac\xac\xac\xac\xac\xac\xac\xac'
    UPLOAD_FORM       =  '\xf0\xf1\xf2\xf3\xf0\xf1\xf2\xf3'
    TAXES_DUE         =  '\xde\xce\xde\xce\xde\xce\xde\xce'
    TAXES_SUBMITTED   =  '\x50\x11\x50\x11\x50\x11\x50\x11'
    PAY_TAXES         =  '\xa0\xce\xf2\xce\xbc\xac\xa2\x11'
    GET_REFUND        =  '\xa0\xbc\xa3\xf2\xf0\xde\xde\xf1'

    TRIGGER_AUDIT     =  '\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA'
    TRIGGER_AUDIT2    =  '\x00\x00\x00\x00\x00\x00\x00\x00'


    OK                =  '\xa0\xa1\xbc\xbc\xac\xac\xf0\xf1'
    ERR               =  '\xa2\xa3\x50\x11\xde\xce\xf2\xf3'

    NICE_TRY          = "NICE_TRY"
    LOGIN_OK          = "LOGIN_OK"
    LOGOUT_OK         = "LOGOUT_OK"
    LOGIN_FAIL        = "LOGIN_FAIL"
    UPLOAD_OK         = "UPLOAD_OK"
    UPLOAD_FAIL       = "UPLOAD_FAIL"
    TAXES_DUE_OK      = "TAXES_DUE_OK"
    TAXES_DUE_FAIL    = "TAXES_DUE_FAIL"
    TAXES_SUBMITTED_OK   = "TAXES_SUBMITTED_OK"
    TAXES_SUBMITTED_FAIL = "TAXES_SUBMITTED_FAIL"
    PAY_TAXES_OK      = "PAY_TAXES_OK"
    PAY_TAXES_FAIL    = "PAY_TAXES_FAIL"
    GET_REFUND_OK     = "GET_REFUND_OK"
    GET_REFUND_FAIL   = "GET_REFUND_FAIL"
    YOU_WIN           = "YOU WON A NEW AUDIT!"
    LUCKY_DAY         = "LUCKY DAY!"
    AUDIT_FAIL        = "AUDIT_FAIL"


    def _gen_random_taxpayer(self):
        tp_id = randint(1, 4000000)
        while tp_id in self.state['tids']:
            tp_id = randint(1, 4000000)
        self.state['tids'].add(tp_id)

        tp_username = sp.random_string(12)
        while tp_username in self.state['usernames']:
            tp_username = sp.random_string(12)
        self.state['usernames'].add(tp_username)

        tp = TaxPayer(tp_id, tp_username)
        tp.gen_random_details()
        return tp

    def _get_random_session(self):
        if {} == self.state['sessions']:
            return None

        username = sample(self.state['sessions'], 1)
        return self.state['sessions'][username[0]]

    def start(self):
        #self.delay(100)
        if DEBUG:
            print "------- start -----------"
        self.state['s'] = NOPE(flag_page=self.magic_page)
        self.state['tids'] = set()
        self.state['usernames'] = set()
        self.state['sessions'] = {}

        re = '(.*)'
        self.state['randkey'] = Variable("randkey")
        self.state['randkey'].set_re(re)

    def create_account(self, taxpayer=None):
        '''
        Create a new account
        '''
        if DEBUG:
            print "cmd: create account -----------"

        if True == isinstance(taxpayer, TaxPayer):
            tp = taxpayer
        else:
            tp = self._gen_random_taxpayer()

        s_key = sp.random_string(12)
        s = Session(s_key, tp, self.CREATE_ACCOUNT, tp.gen_new_taxpayer_data_bytes())

        if DEBUG:
            print s
        buf = s.gen_bytes()
        self.write(buf)

        pwd = self.state['s'].add_new_taxpayer(s, tp)
        resp = Response(s.key, pwd, self.OK)
        if DEBUG:
            print resp

        buf = resp.gen_bytes()
        self.read(length=len(buf), expect=buf)

        return 0

    def login(self):
        '''
        Login to establish a session
        '''
        if DEBUG:
            print "cmd: login -----------"

        tp_invalid = False
        tp = self.state['s'].get_rand_taxpayer()
        if False == isinstance(tp, TaxPayer):
            # create invalid taxpayer to trigger fail paths
            tp = self._gen_random_taxpayer()
            tp_invalid = True

        s_key = sp.random_string(12)
        s = Session(s_key, tp, self.LOGIN, "")

        buf = s.gen_bytes()
        self.write(buf)

        res = self.OK
        ans = self.LOGIN_OK
        if tp.username in self.state['sessions']:
            res = self.ERR

            # taxpayer is already logged in
            s_old = self.state['sessions'][tp.username]
            if s_old.key != s.key:
                ans = self.LOGIN_FAIL
            else:
                ans = self.NICE_TRY
        elif True == tp_invalid:
            # taxpayer has not registered or provided invalid creds
            res = self.ERR
            ans = self.LOGIN_FAIL
        else:
            # rock on
            self.state['sessions'][tp.username] = s

        resp = Response(s_key, ans, res)

        if DEBUG:
            print " Username: {0}".format(tp.username)
            print " Response: K:{0}, A:{1}, R:{2} {3}".format(len(resp.s_key), len(resp.answer), len(resp.result), resp)

        buf = resp.gen_bytes()

        if DEBUG:
            print " resp buf: ({0}) {1}".format(len(buf), sp.hexify(buf))
            print "         as text {0}".format(buf)

        if res == self.ERR:
            # cannot match key on ERR conditions, so just read len
            e = buf[:len(resp.s_key)]
            buf = buf[len(resp.s_key):]
            self.read(length=len(e))
            if DEBUG:
                print " read resp.s_key = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

            e = buf[:len(resp.answer)]
            buf = buf[len(resp.answer):]
            self.read(length=len(e), expect=e)
            if DEBUG:
                print " read resp.answer = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

        else:
            e = buf[:len(resp.s_key)+len(resp.answer)]
            buf = buf[len(resp.s_key)+len(resp.answer):]
            self.read(length=len(e), expect=e)
            if DEBUG:
                print " read resp.s_key + resp.answer = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

        # we've read the key and answer, the rest of the answer bytes are
        # junk, so just read len
        e = buf[:-len(resp.result)]
        buf = buf[-len(resp.result):]
        self.read(length=len(e))
        if DEBUG:
            print " read -len(resp.result) = ({0}) {1}".format(len(e), sp.hexify(e))
            print "  new buf {0}".format(sp.hexify(buf))


        self.read(length=len(buf), expect=buf)
        if DEBUG:
            print " read final len(buf) = ({0}) {1}".format(len(buf), sp.hexify(buf))

        return 0

    def logout(self):
        '''
        Logout to end a session
        '''
        if DEBUG:
            print "cmd: logout -----------"

        s_invalid = False
        s = self._get_random_session()

        if None == s:
            # create invalid session to trigger fail paths
            tp = self._gen_random_taxpayer()
            s_key = sp.random_string(12)
            s = Session(s_key, tp, self.LOGOUT, "")
            s_invalid = True
        else:
            s.cmd = self.LOGOUT

        buf = s.gen_bytes()
        self.write(buf)

        res = self.OK
        ans = self.LOGOUT_OK
        if True == s_invalid:
            res = self.ERR
            ans = self.NICE_TRY
        else:
            # remove session
            self.state['sessions'].pop(s.username)

        resp = Response(s.key, ans, res)

        buf = resp.gen_bytes()
        if res == self.ERR:
            # cannot match key on ERR conditions, so trim
            # it and assign it to regex
            self.read(length=len(resp.s_key), assign=self.state['randkey'])
            buf = buf[len(resp.s_key):]
            self.read(length=len(resp.answer), expect=buf[:len(resp.answer)])
            buf = buf[len(resp.answer):]
        else:
            st = buf[:len(resp.s_key)+len(resp.answer)]
            self.read(length=len(st), expect=st)
            buf = buf[len(resp.s_key)+len(resp.answer):]

        # we've read the key and answer, the rest of the answer bytes are
        # junk, so ignore them.
        self.read(length=len(buf)-len(resp.result))
        # read result
        buf = buf[len(buf)-len(resp.result):]
        self.read(length=len(buf), expect=buf)

        return 0

    def upload_form(self):
        '''
        Upload a tax form
        '''
        if DEBUG:
            print "cmd: upload form"

        s_invalid = False
        t4d_invalid = False
        s = self._get_random_session()

        if None == s:
            # create invalid session to trigger fail paths
            tp = self._gen_random_taxpayer()
            t4d = TenFourD(tp)
            t4d.gen_totals_and_ds()

            s_key = sp.random_string(12)
            s = Session(s_key, tp, self.UPLOAD_FORM, "")
            s_invalid = True
        else:
            tp = self.state['s'].get_taxpayer_by_username(s.username)
            t4d = TenFourD(tp)
            t4d.gen_totals_and_ds()
            for t in tp.tax_forms:
                if t.tax_year == t4d.tax_year:
                    t4d_invalid = True
                    break

            s = Session(s.key, tp, self.UPLOAD_FORM, t4d.gen_bytes())

        buf = s.gen_bytes()
        self.write(buf)

        res = self.OK
        ans = self.UPLOAD_OK
        if True == s_invalid:
            res = self.ERR
            ans = self.NICE_TRY
        elif True == t4d_invalid:
            res = self.ERR
            ans = self.UPLOAD_FAIL
        else:
            # add t4d to taxpayer
            tp.tax_forms.append(t4d)

        resp = Response(s.key, ans, res)
        if DEBUG:
            print s
            print tp
            print t4d
            print resp

        buf = resp.gen_bytes()

        if DEBUG:
            print " Username: {0}".format(tp.username)
            print " Response: K:{0}, A:{1}, R:{2} {3}".format(len(resp.s_key), len(resp.answer), len(resp.result), resp)

        buf = resp.gen_bytes()

        if DEBUG:
            print " resp buf: ({0}) {1}".format(len(buf), sp.hexify(buf))
            print "         as text {0}".format(buf)

        if res == self.ERR:
            # cannot match key on ERR conditions, so just read len
            e = buf[:len(resp.s_key)]
            buf = buf[len(resp.s_key):]
            self.read(length=len(e))
            if DEBUG:
                print " read resp.s_key = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

            e = buf[:len(resp.answer)]
            buf = buf[len(resp.answer):]
            self.read(length=len(e), expect=e)
            if DEBUG:
                print " read resp.answer = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

        else:
            e = buf[:len(resp.s_key)+len(resp.answer)]
            buf = buf[len(resp.s_key)+len(resp.answer):]
            self.read(length=len(e), expect=e)
            if DEBUG:
                print " read resp.s_key + resp.answer = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

        # we've read the key and answer, the rest of the answer bytes are
        # junk, so just read len
        e = buf[:-len(resp.result)]
        buf = buf[-len(resp.result):]
        self.read(length=len(e))
        if DEBUG:
            print " read -len(resp.result) = ({0}) {1}".format(len(e), sp.hexify(e))
            print "  new buf {0}".format(sp.hexify(buf))


        self.read(length=len(buf), expect=buf)
        if DEBUG:
            print " read final len(buf) = ({0}) {1}".format(len(buf), sp.hexify(buf))

        return 0

    def taxes_due(self):
        '''
        Determine total amount of tax due (+) or to be refunded (-)
        '''
        if DEBUG:
            print "cmd: taxes due"

        s_invalid = False
        s = self._get_random_session()
        tdo = DateRange(randint(0, 0xfff), randint(0, 0xffff))
        tdo_invalid = False
        sum_due = 0

        if None == s:
            # create invalid session to trigger fail paths
            tp = self._gen_random_taxpayer()

            s_key = sp.random_string(12)
            s = Session(s_key, tp, self.TAXES_DUE, "")
            s_invalid = True
        else:
            tp = self.state['s'].get_taxpayer_by_username(s.username)
            if False == tdo.is_valid():
                tdo_invalid = True
            else:
                sum_due = tp.get_sum_taxes_due(tdo.start_date, tdo.end_date)

            s = Session(s.key, tp, self.TAXES_DUE, tdo.gen_bytes())

        if DEBUG:
            print tdo
            print " sum_due: {0}".format(sum_due)

        buf = s.gen_bytes()
        self.write(buf)

        res = self.OK
        ans = self.TAXES_DUE_OK
        if True == s_invalid:
            res = self.ERR
            ans = self.NICE_TRY
        elif True == tdo_invalid:
            res = self.ERR
            ans = self.TAXES_DUE_FAIL + sp.pack_single_int32(sum_due)
        else:
            ans = self.TAXES_DUE_OK + sp.pack_single_int32(sum_due)

        resp = Response(s.key, ans, res)
        if DEBUG:
            print resp

        buf = resp.gen_bytes()

        if DEBUG:
            print " Username: {0}".format(tp.username)
            print " Response: K:{0}, A:{1}, R:{2} {3}".format(len(resp.s_key), len(resp.answer), len(resp.result), resp)

        buf = resp.gen_bytes()

        if DEBUG:
            print " resp buf: ({0}) {1}".format(len(buf), sp.hexify(buf))
            print "         as text {0}".format(buf)

        if res == self.ERR:
            # cannot match key on ERR conditions, so just read len
            e = buf[:len(resp.s_key)]
            buf = buf[len(resp.s_key):]
            self.read(length=len(e))
            if DEBUG:
                print " read resp.s_key = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

            e = buf[:len(resp.answer)]
            buf = buf[len(resp.answer):]
            self.read(length=len(e), expect=e)
            if DEBUG:
                print " read resp.answer = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

        else:
            e = buf[:len(resp.s_key)+len(resp.answer)]
            buf = buf[len(resp.s_key)+len(resp.answer):]
            self.read(length=len(e), expect=e)
            if DEBUG:
                print " read resp.s_key + resp.answer = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

        # we've read the key and answer, the rest of the answer bytes are
        # junk, so just read len
        e = buf[:-len(resp.result)]
        buf = buf[-len(resp.result):]
        self.read(length=len(e))
        if DEBUG:
            print " read -len(resp.result) = ({0}) {1}".format(len(e), sp.hexify(e))
            print "  new buf {0}".format(sp.hexify(buf))


        self.read(length=len(buf), expect=buf)
        if DEBUG:
            print " read final len(buf) = ({0}) {1}".format(len(buf), sp.hexify(buf))

        return 0


    def taxes_submitted(self):
        '''
        Determine list of years in which a taxpayer submitted a TenFourD
        '''
        if DEBUG:
            print "cmd: taxes submitted"

        s_invalid = False
        s = self._get_random_session()
        tdo = DateRange(randint(0, 0xfff), randint(0, 0xffff))
        tdo_invalid = False
        years = []

        if None == s:
            # create invalid session to trigger fail paths
            tp = self._gen_random_taxpayer()

            s_key = sp.random_string(12)
            s = Session(s_key, tp, self.TAXES_SUBMITTED, "")
            s_invalid = True
        else:
            tp = self.state['s'].get_taxpayer_by_username(s.username)
            if False == tdo.is_valid():
                tdo_invalid = True
            else:
                years = tp.get_list_submitted_tax_years(tdo.start_date, tdo.end_date)

            s = Session(s.key, tp, self.TAXES_SUBMITTED, tdo.gen_bytes())

        if DEBUG:
            print tdo
            print " years: {0}".format(years)

        buf = s.gen_bytes()
        self.write(buf)

        res = self.OK
        ans = self.TAXES_DUE_OK
        if True == s_invalid:
            res = self.ERR
            ans = self.NICE_TRY
        elif True == tdo_invalid:
            res = self.ERR
            ans = self.TAXES_SUBMITTED_FAIL
        else:
            ans = self.TAXES_SUBMITTED_OK + ''.join([sp.pack_single_uint16(y) for y in years])

        resp = Response(s.key, ans, res)
        if DEBUG:
            print resp

        buf = resp.gen_bytes()

        if DEBUG:
            print " Username: {0}".format(tp.username)
            print " Response: K:{0}, A:{1}, R:{2} {3}".format(len(resp.s_key), len(resp.answer), len(resp.result), resp)

        buf = resp.gen_bytes()

        if DEBUG:
            print " resp buf: ({0}) {1}".format(len(buf), sp.hexify(buf))
            print "         as text {0}".format(buf)

        if res == self.ERR:
            # cannot match key on ERR conditions, so just read len
            e = buf[:len(resp.s_key)]
            buf = buf[len(resp.s_key):]
            self.read(length=len(e))
            if DEBUG:
                print " read resp.s_key = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

            e = buf[:len(resp.answer)]
            buf = buf[len(resp.answer):]
            self.read(length=len(e), expect=e)
            if DEBUG:
                print " read resp.answer = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

        else:
            e = buf[:len(resp.s_key)+len(resp.answer)]
            buf = buf[len(resp.s_key)+len(resp.answer):]
            self.read(length=len(e), expect=e)
            if DEBUG:
                print " read resp.s_key + resp.answer = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

        # we've read the key and answer, the rest of the answer bytes are
        # junk, so just read len
        e = buf[:-len(resp.result)]
        buf = buf[-len(resp.result):]
        self.read(length=len(e))
        if DEBUG:
            print " read -len(resp.result) = ({0}) {1}".format(len(e), sp.hexify(e))
            print "  new buf {0}".format(sp.hexify(buf))


        self.read(length=len(buf), expect=buf)
        if DEBUG:
            print " read final len(buf) = ({0}) {1}".format(len(buf), sp.hexify(buf))

        return 0

    def pay_taxes(self):
        '''
        Apply some funds to tax debts.
        '''
        if DEBUG:
            print "cmd: pay taxes"

        s_invalid = False
        s = self._get_random_session()
        p_invalid = False
        dollaz = randint(0, 0xffff)
        years = []

        if None == s:
            # create invalid session to trigger fail paths
            tp = self._gen_random_taxpayer()

            s_key = sp.random_string(12)
            s = Session(s_key, tp, self.PAY_TAXES, "")
            s_invalid = True
        else:
            tp = self.state['s'].get_taxpayer_by_username(s.username)
            years = tp.get_list_pay_taxes(dollaz)
            if [] == years:
                p_invalid = True

            s = Session(s.key, tp, self.PAY_TAXES, sp.pack_single_uint32(dollaz))

        if DEBUG:
            print "dollaz {0} years: {1}".format(dollaz, years)

        buf = s.gen_bytes()
        self.write(buf)

        res = self.OK
        ans = self.TAXES_DUE_OK
        if True == s_invalid:
            res = self.ERR
            ans = self.NICE_TRY
        elif True == p_invalid:
            res = self.ERR
            ans = self.PAY_TAXES_FAIL
        else:
            ans = self.PAY_TAXES_OK + ''.join([sp.pack_single_uint16(y) for y in years])

        resp = Response(s.key, ans, res)
        if DEBUG:
            print resp

        buf = resp.gen_bytes()

        if DEBUG:
            print " Username: {0}".format(tp.username)
            print " Response: K:{0}, A:{1}, R:{2} {3}".format(len(resp.s_key), len(resp.answer), len(resp.result), resp)

        buf = resp.gen_bytes()

        if DEBUG:
            print " resp buf: ({0}) {1}".format(len(buf), sp.hexify(buf))
            print "         as text {0}".format(buf)

        if res == self.ERR:
            # cannot match key on ERR conditions, so just read len
            e = buf[:len(resp.s_key)]
            buf = buf[len(resp.s_key):]
            self.read(length=len(e))
            if DEBUG:
                print " read resp.s_key = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

            e = buf[:len(resp.answer)]
            buf = buf[len(resp.answer):]
            self.read(length=len(e), expect=e)
            if DEBUG:
                print " read resp.answer = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

        else:
            e = buf[:len(resp.s_key)+len(resp.answer)]
            buf = buf[len(resp.s_key)+len(resp.answer):]
            self.read(length=len(e), expect=e)
            if DEBUG:
                print " read resp.s_key + resp.answer = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

        # we've read the key and answer, the rest of the answer bytes are
        # junk, so just read len
        e = buf[:-len(resp.result)]
        buf = buf[-len(resp.result):]
        self.read(length=len(e))
        if DEBUG:
            print " read -len(resp.result) = ({0}) {1}".format(len(e), sp.hexify(e))
            print "  new buf {0}".format(sp.hexify(buf))


        self.read(length=len(buf), expect=buf)
        if DEBUG:
            print " read final len(buf) = ({0}) {1}".format(len(buf), sp.hexify(buf))

        return 0

    def get_refund(self):
        '''
        Get tax refund.
        '''
        if DEBUG:
            print "cmd: get refund"

        s_invalid = False
        s = self._get_random_session()
        p_invalid = False
        years = []
        refund = 0

        if None == s:
            # create invalid session to trigger fail paths
            tp = self._gen_random_taxpayer()

            s_key = sp.random_string(12)
            s = Session(s_key, tp, self.GET_REFUND, "")
            s_invalid = True
        else:
            tp = self.state['s'].get_taxpayer_by_username(s.username)
            refund, years = tp.get_list_refund()
            if [] == years:
                p_invalid = True

            s = Session(s.key, tp, self.GET_REFUND, "")

        if DEBUG:
            print "refund {0} years: {1}".format(refund, years)

        buf = s.gen_bytes()
        self.write(buf)

        res = self.OK
        ans = self.TAXES_DUE_OK
        if True == s_invalid:
            res = self.ERR
            ans = self.NICE_TRY
        elif True == p_invalid:
            res = self.ERR
            ans = self.GET_REFUND_FAIL
        else:
            ans = self.GET_REFUND_OK + sp.pack_single_uint32(refund) + ''.join([sp.pack_single_uint16(y) for y in years])

        resp = Response(s.key, ans, res)
        if DEBUG:
            print resp

        buf = resp.gen_bytes()

        if DEBUG:
            print " Username: {0}".format(tp.username)
            print " Response: K:{0}, A:{1}, R:{2} {3}".format(len(resp.s_key), len(resp.answer), len(resp.result), resp)

        buf = resp.gen_bytes()

        if DEBUG:
            print " resp buf: ({0}) {1}".format(len(buf), sp.hexify(buf))
            print "         as text {0}".format(buf)

        if res == self.ERR:
            # cannot match key on ERR conditions, so just read len
            e = buf[:len(resp.s_key)]
            buf = buf[len(resp.s_key):]
            self.read(length=len(e))
            if DEBUG:
                print " read resp.s_key = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

            e = buf[:len(resp.answer)]
            buf = buf[len(resp.answer):]
            self.read(length=len(e), expect=e)
            if DEBUG:
                print " read resp.answer = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

        else:
            e = buf[:len(resp.s_key)+len(resp.answer)]
            buf = buf[len(resp.s_key)+len(resp.answer):]
            self.read(length=len(e), expect=e)
            if DEBUG:
                print " read resp.s_key + resp.answer = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

        # we've read the key and answer, the rest of the answer bytes are
        # junk, so just read len
        e = buf[:-len(resp.result)]
        buf = buf[-len(resp.result):]
        self.read(length=len(e))
        if DEBUG:
            print " read -len(resp.result) = ({0}) {1}".format(len(e), sp.hexify(e))
            print "  new buf {0}".format(sp.hexify(buf))


        self.read(length=len(buf), expect=buf)
        if DEBUG:
            print " read final len(buf) = ({0}) {1}".format(len(buf), sp.hexify(buf))

        return 0


    def get_audited(self):
        '''
        Get audited.
        '''
        if DEBUG:
            print "cmd: get audited"

        s_invalid = False
        s = self._get_random_session()
        a_invalid = False
        cmd = self.TRIGGER_AUDIT
        if self.chance(0.4):
            cmd = self.TRIGGER_AUDIT2

        if None == s:
            # create invalid session to trigger fail paths
            tp = self._gen_random_taxpayer()

            s_key = sp.random_string(12)
            s = Session(s_key, tp, cmd, "")
            s_invalid = True
        else:
            tp = self.state['s'].get_taxpayer_by_username(s.username)
            s = Session(s.key, tp, cmd, "")

        buf = s.gen_bytes()
        self.write(buf)

        ar = AuditRecord(tp)
        if tp.id in self.state['s'].audits:
            a_invalid = True

        res = self.OK
        ans = self.LUCKY_DAY
        if True == s_invalid:
            res = self.ERR
            ans = self.NICE_TRY
        elif True == a_invalid:
            res = self.ERR
            ans = self.AUDIT_FAIL
        elif 0 == len(ar.tax_years):
            ans = self.LUCKY_DAY
        else:
            ans = self.YOU_WIN + ''.join([sp.pack_single_uint16(y) for y in ar.tax_years])
            self.state['s'].audit_taxpayer(ar)

            if DEBUG:
                print "audit years: {0}".format(ar.tax_years)

        resp = Response(s.key, ans, res)
        if DEBUG:
            print resp

        buf = resp.gen_bytes()

        if DEBUG:
            print " Username: {0}".format(tp.username)
            print " Response: K:{0}, A:{1}, R:{2} {3}".format(len(resp.s_key), len(resp.answer), len(resp.result), resp)

        buf = resp.gen_bytes()

        if DEBUG:
            print " resp buf: ({0}) {1}".format(len(buf), sp.hexify(buf))
            print "         as text {0}".format(buf)

        if res == self.ERR:
            # cannot match key on ERR conditions, so just read len
            e = buf[:len(resp.s_key)]
            buf = buf[len(resp.s_key):]
            self.read(length=len(e))
            if DEBUG:
                print " read resp.s_key = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

            e = buf[:len(resp.answer)]
            buf = buf[len(resp.answer):]
            self.read(length=len(e), expect=e)
            if DEBUG:
                print " read resp.answer = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

        else:
            e = buf[:len(resp.s_key)+len(resp.answer)]
            buf = buf[len(resp.s_key)+len(resp.answer):]
            self.read(length=len(e), expect=e)
            if DEBUG:
                print " read resp.s_key + resp.answer = ({0}) {1}".format(len(e), sp.hexify(e))
                print "  new buf {0}".format(sp.hexify(buf))

        # we've read the key and answer, the rest of the answer bytes are
        # junk, so just read len
        e = buf[:-len(resp.result)]
        buf = buf[-len(resp.result):]
        self.read(length=len(e))
        if DEBUG:
            print " read -len(resp.result) = ({0}) {1}".format(len(e), sp.hexify(e))
            print "  new buf {0}".format(sp.hexify(buf))


        self.read(length=len(buf), expect=buf)
        if DEBUG:
            print " read final len(buf) = ({0}) {1}".format(len(buf), sp.hexify(buf))

        return 0


    def full_set(self):

        if self.chance(0.1):
            self.login()
        if self.chance(0.1):
            self.logout()
        if self.chance(0.1):
            self.upload_form()
        if self.chance(0.1):
            self.taxes_due()
        if self.chance(0.1):
            self.taxes_submitted()
        if self.chance(0.1):
            self.pay_taxes()
        if self.chance(0.1):
            self.get_refund()
        if self.chance(0.1):
            self.get_audited()

        for _ in range(randint(25,35)):
            self.create_account()

        for _ in range(randint(5,10)):
            self.login()

        for x in range(randint(2,5)):
            self.upload_form()
            self.taxes_due()
            self.taxes_submitted()
            self.pay_taxes()
            self.get_refund()

            if self.chance(0.3):
                self.get_audited()

            if self.chance(0.5):
                self.logout()

        return 0

    def quit(self):
        '''
        Quit cleanly
        '''
        if DEBUG:
            print "cmd: quit -----------"

        return -1

    def broker(self):
        '''
        Branching node for all nodes
        '''
        return 0
