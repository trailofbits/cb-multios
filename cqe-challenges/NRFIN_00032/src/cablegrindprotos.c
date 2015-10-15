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
#include "libc.h"
#include "cablegrind.h"
#include "cablegrindprotos.h"
#include "helpers.h"

STACKPROTECTINIT
void process_llamainutilely(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamainutilely===")-1,"===llamainutilely===");
handle_ntohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaantioxygen(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamasubtileness,process_llamapunaise,process_llamainutilely};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaantioxygen===")-1,"===llamaantioxygen===");
handle_ntohll(payload,size);
handle_lv_vuln(payload,size);
next = handle_nextproto_b(payload,size);
handle_string(payload,size);
handle_letohs(payload,size);
handle_byte(payload,size);
next = handle_nextproto_s(payload,size);
handle_double(payload,size);
handle_letohl(payload,size);
handle_float(payload,size);
handle_slv(payload,size);
handle_float(payload,size);
next = handle_nextproto_b(payload,size);
handle_slv_vuln(payload,size);
handle_string(payload,size);
handle_float(payload,size);
handle_ntohll(payload,size);
handle_ntohl(payload,size);
handle_ntohll(payload,size);
next = handle_nextproto_s(payload,size);
handle_float(payload,size);
handle_ntohll(payload,size);
handle_byte(payload,size);
handle_float(payload,size);
handle_string_vuln(payload,size);
handle_ntohll(payload,size);
handle_letohll(payload,size);
handle_lv_vuln(payload,size);
handle_ntohll(payload,size);
next = handle_nextproto_s(payload,size);
handle_lv_vuln(payload,size);
handle_ntohs(payload,size);
handle_letohll(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamafucate(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamafucate===")-1,"===llamafucate===");
handle_letohs(payload,size);
handle_ntohl(payload,size);
handle_letohll(payload,size);
handle_slv(payload,size);
handle_ntohs(payload,size);
handle_ntohs(payload,size);
handle_slv(payload,size);
handle_letohll(payload,size);
handle_letohll(payload,size);
handle_ntohs(payload,size);
handle_byte(payload,size);
handle_float(payload,size);
handle_ntohs(payload,size);
handle_byte(payload,size);
handle_float(payload,size);
handle_byte(payload,size);
handle_ntohs(payload,size);
handle_ntohs(payload,size);
handle_ntohll(payload,size);
handle_double(payload,size);
handle_float(payload,size);
handle_string_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_slv(payload,size);
handle_string(payload,size);
handle_string_vuln(payload,size);
handle_letohl(payload,size);
handle_lv(payload,size);
handle_double(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamacyanohydrin(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamacyanohydrin===")-1,"===llamacyanohydrin===");
handle_letohs(payload,size);
handle_letohll(payload,size);
handle_string_vuln(payload,size);
handle_ntohl(payload,size);
handle_ntohs(payload,size);
handle_string_vuln(payload,size);
handle_ntohs(payload,size);
handle_float(payload,size);
handle_ntohl(payload,size);
handle_byte(payload,size);
handle_lv_vuln(payload,size);
handle_float(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaisonymy(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaisonymy===")-1,"===llamaisonymy===");
handle_ntohll(payload,size);
handle_string_vuln(payload,size);
handle_float(payload,size);
handle_ntohs(payload,size);
handle_lv(payload,size);
handle_lv_vuln(payload,size);
handle_ntohl(payload,size);
handle_float(payload,size);
handle_byte(payload,size);
handle_lv(payload,size);
handle_letohll(payload,size);
handle_ntohll(payload,size);
handle_letohs(payload,size);
handle_ntohl(payload,size);
handle_double(payload,size);
handle_float(payload,size);
handle_byte(payload,size);
handle_ntohs(payload,size);
handle_letohs(payload,size);
handle_ntohl(payload,size);
handle_string_vuln(payload,size);
handle_letohll(payload,size);
handle_string(payload,size);
handle_byte(payload,size);
handle_byte(payload,size);
handle_slv_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_letohl(payload,size);
handle_byte(payload,size);
handle_lv_vuln(payload,size);
handle_string(payload,size);
handle_string(payload,size);
handle_ntohl(payload,size);
handle_letohll(payload,size);
handle_letohs(payload,size);
handle_ntohs(payload,size);
handle_double(payload,size);
handle_ntohll(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamastrawer(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamamarket};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamastrawer===")-1,"===llamastrawer===");
next = handle_nextproto_b(payload,size);
handle_ntohs(payload,size);
handle_letohll(payload,size);
handle_lv_vuln(payload,size);
handle_letohll(payload,size);
handle_byte(payload,size);
handle_ntohl(payload,size);
handle_byte(payload,size);
handle_byte(payload,size);
next = handle_nextproto_s(payload,size);
handle_lv_vuln(payload,size);
handle_letohl(payload,size);
handle_slv_vuln(payload,size);
handle_letohs(payload,size);
next = handle_nextproto_s(payload,size);
handle_ntohl(payload,size);
handle_lv(payload,size);
next = handle_nextproto_s(payload,size);
handle_string_vuln(payload,size);
handle_float(payload,size);
handle_lv_vuln(payload,size);
next = handle_nextproto_b(payload,size);
handle_float(payload,size);
handle_double(payload,size);
next = handle_nextproto_b(payload,size);
handle_ntohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamacarbonator(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamacarbonator===")-1,"===llamacarbonator===");
handle_double(payload,size);
handle_float(payload,size);
handle_string(payload,size);
handle_double(payload,size);
handle_byte(payload,size);
handle_lv_vuln(payload,size);
handle_ntohll(payload,size);
handle_double(payload,size);
handle_lv(payload,size);
handle_ntohll(payload,size);
handle_letohs(payload,size);
handle_string_vuln(payload,size);
handle_double(payload,size);
handle_byte(payload,size);
handle_float(payload,size);
handle_string(payload,size);
handle_ntohs(payload,size);
handle_double(payload,size);
handle_byte(payload,size);
handle_double(payload,size);
handle_ntohl(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamapoorness(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamasubtileness,process_llamaforebridge,process_llamaunquarrelled};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamapoorness===")-1,"===llamapoorness===");
next = handle_nextproto_s(payload,size);
handle_letohll(payload,size);
handle_ntohs(payload,size);
handle_float(payload,size);
handle_double(payload,size);
handle_ntohs(payload,size);
handle_float(payload,size);
handle_float(payload,size);
handle_letohs(payload,size);
handle_ntohs(payload,size);
handle_float(payload,size);
handle_string(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaundignifiedly(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaundignifiedly===")-1,"===llamaundignifiedly===");
handle_letohl(payload,size);
handle_letohs(payload,size);
handle_double(payload,size);
handle_lv(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaambulacriform(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamamyringotomy,process_llamaskewed};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaambulacriform===")-1,"===llamaambulacriform===");
next = handle_nextproto_b(payload,size);
handle_double(payload,size);
handle_double(payload,size);
handle_letohl(payload,size);
handle_ntohs(payload,size);
handle_slv(payload,size);
next = handle_nextproto_b(payload,size);
handle_string(payload,size);
handle_ntohll(payload,size);
handle_ntohl(payload,size);
handle_float(payload,size);
handle_slv(payload,size);
handle_ntohll(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaJaina(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamaPantagruelistic,process_llamainutilely};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaJaina===")-1,"===llamaJaina===");
handle_string_vuln(payload,size);
handle_ntohs(payload,size);
next = handle_nextproto_s(payload,size);
handle_letohl(payload,size);
next = handle_nextproto_s(payload,size);
handle_lv_vuln(payload,size);
next = handle_nextproto_b(payload,size);
handle_byte(payload,size);
handle_slv_vuln(payload,size);
handle_string_vuln(payload,size);
next = handle_nextproto_b(payload,size);
handle_ntohll(payload,size);
handle_slv(payload,size);
handle_string_vuln(payload,size);
handle_byte(payload,size);
handle_string_vuln(payload,size);
handle_byte(payload,size);
handle_ntohs(payload,size);
handle_ntohs(payload,size);
handle_string_vuln(payload,size);
handle_ntohl(payload,size);
handle_slv_vuln(payload,size);
next = handle_nextproto_b(payload,size);
next = handle_nextproto_s(payload,size);
next = handle_nextproto_s(payload,size);
handle_ntohll(payload,size);
handle_lv(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamafolliculin(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamafolliculin===")-1,"===llamafolliculin===");
handle_ntohll(payload,size);
handle_slv(payload,size);
handle_slv(payload,size);
handle_lv(payload,size);
handle_letohs(payload,size);
handle_string(payload,size);
handle_float(payload,size);
handle_double(payload,size);
handle_double(payload,size);
handle_letohl(payload,size);
handle_ntohl(payload,size);
handle_letohll(payload,size);
handle_letohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamadoldrums(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamadoldrums===")-1,"===llamadoldrums===");
handle_ntohl(payload,size);
handle_float(payload,size);
handle_letohll(payload,size);
handle_letohs(payload,size);
handle_ntohs(payload,size);
handle_slv(payload,size);
handle_lv_vuln(payload,size);
handle_double(payload,size);
handle_slv_vuln(payload,size);
handle_string_vuln(payload,size);
handle_letohs(payload,size);
handle_letohl(payload,size);
handle_slv_vuln(payload,size);
handle_letohl(payload,size);
handle_ntohs(payload,size);
handle_ntohl(payload,size);
handle_letohl(payload,size);
handle_lv_vuln(payload,size);
handle_letohl(payload,size);
handle_string_vuln(payload,size);
handle_letohl(payload,size);
handle_string(payload,size);
handle_letohl(payload,size);
handle_string_vuln(payload,size);
handle_double(payload,size);
handle_string_vuln(payload,size);
handle_slv(payload,size);
handle_slv(payload,size);
handle_slv(payload,size);
handle_float(payload,size);
handle_slv_vuln(payload,size);
handle_ntohs(payload,size);
handle_byte(payload,size);
handle_ntohs(payload,size);
handle_string_vuln(payload,size);
handle_double(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamatelodendron(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamatelodendron===")-1,"===llamatelodendron===");
handle_string(payload,size);
handle_lv_vuln(payload,size);
handle_double(payload,size);
handle_double(payload,size);
handle_lv_vuln(payload,size);
handle_string(payload,size);
handle_byte(payload,size);
handle_letohs(payload,size);
handle_lv_vuln(payload,size);
handle_double(payload,size);
handle_lv_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_slv(payload,size);
handle_ntohs(payload,size);
handle_ntohll(payload,size);
handle_ntohll(payload,size);
handle_ntohll(payload,size);
handle_letohs(payload,size);
handle_float(payload,size);
handle_string(payload,size);
handle_ntohll(payload,size);
handle_double(payload,size);
handle_byte(payload,size);
handle_ntohl(payload,size);
handle_ntohll(payload,size);
handle_slv(payload,size);
handle_ntohl(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamajibi(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamafootpad,process_llamastrawer};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamajibi===")-1,"===llamajibi===");
handle_lv_vuln(payload,size);
handle_float(payload,size);
next = handle_nextproto_s(payload,size);
handle_string(payload,size);
handle_float(payload,size);
handle_ntohll(payload,size);
handle_slv_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_ntohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamapycnite(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamapycnite===")-1,"===llamapycnite===");
handle_slv(payload,size);
handle_slv(payload,size);
handle_slv_vuln(payload,size);
handle_letohll(payload,size);
handle_letohl(payload,size);
handle_ntohs(payload,size);
handle_ntohs(payload,size);
handle_slv(payload,size);
handle_ntohll(payload,size);
handle_letohl(payload,size);
handle_slv_vuln(payload,size);
handle_letohl(payload,size);
handle_letohll(payload,size);
handle_lv(payload,size);
handle_ntohl(payload,size);
handle_ntohll(payload,size);
handle_string_vuln(payload,size);
handle_lv_vuln(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaatophan(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaatophan===")-1,"===llamaatophan===");
handle_string_vuln(payload,size);
handle_string_vuln(payload,size);
handle_ntohs(payload,size);
handle_letohl(payload,size);
handle_lv(payload,size);
handle_letohs(payload,size);
handle_letohl(payload,size);
handle_letohs(payload,size);
handle_lv(payload,size);
handle_ntohs(payload,size);
handle_double(payload,size);
handle_ntohll(payload,size);
handle_lv_vuln(payload,size);
handle_letohll(payload,size);
handle_string_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_string_vuln(payload,size);
handle_byte(payload,size);
handle_ntohl(payload,size);
handle_string(payload,size);
handle_letohs(payload,size);
handle_ntohs(payload,size);
handle_slv(payload,size);
handle_lv_vuln(payload,size);
handle_byte(payload,size);
handle_byte(payload,size);
handle_double(payload,size);
handle_ntohl(payload,size);
handle_float(payload,size);
handle_lv(payload,size);
handle_letohll(payload,size);
handle_double(payload,size);
handle_letohl(payload,size);
handle_float(payload,size);
handle_letohs(payload,size);
handle_letohl(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaobtrusiveness(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaobtrusiveness===")-1,"===llamaobtrusiveness===");
handle_ntohs(payload,size);
handle_string(payload,size);
handle_ntohl(payload,size);
handle_letohl(payload,size);
handle_float(payload,size);
handle_string(payload,size);
handle_letohll(payload,size);
handle_ntohs(payload,size);
handle_letohl(payload,size);
handle_string_vuln(payload,size);
handle_lv(payload,size);
handle_letohl(payload,size);
handle_slv(payload,size);
handle_slv_vuln(payload,size);
handle_letohll(payload,size);
handle_letohl(payload,size);
handle_string_vuln(payload,size);
handle_ntohs(payload,size);
handle_lv_vuln(payload,size);
handle_double(payload,size);
handle_byte(payload,size);
handle_letohl(payload,size);
handle_double(payload,size);
handle_ntohs(payload,size);
handle_string(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamachromophotographic(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamaunacceptable,process_llamaisonymy};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamachromophotographic===")-1,"===llamachromophotographic===");
handle_string(payload,size);
handle_string_vuln(payload,size);
handle_lv(payload,size);
handle_string(payload,size);
handle_lv_vuln(payload,size);
handle_ntohs(payload,size);
handle_slv(payload,size);
handle_letohl(payload,size);
handle_double(payload,size);
handle_string(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaskewed(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaskewed===")-1,"===llamaskewed===");
handle_lv(payload,size);
handle_ntohl(payload,size);
handle_lv(payload,size);
handle_letohs(payload,size);
handle_string_vuln(payload,size);
handle_ntohll(payload,size);
handle_letohll(payload,size);
handle_letohs(payload,size);
handle_letohll(payload,size);
handle_double(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamapanse(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamapanse===")-1,"===llamapanse===");
handle_slv(payload,size);
handle_ntohl(payload,size);
handle_slv(payload,size);
handle_slv_vuln(payload,size);
handle_ntohl(payload,size);
handle_byte(payload,size);
handle_ntohll(payload,size);
handle_double(payload,size);
handle_slv_vuln(payload,size);
handle_letohll(payload,size);
handle_float(payload,size);
handle_string(payload,size);
handle_lv(payload,size);
handle_string(payload,size);
handle_float(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaunacceptable(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaunacceptable===")-1,"===llamaunacceptable===");
handle_lv(payload,size);
handle_ntohl(payload,size);
handle_lv_vuln(payload,size);
handle_letohs(payload,size);
handle_lv(payload,size);
handle_byte(payload,size);
handle_ntohll(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaPantagruelistic(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaPantagruelistic===")-1,"===llamaPantagruelistic===");
handle_float(payload,size);
handle_ntohs(payload,size);
handle_byte(payload,size);
handle_ntohs(payload,size);
handle_slv_vuln(payload,size);
handle_letohl(payload,size);
handle_float(payload,size);
handle_slv_vuln(payload,size);
handle_ntohl(payload,size);
handle_ntohl(payload,size);
handle_slv(payload,size);
handle_lv_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_double(payload,size);
handle_lv_vuln(payload,size);
handle_letohll(payload,size);
handle_letohl(payload,size);
handle_double(payload,size);
handle_byte(payload,size);
handle_lv(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaAraneiformes(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaAraneiformes===")-1,"===llamaAraneiformes===");
handle_ntohs(payload,size);
handle_letohs(payload,size);
handle_float(payload,size);
handle_double(payload,size);
handle_slv_vuln(payload,size);
handle_double(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamascholasticly(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamascholasticly===")-1,"===llamascholasticly===");
handle_lv_vuln(payload,size);
handle_string_vuln(payload,size);
handle_letohs(payload,size);
handle_lv(payload,size);
handle_byte(payload,size);
handle_letohll(payload,size);
handle_letohll(payload,size);
handle_letohl(payload,size);
handle_slv(payload,size);
handle_string(payload,size);
handle_ntohll(payload,size);
handle_byte(payload,size);
handle_letohl(payload,size);
handle_slv_vuln(payload,size);
handle_letohs(payload,size);
handle_slv(payload,size);
handle_double(payload,size);
handle_letohs(payload,size);
handle_slv_vuln(payload,size);
handle_ntohll(payload,size);
handle_slv_vuln(payload,size);
handle_string_vuln(payload,size);
handle_string(payload,size);
handle_lv(payload,size);
handle_string_vuln(payload,size);
handle_float(payload,size);
handle_string_vuln(payload,size);
handle_letohl(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamamarket(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamainutilely,process_llamamyringotomy,process_llamaadulterously,process_llamaatophan};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamamarket===")-1,"===llamamarket===");
handle_lv_vuln(payload,size);
handle_letohll(payload,size);
handle_ntohll(payload,size);
handle_slv_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_lv(payload,size);
handle_ntohs(payload,size);
handle_lv(payload,size);
handle_slv(payload,size);
handle_double(payload,size);
handle_slv(payload,size);
handle_string_vuln(payload,size);
handle_letohl(payload,size);
handle_ntohs(payload,size);
next = handle_nextproto_s(payload,size);
handle_double(payload,size);
handle_ntohl(payload,size);
handle_letohl(payload,size);
handle_lv_vuln(payload,size);
handle_ntohl(payload,size);
handle_slv_vuln(payload,size);
handle_ntohll(payload,size);
handle_string_vuln(payload,size);
next = handle_nextproto_b(payload,size);
handle_double(payload,size);
handle_string_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_ntohs(payload,size);
handle_lv(payload,size);
handle_ntohs(payload,size);
handle_string_vuln(payload,size);
handle_float(payload,size);
handle_lv(payload,size);
handle_lv(payload,size);
handle_slv(payload,size);
handle_lv_vuln(payload,size);
handle_string_vuln(payload,size);
handle_string_vuln(payload,size);
handle_ntohll(payload,size);
handle_ntohs(payload,size);
handle_slv_vuln(payload,size);
handle_string_vuln(payload,size);
handle_letohll(payload,size);
handle_lv_vuln(payload,size);
handle_float(payload,size);
handle_float(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaforebridge(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaforebridge===")-1,"===llamaforebridge===");
handle_string(payload,size);
handle_lv_vuln(payload,size);
handle_lv(payload,size);
handle_letohl(payload,size);
handle_letohl(payload,size);
handle_string(payload,size);
handle_letohs(payload,size);
handle_lv_vuln(payload,size);
handle_string(payload,size);
handle_letohll(payload,size);
handle_ntohll(payload,size);
handle_string_vuln(payload,size);
handle_ntohl(payload,size);
handle_letohll(payload,size);
handle_letohll(payload,size);
handle_slv(payload,size);
handle_double(payload,size);
handle_float(payload,size);
handle_letohs(payload,size);
handle_ntohl(payload,size);
handle_ntohll(payload,size);
handle_double(payload,size);
handle_float(payload,size);
handle_letohl(payload,size);
handle_float(payload,size);
handle_string_vuln(payload,size);
handle_ntohll(payload,size);
handle_letohl(payload,size);
handle_lv_vuln(payload,size);
handle_ntohll(payload,size);
handle_letohl(payload,size);
handle_byte(payload,size);
handle_letohll(payload,size);
handle_lv_vuln(payload,size);
handle_slv_vuln(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamasporocyst(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamasporocyst===")-1,"===llamasporocyst===");
handle_slv_vuln(payload,size);
handle_double(payload,size);
handle_letohl(payload,size);
handle_string(payload,size);
handle_float(payload,size);
handle_letohll(payload,size);
handle_byte(payload,size);
handle_ntohll(payload,size);
handle_float(payload,size);
handle_string_vuln(payload,size);
handle_letohs(payload,size);
handle_slv_vuln(payload,size);
handle_string(payload,size);
handle_ntohl(payload,size);
handle_letohll(payload,size);
handle_float(payload,size);
handle_ntohs(payload,size);
handle_string_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_letohl(payload,size);
handle_letohll(payload,size);
handle_float(payload,size);
handle_ntohl(payload,size);
handle_slv(payload,size);
handle_string_vuln(payload,size);
handle_double(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamahalochromy(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamahalochromy===")-1,"===llamahalochromy===");
handle_letohl(payload,size);
handle_double(payload,size);
handle_slv(payload,size);
handle_byte(payload,size);
handle_string_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_letohll(payload,size);
handle_string_vuln(payload,size);
handle_string(payload,size);
handle_slv(payload,size);
handle_letohll(payload,size);
handle_ntohll(payload,size);
handle_ntohll(payload,size);
handle_letohs(payload,size);
handle_slv(payload,size);
handle_letohll(payload,size);
handle_ntohll(payload,size);
handle_letohll(payload,size);
handle_double(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamafluctuate(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamafluctuate===")-1,"===llamafluctuate===");
handle_float(payload,size);
handle_float(payload,size);
handle_lv(payload,size);
handle_double(payload,size);
handle_letohl(payload,size);
handle_lv_vuln(payload,size);
handle_ntohl(payload,size);
handle_slv(payload,size);
handle_letohll(payload,size);
handle_slv(payload,size);
handle_ntohl(payload,size);
handle_byte(payload,size);
handle_float(payload,size);
handle_string(payload,size);
handle_letohll(payload,size);
handle_lv_vuln(payload,size);
handle_letohl(payload,size);
handle_letohll(payload,size);
handle_double(payload,size);
handle_slv(payload,size);
handle_letohl(payload,size);
handle_ntohll(payload,size);
handle_lv_vuln(payload,size);
handle_slv(payload,size);
handle_double(payload,size);
handle_slv_vuln(payload,size);
handle_string_vuln(payload,size);
handle_float(payload,size);
handle_float(payload,size);
handle_ntohll(payload,size);
handle_letohll(payload,size);
handle_string_vuln(payload,size);
handle_letohs(payload,size);
handle_string(payload,size);
handle_byte(payload,size);
handle_lv(payload,size);
handle_double(payload,size);
handle_ntohs(payload,size);
handle_letohl(payload,size);
handle_slv(payload,size);
handle_float(payload,size);
handle_lv(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamatrochocephalus(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamatrochocephalus===")-1,"===llamatrochocephalus===");
handle_letohl(payload,size);
handle_lv(payload,size);
handle_double(payload,size);
handle_letohll(payload,size);
handle_slv_vuln(payload,size);
handle_slv(payload,size);
handle_ntohl(payload,size);
handle_letohll(payload,size);
handle_letohll(payload,size);
handle_ntohl(payload,size);
handle_string_vuln(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaPlautine(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaPlautine===")-1,"===llamaPlautine===");
handle_ntohl(payload,size);
handle_string(payload,size);
handle_float(payload,size);
handle_lv(payload,size);
handle_string_vuln(payload,size);
handle_string(payload,size);
handle_ntohll(payload,size);
handle_lv(payload,size);
handle_byte(payload,size);
handle_ntohll(payload,size);
handle_ntohs(payload,size);
handle_letohl(payload,size);
handle_lv(payload,size);
handle_slv(payload,size);
handle_ntohs(payload,size);
handle_ntohs(payload,size);
handle_string_vuln(payload,size);
handle_string_vuln(payload,size);
handle_letohll(payload,size);
handle_float(payload,size);
handle_slv_vuln(payload,size);
handle_letohs(payload,size);
handle_letohs(payload,size);
handle_ntohs(payload,size);
handle_slv(payload,size);
handle_letohll(payload,size);
handle_slv(payload,size);
handle_ntohll(payload,size);
handle_float(payload,size);
handle_letohs(payload,size);
handle_slv_vuln(payload,size);
handle_slv_vuln(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaHoplonemertini(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaHoplonemertini===")-1,"===llamaHoplonemertini===");
handle_lv(payload,size);
handle_ntohll(payload,size);
handle_ntohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamapunaise(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamapunaise===")-1,"===llamapunaise===");
handle_slv(payload,size);
handle_lv(payload,size);
handle_lv(payload,size);
handle_float(payload,size);
handle_ntohll(payload,size);
handle_slv(payload,size);
handle_slv(payload,size);
handle_letohs(payload,size);
handle_lv_vuln(payload,size);
handle_letohll(payload,size);
handle_float(payload,size);
handle_lv_vuln(payload,size);
handle_ntohl(payload,size);
handle_byte(payload,size);
handle_byte(payload,size);
handle_lv_vuln(payload,size);
handle_letohll(payload,size);
handle_letohl(payload,size);
handle_ntohl(payload,size);
handle_byte(payload,size);
handle_ntohl(payload,size);
handle_ntohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamanatterjack(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamainutilely};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamanatterjack===")-1,"===llamanatterjack===");
handle_letohl(payload,size);
handle_letohl(payload,size);
handle_float(payload,size);
handle_string_vuln(payload,size);
handle_ntohll(payload,size);
handle_ntohll(payload,size);
handle_slv_vuln(payload,size);
handle_ntohll(payload,size);
handle_slv(payload,size);
handle_slv_vuln(payload,size);
next = handle_nextproto_s(payload,size);
handle_letohs(payload,size);
handle_letohs(payload,size);
handle_lv(payload,size);
handle_lv(payload,size);
next = handle_nextproto_s(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamascobby(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamascobby===")-1,"===llamascobby===");
handle_lv_vuln(payload,size);
handle_letohl(payload,size);
handle_string(payload,size);
handle_string_vuln(payload,size);
handle_ntohs(payload,size);
handle_string(payload,size);
handle_float(payload,size);
handle_lv(payload,size);
handle_double(payload,size);
handle_lv_vuln(payload,size);
handle_letohll(payload,size);
handle_string(payload,size);
handle_float(payload,size);
handle_lv(payload,size);
handle_letohl(payload,size);
handle_ntohll(payload,size);
handle_string_vuln(payload,size);
handle_slv(payload,size);
handle_slv(payload,size);
handle_lv(payload,size);
handle_letohs(payload,size);
handle_ntohs(payload,size);
handle_ntohl(payload,size);
handle_letohll(payload,size);
handle_letohll(payload,size);
handle_slv(payload,size);
handle_float(payload,size);
handle_letohs(payload,size);
handle_letohs(payload,size);
handle_float(payload,size);
handle_double(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamahydropathy(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamahydropathy===")-1,"===llamahydropathy===");
handle_letohl(payload,size);
handle_ntohl(payload,size);
handle_string(payload,size);
handle_letohll(payload,size);
handle_ntohl(payload,size);
handle_lv(payload,size);
handle_float(payload,size);
handle_letohs(payload,size);
handle_byte(payload,size);
handle_lv(payload,size);
handle_letohs(payload,size);
handle_string(payload,size);
handle_lv(payload,size);
handle_lv(payload,size);
handle_ntohll(payload,size);
handle_ntohll(payload,size);
handle_slv(payload,size);
handle_letohll(payload,size);
handle_string_vuln(payload,size);
handle_float(payload,size);
handle_letohl(payload,size);
handle_letohs(payload,size);
handle_letohll(payload,size);
handle_lv_vuln(payload,size);
handle_byte(payload,size);
handle_string(payload,size);
handle_float(payload,size);
handle_letohll(payload,size);
handle_ntohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamadentary(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamadentary===")-1,"===llamadentary===");
handle_letohs(payload,size);
handle_ntohl(payload,size);
handle_ntohs(payload,size);
handle_string_vuln(payload,size);
handle_letohl(payload,size);
handle_letohl(payload,size);
handle_ntohs(payload,size);
handle_lv(payload,size);
handle_slv_vuln(payload,size);
handle_ntohll(payload,size);
handle_lv(payload,size);
handle_lv_vuln(payload,size);
handle_byte(payload,size);
handle_float(payload,size);
handle_letohs(payload,size);
handle_byte(payload,size);
handle_string_vuln(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamadenominate(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamadermophyte,process_llamadyspneic};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamadenominate===")-1,"===llamadenominate===");
handle_letohl(payload,size);
handle_lv(payload,size);
handle_slv_vuln(payload,size);
handle_ntohs(payload,size);
handle_string_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_letohs(payload,size);
next = handle_nextproto_b(payload,size);
handle_float(payload,size);
handle_letohll(payload,size);
handle_byte(payload,size);
handle_double(payload,size);
handle_letohll(payload,size);
handle_slv(payload,size);
handle_slv(payload,size);
handle_ntohl(payload,size);
handle_letohs(payload,size);
handle_slv_vuln(payload,size);
handle_letohl(payload,size);
handle_float(payload,size);
next = handle_nextproto_b(payload,size);
handle_slv_vuln(payload,size);
handle_letohll(payload,size);
handle_letohs(payload,size);
next = handle_nextproto_b(payload,size);
handle_double(payload,size);
handle_ntohll(payload,size);
next = handle_nextproto_b(payload,size);
handle_double(payload,size);
handle_string_vuln(payload,size);
handle_ntohl(payload,size);
handle_slv_vuln(payload,size);
handle_string(payload,size);
next = handle_nextproto_b(payload,size);
next = handle_nextproto_b(payload,size);
handle_ntohl(payload,size);
handle_slv_vuln(payload,size);
handle_float(payload,size);
next = handle_nextproto_b(payload,size);
handle_lv(payload,size);
next = handle_nextproto_s(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamadecoke(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamadecoke===")-1,"===llamadecoke===");
handle_lv(payload,size);
handle_letohll(payload,size);
handle_ntohl(payload,size);
handle_ntohl(payload,size);
handle_string(payload,size);
handle_letohl(payload,size);
handle_string_vuln(payload,size);
handle_ntohs(payload,size);
handle_lv_vuln(payload,size);
handle_byte(payload,size);
handle_ntohll(payload,size);
handle_lv_vuln(payload,size);
handle_byte(payload,size);
handle_slv(payload,size);
handle_ntohs(payload,size);
handle_ntohl(payload,size);
handle_ntohll(payload,size);
handle_float(payload,size);
handle_letohll(payload,size);
handle_lv_vuln(payload,size);
handle_ntohl(payload,size);
handle_ntohll(payload,size);
handle_double(payload,size);
handle_letohs(payload,size);
handle_letohl(payload,size);
handle_slv_vuln(payload,size);
handle_letohl(payload,size);
handle_double(payload,size);
handle_lv_vuln(payload,size);
handle_string_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_slv(payload,size);
handle_letohs(payload,size);
handle_float(payload,size);
handle_ntohl(payload,size);
handle_ntohll(payload,size);
handle_letohl(payload,size);
handle_lv_vuln(payload,size);
handle_slv(payload,size);
handle_byte(payload,size);
handle_string_vuln(payload,size);
handle_string(payload,size);
handle_letohl(payload,size);
handle_string(payload,size);
handle_slv(payload,size);
handle_slv_vuln(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamadigredience(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamadigredience===")-1,"===llamadigredience===");
handle_string_vuln(payload,size);
handle_lv(payload,size);
handle_letohs(payload,size);
handle_lv_vuln(payload,size);
handle_slv(payload,size);
handle_letohs(payload,size);
handle_string_vuln(payload,size);
handle_double(payload,size);
handle_string(payload,size);
handle_ntohll(payload,size);
handle_ntohl(payload,size);
handle_ntohs(payload,size);
handle_ntohl(payload,size);
handle_lv(payload,size);
handle_letohs(payload,size);
handle_byte(payload,size);
handle_string(payload,size);
handle_ntohll(payload,size);
handle_byte(payload,size);
handle_letohl(payload,size);
handle_string(payload,size);
handle_letohll(payload,size);
handle_float(payload,size);
handle_ntohll(payload,size);
handle_letohl(payload,size);
handle_ntohs(payload,size);
handle_double(payload,size);
handle_slv(payload,size);
handle_slv_vuln(payload,size);
handle_byte(payload,size);
handle_letohs(payload,size);
handle_byte(payload,size);
handle_lv_vuln(payload,size);
handle_string_vuln(payload,size);
handle_slv(payload,size);
handle_ntohs(payload,size);
handle_byte(payload,size);
handle_lv_vuln(payload,size);
handle_double(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamabetitle(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamabetitle===")-1,"===llamabetitle===");
handle_ntohs(payload,size);
handle_letohll(payload,size);
handle_ntohll(payload,size);
handle_ntohll(payload,size);
handle_string(payload,size);
handle_double(payload,size);
handle_ntohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamatenebrose(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamascobby,process_llamaonium};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamatenebrose===")-1,"===llamatenebrose===");
handle_double(payload,size);
handle_letohs(payload,size);
handle_letohs(payload,size);
handle_double(payload,size);
handle_letohll(payload,size);
next = handle_nextproto_s(payload,size);
handle_lv(payload,size);
next = handle_nextproto_b(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaforgeability(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaforgeability===")-1,"===llamaforgeability===");
handle_slv_vuln(payload,size);
handle_byte(payload,size);
handle_letohll(payload,size);
handle_letohll(payload,size);
handle_string_vuln(payload,size);
handle_double(payload,size);
handle_ntohll(payload,size);
handle_lv(payload,size);
handle_slv_vuln(payload,size);
handle_ntohs(payload,size);
handle_lv_vuln(payload,size);
handle_ntohl(payload,size);
handle_ntohl(payload,size);
handle_ntohll(payload,size);
handle_string_vuln(payload,size);
handle_string(payload,size);
handle_slv_vuln(payload,size);
handle_lv_vuln(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaunderlease(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaunderlease===")-1,"===llamaunderlease===");
handle_letohll(payload,size);
handle_double(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaunquarrelled(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaunquarrelled===")-1,"===llamaunquarrelled===");
handle_letohs(payload,size);
handle_letohl(payload,size);
handle_float(payload,size);
handle_ntohl(payload,size);
handle_slv_vuln(payload,size);
handle_byte(payload,size);
handle_lv_vuln(payload,size);
handle_lv(payload,size);
handle_letohll(payload,size);
handle_slv_vuln(payload,size);
handle_ntohl(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamasupersympathy(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamasupersympathy===")-1,"===llamasupersympathy===");
handle_ntohs(payload,size);
handle_ntohl(payload,size);
handle_letohs(payload,size);
handle_ntohl(payload,size);
handle_slv_vuln(payload,size);
handle_letohs(payload,size);
handle_ntohll(payload,size);
handle_letohl(payload,size);
handle_byte(payload,size);
handle_double(payload,size);
handle_lv(payload,size);
handle_ntohll(payload,size);
handle_ntohl(payload,size);
handle_letohs(payload,size);
handle_slv_vuln(payload,size);
handle_ntohl(payload,size);
handle_ntohs(payload,size);
handle_double(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamamegasporic(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamamegasporic===")-1,"===llamamegasporic===");
handle_letohll(payload,size);
handle_slv(payload,size);
handle_float(payload,size);
handle_float(payload,size);
handle_string(payload,size);
handle_byte(payload,size);
handle_string_vuln(payload,size);
handle_string_vuln(payload,size);
handle_letohs(payload,size);
handle_lv_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_ntohs(payload,size);
handle_letohll(payload,size);
handle_lv_vuln(payload,size);
handle_float(payload,size);
handle_letohll(payload,size);
handle_double(payload,size);
handle_string_vuln(payload,size);
handle_float(payload,size);
handle_double(payload,size);
handle_letohl(payload,size);
handle_byte(payload,size);
handle_string(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaboll(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaboll===")-1,"===llamaboll===");
handle_byte(payload,size);
handle_string(payload,size);
handle_string(payload,size);
handle_letohs(payload,size);
handle_float(payload,size);
handle_letohs(payload,size);
handle_ntohl(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaonium(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaonium===")-1,"===llamaonium===");
handle_double(payload,size);
handle_float(payload,size);
handle_ntohl(payload,size);
handle_letohll(payload,size);
handle_string(payload,size);
handle_letohll(payload,size);
handle_string_vuln(payload,size);
handle_string(payload,size);
handle_float(payload,size);
handle_lv(payload,size);
handle_ntohs(payload,size);
handle_lv_vuln(payload,size);
handle_letohl(payload,size);
handle_ntohll(payload,size);
handle_string(payload,size);
handle_float(payload,size);
handle_byte(payload,size);
handle_letohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaentodermic(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaentodermic===")-1,"===llamaentodermic===");
handle_string(payload,size);
handle_ntohs(payload,size);
handle_slv(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamapolitician(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamapolitician===")-1,"===llamapolitician===");
handle_letohs(payload,size);
handle_string_vuln(payload,size);
handle_string(payload,size);
handle_lv_vuln(payload,size);
handle_float(payload,size);
handle_lv(payload,size);
handle_letohl(payload,size);
handle_lv(payload,size);
handle_double(payload,size);
handle_string_vuln(payload,size);
handle_double(payload,size);
handle_double(payload,size);
handle_ntohl(payload,size);
handle_string_vuln(payload,size);
handle_letohll(payload,size);
handle_byte(payload,size);
handle_ntohl(payload,size);
handle_slv(payload,size);
handle_letohs(payload,size);
handle_letohl(payload,size);
handle_string_vuln(payload,size);
handle_string_vuln(payload,size);
handle_letohl(payload,size);
handle_byte(payload,size);
handle_letohs(payload,size);
handle_double(payload,size);
handle_lv(payload,size);
handle_lv(payload,size);
handle_letohs(payload,size);
handle_ntohl(payload,size);
handle_byte(payload,size);
handle_byte(payload,size);
handle_slv(payload,size);
handle_ntohll(payload,size);
handle_string_vuln(payload,size);
handle_ntohs(payload,size);
handle_slv(payload,size);
handle_ntohl(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamatopoalgia(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamatopoalgia===")-1,"===llamatopoalgia===");
handle_ntohll(payload,size);
handle_ntohs(payload,size);
handle_lv(payload,size);
handle_letohs(payload,size);
handle_ntohs(payload,size);
handle_double(payload,size);
handle_ntohll(payload,size);
handle_letohll(payload,size);
handle_ntohs(payload,size);
handle_string_vuln(payload,size);
handle_ntohl(payload,size);
handle_slv_vuln(payload,size);
handle_ntohl(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaTamilian(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaTamilian===")-1,"===llamaTamilian===");
handle_string(payload,size);
handle_letohll(payload,size);
handle_ntohl(payload,size);
handle_ntohs(payload,size);
handle_ntohll(payload,size);
handle_ntohs(payload,size);
handle_string(payload,size);
handle_byte(payload,size);
handle_double(payload,size);
handle_float(payload,size);
handle_letohll(payload,size);
handle_byte(payload,size);
handle_letohs(payload,size);
handle_string(payload,size);
handle_string(payload,size);
handle_lv(payload,size);
handle_double(payload,size);
handle_lv(payload,size);
handle_slv_vuln(payload,size);
handle_ntohl(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamasilvicultural(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamasilvicultural===")-1,"===llamasilvicultural===");
handle_float(payload,size);
handle_ntohs(payload,size);
handle_letohl(payload,size);
handle_float(payload,size);
handle_letohl(payload,size);
handle_ntohl(payload,size);
handle_ntohl(payload,size);
handle_lv_vuln(payload,size);
handle_letohs(payload,size);
handle_ntohl(payload,size);
handle_ntohs(payload,size);
handle_byte(payload,size);
handle_string(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaadulterously(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamaatophan,process_llamaunquarrelled,process_llamaadulterously,process_llamaentodermic};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaadulterously===")-1,"===llamaadulterously===");
handle_ntohs(payload,size);
handle_letohs(payload,size);
handle_double(payload,size);
next = handle_nextproto_b(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaschoppen(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaschoppen===")-1,"===llamaschoppen===");
handle_lv_vuln(payload,size);
handle_letohs(payload,size);
handle_letohl(payload,size);
handle_letohl(payload,size);
handle_string(payload,size);
handle_byte(payload,size);
handle_double(payload,size);
handle_ntohll(payload,size);
handle_string(payload,size);
handle_letohll(payload,size);
handle_slv(payload,size);
handle_letohl(payload,size);
handle_string_vuln(payload,size);
handle_double(payload,size);
handle_letohl(payload,size);
handle_letohl(payload,size);
handle_string_vuln(payload,size);
handle_double(payload,size);
handle_string_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_slv(payload,size);
handle_double(payload,size);
handle_float(payload,size);
handle_ntohs(payload,size);
handle_lv(payload,size);
handle_ntohs(payload,size);
handle_letohll(payload,size);
handle_ntohs(payload,size);
handle_double(payload,size);
handle_string(payload,size);
handle_lv_vuln(payload,size);
handle_ntohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamasart(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamasart===")-1,"===llamasart===");
handle_byte(payload,size);
handle_ntohs(payload,size);
handle_letohl(payload,size);
handle_lv(payload,size);
handle_slv(payload,size);
handle_ntohl(payload,size);
handle_lv_vuln(payload,size);
handle_slv(payload,size);
handle_ntohll(payload,size);
handle_double(payload,size);
handle_ntohs(payload,size);
handle_byte(payload,size);
handle_letohl(payload,size);
handle_byte(payload,size);
handle_letohl(payload,size);
handle_slv(payload,size);
handle_float(payload,size);
handle_string_vuln(payload,size);
handle_letohs(payload,size);
handle_double(payload,size);
handle_byte(payload,size);
handle_byte(payload,size);
handle_letohl(payload,size);
handle_ntohs(payload,size);
handle_letohl(payload,size);
handle_double(payload,size);
handle_byte(payload,size);
handle_string_vuln(payload,size);
handle_slv(payload,size);
handle_lv(payload,size);
handle_slv(payload,size);
handle_double(payload,size);
handle_string_vuln(payload,size);
handle_byte(payload,size);
handle_ntohs(payload,size);
handle_letohll(payload,size);
handle_letohll(payload,size);
handle_lv_vuln(payload,size);
handle_string_vuln(payload,size);
handle_string_vuln(payload,size);
handle_ntohs(payload,size);
handle_ntohs(payload,size);
handle_lv_vuln(payload,size);
handle_float(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamamink(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamamink===")-1,"===llamamink===");
handle_byte(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaintracutaneous(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaintracutaneous===")-1,"===llamaintracutaneous===");
handle_ntohs(payload,size);
handle_slv(payload,size);
handle_string_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_byte(payload,size);
handle_ntohll(payload,size);
handle_ntohll(payload,size);
handle_byte(payload,size);
handle_slv_vuln(payload,size);
handle_letohs(payload,size);
handle_ntohs(payload,size);
handle_letohs(payload,size);
handle_double(payload,size);
handle_lv_vuln(payload,size);
handle_byte(payload,size);
handle_letohll(payload,size);
handle_double(payload,size);
handle_letohll(payload,size);
handle_lv(payload,size);
handle_float(payload,size);
handle_letohl(payload,size);
handle_letohs(payload,size);
handle_ntohll(payload,size);
handle_letohll(payload,size);
handle_slv(payload,size);
handle_ntohl(payload,size);
handle_letohs(payload,size);
handle_lv_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_float(payload,size);
handle_double(payload,size);
handle_letohll(payload,size);
handle_slv_vuln(payload,size);
handle_string(payload,size);
handle_letohs(payload,size);
handle_letohl(payload,size);
handle_letohs(payload,size);
handle_double(payload,size);
handle_float(payload,size);
handle_ntohll(payload,size);
handle_ntohll(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamafootpad(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamanatterjack};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamafootpad===")-1,"===llamafootpad===");
handle_ntohll(payload,size);
handle_slv(payload,size);
handle_string(payload,size);
handle_ntohll(payload,size);
handle_string(payload,size);
handle_ntohll(payload,size);
handle_ntohl(payload,size);
handle_slv(payload,size);
next = handle_nextproto_s(payload,size);
handle_float(payload,size);
handle_string(payload,size);
handle_slv_vuln(payload,size);
handle_byte(payload,size);
handle_letohll(payload,size);
handle_double(payload,size);
handle_byte(payload,size);
handle_letohl(payload,size);
handle_letohl(payload,size);
handle_lv(payload,size);
handle_letohs(payload,size);
handle_string(payload,size);
handle_letohll(payload,size);
handle_slv(payload,size);
handle_ntohl(payload,size);
handle_string(payload,size);
handle_lv_vuln(payload,size);
handle_double(payload,size);
handle_double(payload,size);
handle_ntohll(payload,size);
handle_lv(payload,size);
handle_slv_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_double(payload,size);
handle_ntohl(payload,size);
handle_float(payload,size);
handle_slv_vuln(payload,size);
handle_lv(payload,size);
handle_byte(payload,size);
handle_slv(payload,size);
handle_lv(payload,size);
handle_slv(payload,size);
handle_lv_vuln(payload,size);
next = handle_nextproto_b(payload,size);
handle_string_vuln(payload,size);
handle_letohs(payload,size);
handle_double(payload,size);
handle_letohl(payload,size);
handle_lv(payload,size);
handle_string(payload,size);
handle_ntohl(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamamyringotomy(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamamyringotomy===")-1,"===llamamyringotomy===");
handle_letohl(payload,size);
handle_ntohll(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamasubderivative(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamasubderivative===")-1,"===llamasubderivative===");
handle_ntohll(payload,size);
handle_byte(payload,size);
handle_letohll(payload,size);
handle_ntohll(payload,size);
handle_ntohl(payload,size);
handle_ntohs(payload,size);
handle_letohl(payload,size);
handle_letohl(payload,size);
handle_string(payload,size);
handle_ntohl(payload,size);
handle_letohll(payload,size);
handle_byte(payload,size);
handle_ntohs(payload,size);
handle_ntohl(payload,size);
handle_lv(payload,size);
handle_ntohll(payload,size);
handle_float(payload,size);
handle_letohll(payload,size);
handle_lv(payload,size);
handle_byte(payload,size);
handle_ntohll(payload,size);
handle_letohll(payload,size);
handle_ntohll(payload,size);
handle_ntohl(payload,size);
handle_string_vuln(payload,size);
handle_string_vuln(payload,size);
handle_letohll(payload,size);
handle_letohll(payload,size);
handle_string(payload,size);
handle_float(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaleaflessness(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaleaflessness===")-1,"===llamaleaflessness===");
handle_string(payload,size);
handle_ntohl(payload,size);
handle_string(payload,size);
next = handle_nextproto_b(payload,size);
handle_string(payload,size);
handle_letohs(payload,size);
next = handle_nextproto_s(payload,size);
handle_letohs(payload,size);
handle_letohl(payload,size);
handle_byte(payload,size);
handle_byte(payload,size);
handle_lv(payload,size);
handle_lv(payload,size);
handle_ntohs(payload,size);
handle_double(payload,size);
handle_ntohll(payload,size);
handle_letohl(payload,size);
handle_double(payload,size);
handle_slv(payload,size);
next = handle_nextproto_s(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamasquatinid(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamasubtileness,process_llamaintracutaneous};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamasquatinid===")-1,"===llamasquatinid===");
next = handle_nextproto_b(payload,size);
handle_string(payload,size);
handle_ntohll(payload,size);
handle_letohl(payload,size);
handle_ntohl(payload,size);
handle_slv(payload,size);
handle_ntohll(payload,size);
handle_letohs(payload,size);
next = handle_nextproto_s(payload,size);
handle_lv_vuln(payload,size);
handle_lv(payload,size);
handle_float(payload,size);
handle_float(payload,size);
handle_ntohll(payload,size);
handle_float(payload,size);
handle_slv_vuln(payload,size);
handle_letohl(payload,size);
handle_lv(payload,size);
handle_byte(payload,size);
handle_lv(payload,size);
handle_letohl(payload,size);
handle_ntohll(payload,size);
handle_float(payload,size);
handle_lv_vuln(payload,size);
handle_ntohs(payload,size);
handle_letohll(payload,size);
handle_ntohs(payload,size);
handle_letohll(payload,size);
next = handle_nextproto_b(payload,size);
next = handle_nextproto_s(payload,size);
next = handle_nextproto_b(payload,size);
handle_float(payload,size);
handle_ntohll(payload,size);
handle_ntohs(payload,size);
next = handle_nextproto_s(payload,size);
handle_double(payload,size);
handle_string_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_byte(payload,size);
handle_ntohll(payload,size);
handle_lv_vuln(payload,size);
handle_float(payload,size);
handle_slv_vuln(payload,size);
handle_byte(payload,size);
handle_lv_vuln(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaspaying(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaspaying===")-1,"===llamaspaying===");
handle_letohll(payload,size);
handle_letohl(payload,size);
handle_double(payload,size);
handle_lv(payload,size);
handle_ntohs(payload,size);
handle_letohll(payload,size);
handle_ntohll(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaportico(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamaSoricinae};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaportico===")-1,"===llamaportico===");
handle_ntohll(payload,size);
handle_ntohs(payload,size);
handle_ntohl(payload,size);
handle_string_vuln(payload,size);
handle_lv(payload,size);
handle_ntohll(payload,size);
handle_ntohl(payload,size);
handle_ntohll(payload,size);
handle_slv_vuln(payload,size);
handle_letohl(payload,size);
handle_ntohs(payload,size);
handle_byte(payload,size);
handle_letohll(payload,size);
handle_slv_vuln(payload,size);
next = handle_nextproto_s(payload,size);
handle_letohll(payload,size);
handle_letohl(payload,size);
handle_letohl(payload,size);
handle_ntohll(payload,size);
handle_lv_vuln(payload,size);
handle_double(payload,size);
handle_letohs(payload,size);
handle_string(payload,size);
handle_ntohll(payload,size);
handle_letohll(payload,size);
handle_letohll(payload,size);
handle_byte(payload,size);
next = handle_nextproto_s(payload,size);
handle_byte(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaquavery(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamasubderivative};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaquavery===")-1,"===llamaquavery===");
handle_double(payload,size);
handle_ntohl(payload,size);
handle_double(payload,size);
handle_lv_vuln(payload,size);
handle_double(payload,size);
handle_slv_vuln(payload,size);
handle_slv(payload,size);
handle_string(payload,size);
handle_lv_vuln(payload,size);
next = handle_nextproto_s(payload,size);
handle_lv(payload,size);
handle_string_vuln(payload,size);
handle_byte(payload,size);
handle_letohs(payload,size);
handle_letohll(payload,size);
handle_letohll(payload,size);
handle_lv(payload,size);
handle_ntohl(payload,size);
next = handle_nextproto_b(payload,size);
handle_ntohll(payload,size);
handle_string_vuln(payload,size);
next = handle_nextproto_b(payload,size);
handle_byte(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamagamobium(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamagamobium===")-1,"===llamagamobium===");
handle_double(payload,size);
handle_letohl(payload,size);
handle_letohll(payload,size);
handle_float(payload,size);
handle_string(payload,size);
handle_ntohl(payload,size);
handle_slv(payload,size);
handle_letohs(payload,size);
handle_double(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaateuchus(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaateuchus===")-1,"===llamaateuchus===");

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamadebadge(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamadebadge===")-1,"===llamadebadge===");
handle_string(payload,size);
handle_slv_vuln(payload,size);
handle_lv(payload,size);
handle_slv_vuln(payload,size);
handle_lv(payload,size);
handle_ntohl(payload,size);
handle_float(payload,size);
handle_float(payload,size);
handle_string_vuln(payload,size);
handle_ntohl(payload,size);
handle_letohs(payload,size);
handle_letohs(payload,size);
handle_byte(payload,size);
handle_byte(payload,size);
handle_byte(payload,size);
handle_double(payload,size);
handle_lv(payload,size);
handle_lv_vuln(payload,size);
handle_string(payload,size);
handle_ntohl(payload,size);
handle_slv_vuln(payload,size);
handle_ntohll(payload,size);
handle_float(payload,size);
handle_double(payload,size);
handle_slv_vuln(payload,size);
handle_lv(payload,size);
handle_ntohs(payload,size);
handle_letohs(payload,size);
handle_lv(payload,size);
handle_letohl(payload,size);
handle_letohs(payload,size);
handle_ntohs(payload,size);
handle_ntohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaDonia(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaDonia===")-1,"===llamaDonia===");
handle_letohll(payload,size);
handle_float(payload,size);
handle_double(payload,size);
handle_ntohs(payload,size);
handle_letohs(payload,size);
handle_slv(payload,size);
handle_lv(payload,size);
handle_double(payload,size);
handle_byte(payload,size);
handle_slv_vuln(payload,size);
handle_string_vuln(payload,size);
handle_slv(payload,size);
handle_float(payload,size);
handle_float(payload,size);
handle_letohs(payload,size);
handle_ntohll(payload,size);
handle_letohs(payload,size);
handle_ntohs(payload,size);
handle_slv_vuln(payload,size);
handle_ntohs(payload,size);
handle_letohl(payload,size);
handle_letohll(payload,size);
handle_lv(payload,size);
handle_lv(payload,size);
handle_byte(payload,size);
handle_letohs(payload,size);
handle_string(payload,size);
handle_slv_vuln(payload,size);
handle_lv(payload,size);
handle_lv_vuln(payload,size);
handle_string(payload,size);
handle_ntohl(payload,size);
handle_slv_vuln(payload,size);
handle_letohll(payload,size);
handle_double(payload,size);
handle_string_vuln(payload,size);
handle_string_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_slv(payload,size);
handle_letohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamadermophyte(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamadermophyte===")-1,"===llamadermophyte===");
handle_slv(payload,size);
handle_ntohs(payload,size);
handle_string(payload,size);
handle_ntohll(payload,size);
handle_ntohs(payload,size);
handle_lv_vuln(payload,size);
handle_ntohs(payload,size);
handle_slv(payload,size);
handle_ntohl(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamacolophonite(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamacolophonite===")-1,"===llamacolophonite===");
handle_letohs(payload,size);
handle_letohl(payload,size);
handle_byte(payload,size);
handle_ntohll(payload,size);
handle_byte(payload,size);
handle_string_vuln(payload,size);
handle_byte(payload,size);
handle_string(payload,size);
handle_slv_vuln(payload,size);
handle_string_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_string(payload,size);
handle_string_vuln(payload,size);
handle_string(payload,size);
handle_lv(payload,size);
handle_double(payload,size);
handle_float(payload,size);
handle_letohl(payload,size);
handle_byte(payload,size);
handle_ntohs(payload,size);
handle_letohl(payload,size);
handle_ntohll(payload,size);
handle_letohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamadyspneic(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamaentodermic,process_llamadentary,process_llamaJaina,process_llamadiscretion};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamadyspneic===")-1,"===llamadyspneic===");
handle_double(payload,size);
handle_letohll(payload,size);
handle_float(payload,size);
handle_letohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamafurnishable(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamafurnishable===")-1,"===llamafurnishable===");

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamacombatable(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamacombatable===")-1,"===llamacombatable===");
handle_letohl(payload,size);
handle_letohs(payload,size);
handle_ntohl(payload,size);
handle_ntohll(payload,size);
handle_ntohl(payload,size);
handle_double(payload,size);
handle_slv(payload,size);
handle_byte(payload,size);
handle_letohl(payload,size);
handle_ntohs(payload,size);
handle_string_vuln(payload,size);
handle_lv(payload,size);
handle_letohl(payload,size);
handle_float(payload,size);
handle_ntohll(payload,size);
handle_letohl(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamakirombo(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamaonium,process_llamamarket};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamakirombo===")-1,"===llamakirombo===");
handle_byte(payload,size);
handle_ntohll(payload,size);
handle_letohl(payload,size);
handle_double(payload,size);
handle_letohs(payload,size);
next = handle_nextproto_s(payload,size);
handle_lv(payload,size);
handle_lv_vuln(payload,size);
handle_letohl(payload,size);
handle_byte(payload,size);
handle_string(payload,size);
handle_ntohll(payload,size);
handle_double(payload,size);
handle_ntohll(payload,size);
handle_slv(payload,size);
next = handle_nextproto_s(payload,size);
handle_lv_vuln(payload,size);
handle_letohl(payload,size);
handle_string(payload,size);
handle_byte(payload,size);
next = handle_nextproto_s(payload,size);
handle_letohl(payload,size);
handle_lv_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_slv(payload,size);
next = handle_nextproto_b(payload,size);
handle_string(payload,size);
handle_string(payload,size);
handle_ntohs(payload,size);
handle_letohs(payload,size);
handle_slv(payload,size);
handle_string(payload,size);
handle_float(payload,size);
handle_double(payload,size);
handle_double(payload,size);
handle_float(payload,size);
handle_letohl(payload,size);
handle_string(payload,size);
handle_ntohl(payload,size);
handle_letohl(payload,size);
handle_lv_vuln(payload,size);
handle_ntohl(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaworshipability(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaworshipability===")-1,"===llamaworshipability===");
handle_slv(payload,size);
handle_ntohll(payload,size);
handle_letohll(payload,size);
handle_letohl(payload,size);
handle_ntohs(payload,size);
handle_letohs(payload,size);
handle_lv(payload,size);
handle_slv_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_byte(payload,size);
handle_float(payload,size);
handle_float(payload,size);
handle_ntohs(payload,size);
handle_string(payload,size);
handle_ntohl(payload,size);
handle_double(payload,size);
handle_lv_vuln(payload,size);
handle_letohs(payload,size);
handle_letohl(payload,size);
handle_lv(payload,size);
handle_ntohll(payload,size);
handle_double(payload,size);
handle_slv(payload,size);
handle_lv_vuln(payload,size);
handle_letohs(payload,size);
handle_lv(payload,size);
handle_ntohl(payload,size);
handle_slv_vuln(payload,size);
handle_letohs(payload,size);
handle_lv(payload,size);
handle_string(payload,size);
handle_ntohll(payload,size);
handle_byte(payload,size);
handle_letohl(payload,size);
handle_string(payload,size);
handle_ntohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaparmacety(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaparmacety===")-1,"===llamaparmacety===");
handle_ntohll(payload,size);
handle_float(payload,size);
handle_string(payload,size);
handle_float(payload,size);
handle_double(payload,size);
handle_lv_vuln(payload,size);
handle_string(payload,size);
handle_double(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamapronephros(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamapronephros===")-1,"===llamapronephros===");
handle_slv(payload,size);
handle_float(payload,size);
handle_letohll(payload,size);
handle_lv_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_lv(payload,size);
handle_letohs(payload,size);
handle_double(payload,size);
handle_letohll(payload,size);
handle_slv_vuln(payload,size);
handle_slv(payload,size);
handle_byte(payload,size);
handle_letohll(payload,size);
handle_string(payload,size);
handle_letohs(payload,size);
handle_float(payload,size);
handle_lv_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_ntohll(payload,size);
handle_ntohll(payload,size);
handle_letohs(payload,size);
handle_slv(payload,size);
handle_ntohs(payload,size);
handle_letohl(payload,size);
handle_string_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_letohs(payload,size);
handle_letohl(payload,size);
handle_string_vuln(payload,size);
handle_string_vuln(payload,size);
handle_string_vuln(payload,size);
handle_ntohll(payload,size);
handle_double(payload,size);
handle_double(payload,size);
handle_string_vuln(payload,size);
handle_ntohll(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamasmolt(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamasmolt===")-1,"===llamasmolt===");
handle_slv_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_lv(payload,size);
handle_string_vuln(payload,size);
handle_byte(payload,size);
handle_letohll(payload,size);
handle_letohll(payload,size);
handle_slv(payload,size);
handle_ntohll(payload,size);
handle_double(payload,size);
handle_letohl(payload,size);
handle_slv_vuln(payload,size);
handle_double(payload,size);
handle_lv_vuln(payload,size);
handle_float(payload,size);
handle_slv(payload,size);
handle_double(payload,size);
handle_slv_vuln(payload,size);
handle_letohll(payload,size);
handle_letohl(payload,size);
handle_ntohs(payload,size);
handle_slv_vuln(payload,size);
handle_ntohl(payload,size);
handle_slv(payload,size);
handle_letohl(payload,size);
handle_slv_vuln(payload,size);
handle_ntohl(payload,size);
handle_ntohl(payload,size);
handle_byte(payload,size);
handle_byte(payload,size);
handle_byte(payload,size);
handle_string(payload,size);
handle_slv_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_ntohs(payload,size);
handle_slv_vuln(payload,size);
handle_ntohs(payload,size);
handle_ntohl(payload,size);
handle_letohll(payload,size);
handle_ntohll(payload,size);
handle_string(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaJuletta(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamaunquarrelled,process_llamaaalii,process_llamatrochocephalus};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaJuletta===")-1,"===llamaJuletta===");
next = handle_nextproto_s(payload,size);
handle_letohs(payload,size);
handle_ntohs(payload,size);
next = handle_nextproto_s(payload,size);
handle_string(payload,size);
handle_letohs(payload,size);
handle_float(payload,size);
handle_letohl(payload,size);
handle_string_vuln(payload,size);
handle_ntohl(payload,size);
handle_ntohll(payload,size);
handle_ntohll(payload,size);
handle_ntohl(payload,size);
handle_lv_vuln(payload,size);
handle_ntohll(payload,size);
handle_letohs(payload,size);
handle_ntohl(payload,size);
handle_string_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_string_vuln(payload,size);
handle_float(payload,size);
handle_float(payload,size);
handle_letohl(payload,size);
handle_letohs(payload,size);
handle_string_vuln(payload,size);
handle_double(payload,size);
handle_string_vuln(payload,size);
next = handle_nextproto_s(payload,size);
handle_slv_vuln(payload,size);
next = handle_nextproto_s(payload,size);
handle_byte(payload,size);
handle_letohl(payload,size);
handle_double(payload,size);
next = handle_nextproto_b(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamalutecia(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamalutecia===")-1,"===llamalutecia===");
handle_float(payload,size);
handle_slv_vuln(payload,size);
handle_lv_vuln(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaposit(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaposit===")-1,"===llamaposit===");
handle_ntohs(payload,size);
handle_letohs(payload,size);
handle_letohl(payload,size);
handle_lv_vuln(payload,size);
handle_letohs(payload,size);
handle_letohll(payload,size);
handle_lv(payload,size);
handle_ntohl(payload,size);
handle_letohl(payload,size);
handle_double(payload,size);
handle_byte(payload,size);
handle_letohll(payload,size);
handle_ntohl(payload,size);
handle_ntohl(payload,size);
handle_letohl(payload,size);
handle_lv(payload,size);
handle_string_vuln(payload,size);
handle_letohll(payload,size);
handle_slv(payload,size);
handle_letohll(payload,size);
handle_string_vuln(payload,size);
handle_double(payload,size);
handle_string(payload,size);
handle_lv(payload,size);
handle_letohll(payload,size);
handle_slv(payload,size);
handle_slv_vuln(payload,size);
handle_ntohs(payload,size);
handle_lv_vuln(payload,size);
handle_ntohl(payload,size);
handle_letohl(payload,size);
handle_byte(payload,size);
handle_string_vuln(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamacarnaptious(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamacarnaptious===")-1,"===llamacarnaptious===");
handle_ntohll(payload,size);
handle_string(payload,size);
handle_letohs(payload,size);
handle_ntohs(payload,size);
handle_string(payload,size);
handle_float(payload,size);
handle_ntohl(payload,size);
handle_float(payload,size);
handle_letohl(payload,size);
handle_letohs(payload,size);
handle_slv(payload,size);
handle_letohl(payload,size);
handle_lv_vuln(payload,size);
handle_letohl(payload,size);
handle_ntohl(payload,size);
handle_letohl(payload,size);
handle_ntohll(payload,size);
handle_ntohl(payload,size);
handle_ntohl(payload,size);
handle_letohll(payload,size);
handle_string_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_slv(payload,size);
handle_byte(payload,size);
handle_string(payload,size);
handle_slv(payload,size);
handle_slv(payload,size);
handle_lv_vuln(payload,size);
handle_letohs(payload,size);
handle_letohll(payload,size);
handle_byte(payload,size);
handle_string_vuln(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaferocity(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaferocity===")-1,"===llamaferocity===");
handle_letohs(payload,size);
handle_letohs(payload,size);
handle_lv_vuln(payload,size);
handle_float(payload,size);
handle_ntohl(payload,size);
handle_ntohs(payload,size);
handle_letohl(payload,size);
handle_letohll(payload,size);
handle_string_vuln(payload,size);
handle_slv_vuln(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamacoruscant(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamacoruscant===")-1,"===llamacoruscant===");
handle_slv_vuln(payload,size);
handle_ntohll(payload,size);
handle_lv(payload,size);
handle_double(payload,size);
handle_letohl(payload,size);
handle_lv(payload,size);
handle_string_vuln(payload,size);
handle_double(payload,size);
handle_lv_vuln(payload,size);
handle_string(payload,size);
handle_ntohs(payload,size);
handle_string(payload,size);
handle_lv_vuln(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaaalii(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaaalii===")-1,"===llamaaalii===");
handle_lv_vuln(payload,size);
handle_double(payload,size);
handle_string_vuln(payload,size);
handle_letohs(payload,size);
handle_string_vuln(payload,size);
handle_string(payload,size);
handle_ntohl(payload,size);
handle_slv(payload,size);
handle_letohl(payload,size);
handle_float(payload,size);
handle_lv(payload,size);
handle_letohs(payload,size);
handle_ntohll(payload,size);
handle_letohl(payload,size);
handle_float(payload,size);
handle_letohl(payload,size);
handle_float(payload,size);
handle_letohl(payload,size);
handle_ntohs(payload,size);
handle_float(payload,size);
handle_ntohs(payload,size);
handle_letohs(payload,size);
handle_lv_vuln(payload,size);
handle_letohl(payload,size);
handle_letohl(payload,size);
handle_string(payload,size);
handle_letohs(payload,size);
handle_letohll(payload,size);
handle_lv(payload,size);
handle_ntohl(payload,size);
handle_ntohs(payload,size);
handle_letohs(payload,size);
handle_lv(payload,size);
handle_lv_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_string_vuln(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaParthenon(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaParthenon===")-1,"===llamaParthenon===");
handle_byte(payload,size);
handle_byte(payload,size);
handle_slv(payload,size);
handle_byte(payload,size);
handle_float(payload,size);
handle_ntohs(payload,size);
handle_float(payload,size);
handle_ntohs(payload,size);
handle_string_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_ntohl(payload,size);
handle_letohll(payload,size);
handle_ntohll(payload,size);
handle_letohl(payload,size);
handle_string(payload,size);
handle_string_vuln(payload,size);
handle_ntohl(payload,size);
handle_string_vuln(payload,size);
handle_ntohll(payload,size);
handle_string(payload,size);
handle_ntohll(payload,size);
handle_float(payload,size);
handle_letohl(payload,size);
handle_letohll(payload,size);
handle_letohs(payload,size);
handle_ntohl(payload,size);
handle_letohll(payload,size);
handle_string_vuln(payload,size);
handle_string_vuln(payload,size);
handle_string(payload,size);
handle_slv_vuln(payload,size);
handle_letohl(payload,size);
handle_lv_vuln(payload,size);
handle_string(payload,size);
handle_slv_vuln(payload,size);
handle_letohll(payload,size);
handle_float(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamasubtileness(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamasubtileness===")-1,"===llamasubtileness===");
handle_letohll(payload,size);
handle_byte(payload,size);
handle_lv(payload,size);
handle_string_vuln(payload,size);
handle_ntohs(payload,size);
handle_slv(payload,size);
handle_letohs(payload,size);
handle_ntohll(payload,size);
handle_double(payload,size);
handle_lv(payload,size);
handle_slv(payload,size);
handle_slv(payload,size);
handle_double(payload,size);
handle_byte(payload,size);
handle_letohll(payload,size);
handle_slv_vuln(payload,size);
handle_letohll(payload,size);
handle_slv_vuln(payload,size);
handle_letohl(payload,size);
handle_byte(payload,size);
handle_string(payload,size);
handle_ntohll(payload,size);
handle_slv(payload,size);
handle_double(payload,size);
handle_string(payload,size);
handle_ntohs(payload,size);
handle_slv_vuln(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamahemostat(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamahemostat===")-1,"===llamahemostat===");
handle_lv(payload,size);
handle_ntohll(payload,size);
handle_slv(payload,size);
handle_slv(payload,size);
handle_ntohl(payload,size);
handle_lv_vuln(payload,size);
handle_string(payload,size);
handle_float(payload,size);
handle_float(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamadiscretion(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamadiscretion===")-1,"===llamadiscretion===");
handle_lv_vuln(payload,size);
handle_ntohll(payload,size);
handle_byte(payload,size);
handle_ntohs(payload,size);
handle_slv(payload,size);
handle_lv(payload,size);
handle_letohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamamitigate(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamamitigate===")-1,"===llamamitigate===");
handle_slv(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamamachar(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamamachar===")-1,"===llamamachar===");
handle_double(payload,size);
handle_slv_vuln(payload,size);
handle_string(payload,size);
handle_double(payload,size);
handle_ntohs(payload,size);
handle_ntohll(payload,size);
handle_lv(payload,size);
handle_slv_vuln(payload,size);
handle_lv_vuln(payload,size);
handle_double(payload,size);
handle_float(payload,size);
handle_ntohll(payload,size);
handle_letohll(payload,size);
handle_ntohll(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamafactorization(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamafactorization===")-1,"===llamafactorization===");
handle_float(payload,size);
handle_slv(payload,size);
handle_lv_vuln(payload,size);
handle_letohll(payload,size);
handle_ntohs(payload,size);
handle_letohl(payload,size);
handle_ntohll(payload,size);
handle_ntohll(payload,size);
handle_letohl(payload,size);
handle_ntohs(payload,size);
handle_ntohs(payload,size);
handle_letohs(payload,size);
handle_letohl(payload,size);
handle_string_vuln(payload,size);
handle_lv(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaantimaterialistic(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaantimaterialistic===")-1,"===llamaantimaterialistic===");
handle_string(payload,size);
handle_ntohs(payload,size);
handle_string(payload,size);
handle_byte(payload,size);
handle_letohl(payload,size);
handle_ntohs(payload,size);
handle_lv(payload,size);
handle_ntohl(payload,size);
handle_lv(payload,size);
handle_letohll(payload,size);
handle_lv_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_string(payload,size);
handle_lv(payload,size);
handle_lv_vuln(payload,size);
handle_slv_vuln(payload,size);
handle_slv(payload,size);
handle_slv_vuln(payload,size);
handle_lv(payload,size);
handle_slv(payload,size);
handle_ntohl(payload,size);
handle_double(payload,size);
handle_lv(payload,size);
handle_slv(payload,size);
handle_lv_vuln(payload,size);
handle_string(payload,size);
handle_string(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamalowermost(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamalowermost===")-1,"===llamalowermost===");
handle_byte(payload,size);
handle_letohll(payload,size);
handle_ntohll(payload,size);
handle_string(payload,size);
handle_float(payload,size);
handle_letohll(payload,size);
handle_lv(payload,size);
handle_lv(payload,size);
handle_slv(payload,size);
handle_letohl(payload,size);
handle_ntohll(payload,size);
handle_string_vuln(payload,size);
handle_letohs(payload,size);
handle_ntohs(payload,size);
handle_letohs(payload,size);
handle_letohll(payload,size);
handle_letohl(payload,size);
handle_byte(payload,size);
handle_float(payload,size);
handle_double(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamaSoricinae(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamaSoricinae===")-1,"===llamaSoricinae===");
handle_slv_vuln(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}
STACKPROTECTINIT
void process_llamamononomial(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_llamahalochromy};
STACKPROTECTADD
int next = -1;
SSENDL(sizeof("===llamamononomial===")-1,"===llamamononomial===");
next = handle_nextproto_s(payload,size);
handle_string(payload,size);
handle_lv(payload,size);
handle_lv(payload,size);
handle_byte(payload,size);
handle_slv_vuln(payload,size);
handle_slv(payload,size);
handle_ntohs(payload,size);
handle_ntohs(payload,size);

STACKPROTECTCHK
if(*size > 0 && next >= 0 && next < sizeof(next_dissectors)/sizeof(next_dissectors[0])) next_dissectors[next](payload,size);
}

