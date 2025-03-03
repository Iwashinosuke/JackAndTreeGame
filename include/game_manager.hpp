#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SDL3/SDL.h>
#include <string>
using std::string;
#include "structs.hpp"

typedef class   GameManager GameManager;
typedef enum GameState
{
    GAME_STATE_INIT,
    GAME_STATE_TITLE,
    GAME_STATE_EVENT,
    GAME_STATE_PLAY,
    GAME_STATE_PAUSE,
    GAME_STATE_GAMEOVER,
    GAME_STATE_EXIT
}GameState;

extern GameManager game_manager;

class GameManager
{
public:
    GameManager()
    {
        _state = GAME_STATE_INIT;
        _title = "Jack And Tree";
        _version = "0.1";
        _window_width = 600;
        _window_height = 800;
    };
    GameState getState(void) const { return _state; }
    string getTitle(void) const { return _title; }
    string getVersion(void) const { return _version; }
    int getWindowWidth(void) const { return _window_width; }
    int getWindowHeight(void) const { return _window_height; }
private:
    /* データ */
    GameState _state;
    string _title;
    string _version;
    int _window_width;
    int _window_height;
};

#endif // GAMEMANAGER_HPP