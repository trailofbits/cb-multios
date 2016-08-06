#ifndef MATRIX_H_
#define MATRIX_H_

#define MAX_ROWS 16
#define MAX_COLS 16

#define SUCCESS 0
#define ERROR 1
#define FAIL -1

#define GET_OFFSET(_row, _col, _num_cols) (((_row) * (_num_cols)) + (_col))

typedef enum  { SHORT = 1, INT = 2, FLOAT = 4 } mtype_e;

typedef struct matrix matrix_t;
struct matrix {
    int num_rows;
    int num_cols;
    mtype_e ptype;
    union {
        short *psdata;
        int *pldata;
        float *pfdata;
    };

    int (*get_cell)(matrix_t *, unsigned int, unsigned int);
    float (*get_fcell)(matrix_t *, unsigned int, unsigned int);
    int (*set_cell)(matrix_t *, unsigned int, unsigned int, int);
    int (*set_fcell)(matrix_t *, unsigned int, unsigned int, float);
    int (*set_rows_cols)(matrix_t *, unsigned int, unsigned int);
    void (*print_matrix)(matrix_t *);

    char data[];
};


matrix_t *create_matrix(mtype_e ptype, char *data);

int m_add(matrix_t *m1, matrix_t *m2, matrix_t *m_result);
int m_subtract(matrix_t *m1, matrix_t *m2, matrix_t *m_result);
int m_multiply(matrix_t *m1, matrix_t *m2, matrix_t *m_result);
int m_rref(matrix_t *m, matrix_t *m_result);
int m_transpose(matrix_t *m);
int swap_row(matrix_t *m, int row_idx1, int row_idx2);
int swap_col(matrix_t *m, int col_idx1, int col_idx2);

#endif
