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
};

//The surface contained by the window
SDL_Surface* g_screen_surface = NULL;

//The image we will load and show on the screen
SDL_Surface* g_hello_world = NULL;

game_data* init();
bool load_assets();
game_data* close();

int main(int argc, char* args[]);
