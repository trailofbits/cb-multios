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

from os.path import dirname, abspath, join

from genpov import OrderUpPoller


HEAD="""<?xml version="1.0" standalone="no" ?>
<!DOCTYPE cfepov SYSTEM "/usr/share/cgc-docs/cfe-pov.dtd">
<cfepov>
<cbid>service</cbid>
<replay>
    <negotiate><type1>
    <ipmask>0xfefefefe</ipmask>
    <regmask>0xfefefefe</regmask>
    <regnum>2</regnum>
    </type1>
    </negotiate>
"""

READ_STAMP="""
    <!-- Read stamp serial which we need to get the TYPE2_VALUE -->"""


FOOT="""

</replay>
</cfepov>
"""

import os
if __name__ == "__main__":
    POV_DIR=os.path.dirname(__file__)
    POV1_PATH=os.path.join(POV_DIR, 'POV_1c.povxml')
    POV2_PATH=os.path.join(POV_DIR, 'POV_1c.xml')

    tmpl1 = OrderUpPoller()
    tmpl1.start()
    tmpl1.full_meal()
    tmpl1.quit()
    xml_body1  = HEAD.split("\n")
    xml_body1 += tmpl1.xml().split("\n")[5:-2]

    # xml_body1 += READ_STAMP.split("\n")
    # xml_body1 += tmpl1.xml().split("\n")[-9:-6]

    # xml_body1 += READ_STAMP.split("\n")
    # xml_body1 += tmpl1.xml().split("\n")[-6:-2]

    xml_body1 += FOOT.split("\n")
    combined_xml1 = "\n".join(xml_body1)


    # if not os.path.exists(POV_DIR):
    #     os.mkdir(POV_DIR)

    with open(POV1_PATH, 'w') as f:
        f.write(combined_xml1)

    with open(POV2_PATH, 'w') as f:
        f.write(tmpl1.xml())

