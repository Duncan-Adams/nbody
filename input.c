#include "input.h"

extern uint8_t running;
extern int follow;
extern int nbodies;
const uint8_t *KEYS;

void keyboard_input() {
    SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			running = 0;
			break;
			
		case SDL_MOUSEBUTTONDOWN:
			follow += 1;
			if(follow > nbodies) {
				follow = 0;
			}
		
		default:
			break;
		}	
	}
	
	SDL_PumpEvents();
	KEYS = SDL_GetKeyboardState(NULL);
}

void handle_input(Vector *v) {
	if(KEYS[SDL_SCANCODE_LEFT])
		v->x -= 1;
	
	if(KEYS[SDL_SCANCODE_RIGHT])
		v->x += 1;
	
	if(KEYS[SDL_SCANCODE_UP])
		v->y += 1;
	
	if(KEYS[SDL_SCANCODE_DOWN])
		v->y -= 1;
}
