#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "common.hpp"

using namespace PlayerParam;

typedef class Player Player;
extern Player player;


class Player
{
    public:
        Player(void)
        {
            _state = PlayerState::INIT;
            _foot_center_x = 0;
            _foot_center_y = 0;
            _sprite_x = 0.0f;
            _sprite_y = 0.0f;
            _dx = 0.0f;
            _dy = 0.0f;
            _charge_level = 0.0f;
            _prev_foot_center_y = _foot_center_y;
            _left_key = false;
            _right_key = false;
            _charge_key = false;
            _jumping = false;
        }

        void SetPosByWindow(Uint16 x, Uint16 y)
        {
            _foot_center_x = x;
            _foot_center_y = y;
        }
        int InitPlayer(void); 
        int StartPlay(bool reset, Uint16 window_foot_center_y);
        int StopPlay(PlayerState state);

        void UpdateInput(SDL_Event *event);
        PlayerState UpdateRender(SDL_Window *window, SDL_Renderer *renderer);
        Uint16 GetFootCenterX(void){ return _foot_center_x; }
        Uint16 GetFootCenterY(void){ return _foot_center_y; }
        float GetChargeLevel(void){ return _charge_level; }
        float GetSpriteX(void){ return _sprite_x; }
        float GetSpriteY(void){ return _sprite_y; }
        PlayerState GetState(void){ return _state; }

    private:        
        /* 状態 */
        PlayerState _state;

        /* プレイヤの座標は足元の中心を基準とする */
        Uint16 _foot_center_x; 
        Uint16 _foot_center_y;
        Uint16 _prev_foot_center_y;

        /* グラフィック・基本物理 */
        Uint16 _sprite_x;
        Uint16 _sprite_y;
        float _dx;
        float _dy;
        float _charge_level;
        const float _charge_max = 1.0f;
        float _force_y = 0.0f;
        bool _jumping;       

        /* ステージのための変数 */
        Uint64 _stage_foot_center_y; // ステージ上での足元のy座標
        Uint8 _left_edge = 0;
        Uint16 _right_edge = (Uint16)600;

        /* キー */
        bool _left_key;
        bool _right_key;
        bool _charge_key;
};

#endif // PLAYER_HPP
