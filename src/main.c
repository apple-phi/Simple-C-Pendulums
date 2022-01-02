#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include <SDL.h>

#include <simulate.h>
#include <logic.h>
#include <drawing.h>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;

time_t mouse_lift_time;

// bool mouse_down;

void init(const char *title, int x, int y, int w, int h, Uint32 flags)
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "3");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow(title, x, y, w, h, flags);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == NULL)
            {
                printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
            }
            else
            {
                texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h);
                if (texture == NULL)
                {
                    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
                }
            }
        }
    }
}
void pump_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
    }
}
void quit()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_Quit();
}

void draw_vertex(Vertex *v)
{
    if (v->fixed)
    {
        SDL_SetRenderDrawColor(renderer, FIXED_POINT_COLOR);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, POINT_COLOR);
    }
    // SDL_RenderDrawLine(renderer, v->pos.x - POINT_RADIUS, v->pos.y - POINT_RADIUS, v->pos.x + POINT_RADIUS, v->pos.y + POINT_RADIUS);
    // SDL_RenderDrawLine(renderer, v->pos.x + POINT_RADIUS, v->pos.y - POINT_RADIUS, v->pos.x - POINT_RADIUS, v->pos.y + POINT_RADIUS);
    fill_circle(renderer, v->pos.x, v->pos.y, POINT_RADIUS);
}

void draw_vertices()
{
    Vertex *curr_vert = all_vertices;
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        if (curr_vert->initialised)
        {
            // printf("hurghh %i >< (%f, %f)\n", curr_vert->initialised, curr_vert->pos.x, curr_vert->pos.y);
            draw_vertex(curr_vert);
        }
        curr_vert++;
    }
}

void draw_edges()
{
    SDL_SetRenderDrawColor(renderer, LINE_COLOR);
    Edge *curr_edge = all_edges;
    for (int i = 0; i < MAX_EDGES; i++)
    {
        if (curr_edge->initialised && curr_edge->a->initialised && curr_edge->b->initialised)
        {
            // printf("(%i, %i) -> (%i, %i)\n", curr_edge->a->pos.x, curr_edge->a->pos.y, curr_edge->b->pos.x, curr_edge->b->pos.y);
            SDL_RenderDrawLine(renderer, curr_edge->a->pos.x, curr_edge->a->pos.y, curr_edge->b->pos.x, curr_edge->b->pos.y);
        }
        curr_edge++;
    }
}

bool handle_events()
{
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            MOUSE_STATE.pressed = true;
            break;
        case SDL_MOUSEBUTTONUP:
            if (MOUSE_STATE.pressed)
            {
                mouse_up(MOUSE_STATE.x, MOUSE_STATE.y);
                MOUSE_STATE.pressed = false;
            }
            break;
        case SDL_KEYUP:

            switch (event.key.keysym.sym)
            {
            case SDLK_SPACE:
                simulating = true;
                break;
            case SDLK_r:
                reset_state();
                break;
            }
            break;
        }
    }
    return event.type != SDL_QUIT;
}

void draw_frame()
{
    if (MOUSE_STATE.pressed)
    {
        mouse_down(MOUSE_STATE.x, MOUSE_STATE.y);
    }
    if (simulating)
    {
        update_points(all_vertices);
        update_sticks(all_edges);
    }
    draw_vertices();
    draw_edges();
}

void log_errors()
{
    const char *error = SDL_GetError();
    if (*error)
    {
        SDL_Log("SDL error: %s", error);
        SDL_ClearError();
    }
}

void event_loop()
{
    while (handle_events())
    {
        SDL_SetRenderDrawColor(renderer, BG_COLOR);
        SDL_RenderClear(renderer);
        SDL_GetMouseState(&MOUSE_STATE.x, &MOUSE_STATE.y);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        draw_frame();
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
        log_errors();
    }
}

int main(int argc, char *argv[])
{
    reset_state();
    init("🍏", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    event_loop();
    quit();
    return 0;
}