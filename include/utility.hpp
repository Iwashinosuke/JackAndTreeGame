#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SDL3/SDL.h>

void MYDL_RenderBoldLineRect(SDL_Renderer *renderer, float x, float y, float w, float h, float thickness);


void MYDL_RenderBoldLineRect(SDL_Renderer *renderer, float x, float y, float w, float h, float thickness)
{
    SDL_FRect rects[4];

    rects[0].x = x;
    rects[0].y = y;
    rects[0].w = w;
    rects[0].h = thickness;

    rects[1].x = x;
    rects[1].y = y;
    rects[1].w = thickness;
    rects[1].h = h;

    rects[2].x = x;
    rects[2].y = y + h - thickness;
    rects[2].w = w;
    rects[2].h = thickness;

    rects[3].x = x + w - thickness;
    rects[3].y = y;
    rects[3].w = thickness;
    rects[3].h = h;

    SDL_RenderFillRects(renderer, rects, 4);
}

#endif // UTILITY_HPP
