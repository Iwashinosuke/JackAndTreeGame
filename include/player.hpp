#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL3/SDL.h>
#include "common.hpp"

using namespace PlayerParam;

typedef class Player Player;
extern Player player;


class Player
{
    public:
        Player(void)
        {
            _foot_center_x = GameManagerParam::WINDOW_WIDTH / 2;
            _foot_center_y = GameManagerParam::WINDOW_HEIGHT / 2;
            _sprite_x = 0.0f;
            _sprite_y = 0.0f;
            _dx = 0.0f;
            _dy = 0.0f;
            _px = 0.0f;
            _py = 0.0f;
            _charge_level = 0.0f;
            _left_key = false;
            _right_key = false;
            _chargejump_key = false;
        }

        void UpdateInput(SDL_Event *event)
        {
            if (event->type == SDL_EVENT_KEY_DOWN)
                {
                    switch(event->key.scancode)
                    {
                        case SDL_SCANCODE_W:
                            break;
                        case SDL_SCANCODE_A:
                            _left_key = true; // これがないと、細かい調整がしづらい。ボタンを離すと一瞬止まってしまう
                            _dx = -2;
                            break;
                        // case SDL_SCANCODE_S:
                        //     break;
                        case SDL_SCANCODE_D:
                            _right_key = true;
                            _dx = 2;
                            break;
                        case SDL_SCANCODE_SPACE:
                            // if(CanJump())
                            // {
                            //     fy = -10;
                            // }
                            break;
                    }
                }
                if (event->type == SDL_EVENT_KEY_UP)
                {
                    switch(event->key.scancode)
                    {
                        case SDL_SCANCODE_A:
                            _left_key = false;
                            if(!_right_key) _dx = 0;
                            else _dx = 2;
                            break;
                        case SDL_SCANCODE_D:
                            _right_key = false;
                            if(!_left_key) _dx = 0;
                            else _dx = -2;
                            break;
                        case SDL_SCANCODE_SPACE:
                            // if(!CanJump())
                            // {
                            //     fy = 5;
                            // }
                            break;
                    }
                }
        }

        bool UpdateRender(SDL_Window *window, SDL_Renderer *renderer)
        {
            // if(_x <= 0 && dx < 0)
            // {
            //     x = 0;
            //     dx = 0;
            // }
            // else if(x >= 600 - 30 && dx > 0)
            // {
            //     x = 600 - 30;
            //     dx = 0;
            // }
            _foot_center_x += _dx;
            SDL_FRect rect;
            float rect_size = 30;
            rect.x = _foot_center_x - rect_size/2;
            rect.y = _foot_center_y - rect_size;
            rect.w = rect.h = 30;
            SDL_SetRenderScale(renderer, 1.0f, 1.0f);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);  /* red, full alpha */
            SDL_RenderRect(renderer, &rect); 
            return true;
        }

        bool CanJump()
        {
            return _can_jump;
        }

        void SetLeftKey(bool key){ _left_key = key; }
        void SetRightKey(bool key){ _right_key = key; }
        void SetChargeJumpKey(bool key){ _chargejump_key = key; }
        Uint16 GetFootCenterX(void){ return _foot_center_x; }
        Uint16 GetFootCenterY(void){ return _foot_center_y; }
        float GetSpriteX(void){ return _sprite_x; }
        float GetSpriteY(void){ return _sprite_y; }
    private:
        /* 座標計算 */
        float _distortion = 1.0f;
        long int frame = 0;
        void _CalcFootCenter(void){
            _foot_center_y = PlayerParam::MAX_HEIGHT * SDL_sin(2*3.14/40);

        }

        /* プレイヤの座標は足元の中心を基準とする */
        Uint16 _foot_center_x; 
        Uint16 _foot_center_y;

        /* グラフィック・物理 */
        Uint16 _sprite_x;
        Uint16 _sprite_y;
        float _dx;
        float _dy;
        float _px;
        float _py;
        float _charge_level;
        const float _charge_max = 100.0f;
        bool _can_jump;

        /* キー */
        bool _left_key;
        bool _right_key;
        bool _chargejump_key;
};

#endif // PLAYER_HPP
