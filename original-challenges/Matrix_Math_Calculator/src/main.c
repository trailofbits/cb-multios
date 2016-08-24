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

#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define RANDOM_SHORTS 1024
#define LINE_SIZE 2048
#define SWAP_ROW 1
#define SWAP_COL 2

const int *secret = (const int *)0x4347C000;
//30720 * 36744 = 0x4347C000

unsigned int g_random_usage = 0;

short *create_random_shorts()
{
    uint8_t *secret_page = (uint8_t *)0x4347c000;
    short *prand_shorts = malloc(RANDOM_SHORTS * sizeof(short));
    if (!prand_shorts)
        return NULL;

    for (unsigned int i = 0; i < RANDOM_SHORTS; i++)
        prand_shorts[i] = *(int8_t *)&secret_page[i * 3];
    return prand_shorts;
}

short get_rand_short(short *prandom_data)
{
    if (g_random_usage >= RANDOM_SHORTS)
        g_random_usage = 0;
    return prandom_data[g_random_usage++];
}

static int get_byte()
{
    static unsigned char rxbuf[64];
    static int rxidx;
    static int rxcnt;
    if (rxidx == rxcnt)
    {
        size_t rx;
        if (receive(STDIN, rxbuf, 64, &rx) != 0 || rx == 0)
            return -1;
        rxcnt = rx;
        rxidx = 0;
    }
    return rxbuf[rxidx++];
}

int readline(char *buf, size_t buf_size)
{
    if (!buf || buf_size < 2)
        return -1;

    size_t i = 0;
    for (i = 0; i < buf_size; i++)
    {
        int ch = get_byte();
        if (ch != -1)
        {
            buf[i] = ch;
            if(buf[i] == '\n') {
                buf[i] = '\0';
                break;
            }
        }
        else
        {
            return ERROR;
        }
    }

    if (i == buf_size || i == 0)
        return FAIL;

    return SUCCESS;
}

int readnum(char *buf, size_t buf_size, int *num)
{
    int retval = readline(buf, buf_size);
    if (retval != SUCCESS)
        *num = 0;
    else
        *num = strtol(&buf[0], NULL, 10);

    return retval;
}

int select_menu_choice(char *buf, int buf_size)
{
    int choice = 0;
    printf("Make a selection: \n"
        "1. Input Matrix\n"
        "2. Print Matrix\n"
        "3. Add Matrices\n"
        "4. Subtract Matrices\n"
        "5. Multiply Matrices\n"
        "6. Swap Matrix Row\n"
        "7. Swap Matrix Col\n"
        "8. Transpose Matrix\n"
        "9. Perform Reduced Row Echelon Form on Matrix\n"
        "10. Randomize Matrix\n"
        "11. Exit\n"
        ">> ");

    if (readnum(buf, buf_size, &choice) == ERROR)
        return 11;
    else
        return choice;
}

matrix_t *choose_matrix(matrix_t *m1, matrix_t *m2, char *buf, int buf_size)
{
    int choice = 0, retval = 0;
    printf("Select Matrix 1 or Matrix 2\n"
        ">> ");

    retval = readnum(buf, buf_size, &choice);
    if (retval == ERROR)
        return NULL;
    else
        return choice == 2 ? m2 : m1;
}

int resize_matrix(matrix_t *m, char *buf, int buf_size)
{
    int row = 0, col = 0;
    while (1)
    {
        printf("New Row Size (0 to stay the same): ");
        if (readnum(buf, buf_size, &row) == ERROR)
            return ERROR;
        if (row == 0)
            row = m->num_rows;

        printf("New Column Size (0 to stay the same): ");
        if (readnum(buf, buf_size, &col) == ERROR)
            return ERROR;
        if (col == 0)
            col = m->num_cols;

        if (m->set_rows_cols(m, row, col) != SUCCESS)
            printf("Row and Column Sizes must be between 1-16\n");
        else
            return SUCCESS;
    }
}

