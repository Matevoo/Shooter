#ifndef ENTITIES_H
#define ENTITIES_H

typedef struct {
    float x;
    float y;
    float dx;
    float dy;
} Pos;

struct Entity {
    Pos pos;
    int w;
    int h;
    int health;
    int bulletReload;
    int side;
    FireType fireType;
    SDL_Texture *texture;
    Entity *next;
};

struct Explosion {
    Pos pos;
    int r, g, b, a;
    Explosion *next;
};

struct Debris {
    Pos pos;
    int life;
    SDL_Rect rect;
    SDL_Texture *texture;
    Debris *next;
};

typedef struct {
    int x;
    int y;
    int speed;
} Star;

#endif
