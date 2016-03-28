#include <math.h>
#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>
#include <fcntl.h>
#include <memory.h>
#include <io.h>

#include <iostream>

#include <intrin.h>

#include "inc/GL/gl.h"
#include <GL/glu.h>

#include "SDL.h"
#include "SDL_main.h"

#include "mathlib.h"
#include "load3ds.h"
#include "loadjpeg.h"

#define SIZE 	128
#define WIDTH	640
#define HEIGHT	480

int     my_lighting, my_wireframe, my_pause, my_blur = 1;
int     shadow_id, mesh_id, texture_id, ground_id, lamp_id;
float   phi   = -30,psi,dist = 3,angle;
vec3    camera;
vec4    light = { 2, 0, 3, 1 };
vec3    mesh  = { 0, 0, 1 };

unsigned char *image;


