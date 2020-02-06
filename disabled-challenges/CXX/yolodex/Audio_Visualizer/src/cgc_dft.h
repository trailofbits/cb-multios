#ifndef DFT_H_
#define DFT_H_

typedef struct {
    double real;
    double imag;
} complex_t;


complex_t *cgc_dft(double *real_coeff, unsigned int samples, int *len);
double *cgc_idft(complex_t *coeff, unsigned int samples, int *len);

#endif /* !DFT_H_ */
