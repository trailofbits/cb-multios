#ifndef ACCELIO_H_
#define ACCELIO_H_

#define TRIM_FRONT 1
#define TRIM_BACK 2
#define TRIM_ALL 3
#define WHITESPACE "\r\n\t "

int cgc_strtrim(char *str, cgc_size_t size, int sides);
int cgc_valid_cell_id(char *input);
int cgc_get_rowcol(char *input, char *row, char *col, char delim);
int cgc_sanitize_formula(char *formula, cgc_size_t size);

#endif /* ACCELIO_H */
