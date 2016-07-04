#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Game data struct, replacing globals
struct game_data {
  SDL_Window* window;
  SDL_Surface* screen;
  SDL_Surface* hello_image;
  SDL_Surface* press_images;
};

enum g_key_press_surfaces {
  KEY_PRESS_NONE,
  KEY_PRESS_UP,
  KEY_PRESS_DOWN,
  KEY_PRESS_LEFT,
  KEY_PRESS_RIGHT,
  KEY_PRESS_COUNT
};

// asset management
SDL_Surface* load_image(string path);

// main game functions
game_data* init();
bool load_assets(game_data* game);
bool prime_canvass(game_data* game);
game_data* close();

int main(int argc, char* args[]);
