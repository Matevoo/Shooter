#ifndef EFFECT_H
#define EFFECT_H

typedef struct Explosion Explosion;
typedef struct Debris Debris;

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
