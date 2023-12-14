#include "../../common/common.h"
#include "effects.h"

extern Core core;

/* INIT */

void initStarfield(void) {
    for (int i = 0; i < MAX_STARS; i++) {
        core.stars[i].x = randVl(SCREEN_WIDTH),
        core.stars[i].y = randVl(SCREEN_HEIGHT),
        core.stars[i].speed = randBd(2, 5);
    }
}

void initBgDest(void) {
    core.bgDest.x = 0, core.bgDest.y = 0,
    core.bgDest.w = SCREEN_WIDTH, core.bgDest.h = SCREEN_HEIGHT;
}

void initEffects(void) {
    initStarfield();
    initBgDest();
}

/* CREATION */

void addExplosions(const int x, const int y, const int num) {
    for (int i = 0; i < num; i++) {
        Explosion *explosion = calloc(1, sizeof(Explosion));
        core.explosionTail->next = explosion, core.explosionTail = explosion;
        explosion->pos.x = x + randS(32), explosion->pos.y = y + randS(32);
        explosion->pos.dx = randS(10), explosion->pos.dy = randS(10);
        explosion->pos.dx /= 10, explosion->pos.dy /= 10;
        switch (randVl(4)) {
            case 0:
                explosion->r = 255;
                break;
            case 1:
                explosion->r = 255;
                explosion->g = 128;
                break;
            case 2:
                explosion->r = 255;
                explosion->g = 255;
                break;
            default:
                explosion->r = 255;
                explosion->g = 255;
                explosion->b = 255;
                break;
        }
        explosion->a = randVl(FPS) * 3;
    }
}

void addDebris(const Entity *fighter) {
    int w, h;
    w = fighter->w / 2, h = fighter->h / 2;
    for (int y = 0; y <= h; y += h) {
        for (int x = 0; x <= w; x += w) {
            Debris *debris = calloc(1, sizeof(Debris));
            core.debrisTail->next = debris, core.debrisTail = debris;
            debris->pos.x = fighter->pos.x + fighter->w / 2,
            debris->pos.y = fighter->pos.y + fighter->h / 2;
            debris->pos.dx = randS(5), debris->pos.dy = randBd(
                    -10, -5
            );
            debris->life = FPS * 2, debris->texture = fighter->texture;
            debris->rect.x = x, debris->rect.y = y,
            debris->rect.w = w, debris->rect.h = h;
        }
    }
}

