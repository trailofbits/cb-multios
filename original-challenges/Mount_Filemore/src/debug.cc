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

#include <cstdio.h>
#include "print.h"

void debug_bhdr(const bhdr &header)
{
    printf("****Bios Header Information****\n");
    printf("Bytes per sector: " ESC "d\n", header.bytes_per_sector);
    printf("Sectors per cluster: " ESC "d\n", header.sectors_per_cluster);
    printf("Num reserved sectors: " ESC "d\n", header.num_reserved_sectors);
    printf("Num CgFs tables: " ESC "d\n", header.num_cgfst);
    printf("Num root directories: " ESC "d\n", header.num_root_dirs);
    printf("Total Sectors (<65535): " ESC "d\n", header.total_sectors_small);
    printf("Media Info: " ESC "d\n", header.media_info);
    printf("unused: " ESC "d\n", header.unused);
    printf("unused track info: " ESC "d\n", header.unused_track_info);
    printf("unused partition info: " ESC "d\n", header.unused_partition_info);
    printf("Total Sectors (>65535): " ESC "d\n", header.total_sectors_large);

    printf("\n**Extended CgFs Info**\n");
    printf("Sectors per CgFs Table: " ESC "d\n", header.sectors_per_cgfst);
    printf("Drive Description: " ESC "d\n", header.drive_desc);
    printf("Version: " ESC "d\n", header.version);
    printf("Root Cluster Idx: " ESC "d\n", header.root_cluster_idx);
    printf("FS Info Sector Idx: " ESC "d\n", header.fs_info_sector_idx);
    printf("Boot Copy Sector Idx: " ESC "d\n", header.boot_copy_sector_idx);
    printf("--12 Bytes Reserved--\n");
    printf("--16 Bytes Reserved--\n");
    printf("--FS TYPE--\n");
    PRINT_ARR_CHARS(header.fs_type, sizeof(header.fs_type));

    printf("\n**Boot code and end sequence**\n");
    printf("--Boot Code (419 bytes)--\n");
    printf("End of Header Signature: \\x" ESC "02x\\0x" ESC "02x\n", header.end_signature[0], header.end_signature[1]);
    printf("Total header size: " ESC "d\n", sizeof(header));
    printf("****End Bios Header****\n");
    fflush(stdout);
}

void debug_fs_info(const fs_info_sector &fs_info)
{
    printf("****FS Info Sector****\n");
    printf("--FS Signature 1--\n");
    PRINT_ARR_CHARS(fs_info.signature, sizeof(fs_info.signature));
    printf("--Reserved Space (480 Bytes)--\n");
    printf("--FS Signature 2--\n");
    PRINT_ARR_CHARS(fs_info.signature2, sizeof(fs_info.signature2));
    printf("Num Free Clusters: " ESC "d\n", fs_info.num_free_clusters);
    printf("Most Recent Cluster Allocation: " ESC "d\n", fs_info.most_recent_cluster_alloc);
    printf("--12 Bytes Reserved--\n");
    printf("End of Header Signature: \\x" ESC "02x\\0x" ESC "02x\\x" ESC "02x\\0x" ESC "02x\n", fs_info.end_signature[0], fs_info.end_signature[1],
                                                                        fs_info.end_signature[2], fs_info.end_signature[3]);
    printf("****End FS Info****\n");
    fflush(stdout);

}

void debug_file_metadata(const fs_file *file_metadata)
{
    printf("****File Metadata****\n");
    printf("--File Name--\n");
    PRINT_ARR_CHARS(file_metadata->name, sizeof(file_metadata->name));
    printf("--Attributes--\n");
    PRINT_ARR_BYTES(&file_metadata->attrib, sizeof(file_metadata->attrib));
    printf("Starting Cluster Index: " ESC "d\n", file_metadata->starting_cluster);
    printf("File size = " ESC "d\n", file_metadata->size);
    printf("****End File Metadata****\n");
    fflush(stdout);
}

void debug_file(Array<cluster_data> file_clusters)
{
    printf("****File Hex View****\n");
    for (int i = 0; i < file_clusters.length(); i++) {
        PRINT_ARR_HEXDUMP(file_clusters[i].data, file_clusters[i].cluster_size);
    }
    printf("****End File Hex View****\n");
    fflush(stdout);
}
