#ifndef UI_HPP
#define UI_HPP

#include "common.hpp"
#include "utility.hpp"


using namespace UIParam;

typedef class TitleUI TitleUI;
typedef class GameUI GameUI;


extern TitleUI titleUi;
extern GameUI gameUi;

class TitleUI
{
    public:
        TitleUI(void)
        {

        }

        void UpdateRender(SDL_Window *window, SDL_Renderer *renderer)
        {
            SDL_FRect rect;
            rect.x = 0;
            rect.y = 0;
            rect.w = GameManagerParam::WINDOW_WIDTH;
            rect.h = GameManagerParam::WINDOW_HEIGHT;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderRect(renderer, &rect); 
        }
    private:    

};  

class GameUI
{
    public:
        GameUI(void)
        {

        }

        void UpdateRender(SDL_Window *window, SDL_Renderer *renderer)
        {
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
            
            SDL_FRect rect1;
            rect1.x = Game::WINDOW_X;
            rect1.y = Game::WINDOW_Y;
            rect1.w = Game::WINDOW_WIDTH;
            rect1.h = Game::WINDOW_HEIGHT;
            SDL_RenderFillRect(renderer, &rect1); 

            SDL_SetRenderDrawColor(renderer, 10, 10, 10, 100);
            
            // SDL_FRect rects2[2];
            // rects2[0].x = Game::WINDOW_X;
            // rects2[0].y = Game::WINDOW_Y;
            // rects2[0].w = Game::WINDOW_WIDTH;
            // rects2[0].h = 10;
            // rects2[1].x = Game::WINDOW_X;
            // rects2[1].y = Game::WINDOW_Y + Game::WINDOW_HEIGHT -10;
            // rects2[1].w = Game::WINDOW_WIDTH;
            // rects2[1].h = 10;
            // SDL_RenderFillRects(renderer, rects2, 2);
            MYDL_RenderBoldLineRect(renderer, Game::WINDOW_X, Game::WINDOW_Y, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT, 10);
            MYDL_RenderBoldLineRect(renderer, Game::WINDOW_X+15, Game::WINDOW_Y+15, Game::WINDOW_WIDTH-30, Game::WINDOW_HEIGHT-30, 8);

            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

            SDL_SetRenderScale(renderer, 1.5f, 1.5f);
            SDL_SetRenderDrawColor(renderer, 10, 10, 10, SDL_ALPHA_OPAQUE); 
            SDL_RenderDebugTextFormat(renderer, 10, 30, "score x y %" SDL_PRIu64 " %" SDL_PRIu64, (Uint64)score_text_x, (Uint64)score_text_y);
            SDL_RenderDebugTextFormat(renderer, score_text_x, score_text_y , "SCORE: %" SDL_PRIs32 , 100000);
            SDL_SetRenderScale(renderer, 2.0f, 2.0f);
            SDL_RenderDebugTextFormat(renderer, 10, 200, "Press SPACE to jump");
            SDL_RenderDebugTextFormat(renderer, info_text_x, info_text_y, "Press SPACE to jump");
            SDL_SetRenderScale(renderer, 1.0f, 1.0f);
        }
    private:
        const Uint64 score = 0;
        const float score_text_x = Game::WINDOW_X + Game::WINDOW_WIDTH / 2 - 50;
        const float score_text_y = Game::WINDOW_Y + Game::WINDOW_HEIGHT / 3;
        const float info_text_x = Game::WINDOW_X + Game::WINDOW_WIDTH / 2 - 100;
        const float info_text_y = Game::WINDOW_Y + Game::WINDOW_HEIGHT / 3 + 50;    
};

#endif // UI_HPP
