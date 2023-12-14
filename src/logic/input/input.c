#include "../../common/common.h"
#include "input.h"

extern App app;

static void doKey(const SDL_KeyboardEvent *event, bool opt);

void doInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
            case SDL_KEYDOWN:
                doKey(&event.key, true);
                break;
            case SDL_KEYUP:
                doKey(&event.key, false);
                break;
            default: break;
        }
    }
}

static void doKey(const SDL_KeyboardEvent *event, const bool opt) {
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS) {
        app.keyboard[event->keysym.scancode] = opt == false ? 0 : 1;
    }
}