int input_matrix(matrix_t *m, char *buf, int buf_size)
{
    if (resize_matrix(m, buf, buf_size) == ERROR)
        return ERROR;

    int num_cells = m->num_rows * m->num_cols;
    int cell_val = 0, retval = 0;
    char *num_str = NULL;

    retval = readline(buf, buf_size);
    if (retval == ERROR || retval == FAIL)
    {
        printf("Bad Input\n");
        return retval;
    }

    int number_count = 1;
    int i, j;

    for (i = 0; i < strlen(buf); i++)
    {
        if (buf[i] == ' ')
            number_count++;
    }

    if (number_count != num_cells)
    {
        printf("Bad Input\n");
        return FAIL;
    }

    for (i = 0; i < m->num_rows; i++)
    {
        for (j = 0; j < m->num_cols; j++)
        {
            num_str = strsep(&buf, " ");
            if (!num_str)
                return ERROR;

            cell_val = strtol(num_str, NULL, 10);
            m->set_cell(m, i, j, cell_val);
        }
    }

    return SUCCESS;
}

int random_matrix(matrix_t *m, char *buf, int buf_size, short *prandom_data)
{
    if (resize_matrix(m, buf, buf_size) == ERROR)
        return ERROR;

    int i, j;
    for (i = 0; i < m->num_rows; i++)
    {
        for (j = 0; j < m->num_cols; j++)
        {
            m->set_cell(m, i, j, get_rand_short(prandom_data));
        }
    }

    return SUCCESS;
}

void print_matrix(char *text, matrix_t *m)
{
    printf("%s\n", text);
    m->print_matrix(m);
}

void print_matrices(matrix_t *m1, matrix_t *m2, matrix_t *m_result)
{
    print_matrix("-Matrix 1-", m1);
    printf("\n");
    print_matrix("-Matrix 2-", m2);
    printf("\n");
    print_matrix("-Resultant Matrix-", m_result);
}

void add_matrices(matrix_t *m1, matrix_t *m2, matrix_t *m_result)
{
    if (m_add(m1, m2, m_result) != SUCCESS)
        printf("Could not add matrices together. Check sizes\n");
    else
        print_matrix("Result:", m_result);

}

void subtract_matrices(matrix_t *m1, matrix_t *m2, matrix_t *m_result)
{
    if (m_subtract(m1, m2, m_result) != SUCCESS)
        printf("Could not subtract matrices. Check sizes\n");
    else
        print_matrix("Result:", m_result);
}

void multiply_matrices(matrix_t *m1, matrix_t *m2, matrix_t *m_result)
{
    if (m_multiply(m1, m2, m_result) != SUCCESS)
        printf("Could not multiply matrices together. Check sizes\n");
    else
        print_matrix("Result:", m_result);
}

int swap_matrix_row_col(matrix_t *m, int row_or_col, char *buf, int buf_size)
{
    int idx1 = 0, idx2 = 0;
    int max_idx = 0;
    char *row_or_col_str;
    if (row_or_col == SWAP_ROW)
    {
        row_or_col_str = "Row";
        max_idx = m->num_rows;
    }
    else if (row_or_col == SWAP_COL)
    {
        row_or_col_str = "Column";
        max_idx = m->num_cols;
    }
    else
    {
        return FAIL;
    }

    printf("Enter %s Index 1: ", row_or_col_str);
    if (readnum(buf, buf_size, &idx1) == ERROR)
        return ERROR;
    if (idx1 >= max_idx)
    {
        printf("Bad Input\n");
        return FAIL;
    }

    printf("Enter %s Index 2: ", row_or_col_str);
    if (readnum(buf, buf_size, &idx2) == ERROR)
        return ERROR;
    if (idx2 >= max_idx)
    {
        printf("Bad Input\n");
        return FAIL;
    }

    print_matrix("Original Matrix", m);
    if (row_or_col == SWAP_ROW)
        return swap_row(m, idx1, idx2);
    if (row_or_col == SWAP_COL)
        return swap_col(m, idx1, idx2);

    return FAIL;
}

