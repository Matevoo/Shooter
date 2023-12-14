#include "../../common/common.h"

#include "render.h"

extern App app;

void prepareScene(void) {
    SDL_SetRenderDrawColor(app.renderer, 32, 32, 40, 245);
    SDL_RenderClear(app.renderer);
}

void presentScene(void) { SDL_RenderPresent(app.renderer); }

SDL_Texture *loadTexture(char *filename) {
    SDL_LogMessage(
            SDL_LOG_CATEGORY_APPLICATION,
            SDL_LOG_PRIORITY_INFO, "Loading %s", filename
    );
    return IMG_LoadTexture(app.renderer, filename);
}

void renderTexture(SDL_Texture *texture, int x, int y) {
    SDL_Rect dest;
    dest.x = x, dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void renderRect(
        SDL_Texture *texture, const SDL_Rect *src,
        const int x, const int y
) {
    SDL_Rect dest;
    dest.x = x, dest.y = y;
    dest.w = src->w, dest.h = src->h;
    SDL_RenderCopy(app.renderer, texture, src, &dest);
}