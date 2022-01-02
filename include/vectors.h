#include <stdbool.h>
#include <stddef.h>

#ifndef VECTORS_H
#define VECTORS_H

#define initialise(type, ...) \
    (type) { __VA_ARGS__, true }

typedef struct Vec2D
{
    float x, y;
} Vec2D;
typedef struct Vertex
{
    Vec2D pos;
    Vec2D prev_pos;
    bool fixed;
    bool initialised;
} Vertex;
typedef struct Edge
{
    struct Vertex *a;
    struct Vertex *b;
    float length;
    bool initialised;
} Edge;

float vec_mag(Vec2D v);
Vec2D vec_add(Vec2D v1, Vec2D v2);
Vec2D vec_sub(Vec2D v1, Vec2D v2);
Vec2D vec_mul(Vec2D v, float p);
Vec2D vec_div(Vec2D v, float p);
void vec_iadd(Vec2D *v1, Vec2D v2);
void vec_isub(Vec2D *v1, Vec2D v2);
void vec_imul(Vec2D *v, float p);
void vec_idiv(Vec2D *v, float p);
Vec2D vec_normalize(Vec2D v);
void vec_inormalize(Vec2D *v);
Vec2D vec_av(Vec2D a, Vec2D b);

bool vec_eq(Vec2D v1, Vec2D v2);
bool vert_eq(Vertex v1, Vertex v2);
bool edge_eq(Edge v1, Edge v2);

size_t seq_len(void *seq, size_t size);

#endif