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
    } else {
      g_screen_surface = SDL_GetWindowSurface(g_window);
    }
  }

  return result;
}

bool load_assets() {
  bool result = true;

  char path[] = "assets/hi.bmp";

  g_hello_world = SDL_LoadBMP(path);
  if (g_hello_world == NULL) {
    printf("BMP load failure: path: %s\n  error: %s", path, SDL_GetError());
    result = false;
  }

  return result;
}

void close() {
  SDL_FreeSurface(g_hello_world);
  g_hello_world = NULL;

  SDL_DestroyWindow(g_window);
  g_window = NULL;

  SDL_Quit();
}

void main_loop() {
  bool quit = false;
  SDL_Event event;

  float frame_duration = 1.0 / 60.0;

  while (!quit) {
    // handle events
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }
    SDL_BlitSurface(g_hello_world, NULL, g_screen_surface, NULL);
    SDL_UpdateWindowSurface(g_window);

    // Wait for time
    SDL_Delay(frame_duration);
  }
}

int main(int argc, char* args[]) {
  if (!init()) {
    printf("Startup failed. Exiting.\n");
  } else {
    if (!load_assets()) {
      printf("Asset loading failed. Exiting\n");
    } else {
      main_loop();
    }
  }

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}
