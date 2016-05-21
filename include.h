#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define G (double)6.67408e-11
#define DT (double).001

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

typedef struct _camera {
	Vector center;
	double zoom; 

} camera;


#endif
