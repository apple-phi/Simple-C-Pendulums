#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>

#include <vectors.h>

float vec_mag(Vec2D v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}
Vec2D vec_add(Vec2D v1, Vec2D v2)
{
    return (Vec2D){v1.x + v2.x, v1.y + v2.y};
}
void vec_iadd(Vec2D *v1, Vec2D v2)
{
    v1->x += v2.x;
    v1->y += v2.y;
}
Vec2D vec_sub(Vec2D v1, Vec2D v2)
{
    return (Vec2D){v1.x - v2.x, v1.y - v2.y};
}
void vec_isub(Vec2D *v1, Vec2D v2)
{
    v1->x -= v2.x;
    v1->y -= v2.y;
}
Vec2D vec_mul(Vec2D v, float p)
{
    return (Vec2D){v.x * p, v.y * p};
}
void vec_imul(Vec2D *v, float p)
{
    v->x *= p;
    v->y *= p;
}
Vec2D vec_div(Vec2D v, float p)
{
    return (Vec2D){v.x / p, v.y / p};
}
void vec_idiv(Vec2D *v, float p)
{
    v->x /= p;
    v->y /= p;
}
Vec2D vec_normalize(Vec2D v)
{
    float length = vec_mag(v);
    Vec2D new = {v.x / length,
                 v.y / length};
    return new;
}
void vec_inormalize(Vec2D *v)
{
    float length = vec_mag(*v);
    v->x /= length;
    v->x /= length;
}
Vec2D vec_av(Vec2D a, Vec2D b)
{
    return (Vec2D){(a.x + b.x) / 2, (a.y + b.y) / 2};
}

// Vec2D new_vec(float x, float y)
// {
//     return (Vec2D){x, y, true};
// };
// Vertex new_vert(Vec2D pos,
//                 Vec2D vel,
//                 bool fixed)
// {
//     return (Vertex){pos, vel, fixed, true};
// }
//
// bool vec_initialised(Vec2D v)
// {
//     return !(v.x == v.y == 0);
// }
// bool vert_initialised(Vertex v)
// {
//     return vec_initialised(v.pos); // only check position
// }
// bool edge_initialised(Edge e)
// {
//     return e.a != NULL && e.b != NULL && e.length != 0;
// }

bool vec_eq(Vec2D v1, Vec2D v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}
bool vert_eq(Vertex v1, Vertex v2)
{
    return vec_eq(v1.pos, v2.pos) && vec_eq(v1.prev_pos, v2.prev_pos);
}
bool edge_eq(Edge v1, Edge v2)
{
    return (vert_eq(*v1.a, *v2.a) && vert_eq(*v1.b, *v2.b)) || (vert_eq(*v1.a, *v2.b) && vert_eq(*v1.b, *v2.a));
}

size_t seq_len(void *seq, size_t size)
{
    return size / sizeof *seq;
}