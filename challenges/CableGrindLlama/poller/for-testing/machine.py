#!/usr/bin/env python
#
# Copyright (C) 2014 
#   Brian Caswell <bmc@lungetech.com>
#   Narf Industries <info@narfindustries.com>
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
import string
import sys
import os

from xml.sax.saxutils import escape
from generator.actions import Actions
from random import choice,random,randint
from struct import *


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

llama = ['process_llamainutilely', 'process_llamaantioxygen', 'process_llamafucate', 'process_llamacyanohydrin', 'process_llamaisonymy', 'process_llamastrawer', 'process_llamacarbonator', 'process_llamapoorness', 'process_llamaundignifiedly', 'process_llamaambulacriform', 'process_llamaJaina', 'process_llamafolliculin', 'process_llamadoldrums', 'process_llamatelodendron', 'process_llamajibi', 'process_llamapycnite', 'process_llamaatophan', 'process_llamaobtrusiveness', 'process_llamachromophotographic', 'process_llamaskewed', 'process_llamapanse', 'process_llamaunacceptable', 'process_llamaPantagruelistic', 'process_llamaAraneiformes', 'process_llamascholasticly', 'process_llamamarket', 'process_llamaforebridge', 'process_llamasporocyst', 'process_llamahalochromy', 'process_llamafluctuate', 'process_llamatrochocephalus', 'process_llamaPlautine', 'process_llamaHoplonemertini', 'process_llamapunaise', 'process_llamanatterjack', 'process_llamascobby', 'process_llamahydropathy', 'process_llamadentary', 'process_llamadenominate', 'process_llamadecoke', 'process_llamadigredience', 'process_llamabetitle', 'process_llamatenebrose', 'process_llamaforgeability', 'process_llamaunderlease', 'process_llamaunquarrelled', 'process_llamasupersympathy', 'process_llamamegasporic', 'process_llamaboll', 'process_llamaonium', 'process_llamaentodermic', 'process_llamapolitician', 'process_llamatopoalgia', 'process_llamaTamilian', 'process_llamasilvicultural', 'process_llamaadulterously', 'process_llamaschoppen', 'process_llamasart', 'process_llamamink', 'process_llamaintracutaneous', 'process_llamafootpad', 'process_llamamyringotomy', 'process_llamasubderivative', 'process_llamaleaflessness', 'process_llamasquatinid', 'process_llamaspaying', 'process_llamaportico', 'process_llamaquavery', 'process_llamagamobium', 'process_llamaateuchus', 'process_llamadebadge', 'process_llamaDonia', 'process_llamadermophyte', 'process_llamacolophonite', 'process_llamadyspneic', 'process_llamafurnishable', 'process_llamacombatable', 'process_llamakirombo', 'process_llamaworshipability', 'process_llamaparmacety', 'process_llamapronephros', 'process_llamasmolt', 'process_llamaJuletta', 'process_llamalutecia', 'process_llamaposit', 'process_llamacarnaptious', 'process_llamaferocity', 'process_llamacoruscant', 'process_llamaaalii', 'process_llamaParthenon', 'process_llamasubtileness', 'process_llamahemostat', 'process_llamadiscretion', 'process_llamamitigate', 'process_llamamachar', 'process_llamafactorization', 'process_llamaantimaterialistic', 'process_llamalowermost', 'process_llamaSoricinae', 'process_llamamononomial']
pollinfo = {'llamainutilely': ([], ['ntohs']), 'llamaantioxygen': (['llamasubtileness', 'llamapunaise', 'llamainutilely'], ['ntohll', 'lv_vuln', 'nextproto_b', 'string', 'letohs', 'byte', 'nextproto_s', 'double', 'letohl', 'float', 'slv', 'float', 'nextproto_b', 'slv_vuln', 'string', 'float', 'ntohll', 'ntohl', 'ntohll', 'nextproto_s', 'float', 'ntohll', 'byte', 'float', 'string_vuln', 'ntohll', 'letohll', 'lv_vuln', 'ntohll', 'nextproto_s', 'lv_vuln', 'ntohs', 'letohll']), 'llamafucate': ([], ['letohs', 'ntohl', 'letohll', 'slv', 'ntohs', 'ntohs', 'slv', 'letohll', 'letohll', 'ntohs', 'byte', 'float', 'ntohs', 'byte', 'float', 'byte', 'ntohs', 'ntohs', 'ntohll', 'double', 'float', 'string_vuln', 'slv_vuln', 'slv', 'string', 'string_vuln', 'letohl', 'lv', 'double']), 'llamacyanohydrin': ([], ['letohs', 'letohll', 'string_vuln', 'ntohl', 'ntohs', 'string_vuln', 'ntohs', 'float', 'ntohl', 'byte', 'lv_vuln', 'float']), 'llamaisonymy': ([], ['ntohll', 'string_vuln', 'float', 'ntohs', 'lv', 'lv_vuln', 'ntohl', 'float', 'byte', 'lv', 'letohll', 'ntohll', 'letohs', 'ntohl', 'double', 'float', 'byte', 'ntohs', 'letohs', 'ntohl', 'string_vuln', 'letohll', 'string', 'byte', 'byte', 'slv_vuln', 'lv_vuln', 'letohl', 'byte', 'lv_vuln', 'string', 'string', 'ntohl', 'letohll', 'letohs', 'ntohs', 'double', 'ntohll']), 'llamastrawer': (['llamamarket'], ['nextproto_b', 'ntohs', 'letohll', 'lv_vuln', 'letohll', 'byte', 'ntohl', 'byte', 'byte', 'nextproto_s', 'lv_vuln', 'letohl', 'slv_vuln', 'letohs', 'nextproto_s', 'ntohl', 'lv', 'nextproto_s', 'string_vuln', 'float', 'lv_vuln', 'nextproto_b', 'float', 'double', 'nextproto_b', 'ntohs']), 'llamacarbonator': ([], ['double', 'float', 'string', 'double', 'byte', 'lv_vuln', 'ntohll', 'double', 'lv', 'ntohll', 'letohs', 'string_vuln', 'double', 'byte', 'float', 'string', 'ntohs', 'double', 'byte', 'double', 'ntohl']), 'llamapoorness': (['llamasubtileness', 'llamaforebridge', 'llamaunquarrelled'], ['nextproto_s', 'letohll', 'ntohs', 'float', 'double', 'ntohs', 'float', 'float', 'letohs', 'ntohs', 'float', 'string']), 'llamaundignifiedly': ([], ['letohl', 'letohs', 'double', 'lv']), 'llamaambulacriform': (['llamamyringotomy', 'llamaskewed'], ['nextproto_b', 'double', 'double', 'letohl', 'ntohs', 'slv', 'nextproto_b', 'string', 'ntohll', 'ntohl', 'float', 'slv', 'ntohll']), 'llamaJaina': (['llamaPantagruelistic', 'llamainutilely'], ['string_vuln', 'ntohs', 'nextproto_s', 'letohl', 'nextproto_s', 'lv_vuln', 'nextproto_b', 'byte', 'slv_vuln', 'string_vuln', 'nextproto_b', 'ntohll', 'slv', 'string_vuln', 'byte', 'string_vuln', 'byte', 'ntohs', 'ntohs', 'string_vuln', 'ntohl', 'slv_vuln', 'nextproto_b', 'nextproto_s', 'nextproto_s', 'ntohll', 'lv']), 'llamafolliculin': ([], ['ntohll', 'slv', 'slv', 'lv', 'letohs', 'string', 'float', 'double', 'double', 'letohl', 'ntohl', 'letohll', 'letohs']), 'llamadoldrums': ([], ['ntohl', 'float', 'letohll', 'letohs', 'ntohs', 'slv', 'lv_vuln', 'double', 'slv_vuln', 'string_vuln', 'letohs', 'letohl', 'slv_vuln', 'letohl', 'ntohs', 'ntohl', 'letohl', 'lv_vuln', 'letohl', 'string_vuln', 'letohl', 'string', 'letohl', 'string_vuln', 'double', 'string_vuln', 'slv', 'slv', 'slv', 'float', 'slv_vuln', 'ntohs', 'byte', 'ntohs', 'string_vuln', 'double']), 'llamatelodendron': ([], ['string', 'lv_vuln', 'double', 'double', 'lv_vuln', 'string', 'byte', 'letohs', 'lv_vuln', 'double', 'lv_vuln', 'lv_vuln', 'lv_vuln', 'slv', 'ntohs', 'ntohll', 'ntohll', 'ntohll', 'letohs', 'float', 'string', 'ntohll', 'double', 'byte', 'ntohl', 'ntohll', 'slv', 'ntohl']), 'llamajibi': (['llamafootpad', 'llamastrawer'], ['lv_vuln', 'float', 'nextproto_s', 'string', 'float', 'ntohll', 'slv_vuln', 'slv_vuln', 'ntohs']), 'llamapycnite': ([], ['slv', 'slv', 'slv_vuln', 'letohll', 'letohl', 'ntohs', 'ntohs', 'slv', 'ntohll', 'letohl', 'slv_vuln', 'letohl', 'letohll', 'lv', 'ntohl', 'ntohll', 'string_vuln', 'lv_vuln']), 'llamaatophan': ([], ['string_vuln', 'string_vuln', 'ntohs', 'letohl', 'lv', 'letohs', 'letohl', 'letohs', 'lv', 'ntohs', 'double', 'ntohll', 'lv_vuln', 'letohll', 'string_vuln', 'slv_vuln', 'string_vuln', 'byte', 'ntohl', 'string', 'letohs', 'ntohs', 'slv', 'lv_vuln', 'byte', 'byte', 'double', 'ntohl', 'float', 'lv', 'letohll', 'double', 'letohl', 'float', 'letohs', 'letohl']), 'llamaobtrusiveness': ([], ['ntohs', 'string', 'ntohl', 'letohl', 'float', 'string', 'letohll', 'ntohs', 'letohl', 'string_vuln', 'lv', 'letohl', 'slv', 'slv_vuln', 'letohll', 'letohl', 'string_vuln', 'ntohs', 'lv_vuln', 'double', 'byte', 'letohl', 'double', 'ntohs', 'string']), 'llamachromophotographic': (['llamaunacceptable', 'llamaisonymy'], ['string', 'string_vuln', 'lv', 'string', 'lv_vuln', 'ntohs', 'slv', 'letohl', 'double', 'string']), 'llamaskewed': ([], ['lv', 'ntohl', 'lv', 'letohs', 'string_vuln', 'ntohll', 'letohll', 'letohs', 'letohll', 'double']), 'llamapanse': ([], ['slv', 'ntohl', 'slv', 'slv_vuln', 'ntohl', 'byte', 'ntohll', 'double', 'slv_vuln', 'letohll', 'float', 'string', 'lv', 'string', 'float']), 'llamaunacceptable': ([], ['lv', 'ntohl', 'lv_vuln', 'letohs', 'lv', 'byte', 'ntohll']), 'llamaPantagruelistic': ([], ['float', 'ntohs', 'byte', 'ntohs', 'slv_vuln', 'letohl', 'float', 'slv_vuln', 'ntohl', 'ntohl', 'slv', 'lv_vuln', 'lv_vuln', 'double', 'lv_vuln', 'letohll', 'letohl', 'double', 'byte', 'lv']), 'llamaAraneiformes': ([], ['ntohs', 'letohs', 'float', 'double', 'slv_vuln', 'double']), 'llamascholasticly': ([], ['lv_vuln', 'string_vuln', 'letohs', 'lv', 'byte', 'letohll', 'letohll', 'letohl', 'slv', 'string', 'ntohll', 'byte', 'letohl', 'slv_vuln', 'letohs', 'slv', 'double', 'letohs', 'slv_vuln', 'ntohll', 'slv_vuln', 'string_vuln', 'string', 'lv', 'string_vuln', 'float', 'string_vuln', 'letohl']), 'llamamarket': (['llamainutilely', 'llamamyringotomy', 'llamaadulterously', 'llamaatophan'], ['lv_vuln', 'letohll', 'ntohll', 'slv_vuln', 'slv_vuln', 'lv', 'ntohs', 'lv', 'slv', 'double', 'slv', 'string_vuln', 'letohl', 'ntohs', 'nextproto_s', 'double', 'ntohl', 'letohl', 'lv_vuln', 'ntohl', 'slv_vuln', 'ntohll', 'string_vuln', 'nextproto_b', 'double', 'string_vuln', 'lv_vuln', 'ntohs', 'lv', 'ntohs', 'string_vuln', 'float', 'lv', 'lv', 'slv', 'lv_vuln', 'string_vuln', 'string_vuln', 'ntohll', 'ntohs', 'slv_vuln', 'string_vuln', 'letohll', 'lv_vuln', 'float', 'float']), 'llamaforebridge': ([], ['string', 'lv_vuln', 'lv', 'letohl', 'letohl', 'string', 'letohs', 'lv_vuln', 'string', 'letohll', 'ntohll', 'string_vuln', 'ntohl', 'letohll', 'letohll', 'slv', 'double', 'float', 'letohs', 'ntohl', 'ntohll', 'double', 'float', 'letohl', 'float', 'string_vuln', 'ntohll', 'letohl', 'lv_vuln', 'ntohll', 'letohl', 'byte', 'letohll', 'lv_vuln', 'slv_vuln']), 'llamasporocyst': ([], ['slv_vuln', 'double', 'letohl', 'string', 'float', 'letohll', 'byte', 'ntohll', 'float', 'string_vuln', 'letohs', 'slv_vuln', 'string', 'ntohl', 'letohll', 'float', 'ntohs', 'string_vuln', 'lv_vuln', 'letohl', 'letohll', 'float', 'ntohl', 'slv', 'string_vuln', 'double']), 'llamahalochromy': ([], ['letohl', 'double', 'slv', 'byte', 'string_vuln', 'lv_vuln', 'letohll', 'string_vuln', 'string', 'slv', 'letohll', 'ntohll', 'ntohll', 'letohs', 'slv', 'letohll', 'ntohll', 'letohll', 'double']), 'llamafluctuate': ([], ['float', 'float', 'lv', 'double', 'letohl', 'lv_vuln', 'ntohl', 'slv', 'letohll', 'slv', 'ntohl', 'byte', 'float', 'string', 'letohll', 'lv_vuln', 'letohl', 'letohll', 'double', 'slv', 'letohl', 'ntohll', 'lv_vuln', 'slv', 'double', 'slv_vuln', 'string_vuln', 'float', 'float', 'ntohll', 'letohll', 'string_vuln', 'letohs', 'string', 'byte', 'lv', 'double', 'ntohs', 'letohl', 'slv', 'float', 'lv']), 'llamatrochocephalus': ([], ['letohl', 'lv', 'double', 'letohll', 'slv_vuln', 'slv', 'ntohl', 'letohll', 'letohll', 'ntohl', 'string_vuln']), 'llamaPlautine': ([], ['ntohl', 'string', 'float', 'lv', 'string_vuln', 'string', 'ntohll', 'lv', 'byte', 'ntohll', 'ntohs', 'letohl', 'lv', 'slv', 'ntohs', 'ntohs', 'string_vuln', 'string_vuln', 'letohll', 'float', 'slv_vuln', 'letohs', 'letohs', 'ntohs', 'slv', 'letohll', 'slv', 'ntohll', 'float', 'letohs', 'slv_vuln', 'slv_vuln']), 'llamaHoplonemertini': ([], ['lv', 'ntohll', 'ntohs']), 'llamapunaise': ([], ['slv', 'lv', 'lv', 'float', 'ntohll', 'slv', 'slv', 'letohs', 'lv_vuln', 'letohll', 'float', 'lv_vuln', 'ntohl', 'byte', 'byte', 'lv_vuln', 'letohll', 'letohl', 'ntohl', 'byte', 'ntohl', 'ntohs']), 'llamanatterjack': (['llamainutilely'], ['letohl', 'letohl', 'float', 'string_vuln', 'ntohll', 'ntohll', 'slv_vuln', 'ntohll', 'slv', 'slv_vuln', 'nextproto_s', 'letohs', 'letohs', 'lv', 'lv', 'nextproto_s']), 'llamascobby': ([], ['lv_vuln', 'letohl', 'string', 'string_vuln', 'ntohs', 'string', 'float', 'lv', 'double', 'lv_vuln', 'letohll', 'string', 'float', 'lv', 'letohl', 'ntohll', 'string_vuln', 'slv', 'slv', 'lv', 'letohs', 'ntohs', 'ntohl', 'letohll', 'letohll', 'slv', 'float', 'letohs', 'letohs', 'float', 'double']), 'llamahydropathy': ([], ['letohl', 'ntohl', 'string', 'letohll', 'ntohl', 'lv', 'float', 'letohs', 'byte', 'lv', 'letohs', 'string', 'lv', 'lv', 'ntohll', 'ntohll', 'slv', 'letohll', 'string_vuln', 'float', 'letohl', 'letohs', 'letohll', 'lv_vuln', 'byte', 'string', 'float', 'letohll', 'ntohs']), 'llamadentary': ([], ['letohs', 'ntohl', 'ntohs', 'string_vuln', 'letohl', 'letohl', 'ntohs', 'lv', 'slv_vuln', 'ntohll', 'lv', 'lv_vuln', 'byte', 'float', 'letohs', 'byte', 'string_vuln']), 'llamadenominate': (['llamadermophyte', 'llamadyspneic'], ['letohl', 'lv', 'slv_vuln', 'ntohs', 'string_vuln', 'slv_vuln', 'letohs', 'nextproto_b', 'float', 'letohll', 'byte', 'double', 'letohll', 'slv', 'slv', 'ntohl', 'letohs', 'slv_vuln', 'letohl', 'float', 'nextproto_b', 'slv_vuln', 'letohll', 'letohs', 'nextproto_b', 'double', 'ntohll', 'nextproto_b', 'double', 'string_vuln', 'ntohl', 'slv_vuln', 'string', 'nextproto_b', 'nextproto_b', 'ntohl', 'slv_vuln', 'float', 'nextproto_b', 'lv', 'nextproto_s']), 'llamadecoke': ([], ['lv', 'letohll', 'ntohl', 'ntohl', 'string', 'letohl', 'string_vuln', 'ntohs', 'lv_vuln', 'byte', 'ntohll', 'lv_vuln', 'byte', 'slv', 'ntohs', 'ntohl', 'ntohll', 'float', 'letohll', 'lv_vuln', 'ntohl', 'ntohll', 'double', 'letohs', 'letohl', 'slv_vuln', 'letohl', 'double', 'lv_vuln', 'string_vuln', 'slv_vuln', 'slv', 'letohs', 'float', 'ntohl', 'ntohll', 'letohl', 'lv_vuln', 'slv', 'byte', 'string_vuln', 'string', 'letohl', 'string', 'slv', 'slv_vuln']), 'llamadigredience': ([], ['string_vuln', 'lv', 'letohs', 'lv_vuln', 'slv', 'letohs', 'string_vuln', 'double', 'string', 'ntohll', 'ntohl', 'ntohs', 'ntohl', 'lv', 'letohs', 'byte', 'string', 'ntohll', 'byte', 'letohl', 'string', 'letohll', 'float', 'ntohll', 'letohl', 'ntohs', 'double', 'slv', 'slv_vuln', 'byte', 'letohs', 'byte', 'lv_vuln', 'string_vuln', 'slv', 'ntohs', 'byte', 'lv_vuln', 'double']), 'llamabetitle': ([], ['ntohs', 'letohll', 'ntohll', 'ntohll', 'string', 'double', 'ntohs']), 'llamatenebrose': (['llamascobby', 'llamaonium'], ['double', 'letohs', 'letohs', 'double', 'letohll', 'nextproto_s', 'lv', 'nextproto_b']), 'llamaforgeability': ([], ['slv_vuln', 'byte', 'letohll', 'letohll', 'string_vuln', 'double', 'ntohll', 'lv', 'slv_vuln', 'ntohs', 'lv_vuln', 'ntohl', 'ntohl', 'ntohll', 'string_vuln', 'string', 'slv_vuln', 'lv_vuln']), 'llamaunderlease': ([], ['letohll', 'double']), 'llamaunquarrelled': ([], ['letohs', 'letohl', 'float', 'ntohl', 'slv_vuln', 'byte', 'lv_vuln', 'lv', 'letohll', 'slv_vuln', 'ntohl']), 'llamasupersympathy': ([], ['ntohs', 'ntohl', 'letohs', 'ntohl', 'slv_vuln', 'letohs', 'ntohll', 'letohl', 'byte', 'double', 'lv', 'ntohll', 'ntohl', 'letohs', 'slv_vuln', 'ntohl', 'ntohs', 'double']), 'llamamegasporic': ([], ['letohll', 'slv', 'float', 'float', 'string', 'byte', 'string_vuln', 'string_vuln', 'letohs', 'lv_vuln', 'lv_vuln', 'ntohs', 'letohll', 'lv_vuln', 'float', 'letohll', 'double', 'string_vuln', 'float', 'double', 'letohl', 'byte', 'string']), 'llamaboll': ([], ['byte', 'string', 'string', 'letohs', 'float', 'letohs', 'ntohl']), 'llamaonium': ([], ['double', 'float', 'ntohl', 'letohll', 'string', 'letohll', 'string_vuln', 'string', 'float', 'lv', 'ntohs', 'lv_vuln', 'letohl', 'ntohll', 'string', 'float', 'byte', 'letohs']), 'llamaentodermic': ([], ['string', 'ntohs', 'slv']), 'llamapolitician': ([], ['letohs', 'string_vuln', 'string', 'lv_vuln', 'float', 'lv', 'letohl', 'lv', 'double', 'string_vuln', 'double', 'double', 'ntohl', 'string_vuln', 'letohll', 'byte', 'ntohl', 'slv', 'letohs', 'letohl', 'string_vuln', 'string_vuln', 'letohl', 'byte', 'letohs', 'double', 'lv', 'lv', 'letohs', 'ntohl', 'byte', 'byte', 'slv', 'ntohll', 'string_vuln', 'ntohs', 'slv', 'ntohl']), 'llamatopoalgia': ([], ['ntohll', 'ntohs', 'lv', 'letohs', 'ntohs', 'double', 'ntohll', 'letohll', 'ntohs', 'string_vuln', 'ntohl', 'slv_vuln', 'ntohl']), 'llamaTamilian': ([], ['string', 'letohll', 'ntohl', 'ntohs', 'ntohll', 'ntohs', 'string', 'byte', 'double', 'float', 'letohll', 'byte', 'letohs', 'string', 'string', 'lv', 'double', 'lv', 'slv_vuln', 'ntohl']), 'llamasilvicultural': ([], ['float', 'ntohs', 'letohl', 'float', 'letohl', 'ntohl', 'ntohl', 'lv_vuln', 'letohs', 'ntohl', 'ntohs', 'byte', 'string']), 'llamaadulterously': (['llamaatophan', 'llamaunquarrelled', 'llamaadulterously', 'llamaentodermic'], ['ntohs', 'letohs', 'double', 'nextproto_b']), 'llamaschoppen': ([], ['lv_vuln', 'letohs', 'letohl', 'letohl', 'string', 'byte', 'double', 'ntohll', 'string', 'letohll', 'slv', 'letohl', 'string_vuln', 'double', 'letohl', 'letohl', 'string_vuln', 'double', 'string_vuln', 'lv_vuln', 'slv', 'double', 'float', 'ntohs', 'lv', 'ntohs', 'letohll', 'ntohs', 'double', 'string', 'lv_vuln', 'ntohs']), 'llamasart': ([], ['byte', 'ntohs', 'letohl', 'lv', 'slv', 'ntohl', 'lv_vuln', 'slv', 'ntohll', 'double', 'ntohs', 'byte', 'letohl', 'byte', 'letohl', 'slv', 'float', 'string_vuln', 'letohs', 'double', 'byte', 'byte', 'letohl', 'ntohs', 'letohl', 'double', 'byte', 'string_vuln', 'slv', 'lv', 'slv', 'double', 'string_vuln', 'byte', 'ntohs', 'letohll', 'letohll', 'lv_vuln', 'string_vuln', 'string_vuln', 'ntohs', 'ntohs', 'lv_vuln', 'float']), 'llamamink': ([], ['byte']), 'llamaintracutaneous': ([], ['ntohs', 'slv', 'string_vuln', 'lv_vuln', 'byte', 'ntohll', 'ntohll', 'byte', 'slv_vuln', 'letohs', 'ntohs', 'letohs', 'double', 'lv_vuln', 'byte', 'letohll', 'double', 'letohll', 'lv', 'float', 'letohl', 'letohs', 'ntohll', 'letohll', 'slv', 'ntohl', 'letohs', 'lv_vuln', 'lv_vuln', 'float', 'double', 'letohll', 'slv_vuln', 'string', 'letohs', 'letohl', 'letohs', 'double', 'float', 'ntohll', 'ntohll']), 'llamafootpad': (['llamanatterjack'], ['ntohll', 'slv', 'string', 'ntohll', 'string', 'ntohll', 'ntohl', 'slv', 'nextproto_s', 'float', 'string', 'slv_vuln', 'byte', 'letohll', 'double', 'byte', 'letohl', 'letohl', 'lv', 'letohs', 'string', 'letohll', 'slv', 'ntohl', 'string', 'lv_vuln', 'double', 'double', 'ntohll', 'lv', 'slv_vuln', 'slv_vuln', 'double', 'ntohl', 'float', 'slv_vuln', 'lv', 'byte', 'slv', 'lv', 'slv', 'lv_vuln', 'nextproto_b', 'string_vuln', 'letohs', 'double', 'letohl', 'lv', 'string', 'ntohl']), 'llamamyringotomy': ([], ['letohl', 'ntohll']), 'llamasubderivative': ([], ['ntohll', 'byte', 'letohll', 'ntohll', 'ntohl', 'ntohs', 'letohl', 'letohl', 'string', 'ntohl', 'letohll', 'byte', 'ntohs', 'ntohl', 'lv', 'ntohll', 'float', 'letohll', 'lv', 'byte', 'ntohll', 'letohll', 'ntohll', 'ntohl', 'string_vuln', 'string_vuln', 'letohll', 'letohll', 'string', 'float']), 'llamaleaflessness': ([], ['string', 'ntohl', 'string', 'nextproto_b', 'string', 'letohs', 'nextproto_s', 'letohs', 'letohl', 'byte', 'byte', 'lv', 'lv', 'ntohs', 'double', 'ntohll', 'letohl', 'double', 'slv', 'nextproto_s']), 'llamasquatinid': (['llamasubtileness', 'llamaintracutaneous'], ['nextproto_b', 'string', 'ntohll', 'letohl', 'ntohl', 'slv', 'ntohll', 'letohs', 'nextproto_s', 'lv_vuln', 'lv', 'float', 'float', 'ntohll', 'float', 'slv_vuln', 'letohl', 'lv', 'byte', 'lv', 'letohl', 'ntohll', 'float', 'lv_vuln', 'ntohs', 'letohll', 'ntohs', 'letohll', 'nextproto_b', 'nextproto_s', 'nextproto_b', 'float', 'ntohll', 'ntohs', 'nextproto_s', 'double', 'string_vuln', 'slv_vuln', 'byte', 'ntohll', 'lv_vuln', 'float', 'slv_vuln', 'byte', 'lv_vuln']), 'llamaspaying': ([], ['letohll', 'letohl', 'double', 'lv', 'ntohs', 'letohll', 'ntohll']), 'llamaportico': (['llamaSoricinae'], ['ntohll', 'ntohs', 'ntohl', 'string_vuln', 'lv', 'ntohll', 'ntohl', 'ntohll', 'slv_vuln', 'letohl', 'ntohs', 'byte', 'letohll', 'slv_vuln', 'nextproto_s', 'letohll', 'letohl', 'letohl', 'ntohll', 'lv_vuln', 'double', 'letohs', 'string', 'ntohll', 'letohll', 'letohll', 'byte', 'nextproto_s', 'byte']), 'llamaquavery': (['llamasubderivative'], ['double', 'ntohl', 'double', 'lv_vuln', 'double', 'slv_vuln', 'slv', 'string', 'lv_vuln', 'nextproto_s', 'lv', 'string_vuln', 'byte', 'letohs', 'letohll', 'letohll', 'lv', 'ntohl', 'nextproto_b', 'ntohll', 'string_vuln', 'nextproto_b', 'byte']), 'llamagamobium': ([], ['double', 'letohl', 'letohll', 'float', 'string', 'ntohl', 'slv', 'letohs', 'double']), 'llamaateuchus': ([], []), 'llamadebadge': ([], ['string', 'slv_vuln', 'lv', 'slv_vuln', 'lv', 'ntohl', 'float', 'float', 'string_vuln', 'ntohl', 'letohs', 'letohs', 'byte', 'byte', 'byte', 'double', 'lv', 'lv_vuln', 'string', 'ntohl', 'slv_vuln', 'ntohll', 'float', 'double', 'slv_vuln', 'lv', 'ntohs', 'letohs', 'lv', 'letohl', 'letohs', 'ntohs', 'ntohs']), 'llamaDonia': ([], ['letohll', 'float', 'double', 'ntohs', 'letohs', 'slv', 'lv', 'double', 'byte', 'slv_vuln', 'string_vuln', 'slv', 'float', 'float', 'letohs', 'ntohll', 'letohs', 'ntohs', 'slv_vuln', 'ntohs', 'letohl', 'letohll', 'lv', 'lv', 'byte', 'letohs', 'string', 'slv_vuln', 'lv', 'lv_vuln', 'string', 'ntohl', 'slv_vuln', 'letohll', 'double', 'string_vuln', 'string_vuln', 'slv_vuln', 'slv', 'letohs']), 'llamadermophyte': ([], ['slv', 'ntohs', 'string', 'ntohll', 'ntohs', 'lv_vuln', 'ntohs', 'slv', 'ntohl']), 'llamacolophonite': ([], ['letohs', 'letohl', 'byte', 'ntohll', 'byte', 'string_vuln', 'byte', 'string', 'slv_vuln', 'string_vuln', 'slv_vuln', 'string', 'string_vuln', 'string', 'lv', 'double', 'float', 'letohl', 'byte', 'ntohs', 'letohl', 'ntohll', 'letohs']), 'llamadyspneic': (['llamaentodermic', 'llamadentary', 'llamaJaina', 'llamadiscretion'], ['double', 'letohll', 'float', 'letohs']), 'llamafurnishable': ([], []), 'llamacombatable': ([], ['letohl', 'letohs', 'ntohl', 'ntohll', 'ntohl', 'double', 'slv', 'byte', 'letohl', 'ntohs', 'string_vuln', 'lv', 'letohl', 'float', 'ntohll', 'letohl']), 'llamakirombo': (['llamaonium', 'llamamarket'], ['byte', 'ntohll', 'letohl', 'double', 'letohs', 'nextproto_s', 'lv', 'lv_vuln', 'letohl', 'byte', 'string', 'ntohll', 'double', 'ntohll', 'slv', 'nextproto_s', 'lv_vuln', 'letohl', 'string', 'byte', 'nextproto_s', 'letohl', 'lv_vuln', 'slv_vuln', 'slv', 'nextproto_b', 'string', 'string', 'ntohs', 'letohs', 'slv', 'string', 'float', 'double', 'double', 'float', 'letohl', 'string', 'ntohl', 'letohl', 'lv_vuln', 'ntohl']), 'llamaworshipability': ([], ['slv', 'ntohll', 'letohll', 'letohl', 'ntohs', 'letohs', 'lv', 'slv_vuln', 'slv_vuln', 'byte', 'float', 'float', 'ntohs', 'string', 'ntohl', 'double', 'lv_vuln', 'letohs', 'letohl', 'lv', 'ntohll', 'double', 'slv', 'lv_vuln', 'letohs', 'lv', 'ntohl', 'slv_vuln', 'letohs', 'lv', 'string', 'ntohll', 'byte', 'letohl', 'string', 'ntohs']), 'llamaparmacety': ([], ['ntohll', 'float', 'string', 'float', 'double', 'lv_vuln', 'string', 'double']), 'llamapronephros': ([], ['slv', 'float', 'letohll', 'lv_vuln', 'slv_vuln', 'lv', 'letohs', 'double', 'letohll', 'slv_vuln', 'slv', 'byte', 'letohll', 'string', 'letohs', 'float', 'lv_vuln', 'slv_vuln', 'ntohll', 'ntohll', 'letohs', 'slv', 'ntohs', 'letohl', 'string_vuln', 'slv_vuln', 'letohs', 'letohl', 'string_vuln', 'string_vuln', 'string_vuln', 'ntohll', 'double', 'double', 'string_vuln', 'ntohll']), 'llamasmolt': ([], ['slv_vuln', 'lv_vuln', 'lv', 'string_vuln', 'byte', 'letohll', 'letohll', 'slv', 'ntohll', 'double', 'letohl', 'slv_vuln', 'double', 'lv_vuln', 'float', 'slv', 'double', 'slv_vuln', 'letohll', 'letohl', 'ntohs', 'slv_vuln', 'ntohl', 'slv', 'letohl', 'slv_vuln', 'ntohl', 'ntohl', 'byte', 'byte', 'byte', 'string', 'slv_vuln', 'lv_vuln', 'ntohs', 'slv_vuln', 'ntohs', 'ntohl', 'letohll', 'ntohll', 'string']), 'llamaJuletta': (['llamaunquarrelled', 'llamaaalii', 'llamatrochocephalus'], ['nextproto_s', 'letohs', 'ntohs', 'nextproto_s', 'string', 'letohs', 'float', 'letohl', 'string_vuln', 'ntohl', 'ntohll', 'ntohll', 'ntohl', 'lv_vuln', 'ntohll', 'letohs', 'ntohl', 'string_vuln', 'lv_vuln', 'string_vuln', 'float', 'float', 'letohl', 'letohs', 'string_vuln', 'double', 'string_vuln', 'nextproto_s', 'slv_vuln', 'nextproto_s', 'byte', 'letohl', 'double', 'nextproto_b']), 'llamalutecia': ([], ['float', 'slv_vuln', 'lv_vuln']), 'llamaposit': ([], ['ntohs', 'letohs', 'letohl', 'lv_vuln', 'letohs', 'letohll', 'lv', 'ntohl', 'letohl', 'double', 'byte', 'letohll', 'ntohl', 'ntohl', 'letohl', 'lv', 'string_vuln', 'letohll', 'slv', 'letohll', 'string_vuln', 'double', 'string', 'lv', 'letohll', 'slv', 'slv_vuln', 'ntohs', 'lv_vuln', 'ntohl', 'letohl', 'byte', 'string_vuln']), 'llamacarnaptious': ([], ['ntohll', 'string', 'letohs', 'ntohs', 'string', 'float', 'ntohl', 'float', 'letohl', 'letohs', 'slv', 'letohl', 'lv_vuln', 'letohl', 'ntohl', 'letohl', 'ntohll', 'ntohl', 'ntohl', 'letohll', 'string_vuln', 'lv_vuln', 'slv', 'byte', 'string', 'slv', 'slv', 'lv_vuln', 'letohs', 'letohll', 'byte', 'string_vuln']), 'llamaferocity': ([], ['letohs', 'letohs', 'lv_vuln', 'float', 'ntohl', 'ntohs', 'letohl', 'letohll', 'string_vuln', 'slv_vuln']), 'llamacoruscant': ([], ['slv_vuln', 'ntohll', 'lv', 'double', 'letohl', 'lv', 'string_vuln', 'double', 'lv_vuln', 'string', 'ntohs', 'string', 'lv_vuln']), 'llamaaalii': ([], ['lv_vuln', 'double', 'string_vuln', 'letohs', 'string_vuln', 'string', 'ntohl', 'slv', 'letohl', 'float', 'lv', 'letohs', 'ntohll', 'letohl', 'float', 'letohl', 'float', 'letohl', 'ntohs', 'float', 'ntohs', 'letohs', 'lv_vuln', 'letohl', 'letohl', 'string', 'letohs', 'letohll', 'lv', 'ntohl', 'ntohs', 'letohs', 'lv', 'lv_vuln', 'lv_vuln', 'string_vuln']), 'llamaParthenon': ([], ['byte', 'byte', 'slv', 'byte', 'float', 'ntohs', 'float', 'ntohs', 'string_vuln', 'lv_vuln', 'ntohl', 'letohll', 'ntohll', 'letohl', 'string', 'string_vuln', 'ntohl', 'string_vuln', 'ntohll', 'string', 'ntohll', 'float', 'letohl', 'letohll', 'letohs', 'ntohl', 'letohll', 'string_vuln', 'string_vuln', 'string', 'slv_vuln', 'letohl', 'lv_vuln', 'string', 'slv_vuln', 'letohll', 'float']), 'llamasubtileness': ([], ['letohll', 'byte', 'lv', 'string_vuln', 'ntohs', 'slv', 'letohs', 'ntohll', 'double', 'lv', 'slv', 'slv', 'double', 'byte', 'letohll', 'slv_vuln', 'letohll', 'slv_vuln', 'letohl', 'byte', 'string', 'ntohll', 'slv', 'double', 'string', 'ntohs', 'slv_vuln']), 'llamahemostat': ([], ['lv', 'ntohll', 'slv', 'slv', 'ntohl', 'lv_vuln', 'string', 'float', 'float']), 'llamadiscretion': ([], ['lv_vuln', 'ntohll', 'byte', 'ntohs', 'slv', 'lv', 'letohs']), 'llamamitigate': ([], ['slv']), 'llamamachar': ([], ['double', 'slv_vuln', 'string', 'double', 'ntohs', 'ntohll', 'lv', 'slv_vuln', 'lv_vuln', 'double', 'float', 'ntohll', 'letohll', 'ntohll']), 'llamafactorization': ([], ['float', 'slv', 'lv_vuln', 'letohll', 'ntohs', 'letohl', 'ntohll', 'ntohll', 'letohl', 'ntohs', 'ntohs', 'letohs', 'letohl', 'string_vuln', 'lv']), 'llamaantimaterialistic': ([], ['string', 'ntohs', 'string', 'byte', 'letohl', 'ntohs', 'lv', 'ntohl', 'lv', 'letohll', 'lv_vuln', 'slv_vuln', 'string', 'lv', 'lv_vuln', 'slv_vuln', 'slv', 'slv_vuln', 'lv', 'slv', 'ntohl', 'double', 'lv', 'slv', 'lv_vuln', 'string', 'string']), 'llamalowermost': ([], ['byte', 'letohll', 'ntohll', 'string', 'float', 'letohll', 'lv', 'lv', 'slv', 'letohl', 'ntohll', 'string_vuln', 'letohs', 'ntohs', 'letohs', 'letohll', 'letohl', 'byte', 'float', 'double']), 'llamaSoricinae': ([], ['slv_vuln']), 'llamamononomial': (['llamahalochromy'], ['nextproto_s', 'string', 'lv', 'lv', 'byte', 'slv_vuln', 'slv', 'ntohs', 'ntohs'])}

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

