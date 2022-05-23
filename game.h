#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <cmath>
#include "Menu.h"

struct Game
{
    string status, mode;

    void init (character &player, character &enemy, Text &_time, Mix_Chunk *sound[2], Mix_Music *music)
    {
        //// player
        // position
        player.x = 150;//150
        player.y = 350;//350
        player.velocity_x = 0;
        player.velocity_y = 0;
        player.jump = false;
        player.key_left_pressed = false;
        player.key_right_pressed = false;
        player.lastKey = "right";//right
        player.get_animation ("Idle", player.frameMax, 10);
        // attack
        player.attack_x = player.x + 75;
        player.attack_y = player.y;
        player.attack = false;
        player.in_attack = false;
        // health
        player.health = -max_health;
        player.health_bar_x = 550;
        player.health_bar_y = 10;
        player.health_bar_w = -health_bar_length;
        player.health_bar_x2 = 552;
        player.health_bar_y2 = 8;
        player.health_bar_w2 = -504;
        player.death = false;
        player.died = false;

        //// enemy
        // position
        enemy.x = 900;//900
        enemy.y = 350;//350
        enemy.velocity_x = 0;
        enemy.velocity_y = 0;
        enemy.jump = false;
        enemy.key_left_pressed = false;
        enemy.key_right_pressed = false;
        enemy.lastKey = "left";//left
        enemy.get_animation ("Idle", enemy.frameMax, 10);
        // attack
        enemy.attack_x = enemy.x - 10;
        enemy.attack_y = enemy.y;
        enemy.attack = false;
        enemy.in_attack = false;
        // health
        enemy.health = max_health;
        enemy.health_bar_x = 650;
        enemy.health_bar_y = 10;
        enemy.health_bar_w = health_bar_length;
        enemy.health_bar_x2 = 648;
        enemy.health_bar_y2 = 8;
        enemy.health_bar_w2 = 504;
        enemy.death = false;
        enemy.died = false;

        // fire
        player.fire = false;
        player.fire_x = player.x + char_width;
        player.fire_y = player.y + 50;
        player.fire_velocity = 0;
        player.in_target = false;
        player.in_fire = false;

        enemy.fire = false;
        enemy.fire_x = enemy.x;
        enemy.fire_y = enemy.y + 50;
        enemy.fire_velocity = 0;
        enemy.in_target = false;
        enemy.in_fire = false;

        // frameCurrent
        player.frameCurrent = 0;
        player.frameElapsed = 0;

        enemy.frameCurrent = 0;
        enemy.frameElapsed = 0;

        // Time
        _time.text_x = 560;
        _time.text_y = -5;
        _time.text_w = 80;
        _time.text_h = 80;
        _time.color = {255, 255, 255}; // white

        // Sound + music
        sound[0] = Mix_LoadWAV ("sound//attack.wav");
        sound[1] = Mix_LoadWAV ("sound//fire.wav");
        music = Mix_LoadMUS ("sound//music.wav");

        // frame
        switch (player.number)
        {
            case 1:
            {
                player.frame_width = 50;
                player.frame_height = 55;
                break;
            }
            case 2:
            {
                player.frame_width = 60;
                player.frame_height = 62;
                break;
            }
            case 3:
            {
                player.frame_width = 45;
                player.frame_height = 45;
                break;
            }
            case 4:
            {
                player.frame_width = 50;
                player.frame_height = 55;
                break;
            }
        }
        switch (enemy.number)
        {
            case 1:
            {
                enemy.frame_width = 50;
                enemy.frame_height = 55;
                break;
            }
            case 2:
            {
                enemy.frame_width = 60;
                enemy.frame_height = 62;
                break;
            }
            case 3:
            {
                enemy.frame_width = 45;
                enemy.frame_height = 45;
                break;
            }
            case 4:
            {
                enemy.frame_width = 50;
                enemy.frame_height = 55;
                break;
            }
        }
    }

    void background (SDL_Renderer *renderer)
    {
        SDL_Texture *background_img = loadTexture ("image//background.jpg", renderer);
        SDL_Rect background;
        SDL_QueryTexture (background_img, NULL, NULL, &background.w, &background.h);
        background.x = 0;
        background.y = 0;
        background.h = SCREEN_HEIGHT;
        background.w = SCREEN_WIDTH;
        SDL_RenderCopy (renderer, background_img, NULL, &background);
    }

    bool over (character &player, character &enemy, Text &_time)
    {
        if (_time.text == "00") return true;
        if ((player.health >= 0 || enemy.health <= 0) &&
             player.in_attack == false && enemy.in_attack == false &&
             player.in_fire == false && enemy.in_fire == false)
            return true;
        return false;
    }

    void result (SDL_Renderer *renderer, character &player, character &enemy, Text &_time)
    {
        SDL_Texture *result_img;
        if (_time.text == "00")
        {
            if (fabs (player.health) >= enemy.health) result_img = loadTexture ("image//win.jpg", renderer);
            else if (fabs (player.health) < enemy.health) result_img = loadTexture ("image//lose.jpg", renderer);
        }
        else
        {
            if (player.health >= 0) result_img = loadTexture ("image//lose.jpg", renderer);
            else if (enemy.health <= 0) result_img = loadTexture ("image//win.jpg", renderer);
        }
        SDL_Rect result;
        SDL_QueryTexture (result_img, NULL, NULL, &result.w, &result.h);
        result.x = 400;
        result.y = 100;
        result.h = 200;
        result.w = 400;
        SDL_RenderCopy (renderer, result_img, NULL, &result);
    }

    void display (SDL_Renderer *renderer, character &player, character &enemy, Text &_time)
    {
        background (renderer);

        enemy.health_bar (renderer);
        player.health_bar (renderer);

        _time.draw (renderer);

    }
};

// Time
void getTime (int &time_val, Text &_time);

// Main menu
void Main_menu (SDL_Renderer *renderer, Menu &main_menu, Game &game, int &menu_time,
                character &player, character &enemy, Menu &select);
void Select (SDL_Renderer *renderer, Menu &select, Game &game, character &player, character &enemy, int &menu_time);

// fire
void player_fire (SDL_Renderer *renderer, character &player, character &enemy);
void can_AI_Fire (character &enemy, character &player, Mix_Chunk *sound[2]);
void enemy_fire (SDL_Renderer *renderer, character &player, character &enemy);

void player_attack (character &player, character &enemy);
void Move (SDL_Renderer *renderer, Game &game,
           character &player, character &enemy,
           SDL_Event &e, Text &_time, Mix_Chunk *sound[2]);

void AI_Move (Game &game, character &player, character &enemy, Mix_Chunk *sound[2]);
void AI (SDL_Renderer *renderer, Game &game, character &player, character &enemy, Text &_time, Mix_Chunk *sound[2]);
void enemy_attack (character &player, character &enemy, Game &game);

#endif // GAME_H_
