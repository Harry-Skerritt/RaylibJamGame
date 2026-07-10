//
// Created by Harry Skerritt on 10/07/2026.
//

#include "Icon.h"
#include <string>

#include "../../AssetManager/AssetManager.h"

Icon::Icon() {}
Icon::~Icon() {}

void Icon::draw(Vector2 centre, const Texture2D &texture, const std::string &key, int amt, bool active) {
    float scale = 0.3f;
    Color fill = active ? WHITE : Fade(WHITE, 0.2f);
    auto key_font = AssetManager::GetFont("iceland-25");
    auto amt_font = AssetManager::GetFont("itim-25");

    Vector2 texture_pos = { centre.x - (texture.width * scale) / 2, centre.y- (texture.height * scale) / 2 };
    DrawTextureEx(texture, texture_pos , 0, scale, fill);

    const std::string key_str = "[" + key + "]";
    const auto key_dims = MeasureTextEx(key_font, key_str.c_str(), 25, 2);
    const Vector2 key_pos = { centre.x - key_dims.x / 2, centre.y + (texture.height * scale) / 2 + 5 };
    DrawTextEx(key_font, key_str.c_str(), key_pos, 25, 2, fill);

    const std::string amt_str = "x" + std::to_string(amt);
    const auto amt_dims = MeasureTextEx(amt_font, amt_str.c_str(), 25, 2);
    const Vector2 amt_pos = { centre.x + amt_dims.x / 2, centre.y + 8};

    if (amt >= 1)
        DrawTextEx(amt_font, amt_str.c_str(), amt_pos, 25, 2, fill);
}


