#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include "../include/main.hpp"

GameManager game_manager;
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;


/* アプリ初期化 */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata(game_manager.getTitle().c_str(), 
                        game_manager.getVersion().c_str(), 
                        game_manager.getTitle().c_str());

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(game_manager.getTitle().c_str(), game_manager.getWindowWidth(), game_manager.getWindowHeight(), 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE; // プログラム続行
}

/* プレイヤからの入力を監視 */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    // switch (event->type) {
        
        
    // }
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        switch(event->key.scancode)
        {
            case SDL_SCANCODE_W:
                break;
            case SDL_SCANCODE_A:
                break;
            // case SDL_SCANCODE_S:
            //     break;
            case SDL_SCANCODE_D:
                break;
            case SDL_SCANCODE_SPACE:
                break;
        }
    }
    if (event->type == SDL_EVENT_KEY_UP)
    {
        switch(event->key.scancode)
        {
            case SDL_SCANCODE_W:
                break;
            case SDL_SCANCODE_SPACE:
                break;
        }
    }
    if (event->type == SDL_EVENT_MOUSE_MOTION)
    {
        // mx = event->motion.x;
        // my = event->motion.y;
    }
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* OSに正常終了を示して終了 */
    }
    return SDL_APP_CONTINUE;  /* プログラム続行 */
}

/* アプリのメインループ */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    return SDL_APP_CONTINUE; // プログラム続行
}

/* アプリの終了処理 */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* windowとrendererは自動で終了される */
}