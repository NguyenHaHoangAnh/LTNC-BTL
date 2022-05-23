#ifndef SDL_UTILS_H_
#define SDL_UTILS_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;

const string WINDOW_TITLE = "Super Smash Flash 2.exe";

void logSDLError (ostream &os, const string &msg, bool fatal = false);

void initSDL (SDL_Window *&window, SDL_Renderer *&renderer); // khoi tao SDL

SDL_Texture *loadTexture (string path, SDL_Renderer *renderer);

void quitSDL (SDL_Window *window, SDL_Renderer *renderer); // giai phong SDL

void waitUntilKeyPressed (); // doi 1 phim de thoat

#endif // SDL_UTILS_H_
