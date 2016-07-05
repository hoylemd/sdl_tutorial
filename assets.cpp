#include "assets.h"

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

SDL_Surface* load_png(string path, SDL_PixelFormat* format) {
  SDL_Surface* optimized_image = NULL;
  SDL_Surface* image = IMG_Load(path.c_str());

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

SDL_Surface* load_png(string path) {
  return load_png(path, g_default_sdl_pixelformat);
}

SDL_Texture* load_texture(string path, SDL_PixelFormat* format) {
  return NULL;
}

SDL_Texture* load_texture(string path) {
  return NULL;
}

