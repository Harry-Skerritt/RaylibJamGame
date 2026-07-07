//
// Created by harryskerritt on 07/07/2026.
//

#ifndef RAYLIB_GAME_TEMPLATE_HOTBAR_H
#define RAYLIB_GAME_TEMPLATE_HOTBAR_H
#include "raylib.h"

struct HotbarSlot {
    bool is_occupied;
    int atomic_number;
};

class Hotbar {
public:
    void drawHotbar() const;

    void setSlot(int slot_index, int atomic_number);
    void clearSlot(int slot_index);

    bool isSlotOccupied(int slot_index) const;

    int getSlot(int slot_index) const;
    HotbarSlot* getSlots();

    int getSlotCount() const { return sizeof(slots) / sizeof(slots[0]); }

private:
    HotbarSlot slots[3] = { false, 0 };
};


#endif //RAYLIB_GAME_TEMPLATE_HOTBAR_H