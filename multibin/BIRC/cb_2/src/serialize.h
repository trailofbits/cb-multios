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
#ifndef SERIALIZE_H_
#define SERIALIZE_H_
#include "brc_default_codes.h"

#define APPEND_PARAM(_cmd_str, _param, _length) \
    do { \
        unsigned short __temp_length_val = (_length); \
        memcpy((_cmd_str), &__temp_length_val, sizeof((__temp_length_val))); \
        (_cmd_str) += sizeof(__temp_length_val); \
        memcpy((_cmd_str), (_param), __temp_length_val); \
        (_cmd_str) += __temp_length_val; \
    } while(0)

#define ADD_LENGTH(_cur_length, _param_length) \
    do { \
        unsigned short __temp_length_val = (_param_length); \
        (_cur_length) += __temp_length_val + sizeof(__temp_length_val); \
    } while(0)


#define ADD_EOM_LENGTH(_cur_length) \
    do { \
        (_cur_length) += BrcGlobals::eom_length(); \
    } while(0)

#define APPEND_EOM(_cmd_str) \
    do { \
        memcpy((_cmd_str), BrcGlobals::eom(), BrcGlobals::eom_length()); \
        (_cmd_str) += BrcGlobals::eom_length(); \
    } while(0)

#endif /* SERIALIZE_H_ */
