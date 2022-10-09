#ifndef _FUNCTION_H
#define _FUNCTION_H
#include <math.h>
#include <complex.h>

complex double zeta(complex double s);

/* Eisensteinseries 4 */
complex double E4(complex double q); // q = square of the nome

/* Eisensteinseries 5 */
complex double E6(complex double q); // q = square of the nome

complex double J(complex double t);

complex double mandelbrot(complex double c);

complex double collatz(complex double z);

complex double crex(complex double z);

complex double julia(complex double z);

#endif /* _FUNCTION_H */

