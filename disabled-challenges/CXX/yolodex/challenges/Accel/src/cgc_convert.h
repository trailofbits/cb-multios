#ifndef CONVERT_H_
#define CONVERT_H_

#define MAX_DEC 5

extern char *cgc_itoa(int value, char *str, cgc_size_t size);
extern char *cgc_ftoa(double value, char *str, cgc_size_t size);
extern double cgc_atof(char *str, cgc_size_t size, int *bad_conversion);

#endif /* CONVERT_H */
