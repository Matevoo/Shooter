#include "../../common/common.h"
#include "../render/render.h"
#include "bullets.h"
#include "effects.h"
#include "motion.h"
#include "rendering.h"
#include "core.h"

void resetCore();
void initPlayer();
static void logic();
static void draw();

extern App app;
extern Core core;

Entity *player;
static int enemySpawnTimer, coreResetTimer;

void cacheTextures(void) {
    playerTexture = loadTexture(
            "../res/player.png"
    ), bulletTexture = loadTexture(
            "../res/bullet.png"
    ), enemyTexture = loadTexture(
            "../res/enemy.png"
    ), enemyBulletTexture = loadTexture(
            "../res/enemy-bullet.png"
    ), background = loadTexture(
            "../res/background.png"
    ), explosionTexture = loadTexture(
            "../res/explosion.png"
    ), trailTexture = loadTexture(
            "../res/trail.png"
    );
}

void initCore() {
    app.delegate.logic = logic;
    app.delegate.draw = draw;
    cacheTextures();
    resetCore();
}

void resetCore() {
    Entity *entity;

    while (core.fighterHead.next) {
        entity = core.fighterHead.next;
        core.fighterHead.next = entity->next;
        free(entity);
    }

    while (core.bulletHead.next) {
        entity = core.bulletHead.next;
        core.bulletHead.next = entity->next;
        free(entity);
    }

    memset(&core, 0, sizeof(Core));
    core.fighterTail = &core.fighterHead;
    core.bulletTail = &core.bulletHead;
    core.explosionTail = &core.explosionHead;
    core.debrisTail = &core.debrisHead;
    initPlayer();
    initEffects();
    enemySpawnTimer = 0, coreResetTimer = FPS * 2;
}

/* INIT */

void initPlayer() {
    player = malloc(sizeof(Entity));
    memset(player, 0, sizeof(Entity));
    core.fighterTail->next = player, core.fighterTail = player;
    player->health = 1, player->pos.x = 100, player->texture = playerTexture;
    SDL_QueryTexture(
            player->texture, NULL, NULL, &player->w, &player->h
    );
    player->pos.y = SCREEN_HEIGHT / 2.0 - player->h;
    player->side = SIDE_PLAYER;
}

static void initEnemy(Entity *const enemy) {
    core.fighterTail->next = enemy, core.fighterTail = enemy;
    enemy->pos.x = SCREEN_WIDTH, enemy->pos.y = randVl(
            SCREEN_HEIGHT - enemy->h
    );
    enemy->pos.dx = randBd(
            -4, 1
    );
    enemy->health = 1, enemy->side = SIDE_ALIEN;
    enemy->bulletReload = FPS * randBd(
            2, 3
    );
}

/* ENEMY SPAWN */

static void spawnEnemies() {
    if (--enemySpawnTimer <= 0) {
        Entity *enemy = malloc(sizeof(Entity));
        memset(enemy, 0, sizeof(Entity));
        enemy->texture = enemyTexture;
        SDL_QueryTexture(
                enemy->texture, NULL, NULL, &enemy->w, &enemy->h
        );
        initEnemy(enemy);
        enemySpawnTimer = randBd(25, 75);
    }
}

/* LOGIC */

static void logic() {
    moveStarfield();
    movePlayer();
    startEnemyAttack();
    moveFighters();
    moveBullets();
    moveExplosions();
    moveDebris();
    spawnEnemies();
    if (player == NULL && --coreResetTimer <= 0) {
        resetCore();
    }
}

/* RENDERING */

static void draw() {
    renderBackground();
    renderStarfield();
    renderTrails();
    renderFighters();
    renderDebris();
    renderExplosions();
    renderBullets();
}
