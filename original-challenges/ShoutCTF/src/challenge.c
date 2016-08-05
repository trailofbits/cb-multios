/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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

#include <string.h>

#include "challenge.h"

const char* chal_cat_to_string(category_t cat)
{
    switch (cat)
    {
        case CAT_CRYPTO:
            return "Crypto";
        case CAT_PWNABLE:
            return "Pwnable";
        case CAT_FORENSICS:
            return "Forensics";
        case CAT_WEB:
            return "Web";
        case CAT_NETWORK:
            return "Network";
        case CAT_REVERSING:
            return "Reversing";
        case CAT_MISC:
            return "Misc.";
        default:
            return "Unknown";
    }
}

const char* chal_status_to_string(chal_stat_t stat)
{
    switch (stat)
    {
        case CSTAT_LOCKED:
            return "Locked";
        case CSTAT_SOLVED:
            return "Solved";
        case CSTAT_SOLVED_U:
            return "Cleared";
        case CSTAT_OPEN:
            return "Open";
        default:
            return "Unknown";
    }
}

