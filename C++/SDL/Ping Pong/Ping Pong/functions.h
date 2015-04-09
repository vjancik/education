#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>
#include <sstream>
bool init();
SDL_Surface *load_image( std::string filename );
bool load_files();
bool initrender();
void cycle();
void clean_up();
#endif