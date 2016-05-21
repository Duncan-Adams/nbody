#include "include.h"
#include "integrator.h"

int WinMain(){
	main(0, NULL);
}	
	
void orbit(Body *b1, Body *b2, double a, double e, double w) {
	Vector P; /* location of periapsis */
	Vector v; /* orbital velocity */
	double vmag;
	double h; /* specific angular momentum */
	double y; /* angle between (1-e)*a and v */
	
	if(e < 0 || e >= 1)
		return;
	
	P.x = b1->r.x + (1 - e)*a*cos(w);
	P.y = b1->r.y + (1 - e)*a*sin(w);
	
	h = sqrt(a*(1 - e*e)*G*(b1->m + b2->m));
	
	vmag = sqrt(((1 + e)*G*b1->m)/((1 - e)*a));
	
	y = asin((1-e)*a * vmag/h);
	
	v.x = vmag * cos(y);
	v.y = vmag * sin(y);
	
	b2->v = v;
	b2->r = P;
}


int main(int argc, char** argv) {
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) return 0;
	
	SDL_Window* win = SDL_CreateWindow("N-Body", SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, 800, 450, 0);
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(ren, 1600, 900);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	
	
	int nbodies = 2;
	
	Body* body_list = malloc(sizeof(Body) * nbodies);
	
	Body b1, b2;
	
	b1.r = (Vector){1100, 750};
	b1.v = (Vector){0, 0};
	b1.a = (Vector){0, 0};
	b1.m = 5.97e16;
	b1.radius = 10;
	
	b2.r = (Vector){1100 + 100, 750};
	b2.v = (Vector){0, 0};
	b2.a = (Vector){0, 0};
	b2.m = 1;
	b2.radius = 4;
	b2.m = 10;

	orbit(&b1, &b2, 30, 0, 0);
	
	body_list[0] = b1;
	body_list[1] = b2;
	
	Uint32 sim_time = 0;
	Uint32 real_time = 0;

	
	int i = 0;
	int j = 0;
	
	double dt = .001; 
	double f = 0.0;
	
	while(1) {
		
		real_time = SDL_GetTicks();
		
		while(sim_time < real_time) {
		
			SDL_Event e;
			if (SDL_PollEvent(&e)) {
				if(e.type == SDL_QUIT) {
					break;
				}
			}
			
			sim_time += dt * 1000;
			
			for(i = 0; i < nbodies; i++) {
				body_list[i].a.x = 0.0;
				body_list[i].a.y = 0.0;
			}
			
			for(i = 0; i < nbodies; i++) {
				for(j = i + 1; j < nbodies; j++) {
					acceleration(&body_list[i], &body_list[j]);
				}
			}
			
			integrate(body_list, nbodies, dt);
		
		}
			
			SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
			SDL_RenderClear(ren);
			
			for(i = 0; i < nbodies; i++) {
				filledCircleRGBA(ren, body_list[i].r.x, body_list[i].r.y, body_list[i].radius, 170, 0, 0, 255);
			}
			
			SDL_RenderPresent(ren);
		
}

	free(body_list);
	
	
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	
	SDL_Quit();
	
	return 0;	
}
	
