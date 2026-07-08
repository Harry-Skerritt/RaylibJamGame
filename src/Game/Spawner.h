//
// Created by Harry Skerritt on 07/07/2026.
//

#ifndef SPAWNER_H
#define SPAWNER_H



class Spawner {
public:
    Spawner();
    ~Spawner();

    int spawnRandomElement() const;

    int getMaxAtomicNumber() { return max_atomic_number; }
    void setMaxAtomicNumber(int max);
private:
    int max_atomic_number = 1;
};



#endif //SPAWNER_H
