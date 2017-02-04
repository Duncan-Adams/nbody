#include "config.h"
#include "include.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


extern int nbodies;
extern Body* body_list;

static uint32_t string_color(char *s) {
	if (strcmp(s, "red") == 0)
		return 0x990000ff;
	if (strcmp(s, "blue") == 0)
		return 0x191970ff;
	if (strcmp(s, "green") == 0)
		return 0x008000ff;
		
	return 0x990000ff;
}

void read_cfg(char *path) {
	int i = 0;
	
	char color[32];
	
	FILE *z = fopen(path, "r");
	if(!z) exit(EXIT_FAILURE);
	
	fscanf(z, "nbodies:%d\n", &nbodies);
	
	body_list = malloc(sizeof(Body) * nbodies);
	
	for(i = 0; i < nbodies; i++) {
		fscanf(z, "[BODY]\n");
		fscanf(z, "pos=<%lf,%lf>\n", &body_list[i].r.x, &body_list[i].r.y);
		fscanf(z, "vel=<%lf,%lf>\n", &body_list[i].v.x, &body_list[i].v.y);
		fscanf(z, "mass=%lf\n", &body_list[i].m);
		fscanf(z, "color=%s\n", color);
		
		color[31] = '\0';
		body_list[i].color = string_color(color);
	}
	

		
	
	fclose(z);
	return;
}

