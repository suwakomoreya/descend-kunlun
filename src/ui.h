#pragma once
#include <bits/stdc++.h>
#include "raylib.h"
#include "game.h"
#include "nlohmann/json.hpp"
const int screenwidth = GetScreenWidth();
const int screenheight = GetScreenHeight();
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
    const float trigger = 400;
    const float smooth = 3.0f;
    float playerY = p.pos.y + p.size.y/2;

    float desired = playerY + (screenheight/2.0f-trigger);
    if(desired>screenheight/2.0f){
        desired = screenheight/2.0f;
    }
    cam.target.y += (desired-cam.target.y)*smooth*GetFrameTime();
    cam.target.x = lanecenterX;
}