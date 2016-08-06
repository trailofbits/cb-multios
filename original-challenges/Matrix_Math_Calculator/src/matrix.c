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
#include <string.h>

#define TOLERANCE .00099

//Member Functions
static int m_get_cell(matrix_t *m, unsigned int row, unsigned int col)
{
    if (!m)
        return ERROR;
    if (row > m->num_rows || col > m->num_cols)
        return FAIL;

    switch(m->ptype) {
    case SHORT:
        return m->psdata[GET_OFFSET(row, col, m->num_cols)];
    case INT:
        return m->pldata[GET_OFFSET(row, col, m->num_cols)];
    case FLOAT:
        return (int)(m->pfdata[GET_OFFSET(row, col, m->num_cols)]);
    }
}

static float m_get_fcell(matrix_t *m, unsigned int row, unsigned int col)
{
    if (!m)
        return ERROR;
    if (row > m->num_rows || col > m->num_cols)
        return FAIL;

    switch(m->ptype) {
    case SHORT:
        return (float)m->psdata[GET_OFFSET(row, col, m->num_cols)];
    case INT:
        return (float)m->pldata[GET_OFFSET(row, col, m->num_cols)];
    case FLOAT:
        return m->pfdata[GET_OFFSET(row, col, m->num_cols)];
    }
}

static int m_set_cell(matrix_t *m, unsigned int row, unsigned int col, int new_value)
{
    if (!m)
        return ERROR;
    if (row > m->num_rows || col > m->num_cols)
        return FAIL;
    //int offset = GET_OFFSET(row, col, m->num_cols);

    switch(m->ptype) {
    case SHORT:
        //m->psdata[offset] = (short) new_value;
        m->psdata[GET_OFFSET(row, col, m->num_cols)] = (short) new_value;
        break;
    case INT:
        m->pldata[GET_OFFSET(row, col, m->num_cols)] = new_value;
        break;
    case FLOAT:
        m->pfdata[GET_OFFSET(row, col, m->num_cols)] = (float) new_value;
        break;
    }

    return SUCCESS;
}

static int m_set_fcell(matrix_t *m, unsigned int row, unsigned int col, float new_value)
{
    if (!m)
        return ERROR;
    if (row > m->num_rows || col > m->num_cols)
        return FAIL;

    switch(m->ptype) {
    case SHORT:
        m->psdata[GET_OFFSET(row, col, m->num_cols)] = (short) new_value;
        break;
    case INT:
        m->pldata[GET_OFFSET(row, col, m->num_cols)] = (int) new_value;
        break;
    case FLOAT:
        m->pfdata[GET_OFFSET(row, col, m->num_cols)] = new_value;
        break;
    }

    return SUCCESS;
}

static int m_set_rows_cols(matrix_t *m, unsigned int num_rows, unsigned int num_cols)
{
    if (!m)
        return ERROR;
    if (num_rows > MAX_ROWS || num_cols > MAX_COLS)
        return FAIL;

    m->num_rows = num_rows;
    m->num_cols = num_cols;
    return SUCCESS;
}

static void transmitall(char *buf, unsigned int len)
{
    size_t tx, sent = 0;
    while (sent < len)
    {
        if (transmit(STDOUT, buf + sent, len - sent, &tx) != 0 || tx == 0)
            break;
        sent += tx;
    }
}

static void print_matrix(matrix_t *m)
{
    static char buf[8192];
    if (!m)
        return;

    buf[0] = 0;
    int i, j;
    for (i = 0; i < m->num_rows; i++)
    {
        sprintf(buf, "%s|", buf);
        for (j = 0; j < m->num_cols; j++)
        {
            if (strlen(buf) > sizeof(buf) - 1000)
            {
                transmitall(buf, strlen(buf));
                buf[0] = 0;
            }
            if (m->ptype != FLOAT)
            {
                sprintf(buf, "%s %d |", buf, m->get_cell(m, i, j));
            }
            else
            {
                float f = m->get_fcell(m, i, j);
                float f_pos = f >= 0 ? f : f * -1;
                int integer = (int)f_pos;
                int decimal =  (int) ((f_pos - (int)f_pos) * 100);

                if ((int) ((f_pos - (int)f_pos) * 10000) == 9999)
                {
                    integer += 1;
                    decimal = 0;
                }
                else if ((int) ((f_pos - (int)f_pos) * 10000) == 1)
                {
                    decimal = 0;
                }

                if (f_pos < 0.01)
                    sprintf(buf, "%s 0.0 |", buf);
                else if (f >= -TOLERANCE)
                    sprintf(buf, "%s %d.%d |", buf, integer, decimal);
                else
                    sprintf(buf, "%s -%d.%d |", buf, integer, decimal);
            }
        }
        sprintf(buf, "%s\n", buf);
    }
    if (buf[0] != 0)
    {
        transmitall(buf, strlen(buf));
        buf[0] = 0;
    }
}

