#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <SDL3/SDL.h>

inline void MYDL_RenderBoldLineRect(SDL_Renderer *renderer, float x, float y, float w, float h, float thickness);
inline bool IsConflictRectAndPoint(float x1, float y1, float w1, float h1, float x2, float y2);
inline bool IsConflictFRects(SDL_FRect *rect1, SDL_FRect *rect2);

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
inline bool IsConflictFRects(SDL_FRect *rect1, SDL_FRect *rect2)
{
    /* rect1, rect2の各頂点を基準に計算 */
    if(
        IsConflictRectAndPoint(rect2->x, rect2->y, rect2->w, rect2->h, rect1->x, rect1->y) ||
        IsConflictRectAndPoint(rect2->x, rect2->y, rect2->w, rect2->h, rect1->x + rect1->w, rect1->y) ||
        IsConflictRectAndPoint(rect2->x, rect2->y, rect2->w, rect2->h, rect1->x, rect1->y + rect1->h) ||
        IsConflictRectAndPoint(rect2->x, rect2->y, rect2->w, rect2->h, rect1->x + rect1->w, rect1->y + rect1->h) ||
        
        IsConflictRectAndPoint(rect1->x, rect1->y, rect1->w, rect1->h, rect2->x, rect2->y) ||
        IsConflictRectAndPoint(rect1->x, rect1->y, rect1->w, rect1->h, rect2->x + rect2->w, rect2->y) ||
        IsConflictRectAndPoint(rect1->x, rect1->y, rect1->w, rect1->h, rect2->x, rect2->y + rect2->h) ||
        IsConflictRectAndPoint(rect1->x, rect1->y, rect1->w, rect1->h, rect2->x + rect2->w, rect2->y + rect2->h)
    )
    {
        return true;
    }
    return false;
}

/* (cx,cy)を中心として単位時間あたりで点滅するrectを描画します この関数で描画されるrectは、点滅間隔が共有されるため使用法に注意 */
inline void RenderBlinkRect(SDL_Renderer *renderer, Uint16 cx, Uint16 cy)
{
    static Uint64 prevTime;
    static bool lighting = true;
    static Uint8 size = 20;
    Uint64 blink_intensity = 500;

    Uint64 current = SDL_GetTicks();
    Uint64 elapsed = current - prevTime;
    if(elapsed > blink_intensity)
    {
        lighting = !lighting;
        prevTime = current;
    }

    SDL_FRect rect;
    rect.x = cx - size / 2;
    rect.y = cy - size / 2;
    rect.w = size;
    rect.h = size;
    if(lighting)
    {
        SDL_SetRenderDrawColor(renderer, 255, 150, 50, SDL_ALPHA_OPAQUE);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 200, 100, 10, SDL_ALPHA_OPAQUE);
    }

    SDL_RenderFillRect(renderer, &rect);
}

/* (cx,cy)を中心として単位時間あたりで輝くdiamondを描画します この関数で描画される対象は、点滅間隔が共有されるため使用法に注意 */
inline void RenderRainbowDiamond(SDL_Renderer *renderer, Uint16 cx, Uint16 cy)
{
    static Uint8 baseCol;
    static Uint16 size = 50;
    static Uint64 rainbow_intensity = 500;
    SDL_FRect rect;
    rect.x = cx - size / 2;
    rect.y = cy - size / 2;
    rect.w = size;
    rect.h = size;
    


    for(Uint16 rx=0; rx < size/2; rx++)
    {
        SDL_SetRenderDrawColor(renderer, baseCol+rx, baseCol+61+rx, baseCol+101+rx, SDL_ALPHA_OPAQUE);
        SDL_RenderLine(renderer, cx+rx, -size/2+cy+rx, -size/2+cx+rx, cy+rx);
    }

    baseCol++;
}

#endif // UTILITY_HPP
