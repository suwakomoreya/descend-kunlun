#pragma once
#include <bits/stdc++.h>
#include "raylib.h"
#include "collision.h"
#include "nlohmann/json.hpp"
struct player{
    Vector2 pos;
    Vector2 vel;
    Vector2 size ={50,50};
    float speed;
    Color color = WHITE;
    enum class checkpoint{
        section1,
        section2,
        garden,
        section4
    };
    checkpoint Checkpoint = checkpoint::section1;
    int keys;
    int deathcount;
    bool dead;
    bool grounded;
    bool keycollected;

};
struct keypiece{
    Vector2 pos;
    
};

enum class screen {
    menu,
    tutorial,
    game,
    exit
}; 
extern screen current;
extern bool running;
