//
// Created by Harry Skerritt on 07/07/2026.
//

#include "Spawner.h"
#include <algorithm>
#include <iostream>
#include <random>

#include "raylib.h"
#include "../utils/Element.h"

Spawner::Spawner() {}
Spawner::~Spawner() = default;


int Spawner::spawnRandomElement(Grid* grid) const {
    int current_max = max_atomic_number;
    if (current_max <= 2) return GetRandomValue(1, current_max);

    int min_present = grid->getMinAtomicNumber();
    int effective_floor = std::max(min_present, current_max / 2);

    // 30% Chance of a 'rescue'
    std::vector<int> orphans = grid->getOrphanedAtomicNumbers(10);
    if (!orphans.empty() && GetRandomValue(0, 100) < 30) {
        return orphans[GetRandomValue(0, static_cast<int>(orphans.size()) - 1)];
    }

    int roll = GetRandomValue(1, 100);

    // 10% Chance to get a low level
    if (roll <= 10 && min_present < (current_max / 4)) {
        return GetRandomValue(1,  std::max(1, min_present + 5));
    }

    // 50% Chance for something currently in use
    if (roll <= 60) {
        return GetRandomValue(effective_floor, current_max - 2);
    }

    // 40% Chance for "New Stuff"
    return GetRandomValue(std::max(effective_floor, current_max - 3), current_max);
}


void Spawner::setMaxAtomicNumber(int max) {
    if (max > max_atomic_number) max_atomic_number = max;
    max_atomic_number = std::min(max_atomic_number, ELEMENT_COUNT);
}
