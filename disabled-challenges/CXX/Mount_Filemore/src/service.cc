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

#include "cgc_cstring.h"
#include "cgc_cstdio.h"
#include "cgc_bhdr.h"
#include "cgc_cgfs.h"
#include "cgc_fs_info_sector.h"
#include "cgc_print.h"
#include "cgc__defines.h"

unsigned int cgc_p1, cgc_p2;
char *FillBuffer(const char *secret_page, const unsigned int num_bytes)
{
    char *data = new char[num_bytes];
    for (unsigned int i = 0; i < num_bytes; i++)
    {
        cgc_p1 = 47070 * (cgc_p1 & 65535) + (cgc_p1 >> 16);
        cgc_p2 = 84818 * (cgc_p2 & 65535) + (cgc_p2 >> 16);
        unsigned int byte_idx =  ((cgc_p1 << 16) + cgc_p2) % 4096;
        data[i] = secret_page[byte_idx];
    }
    return data;
}

extern "C" int main(int secret_page_i,  char *unused[]) {
    secret_page_i = CGC_FLAG_PAGE_ADDRESS;

    char *secret_page = (char *)secret_page_i;
    (void) secret_page;
    /* If you want to obfuscate input/output, uncomment and change */
    cgc_fxlat(cgc_stdin, "2281771");
    cgc_fxlat(cgc_stdout, "2281771");

    cgc_p1 = *((unsigned int *)(&secret_page[400]));
    cgc_p2 = *((unsigned int *)(&secret_page[404]));
    cgc_fbuffered(cgc_stdout, 1);

    cgc_printf("MOUNT FILEMORE v 1.0" NL);
    cgc_printf(NL NL);

    CgFsImg img;
    char input[1024];
    int exit_program = false;
    bool mounted_fs = false;
    int choice = 0;

    while(!exit_program)
    {
        cgc_printf("Options:" NL);
        if (!mounted_fs)
        {
            cgc_printf("1. Mount File" NL);
            cgc_printf("2. Exit" NL);
            cgc_printf(":> ");
            cgc_fflush(cgc_stdout);
            if (cgc_freaduntil(input, sizeof(input), *NL, cgc_stdin) < 0)
                break;
            if (input[0] == 0)
                continue;

            choice = cgc_strtol(input, NULL, 10);
            if (choice == 1)
            {
                if ((mounted_fs = img.Mount(cgc_stdin)))
                    cgc_printf("Successfully mounted file system" NL);
                else
                    cgc_printf("Could not mount file system" NL);
                cgc_fflush(cgc_stdout);
            }
            else if (choice == 2)
            {
                exit_program = true;
            }
        }
        else
        {
            cgc_printf("1. List File/Directory" NL);
            cgc_printf("2. Recursively List Files/Directories" NL);
            cgc_printf("3. Preview File" NL);
            cgc_printf("4. Read From File" NL);
            cgc_printf("5. Write To File" NL);
            cgc_printf("6. Update File Size" NL);
            cgc_printf("7. Add File" NL);
            cgc_printf("8. Add Directory" NL);
            cgc_printf("9. Delete File" NL);
            cgc_printf("10. Delete Directory" NL);
            cgc_printf("11. View Mounted Filesystem Metadata" NL);
            cgc_printf("12. Unmount Filesystem" NL);
            cgc_printf("13. Exit" NL);
            cgc_printf(":> ");
            cgc_fflush(cgc_stdout);
            if (cgc_freaduntil(input, sizeof(input), *NL, cgc_stdin) < 0)
                break;
            if (input[0] == 0)
                continue;

            choice = cgc_strtol(input, NULL, 10);
            if (choice == 1)
            {
                cgc_printf("Enter Path" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(input, sizeof(input), *NL, cgc_stdin) <= 0)
                    continue;

                img.ListFiles(input, false);
            }
            else if (choice == 2)
            {
                cgc_printf("Enter Path To Recurse" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(input, sizeof(input), *NL, cgc_stdin) <= 0)
                    continue;

                img.ListFiles(input, true);
            }
            else if (choice == 3)
            {
                char *file_preview = NULL;
                unsigned int num_bytes = 0;
                cgc_printf("Enter Path Of File To Preview" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(input, sizeof(input), *NL, cgc_stdin) <= 0)
                    continue;

                if (img.PreviewFile(input, &file_preview, &num_bytes) && file_preview && num_bytes)
                {
                    PRINT_ARR_BYTES(file_preview, num_bytes);
                    cgc_fflush(cgc_stdout);
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
                cgc_printf("Enter Path Of File To Read From" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(input, sizeof(input), *NL, cgc_stdin) <= 0)
                    continue;

                cgc_printf("Enter Offset" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(offset_buf, sizeof(offset_buf), *NL, cgc_stdin) <= 0)
                    continue;

                cgc_printf("Enter Number Of Bytes To Read" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(bytes_to_read_buf, sizeof(bytes_to_read_buf), *NL, cgc_stdin) <= 0)
                    continue;

                offset = cgc_strtol(offset_buf, NULL, 10);
                bytes_to_read = cgc_strtol(bytes_to_read_buf, NULL, 10);
                if (img.ReadFromFile(input, offset, bytes_to_read,  &file_data, &num_bytes) && file_data && num_bytes)
                {
                    PRINT_ARR_BYTES(file_data, num_bytes);
                    cgc_fflush(cgc_stdout);
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
                cgc_printf("Enter Path Of File To Write To" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(input, sizeof(input), *NL, cgc_stdin) <= 0)
                    continue;

                cgc_printf("Enter Offset" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(offset_buf, sizeof(offset_buf), *NL, cgc_stdin) <= 0)
                    continue;

                cgc_printf("Enter Number Of Bytes To Write" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(bytes_to_write_buf, sizeof(bytes_to_write_buf), *NL, cgc_stdin) <= 0)
                    continue;

                offset = cgc_strtol(offset_buf, NULL, 10);
                bytes_to_write= cgc_strtol(bytes_to_write_buf, NULL, 10);

                if (!bytes_to_write)
                    continue;

                file_data = new char[bytes_to_write];
                cgc_printf("Enter File Data To Be Written: [" ESC "d bytes]" NL, bytes_to_write);
                cgc_fflush(cgc_stdout);
                if (cgc_fread(file_data, bytes_to_write, cgc_stdin) <= 0)
                {
                    delete[] file_data;
                    continue;
                }

                if (img.WriteToFile(input, offset, bytes_to_write,  file_data, &num_bytes) && num_bytes)
                {
                    cgc_printf("Successfully wrote: " NL);
                    PRINT_ARR_BYTES(file_data, num_bytes);
                    cgc_fflush(cgc_stdout);
                }
                delete[] file_data;
            }
            else if (choice == 6)
            {
                char new_size_buf[16];
                unsigned int new_size = 0;
                cgc_printf("Enter Path Of File To Update" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(input, sizeof(input), *NL, cgc_stdin) <= 0)
                    continue;

                cgc_printf("Enter New Size" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(new_size_buf, sizeof(new_size_buf), *NL, cgc_stdin) <= 0)
                    continue;

                new_size = cgc_strtol(new_size_buf, NULL, 10);
                if (img.UpdateFileSize(input, new_size))
                {
                    cgc_printf("File " ESC "s has a new file size of: " ESC "d" NL, input, new_size);
                    cgc_fflush(cgc_stdout);
                }
                else
                {
                    cgc_printf("Could not update file size" NL);
                    cgc_fflush(cgc_stdout);
                }
            }
            else if (choice == 7)
            {
                const unsigned int max_file_name = sizeof(((fs_file *)0)->name);
                char *file_data = NULL;
                char filename_buf[max_file_name + 1];
                cgc_memset(filename_buf, 0, sizeof(filename_buf));
                char file_size_buf[16];
                char add_data_yn_buf[16];
                unsigned int file_size;
                unsigned int add_data_yn;
                cgc_printf("Enter Parent Directory Of New File" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(input, sizeof(input), *NL, cgc_stdin) <= 0)
                    continue;

                cgc_printf("Enter Name Of New File" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(filename_buf, sizeof(filename_buf), *NL, cgc_stdin) <= 0)
                    continue;
                cgc_printf("Enter Size Of New File" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(file_size_buf, sizeof(file_size_buf), *NL, cgc_stdin) <= 0)
                    continue;

                cgc_printf("Input File Data?" NL);
                cgc_printf("1. Yes" NL);
                cgc_printf("2. No" NL);
                cgc_printf("3. Fill With Random Data" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(add_data_yn_buf, sizeof(add_data_yn_buf), *NL, cgc_stdin) <= 0)
                    continue;

                file_size = cgc_strtol(file_size_buf, NULL, 10);
                add_data_yn = cgc_strtol(add_data_yn_buf, NULL, 10);

                if (add_data_yn == 1)
                {
                    file_data = new char[file_size];
                    cgc_printf("Enter File Data To Be Written: [" ESC "d bytes]" NL, file_size);
                    cgc_fflush(cgc_stdout);
                    if (cgc_fread(file_data, file_size, cgc_stdin) <= 0)
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
                    cgc_printf("Successfully added file" NL);
                    cgc_printf("Parent dir: " ESC "s" NL, input);
                    cgc_printf("New file name: ");
                    PRINT_ARR_CHARS(filename_buf, cgc_strlen(filename_buf));

                    if (file_data)
                    {
                        cgc_printf("Data written to disk: " NL);
                        PRINT_ARR_BYTES(file_data, file_size);
                    }
                    cgc_fflush(cgc_stdout);
                }
                if (file_data)
                    delete[] file_data;

            }
            else if (choice == 8)
            {
                const unsigned int max_dir_name = sizeof(((fs_file *)0)->name);
                char dirname_buf[max_dir_name+1];
                cgc_memset(dirname_buf, 0, sizeof(dirname_buf));
                cgc_printf("Enter Parent Directory Of New Directory" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(input, sizeof(input), *NL, cgc_stdin) <= 0)
                    continue;

                cgc_printf("Enter Name Of New Directory" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);
                if (cgc_freaduntil(dirname_buf, sizeof(dirname_buf), *NL, cgc_stdin) <= 0)
                    continue;

                if (img.AddDirectory(input, dirname_buf))
                {
                    cgc_printf("Successfully added directory" NL);
                    cgc_printf("Parent dir: " ESC "s" NL, input);
                    cgc_printf("New directory name: ");
                    PRINT_ARR_CHARS(dirname_buf, cgc_strlen(dirname_buf));
                    cgc_fflush(cgc_stdout);
                }
            }
            else if (choice == 9)
            {
                cgc_printf("Enter Path Of File To Delete" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);

                if (cgc_freaduntil(input, sizeof(input), *NL, cgc_stdin) <= 0)
                    continue;

                if (img.DeleteFile(input))
                {
                    cgc_printf("Successfully deleted file" NL);
                    cgc_printf("Deleted file: " ESC "s" NL, input);
                    cgc_fflush(cgc_stdout);
                }
            }
            else if (choice == 10)
            {
                cgc_printf("Enter Path Of Directory To Delete" NL);
                cgc_printf(":> ");
                cgc_fflush(cgc_stdout);

                if (cgc_freaduntil(input, sizeof(input), *NL, cgc_stdin) <= 0)
                    continue;

                if (img.DeleteDirectory(input))
                {
                    cgc_printf("Successfully deleted directory" NL);
                    cgc_printf("Deleted directory: " ESC "s" NL, input);
                    cgc_fflush(cgc_stdout);
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
                    cgc_printf("Successfully unmounted file system" NL);
                else
                    cgc_printf("Could not unmount file system" NL);
                cgc_fflush(cgc_stdout);
            }
            else if (choice == 13)
            {
                exit_program = true;
            }
        }
    }

    cgc_printf("Exiting...." NL);
    cgc_fflush(cgc_stdout);

    return 0;
}
