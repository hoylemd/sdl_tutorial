#include "main.h"

game_data* init() {
  game_data * game = NULL;

  // reinitialize globals
  SDL_Window* window = NULL;
  SDL_Surface* screen = NULL;

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
      screen = SDL_GetWindowSurface(window);
      game = new game_data;
      game->window = window;
      game->screen = screen;
      game->hello_image = NULL;
    }
  }

  return game;
}

bool load_assets(game_data* game) {
  bool result = true;

  char path[] = "assets/hi.bmp";

  game->hello_image = SDL_LoadBMP(path);
  if (game->hello_image == NULL) {
    cerr << "BMP load failure: path: " << path << "\n";
    cerr << "  error: " << SDL_GetError();
    result = false;
  }

  return result;
}

game_data* close(game_data* game) {
  SDL_FreeSurface(game->hello_image);
  game->hello_image = NULL;

  SDL_DestroyWindow(game->window);
  game->window = NULL;
  game->screen = NULL;

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
    SDL_BlitSurface(game->hello_image, NULL, game->screen, NULL);
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
    if (!load_assets(game)) {
      cerr << "Asset loading failed. Exiting\n";
    } else {
      main_loop(game);
    }
  }

  // Quit SDL subsystems
  game = close(game);
  return 0;
}
