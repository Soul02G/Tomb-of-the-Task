#include "raylib.h"

int main() {

    int x = 900;
    int y = 450;



    int move_dir;
    int xspd = 0, yspd = 0;
    int move_spd = 30;
    const int screenWidth = 1800;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Tomb of The Mask");

    while (!WindowShouldClose()) {

        SetTargetFPS(120);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircle(x, y, 30, RED);

        DrawRectangle(0, 0, 30, 900, GRAY);
        DrawRectangle(1770, 0, 30, 900, GRAY);
        DrawRectangle(0, 0, 1800, 30, GRAY);
        DrawRectangle(0, 870, 1800, 30, GRAY);



        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) xspd = move_spd;
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))  xspd = -move_spd;
        if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) yspd = move_spd;
        if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))  yspd = -move_spd;


        //eje x
        if (x + 30 + xspd >= 1800 - 30) {
            x = (1800 - 30) - 30;
            xspd = 0;
        }

        else if (x - 30 + xspd <= 30) {
            x = 30 + 30;
            xspd = 0;
        }
        else {
            x += xspd;
        }
        //eje y
        if (y + 30 + yspd >= 900 - 30) {
            y = (900 - 30) - 30;
            yspd = 0;
        }

        else if (y - 30 + yspd <= 30) {
            y = 30 + 30;
            yspd = 0;
        }
        else {
            y += yspd;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}