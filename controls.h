#ifndef _CONTROLS_H
#define _CONTROLS_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "view.h"


#define STK_SIZE 26
#define HISTORY_MAX 32


typedef struct {
	char cstack[STK_SIZE];
	char _eos;		// must ALWAYS be 0
	bool isChanged;
	int top;	// also shows how many items are on the stack
} cntrstack_t;

// TODO: Reduce ram usage of history
typedef struct {
	struct viewstate snapshot[HISTORY_MAX];
	int index;	// -1 means no history items
} viewhistory_t;

extern cntrstack_t stack;

int push(char item);
bool handleKeyEvent(SDL_Event kbde);
unsigned int pop(void);
int undoCommand(void);
void enqueueCurrent(void);
bool executeStack(void);

#endif /* _CONTROLS_H */
