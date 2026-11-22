#include <raylib.h>
#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
using json =nlohmann::json;
extern std::vector<Rectangle> collision;
std::vector<Rectangle> collision;

extern std::vector<Rectangle> terrain
void loadcollisions(const json&map){
    for(const auto& layer : map["layers"]){
        if(layer["name"] != "collide"){
            continue;
        }
        int width = layer["width"];
        int tilewidth = map["tilewidth"];
        int tilehiehgt = map["tileheight"];
        const auto& data = layer ["data"];
        for(int i=0;i<data.size();i++){
            if (data[i]==0)
                continue;
            int x = (i%width) * tilewidth;
            int y = (i/width)*tilehiehgt;
            collision.push_back({(float)x,(float)y,(float)tilewidth,(float)tilehiehgt});
        } 
        // collisions using the json, every piece of data is on the "collide" funct
        return;
    }
}
