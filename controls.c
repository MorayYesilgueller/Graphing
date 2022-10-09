#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "controls.h"
#include "function.h"
#include "graphingMain.h"
#include "bmp.h"
#include "view.h"

viewhistory_t history;
cntrstack_t stack;

void displayContent()
{
	stack.cstack[stack.top] = 0;// set eos in stack or stack._eos
	printf("%s\n", stack.cstack);
}

// check sizeif keycode
bool handleKeyEvent(SDL_Event kbe)
{
	bool redrawRequired = true;
	stack.isChanged = false;
	switch (kbe.key.keysym.sym){
		case 'b':
		case 'n':
		case 'y':
		case 'u':
		case 'f':
		case 'g':
		case 'q':
		case 'a':
		case 't':
		case 'r':
		case 'e':
		case 'x':
		case 'c':
		case 'w':
		case 's':
		case 'v':
		case 'z':
		case 'o':
		case 'm':
		case 'h':
		case 'j':
		case 'k':
		case 'l':
			push(kbe.key.keysym.sym);
		case SDLK_RETURN:
			redrawRequired = executeStack();
			/* fall through */
		case SDLK_ESCAPE:
			stack.top = 0;
			displayContent();
			return redrawRequired;
		default:
			break;
	}
	if (push(kbe.key.keysym.sym) == -1){	// push to stack
		printf("Invalid Keycode: %d\n", kbe.key.keysym.sym);
	}
	displayContent();
	return redrawRequired;
}


int push(char item)
{
	if (stack.top == STK_SIZE-1 || !isprint(item)){
		stack.top = 0;	// CLEAR STACK
		return -1;	// Operation failed
	} 	
	stack.cstack[stack.top] = item;
	stack.top++;
	return 0;
}

unsigned int pop()
{
	if (stack.top == 0){
		return 0xFFFFFFFF; // all bits of int
	}
	stack.top--;
	stack.isChanged = true;
	return (unsigned int)stack.cstack[stack.top];
}

/* returns to old view state */
int undoCommand(void)
{
	printf("Current index: %d\n", history.index);
	view = history.snapshot[history.index];
	if (history.index == 0){
		history.index = HISTORY_MAX-1;
	} else {
		history.index--;
	}
	return 0;
}
/* Enqueues the current view to the history */
void enqueueCurrent()
{
	printf("Current index: %d\n", history.index);
	history.snapshot[history.index] = view;
	if (history.index == HISTORY_MAX-1){
		history.index = 0;
	} else {
		history.index = history.index % HISTORY_MAX;
	}
}


/* Controls are handled here */

bool executeStack()
{
	bool redrawRequired = true;
	undoAction = true;
	int i = 0;
	int magnitude = 1;
	char reg;
	int times = 0;
	int command = pop();
	int currentTop = stack.top;
	if (command == 0xFFFFFFFF || isdigit(command)){
		printf("invalid command top of stack: %d %c\n", command, command);
		return false;
	}
	
	while (currentTop != 0){
		reg = pop();
		if (reg == 0xFFFFFFFF){
			printf("Done parsing stack content in %d\n", __LINE__);
			break;
		}
		if (isdigit(reg)){ // 0x30 - 0x3a
			times += magnitude * (reg - 0x30);
			printf("digit: %d := %d\n", reg-0x30, times);
			magnitude *= 10;
		}
		currentTop--;
	}
	if (times == 0){
		times = 1;
	}
	printf("Command: %c, times: %d\n", command, times);
	switch (command){ // IC: ignore count
		case 'q':	// shift slice coloring +
			view.shift += times * view.spread;
			break;
		case 'a':	// shift slice coloring -
			view.shift -= times * view.spread;
			break;
		case 'b':	// export image as bitmap
			printf("Wrote %lu bytes.\n", sizeof(int)*
					pixelsToBmp(WIN_WIDTH, WIN_HEIGHT, pixels, &view));
			undoAction = false;
			redrawRequired = false;
			break;
		case 'z':	// Zoom in
			view.scaling -= times * view.scaling * 0.1;
			view.centerx += view.centerx * view.scaling;
			view.centery += view.centery * view.scaling;
			break;
		case 'o':	// Zoom out
			view.scaling += times * view.scaling * 0.1;
			printf("Set scaling to %lf\n", view.scaling);
			break;
		case 'w':	// Increase spread
			view.spread += times*0.1;
			break;
		case 's':	// decrease spread
			view.spread -= times*0.1;
			break;
		case 'c':	// Toggle Coloring mode, mod count(coloring_modes)
			view.color1 = 1+(view.color1+1)%4;
			view.color2 = 1+(view.color2+1)%4;
			printf("c1: %d\nc2: %d\n", view.color1, view.color2);
			break;
		case 'v':	// toggle reals || imaginaries
			if (compvar == &creal){
				compvar = &cimag;
				printf("Plotting imaginaries\n");
				break;
			}
			compvar = &creal;
			printf("Plotting reals\n");
			break;
		case 'x':	// toggle axis IC
			showAxis = showAxis^1;
			break;
		case 'e':	// export params IC
			printf("Scaling: %lf\nPosition: %lf %lf\nSpread: %lf\n"
					"Iterations: %d\nShift: %lf\n"
					"Var1: %d\nVar2: %d\n",
					view.scaling, view.centerx, view.centery,
					view.spread, view.iterations, view.shift,
					view.var1, view.var2);
			redrawRequired = false;
			undoAction = false;
			break;
		case 'h':
			view.centerx -= times * WIN_WIDTH * FACTOR * view.scaling;
			break;
		case 'l':
			view.centerx += times * WIN_WIDTH * FACTOR * view.scaling;
			break;
		case 'j':
			view.centery -= times * WIN_HEIGHT * FACTOR * view.scaling;
			break;
		case 'k':
			view.centery += times * WIN_HEIGHT * FACTOR * view.scaling;
			break;
		case 'm':	// clears most params
			view.scaling = SCALE_START;
			view.spread = SPREAD_START;
			view.centerx = 0.0;
			view.centery = 0.0;
			view.shift = 0.0;
			view.var1 = 0;
			view.var2 = 0;
			break;
		case 'r':
			view.iterations -= times;
			break;
		case 't':
			view.iterations += times;
			break;
		case 'f':
			view.var1 += times;
			break;
		case 'g':
			view.var1 -= times;
			break;
		case 'n':
			view.var2 += times;
			break;
		case 'y':
			view.var2 -= times;
			break;


		case 'u':	// Optimise for multiple undos
			for (int i = 0; i < times; i++){
				undoCommand();
				if (i == HISTORY_MAX-1){
					printf("Reached oldest change");
					break;
				}
			}				
			undoAction = false;
			break;
		default:
			printf("invalid command top of stack: %d, mag: %d\n", command, times);
			//redrawRequired = false;
			break;


	}
	return redrawRequired;
}
