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
    enum location{
        section1,
        section2,
        garden,
        section4
    };
    int keys;

    bool grounded;

};
struct keypiece{
    Vector2 pos;
    enum locationtype{
        inbush,
        inrock,
        inwater
    };
};

enum class screen {
    menu,
    tutorial,
    game,
    exit
}; 
extern screen current;
extern bool running;
