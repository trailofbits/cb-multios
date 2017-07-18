/*
 * Copyright (c) 2016 Kaprica Security, Inc.
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

#ifndef BHDR_H_
#define BHDR_H_

#pragma pack(push, 1)
struct bhdr
{
    unsigned char jmp_ins[3];
    unsigned char name[8];

    unsigned char sectors_per_cluster;    //1
    unsigned short num_reserved_sectors;
    unsigned short bytes_per_sector;   //512
    unsigned char num_cgfst;
    unsigned short num_root_dirs;
    unsigned short total_sectors_small;   //if zero refer to total_sectors_large;
    unsigned char media_info;
    unsigned short unused;
    unsigned short unused_track_info;
    unsigned short unused_head_info;
    unsigned int unused_partition_info;
    unsigned int total_sectors_large;

    unsigned int root_cluster_idx;
    unsigned short drive_desc;
    unsigned short version;
    unsigned int sectors_per_cgfst;
    unsigned short fs_info_sector_idx;
    unsigned short boot_copy_sector_idx;
    unsigned char reserved[12];
    unsigned char cf_cgfst16_32[18];
    unsigned char fs_type[8];

    unsigned char unused_boot_code[419];

    unsigned char drive_num;
    unsigned char end_signature[2]; // {0x55, 0xAA}
};
#pragma pack(pop)

#endif

