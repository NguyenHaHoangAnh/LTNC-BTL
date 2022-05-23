#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "SDL_utils.h"

using namespace std;

SDL_Texture *loadTexture (string path, SDL_Renderer *renderer)
{
    SDL_Texture *newTexture = nullptr;
    SDL_Surface *loadedSurface = IMG_Load (path.c_str()); // nap anh
    if (loadedSurface == nullptr)
        cout << "Unable to load image " << path << " SDL Error: "
             << SDL_GetError () << endl;
    else
    {
        newTexture = SDL_CreateTextureFromSurface (renderer, loadedSurface);
        if (newTexture == nullptr)
            cout << "Unable to create texture from" << path << " SDL Error: "
                 << SDL_GetError () << endl;
            SDL_FreeSurface (loadedSurface);
    }
    return newTexture;
}

void logSDLError (ostream &os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal)
    {

        SDL_Quit();
        exit(1);
    }
}

void initSDL (SDL_Window *&window, SDL_Renderer *&renderer)
{
    if (SDL_Init (SDL_INIT_EVERYTHING) != 0)
        logSDLError (cout, "SDL_Init", true); // mo cua so ve

    window = SDL_CreateWindow (WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError (cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED |
                                   SDL_RENDERER_PRESENTVSYNC); // lay but ve

    if (renderer == nullptr) logSDLError (cout, "CreateRenderer", true);

    TTF_Init();
    if (TTF_Init() < 0) SDL_Log ("%s", TTF_GetError());

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) SDL_Log ("%s", Mix_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL (SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (window);
    SDL_Quit(); // giai phong bo nho quan ly cua so va but ve
    TTF_Quit ();
    Mix_CloseAudio();
}

void waitUntilKeyPressed ()
{
    SDL_Event e;
    while (true)
    {
        if (SDL_WaitEvent (&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay (50);
    }
}
