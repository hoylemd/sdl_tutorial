#include "main.h"

SDL_Surface* load_image(string path, SDL_PixelFormat* format) {
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

game_data* init() {
  game_data * game = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cerr << "SDL initialization failure: " << SDL_GetError() << "\n";
    return NULL;
  }

  game = new game_data;
  game->window = NULL;
  game->screen = NULL;

  return game;
}

bool load_assets(game_data* game) {
  bool result = true;

  int size = sizeof(SDL_Surface*);
  SDL_PixelFormat* format = game->screen->format;

  // load key images
  SDL_Surface ** key_images = (SDL_Surface**) malloc(size * KEY_PRESS_COUNT);

  if(!(key_images[KEY_PRESS_NONE] = load_image("assets/none.bmp", format))) {
    result = false;
  }
  if(!(key_images[KEY_PRESS_UP] = load_image("assets/up.bmp", format))) {
    result = false;
  }
  if(!(key_images[KEY_PRESS_DOWN] = load_image("assets/down.bmp", format))) {
    result = false;
  }
  if(!(key_images[KEY_PRESS_LEFT] = load_image("assets/left.bmp", format))) {
    result = false;
  }
  if(!(key_images[KEY_PRESS_RIGHT] = load_image("assets/right.bmp", format))) {
    result = false;
  }
  game->press_images = key_images;

  // load stretch image
  if(!(game->stretch_image = load_image("assets/stretch.bmp", format))) {
    result = false;
  }

  return result;
}

bool prime_canvass(game_data* game) {

  SDL_Surface* screen = NULL;
  SDL_Window* window = SDL_CreateWindow("SDL Tutorial",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SCREEN_WIDTH,
                                        SCREEN_HEIGHT,
                                        SDL_WINDOW_SHOWN);
  if (window == NULL) {
    cerr << "Window creation failure: " << SDL_GetError() << "\n";
    return false;
  }

  screen = SDL_GetWindowSurface(window);
  game->window = window;
  game->screen = screen;

  return true;
}

game_data* close(game_data* game) {
  int i = 0;

  for (i = 0; i < KEY_PRESS_COUNT; i += 1) {
    SDL_FreeSurface(game->press_images[i]);
    game->press_images[i] = NULL;
  }
  free(game->press_images);
  game->press_images = NULL;

  SDL_FreeSurface(game->stretch_image);
  game->stretch_image = NULL;

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
  SDL_Surface* current_image = game->stretch_image;

  float frame_duration = 1.0 / 60.0;

  while (!quit) {
    // handle events
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = true;
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_UP:
            current_image = game->press_images[KEY_PRESS_UP];
            break;
          case SDLK_DOWN:
            current_image = game->press_images[KEY_PRESS_DOWN];
            break;
          case SDLK_LEFT:
            current_image = game->press_images[KEY_PRESS_LEFT];
            break;
          case SDLK_RIGHT:
            current_image = game->press_images[KEY_PRESS_RIGHT];
            break;
          case SDLK_s:
            current_image = game->stretch_image;
            break;
          default:
            current_image = game->press_images[KEY_PRESS_NONE];
        }
      }
    }
    SDL_BlitSurface(current_image, NULL, game->screen, NULL);
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
    if (!prime_canvass(game)) {
      cerr << "Priming canvass failed. Exiting\n";
    } else {
      if (!load_assets(game)) {
        cerr << "Asset loading failed. Exiting\n";
      } else {
        main_loop(game);
      }
    }
  }

  // Quit SDL subsystems
  game = close(game);
  return 0;
}
