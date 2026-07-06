//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef GRID_H
#define GRID_H
#include <vector>

struct Tile {
    int q, r;
    int atomic_number;
};

class Grid {
public:
    Grid();
    void update();
    void draw();

    void setAtom(int q, int r, int element);
    Tile* getTile(int q, int r);


    Tile* getTileAtMouse();
    Tile* getNearestHex(float q, float r);

private:
    Tile* hovered_tile = nullptr;
    std::vector<Tile> tiles;
    float hex_size = 50.0f;
    float centre_x = 360.0f;
    float centre_y = 310.0f;
};



#endif //GRID_H
