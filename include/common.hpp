#ifndef COMMON_HPP
#define COMMON_HPP

#include <SDL3/SDL.h>
#include <string>
using std::string;

namespace GameManagerParam
{
    enum GameState
    {
        INIT,
        TITLE,
        EVENT,
        PLAY,
        PAUSE,
        GAMEOVER,
        EXIT
    };
    const string GAME_TITLE = "Mono Jumper";
    const string GAME_VERSION = "0.1";
    constexpr Uint16 WINDOW_WIDTH = 600;
    constexpr Uint16 WINDOW_HEIGHT = 800;
    constexpr Uint64 TARGET_FPS_NANO_SEC = 16666667; // 60fps ~= 16666667ns
}

namespace PlayerParam
{
    constexpr float MAX_HEIGHT = 100.0f;
    constexpr float GRAVITY = 25.0f;
    constexpr float JUMP_POWER = 100.0f;
    constexpr float MAX_DX = 10.0f;
    constexpr float AX = 2.0f;
}

namespace StageParam
{
    constexpr int WIDTH = 600;
    constexpr int HEIGHT = 800;
    constexpr int BLOCK_SIZE = 10;
}

namespace UIParam
{
    namespace Title
    {
        constexpr int FONT_SIZE = 50;
    }

    namespace Game
    {
        // constexpr float FONT_SIZE = 20.0f;
        constexpr int FONT_COLOR = 0;
        Uint16 WINDOW_X = 0;
        Uint16 WINDOW_Y = GameManagerParam::WINDOW_HEIGHT - 150;
        Uint16 WINDOW_WIDTH = GameManagerParam::WINDOW_WIDTH;
        Uint16 WINDOW_HEIGHT = 150;        
    }
}

#endif // COMMON_HPP