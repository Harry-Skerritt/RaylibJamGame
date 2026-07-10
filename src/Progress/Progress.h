//
// Created by Harry Skerritt on 09/07/2026.
//

#ifndef PROGRESS_H
#define PROGRESS_H
#include <vector>

#include "../UI/TableElement/TableElement.h"


class Progress {
public:
    Progress();
    ~Progress();

    void init(int max_atomic_number);
    void update();
    void draw();

    bool transitionToGame() const { return go_to_game; }

private:
    std::vector<TableElement*> elements;
    Vector2 element_size = { 42, 42 };
    Vector2 element_gap = { 5, 5 };
    Vector2 start_pos = { 10, 40 };
    float group_gap_y = 75;
    int row_max_elements = 15;

    int max_atomic_number = 69;

    std::vector<int> onm_numbers;   // Other Non Metals
    std::vector<int> am_numbers;    // Alkali Metals
    std::vector<int> aem_numbers;   // Alkaline Earth Metals
    std::vector<int> h_numbers;     // Halogens
    std::vector<int> ng_numbers;    // Noble Gasses
    std::vector<int> om_numbers;    // Other Metals
    std::vector<int> a_numbers;     // Actinoids
    std::vector<int> ree_numbers;   // Rare Earth Elements
    std::vector<int> tm_numbers;    // Transition Metals
    void getAtomicNumbers();

    void drawGroup(const char* group_title, int count, std::vector<int> numbers, Vector2 start_pos);
    void drawTitle();


    bool go_to_game = false;
};



#endif //PROGRESS_H
