#pragma once
#include <bits/stdc++.h>
#include "raylib.h"
#include "game.h"
const int screenwidth = GetScreenWidth();
const int screenheight = GetScreenHeight();

//ui
// void drawbg (youre gonna use a 1800x7200 image bro split dat into 4 later so u can render it teh same way you did for bouldering)



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

void createplayer(float x, float y){
    player p;
    p.pos = {x,y};
    p.speed = 40;
    p.keys = 0;
    
}