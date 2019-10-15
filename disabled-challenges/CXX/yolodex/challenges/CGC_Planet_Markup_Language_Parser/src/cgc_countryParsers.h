/*

Author: John Berry <hj@cromulence.co>

Copyright (c) 2014 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#ifndef __COUNTRYPARSERS_H__
#define __COUNTRYPARSERS_H__

#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_service.h"
#include "cgc_helper.h"
#include "cgc_genericParsers.h"
#include "cgc_territoryParsers.h"

int cgc_countryMenu( pCountry co );
void cgc_freeCountry( pCountry co );
void cgc_printCountryInfo( pCountry co);
pCountry cgc_countryTopLevel( pstring str);
void cgc_initCountry( pCountry co );
char *cgc_extractLanguage( pstring str );
char *cgc_extractCapitol( pstring str );

#endif

