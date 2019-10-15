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
#ifndef DESERIALIZE_H_
#define DESERIALIZE_H_

#define PRINT_PARAM(_param, _param_len, _str) \
    do { \
        PRINTF("Received %s\n", (_str)); \
        PRINTF("%s Len = %u\n", (_str), (_param_len)); \
        print_byte_array((char *)(_param), (_param_len)); \
    } while(0)

#define PARSE_SERVER_ADDR(_pcmd, _server_addr) \
    do { \
        (_server_addr) = *((int *)(_pcmd)); \
        (_pcmd) += sizeof(int); \
    } while(0)

#define PARSE_USHORT(_pcmd, _ushort_val) \
    do { \
        (_ushort_val) = *((unsigned short *)(_pcmd)); \
        (_pcmd) += sizeof(unsigned short); \
    } while(0)

#define PARSE_PARAM(_pcmd, _pparam, _paramlen) \
    do { \
        (_paramlen) = *((unsigned short*)(_pcmd)); \
        (_pcmd) += sizeof(unsigned short); \
        if ((_paramlen)) { \
            _pparam = _pcmd; \
        } else { \
            (_pparam) = (char *)NULL; \
        } \
        (_pcmd) += (_paramlen);\
    } while(0)

#define PARSE_EOM(_pcmd, _success) \
    do { \
        unsigned short __eom_len = *((unsigned short*)(_pcmd)); \
        (_pcmd) += sizeof(unsigned short); \
        (_success) = __eom_len ? 0 : 1;\
    } while(0)


#endif /* DESERIALIZE_H_ */
