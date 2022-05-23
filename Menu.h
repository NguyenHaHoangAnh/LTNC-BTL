#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <string>
#include <SDL_ttf.h>
#include "Text.h"

using namespace std;

struct Menu
{
    int pointer_x, pointer_y;

    void background (SDL_Renderer *renderer)
    {
        SDL_Texture *menu_img = loadTexture ("image//background.jpg", renderer);
        SDL_Rect menu;
        SDL_QueryTexture (menu_img, NULL, NULL, &menu.w, &menu.h);
        menu.x = 0;
        menu.y = 0;
        menu.h = SCREEN_HEIGHT;
        menu.w = SCREEN_WIDTH;
        SDL_RenderCopy (renderer, menu_img, NULL, &menu);
    }

    void logo (SDL_Renderer *renderer)
    {
        SDL_Texture *logo_img = loadTexture ("image//logo.png", renderer);
        SDL_Rect logo;
        SDL_QueryTexture (logo_img, NULL, NULL, &logo.w, &logo.h);
        logo.x = 250;
        logo.y = 10;
        logo.h = 300;
        logo.w = 700;
        SDL_RenderCopy (renderer, logo_img, NULL, &logo);
    }
};

#endif // TEXT_H

