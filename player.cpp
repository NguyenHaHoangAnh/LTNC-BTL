#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "game.h"

void Move (SDL_Renderer *renderer, Game &game,
           character &player, character &enemy,
           SDL_Event &e, Text &_time, Mix_Chunk *sound[2])
{
    if (player.y + char_height + gravity < ground)
    {
        if (player.y <= 103)
        {
            player.frameCurrent = 0;
            player.get_animation ("Fall", player.frameMax, 5);
        }
        if (player.y + char_height >= ground-5)
        {
            player.jump = false;
            if ((player.key_right_pressed == true || player.key_left_pressed == true) && player.jump == false)
                player.get_animation ("Run", player.frameMax, 3);
            else if (player.key_right_pressed == false && player.key_left_pressed == false && player.jump == false)
                player.get_animation ("Idle", player.frameMax, 10);
        }
        player.update (renderer);
    }
    else if (player.key_left_pressed == false && player.key_right_pressed == false &&
        player.jump == false && player.attack == false &&
        player.in_attack == false && player.in_fire == false && player.death == false)
            player.get_animation ("Idle", player.frameMax, 10);
    if (player.in_attack)
        player.get_animation ("Attack1", player.frameMax, 4);
    else if (player.in_fire)
        player.get_animation ("Attack2", player.frameMax, 4);
    if (SDL_PollEvent (&e) == 0) {} // ko bam thi tiep tuc chay
    else if (e.type == SDL_QUIT) game.status = "quit";
    else if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_ESCAPE: break;
            case SDLK_LEFT:
            {
                if (player.in_attack == false && player.in_fire == false &&
                    player.death == false && player.died == false)
                {
                    player.key_left_pressed = true;
                    if (fabs (player.x - (enemy.x + char_width / 2)) <= 20) // moc: 825, 820 <= player.x <= 830
                        player.velocity_x = 0;
                    else
                        player.velocity_x = -step;
                    player.lastKey = "left";
                    player.get_animation ("Run", player.frameMax, 3);
                    player.attack_x = player.x - 10;
                    if (!player.fire) player.fire_x = player.x;
                }
                break;
            }
            case SDLK_RIGHT:
            {
                if (player.in_attack == false && player.in_fire == false &&
                    player.death == false && player.died == false)
                {
                    player.key_right_pressed = true;
                    if (fabs ((player.x + char_width) - (enemy.x + char_width / 2)) <= 20)
                        player.velocity_x = 0;
                    else
                        player.velocity_x = step;
                    player.lastKey = "right";
                    player.get_animation ("Run", player.frameMax, 3);
                    player.attack_x = player.x + 75;
                    if (!player.fire) player.fire_x = player.x + char_width;
                }
                break;
            }
            case SDLK_UP:
            {
                if (player.in_attack == false && player.in_fire == false &&
                    player.death == false && player.died == false && player.jump == false)
                {
                    player.jump = true;
                    player.frameCurrent = 0;
                    player.get_animation ("Jump", player.frameMax, 5);
                    player.velocity_y = -jump_height;
                    break;
                }
            }
            case SDLK_c: // attack
            {
                if (player.in_attack == false && player.in_fire == false &&
                    player.death == false && player.died == false && player.jump == false)
                {
                    player.attack = true;
                    player.in_attack = true;
                    player.key_left_pressed = false;
                    player.key_right_pressed = false;
                    player.frameCurrent = 0;
                    Mix_PlayChannel(-1, sound[0], 0);
                }
                break;
            }
            case SDLK_x: // fire
            {
                if (player.in_attack == false && player.in_fire == false &&
                    player.death == false && player.died == false && player.jump == false)
                {
                    player.fire = true;
                    player.in_fire = true;
                    if (player.lastKey == "right")
                        player.fire_velocity = fire_step;
                    else if (player.lastKey == "left")
                        player.fire_velocity = -fire_step;
                    player.key_left_pressed = false;
                    player.key_right_pressed = false;
                    player.frameCurrent = 0;
                    Mix_PlayChannel(-1, sound[1], 0);
                }
                break;
            }
            default: break;
        }
    }
    else if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_ESCAPE: break;
            case SDLK_LEFT:
            {
                player.velocity_x = 0;
                player.key_left_pressed = false;
                break;
            }
            case SDLK_RIGHT:
            {
                player.velocity_x = 0;
                player.key_right_pressed = false;
                break;
            }
            case SDLK_UP:
            {
                break;
            }
            case SDLK_c: // attack
            {
                player.attack = false;
                break;
            }
            case SDLK_x: // fire
            {
                break;
            }
        }
    }
    if (player.fire) player_fire (renderer, player, enemy);
    player.update (renderer);
}

bool player_in_target (character &player, character &enemy)
{
    if (player.lastKey == "right")
    {
        if (player.fire_x + fire_width >= enemy.x + 50 && player.x <= enemy.x)
            return true;
    }
    else if (player.lastKey == "left")
    {
        if (player.fire_x <= enemy.x + char_width - 50 && player.x >= enemy.x)
            return true;
    }
    return false;
}

void player_fire (SDL_Renderer *renderer, character &player, character &enemy)
{
    if (player.lastKey == "right")
    {

        if (player.fire_x + fire_width + player.fire_velocity >= SCREEN_WIDTH || player_in_target (player, enemy) == true)
        {
            player.fire = false;
            player.fire_velocity = 0;
            player.fire_x = player.x + char_width;
        }
    }
    else if (player.lastKey == "left")
    {

        if (player.fire_x + player.fire_velocity <= 0 || player_in_target (player, enemy) == true)
        {
            player.fire = false;
            player.fire_velocity = 0;
            player.fire_x = player.x;
        }
    }
    player.fire_update (renderer);
    if (player_in_target (player, enemy) == true && player.fire == true) player.in_target = true;
    else player.in_target = false;
}

void player_attack (character &player, character &enemy)
{
    if (player.lastKey == "right" && (player.attack == true || player.in_target == true))
    {
        if ((enemy.x + char_width/2) >= (player.x + char_width/2) &&
            (enemy.x + char_width/2) <= (player.x + char_width + attack_width[player.number]))
            enemy.health -= normal_damage[player.number];
        else if (player.in_target)
        {
            enemy.health -= shoot_damage;
            player.in_target = false;
            player.fire = false;
            player.fire_x = player.x + char_width;
        }
    }
    else if (player.lastKey == "left" && (player.attack == true || player.in_target == true))
    {
        if ((enemy.x + char_width/2) <= (player.x + char_width/2) &&
            (enemy.x + char_width/2) >= (player.x - attack_width[player.number]))
            enemy.health -= normal_damage[player.number];
        else if (player.in_target)
        {
            enemy.health -= shoot_damage;
            player.in_target = false;
            player.fire = false;
            player.fire_x = player.x;
        }
    }
    if (enemy.health <= 0)
    {
        enemy.health = 0;
        enemy.death = true;
    }
}
