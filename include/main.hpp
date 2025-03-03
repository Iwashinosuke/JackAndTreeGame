#ifndef MAIN_HPP
#define MAIN_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include "game_manager.hpp"
#include "player.hpp"

void    CapFrameRate    (Uint64 targetFpsNanoSec);
Uint64  CalcFps         ( void );

#endif // MAIN_HPP