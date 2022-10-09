#include "view.h"

struct viewstate view = {
	0.0,		// centerx
	0.0, 		// centery
	SPREAD_START,
	SCALE_START,
	0.0,
	ITERATIONS,
	4,
	3,
	1,
	1
};

int *pixels;
bool showAxis = true;
bool undoAction = false;
