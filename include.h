#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define G 6.67408e-11

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


#endif
