#include "include.h"
#include "integrator.h"
#include "render.h"

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

extern SDL_Window* win;
extern SDL_Renderer* ren;

int main(int argc, char** argv) {
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) return 0;
	
	win = SDL_CreateWindow("N-Body", SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, 800, 450, 0);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(ren, 1600, 900);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	
	
	int nbodies = 4;
	
	Body* body_list = malloc(sizeof(Body) * nbodies);
	
	Body b1, b2, b3, b4;
	
	b1.r = (Vector){0, 0};
	b1.v = (Vector){0, 0};
	b1.a = (Vector){0, 0};
	b1.m = 5.97e16;
	b1.radius = 10;
	
	b2.r = (Vector){100, 0};
	b2.v = (Vector){0, 0};
	b2.a = (Vector){0, 0};
	b2.m = 1e9;
	b2.radius = 8;

	orbit(&b1, &b2, 100, 0, 0);
	
	b3.r = (Vector){50, 86.6025};
	b3.v = (Vector){-172.8484, 99.794};
	b3.a = (Vector){0, 0};
	b3.m = 1;
	b3.radius = 4;

	
	b4.r = (Vector){50, -86.6025};
	b4.v = (Vector){172.8484, 99.794};
	b4.a = (Vector){0, 0};
	b4.m = 1;
	b4.radius = 4;

	
	camera c;
	c.center.x = 0;
	c.center.y = 0;
	
	body_list[0] = b1;
	body_list[1] = b2;
	body_list[2] = b3;
	body_list[3] = b4;
	
	Uint32 sim_time = 0;
	Uint32 real_time = 0;
	
	/* call acceleration here to initiliaze the integrator with */
	acceleration(body_list, nbodies);
	
	while(1) {
		
		real_time = SDL_GetTicks();
		
		while(sim_time < real_time) {
		
			SDL_Event e;
			if (SDL_PollEvent(&e)) {
				if(e.type == SDL_QUIT) {
					break;
				}
			}
			
			sim_time += DT * 1000;
		
			integrate(body_list, nbodies, DT);
		
		}
			
			render(body_list, nbodies, c);
}



	free(body_list);
	
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	
	SDL_Quit();
	
	return 0;	
}
	
