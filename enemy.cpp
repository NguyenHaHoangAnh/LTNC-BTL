#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "game.h"

int Random ()
{
    return rand () % 10 + 0;
}

void can_AI_Fire (character &enemy, character &player, Mix_Chunk *sound[2])
{
    if (AI_fire[Random ()] == 1 && abs (enemy.x - player.x) >= 350) enemy.fire = true;
    else enemy.fire = false;
    if (enemy.fire)
    {
        Mix_PlayChannel(-1, sound[1], 0);
        enemy.in_fire = true;
        if (enemy.lastKey == "right")
            enemy.fire_velocity = fire_step;
        else if (enemy.lastKey == "left")
            enemy.fire_velocity = -fire_step;
        enemy.key_left_pressed = false;
        enemy.key_right_pressed = false;
    }
    else
    {
        enemy.in_fire = false;
        enemy.fire_velocity = 0;
    }
}

bool enemy_in_target (character &player, character &enemy)
{
    if (enemy.lastKey == "right")
    {
        if ((enemy.fire_x + fire_width >= player.x + 50 && enemy.x <= player.x) && fabs(enemy.y - player.y) <= 10)
            return true;
    }
    else if (enemy.lastKey == "left")
    {
        if ((enemy.fire_x <= player.x + char_width - 50 && enemy.x >= player.x) && fabs(enemy.y - player.y) <= 10)
            return true;
    }
    return false;
}

void enemy_fire (SDL_Renderer *renderer, character &player, character &enemy)
{
    enemy.key_left_pressed = false;
    enemy.key_right_pressed = false;
    enemy.attack = false;
    if (enemy.lastKey == "right")
    {
        if (enemy.fire_x + fire_width + enemy.fire_velocity >= SCREEN_WIDTH || enemy_in_target (player, enemy) == true)
        {
            enemy.fire = false;
            enemy.fire_velocity = 0;
            enemy.fire_x = enemy.x + char_width;
        }
    }
    else if (enemy.lastKey == "left")
    {

        if (enemy.fire_x + enemy.fire_velocity <= 0 || enemy_in_target (player, enemy) == true)
        {
            enemy.fire = false;
            enemy.fire_velocity = 0;
            enemy.fire_x = enemy.x;
        }
    }
    enemy.fire_update (renderer);
    if (enemy_in_target (player, enemy) == true && enemy.fire == true) enemy.in_target = true;
    else enemy.in_target = false;
}

void AI_Move (character &player, character &enemy, Mix_Chunk *sound[2])
{
    //move
    if (enemy.key_left_pressed == false && enemy.key_right_pressed == false)
    {
        if (enemy.x >= (player.x + char_width - 70))
        {
            if (enemy.in_attack == false && enemy.in_fire == false &&
                player.death == false && enemy.death == false && enemy.died == false)
            {
                enemy.key_left_pressed = true;
                enemy.key_right_pressed = false;
                enemy.attack = false;
                enemy.fire = false;
                enemy.lastKey = "left";
            }

        }
        else if (enemy.x <= (player.x - 70))
        {
            if (enemy.in_attack == false && enemy.in_fire == false &&
                player.death == false && enemy.death == false && enemy.died == false)
            {
                enemy.key_left_pressed = false;
                enemy.key_right_pressed = true;
                enemy.attack = false;
                enemy.fire = false;
                enemy.lastKey = "right";
            }
        }
    }
    if (enemy.key_left_pressed)
    {
        if (fabs (enemy.x - (player.x + char_width / 2)) <= 20)
            enemy.velocity_x = 0;
        else
            enemy.velocity_x = -step;
        enemy.attack_x = enemy.x;
        enemy.get_animation ("Run", enemy.frameMax, 3);
        if (!enemy.fire) enemy.fire_x = enemy.x;
    }
    else if (enemy.key_right_pressed)
    {
        if (fabs ((enemy.x + char_width) - (player.x + char_width / 2)) <= 20)
            enemy.velocity_x = 0;
        else
            enemy.velocity_x = step;
        enemy.attack_x = enemy.x + 75;
        enemy.get_animation ("Run", enemy.frameMax, 3);
        if (!enemy.fire) enemy.fire_x = enemy.x + char_width;
    }
    // action
    if (enemy.velocity_x == 0)
    {
        switch (AI_action[Random ()])
        {
            case 0:
            {
                enemy.key_left_pressed = false;
                enemy.key_right_pressed = false;
                enemy.attack = false;
                enemy.fire = false;
                enemy.get_animation ("Idle", enemy.frameMax, 10);
                break;
            }
            case 1:
            {
                if (enemy.in_attack == false && enemy.in_fire == false &&
                    enemy.death == false && enemy.died == false)
                {
                    enemy.key_left_pressed = false;
                    enemy.key_right_pressed = false;
                    enemy.attack = true;
                    enemy.in_attack = true;
                    enemy.fire = false;
                    enemy.frameCurrent = 0;
                    Mix_PlayChannel(-1, sound[0], 0);
                }
                break;
            }
        }
    }

}

void AI (SDL_Renderer *renderer, Game &game, character &player, character &enemy, Text &_time, Mix_Chunk *sound[2])
{
    if (enemy.in_fire)
        enemy.get_animation ("Attack2", enemy.frameMax, 4);
    else if (enemy.in_attack)
        enemy.get_animation ("Attack1", enemy.frameMax, 4);
    else if (enemy.in_fire == false && enemy.in_attack == false &&
             enemy.death == false && enemy.died == false)
    {
        if (!player.death)
        {
            if (!enemy.fire) can_AI_Fire (enemy, player, sound);
            if (enemy.fire)
            {
                enemy.frameCurrent = 0;
                enemy_fire (renderer, player, enemy);
            }
            if (!enemy.fire) AI_Move (player, enemy, sound);
        }

    }
    enemy.update (renderer);
}

void enemy_attack (character &player, character &enemy, Game &game)
{
    int offset_damage;
    if (game.mode == "easy") offset_damage = 4;
    else if (game.mode == "medium") offset_damage = 3;
    else if (game.mode == "hard") offset_damage = 2;

    if (enemy.lastKey == "right" && (enemy.attack == true || enemy.in_target == true))
    {
        if ((player.x + char_width/2) >= (enemy.x + char_width/2) &&
            (player.x + char_width/2) <= (enemy.x + char_width + attack_width[enemy.number]))
            player.health += normal_damage[enemy.number]/offset_damage;
        else if (enemy.in_target)
        {
            player.health += shoot_damage;
            enemy.in_target = false;
            enemy.fire = false;
            enemy.fire_x = enemy.x + char_width;
        }
    }
    else if (enemy.lastKey == "left" && (enemy.attack == true || enemy.in_target == true))
    {
        if ((player.x + char_width/2) <= (enemy.x + char_width/2) &&
            (player.x + char_width/2) >= (enemy.x - attack_width[enemy.number]))
            player.health += normal_damage[enemy.number]/offset_damage;
        else if (enemy.in_target)
        {
            player.health += shoot_damage;
            enemy.in_target = false;
            enemy.fire = false;
            enemy.fire_x = enemy.x;
        }
    }
    if (player.health >= 0)
    {
        player.health = 0;
        player.death = true;
    }
}
