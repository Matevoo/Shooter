#ifndef UTIL_H
#define UTIL_H

void initRandomness(void);
long randBd(long min, long max);
long randVl(long val);
long randS(long val);

int didCollide(
        const Entity *e, const Entity *e2
);

void calcSlope(
        int x1, int y1, int x2, int y2, float *dx, float *dy
);

void centerBulletTexture(
        Entity *bullet, const Entity *entity
);

void setBulletFireType(
        Entity *enemy, const Entity *player
);

#endif
