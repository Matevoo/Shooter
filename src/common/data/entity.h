#ifndef ENTITIES_H
#define ENTITIES_H

typedef struct Entity Entity;

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

#endif
