//
// Created by Harry Skerritt on 10/07/2026.
//

#include "FloatingTextManager.h"

void FloatingTextManager::add(std::string text, Vector2 pos) {
    texts.push_back({ text, pos });
}

void FloatingTextManager::update(float dt) {
    for (int i = 0; i < texts.size(); i++) {
        float up_speed = 30.0f * (i + 1);
        texts[i].pos.y -= up_speed * dt;
        texts[i].lifetime -= dt;
        texts[i].alpha = texts[i].lifetime;

        if (texts[i].lifetime <= 0.0f) {
            texts.erase(texts.begin() + i);
            i--;
        }
    }
}


void FloatingTextManager::draw(Font font) {
    for (const auto& ft : texts) {
        DrawTextEx(font, ft.text.c_str(), {ft.pos.x + 1, ft.pos.y + 1}, 25, 2, Fade(BLACK, ft.alpha * 0.5f));
        DrawTextEx(font, ft.text.c_str(), ft.pos, 25, 2, Fade(GOLD, ft.alpha));
    }
}

