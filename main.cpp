#include "main.h"

game_data* init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cerr << "SDL initialization failure: " << SDL_GetError() << "\n";
    return NULL;
  }

  SDL_Window* window = SDL_CreateWindow("SDL Tutorial",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SCREEN_WIDTH,
                                        SCREEN_HEIGHT,
                                        SDL_WINDOW_SHOWN);
  if (window == NULL) {
    cerr << "Window creation failure: " << SDL_GetError() << "\n";
    return NULL;
  }

  int pngFlags = IMG_INIT_PNG;
  if (!(IMG_Init(pngFlags) & pngFlags)) {
    cerr << "SDL image initialization failure: " <<IMG_GetError() << "\n";

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
    return NULL;
  }

  game_data* game = new game_data;
  game->window = window;
  game->screen = SDL_GetWindowSurface(window);
  g_default_sdl_pixelformat = game->screen->format;

  game->press_images = NULL;
  game->stretch_image = NULL;

  return game;
}

bool load_assets(game_data* game) {
  bool result = true;

  int size = sizeof(SDL_Surface*);
  SDL_PixelFormat* format = game->screen->format;

  // load key images
  SDL_Surface ** key_images = (SDL_Surface**) malloc(size * KEY_PRESS_COUNT);

  if(!(key_images[KEY_PRESS_NONE] = load_bmp("assets/none.bmp"))) {
    result = false;
  }
  if(!(key_images[KEY_PRESS_UP] = load_bmp("assets/up.bmp"))) {
    result = false;
  }
  if(!(key_images[KEY_PRESS_DOWN] = load_bmp("assets/down.bmp"))) {
    result = false;
  }
  if(!(key_images[KEY_PRESS_LEFT] = load_bmp("assets/left.bmp"))) {
    result = false;
  }
  if(!(key_images[KEY_PRESS_RIGHT] = load_bmp("assets/right.bmp"))) {
    result = false;
  }
  game->press_images = key_images;

  // load stretch image
  if(!(game->stretch_image = load_bmp("assets/stretch.bmp"))) {
    result = false;
  }

  // load png image
  if (!(game->png_image = load_png("assets/loaded.png"))) {
    result = false;
  }

  return result;
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

  SDL_FreeSurface(game->png_image);
  game->png_image = NULL;

  SDL_DestroyWindow(game->window);
  game->window = NULL;
  game->screen = NULL;

  IMG_Quit();
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
          case SDLK_p:
            current_image = game->png_image;
            break;
          default:
            current_image = game->press_images[KEY_PRESS_NONE];
        }
      }
    }
    SDL_Rect stretch_rectangle;
    stretch_rectangle.x = 0;
    stretch_rectangle.y = 0;
    stretch_rectangle.w = SCREEN_WIDTH;
    stretch_rectangle.h = SCREEN_HEIGHT;

    SDL_BlitScaled(current_image, NULL, game->screen, &stretch_rectangle);

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
