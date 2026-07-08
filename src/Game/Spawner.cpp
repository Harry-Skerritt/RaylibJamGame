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


int Spawner::spawnRandomElement() const {
    int current_max = max_atomic_number;

    if (current_max <= 1) return 1;

    bool has_legacy = (current_max >= 10);
    int legacy_ceiling = has_legacy ? (current_max / 5) : 0;

    int roll = GetRandomValue(1, 100);

    if (has_legacy && roll <= 10) {
        // 10% Chance to get a low level (1-10)
        return GetRandomValue(1, legacy_ceiling);
    }
    else if (roll <= 70) {
        // 60% Chance for something currently in use
        int working_floor = std::max(legacy_ceiling + 1, current_max - 15);
        return GetRandomValue(working_floor, current_max - 1);
    }
    else {
        // 30% chance for the "new stuff"
        int newest_floor = std::max(2, current_max - 3);
        return GetRandomValue(newest_floor, current_max);
    }
}


void Spawner::setMaxAtomicNumber(int max) {
    if (max > max_atomic_number) max_atomic_number = max;
    max_atomic_number = std::min(max_atomic_number, ELEMENT_COUNT);
}
