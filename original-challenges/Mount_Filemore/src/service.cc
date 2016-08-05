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

#include <cstring.h>
#include <cstdio.h>
#include "bhdr.h"
#include "cgfs.h"
#include "fs_info_sector.h"
#include "print.h"

unsigned int p1, p2;
char *FillBuffer(const char *secret_page, const unsigned int num_bytes)
{
    char *data = new char[num_bytes];
    for (unsigned int i = 0; i < num_bytes; i++)
    {
        p1 = 47070 * (p1 & 65535) + (p1 >> 16);
        p2 = 84818 * (p2 & 65535) + (p2 >> 16);
        unsigned int byte_idx =  ((p1 << 16) + p2) % 4096;
        data[i] = secret_page[byte_idx];
    }
    return data;
}

extern "C" int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
    char *secret_page = (char *)secret_page_i;
    (void) secret_page;
    /* If you want to obfuscate input/output, uncomment and change */
    fxlat(stdin, "2281771");
    fxlat(stdout, "2281771");

    p1 = *((unsigned int *)(&secret_page[400]));
    p2 = *((unsigned int *)(&secret_page[404]));
    fbuffered(stdout, 1);

    printf("MOUNT FILEMORE v 1.0" NL);
    printf(NL NL);

    CgFsImg img;
    char input[1024];
    int exit_program = false;
    bool mounted_fs = false;
    int choice = 0;

    while(!exit_program)
    {
        printf("Options:" NL);
        if (!mounted_fs)
        {
            printf("1. Mount File" NL);
            printf("2. Exit" NL);
            printf(":> ");
            fflush(stdout);
            if (freaduntil(input, sizeof(input), *NL, stdin) < 0)
                break;
            if (input[0] == 0)
                continue;

            choice = strtol(input, NULL, 10);
            if (choice == 1)
            {
                if ((mounted_fs = img.Mount(stdin)))
                    printf("Successfully mounted file system" NL);
                else
                    printf("Could not mount file system" NL);
                fflush(stdout);
            }
            else if (choice == 2)
            {
                exit_program = true;
            }
        }
        else
        {
            printf("1. List File/Directory" NL);
            printf("2. Recursively List Files/Directories" NL);
            printf("3. Preview File" NL);
            printf("4. Read From File" NL);
            printf("5. Write To File" NL);
            printf("6. Update File Size" NL);
            printf("7. Add File" NL);
            printf("8. Add Directory" NL);
            printf("9. Delete File" NL);
            printf("10. Delete Directory" NL);
            printf("11. View Mounted Filesystem Metadata" NL);
            printf("12. Unmount Filesystem" NL);
            printf("13. Exit" NL);
            printf(":> ");
            fflush(stdout);
            if (freaduntil(input, sizeof(input), *NL, stdin) < 0)
                break;
            if (input[0] == 0)
                continue;

            choice = strtol(input, NULL, 10);
            if (choice == 1)
            {
                printf("Enter Path" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(input, sizeof(input), *NL, stdin) <= 0)
                    continue;

                img.ListFiles(input, false);
            }
            else if (choice == 2)
            {
                printf("Enter Path To Recurse" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(input, sizeof(input), *NL, stdin) <= 0)
                    continue;

                img.ListFiles(input, true);
            }
            else if (choice == 3)
            {
                char *file_preview = NULL;
                unsigned int num_bytes = 0;
                printf("Enter Path Of File To Preview" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(input, sizeof(input), *NL, stdin) <= 0)
                    continue;

                if (img.PreviewFile(input, &file_preview, &num_bytes) && file_preview && num_bytes)
                {
                    PRINT_ARR_BYTES(file_preview, num_bytes);
                    fflush(stdout);
                    delete[] file_preview;
                }
            }
            else if (choice == 4)
            {
                char *file_data = NULL;
                char offset_buf[16];
                char bytes_to_read_buf[16];
                unsigned int num_bytes = 0;
                unsigned int offset = 0;
                unsigned int bytes_to_read = 0;
                printf("Enter Path Of File To Read From" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(input, sizeof(input), *NL, stdin) <= 0)
                    continue;

                printf("Enter Offset" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(offset_buf, sizeof(offset_buf), *NL, stdin) <= 0)
                    continue;

                printf("Enter Number Of Bytes To Read" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(bytes_to_read_buf, sizeof(bytes_to_read_buf), *NL, stdin) <= 0)
                    continue;

                offset = strtol(offset_buf, NULL, 10);
                bytes_to_read = strtol(bytes_to_read_buf, NULL, 10);
                if (img.ReadFromFile(input, offset, bytes_to_read,  &file_data, &num_bytes) && file_data && num_bytes)
                {
                    PRINT_ARR_BYTES(file_data, num_bytes);
                    fflush(stdout);
                    delete[] file_data;
                }
            }
            else if (choice == 5)
            {
                char *file_data = NULL;
                char offset_buf[16];
                char bytes_to_write_buf[16];
                unsigned int num_bytes = 0;
                unsigned int offset = 0;
                unsigned int bytes_to_write = 0;
                printf("Enter Path Of File To Write To" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(input, sizeof(input), *NL, stdin) <= 0)
                    continue;

                printf("Enter Offset" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(offset_buf, sizeof(offset_buf), *NL, stdin) <= 0)
                    continue;

                printf("Enter Number Of Bytes To Write" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(bytes_to_write_buf, sizeof(bytes_to_write_buf), *NL, stdin) <= 0)
                    continue;

                offset = strtol(offset_buf, NULL, 10);
                bytes_to_write= strtol(bytes_to_write_buf, NULL, 10);

                if (!bytes_to_write)
                    continue;

                file_data = new char[bytes_to_write];
                printf("Enter File Data To Be Written: [" ESC "d bytes]" NL, bytes_to_write);
                fflush(stdout);
                if (fread(file_data, bytes_to_write, stdin) <= 0)
                {
                    delete[] file_data;
                    continue;
                }

                if (img.WriteToFile(input, offset, bytes_to_write,  file_data, &num_bytes) && num_bytes)
                {
                    printf("Successfully wrote: " NL);
                    PRINT_ARR_BYTES(file_data, num_bytes);
                    fflush(stdout);
                }
                delete[] file_data;
            }
            else if (choice == 6)
            {
                char new_size_buf[16];
                unsigned int new_size = 0;
                printf("Enter Path Of File To Update" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(input, sizeof(input), *NL, stdin) <= 0)
                    continue;

                printf("Enter New Size" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(new_size_buf, sizeof(new_size_buf), *NL, stdin) <= 0)
                    continue;

                new_size = strtol(new_size_buf, NULL, 10);
                if (img.UpdateFileSize(input, new_size))
                {
                    printf("File " ESC "s has a new file size of: " ESC "d" NL, input, new_size);
                    fflush(stdout);
                }
                else
                {
                    printf("Could not update file size" NL);
                    fflush(stdout);
                }
            }
            else if (choice == 7)
            {
                const unsigned int max_file_name = sizeof(((fs_file *)0)->name);
                char *file_data = NULL;
                char filename_buf[max_file_name + 1];
                memset(filename_buf, 0, sizeof(filename_buf));
                char file_size_buf[16];
                char add_data_yn_buf[16];
                unsigned int file_size;
                unsigned int add_data_yn;
                printf("Enter Parent Directory Of New File" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(input, sizeof(input), *NL, stdin) <= 0)
                    continue;

                printf("Enter Name Of New File" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(filename_buf, sizeof(filename_buf), *NL, stdin) <= 0)
                    continue;
                printf("Enter Size Of New File" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(file_size_buf, sizeof(file_size_buf), *NL, stdin) <= 0)
                    continue;

                printf("Input File Data?" NL);
                printf("1. Yes" NL);
                printf("2. No" NL);
                printf("3. Fill With Random Data" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(add_data_yn_buf, sizeof(add_data_yn_buf), *NL, stdin) <= 0)
                    continue;

                file_size = strtol(file_size_buf, NULL, 10);
                add_data_yn = strtol(add_data_yn_buf, NULL, 10);

                if (add_data_yn == 1)
                {
                    file_data = new char[file_size];
                    printf("Enter File Data To Be Written: [" ESC "d bytes]" NL, file_size);
                    fflush(stdout);
                    if (fread(file_data, file_size, stdin) <= 0)
                    {
                        delete[] file_data;
                        continue;
                    }
                }
                else if (add_data_yn == 3)
                {
                    file_data = FillBuffer(secret_page, file_size);
                }

                if (img.AddFile(input, filename_buf, file_data, file_size))
                {
                    printf("Successfully added file" NL);
                    printf("Parent dir: " ESC "s" NL, input);
                    printf("New file name: ");
                    PRINT_ARR_CHARS(filename_buf, strlen(filename_buf));

                    if (file_data)
                    {
                        printf("Data written to disk: " NL);
                        PRINT_ARR_BYTES(file_data, file_size);
                    }
                    fflush(stdout);
                }
                if (file_data)
                    delete[] file_data;

            }
            else if (choice == 8)
            {
                const unsigned int max_dir_name = sizeof(((fs_file *)0)->name);
                char dirname_buf[max_dir_name+1];
                memset(dirname_buf, 0, sizeof(dirname_buf));
                printf("Enter Parent Directory Of New Directory" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(input, sizeof(input), *NL, stdin) <= 0)
                    continue;

                printf("Enter Name Of New Directory" NL);
                printf(":> ");
                fflush(stdout);
                if (freaduntil(dirname_buf, sizeof(dirname_buf), *NL, stdin) <= 0)
                    continue;

                if (img.AddDirectory(input, dirname_buf))
                {
                    printf("Successfully added directory" NL);
                    printf("Parent dir: " ESC "s" NL, input);
                    printf("New directory name: ");
                    PRINT_ARR_CHARS(dirname_buf, strlen(dirname_buf));
                    fflush(stdout);
                }
            }
            else if (choice == 9)
            {
                printf("Enter Path Of File To Delete" NL);
                printf(":> ");
                fflush(stdout);

                if (freaduntil(input, sizeof(input), *NL, stdin) <= 0)
                    continue;

                if (img.DeleteFile(input))
                {
                    printf("Successfully deleted file" NL);
                    printf("Deleted file: " ESC "s" NL, input);
                    fflush(stdout);
                }
            }
            else if (choice == 10)
            {
                printf("Enter Path Of Directory To Delete" NL);
                printf(":> ");
                fflush(stdout);

                if (freaduntil(input, sizeof(input), *NL, stdin) <= 0)
                    continue;

                if (img.DeleteDirectory(input))
                {
                    printf("Successfully deleted directory" NL);
                    printf("Deleted directory: " ESC "s" NL, input);
                    fflush(stdout);
                }
            }
            else if (choice == 11)
            {
                img.DebugMetadata();
            }
            else if (choice == 12)
            {
                if (img.Unmount())
                    mounted_fs = false;

                if (!mounted_fs)
                    printf("Successfully unmounted file system" NL);
                else
                    printf("Could not unmount file system" NL);
                fflush(stdout);
            }
            else if (choice == 13)
            {
                exit_program = true;
            }
        }
    }

    printf("Exiting...." NL);
    fflush(stdout);

    return 0;
}
