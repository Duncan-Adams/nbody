#include "render.h"

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
		
		filledCircleRGBA(ren, screen_coord.x, screen_coord.y, list[i].radius, 170, 0, 0, 255);
	}
	
	SDL_RenderPresent(ren);
}
