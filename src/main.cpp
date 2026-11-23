#include "bits/stdc++.h"
#include "raylib.h"
#include "ui.h"
#include "game.h"
#include "collision.h"
#include "collision.h"
#include "nlohmann/json.hpp"

screen current = screen::menu;
bool running = true;
double messagetime = 0;
bool messagestarted = false;

int main(){
    InitWindow(900,900, "Descent");
    map = LoadTexture(mappathz.c_str());
    terrained = LoadTexture(terrains.c_str());
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    
    cammain.target = {450,450};
    cammain.offset =  {450,450};
    cammain.rotation = 0.0f;
    cammain.zoom = 1.0f;
    int screenwidth = GetScreenWidth();
    int screenheight = GetScreenHeight();
    player p1 = createplayer(50,50);
    p1.keys = 0;
    
    std::fstream file(std::string(GetApplicationDirectory()) + "assets/mapped2.json");
    if(!file.is_open()){
            std::cerr << "failed to init map";
            return 1;
    }
    json map;
    file >>map;
    loadcollisions(map);
    loadboundaries();
    loadtterrain(map);
    loadspikes(map);
    loadkeys(map);
    loadgate1(map);
    loadgate2(map);
    while(!WindowShouldClose() && running){
        if(current == screen::menu){
            menuui(p1);
        }

        BeginDrawing();
        BeginMode2D(cammain);
        ClearBackground(BLACK);
        // remove these after release, its just for testing.
        drawcollide();
   
        switch(current){
            case screen::menu:
                drawmenuui();
                break;
            case screen::game:
                
                updatepphysics(p1,GetFrameTime());
                followplayer(cammain,p1,screenwidth/2.0f);
                checkpoint(p1);
                drawplayer(p1);
                drawterrain();
                for(const auto& block : collision){
                    DrawRectangleLinesEx(block,1,WHITE);
                }
                for(const auto& block : terrain){
                    DrawRectangleLinesEx(block,1,LIGHTGRAY);
                }

                for(const auto& block : spikes){
                    DrawRectangleLinesEx(block,1,RED);
                }
                for(const auto& key : keys){
                    DrawRectangleLinesEx(key,1, GOLD);
                }
                for(const auto& block : gate1){
                    DrawRectangleLinesEx(block,1,BROWN);
                }
                for(const auto& block : gate2){
                    DrawRectangleLinesEx(block,1,DARKBROWN);
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
        EndMode2D();
        testmode(p1);
        if(p1.keycollected == true){
            if(!messagestarted){
                messagetime =GetTime();
                messagestarted = true;
            }
          
            if(GetTime() - messagetime < 5.0){
                DrawText(TextFormat("Jades collected: %i/5", p1.keys),screenwidth/2-200,100,45,RED);
            }
            else{
                p1.keycollected = false;
                messagestarted = false;
            }
        }
        EndDrawing();
       
        if(IsKeyPressed(KEY_Q)){
            running = false;
        }
    }
    CloseWindow();
}