//Public Functions
matrix_t *create_matrix(mtype_e ptype, char *data)
{
    matrix_t *new_matrix = NULL;

    if (data)
    {
        new_matrix = calloc(1, sizeof(matrix_t));
        if (!new_matrix)
            return NULL;

        new_matrix->pldata = (int *)data;
    }
    else
    {
        int data_size;
        switch(ptype) {
        case SHORT:
            data_size = MAX_ROWS * MAX_COLS * sizeof(short);
            break;
        case INT:
            data_size = MAX_ROWS * MAX_COLS * sizeof(int);
            break;
        case FLOAT:
            data_size = MAX_ROWS * MAX_COLS * sizeof(float);
            break;
        }

        new_matrix = calloc(1, sizeof(matrix_t) + data_size);
        if (!new_matrix)
            return NULL;

        new_matrix->pldata = (void *)new_matrix->data;
    }

    new_matrix->num_rows = 1;
    new_matrix->num_cols = 1;
    new_matrix->ptype = ptype;
    new_matrix->get_cell = &m_get_cell;
    new_matrix->get_fcell = &m_get_fcell;
    new_matrix->set_cell = &m_set_cell;
    new_matrix->set_fcell = &m_set_fcell;
    new_matrix->set_rows_cols = &m_set_rows_cols;
    new_matrix->print_matrix = &print_matrix;

    return new_matrix;
}

int m_add(matrix_t *m1, matrix_t *m2, matrix_t *m_result)
{
    if (!m1 || !m2 || !m_result)
        return ERROR;

    if(m1->num_rows != m2->num_rows ||  m1->num_cols != m2->num_cols)
        return FAIL;

    m_result->ptype = SHORT;
    m_result->set_rows_cols(m_result, m1->num_rows, m1->num_cols);

    int i, j;
    for (i = 0; i < m_result->num_rows; i++)
    {
        for (j = 0; j < m_result->num_cols; j++)
        {
            short a, b;
            a = m1->get_cell(m1, i, j);
            b = m2->get_cell(m2, i, j);
            m_result->set_cell(m_result, i, j, a+b);
        }
    }

    return SUCCESS;
}

int m_subtract(matrix_t *m1, matrix_t *m2, matrix_t *m_result)
{
    if (!m1 || !m2 || !m_result)
        return ERROR;

    if(m1->num_rows != m2->num_rows ||  m1->num_cols != m2->num_cols)
        return FAIL;

    m_result->ptype = SHORT;
    m_result->set_rows_cols(m_result, m1->num_rows, m1->num_cols);

    int i, j;
    for (i = 0; i < m_result->num_rows; i++)
    {
        for (j = 0; j < m_result->num_cols; j++)
        {
            short a, b;
            a = m1->get_cell(m1, i, j);
            b = m2->get_cell(m2, i, j);
            m_result->set_cell(m_result, i, j, a-b);
        }
    }

    return SUCCESS;
}

int m_multiply(matrix_t *m1, matrix_t *m2, matrix_t *m_result)
{
    if (!m1 || !m2 || !m_result)
        return ERROR;

    if(m1->num_cols != m2->num_rows)
        return FAIL;

    m_result->ptype = INT;
    m_result->set_rows_cols(m_result, m1->num_rows, m2->num_cols);

    int i, j, k, sum;
    for (i = 0; i < m1->num_rows; i++)
    {
        for (k = 0; k < m2->num_cols; k++)
        {
            sum = 0;
            for (j = 0; j < m1->num_cols; j++)
            {
                sum += (int)m1->get_cell(m1, i, j) * (int)m2->get_cell(m2, j, k);
            }
            m_result->set_cell(m_result, i, k, sum);
        }
    }

    return SUCCESS;
}

int swap_row(matrix_t *m, int row_idx1, int row_idx2)
{
    if (!m)
        return ERROR;

    float temp1, temp2;
    if (row_idx1 > m->num_rows || row_idx2 > m->num_rows)
        return FAIL;

    int j;
    for (j = 0; j < m->num_cols; j++)
    {
        temp1 = m->get_fcell(m, row_idx1, j);
        temp2 = m->get_fcell(m, row_idx2, j);
        m->set_fcell(m, row_idx1, j, temp2);
        m->set_fcell(m, row_idx2, j, temp1);
    }

    return SUCCESS;
}

