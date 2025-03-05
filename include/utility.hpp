#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SDL3/SDL.h>

inline void MYDL_RenderBoldLineRect(SDL_Renderer *renderer, float x, float y, float w, float h, float thickness);
inline bool IsConflictRectAndPoint(float x1, float y1, float w1, float h1, float x2, float y2);
inline bool IsConflictRectAndRect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

/* (x,y)を左上頂点とする太線のrectを描画します */
inline void MYDL_RenderBoldLineRect(SDL_Renderer *renderer, float x, float y, float w, float h, float thickness)
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

/* rectと点の衝突判定 */
inline bool IsConflictRectAndPoint(float x1, float y1, float w1, float h1, float x2, float y2)
{
    if(x1 < x2 && x2 < x1 + w1 && y1 < y2 && y2 < y1 + h1)
    {
        return true;
    }
    return false;
}

/* rectとrectの衝突判定 */
inline bool IsConflictRectAndRect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
    if(x1 < x2 + w2 && x2 < x1 + w1 && y1 < y2 + h2 && y2 < y1 + h1)
    {
        return true;
    }
    return false;
}

#endif // UTILITY_HPP
