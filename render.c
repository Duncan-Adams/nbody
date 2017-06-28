#include "render.h"

static int16_t x[N_TRACK];
static int16_t y[N_TRACK];

static void render_history(Body *b, camera c) {
	int i = 0;
	
	int n_stored = b->n_stored;
	int start = b->start;
	
	
	for(i = 0; i < b->n_stored || i < N_TRACK; i++) {
		x[i] = (int16_t)b->history[(start + i) % N_TRACK].x;
		y[i] = (int16_t)b->history[(start + i) % N_TRACK].y;
		
		x[i] -= c.center.x;
		y[i] -= c.center.y;
		
		x[i] += 800;
		y[i] = 450 - y[i];
	}
	
	polygonColor(ren, x, y, n_stored < N_TRACK ? n_stored:N_TRACK,  b->color); 
	return;
}

void render(Body* list, int n, camera c) {
	int i;
	Vector cam_coord;
	Vector screen_coord;
	
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	
	for(i = 0; i < n; i++) {
		
		/* transform world coords into camera space */
		
		cam_coord.x = list[i].r.x - c.center.x;
		cam_coord.y = list[i].r.y - c.center.y;
		
		/* transform camera coords into screen space */
		
		screen_coord.x = cam_coord.x + 800;
		screen_coord.y = 450 - cam_coord.y;
		
		/* render */
		
		filledCircleColor(ren, screen_coord.x, screen_coord.y, log(list[i].m) + 5, list[i].color);
		if(list[i].track == 1 && list[i].n_stored > 2)
			render_history(&list[i], c);
	}
	
	SDL_RenderPresent(ren);
}
