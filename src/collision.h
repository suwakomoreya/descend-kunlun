#pragma once
#include <raylib.h>
#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
using json =nlohmann::json;
std::vector<Rectangle> collision;
void loadcollisions(const json&map){
    for(const auto& layer : map["layers"]){
        if()
    }
}