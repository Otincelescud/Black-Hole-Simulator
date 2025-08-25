#ifndef Graphics_h
#define Graphics_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "vectorN.h"

// load image func
SDL_Surface* loadImage(const char* filePath);

// unload image func
void unloadImage(SDL_Surface* image);

// get pixel color from image at (x, y)
Uint32 getPixel(SDL_Surface* surface, const VectorN<int, 2>& pos, bool isTiled);

// camera class

// raytracer

#endif // Graphics_h