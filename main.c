#include "include.h"
#include "integrator.h"
#include "render.h"
#include "config.h"
#include "input.h"


	

Body* body_list;
int nbodies;

uint8_t running = 1;
int follow = 0;


extern SDL_Window* win;
extern SDL_Renderer* ren;

void enable_tracking(Body *b) {
	b->track = 1;
	b->history = malloc(N_TRACK*sizeof(Vector));
	b->n_stored = 0;
	b->index = 0;
	b->start = 0;
}

int main(int argc, char** argv) {
	int i = 0;
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) return 0;
	
	win = SDL_CreateWindow("N-Body", SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, 800, 450, 0);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(ren, 1600, 900);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	
	read_cfg("./cfg/lagrange.cfg");

	
	Uint32 sim_time = 0;
	Uint32 real_time = 0;
	Uint32 tracker = 0;
	/* call acceleration here to initiliaze the integrator with */
	acceleration(body_list, nbodies);
	
	camera c;
	c.center.x = 0;
	c.center.y = 0;
	
	Vector cam_pos = c.center;
	
	for(i = 0; i < nbodies; i++) {
		if(body_list[i].track)
			enable_tracking(&body_list[i]);		
	}
	
	while(running) {
		
		real_time = SDL_GetTicks();
		
		while(sim_time < real_time) {
		
			keyboard_input();
			handle_input(&cam_pos);
			
			sim_time += DT * 1000;
			tracker += DT * 1000;
	
			integrate(body_list, nbodies, DT);
			
			if(tracker > 10) {
				for(i = 0; i < nbodies; i++) {
					if(body_list[i].track == 1) {
						body_list[i].history[body_list[i].index].x = body_list[i].r.x;
						body_list[i].history[body_list[i].index].y = body_list[i].r.y;
						body_list[i].n_stored += 1;
						body_list[i].index += 1;
						if(body_list[i].index == N_TRACK) {
							body_list[i].start += 1;
							body_list[i].start %= N_TRACK;
							body_list[i].index = 0;
						}
					}
				}
				tracker = 0;
			}
			
			if(follow > 0) {
				c.center.x = body_list[follow - 1].r.x;
				c.center.y = body_list[follow - 1].r.y;
			} else {
				c.center = cam_pos;
			}
	
		}
			
			render(body_list, nbodies, c);
}



	free(body_list);
	
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	
	SDL_Quit();
	
	return 0;	
}

int WinMain(){
	return main(0, NULL);
}	
	
