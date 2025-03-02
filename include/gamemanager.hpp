#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "structs.hpp"

class GameManager
{
private:
    /* data */
    app_t *app;
    mouse_t *mouse;
    keyboard_t *keyboard;
public:
    GameManager(/* args */);
    ~GameManager();
    void init();
    void event();
    void iterate();
};


#endif // GAMEMANAGER_HPP