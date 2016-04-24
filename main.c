#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

const double G = 6.67408e-11;

typedef struct _vec {
	double x;
	double y;
} Vector;

typedef struct _body {
	Vector r;
	Vector v;
	Vector a;
	
	double m;
	double radius;
	
} Body;

int WinMain(){
	main(0, NULL);
}

void acceleration(Body *b1, Body *b2) {
	double mag = 0.0;
	long double theta = 0.0;
	Vector f;
	Vector distance;
	double g = 0.0;
	double r = 0.0;
	
	distance.x = b2->r.x - b1->r.x;
	distance.y = b2->r.y - b1->r.y;
	
	r = hypot(distance.x, distance.y);
	
	g = (r * r * r)/G; /* inverse of G over r cubed */
	
	b1->a.x += b2->m*distance.x/g;
	b1->a.y += b2->m*distance.y/g;
									
	b2->a.x -= b1->m*distance.x/g;
	b2->a.y -= b1->m*distance.y/g;

}

void integrate(Body* list, int n, double dt) {
	int i = 0;
	
	if(n <= 0) return;
	
	for(i = 0; i < n; i++) {
		list[i].r.x += list[i].v.x * dt + .5 * list[i].a.x * (dt * dt);
		list[i].r.y += list[i].v.y * dt + .5 * list[i].a.y * (dt * dt);
		
		list[i].v.x += list[i].a.x * dt;
		list[i].v.y += list[i].a.y * dt;
	
	}
}
	
	


int main(int argc, char** argv) {
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) return 0;
	
	SDL_Window* win = SDL_CreateWindow("N-Body", SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, 800, 450, 0);
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(ren, 1600, 900);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	
	
	int nbodies = 3;
	
	Body* body_list = malloc(sizeof(Body) * nbodies);
	
	Body b1, b2, b3;
	
	b1.r = (Vector){800, 450};
	b1.v = (Vector){0, 0};
	b1.a = (Vector){0, 0};
	b1.m = 5.97e16;
	b1.radius = 10;
	
	b2.r = (Vector){800, 600};
	b2.v = (Vector){162.93, 0};
	b2.a = (Vector){0, 0};
	b2.m = 1e13;
	b2.radius = 10;
	
	b3.r = (Vector){929.9038, 525};
	b3.v = (Vector){81.48, -141.13};
	b3.a = (Vector){0, 0};
	b3.m = 1;
	b3.radius = 10;
	
	body_list[0] = b1;
	body_list[1] = b2;
	body_list[2] = b3;
	
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
				filledCircleRGBA(ren, body_list[i].r.x, body_list[i].r.y, 10, 170, 0, 0, 255);
			}
			
			SDL_RenderPresent(ren);
		
}

	free(body_list);
	
	
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	
	SDL_Quit();
	
	return 0;	
}
	
