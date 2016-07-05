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
#include <libcgc.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "accel.h"
#include "accelio.h"
#include "convert.h"

#define ASSIGN "ASSIGN"
#define CLEAR "CLEAR "
#define REPR "REPR "
#define SHOW "SHOW "
#define TABLE "TABLE"
#define EXIT "EXIT"

#define BAD_CLEAR_CMD -8
#define BAD_ASSIGN_CMD -4
#define BAD_SHOW_CMD -2
#define BAD_INPUT -1
#define CMD_SUCCESS 0
#define EXIT_CODE 1

#define LINE_SIZE 512

static void print_table() {
   print_assigned_cells();
}

static int readline(int fd, char *line, size_t line_size)
{
    size_t i;
    size_t rx;

    for (i = 0; i < line_size; i++) {
        if (receive(fd, line, 1, &rx) != 0 || rx == 0)
            exit(0);
        if (*line == '\n')
            break;
        line++;
    }

    if (i == line_size && *line != '\n')
        return -1;
    else if (*line != '\n')
        return 1;
    else
        *line = '\0';

    return 0;
}

static int parse_line(char *line)
{
    int is_repr = 0;
    size_t i;
    char tmp[32];
    char *tok;
    char val_str[LINE_SIZE];
    char *cell_str;

    if (strtrim(line, LINE_SIZE, TRIM_FRONT) == -1)
        return BAD_INPUT;

    memcpy(tmp, line, strlen(SHOW));
    for (i = 0; i < strlen(SHOW); i++)
        tmp[i] = toupper(tmp[i]);

    if (memcmp(tmp, SHOW, strlen(SHOW)) == 0)
        goto show_cmd;

    memcpy(tmp, line, strlen(REPR));
    for (i = 0; i < strlen(REPR); i++)
        tmp[i] = toupper(tmp[i]);

    if (memcmp(tmp, REPR, strlen(REPR)) == 0) {
        is_repr = 1;
        goto show_cmd;
    }

    memcpy(tmp, line, strlen(CLEAR));
    for (i = 0; i < strlen(CLEAR); i++)
        tmp[i] = toupper(tmp[i]);

    if (memcmp(tmp, CLEAR, strlen(CLEAR)) == 0)
        goto clear_cmd;

    // Use sizeof to include null terminator (vs strlen)
    memcpy(tmp, line, sizeof(EXIT));
    for (i = 0; i < sizeof(EXIT); i++)
        tmp[i] = toupper(tmp[i]);

    if (memcmp(tmp, EXIT, sizeof(EXIT)) == 0)
        goto exit_cmd;

    goto assign_cmd;

show_cmd:
    strtrim(line, LINE_SIZE, TRIM_BACK);
    memcpy(tmp, &line[strlen(SHOW)], sizeof(TABLE));
    for (i = 0; i < sizeof(TABLE); i++)
        tmp[i] = toupper(tmp[i]);

    // Use sizeof to include null terminator (vs strlen)
    if (memcmp(tmp, TABLE, sizeof(TABLE)) == 0) {
        print_table();
        return CMD_SUCCESS;
    } else if (valid_cell_id(&line[strlen(SHOW)]) != -1) {
        cell_str = show_cell(&line[strlen(SHOW)], is_repr, val_str, LINE_SIZE);
        if (is_repr)
            printf("Cell Repr: %s\n", cell_str);
        else
            printf("Cell Value: %s\n", cell_str);
        return CMD_SUCCESS;
    } else {
        return BAD_SHOW_CMD;
    }

clear_cmd:
    if (clear_cell(&line[strlen(CLEAR)]) != 0)
        return BAD_CLEAR_CMD;

    return CMD_SUCCESS;

assign_cmd:
    tok = strsep(&line, "=");
    if (tok == NULL || line == NULL)
        return BAD_INPUT;

    if (set_cell(tok, line, LINE_SIZE) != 0)
        return BAD_ASSIGN_CMD;

    return CMD_SUCCESS;

exit_cmd:
    return EXIT_CODE;
}

int main(void) {
    char line[LINE_SIZE];
    init_sheet();
    int exit = 0;
    int line_status;

    do {
        printf("Accel:-$ ");
        line_status = readline(STDIN, line, LINE_SIZE);
        if(line_status != 0) {
            printf("\n");
            continue;
        }

        switch (parse_line(line)) {
            case BAD_CLEAR_CMD:
                printf("Error clearing cell\n");
                break;
            case BAD_ASSIGN_CMD:
                printf("Error assigning cell. Valid Cells: A0-ZZ99\n");
                break;
            case BAD_SHOW_CMD:
                printf("Error showing data. Try SHOW TABLE or SHOW [A0-ZZ99]\n");
                break;
            case BAD_INPUT:
                printf("Bad input\n");
                break;
            case CMD_SUCCESS:
                printf("Success.\n");
                break;
            case EXIT_CODE:
                exit = 1;
                printf("Exiting...\n");
                return 0;
            default:
                printf("Unknown Input\n");
                break;
        }
    } while (!exit);

    printf("Unsupported signal. Exiting...\n");
    return 0;
}

