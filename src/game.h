#pragma once
#include <bits/stdc++.h>
#include "raylib.h"
struct player{
    Vector2 pos;
    Vector2 size;
    float speed;
    Color color;
    enum location{
        section1,
        section2,
        garden,
        section4
    };
    int keys = 0;

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
extern screen current = screen::menu;
extern bool running = true;
