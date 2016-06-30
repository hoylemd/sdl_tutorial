#include "main.h"

bool init() {
  // reinitialize globals
  g_window = NULL;
  g_screen_surface = NULL;

  bool result = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL initialization failure: %s\n", SDL_GetError());
    result = false;
  } else {
    g_window = SDL_CreateWindow("SDL Tutorial",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if (g_window == NULL) {
      printf("Window creation failure: %s\n", SDL_GetError());
      result = false;
    }
  }

  return result;
}

bool load_media() {
  return true;
}

void close() {
  return;
}

int main(int argc, char* args[]) {
  if (init()) {
    // Get window surface
    g_screen_surface = SDL_GetWindowSurface(g_window);

    // Fill the surface white
    SDL_FillRect(g_screen_surface,
                 NULL,
                 SDL_MapRGB(g_screen_surface->format, 0xFF, 0xFF, 0xFF));

    // Update the surface
    SDL_UpdateWindowSurface(g_window);

    // Wait for time
    SDL_Delay(666);

    // Destroy window
    SDL_DestroyWindow(g_window);
  }

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}
