#include "graphics.h"

SDL_Surface* loadImage(const char* filePath) {
    SDL_Surface* image = IMG_Load(filePath); // make it so it loads from assets folder
    if (!image) {
        SDL_Log("Failed to load image %s: %s", filePath, IMG_GetError());
        return nullptr;
    }
    return image;
}

void unloadImage(SDL_Surface* image) {
    if (image) {
        SDL_FreeSurface(image);
    }
    else {
        SDL_Log("Attempted to free a null surface.");
    }
}

// find pixel format

Uint32 getPixel(SDL_Surface* surface, const VectorN<int, 2>& pos, bool isTiled) {
    if (pos[0] < 0 || pos[0] >= surface->w || pos[1] < 0 || pos[1] >= surface->h) {
        //SDL_Log("Position out of bounds: (%d, %d)", pos[0], pos[1]);
        return 0;
    }

    if (surface->format->BytesPerPixel != 4) {
        //SDL_Log("getPixel only supports 32bpp surfaces.");
        return 0;
    }

    Uint8* p = (Uint8*)surface->pixels + pos[1] * surface->pitch + pos[0] * 4;
    return *(Uint32*)p;
}