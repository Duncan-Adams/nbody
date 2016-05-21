#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "include.h"

void acceleration(Body *b1, Body *b2);

void integrate(Body* list, int n, double dt);

#endif
