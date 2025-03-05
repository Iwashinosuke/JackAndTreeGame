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

Uint64 score=0;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

// StageAuto インスタンスを生成（setupStage() により初期化）
StageAuto stageAuto = setupStage();

// デバッグ用変数
Uint64 conflict_check_cnt = 0;
Uint64 valid_conflict_check_cnt = 0;

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
            score = 0;
            stageAuto.Reset();
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
        gameUi.InformScore(score);
        gameUi.UpdateRender(window,renderer);
        ps  = player.UpdateRender(window,renderer);
    }

    if(gs == GameManagerParam::GameState::PLAY)
    {
        if(ps == PlayerParam::PlayerState::GAMEOVER)
        {
            game_manager.CallGameOver();
        }    
        else score++;
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
    // SDL_SetRenderScale(renderer, 1.0f, 1.0f);
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); 
    // SDL_RenderDebugTextFormat(renderer, 10, 10, "FPS: %" SDL_PRIu64 , CalcFps());
    // SDL_RenderDebugTextFormat(renderer, 10, 20, "centerX: %" SDL_PRIs32 , player.GetFootCenterX());
    // SDL_RenderDebugTextFormat(renderer, 10, 30, "centerY: %" SDL_PRIs32 , player.GetFootCenterY());
    // SDL_RenderDebugTextFormat(renderer, 10, 40, "charge level: %f" , player.GetChargeLevel());
    // SDL_RenderDebugTextFormat(renderer, 10, 50, "GameState: %d" , game_manager.GetState());
    // SDL_RenderDebugTextFormat(renderer, 10, 60, "PlayerState: %d" , player.GetState());
    // SDL_FRect player_sprite_rect = player.GetPlayerSpriteRect();
    // SDL_RenderDebugTextFormat(renderer, 10, 70, "PlayerSpriteRect: x=%f, y=%f, w=%f, h=%f" , player_sprite_rect.x, player_sprite_rect.y, player_sprite_rect.w, player_sprite_rect.h);
    // SDL_RenderDebugTextFormat(renderer, 10, 80, "conflict_check_cnt: %" SDL_PRIu64 , conflict_check_cnt);
    // SDL_RenderDebugTextFormat(renderer, 10, 90, "valid_conflict_check_cnt: %" SDL_PRIu64 , valid_conflict_check_cnt);

    /* 描画 */
    SDL_RenderPresent(renderer);  

    return SDL_APP_CONTINUE; // プログラム続行
}

/* アプリの終了処理 */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* windowとrendererは自動で終了される */
}