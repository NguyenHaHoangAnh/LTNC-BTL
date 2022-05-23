#include <iostream>
#include <string>
#include "game.h"

void Main_menu (SDL_Renderer *renderer, Menu &main_menu, Game &game, int &menu_time,
                character &player, character &enemy, Menu &select)
{
    main_menu.background (renderer);
    main_menu.logo (renderer);

    Text play_txt, exit_txt;
    Mix_Chunk *m_sound;
    m_sound = Mix_LoadWAV ("sound//select.wav");

    play_txt.text = "PLAY";
    play_txt.color = {255, 255, 255};
    play_txt.text_x = 500;
    play_txt.text_y = 300;
    play_txt.text_w = 200;
    play_txt.text_h = 70;
    play_txt.draw (renderer);

    exit_txt.text = "EXIT";
    exit_txt.color = {255, 255, 255};
    exit_txt.text_x = 550;
    exit_txt.text_y = 380;
    exit_txt.text_w = 100;
    exit_txt.text_h = 50;
    exit_txt.draw (renderer);

    SDL_RenderPresent (renderer);
    SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
    bool quit = false;
    int play_sound = 0, exit_sound = 0;
    SDL_Event m;

    while (!quit)
    {
        main_menu.background (renderer);
        main_menu.logo (renderer);
        play_txt.draw (renderer);
        exit_txt.draw (renderer);

        if (SDL_PollEvent (&m) == 0) {} // ko bam thi tiep tuc chay
        switch (m.type)
        {
            case SDL_QUIT:
            {
                quit = true;
                game.status = "quit";
                break;
            }
            case SDL_MOUSEMOTION:
            {
                main_menu.pointer_x = m.motion.x;
                main_menu.pointer_y = m.motion.y;

                if (main_menu.pointer_x >= play_txt.text_x &&
                    main_menu.pointer_x <= play_txt.text_x + play_txt.text_w &&
                    main_menu.pointer_y >= play_txt.text_y &&
                    main_menu.pointer_y <= play_txt.text_y + play_txt.text_h)
                {
                    play_txt.color = {255, 255, 0};
                    play_sound++;
                }

                else
                {
                    play_txt.color = {255, 255, 255};
                    play_sound = 0;
                }

                if (main_menu.pointer_x >= exit_txt.text_x &&
                    main_menu.pointer_x <= exit_txt.text_x + exit_txt.text_w &&
                    main_menu.pointer_y >= exit_txt.text_y &&
                    main_menu.pointer_y <= exit_txt.text_y + exit_txt.text_h)
                {
                    exit_txt.color = {255, 255, 0};
                    exit_sound++;
                }
                else
                {
                    exit_txt.color = {255, 255, 255};
                    exit_sound = 0;
                }
                if (play_sound == 1 || exit_sound == 1)
                    Mix_PlayChannel(-1, m_sound, 0);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                main_menu.pointer_x = m.button.x;
                main_menu.pointer_y = m.button.y;

                if (main_menu.pointer_x >= play_txt.text_x &&
                    main_menu.pointer_x <= play_txt.text_x + play_txt.text_w &&
                    main_menu.pointer_y >= play_txt.text_y &&
                    main_menu.pointer_y <= play_txt.text_y + play_txt.text_h &&
                    m.button.button == SDL_BUTTON_LEFT)
                    {
                        game.status = "select";
                    }
                else if (main_menu.pointer_x >= exit_txt.text_x &&
                         main_menu.pointer_x <= exit_txt.text_x + exit_txt.text_w &&
                         main_menu.pointer_y >= exit_txt.text_y &&
                         main_menu.pointer_y <= exit_txt.text_y + exit_txt.text_h &&
                         m.button.button == SDL_BUTTON_LEFT)
                        {
                            game.status = "quit";
                            quit = true;
                        }
                break;
            }
        }
        if (game.status == "select")
            Select (renderer, select, game, player, enemy, menu_time);
        if (game.status == "play")
            quit = true;
        if (game.status == "quit")
            quit = true;
        SDL_RenderPresent (renderer);
        SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
        SDL_RenderClear (renderer);

    }

}
