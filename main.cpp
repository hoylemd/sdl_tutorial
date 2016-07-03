#include "main.h"

game_data* init() {
  game_data * game = NULL;

  // reinitialize globals
  g_window = NULL;
  g_screen_surface = NULL;

  bool result = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cerr << "SDL initialization failure: " << SDL_GetError() << "\n";
    result = false;
  } else {
    g_window = SDL_CreateWindow("SDL Tutorial",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if (g_window == NULL) {
      cerr << "Window creation failure: " << SDL_GetError() << "\n";
    } else {
      g_screen_surface = SDL_GetWindowSurface(g_window);
      game = new game_data;
      game->window = g_window;
    }
  }

  return game;
}

bool load_assets() {
  bool result = true;

  char path[] = "assets/hi.bmp";

  g_hello_world = SDL_LoadBMP(path);
  if (g_hello_world == NULL) {
    cerr << "BMP load failure: path: " << path << "\n";
    cerr << "  error: " << SDL_GetError();
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
  game_data * game = NULL;

  game = init();
  if (!game) {
    cerr << "Startup failed. Exiting.\n";
  } else {
    if (!load_assets()) {
      cerr << "Asset loading failed. Exiting\n";
    } else {
      main_loop();
    }
  }

  // Quit SDL subsystems
  SDL_Quit();

  return 0;
}
