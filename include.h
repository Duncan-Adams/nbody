#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#define G (double)1.0
#define DT (double).001 /* measured in seconds */

#define N_TRACK 3000

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
	
	uint32_t color;
	uint8_t track;
	
	Vector *history;
	
	uint16_t n_stored;
	uint16_t start;
	int index;
	
} Body;

typedef struct _camera {
	Vector center;
	double zoom; 

} camera;


#endif
