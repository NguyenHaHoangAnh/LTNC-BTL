#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <iostream>
#include "SDL_utils.h"

const double ground = 500;

const double jump_height = 17;
const double jump_step = 3;
const double attack_step = 1;
const double step = 7; // 20
const double gravity = 0.6;
const double attack_width[] = {0, 150, 150, 200, 100};

const double fire_width = 80; // fire
const double fire_step = 30;

const int health_bar_length = 500;
const int max_health = 500;

const int normal_damage[] = {0, 8, 5, 10, 9};
const int shoot_damage = 40;

const int AI_action [] = {0, 0, 1, 0, 0, 1, 0, 0, 1, 0};
const int AI_fire [] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0};

const int max_time = 20;

const double OFFSET_Y[] = {0,70, 70, 150, 70};

const double char_height = 150;
const double char_width = 150;
const double char_attack_height[] = {0, 220, 220, 310, 220};
const double char_attack_width[] = {0, 300, 300, 400, 330};
const double frame_h[] = {0, 200, 200, 162, 180};
const double frame_w[] = {0, 200, 200, 162, 180};
const double offset_x[] = {0,75, 75, 52, 70};
const double offset_y[] = {0,70, 70, 55, 60};
const double offset_attack_x[] = {0,75, 75, 25, 55};
const double offset_attack_y[] = {0, 40, 40, 0, 30};
const double offset_attack_w[] = {0, 120, 120, 130, 120};
const double offset_attack_h[] = {0, 85, 85, 105, 85};

struct character
{
    double x, y;
    double velocity_x;
    double velocity_y;
    double frame_width, frame_height;
    bool jump;
    bool key_left_pressed;
    bool key_right_pressed;
    string lastKey;
    string path;
    double attack_x, attack_y;
    bool attack;
    bool in_attack;

    int health;
    int health_bar_x, health_bar_y, health_bar_w;
    int health_bar_x2, health_bar_y2, health_bar_w2;

    // fire
    bool fire;
    double fire_x, fire_y;
    double fire_velocity;
    bool in_target;
    bool in_fire;
    string fire_path;

    bool death;
    bool died;

    int frameCurrent, frameMax;
    int frameElapsed, frameHold;

    int number;

    void get_animation (string action, int cframeMax, int cframeHold)
    {
        string num = to_string (number);
        path = "image//" + num + "_" + action + ".png";
        frameMax = cframeMax;
        frameHold = cframeHold;
    }

    void animation ()
    {
        frameElapsed++;
        if (frameElapsed % frameHold == 0)
        {
            if (frameCurrent < frameMax - 1)
                frameCurrent++;
            else
                frameCurrent = 0;
            if (in_attack)
            {
                if (frameCurrent == frameMax - 1)
                    in_attack = false;
            }
            else if (in_fire)
            {
                if (frameCurrent == frameMax - 1)
                    in_fire = false;
            }
            else if (death)
            {
                if (frameCurrent == frameMax - 1)
                {
                    died = true;
                }
            }
        }
    }

    void draw (SDL_Renderer *renderer)
    {
        SDL_Texture *player_img = loadTexture (path, renderer);
        SDL_Rect player;
        SDL_QueryTexture (player_img, NULL, NULL, &player.w, &player.h);
        int width = player.w;
        frameMax = player.w / frame_w[number];

        if (in_attack == false && in_fire == false &&
            death == false && died == false)
        {
            player.x = x;
            player.y = y;
            player.h = char_height;
            player.w = char_width;
        }
        else if ((in_attack == true || in_fire == true) && death == false)
        {
            if (lastKey == "right") player.x = x;
            if (lastKey == "left") player.x = x - char_width;
            player.y = y - OFFSET_Y[number];
            player.h = char_attack_height[number];
            player.w = char_attack_width[number];
        }
        else if (death == true || died == true)
        {
            player.x = x;
            player.y = y;
            player.h = char_height;
            player.w = char_width + 100;
        }

        SDL_Rect playerScr;
        if (in_attack == false && in_fire == false &&
            death == false && died == false)
        {
            playerScr.x = frameCurrent * frame_w[number] + offset_x[number];
            playerScr.y = offset_y[number];
            playerScr.w = frame_width;
            playerScr.h = frame_height;
        }
        else if ((in_attack == true || in_fire == true) && death == false)
        {
            playerScr.x = frameCurrent * frame_w[number] + offset_attack_x[number];
            playerScr.y = offset_attack_y[number];
            playerScr.w = offset_attack_w[number];
            playerScr.h = offset_attack_h[number];
        }
        else if (death == true || died == true)
        {
            playerScr.x = frameCurrent * frame_w[number] + offset_x[number];
            playerScr.y = offset_y[number];
            playerScr.w = frame_width + 50;
            playerScr.h = frame_height;
        }

        SDL_RendererFlip flip;
        if (lastKey == "right")
            flip = SDL_FLIP_NONE;
        else if (lastKey == "left")
            flip = SDL_FLIP_HORIZONTAL;
        SDL_RenderCopyEx (renderer, player_img, &playerScr, &player, NULL, NULL, flip);
    }

