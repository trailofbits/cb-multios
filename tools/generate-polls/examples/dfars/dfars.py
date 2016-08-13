#!/usr/bin/env python
#
# Copyright (C) 2014 Brian Caswell <bmc@lungetech.com>
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

from generator.actions import Actions
import copy
import random
import string


def random_alpha(a, b):
    return ''.join(random.choice(string.letters) for _ in range(
        random.randint(a, b)))


def random_string(a, b):
    chars = string.letters + string.digits
    return ''.join(random.choice(chars) for _ in range(random.randint(a, b)))

sections = ['|', '|1|2|', '|1|3|', '|1|4|', '|1|5|', '|1|6|', '|1|7|', '|2|2|',
            '|3|2|', '|3|3|', '|3|4|', '|3|5|', '|3|6|', '|3|7|', '|3|8|',
            '|3|9|', '|3|10|', '|3|11|', '|4|2|', '|4|3|', '|4|4|', '|4|5|',
            '|4|6|', '|4|7|', '|4|8|', '|4|9|', '|4|10|', '|4|11|', '|4|12|',
            '|4|13|', '|4|14|', '|4|15|', '|4|16|', '|5|2|', '|5|3|', '|5|4|',
            '|5|5|', '|5|6|', '|5|7|', '|6|2|', '|6|3|', '|6|4|', '|6|5|',
            '|7|2|', '|7|3|', '|7|4|', '|7|5|', '|8|4|', '|8|5|', '|8|6|',
            '|8|7|', '|8|8|', '|8|11|', '|9|2|', '|9|3|', '|9|4|', '|9|5|',
            '|9|6|', '|9|7|', '|11|2|', '|11|3|', '|11|4|', '|11|5|', '|11|6|',
            '|11|7|', '|11|8|', '|12|2|', '|12|3|', '|12|4|', '|12|5|',
            '|12|6|', '|13|2|', '|13|3|', '|13|4|', '|13|5|', '|14|2|',
            '|14|3|', '|14|4|', '|14|5|', '|15|2|', '|15|3|', '|15|4|',
            '|15|5|', '|15|6|', '|16|2|', '|16|3|', '|16|4|', '|16|5|',
            '|16|6|', '|16|7|', '|17|2|', '|17|4|', '|17|5|', '|17|6|',
            '|17|7|', '|18|2|', '|19|2|', '|19|3|', '|19|4|', '|19|5|',
            '|19|6|', '|19|7|', '|19|8|', '|19|11|', '|19|12|', '|19|13|',
            '|19|14|', '|19|15|', '|22|2|', '|22|3|', '|22|4|', '|22|6|',
            '|22|8|', '|22|9|', '|22|10|', '|22|11|', '|22|12|', '|22|14|',
            '|22|15|', '|22|16|', '|22|17|', '|22|18|', '|23|10|', '|23|11|']

