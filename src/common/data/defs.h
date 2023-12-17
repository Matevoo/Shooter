#ifndef DEFS_H
#define DEFS_H

typedef enum {
    MULTI_DIRECTIONAL, STRAIGHT, NONE
} FireType;

typedef struct {
    float x;
    float y;
    float dx;
    float dy;
} Pos;

#endif
