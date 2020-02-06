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
#include "libcgc.h"
#include "cgc_stdint.h"
#include "cgc_libc.h"
#include "cgc_memcpy.h"
#include "cgc_memset.h"
#include "cgc_list.h"
#include "cgc_malloc.h"
#include "cgc_string.h"

#include "cgc_products.h"
#include "cgc_inventory.h"
#include "cgc_sale.h"

void cgc_load_inventory(Inventory *inv) {
    Product *p = NULL;
    const char *b = NULL;
    const char *d = NULL;

    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "41916155";
    d = "CBoXdTVlxY";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 59889;
    p->cost = 0.17;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "12099137";
    d = "BURcRQvrJKLoWsuIu";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 1128;
    p->cost = 5.87;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "86848322";
    d = "OuYFqLLPzpStQmLGNfrdmNBtqESEZPD";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 64101;
    p->cost = 2.54;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "87849215";
    d = "osjXtGjM";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 46035;
    p->cost = 4.37;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "50361802";
    d = "WaALSqUGTUcRRQbrpD";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 12881;
    p->cost = 5.64;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "28433101";
    d = "UeC";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 31708;
    p->cost = 7.28;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "12220539";
    d = "lbYe";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 23198;
    p->cost = 5.34;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "47111925";
    d = "MxLyPsRDfZNyZCZyPiFcO";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 31486;
    p->cost = 1.1;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "00664810";
    d = "WBsFTZeoBiL";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 27300;
    p->cost = 4.89;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "94282841";
    d = "CiyXLti";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 10630;
    p->cost = 1.09;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "72291601";
    d = "RJOT";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 50229;
    p->cost = 5.77;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "49840365";
    d = "LrmPNlODBcMuDdejSrklcnEJbCdJOA";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 45345;
    p->cost = 5.19;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "50717007";
    d = "OcYEZmPsrGyvcbxflxxamqLlLJ";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 60011;
    p->cost = 2.57;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "99964712";
    d = "NcVIOJwRguXBwKdEwzx";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 116;
    p->cost = 6.68;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "13706532";
    d = "SmMpCSxZTsPtsDwZprYJIBYtCczZ";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 39806;
    p->cost = 7.33;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "44381534";
    d = "mfuSPgiZIaaPTtfMKuYWPqW";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 30120;
    p->cost = 4.71;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "66900952";
    d = "dLuOlZFcVURjFo";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 14927;
    p->cost = 3.05;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "74926350";
    d = "cXK";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 2472;
    p->cost = 3.89;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "31951871";
    d = "gZOISWZizsGWxfIV";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 25650;
    p->cost = 2.72;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "20585072";
    d = "OVNnctOCWjcIXOvxXwZdeYk";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 33445;
    p->cost = 3.71;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "29987528";
    d = "bQemYYbkbgRlHzYhddLTXBV";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 63850;
    p->cost = 8.27;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "44567831";
    d = "bVxVzqJoMAbbABpuK";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 10273;
    p->cost = 1.29;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "50044195";
    d = "TIwQNAxBYeidFJgiuiceKyyZOo";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 64340;
    p->cost = 6.58;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "80320569";
    d = "ZbOKiKsPtSLZUXGSgVuVvEg";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 3226;
    p->cost = 8.54;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "12555125";
    d = "OOBHIukxWBXTujZouCmy";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 48316;
    p->cost = 1.52;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "77475676";
    d = "TkFFmsuzuD";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 12910;
    p->cost = 8.68;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "68500061";
    d = "xXKivnPyFeKjDSsLIcHJkcfDZr";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 25325;
    p->cost = 5.73;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "28801547";
    d = "zPzfWrYgkzusXM";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 55098;
    p->cost = 3.69;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "27286316";
    d = "iaOSmHodjClBbsmNMxMUjFEEBw";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 45201;
    p->cost = 6.05;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "06744775";
    d = "RZaRMCR";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 39161;
    p->cost = 10.0;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "14976063";
    d = "lXkSGfmjnIcJrqjzuwaLpNVsxCoeZla";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 58432;
    p->cost = 5.36;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "93921599";
    d = "qJGFxRH";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 51914;
    p->cost = 1.06;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "78486525";
    d = "lrWSt";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 5215;
    p->cost = 1.92;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "75836131";
    d = "Cm";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 35136;
    p->cost = 8.44;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "95486291";
    d = "jJIhbikVwbdVIhCAZGHqjLY";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 30557;
    p->cost = 5.14;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "19044824";
    d = "mfoLvDmaKMrQNvWLWUiYCiXNnZOMU";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 18280;
    p->cost = 3.65;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "30172465";
    d = "CKFuyRMTABZMIBdsK";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 44608;
    p->cost = 5.41;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "83497266";
    d = "XyEYbfHmiWVtxO";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 1520;
    p->cost = 6.46;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "46693171";
    d = "YmUHUvQoJ";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 45063;
    p->cost = 0.68;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "60531381";
    d = "QiMrgINCfFjkdvozTnpjtYrELDjgmK";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 50365;
    p->cost = 1.93;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "80111827";
    d = "EGCyAcNvAoGTznBIInHD";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 50163;
    p->cost = 7.36;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "46108933";
    d = "yA";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 18997;
    p->cost = 0.89;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "71344234";
    d = "GZxglAxzKwgOEwRVCgPdf";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 40662;
    p->cost = 4.91;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "20102117";
    d = "RijMwfgJPEmoMjLCeepSY";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 31998;
    p->cost = 1.43;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "79267208";
    d = "XvnPoMSNWZVhfUMmpFKpphmfbwSTVo";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 34301;
    p->cost = 9.62;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "13001388";
    d = "ngllfhKdGIPHvstPd";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 54407;
    p->cost = 4.96;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "17573103";
    d = "P";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 2515;
    p->cost = 4.57;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "22995054";
    d = "GoiSSYhLBSSyDMzpZEfEN";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 23072;
    p->cost = 8.89;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "58885039";
    d = "LvJBSMasVdFOjklc";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 45088;
    p->cost = 2.69;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "36970139";
    d = "emCCzWhvvveEoEViRKwIsyWcMA";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 47167;
    p->cost = 1.94;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "15048891";
    d = "QPuFuYcsUqextKPzFHBFhWWxiwL";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 39914;
    p->cost = 9.83;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "52820574";
    d = "VweQMYhAYdTCE";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 34549;
    p->cost = 7.15;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "05558432";
    d = "YrsbMdytqSNuDPUN";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 43021;
    p->cost = 7.77;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "45266556";
    d = "SxagJhzOzEhqAhpAdpuREDJnM";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 53735;
    p->cost = 2.5;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "55671691";
    d = "JvqXCPHjJyQ";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 60683;
    p->cost = 5.15;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "30246117";
    d = "DaEzVgFxbPzzIF";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 11978;
    p->cost = 2.24;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "32349600";
    d = "vDzqEgRHizanDmHWYmtKjy";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 32694;
    p->cost = 0.9;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "27002400";
    d = "TAAwfhYZBDTbayzgoqEhIiYYZLPBss";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 28221;
    p->cost = 9.18;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "23728750";
    d = "KMLqLPUgFrTS";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 28808;
    p->cost = 0.98;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "27227405";
    d = "xbIkRMPWFwVechYvOEnobB";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 7006;
    p->cost = 9.0;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "88925705";
    d = "aMZLCrgwzBKDLiauIPwEHaX";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 6082;
    p->cost = 6.82;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "60234543";
    d = "UcWX";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 23069;
    p->cost = 1.92;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "26550548";
    d = "btg";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 57058;
    p->cost = 7.31;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //
    //
    p = cgc_malloc(sizeof(Product));
    MALLOC_OK(p);
    cgc_memset(p, '\0', sizeof(Product));

    b = "80824106";
    d = "B";
    cgc_memcpy(p->barcode, b, cgc_strlen(b, '\0'));
    cgc_memcpy(p->desc, d, cgc_strlen(d, '\0'));
    p->model_num = 37533;
    p->cost = 4.06;
    p->sfn = onsale_fn[0];
    p->update_serial = 0;

    cgc_list_insert_at_end(inv, p);
    //

}

