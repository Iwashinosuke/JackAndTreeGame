#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SDL3/SDL.h>
#include "common.hpp"

using namespace GameManagerParam;

typedef class   GameManager GameManager;
extern GameManager game_manager;


class GameManager
{
    public:
        GameManager()
        {
            _state = GameState::INIT;
            _title = GAME_TITLE;
            _version = GAME_VERSION;
            _window_width = WINDOW_WIDTH;
            _window_height = WINDOW_HEIGHT;
        };

        int InitGameManager(void)
        {
            // _state = GameState::TITLE;
            return 0;
        }

        GameState UpdateInput(SDL_Event *event)
        {
            if(_state == GameState::INIT)
            {
                _state = GameState::TITLE;
            }
            else if(_state == GameState::TITLE)
            {
                /* "Press Any Button To Start"を実装 */
                if(event->type == SDL_EVENT_KEY_DOWN)
                {
                    _state = GameState::PLAY;
                }
            }
            else if(_state == GameState::PLAY)
            {
                if(event->type == SDL_EVENT_KEY_DOWN)
                {
                    switch(event->key.scancode)
                    {
                        case SDL_SCANCODE_P:
                            _state = GameState::PAUSE;
                            break;
                    }
                }
            }
            else if(_state == GameState::PAUSE)
            {
                if(event->type == SDL_EVENT_KEY_DOWN)
                {
                    switch(event->key.scancode)
                    {
                        case SDL_SCANCODE_P:
                            _state = GameState::PLAY;
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            _state = GameState::EXIT;
                            break;
                    }
                }
            }
            else if(_state == GameState::GAMEOVER)
            {
                if(event->type == SDL_EVENT_KEY_DOWN)
                {
                    switch(event->key.scancode)
                    {
                        case SDL_SCANCODE_SPACE:
                            _state = GameState::PLAY;
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            _state = GameState::EXIT;
                            break;
                    }
                }
            }


            return _state;
        }
        void CallGameOver(void)
        {
            _state = GameState::GAMEOVER;
        }

        GameState GetState(void) const { return _state; }
        string GetTitle(void) const { return _title; }
        string GetVersion(void) const { return _version; }
        int GetWindowWidth(void) const { return _window_width; }
        int GetWindowHeight(void) const { return _window_height; }
    private:
        /* データ */
        GameState _state;
        string _title;
        string _version;
        int _window_width;
        int _window_height;
};

#endif // GAMEMANAGER_HPP