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

#include "cgc_matrix.h"
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_stdint.h"
#include "cgc_string.h"

#define RANDOM_SHORTS 1024
#define LINE_SIZE 2048
#define SWAP_ROW 1
#define SWAP_COL 2

const int *secret = (const int *)0x4347C000;
//30720 * 36744 = 0x4347C000

unsigned int cgc_g_random_usage = 0;

short *cgc_create_random_shorts()
{
    uint8_t *secret_page = (uint8_t *)0x4347c000;
    short *prand_shorts = cgc_malloc(RANDOM_SHORTS * sizeof(short));
    if (!prand_shorts)
        return NULL;

    for (unsigned int i = 0; i < RANDOM_SHORTS; i++)
        prand_shorts[i] = *(int8_t *)&secret_page[i * 3];
    return prand_shorts;
}

short cgc_get_rand_short(short *prandom_data)
{
    if (cgc_g_random_usage >= RANDOM_SHORTS)
        cgc_g_random_usage = 0;
    return prandom_data[cgc_g_random_usage++];
}

static int cgc_get_byte()
{
    static unsigned char rxbuf[64];
    static int rxidx;
    static int rxcnt;
    if (rxidx == rxcnt)
    {
        cgc_size_t rx;
        if (cgc_receive(STDIN, rxbuf, 64, &rx) != 0 || rx == 0)
            return -1;
        rxcnt = rx;
        rxidx = 0;
    }
    return rxbuf[rxidx++];
}