    void update (SDL_Renderer *renderer)
    {
        if (jump)
        {
            if (key_left_pressed == true && lastKey == "left")
                velocity_x = -jump_step;
            else if (key_right_pressed == true && lastKey == "right")
                velocity_x = jump_step;
        }
        else
        {
            if (key_left_pressed == true && lastKey == "left")
                velocity_x = -step;
            else if (key_right_pressed == true && lastKey == "right")
                velocity_x = step;
        }

        if (attack)
        {
            if (lastKey == "left")
                x -= attack_step;
            else if (lastKey == "right")
                x += attack_step;
        }
        else
        {
            if (key_left_pressed == false && key_right_pressed == false) velocity_x = 0;
        }

        if ((key_left_pressed == true || attack == true) && (x < -(char_width) || (x - char_width) < -(char_width)))
        {
            velocity_x = 0;
            if (attack) x += attack_step;
        }
        if ((key_right_pressed == true || attack == true) && (x > SCREEN_WIDTH || (x + char_width) > SCREEN_WIDTH))
        {
            velocity_x = 0;
            if (attack) x -= attack_step;
        }

        x += velocity_x;
        attack_x += velocity_x;
        y += velocity_y;
        // fall
        if (y + char_height + velocity_y >= ground)
            velocity_y = 0;
        else
            velocity_y += gravity;

        draw (renderer);
        animation ();

    }

    void health_bar (SDL_Renderer *renderer)
    {
        SDL_Rect bar_2;
        bar_2.x = health_bar_x2;
        bar_2.y = health_bar_y2;
        bar_2.h = 44;
        bar_2.w = health_bar_w2;
        SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);//white
        SDL_RenderFillRect (renderer, &bar_2);

        SDL_Rect bar;
        bar.x = health_bar_x;
        bar.y = health_bar_y;
        bar.h = 40;
        bar.w = health_bar_w;
        SDL_SetRenderDrawColor (renderer, 0, 0, 0, 0);//black
        SDL_RenderFillRect (renderer, &bar);

        SDL_Rect hp;
        hp.x = health_bar_x;
        hp.y = health_bar_y;
        hp.h = 40;
        hp.w = health;
        SDL_SetRenderDrawColor (renderer, 255, 0, 0, 255);//red
        SDL_RenderFillRect (renderer, &hp);
    }

    void draw_fire (SDL_Renderer *renderer)
    {
        if (lastKey == "right") fire_path = "image//fire_right.jpg";
        else if (lastKey == "left") fire_path = "image//fire_left.jpg";
        SDL_Texture *fire_img = loadTexture (fire_path, renderer);
        SDL_Rect fire;
        SDL_QueryTexture (fire_img, NULL, NULL, &fire.w, &fire.h);
        fire.x = fire_x;
        fire.y = fire_y;
        fire.h = 30;
        fire.w = fire_width;
        SDL_RenderCopy (renderer, fire_img, NULL, &fire);
    }

    void fire_update (SDL_Renderer *renderer)
    {
        if (fire)
            fire_x += fire_velocity;
        draw_fire (renderer);
    }

};

#endif // CHARACTER_H_
