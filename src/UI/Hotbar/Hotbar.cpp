//
// Created by harryskerritt on 07/07/2026.
//

#include "Hotbar.h"

#include <iostream>
#include <__ostream/basic_ostream.h>

#include "../../utils/Colours.h"
#include "../../utils/Element.h"

void Hotbar::drawHotbar() const {
    constexpr float slot_size = 80;
    constexpr float h_slot_size = slot_size / 2.0f;
    constexpr int slot_gap = 20;

    constexpr int slot_count = 3;
    constexpr int background_padding_x = 20;
    constexpr int background_padding_y = 40;

    constexpr float hotbar_width = slot_count * (slot_size + slot_gap) - slot_gap;
    const float start_x = static_cast<float>(GetScreenWidth()) - hotbar_width - background_padding_x;
    const float start_y = static_cast<float>(GetScreenHeight()) - slot_size - 20;

    Rectangle background_rect = {
        static_cast<float>(start_x) - (background_padding_x / 2.0f),
        static_cast<float>(start_y) - (background_padding_y * 0.75f),
        static_cast<float>(hotbar_width) + background_padding_x,
        static_cast<float>(slot_size) + background_padding_y,
    };

    DrawRectangleRounded(background_rect, 0.2f, 20, Fade(BLACK, 0.2f));

    DrawText("Next Elements",
        static_cast<int>(start_x - (background_padding_x / 2.0f) + 10),
        static_cast<int>(start_y - (background_padding_y * 0.75f) + 5), 20, RAYWHITE);

    for (int i = 0; i < slot_count; i++) {
        const float local_x = start_x + i * (slot_size + slot_gap);
        const float local_y = start_y;

        const Rectangle slot_rect = {
            local_x,
            local_y,
            slot_size,
            slot_size
        };

        Color fill = (slots[i].is_occupied) ? DARKGRAY : Fade(BLACK, 0.1f);
        DrawRectangleRounded(slot_rect, 0.1f, 20, fill);
        DrawRectangleRoundedLinesEx(slot_rect, 0.1f, 20, 2, BLACK);

        if (slots[i].is_occupied) {
            const Vector2 centre = {
                local_x + h_slot_size,
                local_y + h_slot_size
            };

            if (slots[i].atomic_number > 0) {
                Element e = PeriodicTable[slots[i].atomic_number];
                Color fill = getColourForType(e.type);

                DrawPoly(
                    centre,6, h_slot_size - 4, 0, fill
                );

                DrawPolyLinesEx(
                    centre,6, h_slot_size - 4, 0, 3.0f, Colours::HEX_BORDER
                );

                int symbol_width = MeasureText(e.symbol, 30);
                DrawText(e.symbol, (int)centre.x - symbol_width / 2, (int)centre.y - 20, 30, DARKGRAY);

                std::string num = std::to_string(slots[i].atomic_number);
                int num_width = MeasureText(num.c_str(), 15);
                DrawText(num.c_str(), (int)centre.x - num_width / 2, (int)centre.y + 15, 12, GRAY);
            }
        }
    }
}

// Getters & Setters
void Hotbar::setSlot(const int slot_index, const int atomic_number) {
    slots[slot_index].atomic_number = atomic_number;
    slots[slot_index].is_occupied = true;
}

void Hotbar::clearSlot(const int slot_index) {
    slots[slot_index].is_occupied = false;
    slots[slot_index].atomic_number = 0;
}

bool Hotbar::isSlotOccupied(const int slot_index) const {
    return slots[slot_index].is_occupied;
}


int Hotbar::getSlot(const int slot_index) const {
    return slots[slot_index].atomic_number;
}

HotbarSlot *Hotbar::getSlots() {
    return slots;
}




