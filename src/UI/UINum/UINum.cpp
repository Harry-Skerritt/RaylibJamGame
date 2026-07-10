//
// Created by Harry Skerritt on 10/07/2026.
//

#include "UINum.h"
#include "../../AssetManager/AssetManager.h"
#include "../../utils/Colours.h"

void UINum::draw(Vector2 pos, Vector2 size, int score, int max_atomic_num) {
    // Draw UI Box
    Rectangle hud_bg = { pos.x, pos.y, size.x, size.y };
    DrawRectangleRounded(hud_bg, 0.1f, 10, Fade(BLACK, 0.4f));
    DrawRectangleRoundedLines(hud_bg, 0.1f, 10, Fade(GRAY, 0.5f));

    auto ui_font = AssetManager::GetFont("itim-25");
    float start_x = hud_bg.x + 15;
    float current_y = hud_bg.y + 10;

    auto drawLine = [&](const std::string& label, const std::string& value, Color color) {
        DrawTextEx(ui_font, label.c_str(), { start_x, current_y }, 25, 2, Colours::WHITE_TEXT);
        DrawTextEx(ui_font, value.c_str(), { start_x + 160, current_y }, 25, 2, color);
        current_y += 30;
    };

    drawLine("Score:", std::to_string(score), Colours::MAIN_CYAN);
    drawLine("Max Atomic:", std::to_string(max_atomic_num), GOLD);


}

