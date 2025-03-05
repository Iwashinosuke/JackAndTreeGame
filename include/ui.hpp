#ifndef UI_HPP
#define UI_HPP

#include "common.hpp"
#include "utility.hpp"


using namespace UIParam;

typedef class UIBase UIBase;    
typedef class TitleUI TitleUI;
typedef class GameUI GameUI;
typedef class PauseUI PauseUI;
typedef class GameOverUI GameOverUI;


extern TitleUI titleUi;
extern GameUI gameUi;
extern PauseUI pauseUi;
extern GameOverUI gameOverUi;

class UIBase
{
    public:
        virtual void UpdateRender(SDL_Window *window, SDL_Renderer *renderer){}
};

class TitleUI : public UIBase
{
    public:
        void UpdateRender(SDL_Window *window, SDL_Renderer *renderer) override
        {
            SDL_SetRenderScale(renderer, 4.0f, 4.0f);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); 
            SDL_RenderDebugText(renderer, 31, GameManagerParam::WINDOW_HEIGHT/10, "Mono Jumper");
            SDL_SetRenderScale(renderer, 2.0f, 2.0f);
            SDL_RenderDebugText(renderer, 50, GameManagerParam::WINDOW_HEIGHT/3+50, "Press Any Button To Start");
        }
    private:    
        SDL_Surface *text_surfaces;
        int text_cnt;
};  

class GameUI : public UIBase
{
    public:
        void UpdateRender(SDL_Window *window, SDL_Renderer *renderer) override
        {
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
            
            SDL_FRect rect1;
            rect1.x = Game::WINDOW_X;
            rect1.y = Game::WINDOW_Y;
            rect1.w = Game::WINDOW_WIDTH;
            rect1.h = Game::WINDOW_HEIGHT;
            SDL_RenderFillRect(renderer, &rect1); 

            SDL_SetRenderDrawColor(renderer, 180, 180, 180, SDL_ALPHA_OPAQUE);
            
            MYDL_RenderBoldLineRect(renderer, Game::WINDOW_X, Game::WINDOW_Y, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT, 10);
            MYDL_RenderBoldLineRect(renderer, Game::WINDOW_X+15, Game::WINDOW_Y+15, Game::WINDOW_WIDTH-30, Game::WINDOW_HEIGHT-30, 8);
        
            SDL_SetRenderScale(renderer, 1.8f, 1.8f);           
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderDebugTextFormat(renderer, 130,390, "SCORE: %" SDL_PRIu64, score);
            SDL_SetRenderScale(renderer, 1.4f, 1.4f); 
            SDL_RenderDebugText(renderer, 150, 520, "Press P to Pause");
        }
    private:
        Uint64 score = 0;  
};

class PauseUI : public UIBase
{
    public:
        void UpdateRender(SDL_Window *window, SDL_Renderer *renderer) override
        {
            SDL_SetRenderScale(renderer, 2.0f, 2.0f);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); 
            SDL_RenderDebugText(renderer, GameManagerParam::WINDOW_WIDTH/5+6, GameManagerParam::WINDOW_HEIGHT/5, "PAUSE");
            SDL_SetRenderScale(renderer, 1.5f, 1.5f);
            SDL_RenderDebugText(renderer, GameManagerParam::WINDOW_WIDTH/5+2, GameManagerParam::WINDOW_HEIGHT/5+80, "Press P to Resume");

            SDL_SetRenderScale(renderer, 1.8f, 1.8f);           
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderDebugTextFormat(renderer, 130,390, "SCORE: %" SDL_PRIu64, score);
            SDL_SetRenderScale(renderer, 1.4f, 1.4f); 
            SDL_RenderDebugText(renderer, 130, 390, "Press P to Pause");
        }
    private:    
        Uint64 score = 0;
};

class GameOverUI : public UIBase
{
    public:
        void UpdateRender(SDL_Window *window, SDL_Renderer *renderer) override
        {
            SDL_SetRenderScale(renderer, 4.0f, 4.0f);
            SDL_SetRenderDrawColor(renderer, 200, 0, 0, SDL_ALPHA_OPAQUE); 
            SDL_RenderDebugText(renderer, 40, GameManagerParam::WINDOW_HEIGHT/10, "GAME OVER");
        }        
};

#endif // UI_HPP