from struct import *

typelen = {
    'ntohll':8,
    'letohll':8,
    'ntohl':4,
    'letohl':4,
    'ntohs':2,
    'letohs':2,
    'byte':1,
    'float':4,
    'double':8,
}

class DUPE(object):
    def __init__(self,ver=1,ctype=0,clen=-1,flen=1000,idx=0,heap=0,pkts=[]):
        self.ver = ver
        self.ctype = ctype
        self.clen = clen
        self.flen = flen
        self.idx = idx
        self.pkts = pkts
        self.heap = heap
    def __str__(self):
        pktdata = "".join(str(pkt) for pkt in self.pkts)
        if self.clen == -1:
            self.clen = len(pktdata)
        s = pack("<IIiiII",self.ver,self.ctype,self.clen,self.flen,self.idx,self.heap)
        return s+pktdata

class DUPEpkt(object):
    def __init__(self,data,ts=0,l=-1):
        self.data = data
        self.ts = ts
        if l == -1:
            self.l = len(data)
        else:
            self.l = l

    def __str__(self):
        return pack("<Ii",self.ts,self.l)+self.data

def random_alpha(a, b):
    return ''.join(choice(string.letters) for _ in range(randint(a, b)))

def random_string(a, b):
    chars = string.letters + string.digits
    return ''.join(choice(chars) for _ in range(randint(a, b)))

