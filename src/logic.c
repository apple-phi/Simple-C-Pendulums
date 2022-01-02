#include <math.h>
#include <stdlib.h>

#include <state.h>

unsigned int dist_manhatten(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

float dist_euclidean(int x1, int y1, int x2, int y2)
{
    int dx = x1 - x2;
    int dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

Vertex *get_vertex(int x, int y)
{
    Vertex *curr_vert = all_vertices;
    for (int _ = 0; _ < MAX_VERTICES; _++)
    {
        if (curr_vert->initialised && dist_euclidean(curr_vert->pos.x, curr_vert->pos.y, x, y) < POINT_RADIUS * 2)
        {
            return curr_vert;
        }
        curr_vert++;
    };
    return NULL;
}

bool edge_exists(Edge e)
{
    for (int i = 0; i < MAX_EDGES; i++)
    {
        if (all_edges[i].initialised && edge_eq(e, all_edges[i]))
        {
            return true;
        }
    }
    return false;
}

bool vert_exists(Vertex v)
{
    for (int i = 0; i < MAX_EDGES; i++)
    {
        if (all_vertices[i].initialised && vert_eq(v, all_vertices[i]))
        {
            return true;
        }
    }
    return false;
}

Edge *register_edge(Edge e)
{
    for (int i = 0; i < MAX_EDGES; i++)
    {
        if (!all_edges[i].initialised)
        {
            all_edges[i] = e;
            return &all_edges[i];
        }
    }
    return NULL;
}

Vertex *register_vert(Vertex v)
{
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        if (!all_vertices[i].initialised)
        {
            all_vertices[i] = v;
            return &all_vertices[i];
        }
    }
    return NULL;
}

Vertex *latest_vert;
void mouse_down(int x, int y)
{
    Vertex *existing_vert = get_vertex(x, y);
    if (latest_vert && latest_vert->initialised && existing_vert && existing_vert->initialised && !vert_eq(*latest_vert, *existing_vert))
    {
        Edge new_edge = initialise(Edge,
                                   existing_vert,
                                   latest_vert,
                                   dist_euclidean(x, y, latest_vert->pos.x, latest_vert->pos.y));
        if (!edge_exists(new_edge))
        {
            register_edge(new_edge);
        }
        latest_vert = existing_vert;
        MOUSE_STATE.pressed = false; // final action
    }
}

void mouse_up(int x, int y)
{
    Vertex *existing_vert = get_vertex(x, y);
    if (existing_vert)
    {
        if (vert_eq(*latest_vert, *existing_vert))
        {
            existing_vert->fixed = !existing_vert->fixed;
            latest_vert = existing_vert;
        }
    }
    else
    {
        Vertex new_vert = initialise(Vertex, {x, y}, {x, y}, false);
        Vertex *v = register_vert(new_vert);
        if (v)
        {
            latest_vert = v;
        }
    }
}
