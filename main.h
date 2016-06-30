#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool load_assets();
void close();

int main(int argc, char* args[]);

// GLOBAL VARIABLES I AM LITERAL HITLER AND STALIN
SDL_Window* g_window = NULL;

//The surface contained by the window
SDL_Surface* g_screen_surface = NULL;

//The image we will load and show on the screen
SDL_Surface* g_hello_world = NULL;
