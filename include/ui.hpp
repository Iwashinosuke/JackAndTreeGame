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
        TitleUI(void)
        {
            
        }

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
        GameUI(void)
        {

        }

        void UpdateRender(SDL_Window *window, SDL_Renderer *renderer) override
        {
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
            
            SDL_FRect rect1;
            rect1.x = Game::WINDOW_X;
            rect1.y = Game::WINDOW_Y;
            rect1.w = Game::WINDOW_WIDTH;
            rect1.h = Game::WINDOW_HEIGHT;
            SDL_RenderFillRect(renderer, &rect1); 

            SDL_SetRenderDrawColor(renderer, 80, 80, 80, SDL_ALPHA_OPAQUE);
            
            MYDL_RenderBoldLineRect(renderer, Game::WINDOW_X, Game::WINDOW_Y, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT, 10);
            MYDL_RenderBoldLineRect(renderer, Game::WINDOW_X+15, Game::WINDOW_Y+15, Game::WINDOW_WIDTH-30, Game::WINDOW_HEIGHT-30, 8);
        }
    private:
        const Uint64 score = 0;
        const float score_text_x = Game::WINDOW_X + Game::WINDOW_WIDTH / 2 - 50;
        const float score_text_y = Game::WINDOW_Y + Game::WINDOW_HEIGHT / 3;
        const float info_text_x = Game::WINDOW_X + Game::WINDOW_WIDTH / 2 - 100;
        const float info_text_y = Game::WINDOW_Y + Game::WINDOW_HEIGHT / 3 + 50;    
};

class PauseUI : public UIBase
{
    public:
        PauseUI(void)
        {

        }

        void UpdateRender(SDL_Window *window, SDL_Renderer *renderer) override
        {
            SDL_SetRenderScale(renderer, 2.0f, 2.0f);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); 
            SDL_RenderDebugText(renderer, 33, GameManagerParam::WINDOW_HEIGHT/5, "PAUSE");
        }
    private:    

};

class GameOverUI : public UIBase
{
    public:
        GameOverUI(void)
        {
            
        }

        void UpdateRender(SDL_Window *window, SDL_Renderer *renderer) override
        {
            SDL_SetRenderScale(renderer, 4.0f, 4.0f);
            SDL_SetRenderDrawColor(renderer, 200, 0, 0, SDL_ALPHA_OPAQUE); 
            SDL_RenderDebugText(renderer, 33, GameManagerParam::WINDOW_HEIGHT/10, "GAME OVER");
        }
    private:    
        
};

#endif // UI_HPP
