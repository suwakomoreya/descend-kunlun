#include <bits/stdc++.h>
#include "raylib.h"
#include "ui.h"
#include "game.h"
#include "collision.h"
#include "nlohmann/json.hpp"

screen current = screen::menu;
bool running = true;


int main(){
    InitWindow(900,900, "Descent");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    

    int screenwidth = GetScreenWidth();
    int screenheight = GetScreenHeight();

    std::fstream file("assets/mapped.json");
    if(!file.is_open()){
            std::cerr << "failed to init map";
            return 1;
    }
    json map;
    file >>map;
    loadcollisions(map);

    player p1 = createplayer(50,50);
    while(!WindowShouldClose() && running){
        if(current == screen::menu){
            menuui();
        }

        BeginDrawing();
        ClearBackground(BLACK);
        
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
                EndMode2D();
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