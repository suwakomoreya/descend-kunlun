#include <bits/stdc++.h>
#include "raylib.h"
#include "ui.h"
#include "game.h"

int main(){
    InitWindow(900,900, "Descent");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

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
        }
        DrawText("yoooohooo", 500,350,30, WHITE);
        
        
        EndDrawing();
        if(IsKeyPressed(KEY_Q)){
            running = false;
        }
    }
    CloseWindow();
}