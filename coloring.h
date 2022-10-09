#ifndef _COLOR_H
#define _COLOR_H
#include <complex.h>
extern double (*compvar)(complex double); // cimag | creal

int colorTest(complex double z);

int coloring(complex double z);

int coloring2(complex double z);

int colorwheel(complex double z);


#endif /* _COLOR_H */
