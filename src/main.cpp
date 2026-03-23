#include "raylib.h"
#include "scenes.h"
#include "game.h"
#include "menu.h"

int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tomb of The Mask");
    SetTargetFPS(120);
    SetAudioStreamBufferSizeDefault(2048);  // Reduce delay de audio
    InitAudioDevice();

    GameState gameState = { 0 };
    MenuState menuState = { 0 };

    // El juego arranca en el menú principal
    Scene currentScene = SCENE_MENU;
    MenuLoad(&menuState);

    while (!WindowShouldClose()) {

        // Dibuja PRIMERO (para que el último frame del zoom se vea antes de cambiar)
        BeginDrawing();
        switch (currentScene) {
        case SCENE_MENU: MenuDraw(&menuState, SCREEN_WIDTH, SCREEN_HEIGHT); break;
        case SCENE_GAME: GameDraw(&gameState);                              break;
        }
        EndDrawing();

        // Luego actualiza y gestiona cambios de escena
        Scene nextScene = currentScene;
        switch (currentScene) {
        case SCENE_MENU: nextScene = MenuUpdate(&menuState); break;
        case SCENE_GAME: nextScene = GameUpdate(&gameState); break;
        }

        if (nextScene != currentScene) {
            switch (currentScene) {
            case SCENE_MENU: MenuUnload(&menuState); break;
            case SCENE_GAME: GameUnload(&gameState); break;
            }
            switch (nextScene) {
            case SCENE_MENU: MenuLoad(&menuState);   break;
            case SCENE_GAME: GameLoad(&gameState);   break;
            }
            currentScene = nextScene;
        }
    }

    // Limpieza al salir
    switch (currentScene) {
    case SCENE_MENU: MenuUnload(&menuState); break;
    case SCENE_GAME: GameUnload(&gameState); break;
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}