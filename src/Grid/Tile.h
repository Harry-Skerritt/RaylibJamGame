//
// Created by Harry Skerritt on 07/07/2026.
//

#ifndef TILE_H
#define TILE_H
#include "raylib.h"


class Tile {
public:
    int q, r, atomic_number;
    Vector2 pos;
    bool is_highlighted = false;
    float stability = 1.0f;
    int stability_passes;
    bool is_volatile = false;

    Tile(int q, int r, int atomic_number, Vector2 pos, int passes);

    bool isValidPlacement();

    void draw(float hex_size, float centre_x, float centre_y, bool is_hovered, bool is_placing);
    void drawTempTile(Vector2 screenPos, float hex_size, int atomic_number);

    void setStability(float stability) { this->stability = stability; }
    void changeStability(float stability) { this->stability += stability; }
    [[nodiscard]] float getStability() const { return stability; }

    void minusPass() { stability_passes -= 1; }
    [[nodiscard]] int getStabilityPasses() const { return stability_passes; }
    [[nodiscard]] bool isStable() const { return stability_passes != 0; };

private:
    void drawHealthBar(Vector2 pos, float current_health, float max_health);
    Color getContrastColor(Color c);
};



#endif //TILE_H