void transpose_matrix(matrix_t *m)
{
    print_matrix("Original Matrix", m);
    m_transpose(m);
    print_matrix("Transposed Matrix", m);
}

void rref_matrix(matrix_t *m, matrix_t *m_result)
{
    if (m_rref(m, m_result) != SUCCESS)
        printf("Could not complete reduced row echelon form\n");
    else
        print_matrix("RREF Result:", m_result);
}

int main(void)
{
    int retval = 0;
    int choice = 0;
    short *prandom_data;
#ifdef PATCHED_1
    char m_result_data[MAX_ROWS * MAX_COLS * sizeof(int)];
#else
    char m_result_data[((MAX_ROWS * MAX_COLS) - 1) * sizeof(int)];
#endif

    prandom_data = create_random_shorts();
    matrix_t *m;
    matrix_t *m1, *m2;
    matrix_t *m_result;
    m1 = create_matrix(SHORT, NULL);
    m2 = create_matrix(SHORT, NULL);
    m_result = create_matrix(INT, m_result_data);

    char *input = malloc(2048);
    printf("Matrix math is fun!\n");
    printf("-------------------\n");
    while (1)
    {
        choice = select_menu_choice(input, LINE_SIZE);
        switch(choice)
        {
        case 1:
            printf("Inputting Matrix Values:\n");
            m = choose_matrix(m1, m2, input, LINE_SIZE);
            if (!m)
                goto exit;
            if (input_matrix(m, input, LINE_SIZE) == ERROR)
                goto exit;
            break;
        case 2:
            printf("Print Matrices:\n");
            print_matrices(m1, m2, m_result);
            break;
        case 3:
            printf("Adding Matrices:\n");
            add_matrices(m1, m2, m_result);
            break;
        case 4:
            printf("Subtracting Matrices:\n");
            subtract_matrices(m1, m2, m_result);
            break;
        case 5:
            printf("Multiplying Matrices:\n");
            multiply_matrices(m1, m2, m_result);
            break;
        case 6:
            printf("Swap Rows in a  Matrix:\n");
            m = choose_matrix(m1, m2, input, LINE_SIZE);
            if (!m)
                goto exit;
            retval = swap_matrix_row_col(m, SWAP_ROW, input, LINE_SIZE);
            if (retval == ERROR)
                goto exit;
            if (retval == SUCCESS)
                print_matrix("Swapped Rows", m);
            break;
        case 7:
            printf("Swap Columns in a  Matrix:\n");
            m = choose_matrix(m1, m2, input, LINE_SIZE);
            if (!m)
                goto exit;
            retval = swap_matrix_row_col(m, SWAP_COL, input, LINE_SIZE);
            if (retval == ERROR)
                goto exit;
            if (retval == SUCCESS)
                print_matrix("Swapped Columns", m);
            break;
        case 8:
            printf("Transpose a Matrix:\n");
            m = choose_matrix(m1, m2, input, LINE_SIZE);
            if (!m)
                goto exit;
            transpose_matrix(m);
            break;
        case 9:
            printf("Perform Reduced Row Echelon Form on Matrix\n");
            m = choose_matrix(m1, m2, input, LINE_SIZE);
            if (!m)
                goto exit;
            rref_matrix(m, m_result);
            break;
        case 10:
            printf("Create a Random Matrix:\n");
            m = choose_matrix(m1, m2, input, LINE_SIZE);
            if (!m)
                goto exit;
            if (random_matrix(m, input, LINE_SIZE, prandom_data) == ERROR)
                goto exit;
            break;
        case 11:
            goto exit;
        default:
            printf("Bad Selection\n");
        }
    }

exit:
    printf("Exiting...\n");
    return 0;
}

