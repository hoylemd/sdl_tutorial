#include "main.h"

game_data* init() {
  game_data * game = NULL;

  // reinitialize globals
  SDL_Window* window = NULL;
  g_screen_surface = NULL;

  bool result = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cerr << "SDL initialization failure: " << SDL_GetError() << "\n";
    result = false;
  } else {
    window = SDL_CreateWindow("SDL Tutorial",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) {
      cerr << "Window creation failure: " << SDL_GetError() << "\n";
    } else {
      g_screen_surface = SDL_GetWindowSurface(window);
      game = new game_data;
      game->window = window;
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

game_data* close(game_data* game) {
  SDL_FreeSurface(g_hello_world);
  g_hello_world = NULL;

  SDL_DestroyWindow(game->window);
  game->window = NULL;

  SDL_Quit();

  free(game);
  game = NULL;

  return game;
}

void main_loop(game_data* game) {
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
    SDL_UpdateWindowSurface(game->window);

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
      main_loop(game);
    }
  }

  // Quit SDL subsystems
  game = close(game);
  return 0;
}