books = {
    '|': {},
    '|1|2|': {'Administration': ''},
    '|1|3|': {'Agency Acquisition Regulations': ''},
    '|1|4|': {'Deviations from the FAR': ''},
    '|1|5|': {'Agency and Public Participation': ''},
    '|1|6|': {'Career Development, Contracting Authority, and '
              'Responsibilities': ''},
    '|1|7|': {'Determinations and Findings': ''},
    '|2|2|': {'Definitions Clause': ''},
    '|3|2|': {'Contractor Gratuities to Government Personnel': ''},
    '|3|3|': {'Reports of Suspected Antitrust Violations': ''},
    '|3|4|': {'Contingent Fees': ''},
    '|3|5|': {'Other Improper Business Practices': ''},
    '|3|6|': {'Contracts with Government Employees or Organizations Owned '
              'or Controlled by Them': ''},
    '|3|7|': {'Voiding and Rescinding Contracts': ''},
    '|3|8|': {'Limitations on the Payment of Funds to Influence Federal '
              'Transactions': ''},
    '|3|9|': {'Whistleblower Protections for Contractor Employees': ''},
    '|3|10|': {'Contractor Code of Business Ethics and Conduct': ''},
    '|3|11|': {'Preventing Personal Conflicts of Interest for Contractor '
               'Employees Performing Acquisition Functions': ''},
    '|4|2|': {'Contract Distribution': ''},
    '|4|3|': {'Paper Documents': ''},
    '|4|4|': {'Safeguarding Classified Information Within Industry': ''},
    '|4|5|': {'Electronic Commerce in Contracting': ''},
    '|4|6|': {'Contract Reporting': ''},
    '|4|7|': {'Contractor Records Retention': ''},
    '|4|8|': {'Government Contract Files': ''},
    '|4|9|': {'Taxpayer Identification Number Information': ''},
    '|4|10|': {'Contract Line Items': ''},
    '|4|11|': {'System for Award Management': ''},
    '|4|12|': {'Representations and Certifications': ''},
    '|4|13|': {'Personal Identity Verification': ''},
    '|4|14|': {'Reporting Executive Compensation and First-Tier Subcontract '
               'Awards': ''},
    '|4|15|': {'American Recovery and Reinvestment Act-Reporting '
               'Requirements': ''},
    '|4|16|': {'Unique Procurement Instrument Identifiers': ''},
    '|5|2|': {'Synopses of Proposed Contract Actions': ''},
    '|5|3|': {'Synopses of Contract Awards': ''},
    '|5|4|': {'Release of Information': ''},
    '|5|5|': {'Paid Advertisements': ''},
    '|5|6|': {'Publicizing Multi-Agency Use Contracts': ''},
    '|5|7|': {'Publicizing Requirements Under the American Recovery and '
              'Reinvestment Act of 2009': ''},
    '|6|2|': {'Full and Open Competition After Exclusion of Sources': ''},
    '|6|3|': {'Other Than Full and Open Competition': ''},
    '|6|4|': {'Sealed Bidding and Competitive Proposals': ''},
    '|6|5|': {'Competition Advocates': ''},
    '|7|2|': {'Planning for the Purchase of Supplies in Economic '
              'Quantities': ''},
    '|7|3|': {'Contractor Versus Government Performance': ''},
    '|7|4|': {'Equipment Lease or Purchase': ''},
    '|7|5|': {'Inherently Governmental Functions': ''},
    '|8|4|': {'Federal Supply Schedules': ''},
    '|8|5|': {'Acquisition of Helium': ''},
    '|8|6|': {'Acquisition from Federal Prison Industries, Inc.': ''},
    '|8|7|': {'Acquisition from Nonprofit Agencies Employing People Who Are '
              'Blind or Severely Disabled': ''},
    '|8|8|': {'Acquisition of Printing and Related Supplies': ''},
    '|8|11|': {'Leasing of Motor Vehicles': ''},
    '|9|2|': {'Qualifications Requirements': ''},
    '|9|3|': {'First Article Testing and Approval': ''},
    '|9|4|': {'Debarment, Suspension, and Ineligibility': ''},
    '|9|5|': {'Organizational and Consultant Conflicts of Interest': ''},
    '|9|6|': {'Contractor Team Arrangements': ''},
    '|9|7|': {'Defense Production Pools and Research and Development '
              'Pools': ''},
    '|11|2|': {'Using and Maintaining Requirements Documents': ''},
    '|11|3|': {'Acceptable Material': ''},
    '|11|4|': {'Delivery or Performance Schedules': ''},
    '|11|5|': {'Liquidated Damages': ''},
    '|11|6|': {'Priorities and Allocations': ''},
    '|11|7|': {'Variation in Quantity': ''},
    '|11|8|': {'Testing': ''},
    '|12|2|': {'Special Requirements for the Acquisition of Commercial '
               'Items': ''},
    '|12|3|': {'Solicitation Provisions and Contract Clauses for the '
               'Acquisition of Commercial Items': ''},
    '|12|4|': {'Unique Requirements Regarding Terms and Conditions for '
               'Commercial Items': ''},
    '|12|5|': {'Applicability of Certain Laws to the Acquisition of '
               'Commercial Items and Commercially Available '
               'Off-The-Shelf Items': ''},
    '|12|6|': {'Streamlined Procedures for Evaluation and Solicitation for '
               'Commercial Items': ''},
    '|13|2|': {'Actions At or Below the Micro-Purchase Threshold': ''},
    '|13|3|': {'Simplified Acquisition Methods': ''},
    '|13|4|': {'Fast Payment Procedure': ''},
    '|13|5|': {'Test Program for Certain Commercial Items': ''},
    '|14|2|': {'Solicitation of Bids': ''},
    '|14|3|': {'Submission of Bids': ''},
    '|14|4|': {'Opening of Bids and Award of Contract': ''},
    '|14|5|': {'Two-Step Sealed Bidding': ''},
    '|15|2|': {'Solicitation and Receipt of Proposals and Information': ''},
    '|15|3|': {'Source Selection': ''},
    '|15|4|': {'Contract Pricing': ''},
    '|15|5|': {'Preaward, Award, and Postaward Notifications, Protests, and '
               'Mistakes': ''},
    '|15|6|': {'Unsolicited Proposals': ''},
    '|16|2|': {'Fixed-Price Contracts': ''},
    '|16|3|': {'Cost-Reimbursement Contracts': ''},
    '|16|4|': {'Incentive Contracts': ''},
    '|16|5|': {'Indefinite-Delivery Contracts': ''},
    '|16|6|': {'Time-and-Materials, Labor-Hour, and Letter Contracts': ''},
    '|16|7|': {'Agreements': ''},
    '|17|2|': {'Options': ''},
    '|17|4|': {'Leader Company Contracting': ''},
    '|17|5|': {'Interagency Acquisitions': ''},
    '|17|6|': {'Management and Operating Contracts': ''},
    '|17|7|': {'Interagency Acquisitions: Acquisitions by Nondefense Agencies '
               'on Behalf of the Department of Defense': ''},
    '|18|2|': {'Emergency Acquisition Flexibilities': ''},
    '|19|2|': {'Policies': ''},
    '|19|3|': {'Determination of Small Business Status for Small Business '
               'Programs': ''},
    '|19|4|': {'Cooperation with the Small Business Administration': ''},
    '|19|5|': {'Set-Asides for Small Business': ''},
    '|19|6|': {'Certificates of Competency and Determinations of '
               'Responsibility': ''},
    '|19|7|': {'The Small Business Subcontracting Program': ''},
    '|19|8|': {'Contracting with the Small Business Administration (The 8(a) '
               'Program)': ''},
    '|19|11|': {'Price Evaluation Adjustment for Small Disadvantaged Business '
                'Concerns': ''},
    '|19|12|': {'Small Disadvantaged Business Participation Program': ''},
    '|19|13|': {'Historically Underutilized Business Zone (HUBZone) '
                'Program': ''},
    '|19|14|': {'Service-Disabled Veteran-Owned Small Business Procurement '
                'Program': ''},
    '|19|15|': {'Women-Owned Small Business (WOSB) Program': ''},
    '|22|2|': {'Convict Labor': ''},
    '|22|3|': {'Contract Work Hours and Safety Standards Act': ''},
    '|22|4|': {'Labor Standards for Contracts Involving Construction': ''},
    '|22|6|': {'Walsh-Healey Public Contracts Act': ''},
    '|22|8|': {'Equal Employment Opportunity': ''},
    '|22|9|': {'Nondiscrimination Because of Age': ''},
    '|22|10|': {'Service Contract Act of 1965, as Amended': ''},
    '|22|11|': {'Professional Employee Compensation': ''},
    '|22|12|': {'Nondisplacement of Qualified Workers Under Service '
                'Contracts': ''},
    '|22|14|': {'Employment of Workers with Disabilities': ''},
    '|22|15|': {'Prohibition of Acquisition of Products Produced by Forced or '
                'Indentured Child Labor': ''},
    '|22|16|': {'Notification of Employee Rights Under the National Labor '
                'Relations Act': ''},
    '|22|17|': {'Combating Trafficking in Persons': ''},
    '|22|18|': {'Employment Eligibility Verification': ''},
    '|23|10|': {'Federal Compliance with Right-to-Know Laws and Pollution '
                'Prevention Requirements': ''},
    '|23|11|': {'Encouraging Contractor Policies to Ban Text Messaging While '
                'Driving': ''},
}


