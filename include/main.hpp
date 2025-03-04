#ifndef MAIN_HPP
#define MAIN_HPP

#include <SDL3/SDL_main.h>
#include "game_manager.hpp"
#include "player.hpp"
#include "stage.hpp"
#include "ui.hpp"
#include "utility.hpp"

void    CapFrameRate    (Uint64 targetFpsNanoSec);
Uint64  CalcFps         ( void );

#endif // MAIN_HPP