def urand(size):
    return ''.join(chr(randint(0,255)) for _ in range(size)) 

def makerandpkt(framelen=1000,ctype=0):
    #need to make a llama header in a bit
    idx = randint(0,len(llama)-1)
    layers = [urand(20)+pack("<I",idx)]
    curname = llama[idx].split("_")[1]
    names = ["llama"]
        
    while 1:
        cur = pollinfo[curname]
        names.append(curname)
        nxt = -1
        layer = []
        for field in cur[1]:
            if field in typelen:
                layer.append(urand(typelen[field]))
            elif field == "nextproto_b":
                nxt = -1 if len(cur[0]) == 0 else randint(0,len(cur[0])-1)
                layer.append(pack("b",nxt))
            elif field == "nextproto_s":
                nxt = -1 if len(cur[0]) == 0 else randint(0,len(cur[0])-1)
                layer.append(pack("<h",nxt))
            elif field in ["string","string_vuln"]:
                l = randint(0,110)
                layer.append(urand(l).replace("\x00","").replace("\n","")+"\x00")
            elif field in ["lv","lv_vuln"]:
                l = randint(1,230)
                layer.append(pack("B",l))
                layer.append(urand(l))
            elif field in ["slv","slv_vuln"]:
                l = randint(1,4000)
                layer.append(pack("H",l))
                layer.append(urand(l))
                
        if len("".join(layer+layers)) > framelen or len("".join(layer)) == 0:
            names = names[:-1]
            break
        layers.append("".join(layer))
        if nxt == -1 :
            break
        curname = cur[0][nxt]
    
    return DUPEpkt("".join(layers)),names

