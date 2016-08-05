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

#include "fs_file.h"
#include <cstring.h>

#define GET_BIT(_bit_idx) ((1<<(_bit_idx)) - 1)
#define READONLY_FLAG GET_BIT(1)
#define HIDDEN_FLAG GET_BIT(2)
#define SYSTEM_FLAG GET_BIT(3)
#define VOLUME_LBL_FLAG GET_BIT(4)
#define SUBDIRECTORY_FLAG GET_BIT(5)
#define ARCHIVE_FLAG GET_BIT(6)

#define SKIP_FILE 0xf


namespace CgFsFile
{


bool FreeEntry(const fs_file *file_metadata)
{
    if (file_metadata->name[0] == 0x00 || file_metadata->name[0] == 0xE5)
        return true;

    return false;
}

bool SkipEntry(const fs_file *file_metadata)
{
    if (file_metadata->attrib == 0x0F || file_metadata->name[0] == 0x00 || file_metadata->name[0] == 0xE5)
        return true;

    return false;
}

bool IsDotEntry(const fs_file *file_metadata)
{
    return (file_metadata->name[0] == 0x2E);
}

bool IsDirectory(const fs_file *file_metadata)
{
    return (file_metadata->attrib & SUBDIRECTORY_FLAG);
}

bool IsFile(const fs_file *file_metadata)
{
    return !(file_metadata->attrib & SUBDIRECTORY_FLAG);
}

bool IsSystemFile(const fs_file *file_metadata)
{
    return (file_metadata->attrib & SYSTEM_FLAG);
}

bool IsHiddenFile(const fs_file *file_metadata)
{
    return (file_metadata->attrib & HIDDEN_FLAG);
}

bool IsArchive(const fs_file *file_metadata)
{
    return (file_metadata->attrib & ARCHIVE_FLAG);
}

void DeleteMetadataEntry(fs_file *file_metadata)
{
    file_metadata->name[0] = 0xE5;
}

bool NameEquals(const fs_file *file_metadata, const char *filename, unsigned int name_len)
{
    if (name_len > sizeof(((fs_file *)0)->name))
        return false;
    if (memcmp(file_metadata->name, filename, name_len) != 0)
        return false;
    for (int i = name_len; i < sizeof(((fs_file *)0)->name); i++)
    {
        if (file_metadata->name[i] != 0x20)
            return false;
    }

    return true;
}

}
