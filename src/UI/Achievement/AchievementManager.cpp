//
// Created by Harry Skerritt on 10/07/2026.
//

#include "AchievementManager.h"
#include "../../AssetManager/AssetManager.h"

void AchievementManager::add(std::string title, ElementType type) {
    achievements.push_back({ title, type, 0.0f, 0.0f, 0 });
}

void AchievementManager::update(float dt) {
    for (int i = 0; i < achievements.size(); i++) {
        auto& ach = achievements[i];

        // Fade In
        if (ach.state == 0) {
            ach.alpha += dt * fadeTime;
            if (ach.alpha >= 1.0f) {
                ach.alpha = 1.0f;
                ach.state = 1;
            }
        }
        // Hold
        else if (ach.state == 1) {
            ach.timer += dt;
            if (ach.timer >= holdTime) {
                ach.state = 2;
            }
        }
        // Fade Out
        else if (ach.state == 2) {
            ach.alpha -= dt * fadeTime;
            if (ach.alpha <= 0.0f) {
                achievements.erase(achievements.begin() + i);
                i--;
            }
        }
    }
}

void AchievementManager::draw(Font font_header, Font font_body) {
    for (const auto& ach : achievements) {
        float width = 450.0f;
        float height = 75.0f;
        Vector2 pos = { (GetScreenWidth() - width) / 2.0f, 20.0f };

        // Background
        DrawRectangleRounded({pos.x, pos.y, width, height}, 0.4f, 20, Fade(BLACK, ach.alpha * 0.4f));

        auto icon = AssetManager::GetTexture("trophy-icon");
        DrawTexturePro(icon,
            {0, 0, static_cast<float>(icon.width), static_cast<float>(icon.height)},
            {pos.x + 10, pos.y + 10, 60, 60},
            {0, 0}, 0, Fade(WHITE, ach.alpha));

        DrawTextEx(font_header, "Goal Reached", {pos.x + 80, pos.y + 10}, 20, 2, Fade(WHITE, ach.alpha));
        DrawTextEx(font_body, ach.title.c_str(), {pos.x + 80, pos.y + 35}, 25, 2, Fade(getColourForType(ach.type), ach.alpha));
    }
}