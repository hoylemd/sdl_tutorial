#include "main.h"

SDL_PixelFormat* g_default_sdl_pixelformat = NULL;

SDL_Surface* load_bmp(string path, SDL_PixelFormat* format) {
  SDL_Surface* optimized_image = NULL;
  SDL_Surface* image = SDL_LoadBMP(path.c_str());

  if (image == NULL) {
    cerr << "load image failure: path: " << path << "\n";
    cerr << "  error: " << SDL_GetError() << "\n";
    return NULL;
  }
  optimized_image = SDL_ConvertSurface(image, format, 0);
  if (optimized_image == NULL) {
    cerr << "image optimization failure: path:" << path << "\n";
    cerr << "  error: " << SDL_GetError() << "\n";
  }

  SDL_FreeSurface(image);

  return optimized_image;
}

SDL_Surface* load_bmp(string path) {
  return load_bmp(path, g_default_sdl_pixelformat);
}


