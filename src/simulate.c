#include <stdlib.h>

#include <state.h>

void handle_walls(Vertex *v)
{
    if (v->pos.y <= POINT_RADIUS)
    {
        v->prev_pos.y = POINT_RADIUS - (v->prev_pos.y - v->pos.y);
        v->pos.y = POINT_RADIUS;
    }
    else if (v->pos.y >= SCREEN_HEIGHT - POINT_RADIUS)
    {
        v->prev_pos.y = (SCREEN_HEIGHT - POINT_RADIUS) + (v->pos.y - v->prev_pos.y);
        v->pos.y = SCREEN_HEIGHT - POINT_RADIUS;
    }
    if (v->pos.x <= POINT_RADIUS)
    {
        v->prev_pos.x = POINT_RADIUS - (v->prev_pos.x - v->pos.x);
        v->pos.x = POINT_RADIUS;
    }
    else if (v->pos.x >= SCREEN_WIDTH - POINT_RADIUS)
    {
        v->prev_pos.x = (SCREEN_WIDTH - POINT_RADIUS) + (v->pos.x - v->prev_pos.x);
        v->pos.x = SCREEN_WIDTH - POINT_RADIUS;
    }
}

void update_points(Vertex *vertices)
{
    for (int _ = 0; _ < MAX_VERTICES; _++)
    {
        if (vertices->initialised && !vertices->fixed)
        {
            Vec2D vel = vec_sub(vertices->pos, vertices->prev_pos);
            vertices->prev_pos = vertices->pos;
            vec_iadd(
                &vertices->pos,
                vec_add(
                    vec_mul(vel, DELTATIME),
                    vec_mul(VEC_GRAV, DELTATIME * DELTATIME / 2)));
            handle_walls(vertices);
        }
        vertices++;
    }
}

void _update_sticks(Edge *edges)
{
    for (int _ = 0; _ < MAX_EDGES; _++)
    {
        if (edges->initialised)
        {
            // Vec2D center = vec_av(edges->a->pos, edges->b->pos);
            // Vec2D vector = vec_sub(edges->a->pos, edges->b->pos);
            // float extension = vec_mag(vector) - edges->length;
            // Vec2D dir = vec_normalize(vector);
            // Vec2D force = vec_mul(dir, STIFFNESS * extension);
            // Vec2D acc = vec_div(force, MASS);
            // printf("a0: (%f, %f)\n", edges->a->pos.x, edges->a->pos.y);
            // printf("b0: (%f, %f)\n", edges->b->pos.x, edges->b->pos.y);
            Vec2D center = vec_av(edges->a->pos, edges->b->pos);
            // printf("center: (%f, %f)\n", center.x, center.y);
            Vec2D dir = vec_normalize(vec_sub(edges->a->pos, edges->b->pos));
            // printf("dir: (%f, %f)\n", dir.x, dir.y);
            // printf("sub: (%f, %f)\n", vec_sub(edges->a->pos, edges->b->pos).x, vec_sub(edges->a->pos, edges->b->pos).y);
            Vec2D change = vec_mul(dir, edges->length / 2);
            if (!edges->a->fixed && edges->a->initialised)
            {
                // printf("a1: (%f, %f)\n", edges->a->pos.x, edges->a->pos.y);
                edges->a->pos = vec_add(center, change);
                // printf("a2: (%f, %f)\n", edges->a->pos.x, edges->a->pos.y);

                // handle_walls(edges->a);
                // handle_walls(edges->a);
            }
            if (!edges->b->fixed && edges->b->initialised)
            {
                // printf("b1: (%f, %f)\n", edges->b->pos.x, edges->b->pos.y);
                edges->b->pos = vec_sub(center, change);
                // printf("b2: (%f, %f)\n", edges->b->pos.x, edges->b->pos.y);

                // handle_walls(edges->b);
                // handle_walls(edges->b);
            }
            if (edges->b->pos.x != edges->b->pos.x)
            {
                exit(1);
            }
        }
        edges++;
    }
}

void update_sticks(Edge *edges)
{
    for (int _ = 0; _ < NUM_ITER; _++) // iterative method so that stick positions
    {                                  // stabilise to match edge positions
        _update_sticks(edges);
    }
}