#include "integrator.h"

void acceleration(Body *b1, Body *b2) {
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
