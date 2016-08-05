/*

Author: Debbie Nuttall <debbie@cromulence.com>

Copyright (c) 2016 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#ifndef SHELL_H
#define SHELL_H

#define DELIM '\n'

// Possible Commands
#define UPLOAD_A_FILE   'u'
#define READ_A_FILE     'r'
#define DELETE_A_FILE   'd'
#define LIST_FILES      'l'
#define LIST_FILES_LONG 'g'
#define CREATE_DIR      'c'
#define PWD             'w'
#define CHANGE_DIR      'h'
#define EXIT_CMD        'x'

#define SHORTCUT_MAGIC 0x4c494e4b

#pragma pack(push,1)
typedef struct ShortcutFileHeader_s {
  uint32_t size;
  uint32_t magic;
  char targetName[65];
  uint32_t index;
  uint16_t numResources;
} ShortcutFileHeader;

void ListFilesRecurse(FileNode *file, int level);
void ListFilesLong(FileNode *parent);
void ExtractLinkTargetAndID(ShortcutFileHeader *sh, FileNode *parent, ExecutableInMemory **flavorSL, int *index);
ExecutableInMemory *VerifyAndLoadFlavorFile(char *name, FileNode *parent);
char ReceiveCommand();

#endif