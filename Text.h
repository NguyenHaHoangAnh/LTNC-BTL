#ifndef TEXT_H_
#define TEXT_H_

#include <iostream>
#include <string>
#include <SDL_ttf.h>
#include "character.h"

using namespace std;

struct Text
{
    string text;
    SDL_Color color;
    int text_x, text_y;
    int text_w, text_h;

    void draw (SDL_Renderer *renderer)
    {
        TTF_Font *font =  TTF_OpenFont ("8514oem.ttf", 30); // (font, size)
        SDL_Surface* surface = TTF_RenderText_Solid (font, text.c_str(), color); // (font, text, color)
        SDL_Texture* texture = SDL_CreateTextureFromSurface (renderer, surface);

        SDL_Rect text_txt;
        TTF_SizeText (font, text.c_str(), &text_txt.w, &text_txt.h);
        text_txt.x = text_x;
        text_txt.y = text_y;
        text_txt.w = text_w;
        text_txt.h = text_h;
        SDL_RenderCopy(renderer, texture, NULL, &text_txt);
    }
};

#endif // TEXT_H
