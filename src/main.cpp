//
// Created by Harry Skerritt on 06/07/2026.
//
#include "raylib.h"
#include "AssetManager/AssetManager.h"
#include "GameState/GameState.h"
#include "UI/Hotbar/Hotbar.h"
#include "utils/Colours.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>      // Emscripten library
#endif

GameState gameState;

static const int screen_width = 720;
static const int screen_height = 720;
static RenderTexture2D target = { 0 };
static int frame_counter = 0;

static void UpdateDrawFrame(void);

int main() {
    InitWindow(screen_width, screen_height, "Atomic Synthesis");
    target = LoadRenderTexture(screen_width, screen_height);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    AssetManager::LoadFontKey("itim-40", "resources/fonts/Itim/Itim-Regular.ttf", 40);
    AssetManager::LoadFontKey("itim-25", "resources/fonts/Itim/Itim-Regular.ttf", 25);
    AssetManager::LoadFontKey("itim-20", "resources/fonts/Itim/Itim-Regular.ttf", 20);

    // For WASM
#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    // For Desktop
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
#endif

    UnloadRenderTexture(target);
    CloseWindow();
    AssetManager::UnloadAll();
    return 0;
}

void UpdateDrawFrame(void) {
    frame_counter++;
    gameState.update();


    BeginTextureMode(target);
        ClearBackground(Colours::MAIN_BACKGROUND);
        gameState.draw();
    EndTextureMode();

    BeginDrawing();
        ClearBackground(Colours::MAIN_BACKGROUND);
        DrawTexturePro(target.texture,
        (Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height },
        (Rectangle){ 0, 0, (float)target.texture.width, (float)target.texture.height },
        (Vector2){ 0, 0 }, 0.0f, WHITE);


    // UI?

    gameState.drawUI();
    EndDrawing();
}
