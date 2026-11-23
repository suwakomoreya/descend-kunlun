#include <bits/stdc++.h>
#include "raylib.h"
#include "ui.h"
#include "game.h"
#include "collision.h"
#include "collision.h"
#include "nlohmann/json.hpp"

screen current = screen::menu;
bool running = true;


int main(){
    InitWindow(900,900, "Descent");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    
    cammain.target = {450,75};
    cammain.offset =  {450,450};
    cammain.rotation = 0.0f;
    cammain.zoom = 1.0f;
    int screenwidth = GetScreenWidth();
    int screenheight = GetScreenHeight();

    std::fstream file("assets/mapped2.json");
    if(!file.is_open()){
            std::cerr << "failed to init map";
            return 1;
    }
    json map;
    file >>map;
    loadcollisions(map);
    loadboundaries();
    loadtterrain(map);
    player p1 = createplayer(50,50);
    while(!WindowShouldClose() && running){
        if(current == screen::menu){
            menuui(p1);
        }

        BeginDrawing();
        ClearBackground(BLACK);
        // remove these after release, its just for testing.
        testmode(p1);
        drawcollide();
        switch(current){
            case screen::menu:
                drawmenuui();
                break;
            case screen::game:
                updatepphysics(p1,GetFrameTime());
                followplayer(cammain,p1,screenwidth/2.0f);
                BeginMode2D(cammain);
                drawplayer(p1);
                for(const auto& block : collision){
                    DrawRectangleLinesEx(block,1,RED);
                }
                for(const auto& block : terrain){
                    DrawRectangleLinesEx(block,1,LIGHTGRAY);
                }
                EndMode2D();
                if(IsKeyPressed(KEY_ESCAPE)){
                    current = screen::menu;
                }
                
                break;
            case screen::tutorial:
                tutorialscreen();
                break;
            case screen::exit:
                running = false;
            
        }
        
        DrawText("yoooohooo", 500,350,30, WHITE);
        
        
        EndDrawing();
        if(IsKeyPressed(KEY_Q)){
            running = false;
        }
    }
    CloseWindow();
}