class Dfars(Actions):
    DELIM = '|'
    SEP = '++'

    def start(self):
        self.state['current_dir'] = '|'
        self.state['books'] = copy.deepcopy(books)
        self.state['sections'] = copy.deepcopy(sections)

    def input(self):
        self.read(delim='> ', expect='> ')

    def normalize(self, string):
        dirs = string.split('|')
        out = []

        for item in dirs:
            if item == '++':
                out.pop()
            else:
                out.append(item)

        result = '|'.join(out)
        if result == '':
            result = '|'

        return result

    def ch_sec(self):
        new_dir = ''

        if self.chance(.10):
            new_dir += '++|'
        elif self.chance(.00005):
            dirs = random.choice(self.state['books'].keys()).split('|')[1:-1]
            for i in range(0, random.randint(0, 3)):
                insert_offset = random.randint(0, len(dirs))

                dirs.insert(insert_offset, '++')
                dirs.insert(
                    insert_offset, random_string(1, random.randint(1, 3)))

            new_dir = '|'.join(dirs) + '|'

            if self.chance(.5):
                new_dir = "|" + new_dir
            # print "GOT", new_dir
        else:
            new_dir = random.choice(self.state['books'].keys())
            # print "Changing to %s" % new_dir

        self.write('ch_sec %s\n' % (new_dir))

        if new_dir[0] is not '|':
            new_dir = self.state['current_dir'] + new_dir

        # print "BEFORE", repr(new_dir), repr(self.state)
        new_dir = self.normalize(new_dir)
        # print "GOT", repr(new_dir)
        if new_dir in self.state['books']:
            self.state['current_dir'] = new_dir
        else:
            for book in self.state['books']:
                if book.startswith(new_dir):
                    self.state['current_dir'] = new_dir
                    break
        # print repr(self.state)

    def compress(self):
        if self.chance(.001):
            self.write('compress\n')
            self.read(delim='\n', expect='command failed: compress\n')
            return -1

        if (self.state['current_dir'] in self.state['books'] and len(self.state['books'][self.state['current_dir']]) > 0):
            book = random.choice(
                self.state['books'][self.state['current_dir']].keys()
                )[:39].rstrip()
            self.write('compress %s\n' % book)
            self.read(delim='\n\n', expect=r'%s\n.*\n\n' %
                      book.replace('(', '\\(').replace(')', '\\)'),
                      expect_format='pcre')
        else:
            self.write('compress %s\n' % random_string(5, 25))
            self.read(delim='\n', expect='command failed: compress\n')
            return -1

    def cur_sec(self):
        self.write('cur_sec\n')
        self.read(delim='\n', expect=self.state['current_dir'] + '\n')

    def get(self):
        if self.state['current_dir'] in self.state['books'] and len(self.state['books'][self.state['current_dir']]) > 0:
            book = random.choice(
                self.state['books'][self.state['current_dir']].keys()
                )[:39].rstrip()
            self.write('get %s\n' % book)
            self.read(delim='\n\n', expect=r'%s\n.*\n\n' %
                      book.replace('(', '\\(').replace(')', '\\)'),
                      expect_format='pcre')
        elif self.chance(.01):
            self.write('get\n')
            self.read(delim='\n', expect='command failed: get\n')
            return -1
        else:
            self.write('get %s\n' % random_string(3, random.randint(3, 30)))

    def list(self):
        # print repr(self.state)
        self.write('list\n')
        self.read(delim='\n', expect='current section: %s\n' %
                  self.state['current_dir'])
        if self.state['current_dir'] == '|':
            self.read(delim='\n', expect='\n')

        # this should verify the returned list
        self.read(delim='\n\n')

    def make_sec(self):
        if self.chance(.01):
            self.write('make_sec\n')
            self.read(delim='\n', expect='command failed: make_sec\n')
            return -1

        sec = random_string(3, 10)
        self.write('make_sec %s\n' % sec)

        full_sec = self.state['current_dir'] + sec + '|'
        if full_sec not in self.state['books']:
            self.state['books'][full_sec] = {}
        if full_sec not in sections:
            sections.append(full_sec)

    def put(self):
        if self.chance(.001):
            self.write('put\n')
            return -1

        name = random_string(3, 10)
        data = random_string(10, 20)
        self.write('put %s %s\n' % (name, data))
        if self.state['current_dir'] not in self.state['books']:
            self.state['books'][self.state['current_dir']] = {}
        self.state['books'][self.state['current_dir']][name] = data

    def quit(self):
        self.write('quit\n')
        return -1

    def search(self):
        # this command does not error without an argument, as the others do
        if self.chance(.001):
            self.write('search\n')
            return

        value = ''
        if self.chance(.05):
            value = random_string(5, 30)
        else:
            # this should extract a random string from the dfars entries and
            # verify it
            pass

        self.write('search %s\n' % value)
