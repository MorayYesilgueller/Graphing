#ifndef _VIEW_H
#define _VIEW_H
#include <stdbool.h>

// large spread implies only sparse highlight and only large values
#define SPREAD_START 3.2
// small scale means huge zoom
#define SCALE_START 0.01
//  must be more than two since starts at 1
#define ITERATIONS 12 /* depends on type of function, some converge faster than others */
#define WIN_WIDTH (1260)
#define WIN_HEIGHT (820)
#define COLOR_MODE_CNT 5 /* col2 phase-linear arg-linear phase-s arg-s*/
#define FACTOR 20.0


struct viewstate {
	double centerx;
	double centery;
	double spread;
	double scaling;
	double shift;
	int iterations;
	int color1;
	int color2;
	int var1;
	int var2;
};

extern struct viewstate view;
extern int *pixels;
extern bool showAxis;
extern bool undoAction;
#endif /* _VIEW_H */
