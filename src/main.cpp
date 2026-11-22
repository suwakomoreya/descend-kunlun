#include <bits/stdc++.h>
#include "raylib.h"
#include "ui.h"
#include "game.h"
#include "collision.h"
#include "nlohmann/json.hpp"

int main(){
    InitWindow(900,900, "Descent");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    
    std::fstream file("assets/mapped.json");
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

                BeginMode2D(cammain);
                drawplayer(p1);
                followplayer(cammain,p1,screenwidth/2.0f);
                for(const auto& block : collision){
                    DrawRectangleLinesEx(block,1,RED);
                }
                EndMode2D();
        }
        
        DrawText("yoooohooo", 500,350,30, WHITE);
        
        
        EndDrawing();
        if(IsKeyPressed(KEY_Q)){
            running = false;
        }
    }
    CloseWindow();
}