/*** -注 common.hpp内で他の変数の値を用いて定義する場合、初期化順序が保証されてないことに注意 ***/

#ifndef COMMON_HPP
#define COMMON_HPP

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <string>
using std::string;

namespace GameManagerParam
{
    enum GameState
    {
        INIT,
        TITLE,
        PLAY,
        PAUSE,
        GAMEOVER,
        EXIT
    };
    inline const string GAME_TITLE = "Mono Jumper";
    inline const string GAME_VERSION = "0.1";
    inline constexpr Uint16 WINDOW_WIDTH = 600;
    inline constexpr Uint16 WINDOW_HEIGHT = 800;
    inline constexpr Uint64 TARGET_FPS = 60; // 60fps, 変更時はTARGET_FPS_NANO_SECも変更
    inline constexpr Uint64 TARGET_FPS_NANO_SEC = 16666667; // 60fps ~= 16666667ns
}

// namespace InputParam
// {
//     enum class Keys
//     {
//         CHARGE,
//         MOVE_LEFT,
//         MOVE_RIGHT,
//         PAUSE,
//         MENU,
//         EXIT
//     };
// }

namespace PlayerParam
{
    enum class PlayerState
    {
        INIT,
        PLAY,
        PAUSE,
        GAMEOVER,
        EXIT
    };
    inline constexpr float MAX_CHARGE_TIME = 1.5f; // FPS準拠、大体の時間
    inline constexpr float CHARGE_ADDR = 1 / (MAX_CHARGE_TIME * GameManagerParam::TARGET_FPS);
    inline constexpr float MAX_JUMP_POWER = 20.0f;
    inline constexpr float JUMP_POWER_LOSS = 1.0f;
    inline constexpr float MAX_FALL_POWER = 10.0f;
    inline constexpr float FALL_POWER_ADDR = 0.5f;
}

namespace StageParam
{
    inline constexpr int WIDTH = 600;
    inline constexpr int HEIGHT = 800;
    inline constexpr int BLOCK_SIZE = 10;
}

namespace UIParam
{
    namespace Title
    {
        inline constexpr int FONT_SIZE = 50;
    }

    namespace Game
    {
        // constexpr float FONT_SIZE = 20.0f;
        inline constexpr int FONT_COLOR = 0;
        inline constexpr Uint16 WINDOW_X = 0;
        inline constexpr Uint16 WINDOW_Y = GameManagerParam::WINDOW_HEIGHT - 150;
        inline constexpr Uint16 WINDOW_WIDTH = GameManagerParam::WINDOW_WIDTH;
        inline constexpr Uint16 WINDOW_HEIGHT = 150;        
    }
}


#endif // COMMON_HPP