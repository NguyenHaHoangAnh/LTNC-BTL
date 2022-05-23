#include <iostream>
#include <string>
#include "game.h"

const int max_char = 2;
const int can_play = 3;

void Select_char (SDL_Renderer *renderer, character *select_char)
{
    // char 1
    select_char[0].number = 1;
    select_char[0].lastKey = "right";
    select_char[0].x = 225;
    select_char[0].y = 300;
    select_char[0].frame_width = 50;
    select_char[0].frame_height = 55;
    select_char[0].get_animation ("Idle", select_char[0].frameMax, 10);
    select_char[0].animation ();
    select_char[0].draw (renderer);

    // char 2
    select_char[1].number = 2;
    select_char[1].lastKey = "right";
    select_char[1].x = 425;
    select_char[1].y = 300;
    select_char[1].frame_width = 60;
    select_char[1].frame_height = 62;
    select_char[1].get_animation ("Idle", select_char[1].frameMax, 10);
    select_char[1].animation ();
    select_char[1].draw (renderer);

    // char 3
    select_char[2].number = 3;
    select_char[2].lastKey = "right";
    select_char[2].x = 625;
    select_char[2].y = 300;
    select_char[2].frame_width = 45;
    select_char[2].frame_height = 45;
    select_char[2].get_animation ("Idle", select_char[2].frameMax, 10);
    select_char[2].animation ();
    select_char[2].draw (renderer);

    // char 4
    select_char[3].number = 4;
    select_char[3].lastKey = "right";
    select_char[3].x = 825;
    select_char[3].y = 300;
    select_char[3].frame_width = 50;
    select_char[3].frame_height = 55;
    select_char[3].get_animation ("Idle", select_char[3].frameMax, 10);
    select_char[3].animation ();
    select_char[3].draw (renderer);
}

