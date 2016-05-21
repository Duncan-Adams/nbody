#include "integrator.h"

static void acceleration_helper(Body *b1, Body *b2) {
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

void acceleration(Body* list, int n) {
	int i;
	int j;
	
	for(i = 0; i < n; i++) {
		list[i].a.x = 0.0;
		list[i].a.y = 0.0;
	}
	
	for(i = 0; i < n; i++) {
		for(j = i + 1; j < n; j++) {
			acceleration_helper(&list[i], &list[j]);				
		}
	}
}

/* integration using leapfrog method */

void integrate(Body* list, int n, double dt) {
	int i = 0;
	
	if(n <= 0) return;

	
	for(i = 0; i < n; i++) {
		list[i].v.x += .5*DT * list[i].a.x;
		list[i].v.y += .5*DT * list[i].a.y;
		
		list[i].r.x += DT * list[i].v.x;
		list[i].r.y += DT * list[i].v.y;
	}
	
	acceleration(list, n);
	
	for(i = 0; i < n; i++) {
		list[i].v.x += .5*DT * list[i].a.x;
		list[i].v.y += .5*DT * list[i].a.y;
	}
}
