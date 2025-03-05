#include "../include/player.hpp"

int Player::InitPlayer(SDL_Renderer *renderer)
{
    _state = PlayerState::INIT;
    _foot_center_x = GameManagerParam::WINDOW_WIDTH / 2;

    _sprites = new SDL_Texture*[_sprite_cnt];

    if(_sprites == NULL)
    {
        SDL_Log("Failed to allocate memory :%s", SDL_GetError());
        return -1;
    }

    try
    {
        SDL_Surface *surface;
        surface = SDL_LoadBMP("../res/image/idle.bmp");
        _sprites[IDLE] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface); 

        surface = SDL_LoadBMP("../res/image/dash1.bmp");
        _sprites[DASH1] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);

        surface = SDL_LoadBMP("../res/image/dash2.bmp");
        _sprites[DASH2] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);

        surface = SDL_LoadBMP("../res/image/dame1.bmp");
        _sprites[DAME1] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);

        surface = SDL_LoadBMP("../res/image/dame2.bmp");
        _sprites[DAME2] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_DestroySurface(surface);
    }
    catch(const std::exception& e)
    {
        SDL_Log("Failed to load image :%s", SDL_GetError());
        return -1;
    }

    return 0;
}

int Player::StartPlay(bool reset, Uint16 window_foot_center_y)
{
    if(reset)
    {
        _foot_center_x = GameManagerParam::WINDOW_WIDTH / 3;
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

/* 登録されてるスプライト依存 */
Uint8 Player::GetCurrentSpriteNum(void)
{
    static Uint64 prevFps;
    static Uint8 prev_sprite_num;
    Uint64 nowFps = SDL_GetTicks();

    if(_state == PlayerState::GAMEOVER)
    {
        if(prev_sprite_num == IDLE || prev_sprite_num == DASH1)
        {
            prev_sprite_num = DAME1;
            return DAME1;
        }
        else if(prev_sprite_num == DASH2)
        {
            prev_sprite_num = DAME2;
            return DAME2;
        }
    }
    else if(this->_jumping)
    {
        return IDLE;
    }
    if(nowFps - prevFps > 500)
    {
        prevFps = nowFps;
        if(_state == PlayerState::PLAY)
        {
            if(prev_sprite_num != 1)
            {
                prev_sprite_num = 1;
                return DASH1;
            }
            else
            {
                prev_sprite_num = 2;
                return DASH2;
            }
        }
    }
    return prev_sprite_num;
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
                    if(!_jumping && !_charge_key)
                    {
                        _force_y = -MAX_JUMP_POWER;
                        _jumping = true;
                        _charge_key = true;
                    }
                    // _charge_key = true;
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

                    _charge_key = false;
                    _charge_level = 0.0f;

                    // if(_charge_key && !_jumping)
                    // {
                    //     _force_y = -MAX_JUMP_POWER*_charge_level;
                    // }
                    // _charge_key = false;
                    // _jumping =true;
                    // _charge_level = 0.0f;
                    break;
            }
        }
}

PlayerState Player::UpdateRender(SDL_Window *window, SDL_Renderer *renderer)
{    
    SDL_FRect dst_rects[_sprite_cnt];
    if(_state == PlayerState::PLAY)
    {
        /* チャージアップデート */
        // if(_charge_key && !_jumping)
        if(_charge_key && _jumping)
        {
            if(_charge_level < _charge_max)
            {
                _charge_level += CHARGE_ADDR;
                if(_charge_level > _charge_max) _charge_level = _charge_max;
                else _force_y -= TMP_JUMP_POWER_ADDR;
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
        // if(_jumping) _foot_center_x += _dx;

        _foot_center_x += _dx;
        if(_foot_center_x > _right_edge)
        {
            _foot_center_x = _right_edge;
            // _foot_center_x = _left_edge;
        }
        else if(_foot_center_x <= _left_edge)
        {
            _foot_center_x = _left_edge;
            // _foot_center_x = _right_edge;
        }
    }
    else{
        _left_key = false;
        _right_key = false;
        _charge_key = false;
        _charge_level = 0.0f;
        _dx = 0;
    }

    /* 描画 */
    LABEL_RENDER:
    Uint8 sn = GetCurrentSpriteNum();

    SDL_FRect dst_rect;
    SDL_Texture *target_sprite = _sprites[sn];
    Uint16 sprite_w = target_sprite->w / 2;
    Uint16 sprite_h = target_sprite->h / 2;
    dst_rect.x = _foot_center_x - 100;
    dst_rect.y = _foot_center_y - 170;
    dst_rect.w = sprite_w;
    dst_rect.h = sprite_h;
    SDL_RenderTexture(renderer, target_sprite, NULL, &dst_rect);
    SDL_RenderRect(renderer, &dst_rect);

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
    // SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* red, full alpha */
    // SDL_RenderRect(renderer, &rect); 

    return _state;
}
