#include <math.h>
#include <complex.h>
#include "function.h"
#include "view.h"

complex double zeta(complex double s)
{
	complex double sum = CMPLX(0.0, 0.0);
	for (int n = 1; n < view.iterations; n++){
		sum += 1.0/cpow(n,s);
	}
	return sum;
}

/* Eisensteinseries 4 */
complex double E4(complex double q) // q = square of the nome
{
	complex double sum = CMPLX(0.0, 0.0);
	complex double qn;
	for (int n = 1; n < view.iterations; n++){
		qn = cpow(q,n);
		sum += (n*n*n * qn) / (1.0-qn);
	}
	return 1.0 + sum*240.0;
}

/* Eisensteinseries 5 */
complex double E6(complex double q) // q = square of the nome
{
	complex double sum = CMPLX(0.0, 0.0);
	complex double qn;
	for (int n = 1; n < view.iterations; n++){
		qn = cpow(q,n);
		sum += (n*n*n*n*n * qn) / (1.0-qn);
	}
	return 1.0 - sum*504.0;
}

complex double J(complex double t)
{
	complex double q = cexp(M_PI*I*2.0*t);
	complex double e4 = E4(q);
	complex double e6 = E6(q);
	e4 *= (e4 * e4);
	return 1728.0 * (e4 / (e4-e6*e6));
}

complex double mandelbrot( complex double c)
{
	complex double z = CMPLX(0.0,0.0);
	for (int n = 0; n < view.iterations; n++){
		z = z*z + c;
	}
	return z;
}


complex double collatz(complex double z)
{
	for (int n = 0; n < view.iterations; n++){
		z = ccos(z*M_PI/((double)view.var1*0.01))/2.0 + ((double)view.var2*0.01*z+1.0)/2.0*csin(z*M_PI/2.0);
	}
	return z;
}

complex double crex(complex double z)
{	
	if (z == CMPLX(0.0, 0.0)){
		z += 0.000000000000001;
	}
	for (int n = 0; n < view.iterations; n++){
		z = cexp(1.0/z);
	}
	return z;
}

complex double julia(complex double z)
{
	complex double c = CMPLX((double)view.var1*0.01, (double)view.var2*0.01);
	for (int n = 0; n < view.iterations; n++){
		z = z*z + c;
	}
	return z;
}


