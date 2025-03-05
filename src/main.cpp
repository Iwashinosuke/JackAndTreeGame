#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include "../include/main.hpp"

#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_surface.h>

GameManager game_manager;
Player player;
TitleUI titleUi;
GameUI gameUi;
PauseUI pauseUi;
GameOverUI gameOverUi;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

// StageAuto インスタンスを生成（setupStage() により初期化）
StageAuto stageAuto = setupStage();

/* (cx,cy)を中心として単位時間あたりで点滅するrectを描画します この関数で描画されるrectは、点滅間隔が共有されるため使用法に注意 */
inline void RenderBlinkRect(SDL_Renderer *renderer, Uint16 cx, Uint16 cy)
{
    static Uint64 prevTime;
    static bool lighting = true;
    static Uint8 size = 20;
    Uint64 blink_intensity = 500;

    Uint64 current = SDL_GetTicks();
    Uint64 elapsed = current - prevTime;
    if(elapsed > blink_intensity)
    {
        lighting = !lighting;
        prevTime = current;
    }

    SDL_FRect rect;
    rect.x = cx - size / 2;
    rect.y = cy - size / 2;
    rect.w = size;
    rect.h = size;
    if(lighting)
    {
        SDL_SetRenderDrawColor(renderer, 255, 150, 50, SDL_ALPHA_OPAQUE);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 200, 100, 10, SDL_ALPHA_OPAQUE);
    }

    SDL_RenderFillRect(renderer, &rect);
}

/* (cx,cy)を中心として単位時間あたりで輝くdiamondを描画します この関数で描画される対象は、点滅間隔が共有されるため使用法に注意 */
inline void RenderRainbowDiamond(SDL_Renderer *renderer, Uint16 cx, Uint16 cy)
{
    static Uint8 baseCol;
    static Uint16 size = 50;
    static Uint64 rainbow_intensity = 500;
    SDL_FRect rect;
    rect.x = cx - size / 2;
    rect.y = cy - size / 2;
    rect.w = size;
    rect.h = size;
    


    for(Uint16 rx=0; rx < size/2; rx++)
    {
        SDL_SetRenderDrawColor(renderer, baseCol+rx, baseCol+61+rx, baseCol+101+rx, SDL_ALPHA_OPAQUE);
        SDL_RenderLine(renderer, cx+rx, -size/2+cy+rx, -size/2+cx+rx, cy+rx);
    }

    baseCol++;
}


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
    int result = player.InitPlayer(renderer);
    player.StartPlay(true, GameManagerParam::WINDOW_HEIGHT / 2);

    if (result != 0) {
        SDL_Log("Couldn't initialize player: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

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
    SDL_SetRenderDrawColor(renderer, 250, 250, 250, SDL_ALPHA_OPAQUE);  /* white, full alpha */
    SDL_RenderClear(renderer);  /* start with a blank canvas. */    

    GameManagerParam::GameState gs = game_manager.GetState();
    PlayerParam::PlayerState ps = PlayerParam::PlayerState::INIT;
    if(gs == GameManagerParam::GameState::TITLE)
    {
        titleUi.UpdateRender(window,renderer);
    }
    else
    {
        gameUi.InformCurrentState(gs);
        gameUi.InformScore(0);
        gameUi.UpdateRender(window,renderer);
        ps  = player.UpdateRender(window,renderer);
    }

    if(gs == GameManagerParam::GameState::PLAY)
    {
        if(ps == PlayerParam::PlayerState::GAMEOVER)
        {
            game_manager.CallGameOver();
        }    
    }
    else if(gs == GameManagerParam::GameState::PAUSE)
    {
        player.StopPlay(PlayerParam::PlayerState::PAUSE);
        pauseUi.UpdateRender(window,renderer);
    }
    else if(gs == GameManagerParam::GameState::GAMEOVER)
    {
        gameOverUi.UpdateRender(window,renderer);
    }
    else if(gs == GameManagerParam::GameState::EXIT)
    {
        return SDL_APP_SUCCESS;  /* OSに正常終了を報告 */
    }

    // ----- 障害物（足場）の描画と更新 -----
    if (gs == GameManagerParam::GameState::PLAY) {
        stageAuto.render(renderer);
        stageAuto.generateNextStage();
        }

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
    SDL_RenderDebugTextFormat(renderer, 10, 60, "PlayerState: %d" , player.GetState());
    
    /* 描画 */
    SDL_RenderPresent(renderer);  

    return SDL_APP_CONTINUE; // プログラム続行
}

/* アプリの終了処理 */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* windowとrendererは自動で終了される */
}