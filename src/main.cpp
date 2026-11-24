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
float gametimerun = 0.0f;

float menucameray(){
    float miny = std::numeric_limits<float>::max();
    float maxy = std::numeric_limits<float>::lowest();
    for(const auto& gate : gate2){
        miny = std::min(miny, gate.y);
        maxy = std::max(maxy, gate.y + gate.height);
    }
    if(miny > maxy){
        return 450.0f;
    }
    return std::clamp((miny + maxy)/2.0f, 450.0f, 2688.0f - 450.0f);
}

void resetgame(player& p, const json& level){
    p = createplayer(playerstartx, playerstarty);
    resetkeys(level);
    gametimerun = 0.0f;
    messagetime = 0;
    messagestarted = false;
}

int main(){
    InitWindow(900,900, "Descent");
    map = LoadTexture(mappathz.c_str());
    terrained = LoadTexture(terrains.c_str());
    gated1 = LoadTexture(gates1.c_str());
    gated2 = LoadTexture(gates2.c_str());
    keysz = LoadTexture(keyimg.c_str());
    kreskart = LoadTexture(kreskapath.c_str());
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    
    cammain.target = {450,450};
    cammain.offset =  {450,450};
    cammain.rotation = 0.0f;
    cammain.zoom = 1.0f;
    int screenwidth = GetScreenWidth();
    int screenheight = GetScreenHeight();
    player p1 = createplayer(playerstartx, playerstarty);
    
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
    cammain.target = {450.0f, menucameray()};
    while(!WindowShouldClose() && running){
        if(current == screen::menu){
            float desired = menucameray();
            cammain.target.y += (desired - cammain.target.y) * 5.0f * GetFrameTime();
            menuui(p1);
        }
        else if(current == screen::tutorial && IsKeyPressed(KEY_ESCAPE)){
            current = screen::menu;
            resetgame(p1, map);
        }
        else if(current == screen::gameover && IsKeyPressed(KEY_ESCAPE)){
            current = screen::menu;
            resetgame(p1, map);
        }

        BeginDrawing();
        BeginMode2D(cammain);
        ClearBackground(BLACK);
        // remove these after release, its just for testing.
        drawbg();
        drawcollide();
        drawterrain();
        drawkeys();
        if(p1.keys < 3){
            drawgate1();
        }
        if(p1.keys<5){
            drawgate2();
        }
        switch(current){
            case screen::menu:
                break;
            case screen::game:
                
                gametimerun += GetFrameTime();
                updatepphysics(p1,GetFrameTime());
                followplayer(cammain,p1,screenwidth/2.0f);
                checkpoint(p1);
                drawplayer(p1);
                for(const auto& block : collision){
                    DrawRectangleLinesEx(block,0,WHITE);
                }
                for(const auto& block : terrain){
                    DrawRectangleLinesEx(block,0,LIGHTGRAY);
                }

                for(const auto& block : spikes){
                    DrawRectangleLinesEx(block,0,RED);
                }
                for(const auto& key : keys){
                    DrawRectangleLinesEx(key,0, GOLD);
                }
                if(p1.keys<3){
                    for(const auto& block : gate1){
                        DrawRectangleLinesEx(block,0,BROWN);
                    }
                }
                if(p1.keys < 5){
                    for(const auto& block : gate2){
                        DrawRectangleLinesEx(block,0,DARKBROWN);
                    }
                }
               
                
                if(IsKeyPressed(KEY_ESCAPE)){
                    current = screen::menu;
                    resetgame(p1, map);
                }
                
                break;
            case screen::gameover:
                break;
            case screen::tutorial:
                break;
            case screen::exit:
                running = false;
            
        }
        
        EndMode2D();

        if(current == screen::menu){
            drawmenuui();
        }
        if(current == screen::tutorial){
            tutorialscreen();
        }
        if(current == screen::game){
            testmode(p1);
        }
        if(current == screen::gameover){
            gameoverscreen(p1);
        }
        DrawText("yoooohooo", 500,350,30, WHITE);

        if(p1.keycollected == true){
            if(!messagestarted){
                messagetime =GetTime();
                messagestarted = true;
            }
          
            if(GetTime() - messagetime < 5.0){
                DrawText(TextFormat("Keys collected: %i/5", p1.keys),screenwidth/2-200,100,45,RED);
            }
            else{
                p1.keycollected = false;
                messagestarted = false;
            }
        }
        EndDrawing();
       
        
    }
    CloseWindow();
}