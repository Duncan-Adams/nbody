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



Body* body_list;
int nbodies;

void read_cfg(char *path) {
	int i = 0;
	
	FILE *z = fopen(path, "r");
	if(!z) exit(EXIT_FAILURE);
	
	fscanf(z, "nbodies:%d\n", &nbodies);
	
	body_list = malloc(sizeof(Body) * nbodies);
	
	for(i = 0; i < nbodies; i++) {
		fscanf(z, "[BODY]\n");
		fscanf(z, "pos=<%lf,%lf>\n", &body_list[i].r.x, &body_list[i].r.y);
		fscanf(z, "vel=<%lf,%lf>\n", &body_list[i].v.x, &body_list[i].v.y);
		fscanf(z, "mass=%lf\n", &body_list[i].m);
	}
	
	fclose(z);
	
	
}

extern SDL_Window* win;
extern SDL_Renderer* ren;

int main(int argc, char** argv) {
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) return 0;
	
	win = SDL_CreateWindow("N-Body", SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED, 800, 450, 0);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(ren, 1600, 900);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	
	read_cfg("./cfg.txt");

	
	Uint32 sim_time = 0;
	Uint32 real_time = 0;
	
	/* call acceleration here to initiliaze the integrator with */
	acceleration(body_list, nbodies);
	
	int follow = 0;
	
	camera c;
	c.center.x = 0;
	c.center.y = 0;
	
	Vector cam_pos = c.center;
	
	while(1) {
		
		real_time = SDL_GetTicks();
		
		while(sim_time < real_time) {
		
			SDL_Event e;
			if (SDL_PollEvent(&e)) {
				if(e.type == SDL_QUIT) {
					break;
				}
				
				if(e.type == SDL_MOUSEBUTTONDOWN) {
					follow += 1;
					if(follow > nbodies) {
						follow = 0;
					}
				}
			}
			
			sim_time += DT * 1000;
		
			integrate(body_list, nbodies, DT);
			
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
	
