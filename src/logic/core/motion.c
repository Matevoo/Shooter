#include "../../common/common.h"
#include "bullets.h"
#include "motion.h"
#include "effects.h"

extern App app;
extern Core core;
extern Entity* player;
extern SDL_Texture* trailTexture;

/* ENTITY COLLISION */

static bool entityCollision(Entity* target) {
    for (Entity* fighter = core.fighterHead.next; fighter != NULL; fighter = fighter->next)
        if (fighter->side != target->side && didCollide(
                target, fighter
            )) {
            target->health = 0, fighter->health = 0;
            addExplosions(fighter->pos.x,
                          fighter->pos.y, 32);
            addDebris(fighter);
            return true;
        }
    return false;
}

/* FIGHTERS */

void moveFighters() {
    Entity *fighter, *prev = &core.fighterHead;
    for (fighter = core.fighterHead.next; fighter != NULL; fighter = fighter->next) {
        fighter->pos.x += fighter->pos.dx,
        fighter->pos.y += fighter->pos.dy;

        if (fighter != player && fighter->pos.x <= -fighter->w) {
            fighter->health = 0;
        }

        if (fighter->health == 0) {
            if (fighter == player) player = NULL;
            if (fighter == core.fighterTail) {
                core.fighterTail = prev;
            }

            prev->next = fighter->next;
            free(fighter);
            fighter = prev;
        }

        prev = fighter;
    }
}

/* BULLETS */

void moveBullets() {
    Entity *bullet, *prev = &core.bulletHead;
    for (bullet = core.bulletHead.next; bullet != NULL; bullet = bullet->next) {
        bullet->pos.x += bullet->pos.dx,
        bullet->pos.y += bullet->pos.dy;

        if (entityCollision(bullet) ||
            bullet->pos.x <= -bullet->w || bullet->pos.y <= -bullet->h ||
            bullet->pos.y >= SCREEN_HEIGHT || bullet->pos.x >= SCREEN_WIDTH) {
            if (bullet == core.bulletTail) {
                core.bulletTail = prev;
            }

            prev->next = bullet->next;
            free(bullet);
            bullet = prev;
        }

        prev = bullet;
    }
}

/* PLAYER */

static void clipPlayer() {
    if (player->pos.x >= SCREEN_WIDTH / 2) {
        player->pos.dx -= PLAYER_SPEED;
    }
    if (player->pos.y + player->h >= SCREEN_HEIGHT) {
        player->pos.dy -= PLAYER_SPEED;
    }
    if (player->pos.x <= 0) player->pos.dx += PLAYER_SPEED;
    if (player->pos.y <= 0) player->pos.dy += PLAYER_SPEED;
}

static void playerInput() {
    if (app.keyboard[SDL_SCANCODE_W])
        player->pos.dy = -PLAYER_SPEED;
    if (app.keyboard[SDL_SCANCODE_A])
        player->pos.dx = -PLAYER_SPEED;
    if (app.keyboard[SDL_SCANCODE_S])
        player->pos.dy = PLAYER_SPEED;
    if (app.keyboard[SDL_SCANCODE_D])
        player->pos.dx = PLAYER_SPEED;
    if (app.keyboard[SDL_SCANCODE_SPACE]
        && player->bulletReload <= 0) {
        fireBullet();
    }
    clipPlayer();
}

void movePlayer() {
    if (player != NULL) {
        player->pos.dx = player->pos.dy = 0;
        if (player->bulletReload > 0) {
            player->bulletReload--;
        }
        playerInput();
    }
}

/* EXPLOSIONS */

void moveExplosions() {
    Explosion *explosion, *prev = &core.explosionHead;
    for (explosion = core.explosionHead.next; explosion != NULL; explosion = explosion->next) {
        explosion->pos.x += explosion->pos.dx,
        explosion->pos.y += explosion->pos.dy;

        if (--explosion->a <= 0) {
            if (explosion == core.explosionTail) {
                core.explosionTail = prev;
            }

            prev->next = explosion->next;
            free(explosion);
            explosion = prev;
        }

        prev = explosion;
    }
}

/* DEBRIS */

void moveDebris() {
    Debris *debris, *prev = &core.debrisHead;
    for (debris = core.debrisHead.next; debris != NULL; debris = debris->next) {
        debris->pos.x += debris->pos.dx,
        debris->pos.y += debris->pos.dy, debris->pos.dy += 0.4;

        if (--debris->life <= 0) {
            if (debris == core.debrisTail) {
                core.debrisTail = prev;
            }

            prev->next = debris->next;
            free(debris);
            debris = prev;
        }

        prev = debris;
    }
}

/* STARFIELD */

void moveStarfield() {
    for (int i = 0; i < MAX_STARS; i++) {
        core.stars[i].x -= core.stars[i].speed;

        if (core.stars[i].x < 0) {
            core.stars[i].x = SCREEN_WIDTH + core.stars[i].x;
        }
    }
}

