#include "raylib.h"

#define TRAIL_LENGTH 15

int main() {

    const int screenWidth = 1800;
    const int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "Tomb of The Mask");
    SetTargetFPS(120);

    // Animación
    Texture2D frames[5];
    frames[0] = LoadTexture("resources\\totm.png");
    frames[1] = LoadTexture("resources\\totm_1.png");
    frames[2] = LoadTexture("resources\\totm_2.png");
    frames[3] = LoadTexture("resources\\totm_3.png");
    frames[4] = LoadTexture("resources\\totm_4.png");

    int animOrder[8] = { 0, 1, 0, 2, 3, 2, 0, 4 };
    int animFrame = 0;
    int animTimer = 0;
    int animSpeed = 10;

    Texture2D trail = LoadTexture("resources\\trail.png");

    SetTextureFilter(frames[0], TEXTURE_FILTER_POINT);
    SetTextureFilter(trail, TEXTURE_FILTER_POINT);

    int x = 30;
    int y = 30;

    int xspd = 0, yspd = 0;
    int move_spd = 30;
    float scale = 5.0f;

    int playerWidth = (int)(frames[0].width * scale);
    int playerHeight = (int)(frames[0].height * scale);

    Vector2 trailPositions[TRAIL_LENGTH];
    for (int i = 0; i < TRAIL_LENGTH; i++) {
        trailPositions[i] = (Vector2){ (float)x, (float)y };
    }

    while (!WindowShouldClose()) {

        // Movimiento
        if (xspd == 0 && yspd == 0)
        {
            if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) xspd = move_spd;
            else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) xspd = -move_spd;
            else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) yspd = move_spd;
            else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) yspd = -move_spd;
        }

        // Límites
        if (x + playerWidth + xspd >= screenWidth - 30) {
            x = screenWidth - 30 - playerWidth;
            xspd = 0;
        }
        else if (x + xspd <= 30) {
            x = 30;
            xspd = 0;
        }
        else {
            x += xspd;
        }

        if (y + playerHeight + yspd >= screenHeight - 30) {
            y = screenHeight - 30 - playerHeight;
            yspd = 0;
        }
        else if (y + yspd <= 30) {
            y = 30;
            yspd = 0;
        }
        else {
            y += yspd;
        }

        int isMoving = (xspd != 0 || yspd != 0);

        if (isMoving) {
            // Sin animación al moverse
            animFrame = 0;
            animTimer = 0;

            // Trail
            for (int i = TRAIL_LENGTH - 1; i > 0; i--) {
                trailPositions[i] = trailPositions[i - 1];
            }
            trailPositions[0] = (Vector2){ (float)x, (float)y };
        }
        else {
            // Animación idle cuando está quieto
            animTimer++;
            if (animTimer >= animSpeed) {
                animTimer = 0;
                animFrame = (animFrame + 1) % 8;
            }

            for (int i = 0; i < TRAIL_LENGTH; i++) {
                trailPositions[i] = (Vector2){ (float)x, (float)y };
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (isMoving) {
            for (int i = TRAIL_LENGTH - 1; i >= 0; i--) {
                float alpha = (float)(TRAIL_LENGTH - i) / (float)TRAIL_LENGTH;
                Color tint = (Color){ 255, 255, 255, (unsigned char)(255 * alpha) };
                DrawTextureEx(trail, trailPositions[i], 0.0f, scale, tint);
            }
        }

        // Jugador
        Texture2D current = frames[animOrder[animFrame]];
        DrawTextureEx(current, (Vector2) { (float)x, (float)y }, 0.0f, scale, WHITE);

        // Muros
        DrawRectangle(0, 0, 30, screenHeight, GRAY);
        DrawRectangle(screenWidth - 30, 0, 30, screenHeight, GRAY);
        DrawRectangle(0, 0, screenWidth, 30, GRAY);
        DrawRectangle(0, screenHeight - 30, screenWidth, 30, GRAY);

        EndDrawing();
    }

    for (int i = 0; i < 5; i++) UnloadTexture(frames[i]);
    UnloadTexture(trail);
    CloseWindow();
    return 0;
}