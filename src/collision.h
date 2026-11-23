#pragma once
#include <bits/stdc++.h>
#include <raylib.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
extern std::vector<Rectangle> collision;
void loadcollisions(const json& map);

extern std::vector<Rectangle> terrain;
void loadtterrain(const json& map);
void loadboundaries();
