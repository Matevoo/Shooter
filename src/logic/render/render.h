#ifndef RENDER_H
#define RENDER_H

void prepareScene(void);

void presentScene(void);

SDL_Texture *loadTexture(char *filename);

void renderTexture(SDL_Texture *texture, int x, int y);

void renderRect(
        SDL_Texture *texture, const SDL_Rect *src,
        int x, int y
);

#endif
