//
// Created by Harry Skerritt on 07/07/2026.
//

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include "raylib.h"
#include <map>
#include <string>

class AssetManager {
private:
    static std::map<std::string, Font> fonts;
    static std::map<std::string, Texture> textures;

public:
    // Fonts
    static void LoadFontKey(std::string key, const char* path, int font_size) {
        fonts[key] = LoadFontEx(path, font_size, nullptr, 0);
        SetTextureFilter(fonts[key].texture, TEXTURE_FILTER_BILINEAR);
    }

    static Font& GetFont(std::string key) {
        return fonts[key];
    }

    // Textures
    static void LoadTextureKey(std::string key, const char* path) {
        textures[key] = LoadTexture(path);
    }

    static Texture& GetTexture(std::string key) {
        return textures[key];
    }


    static void UnloadAll() {
        for (auto& pair : fonts) {
            UnloadFont(pair.second);
        }
        fonts.clear();

        for (auto& pair : textures) {
            UnloadTexture(pair.second);
        }
        textures.clear();
    }
};



#endif //ASSETMANAGER_H
