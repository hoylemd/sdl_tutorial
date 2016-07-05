#ifndef ASSETS_H
#define ASSETS_H

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

using namespace std;
// asset management
extern SDL_PixelFormat* g_default_sdl_pixelformat;
SDL_Surface* load_bmp(string path);
SDL_Surface* load_bmp(string path, SDL_PixelFormat* format);
SDL_Surface* load_png(string path);
SDL_Surface* load_png(string path, SDL_PixelFormat* format);

#endif // ASSETS_H
