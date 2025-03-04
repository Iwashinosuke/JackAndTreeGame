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

    /*プレイヤの初期化*/
    game_manager.InitGameManager();
    player.InitPlayer();
    player.StartPlay(true, GameManagerParam::WINDOW_HEIGHT / 2);

    return SDL_APP_CONTINUE; // プログラム続行
}

/* プレイヤからの入力を監視 そのほかコールバックを受付け */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) { 
        return SDL_APP_SUCCESS;  /* OSに正常終了を報告 */
    }

    GameManagerParam::GameState prevgs = game_manager.GetState();
    GameManagerParam::GameState gs = game_manager.UpdateInput(event);
    if(gs == GameManagerParam::GameState::EXIT)
    {
        return SDL_APP_SUCCESS;  /* OSに正常終了を報告 */
    }
    if(gs == GameManagerParam::GameState::PAUSE)
    {
        player.StopPlay(PlayerParam::PlayerState::PAUSE);
        return SDL_APP_CONTINUE;  /* プログラム続行 */
    }
    if(gs == GameManagerParam::GameState::PLAY)
    {
        if(prevgs == GameManagerParam::GameState::GAMEOVER)
        {
            player.StartPlay(true, GameManagerParam::WINDOW_HEIGHT / 2);
        }
        else
        {
            player.StartPlay(false, 0);
        }
        player.UpdateInput(event);
    }
    
    return SDL_APP_CONTINUE;  /* プログラム続行 */
}

/* アプリのメインループ */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    /* 白背景の描画 */
    SDL_SetRenderDrawColor(renderer, 225, 225, 225, SDL_ALPHA_OPAQUE);  /* white, full alpha */

    if(player.GetState() == PlayerParam::PlayerState::GAMEOVER)
    {
        SDL_SetRenderDrawColor(renderer, 225, 0, 0, SDL_ALPHA_OPAQUE);
    }

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


    PlayerParam::PlayerState    ps  = player.UpdateRender(window,renderer);

    if(ps == PlayerParam::PlayerState::GAMEOVER)
    {
        game_manager.CallGameOver();
    }

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
    SDL_RenderDebugTextFormat(renderer, 10, 50, "GameState: %d" , game_manager.GetState());
    
    /* 描画 */
    SDL_RenderPresent(renderer);  

    return SDL_APP_CONTINUE; // プログラム続行
}

/* アプリの終了処理 */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* windowとrendererは自動で終了される */
}