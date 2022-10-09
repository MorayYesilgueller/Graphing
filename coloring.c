#include <math.h>
#include <complex.h>
#include "view.h"
#include "coloring.h"



int coloring(complex double z)
{
	double p = compvar(z);
	double s = p/exp(view.spread);
	int x = ((int)(255.0 + (-255.0/(1.0+ s*s)))) << 8;
	return x;
}

int coloring2(complex double z)
{
	double p = compvar(z);
	double x = (p+view.shift)/exp(view.spread);
	x = fabs((atan(x) / M_PI)*(1.0 - 1.0/(1.0+x*x)))*510.0;
	if (p <= 0){
		return (int)x << view.color1*8; // blue negative
	}
	return (int)x << view.color2*8;	// green positive
	
}

/* under construction */
int colorwheel(complex double z)
{
	// phase to rgb
	double angle = atan2(creal(z), cimag(z));	
	double lightness = carg(z); // find good lightness plotter, log seems aight
	return 0;
}

/* unused */
int colorTest(complex double z)
{
	if (creal(z) < 5.0 && creal(z) > -5.0){
		return 0xff00ff00;
	} else if (cimag(z) < 5.0 && cimag(z) > -5.0){
		return 0xffff0000;
	}
	return 0xff000fff;
}