int cgc_readline(char *buf, cgc_size_t buf_size)
{
    if (!buf || buf_size < 2)
        return -1;

    cgc_size_t i = 0;
    for (i = 0; i < buf_size; i++)
    {
        int ch = cgc_get_byte();
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

int cgc_readnum(char *buf, cgc_size_t buf_size, int *num)
{
    int retval = cgc_readline(buf, buf_size);
    if (retval != SUCCESS)
        *num = 0;
    else
        *num = cgc_strtol(&buf[0], NULL, 10);

    return retval;
}

int cgc_select_menu_choice(char *buf, int buf_size)
{
    int choice = 0;
    cgc_printf("Make a selection: \n"
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

    if (cgc_readnum(buf, buf_size, &choice) == ERROR)
        return 11;
    else
        return choice;
}

matrix_t *cgc_choose_matrix(matrix_t *m1, matrix_t *m2, char *buf, int buf_size)
{
    int choice = 0, retval = 0;
    cgc_printf("Select Matrix 1 or Matrix 2\n"
        ">> ");

    retval = cgc_readnum(buf, buf_size, &choice);
    if (retval == ERROR)
        return NULL;
    else
        return choice == 2 ? m2 : m1;
}

int cgc_resize_matrix(matrix_t *m, char *buf, int buf_size)
{
    int row = 0, col = 0;
    while (1)
    {
        cgc_printf("New Row Size (0 to stay the same): ");
        if (cgc_readnum(buf, buf_size, &row) == ERROR)
            return ERROR;
        if (row == 0)
            row = m->num_rows;

        cgc_printf("New Column Size (0 to stay the same): ");
        if (cgc_readnum(buf, buf_size, &col) == ERROR)
            return ERROR;
        if (col == 0)
            col = m->num_cols;

        if (m->set_rows_cols(m, row, col) != SUCCESS)
            cgc_printf("Row and Column Sizes must be between 1-16\n");
        else
            return SUCCESS;
    }
}

int cgc_input_matrix(matrix_t *m, char *buf, int buf_size)
{
    if (cgc_resize_matrix(m, buf, buf_size) == ERROR)
        return ERROR;

    int num_cells = m->num_rows * m->num_cols;
    int cell_val = 0, retval = 0;
    char *num_str = NULL;

    retval = cgc_readline(buf, buf_size);
    if (retval == ERROR || retval == FAIL)
    {
        cgc_printf("Bad Input\n");
        return retval;
    }

    int number_count = 1;
    int i, j;

    for (i = 0; i < cgc_strlen(buf); i++)
    {
        if (buf[i] == ' ')
            number_count++;
    }

    if (number_count != num_cells)
    {
        cgc_printf("Bad Input\n");
        return FAIL;
    }

    for (i = 0; i < m->num_rows; i++)
    {
        for (j = 0; j < m->num_cols; j++)
        {
            num_str = cgc_strsep(&buf, " ");
            if (!num_str)
                return ERROR;

            cell_val = cgc_strtol(num_str, NULL, 10);
            m->set_cell(m, i, j, cell_val);
        }
    }

    return SUCCESS;
}

int cgc_random_matrix(matrix_t *m, char *buf, int buf_size, short *prandom_data)
{
    if (cgc_resize_matrix(m, buf, buf_size) == ERROR)
        return ERROR;

    int i, j;
    for (i = 0; i < m->num_rows; i++)
    {
        for (j = 0; j < m->num_cols; j++)
        {
            m->set_cell(m, i, j, cgc_get_rand_short(prandom_data));
        }
    }

    return SUCCESS;
}

void cgc_print_matrix(char *text, matrix_t *m)
{
    cgc_printf("%s\n", text);
    m->print_matrix(m);
}

void cgc_print_matrices(matrix_t *m1, matrix_t *m2, matrix_t *m_result)
{
    cgc_print_matrix("-Matrix 1-", m1);
    cgc_printf("\n");
    cgc_print_matrix("-Matrix 2-", m2);
    cgc_printf("\n");
    cgc_print_matrix("-Resultant Matrix-", m_result);
}

void cgc_add_matrices(matrix_t *m1, matrix_t *m2, matrix_t *m_result)
{
    if (cgc_m_add(m1, m2, m_result) != SUCCESS)
        cgc_printf("Could not add matrices together. Check sizes\n");
    else
        cgc_print_matrix("Result:", m_result);

}

void cgc_subtract_matrices(matrix_t *m1, matrix_t *m2, matrix_t *m_result)
{
    if (cgc_m_subtract(m1, m2, m_result) != SUCCESS)
        cgc_printf("Could not subtract matrices. Check sizes\n");
    else
        cgc_print_matrix("Result:", m_result);
}

void cgc_multiply_matrices(matrix_t *m1, matrix_t *m2, matrix_t *m_result)
{
    if (cgc_m_multiply(m1, m2, m_result) != SUCCESS)
        cgc_printf("Could not multiply matrices together. Check sizes\n");
    else
        cgc_print_matrix("Result:", m_result);
}

int cgc_swap_matrix_row_col(matrix_t *m, int row_or_col, char *buf, int buf_size)
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

    cgc_printf("Enter %s Index 1: ", row_or_col_str);
    if (cgc_readnum(buf, buf_size, &idx1) == ERROR)
        return ERROR;
    if (idx1 >= max_idx)
    {
        cgc_printf("Bad Input\n");
        return FAIL;
    }

    cgc_printf("Enter %s Index 2: ", row_or_col_str);
    if (cgc_readnum(buf, buf_size, &idx2) == ERROR)
        return ERROR;
    if (idx2 >= max_idx)
    {
        cgc_printf("Bad Input\n");
        return FAIL;
    }

    cgc_print_matrix("Original Matrix", m);
    if (row_or_col == SWAP_ROW)
        return cgc_swap_row(m, idx1, idx2);
    if (row_or_col == SWAP_COL)
        return cgc_swap_col(m, idx1, idx2);

    return FAIL;
}

void cgc_transpose_matrix(matrix_t *m)
{
    cgc_print_matrix("Original Matrix", m);
    cgc_m_transpose(m);
    cgc_print_matrix("Transposed Matrix", m);
}

void cgc_rref_matrix(matrix_t *m, matrix_t *m_result)
{
    if (cgc_m_rref(m, m_result) != SUCCESS)
        cgc_printf("Could not complete reduced row echelon form\n");
    else
        cgc_print_matrix("RREF Result:", m_result);
}

int main(int cgc_argc, char *cgc_argv[])
{
    int retval = 0;
    int choice = 0;
    short *prandom_data;
#ifdef PATCHED_1
    char m_result_data[MAX_ROWS * MAX_COLS * sizeof(int)];
#else
    char m_result_data[((MAX_ROWS * MAX_COLS) - 1) * sizeof(int)];
#endif

    prandom_data = cgc_create_random_shorts();
    matrix_t *m;
    matrix_t *m1, *m2;
    matrix_t *m_result;
    m1 = cgc_create_matrix(SHORT, NULL);
    m2 = cgc_create_matrix(SHORT, NULL);
    m_result = cgc_create_matrix(INT, m_result_data);

    char *input = cgc_malloc(2048);
    cgc_printf("Matrix math is fun!\n");
    cgc_printf("-------------------\n");
    while (1)
    {
        choice = cgc_select_menu_choice(input, LINE_SIZE);
        switch(choice)
        {
        case 1:
            cgc_printf("Inputting Matrix Values:\n");
            m = cgc_choose_matrix(m1, m2, input, LINE_SIZE);
            if (!m)
                goto cgc_exit;
            if (cgc_input_matrix(m, input, LINE_SIZE) == ERROR)
                goto cgc_exit;
            break;
        case 2:
            cgc_printf("Print Matrices:\n");
            cgc_print_matrices(m1, m2, m_result);
            break;
        case 3:
            cgc_printf("Adding Matrices:\n");
            cgc_add_matrices(m1, m2, m_result);
            break;
        case 4:
            cgc_printf("Subtracting Matrices:\n");
            cgc_subtract_matrices(m1, m2, m_result);
            break;
        case 5:
            cgc_printf("Multiplying Matrices:\n");
            cgc_multiply_matrices(m1, m2, m_result);
            break;
        case 6:
            cgc_printf("Swap Rows in a  Matrix:\n");
            m = cgc_choose_matrix(m1, m2, input, LINE_SIZE);
            if (!m)
                goto cgc_exit;
            retval = cgc_swap_matrix_row_col(m, SWAP_ROW, input, LINE_SIZE);
            if (retval == ERROR)
                goto cgc_exit;
            if (retval == SUCCESS)
                cgc_print_matrix("Swapped Rows", m);
            break;
        case 7:
            cgc_printf("Swap Columns in a  Matrix:\n");
            m = cgc_choose_matrix(m1, m2, input, LINE_SIZE);
            if (!m)
                goto cgc_exit;
            retval = cgc_swap_matrix_row_col(m, SWAP_COL, input, LINE_SIZE);
            if (retval == ERROR)
                goto cgc_exit;
            if (retval == SUCCESS)
                cgc_print_matrix("Swapped Columns", m);
            break;
        case 8:
            cgc_printf("Transpose a Matrix:\n");
            m = cgc_choose_matrix(m1, m2, input, LINE_SIZE);
            if (!m)
                goto cgc_exit;
            cgc_transpose_matrix(m);
            break;
        case 9:
            cgc_printf("Perform Reduced Row Echelon Form on Matrix\n");
            m = cgc_choose_matrix(m1, m2, input, LINE_SIZE);
            if (!m)
                goto cgc_exit;
            cgc_rref_matrix(m, m_result);
            break;
        case 10:
            cgc_printf("Create a Random Matrix:\n");
            m = cgc_choose_matrix(m1, m2, input, LINE_SIZE);
            if (!m)
                goto cgc_exit;
            if (cgc_random_matrix(m, input, LINE_SIZE, prandom_data) == ERROR)
                goto cgc_exit;
            break;
        case 11:
            goto cgc_exit;
        default:
            cgc_printf("Bad Selection\n");
        }
    }

cgc_exit:
    cgc_printf("Exiting...\n");
    return 0;
}

