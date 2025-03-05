#include "../include/player.hpp" // playerを使用
#include "../include/game_manager.hpp" // game_managerを使用

#include "../include/stage.hpp"

// コンストラクタ
StageAuto::StageAuto(const BlockParams& params, float groundY, float speed)
    : _params(params), _groundY(groundY), _speed(speed)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    // 初期状態では障害物リストは空
}

// 障害物の更新（移動および画面外の障害物の削除）
void StageAuto::updateObstacles() {
    // 各障害物を左方向へ移動
    for(auto& obs : _obstacles) {
        obs.x -= _speed;
    }
    // 画面外（完全に左に消えた障害物）を削除
    _obstacles.erase(
        std::remove_if(_obstacles.begin(), _obstacles.end(),
            [this](const Obstacle& obs) {
                return (obs.x + obs.colCount * _params.blockWidth) < 0;
            }),
        _obstacles.end()
    );
}

// 障害物の生成
void StageAuto::generateObstacle() {
    // 横方向の正方形の数: 1～3
    int colCount = (std::rand() % 3) + 1;
    // 縦方向の正方形の数: 1～4
    int rowCount = (std::rand() % 4) + 1;

    // 新しい障害物のX座標は、ウィンドウの右端から0～99pxのランダムなオフセットで出現
    float x = GameManagerParam::WINDOW_WIDTH + (std::rand() % 100);
    
    Obstacle obs = { x, colCount, rowCount };
    _obstacles.push_back(obs);
}

// generateNextStage: 次の障害物（足場）を生成する
void StageAuto::generateNextStage() {
    // 基準間隔を200pxとし、その1.5倍～3倍の範囲でランダムに生成間隔を決定
    int baseInterval = 400;
    int minInterval = static_cast<int>(baseInterval * 1.5);
    int maxInterval = baseInterval * 3;
    int generationInterval = (std::rand() % (maxInterval - minInterval + 1)) + minInterval;
    
    // 障害物リストが空、または最後の障害物のX座標がウィンドウ右端から generationInterval 内なら新規生成
    if (_obstacles.empty() || (_obstacles.back().x < GameManagerParam::WINDOW_WIDTH - generationInterval)) {
        generateObstacle();
    }
}

// 障害物の描画
void StageAuto::render(SDL_Renderer* renderer) {
    updateObstacles();
    
    // 障害物がない、または最後の障害物がウィンドウ右端から200px以内の場合、新たに生成
    if (_obstacles.empty() || (_obstacles.back().x < GameManagerParam::WINDOW_WIDTH - 400)) {
        generateObstacle();
    }
    
    // 各障害物を描画（障害物の底部が _groundY に揃う）
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (const auto& obs : _obstacles) {
        /* 最適化 */
        SDL_FRect rectF = { obs.x, _groundY - obs.rowCount * _params.blockWidth, obs.colCount * _params.blockWidth, obs.rowCount * _params.blockWidth };
        SDL_RenderFillRect(renderer, &rectF);
        /* 衝突判定 */
        if(player.CheckConflictFRect(&rectF))
        {
            game_manager.CallGameOver();
            return;
        }

        // for (int i = 0; i < obs.rowCount; ++i) {
        //     for (int j = 0; j < obs.colCount; ++j) {
        //         SDL_FRect rectF = { obs.x + j * _params.blockWidth, _groundY - (i+1) * _params.blockWidth, _params.blockWidth, _params.blockWidth };
        //         SDL_RenderFillRect(renderer, &rectF);
        //     }
        // }
    }
}
