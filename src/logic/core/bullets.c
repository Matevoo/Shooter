#include "../../common/common.h"
#include "core.h"
#include "bullets.h"

extern Core core;
extern Entity *player;

/* INIT */

static void initBullet(Entity *const bullet) {
    core.bulletTail->next = bullet;
    core.bulletTail = bullet;
    bullet->pos.x = player->pos.x + 40, bullet->pos.y = randBd(
            player->pos.y - BOUND, player->pos.y + BOUND
    ), bullet->pos.dx = PLAYER_BULLET_SPEED;
    bullet->health = 1, bullet->texture = bulletTexture, bullet->side = SIDE_PLAYER;
}

static void initEnemyBullet(const Entity *const entity, Entity *const bullet) {
    core.bulletTail->next = bullet;
    core.bulletTail = bullet;
    bullet->pos.x = entity->pos.x, bullet->pos.y = entity->pos.y, bullet->health = 1;
    bullet->texture = enemyBulletTexture, bullet->side = SIDE_ALIEN;
}

/* FIRING */

void fireBullet() {
    Entity *bullet = calloc(1, sizeof(Entity));
    initBullet(bullet);
    centerBulletTexture(bullet, player);
    player->bulletReload = BULLET_RELOAD;
}

void fireEnemyBullet(Entity *entity) {
    if (entity->fireType == NONE) {
        return;
    }
    Entity *bullet = calloc(1, sizeof(Entity));
    initEnemyBullet(entity, bullet);
    centerBulletTexture(bullet, entity);
    if (entity->fireType == MULTI_DIRECTIONAL) {
        calcSlope(
                player->pos.x + (player->w / 2),
                player->pos.y + (player->h / 2),
                entity->pos.x, entity->pos.y,
                &bullet->pos.dx, &bullet->pos.dy
        );
        bullet->pos.dx *= ALIEN_BULLET_SPEED,
        bullet->pos.dy *= ALIEN_BULLET_SPEED;
    } else if (entity->fireType == STRAIGHT) {
        bullet->pos.dx = -ALIEN_BULLET_SPEED;
    }
    entity->bulletReload = randBd(
            FPS * 2, FPS * 2.5
    );
}

void startEnemyAttack() {
    for (Entity *entity = core.fighterHead.next; entity != NULL; entity = entity->next) {
        if (entity != player && player != NULL && --entity->bulletReload <= 0) {
            setBulletFireType(entity, player);
            fireEnemyBullet(entity);
        }
    }
}

