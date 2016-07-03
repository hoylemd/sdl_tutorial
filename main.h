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
};

game_data* init();
bool load_assets(game_data* game);
game_data* close();

int main(int argc, char* args[]);
