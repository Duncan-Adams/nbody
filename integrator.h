#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "include.h"

void acceleration(Body* list, int n);

void integrate(Body* list, int n, double dt); /* intgeration using leapfrog method */

#endif