void Select (SDL_Renderer *renderer, Menu &select, Game &game, character &player, character &enemy, int &menu_time)
{
    select.background (renderer);

    Text play_txt, back_txt, select_txt;
    Mix_Chunk *m_sound;
    m_sound = Mix_LoadWAV ("sound//select.wav");

    play_txt.text = "PLAY";
    play_txt.color = {255, 255, 255};
    play_txt.text_x = 1050;
    play_txt.text_y = 10;
    play_txt.text_w = 100;
    play_txt.text_h = 50;
    play_txt.draw (renderer);

    back_txt.text = "BACK";
    back_txt.color = {255, 255, 255};
    back_txt.text_x = 50;
    back_txt.text_y = 10;
    back_txt.text_w = 100;
    back_txt.text_h = 50;
    back_txt.draw (renderer);

    select_txt.text = "PLAYER SELECT";
    select_txt.color = {255, 255, 255};
    select_txt.text_x = 450;
    select_txt.text_y = 150;
    select_txt.text_w = 300;
    select_txt.text_h = 50;
    select_txt.draw (renderer);

    Text char_txt[4];
    // char 1
    char_txt[0].text = "NINJA";
    char_txt[0].color = {255, 255, 255};
    char_txt[0].text_x = 250;
    char_txt[0].text_y = 460;
    char_txt[0].text_w = 100;
    char_txt[0].text_h = 50;
    char_txt[0].draw (renderer);
    // char 2
    char_txt[1].text = "SAMURAI";
    char_txt[1].color = {255, 255, 255};
    char_txt[1].text_x = 450;
    char_txt[1].text_y = 460;
    char_txt[1].text_w = 100;
    char_txt[1].text_h = 50;
    char_txt[1].draw (renderer);
    // char 3
    char_txt[2].text = "KNIGHT";
    char_txt[2].color = {255, 255, 255};
    char_txt[2].text_x = 650;
    char_txt[2].text_y = 460;
    char_txt[2].text_w = 100;
    char_txt[2].text_h = 50;
    char_txt[2].draw (renderer);
    // char 4
    char_txt[3].text = "WARRIOR";
    char_txt[3].color = {255, 255, 255};
    char_txt[3].text_x = 850;
    char_txt[3].text_y = 460;
    char_txt[3].text_w = 100;
    char_txt[3].text_h = 50;
    char_txt[3].draw (renderer);

    character select_char[4];
    Select_char (renderer, select_char);

    Text mode_txt[3];
    // easy
    mode_txt[0].text = "EASY";
    mode_txt[0].color = {255, 255, 255};
    mode_txt[0].text_x = 400;
    mode_txt[0].text_y = 200;
    mode_txt[0].text_w = 100;
    mode_txt[0].text_h = 50;
    //mode_txt[0].draw (renderer);
    // medium
    mode_txt[1].text = "MEDIUM";
    mode_txt[1].color = {255, 255, 255};
    mode_txt[1].text_x = 550;
    mode_txt[1].text_y = 200;
    mode_txt[1].text_w = 100;
    mode_txt[1].text_h = 50;
    // hard
    mode_txt[2].text = "HARD";
    mode_txt[2].color = {255, 255, 255};
    mode_txt[2].text_x = 700;
    mode_txt[2].text_y = 200;
    mode_txt[2].text_w = 100;
    mode_txt[2].text_h = 50;

    SDL_RenderPresent (renderer);
    SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
    SDL_RenderClear (renderer);
    bool quit = false;
    int dem = 0;
    int play_sound = 0, back_sound = 0;
    int char_sound[4] = {0};
    int mode_sound[3] = {0};
    SDL_Event m;

    while (!quit)
    {
        select.background (renderer);
        play_txt.draw (renderer);
        back_txt.draw (renderer);
        select_txt.draw (renderer);
        if (dem == 1) select_txt.text = "COMPUTER SELECT";
        else if (dem == 2)
        {
            select_txt.text = "SELECT DIFFICULTY";
            mode_txt[0].draw (renderer);
            mode_txt[1].draw (renderer);
            mode_txt[2].draw (renderer);
        }
        else if (dem == 3)
        {
            select_txt.text = "LET'S PLAY";
            mode_txt[0].draw (renderer);
            mode_txt[1].draw (renderer);
            mode_txt[2].draw (renderer);
        }
        char_txt[0].draw (renderer);
        char_txt[1].draw (renderer);
        char_txt[2].draw (renderer);
        char_txt[3].draw (renderer);
        Select_char (renderer, select_char);
        if (game.status != "play")
            menu_time = SDL_GetTicks() / 1000;

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
                select.pointer_x = m.motion.x;
                select.pointer_y = m.motion.y;
                // play
                if (select.pointer_x >= play_txt.text_x &&
                    select.pointer_x <= play_txt.text_x + play_txt.text_w &&
                    select.pointer_y >= play_txt.text_y &&
                    select.pointer_y <= play_txt.text_y + play_txt.text_h)
                {
                    play_txt.color = {255, 255, 0};
                    play_sound++;
                }

                else
                {
                    play_txt.color = {255, 255, 255};
                    play_sound = 0;
                }
                // back
                if (select.pointer_x >= back_txt.text_x &&
                    select.pointer_x <= back_txt.text_x + back_txt.text_w &&
                    select.pointer_y >= back_txt.text_y &&
                    select.pointer_y <= back_txt.text_y + back_txt.text_h)
                {
                    back_txt.color = {255, 255, 0};
                    back_sound++;
                }
                else
                {
                    back_txt.color = {255, 255, 255};
                    back_sound = 0;
                }
                // char 1
                if (select.pointer_x >= select_char[0].x &&
                    select.pointer_x <= select_char[0].x + char_width &&
                    select.pointer_y >= select_char[0].y &&
                    select.pointer_y <= select_char[0].y + char_height)
                {
                    char_txt[0].color = {255, 255, 0};
                    char_sound[0]++;
                }
                else
                {
                    char_txt[0].color = {255, 255, 255};
                    char_sound[0] = 0;
                }
                // char 2
                if (select.pointer_x >= select_char[1].x &&
                    select.pointer_x <= select_char[1].x + char_width &&
                    select.pointer_y >= select_char[1].y &&
                    select.pointer_y <= select_char[1].y + char_height)
                {
                    char_txt[1].color = {255, 255, 0};
                    char_sound[1]++;
                }
                else
                {
                    char_txt[1].color = {255, 255, 255};
                    char_sound[1] = 0;
                }
                // char 3
                if (select.pointer_x >= select_char[2].x &&
                    select.pointer_x <= select_char[2].x + char_width &&
                    select.pointer_y >= select_char[2].y &&
                    select.pointer_y <= select_char[2].y + char_height)
                {
                    char_txt[2].color = {255, 255, 0};
                    char_sound[2]++;
                }
                else
                {
                    char_txt[2].color = {255, 255, 255};
                    char_sound[2] = 0;
                }
                // char 4
                if (select.pointer_x >= select_char[3].x &&
                    select.pointer_x <= select_char[3].x + char_width &&
                    select.pointer_y >= select_char[3].y &&
                    select.pointer_y <= select_char[3].y + char_height)
                {
                    char_txt[3].color = {255, 255, 0};
                    char_sound[3]++;
                }
                else
                {
                    char_txt[3].color = {255, 255, 255};
                    char_sound[3] = 0;
                }
                // easy
                if (select.pointer_x >= mode_txt[0].text_x &&
                    select.pointer_x <= mode_txt[0].text_x + mode_txt[0].text_w &&
                    select.pointer_y >= mode_txt[0].text_y &&
                    select.pointer_y <= mode_txt[0].text_y + mode_txt[0].text_h)
                {
                    if (dem == max_char)
                    {
                        mode_txt[0].color = {255, 255, 0};
                        mode_sound[0]++;
                    }
                }

                else
                {
                    if (dem == max_char)
                    {
                        mode_txt[0].color = {255, 255, 255};
                        mode_sound[0] = 0;
                    }
                }
                // medium
                if (select.pointer_x >= mode_txt[1].text_x &&
                    select.pointer_x <= mode_txt[1].text_x + mode_txt[1].text_w &&
                    select.pointer_y >= mode_txt[1].text_y &&
                    select.pointer_y <= mode_txt[1].text_y + mode_txt[1].text_h)
                {
                    if (dem == max_char)
                    {
                        mode_txt[1].color = {255, 255, 0};
                        mode_sound[1]++;
                    }
                }

                else
                {
                    if (dem == max_char)
                    {
                        mode_txt[1].color = {255, 255, 255};
                        mode_sound[1] = 0;
                    }
                }
                // hard
                if (select.pointer_x >= mode_txt[2].text_x &&
                    select.pointer_x <= mode_txt[2].text_x + mode_txt[2].text_w &&
                    select.pointer_y >= mode_txt[2].text_y &&
                    select.pointer_y <= mode_txt[2].text_y + mode_txt[2].text_h)
                {
                    if (dem == max_char)
                    {
                        mode_txt[2].color = {255, 255, 0};
                        mode_sound[2]++;
                    }
                }

                else
                {
                    if (dem == max_char)
                    {
                        mode_txt[2].color = {255, 255, 255};
                        mode_sound[2] = 0;
                    }
                }

                if (play_sound == 1 || back_sound == 1 ||
                    char_sound[0] == 1 || char_sound[1] == 1 ||
                    char_sound[2] == 1 || char_sound[3] == 1 ||
                    mode_sound[0] == 1 || mode_sound[1] == 1 ||
                    mode_sound[2] == 1)
                    Mix_PlayChannel(-1, m_sound, 0);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                select.pointer_x = m.button.x;
                select.pointer_y = m.button.y;

                // char 1
                if (select.pointer_x >= select_char[0].x &&
                    select.pointer_x <= select_char[0].x + char_width &&
                    select.pointer_y >= select_char[0].y &&
                    select.pointer_y <= select_char[0].y + char_height &&
                    m.button.button == SDL_BUTTON_LEFT)
                {
                    if (dem == 0)
                    {
                        player.number = 1;
                        dem++;
                    }
                    else if (dem == 1)
                    {
                        enemy.number = 1;
                        dem++;
                    }
                }
                // char 2
                else if (select.pointer_x >= select_char[1].x &&
                         select.pointer_x <= select_char[1].x + char_width &&
                         select.pointer_y >= select_char[1].y &&
                         select.pointer_y <= select_char[1].y + char_height &&
                         m.button.button == SDL_BUTTON_LEFT)
                {
                    if (dem == 0)
                    {
                        player.number = 2;
                        dem++;
                    }
                    else if (dem == 1)
                    {
                        enemy.number = 2;
                        dem++;
                    }
                }
                // char 3
                else if (select.pointer_x >= select_char[2].x &&
                         select.pointer_x <= select_char[2].x + char_width &&
                         select.pointer_y >= select_char[2].y &&
                         select.pointer_y <= select_char[2].y + char_height &&
                         m.button.button == SDL_BUTTON_LEFT)
                {
                    if (dem == 0)
                    {
                        player.number = 3;
                        dem++;
                    }
                    else if (dem == 1)
                    {
                        enemy.number = 3;
                        dem++;
                    }
                }
                // char 4
                else if (select.pointer_x >= select_char[3].x &&
                         select.pointer_x <= select_char[3].x + char_width &&
                         select.pointer_y >= select_char[3].y &&
                         select.pointer_y <= select_char[3].y + char_height &&
                         m.button.button == SDL_BUTTON_LEFT)
                {
                    if (dem == 0)
                    {
                        player.number = 4;
                        dem++;
                    }
                    else if (dem == 1)
                    {
                        enemy.number = 4;
                        dem++;
                    }
                }
                // easy
                else if (select.pointer_x >= mode_txt[0].text_x &&
                         select.pointer_x <= mode_txt[0].text_x + mode_txt[0].text_w &&
                         select.pointer_y >= mode_txt[0].text_y &&
                         select.pointer_y <= mode_txt[0].text_y + mode_txt[0].text_h &&
                         m.button.button == SDL_BUTTON_LEFT && dem == max_char)
                {
                    game.mode = "easy";
                    mode_txt[0].color = {255, 255, 0};
                    dem++;
                }
                // medium
                else if (select.pointer_x >= mode_txt[1].text_x &&
                         select.pointer_x <= mode_txt[1].text_x + mode_txt[1].text_w &&
                         select.pointer_y >= mode_txt[1].text_y &&
                         select.pointer_y <= mode_txt[1].text_y + mode_txt[1].text_h &&
                         m.button.button == SDL_BUTTON_LEFT && dem == max_char)
                {
                    game.mode = "medium";
                    mode_txt[1].color = {255, 255, 0};
                    dem++;
                }
                // hard
                else if (select.pointer_x >= mode_txt[2].text_x &&
                         select.pointer_x <= mode_txt[2].text_x + mode_txt[2].text_w &&
                         select.pointer_y >= mode_txt[2].text_y &&
                         select.pointer_y <= mode_txt[2].text_y + mode_txt[2].text_h &&
                         m.button.button == SDL_BUTTON_LEFT && dem == max_char)
                {
                    game.mode = "hard";
                    mode_txt[2].color = {255, 255, 0};
                    dem++;
                }
                // play
                else if (select.pointer_x >= play_txt.text_x &&
                         select.pointer_x <= play_txt.text_x + play_txt.text_w &&
                         select.pointer_y >= play_txt.text_y &&
                         select.pointer_y <= play_txt.text_y + play_txt.text_h &&
                         m.button.button == SDL_BUTTON_LEFT && dem == can_play)
                {
                    game.status = "play";
                    quit = true;
                }
                // back
                else if (select.pointer_x >= back_txt.text_x &&
                         select.pointer_x <= back_txt.text_x + back_txt.text_w &&
                         select.pointer_y >= back_txt.text_y &&
                         select.pointer_y <= back_txt.text_y + back_txt.text_h &&
                         m.button.button == SDL_BUTTON_LEFT)
                {
                    game.status = "back";
                    dem = 0;
                    quit = true;
                }

                break;
            }
        }
        SDL_RenderPresent (renderer);
        SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
        SDL_RenderClear (renderer);

    }

}
