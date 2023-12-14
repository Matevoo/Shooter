#include "common/common.h"
#include "logic/init/init.h"
#include "logic/input/input.h"
#include "logic/core/core.h"

App app;
Core core;

static void capFrameRate(long *then, float *remainder);

//TODO Later on create a README file describing all of util's functions and game's logic
//TODO Review defn.h to make gameplay more realistic
//TODO Implement thrust animation for fighters

int main(void) {
    long then;
    float remainder;
    memset(&app, 0, sizeof(App));
    initSDL();
    atexit(cleanup);
    initCore();
    initRandomness();
    then = SDL_GetTicks();
    remainder = 0;
    while (true) {
        prepareScene();
        doInput();
        app.delegate.logic();
        app.delegate.draw();
        presentScene();
        capFrameRate(&then, &remainder);
    }
}

static void capFrameRate(long *then, float *remainder) {
    const long frameTime = SDL_GetTicks() - *then; long wait;
    wait = 16 + *remainder, *remainder -= (int) *remainder;
    wait -= frameTime;
    if (wait < 1) {
        wait = 1;
    }
    SDL_Delay(wait);
    *remainder += 0.667, *then = SDL_GetTicks();
}
