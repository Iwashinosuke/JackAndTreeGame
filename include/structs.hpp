#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <SDL3/SDL.h>

typedef struct App          app_t;
typedef struct Mouse        mouse_t;
typedef struct Keyboard     keyboard_t;

struct App
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    mouse_t *mouse;
    keyboard_t *keyboard;
};

struct  Mouse
{
    /* data */
};

struct Keyboard
{
    /* data */
};



#endif // STRUCTS_HPP