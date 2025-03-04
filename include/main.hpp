#ifndef MAIN_HPP
#define MAIN_HPP

#include "game_manager.hpp"
#include "player.hpp"
#include "stage.hpp"
#include "ui.hpp"
#include "utility.hpp"

void    CapFrameRate    (Uint64 targetFpsNanoSec);
Uint64  CalcFps         ( void );

#endif // MAIN_HPP