class CABLEGRINDER(Actions):
    def start(self):
        pass
    def valid(self):
        numpkts = randint(1,200)
        pkts,names = [],[]
        ctype = 0 
        flen = randint(250,8000)
        for i in range(numpkts):
            pkt,name = makerandpkt(ctype=ctype,framelen=flen)
            pkts.append(pkt)
            names.append(name)
        payload = str(DUPE(pkts=pkts,ctype=ctype,flen=flen))
        self.write(pack("<I",len(payload)))
        self.write(payload)

        #our match deems most of the actual dissection non-essential
        #checking layer names is sufficient to ensure desync hasn't occurred
        #and our for-testing release checks actual dissection of vuln layer
        self.read(delim="\n",expect="Starting dissection...")
        for cur in names:
            self.read(delim="====\n",expect=".*New Packet",expect_format='pcre')
            for name in cur:
                self.read(delim="===\n",expect=".*==="+name,expect_format='pcre')
            
        self.read(delim="===\n",expect=".*Dissection finished",expect_format='pcre')
    def invalidver(self):
        numpkts = randint(1,200)
        pkts,names = [],[]
        ctype = choice([0,1])
        flen = randint(250,8000)
        pkt,name = makerandpkt(ctype=ctype,framelen=flen)
        pkts.append(pkt)
        names.append(name)
        payload = str(DUPE(ver=randint(4,255),pkts=pkts,ctype=ctype,flen=flen))
        self.write(pack("<I",len(payload)))
        self.write(payload)
        self.read(delim="\n",expect="Bad file.")
