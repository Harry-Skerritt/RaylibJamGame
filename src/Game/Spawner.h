//
// Created by Harry Skerritt on 07/07/2026.
//

#ifndef SPAWNER_H
#define SPAWNER_H
#include <algorithm>
#include "../Grid/Grid.h"

class Spawner {
public:
    Spawner();
    ~Spawner();

    [[nodiscard]] int spawnRandomElement(Grid* grid) const;

    [[nodiscard]] int getMaxAtomicNumber() const { return max_atomic_number; }
    void setMaxAtomicNumber(int max);

    void reset() { max_atomic_number = 1; }
private:
    int max_atomic_number = 1;
};



#endif //SPAWNER_H
