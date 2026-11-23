#include <raylib.h>
#include <string>

int main()
{
    InitWindow(800, 600, "texture");

    // GetApplicationDirectory() gives the exe's folder on both Windows and macOS,
    // and it already ends in a separator. No current_path(), no platform #ifdef.
    const std::string asset = std::string(GetApplicationDirectory()) + "assets/mapped2.png";
    Texture2D tex = LoadTexture(asset.c_str());

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawTexture(tex, 40, 40, WHITE);
            DrawText(asset.c_str(), 40, 560, 10, DARKGRAY);
        EndDrawing();
    }

    UnloadTexture(tex);
    CloseWindow();
}
