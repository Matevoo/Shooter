#include "../../common/common.h"
#include "util.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/* RANDOMNESS */

void initRandomness(void) {
    srand(time(NULL));
}

long randBd(const long min,
    const long max) {
    return min + (rand() % (max - min));
}

long randVl(const long val) {
    return rand() % val;
}

long randS(const long val) {
    return rand() % val - rand() % val;
}

/* COLLISION */

int didCollide(
        const Entity *const e, const Entity *const e2
) {
    return MAX(e->pos.x, e2->pos.x) < MIN(e->pos.x + e->w, e2->pos.x + e2->w)
        && MAX(e->pos.y, e2->pos.y) < MIN(e->pos.y + e->h, e2->pos.y + e2->h);
}

/* TRAJECTORY */

void calcSlope(
        const int x1, const int y1,
        const int x2, const int y2,
        float *const dx, float *const dy
) {
    const int steps = MAX(abs(x1 - x2), abs(y1 - y2));

    if (steps == 0) {
        *dx = *dy = 0;
        return;
    }

    *dx = x1 - x2, *dx /= steps;
    *dy = y1 - y2, *dy /= steps;
}

/* TEXTURE */

void centerBulletTexture(
        Entity *const bullet, const Entity *const entity
) {
    SDL_QueryTexture(
            bullet->texture, NULL,
            NULL, &bullet->w, &bullet->h
    );
    bullet->pos.x += entity->w / 2 - bullet->w / 2;
    bullet->pos.y += entity->h / 2 - bullet->h / 2;
}

/* FIRING */

void setBulletFireType(
        Entity *const enemy, const Entity *const player
) {
    if (enemy->pos.x < player->pos.x) enemy->fireType = NONE;
    else {
        if (enemy->pos.y >= player->pos.y - player->h
            && enemy->pos.y <= player->pos.y + player->h
            && enemy->pos.x > player->pos.x) {
            enemy->fireType = STRAIGHT;
        } else if (enemy->pos.x > player->pos.x) {
            enemy->fireType = MULTI_DIRECTIONAL;
        }
    }
}

