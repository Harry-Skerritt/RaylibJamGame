//
// Created by harryskerritt on 07/07/2026.
//

#include "Hotbar.h"

#include "../../AssetManager/AssetManager.h"
#include "../../Grid/Tile.h"

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

    DrawRectangleRounded(background_rect, 0.1f, 20, Fade(BLACK, 0.4f));
    DrawRectangleRoundedLines(background_rect, 0.1f, 20, Fade(GRAY, 0.5f));

    auto font = AssetManager::GetFont("itim-20");
    DrawTextEx(font, "Next Elements",
        {start_x - (background_padding_x / 2.0f) + 10, start_y - (background_padding_y * 0.75f) + 5 }, 22, 2, RAYWHITE);

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
                Tile temp_tile(0, 0, slots[i].atomic_number, centre, 3);
                temp_tile.drawTempTile(centre, h_slot_size - 5, slots[i].atomic_number);
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

void Hotbar::clearAll() {
    for (int i = 0; i < 3; i++) {
        slots[i].is_occupied = false;
        slots[i].atomic_number = 0;
    }
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

int Hotbar::getNextEmptyIndex() const {
    for (int i = 0; i < getSlotCount(); i++) {
        if (slots[i].is_occupied) continue;
        return i;
    }

    return -1;
}





