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