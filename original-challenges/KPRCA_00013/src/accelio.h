#ifndef ACCELIO_H_
#define ACCELIO_H_

#define TRIM_FRONT 1
#define TRIM_BACK 2
#define TRIM_ALL 3
#define WHITESPACE "\r\n\t "

int strtrim(char *str, size_t size, int sides);
int valid_cell_id(char *input);
int get_rowcol(char *input, char *row, char *col, char delim);
int sanitize_formula(char *formula, size_t size);

#endif /* ACCELIO_H */
