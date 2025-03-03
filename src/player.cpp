#include "../include/player.hpp"

int Player::InitPlayer(void)
{
    _state = PlayerState::INIT;
    _foot_center_x = GameManagerParam::WINDOW_WIDTH / 2;

    return 0;
}

int Player::StartPlay(bool reset, Uint16 window_foot_center_y)
{
    if(reset)
    {
        _foot_center_x = GameManagerParam::WINDOW_WIDTH / 2;
        _foot_center_y = window_foot_center_y;
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
    _state = PlayerState::PLAY;

    return 0;
}

int Player::StopPlay(PlayerParam::PlayerState state)
{
    _state = state;

    return 0;
}

void Player::UpdateInput(SDL_Event *event)
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
                case SDL_SCANCODE_D:
                    _right_key = true;
                    _dx = 2;
                    break;
                case SDL_SCANCODE_SPACE:
                    _charge_key = true;
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
                    if(_charge_key && !_jumping)
                    {
                        _force_y = -MAX_JUMP_POWER*_charge_level;
                    }
                    _charge_key = false;
                    _jumping =true;
                    _charge_level = 0.0f;
                    break;
            }
        }
}

PlayerState Player::UpdateRender(SDL_Window *window, SDL_Renderer *renderer)
{    
    if(_state == PlayerState::PLAY)
    {
        /* チャージアップデート */
        if(_charge_key && !_jumping)
        {
            if(_charge_level < _charge_max)
            {
                _charge_level += CHARGE_ADDR;
                if(_charge_level > _charge_max) _charge_level = _charge_max;
            } 
        }

        /* y軸アップデート */
        _foot_center_y += _force_y;
        if(_foot_center_y < GameManagerParam::WINDOW_HEIGHT / 2 || _sprite_x > GameManagerParam::WINDOW_WIDTH /3 *2) //床に着いたかの判定
        {
            if(_force_y < 0)
            {
                _force_y += JUMP_POWER_LOSS;
            }
            else
            {
                if(_force_y < MAX_FALL_POWER)_force_y += FALL_POWER_ADDR;
                else _force_y = MAX_FALL_POWER;
            }
        }
        else
        {
            _foot_center_y = GameManagerParam::WINDOW_HEIGHT / 2;
            _force_y = 0.0f;
            _jumping = false;
        }

        /* ゲームクリア判定 */
        //省略

        /* ゲームオーバー判定 */
        if(_foot_center_y > GameManagerParam::WINDOW_HEIGHT / 3 * 2)
        {
            _foot_center_y = GameManagerParam::WINDOW_HEIGHT / 3 * 2;
            _force_y = 0.0f;
            _jumping = false;
            _state = PlayerState::GAMEOVER;
            goto LABEL_RENDER;
        }        

        /* x軸アップデート */
        if(_jumping) _foot_center_x += _dx;
        if(_foot_center_x > _right_edge)
        {
            _foot_center_x = _left_edge;
        }
        else if(_foot_center_x <= _left_edge)
        {
            _foot_center_x = _right_edge;
        }
    }
    

    /* 描画 */
    LABEL_RENDER:
    SDL_FRect rect;
    float rect_size = 30;
    _sprite_x = _foot_center_x - rect_size/2;
    _sprite_y = _foot_center_y - rect_size;
    rect.x = _sprite_x;
    rect.y = _sprite_y;
    rect.w = rect.h = 30;
    SDL_SetRenderScale(renderer, 1.0f, 1.0f);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, (Uint8)(SDL_ALPHA_OPAQUE*_charge_level)); 
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* red, full alpha */
    SDL_RenderRect(renderer, &rect); 

    return _state;
}
