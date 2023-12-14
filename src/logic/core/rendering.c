#include "../../common/common.h"
#include "core.h"

extern App app;
extern Core core;
extern Entity *player;

/* FIGHTERS */

void renderFighters() {
    for (const Entity *entity = core.fighterHead.next; entity != NULL; entity = entity->next) {
        renderTexture(entity->texture, entity->pos.x, entity->pos.y);
    }
}

/* BULLETS */

void renderBullets() {
    for (const Entity *bullet = core.bulletHead.next; bullet != NULL; bullet = bullet->next) {
        renderTexture(bullet->texture, bullet->pos.x, bullet->pos.y);
    }
}

/* DEBRIS */

void renderDebris() {
    for (const Debris *debris = core.debrisHead.next; debris != NULL; debris = debris->next) {
        renderRect(debris->texture, &debris->rect, debris->pos.x, debris->pos.y);
    }
}

/* BACKGROUND */

void renderBackground() {
    SDL_RenderCopy(app.renderer, background, NULL, &core.bgDest);
}

/* STARFIELD */

void renderStarfield() {
    for (int i = 0; i < MAX_STARS; i++) {
        const int c = 32 * core.stars[i].speed;
        SDL_SetRenderDrawColor(
                app.renderer, c, c, c, 255
        );
        SDL_RenderDrawLine(
                app.renderer,
                core.stars[i].x, core.stars[i].y,
                core.stars[i].x + 3, core.stars[i].y
        );
    }
}

/* EXPLOSIONS */

void renderExplosions() {
    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
    SDL_SetTextureBlendMode(explosionTexture, SDL_BLENDMODE_ADD);
    for (const Explosion *explosion = core.explosionHead.next; explosion != NULL; explosion = explosion->next) {
        SDL_SetTextureColorMod(
                explosionTexture, explosion->r, explosion->g, explosion->b
        );
        SDL_SetTextureAlphaMod(
                explosionTexture, explosion->a
        );
        renderTexture(explosionTexture, explosion->pos.x, explosion->pos.y);
    }
    SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

// TODO Finish renderTrails()

void renderTrails() {
    if (player == NULL) {
        return;
    }
    int w, h, x = player->pos.x, y = player->pos.y;
    SDL_QueryTexture(
            trailTexture, NULL,
            NULL, &w, &h
    );
    x -= player->w / 2;
    renderTexture(
            trailTexture, x, y + h
    );
    y += player->h;
    renderTexture(
            trailTexture, x, y - h * 2
    );
}