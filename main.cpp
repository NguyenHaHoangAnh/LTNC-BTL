#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "game.h"

int main (int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    initSDL (window, renderer);
    srand (time (0));

    Game game;
    character player;
    character enemy;
    Text _time;
    Menu main_menu;
    Menu select;

    // Time
    int time_val, menu_time;

    // MAIN MENU
    Main_menu (renderer, main_menu, game, menu_time, player, enemy, select);
    SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
    SDL_RenderClear (renderer);
    if (game.status == "quit")
        quitSDL (window, renderer);
    else if (game.status == "play")
    {
        Mix_Chunk *sound[2];
        Mix_Music *music;
        Mix_PlayMusic (music, -1);

        game.init (player, enemy, _time, sound, music);
        SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
        game.display (renderer, player, enemy, _time);
        player.update (renderer);
        enemy.update (renderer);
        SDL_RenderPresent (renderer);
        SDL_RenderClear (renderer);

        SDL_Event e;
        while (!game.over (player, enemy, _time))
        {
            if (game.status == "quit") break;
            time_val = SDL_GetTicks () / 1000 - menu_time;
            getTime (time_val, _time);

            SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
            SDL_RenderClear (renderer);
            game.display (renderer, player, enemy, _time);

            Move (renderer, game, player, enemy, e, _time, sound);
            AI (renderer, game, player, enemy, _time, sound);

            player_attack (player, enemy);
            enemy_attack (player, enemy, game);

            SDL_RenderPresent (renderer);
        }

        while (game.over (player, enemy, _time))
        {
            if (player.died == true || enemy.died == true) break;
            SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
            SDL_RenderClear (renderer);

            game.display (renderer, player, enemy, _time);
            game.result (renderer, player, enemy, _time);
            if (player.death)
                player.get_animation ("Death", player.frameMax, 5);
            else if (player.death == false && player.in_attack == false && player.in_fire == false)
                player.get_animation ("Idle", player.frameMax, 10);
            if (enemy.death)
                enemy.get_animation ("Death", enemy.frameMax, 5);
            else if (enemy.death == false && enemy.in_attack == false && enemy.in_fire == false)
                enemy.get_animation ("Idle", enemy.frameMax, 10);

            player.animation ();
            player.draw (renderer);
            enemy.animation ();
            enemy.draw (renderer);

            SDL_RenderPresent (renderer);
        }

        if (game.status != "quit") waitUntilKeyPressed ();
    }
    quitSDL (window, renderer);

    return 0;
}
