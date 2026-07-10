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

GameState* gameState = nullptr;

static const int screen_width = 720;
static const int screen_height = 720;
static RenderTexture2D target = { 0 };
static int frame_counter = 0;

static void UpdateDrawFrame(void);

int main() {
    InitWindow(screen_width, screen_height, "Atomic Synthesis");
    InitAudioDevice();
    target = LoadRenderTexture(screen_width, screen_height);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    // Load Fonts
    AssetManager::LoadFontKey("itim-40", "resources/fonts/Itim/Itim-Regular.ttf", 40);
    AssetManager::LoadFontKey("itim-30", "resources/fonts/Itim/Itim-Regular.ttf", 30);
    AssetManager::LoadFontKey("itim-25", "resources/fonts/Itim/Itim-Regular.ttf", 25);
    AssetManager::LoadFontKey("itim-20", "resources/fonts/Itim/Itim-Regular.ttf", 20);
    AssetManager::LoadFontKey("itim-15", "resources/fonts/Itim/Itim-Regular.ttf", 15);

    AssetManager::LoadFontKey("iceland-100", "resources/fonts/Iceland/Iceland-Regular.ttf", 100);
    AssetManager::LoadFontKey("iceland-80", "resources/fonts/Iceland/Iceland-Regular.ttf", 80);
    AssetManager::LoadFontKey("iceland-50", "resources/fonts/Iceland/Iceland-Regular.ttf", 50);
    AssetManager::LoadFontKey("iceland-40", "resources/fonts/Iceland/Iceland-Regular.ttf", 40);
    AssetManager::LoadFontKey("iceland-25", "resources/fonts/Iceland/Iceland-Regular.ttf", 25);

    // Load Textures
    AssetManager::LoadTextureKey("menu-title", "resources/menu/title.png");
    AssetManager::LoadTextureKey("atom", "resources/textures/atom.png");
    AssetManager::LoadTextureKey("small-btn", "resources/textures/small-btn-background.png");
    AssetManager::LoadTextureKey("sacrifice-icon", "resources/textures/sacrifice-icon.png");

    // Sounds
    AssetManager::LoadSoundKey("tile-place", "resources/sounds/tile_place.ogg");
    AssetManager::LoadSoundKey("tile-remove", "resources/sounds/tile_remove.ogg");
    AssetManager::LoadSoundKey("sacrifice-added", "resources/sounds/sacrifice_added.ogg");
    AssetManager::LoadSoundKey("merge", "resources/sounds/merge.ogg");
    AssetManager::LoadSoundKey("game-over", "resources/sounds/game_over.ogg");
    AssetManager::LoadSoundKey("btn-click", "resources/sounds/button.ogg");
    AssetManager::LoadSoundKey("game-start", "resources/sounds/game_start.ogg");
    AssetManager::LoadSoundKey("sacrifice-mode", "resources/sounds/sacrifice_mode.ogg");
    AssetManager::LoadSoundKey("game-win", "resources/sounds/game_win.ogg");
    AssetManager::LoadSoundKey("catalyst", "resources/sounds/catalyst.ogg");

    // Music
    AssetManager::LoadMusicKey("main-music", "resources/music/main-music.mp3");
    AssetManager::LoadMusicKey("menu-music", "resources/music/menu-music.mp3");


    gameState = new GameState();
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

    delete gameState;
    CloseAudioDevice();
    CloseWindow();
    AssetManager::UnloadAll();

    return 0;
}

void UpdateDrawFrame(void) {
    if (gameState == nullptr) return;
    frame_counter++;
    gameState->update();


    BeginTextureMode(target);
        ClearBackground(Colours::MAIN_BACKGROUND);
        gameState->draw();
    EndTextureMode();

    BeginDrawing();
        ClearBackground(Colours::MAIN_BACKGROUND);
        DrawTexturePro(target.texture,
        (Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height },
        (Rectangle){ 0, 0, (float)target.texture.width, (float)target.texture.height },
        (Vector2){ 0, 0 }, 0.0f, WHITE);


    // UI?

    gameState->drawUI();
    EndDrawing();
}
