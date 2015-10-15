#ifndef CONVERT_H_
#define CONVERT_H_

#define MAX_DEC 5

extern char *itoa(int value, char *str, size_t size);
extern char *ftoa(double value, char *str, size_t size);
extern double atof(char *str, size_t size, int *bad_conversion);

#endif /* CONVERT_H */
