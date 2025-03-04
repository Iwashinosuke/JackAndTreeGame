#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include "../include/main.hpp"

GameManager game_manager;
Player player;
TitleUI titleUi;
GameUI gameUi;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

/* 実際のFPSの計算　デバッグ用 */
Uint64 CalcFps()
{
    static Uint64 prevTime;
    Uint64 current = SDL_GetTicks();
    Uint64 fpsCnt = current - prevTime;
    prevTime = current;
    return 1000 / fpsCnt;
}

/* 大体目標のFPSくらいになるようにフレームレートを制限 */
void CapFrameRate(Uint64 targetFpsNanoSec)
{
    static Uint64 prevTime;
    Uint64 workedNanoSec = (SDL_GetTicks() - prevTime) * 1000000;
    Uint64 wait = targetFpsNanoSec - workedNanoSec;

    if(wait > 0) SDL_DelayPrecise(wait);

    prevTime = SDL_GetTicks();
}

/* アプリ初期化 */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata(game_manager.GetTitle().c_str(), 
                        game_manager.GetVersion().c_str(), 
                        game_manager.GetTitle().c_str());

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(game_manager.GetTitle().c_str(), game_manager.GetWindowWidth(), game_manager.GetWindowHeight(), 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE; // プログラム続行
}

/* プレイヤからの入力を監視 そのほかコールバックを受付け */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    player.UpdateInput(event);
    
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* OSに正常終了を示して終了 */
    }
    return SDL_APP_CONTINUE;  /* プログラム続行 */
}

/* アプリのメインループ */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    /* 白背景の描画 */
    SDL_SetRenderDrawColor(renderer, 225, 225, 225, SDL_ALPHA_OPAQUE);  /* white, full alpha */
    SDL_RenderClear(renderer);  /* start with a blank canvas. */    

    /* ゲーム内オブジェクトの更新 */
    SDL_FRect rect;
    float rect_size = 80;
    rect.x = 0;
    rect.y = GameManagerParam::WINDOW_HEIGHT / 2;
    rect.w = GameManagerParam::WINDOW_WIDTH; 
    rect.h = rect_size;
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* red, full alpha */
    SDL_RenderFillRect(renderer, &rect); 
 
    // TTF_Font *font = TTF_OpenFont("../res/font/8bitOperatorPlusSC-Bold.ttf", 20);
    // SDL_Color color = {55, 255, 255};
    // SDL_Surface *text1 = TTF_RenderText_Solid(font, "Hello, World!", 14 , color);

    SDL_FRect rect2;
    float rect2_size = 80;
    rect2.x = GameManagerParam::WINDOW_WIDTH / 3;
    rect2.y = GameManagerParam::WINDOW_HEIGHT / 2 + 50;
    rect2.w = GameManagerParam::WINDOW_WIDTH / 3; 
    rect2.h = 500;
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
    SDL_SetRenderDrawColor(renderer, 200, 0, 0, SDL_ALPHA_OPAQUE);  /* red, full alpha */
    SDL_RenderFillRect(renderer, &rect2); 

    player.UpdateRender(window,renderer);
    gameUi.UpdateRender(window,renderer);

    /*フレームレート制限*/
    CapFrameRate(GameManagerParam::TARGET_FPS_NANO_SEC);

    /* (デバッグ)FPS表示 */
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); 
    SDL_RenderDebugTextFormat(renderer, 10, 10, "FPS: %" SDL_PRIu64 , CalcFps());
    SDL_RenderDebugTextFormat(renderer, 10, 20, "centerX: %" SDL_PRIs32 , player.GetFootCenterX());
    SDL_RenderDebugTextFormat(renderer, 10, 30, "centerY: %" SDL_PRIs32 , player.GetFootCenterY());
    SDL_RenderDebugTextFormat(renderer, 10, 40, "charge level: %f" , player.GetChargeLevel());
    
    /* 描画 */
    SDL_RenderPresent(renderer);  

    return SDL_APP_CONTINUE; // プログラム続行
}

/* アプリの終了処理 */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* windowとrendererは自動で終了される */
}