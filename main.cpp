#include "main.h"

SDL_Surface* load_image(const char* path) {
  SDL_Surface* image = SDL_LoadBMP(path);

  if (image == NULL) {
    cerr << "load image failure: path: " << path << "\n";
    cerr << "  error: " << SDL_GetError() << "\n";
    image = NULL;
  }

  return image;
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
  game->hello_image = NULL;

  return game;
}

bool load_assets(game_data* game) {
  bool result = true;
  char path[] = "assets/hi.bmp";

  if (!(game->hello_image = load_image(path))) {
    result = false;
  }

  // load key images
  int size = sizeof(SDL_Surface*);
  game->press_images = (SDL_Surface**) malloc(size * KEY_PRESS_COUNT);
  SDL_Surface ** press_images = game->press_images;

  if(!(press_images[KEY_PRESS_NONE] = load_image("assets/none.bmp"))) {
    result = false;
  }
  if(!(press_images[KEY_PRESS_UP] = load_image("assets/up.bmp"))) {
    result = false;
  }
  if(!(press_images[KEY_PRESS_DOWN] = load_image("assets/down.bmp"))) {
    result = false;
  }
  if(!(press_images[KEY_PRESS_LEFT] = load_image("assets/left.bmp"))) {
    result = false;
  }
  if(!(press_images[KEY_PRESS_RIGHT] = load_image("assets/right.bmp"))) {
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

  SDL_FreeSurface(game->hello_image);
  game->hello_image = NULL;

  for (i = 0; i < KEY_PRESS_COUNT; i += 1) {
    SDL_FreeSurface(game->press_images[i]);
    game->press_images[i] = NULL;
  }
  free(game->press_images);

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
      if (!prime_canvass(game)) {
        cerr << "Priming canvass failed. Exiting\n";
      } else {
        main_loop(game);
      }
    }
  }

  // Quit SDL subsystems
  game = close(game);
  return 0;
}
