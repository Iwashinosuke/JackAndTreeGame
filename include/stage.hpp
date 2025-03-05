#ifndef STAGE_HPP
#define STAGE_HPP

#include "../include/common.hpp"  // GameManagerParam::WINDOW_WIDTH, WINDOW_HEIGHT などが定義されている前提
#include <SDL3/SDL.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// BlockParams: 障害物ブロックのパラメータ
struct BlockParams {
    float blockWidth;  // 各正方形ブロックの幅
};

// Obstacle: 障害物の情報構造体
// 障害物は横方向に1～3マス、縦方向に1～4マスの正方形ブロックから構成される
struct Obstacle {
    float x;       // 障害物の左端のX座標
    int colCount;  // 横方向の正方形の数 (1～3)
    int rowCount;  // 縦方向の正方形の数 (1～4)
};

// StageAuto クラス：障害物（足場）を管理する
class StageAuto {
public:
    // params   : 障害物ブロックのパラメータ
    // groundY  : 障害物が配置される地面レベルのY座標（障害物の底部がこの位置に揃う）
    // speed    : 障害物の左方向への移動速度（ピクセル/フレーム）
    StageAuto(const BlockParams& params, float groundY, float speed);

    // 障害物の描画
    void render(SDL_Renderer* renderer);

    // 次の障害物（足場）を生成する（障害物毎にランダムな生成間隔で生成）
    void generateNextStage();

    /* 障害物初期化 */
    void Reset()
    {
        _obstacles.clear();
    }

private:
    BlockParams _params;
    float _groundY;   // 地面のY座標
    float _speed;     // 障害物の移動速度

    std::vector<Obstacle> _obstacles;  // 現在存在する障害物のリスト

    // 内部で障害物を生成する関数
    void generateObstacle();

    // 障害物の更新（位置の移動および画面外の障害物の削除）
    void updateObstacles();
};

// setupStage() 関数：StageAuto インスタンスを生成して返す（stage_setup を統合）
inline StageAuto setupStage() {
    BlockParams params;
    params.blockWidth = 30.0f;  // 各正方形ブロックの幅（30px）

    // 地面のY座標を画面中央に設定
    float groundY = GameManagerParam::WINDOW_HEIGHT / 2;
    
    // 障害物の移動速度：例として5ピクセル/フレーム
    float speed = 5.0f;
    
    return StageAuto(params, groundY, speed);
}

#endif // STAGE_HPP

