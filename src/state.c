#include <state.h>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

const float DELTATIME = 1; // ms
const int NUM_ITER = 1;    // for edge stabilisation

const float GRAV_FIELD_STRENGTH = 9.81 / 10;     // ms^-2
const Vec2D VEC_GRAV = {0, GRAV_FIELD_STRENGTH}; // ms^-2

const float MASS = 10;
const float STIFFNESS = 2;

const int POINT_RADIUS = 10;
static const int POINT_DIAMETER = 2 * POINT_RADIUS;
static const int POINT_GAP = 3 * POINT_DIAMETER;

static const int MAX_X_VERTICES = SCREEN_WIDTH / (POINT_DIAMETER + POINT_GAP);
static const int MAX_Y_VERTICES = SCREEN_HEIGHT / (POINT_DIAMETER + POINT_GAP);
const int MAX_VERTICES = MAX_X_VERTICES * MAX_Y_VERTICES;
const int MAX_EDGES = 2 * MAX_VERTICES - MAX_X_VERTICES - MAX_Y_VERTICES; // simplified from x(y-1) + y(x-1)

Vertex all_vertices[MAX_VERTICES];
Edge all_edges[MAX_EDGES];

bool simulating;
void reset_state()
{
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        all_vertices[i].initialised = false;
        all_edges[i].initialised = false;
    }
    all_vertices[0] = initialise(Vertex, {100, 50}, {100, 50}, true);
    all_vertices[1] = initialise(Vertex, {400, 80}, {400, 80}, true);
    simulating = false;
};
