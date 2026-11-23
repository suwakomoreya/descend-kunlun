#pragma once
#include "bits/stdc++.h"
#include "raylib.h"
#include "game.h"
#include "nlohmann/json.hpp"
#include "collision.h"

using json = nlohmann::json;
//ui
// void drawbg (youre gonna use a 1800x7200 image bro split dat into 4 later so u can render it teh same way you did for bouldering)
std::string mappathz = std::string(GetApplicationDirectory()) + "assets/mapped2.png";
std::string terrains = std::string(GetApplicationDirectory()) + "assets/terrains.png";

Camera2D cammain = {0};
Texture2D map;
Texture2D terrained;
const int count = 3;
int selected =0;
const char*items[] ={
    "Descend",
    "Tutorial",
    "Exit"
};
void menuui(player&p){

    if(IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)){
        selected = (selected+1)% count;
    }
    if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
        selected = (selected-1+count)% count;
    }
    if(IsKeyPressed(KEY_ENTER)){
        if(selected==0){
            current = screen::game;
            p.pos.x = 393.0f;
            p.pos.y = 526.0f;
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
    Rectangle playerblock = {p.pos.x,p.pos.y,p.size.x,p.size.y};
    DrawRectangleLinesEx(playerblock,3.0f,RED);
}
void followplayer(Camera2D& cam, const  player&p, float lanecenterX){
    
    float playery = p.pos.y + p.size.y /2.0f;
    float desired = std::max(playery,450.0f);

    desired = std::min(desired,2688.0f-450.0f);
    float smooth = 5.0f;
    cam.target.y += (desired - cam.target.y) *smooth *GetFrameTime();
    cam.target.x = lanecenterX;
}
void updatepphysics(player&p, float dt){

    const float gravity = 700.0f;
    const float jumpimpulse =450.0f;
    const float movespeed = 250.0f;
    
    p.vel.x = 0.0f; // leftrighties
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)){
        p.vel.x = -movespeed;
    }
    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){
        p.vel.x = movespeed;
    }

    if((IsKeyPressed(KEY_UP)|| IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W)) && p.grounded){
        p.vel.y = -jumpimpulse;
        p.grounded = false;
    }
    // cut dat jump on release
    if((IsKeyReleased(KEY_SPACE) || IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_W))&& p.vel.y < 0.0f){
        p.vel.y *= 0.5f;
    }

    //gravity bro its gravity
    p.vel.y +=gravity*dt; // velocity (you know itd probably be 9.8 for my gravity? )

    p.pos.x += p.vel.x * dt; 

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
            if(p.vel.x > 0){
                p.pos.x = block.x - p.size.x;

            }
            else if (p.vel.x<0){
                p.pos.x = block.x + block.width;
            }
            playerbounds.x = p.pos.x;
        }
    }
    for(const auto& block : gate1){
        if(p.keys<3){
            if(CheckCollisionRecs(playerbounds,block)){
                if(p.vel.y>0){
                    p.pos.y = block.y-p.size.y;
                    p.grounded = true;
                }
                else if(p.vel.y<0){
                    p.pos.y = block.y + block.height;
                }
                p.vel.y=0;
                playerbounds.y=p.pos.y;
            }
        }
    }
    for(const auto& block : spikes){
        if(CheckCollisionRecs(playerbounds,block)){
            p.dead = true;
            if(p.Checkpoint == player::checkpoint::section1){
                p.pos.x = 450.0f;
                p.pos.y = 450.0f;
            }
            else if(p.Checkpoint == player::checkpoint::garden){
                p.pos.x = 322.0f;
                p.pos.y = 1358.0f;
            }
            else if(p.Checkpoint == player::checkpoint::section2){
                p.pos.x = 390.0f;
                p.pos.y = 1806.0f;
            }
            p.deathcount++;
            p.dead = false;
        }
    }
    for(auto it = keys.begin(); it !=keys.end();){
        if(CheckCollisionRecs(playerbounds,*it)){
            p.keys++;
            it = keys.erase(it);
            p.keycollected = true;
        }
        else{
            ++it;
        }
    }
}

void tutorialscreen(){
    DrawText("How to Play", 40,150,50,WHITE);
    DrawRectangle(GetScreenWidth()/2-350,GetScreenHeight()/2-200,700,400,WHITE);
    DrawText("A-D or LEFT RIGHT on the arrow keys",GetScreenWidth()/2-300,450,20,BLACK);
    DrawText("Space or UP to Jump",GetScreenHeight()/2-300,500,20,BLACK);
    if(IsKeyPressed(KEY_ESCAPE)){
        current = screen::menu;
    }
}

void testmode(player&p){
    float playerx = p.pos.x;
    float playery= p.pos.y;
    float velx = p.vel.x;
    float vely = p.vel.y;
    Color c;
    if(p.keys == 5){
        c = GREEN;
    }
    else c = RED;
    // DrawText(TextFormat("pos: %f,%f", playerx,playery),500,40,30,GREEN);
    // DrawText(TextFormat("vel: %f,%f",velx,vely),500,90,30,GREEN);
    DrawText(TextFormat("Keys: %i", p.keys),50,40,30,c);
}
void checkpoint(player&p){
    if(p.pos.y < 974.0f){
        p.Checkpoint = player::checkpoint::section1;
    }
    else if(p.pos.y >974.0f && p.pos.y < 1550.0f){
        p.Checkpoint = player::checkpoint::garden;
    }
    else if(p.pos.y > 1550.0f){
        p.Checkpoint = player::checkpoint::section2;
    }
}
void drawcollide(){
    DrawTexture(map,0,0,WHITE);
}
void drawterrain(){
    DrawTexture(terrained,0,0,WHITE);
}

void gameoverscreen(player&p){
    
}