int swap_col(matrix_t *m, int col_idx1, int col_idx2)
{
    if (!m)
        return ERROR;

    float temp1, temp2;
    if (col_idx1 > m->num_cols || col_idx2 > m->num_cols)
        return FAIL;

    int i;
    for (i = 0; i < m->num_rows; i++)
    {
        temp1 = m->get_cell(m, i, col_idx1);
        temp2 = m->get_cell(m, i, col_idx2);
        m->set_cell(m, i, col_idx1, temp2);
        m->set_cell(m, i, col_idx2, temp1);
    }

    return SUCCESS;
}

int m_transpose(matrix_t *m)
{
    if (!m)
        return ERROR;

    //int squarify = m->num_rows > m->num_cols ? m->num_rows : m->num_cols;
    int old_rows = m->num_rows;
    int old_cols = m->num_cols;

    int data_width;

    matrix_t *mt = NULL;
    switch(m->ptype)
    {
    case(SHORT):
        mt = create_matrix(SHORT, NULL);
        data_width = sizeof(short);
        break;
    case(INT):
        mt = create_matrix(INT, NULL);
        data_width = sizeof(INT);
        break;
    case(FLOAT):
        mt->set_rows_cols(mt, old_cols, old_rows);
        data_width = sizeof(FLOAT);
        break;
    }

    mt->set_rows_cols(mt, old_cols, old_rows);

    int i, j;
    for (i = 0; i < m->num_rows; i++)
    {
        for (j = 0; j < m->num_cols; j++)
        {
            int temp = m->get_cell(m, i, j);
            mt->set_cell(mt, j, i, temp);
        }
    }

    m->set_rows_cols(m, old_cols, old_rows);
    memcpy(m->data, mt->data, old_cols * old_rows * data_width);
    free(mt);
    return SUCCESS;
}

//Helper Functions
static int swap_nonzero_cell(matrix_t *m, int row, int col)
{
    if (!m)
        return ERROR;
    if (m->get_fcell(m, row, col) > TOLERANCE || m->get_fcell(m, row, col) < -TOLERANCE)
        return SUCCESS;

    int init_row = row;
    for (row=row + 1; row < m->num_rows; row++)
        if (m->get_fcell(m, row, col) > TOLERANCE || m->get_fcell(m, row, col) < -TOLERANCE)
            return swap_row(m, init_row, row);

    return FAIL;
}


static int subtract_row(matrix_t *m, int row_idx1, int row_idx2, int col_offset, float scalar)
{
    if (!m)
        return ERROR;

    float temp1, temp2;
    if (row_idx1 > m->num_rows || row_idx2 > m->num_rows)
        return FAIL;

    int j;
    for (j = col_offset; j < m->num_cols; j++)
    {
        temp1 = m->get_fcell(m, row_idx1, j) * scalar;
        temp2 = m->get_fcell(m, row_idx2, j);
        m->set_fcell(m, row_idx2, j, temp2 - temp1);
    }

    return SUCCESS;
}

int m_rref(matrix_t *m, matrix_t *m_result)
{
    if (!m || !m_result)
        return ERROR;

    m_result->ptype = FLOAT;
    m_result->set_rows_cols(m_result, m->num_rows, m->num_cols);
    int i, j;
    for (i = 0; i < m->num_rows; i++)
        for (j = 0; j < m->num_cols; j++)
            m_result->set_fcell(m_result, i, j, m->get_cell(m, i, j));

    float divisor = 1;
    int k = 0;
    for (i = 0, j = 0; i < m_result->num_rows && j < m_result->num_cols; i++, j++)
    {
        if (divisor <= TOLERANCE && divisor >= -TOLERANCE)
            --i;

        swap_nonzero_cell(m_result, i, j);
        divisor = m_result->get_fcell(m_result, i, j);
        for (k = j; k < m_result->num_cols; k++)
        {
            if (divisor <= TOLERANCE && divisor >= -TOLERANCE)
                break;
            if (divisor -1 <= TOLERANCE && divisor -1 >= -TOLERANCE)
                break;

            float temp = m_result->get_fcell(m_result, i, k);
            m_result->set_fcell(m_result, i, k, temp/divisor);
        }
        for (k = 0; k < m_result->num_rows; k++)
        {
            if (divisor <= TOLERANCE && divisor >= -TOLERANCE)
                break;
            if (k == i)
                continue;

            float scalar = m_result->get_fcell(m_result, k, j);
            if (scalar > TOLERANCE || scalar < -TOLERANCE)
                subtract_row(m_result, i, k, j, scalar);
        }
    }

    return SUCCESS;
}
