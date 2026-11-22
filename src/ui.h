#pragma once
#include <bits/stdc++.h>
#include "raylib.h"
#include "game.h"
#include "nlohmann/json.hpp"
#include "collision.h"

using json = nlohmann::json;
//ui
// void drawbg (youre gonna use a 1800x7200 image bro split dat into 4 later so u can render it teh same way you did for bouldering)

Camera2D cammain = {0};

const int count = 3;
int selected =0;
const char*items[] ={
    "Descend",
    "Tutorial",
    "Exit"
};
void menuui(){

    if(IsKeyPressed(KEY_S)){
        selected = (selected+1)% count;
    }
    if(IsKeyPressed(KEY_W)){
        selected = (selected-1+count)% count;
    }
    if(IsKeyPressed(KEY_ENTER)){
        if(selected==0){
            current = screen::game;
        }
        if(selected==1){
            current = screen::tutorial;
        }
        if(selected==2){
            running = false;
        }
    }
}

void drawmenuui(){
    DrawText("Descent to Immortality", 40,150 ,50,WHITE);
    for(int i =0;i<count;i++){
        int x = 70;
        int y = 220 + i*70;
        Color c = (i==selected) ? WHITE : YELLOW;
        
        if(i==selected){
            DrawText(">",x-36,y,35,WHITE);
        }
        DrawText(items[i],x,y,35,c);
    }
}
player createplayer(float x, float y){
    player p;
    p.pos = {x,y};
    p.speed = 40;
    p.keys = 0;
    return p;
}

void drawplayer(const player&p){
    DrawRectangleV(p.pos,p.size,p.color);
}
void followplayer(Camera2D& cam, const  player&p, float lanecenterX){
    
    float playery = p.pos.y + p.size.y /2.0f;
    float desired = std::max(playery,450.0f);

    desired = std::min(desired,2688.0f-450.0f);
    float smooth = 5.0f;
    cam.target.y += (desired - cam.target.y) *smooth *GetFrameTime();
    cam.target.x = lanecenterX;
}
void updatepphysics(player&p, float groundy, float dt){

    const float gravity = 700.0f;
    const float jumpimpulse =500.0f;
    const float movespeed = 100.0f;
    
    p.vel.x =0.0f; // leftrighties
    if(IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)){
        p.vel.x = -movespeed;
    }
    if(IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)){
        p.vel.x = movespeed;
    }

    if((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))&& p.grounded){
        p.vel.y = -jumpimpulse;
        p.grounded = false;
    }
    // cut dat jump on release
    if((IsKeyReleased(KEY_SPACE) || IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_W))&& p.vel.y < 0.0f){
        p.vel.y *= 0.5f;
    }

    //gravity bro its gravity
    p.vel.y +=gravity*dt; // velocity (you know itd probably be 9.8 for my gravity? )

    p.vel.x += p.vel.x * dt; 

    Rectangle playerbounds = {
        p.pos.x,p.pos.y,p.size.x,p.size.y
    }; // this type of movement is my first, raylibs examplication
    for(const auto& block : collision){
        if(CheckCollisionRecs(playerbounds,block)){
            if(p.vel.x > 0){
                p.pos.x = block.x - p.size.x;

            }
            else if(p.vel.x<0){
                p.pos.x = block.x + block.width;
            }
            playerbounds.x = p.pos.x;
        }
    }

    p.pos.y += p.vel.y *dt;

    p.grounded = false;

    playerbounds = {p.pos.x,p.pos.y,
        p.size.x,p.size.y};

    for(const auto& block : collision){
        if(CheckCollisionRecs(playerbounds,block)){
            if(p.vel.y>0){
                //fall
                p.pos.y = block.y-p.size.y;
                p.grounded = true;
            }   //collisionals
            else if(p.vel.y<0){
                p.pos.y = block.y + block.height;
            }
            p.vel.y=0;
            playerbounds.y = p.pos.y;
        }
    }

}
void tutorialscreen(){
    DrawText("How to Play", 40,150,50,WHITE);
    DrawRectangle(GetScreenWidth()/2-350,GetScreenHeight()/2-200,700,400,WHITE);
    DrawText("")
}

