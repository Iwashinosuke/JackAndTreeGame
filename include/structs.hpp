#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <SDL3/SDL.h>

typedef long long int           entityId;

typedef struct App              app_t;
typedef struct Mouse            mouse_t;
typedef struct Keyboard         keyboard_t;
typedef struct EntityManager    entity_manager_t;
typedef struct Entity           entity_t;

struct App
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    mouse_t *mouse;
    keyboard_t *keyboard;
};

struct  Mouse
{
    /* data */
};

struct Keyboard
{
    /* data */
};

/* loop内で更新されるオブジェクトはすべてこの構造体を継承すること */
struct EntityManager
{
    public:
        EntityManager();
        ~EntityManager();
        void init();
        void event();
        void iterate();
        void Add(entity_t *entity);
    private:
        

        void Add(entity_t *entity);
        void remove_entity(entityId id);
        entity_t *get_entity(entityId id);
        void update();
        void draw();
        entity_manager_t *entity_manager;
};

struct Entity
{
    public:
        Entity()
        {
            _id = 0;
            _active = true;
        }
    private:
        entityId _id;
        bool _active;
};

#endif // STRUCTS_HPP