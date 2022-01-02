#include <stdio.h>

#include "vectors.h"

#ifndef PARAMS_H
#define PARAMS_H

const int SCREEN_WIDTH;
const int SCREEN_HEIGHT;

#define BG_COLOR 179, 136, 235, 255
#define POINT_COLOR 233, 250, 227, 255
#define FIXED_POINT_COLOR 67, 154, 134, 255
#define LINE_COLOR 65, 64, 102, 255

const float DELTATIME;
const int NUM_ITER;

const float GRAV_FIELD_STRENGTH;
const Vec2D VEC_GRAV;

const float MASS;
const float STIFFNESS;

const int POINT_RADIUS;
const int MAX_VERTICES;
const int MAX_EDGES;

extern Vertex all_vertices[];
extern Edge all_edges[];

struct MOUSE_STATE
{
    int x, y;
    bool pressed;
} MOUSE_STATE;

bool simulating;
void reset_state();

#endif