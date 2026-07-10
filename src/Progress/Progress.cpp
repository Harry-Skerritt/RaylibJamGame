//
// Created by Harry Skerritt on 09/07/2026.
//

#include "Progress.h"

#include <iostream>
#include <__ostream/basic_ostream.h>

#include "../UI/TableElement/TableElement.h"
#include "../AssetManager/AssetManager.h"
#include "../utils/Element.h"

Progress::Progress() {}
Progress::~Progress() {}


void Progress::init(int max_atomic_number) {
    this->max_atomic_number = max_atomic_number;
    getAtomicNumbers();
}


void Progress::update() {
    go_to_game = false;
    if (IsKeyPressed(KEY_TAB)) {
        go_to_game = true;
    }
}

void Progress::draw() {
    drawTitle();

    drawGroup("Other Non Metals", 11, onm_numbers, start_pos);

    drawGroup("Other Metals", 14, om_numbers, { start_pos.x, start_pos.y + group_gap_y });

    drawGroup("Transition Metals", 36, tm_numbers, { start_pos.x, start_pos.y + group_gap_y * 2});

    drawGroup("Halogens", 6, h_numbers, { start_pos.x, start_pos.y + group_gap_y * 3 + 100});
    drawGroup("Alkali Metals", 6, am_numbers, { static_cast<float>(GetScreenWidth()) - 287, start_pos.y + group_gap_y * 3 + 100});

    drawGroup("Noble Gasses", 7, ng_numbers, { start_pos.x, start_pos.y + group_gap_y * 4 + 100});
    drawGroup("Alkali Earth Metals", 6, aem_numbers, { static_cast<float>(GetScreenWidth()) - 287, start_pos.y + group_gap_y * 4 + 100});

    drawGroup("Actinoids", 15, a_numbers, { start_pos.x, start_pos.y + group_gap_y * 5 + 100});

    drawGroup("Rare Earth Elements & Lanthanoids", 17, ree_numbers, { start_pos.x, start_pos.y + group_gap_y * 6 + 100});
}

void Progress::drawGroup(const char* group_title, const int count, std::vector<int> numbers, const Vector2 start_pos) {
    // Load Fonts
    auto symbol_font = AssetManager::GetFont("itim-25");
    auto num_font = AssetManager::GetFont("itim-15");
    auto title_font = AssetManager::GetFont("itim-30");

    // Draw Title
    auto title_dims = MeasureTextEx(title_font, group_title, 30, 2);
    DrawTextEx(title_font, group_title, start_pos, 30, 2, WHITE);

    // Draw
    for (int i = 0; i < count; i++) {
        int row = i / row_max_elements;
        int col = i % row_max_elements;

        Vector2 pos;
        pos.x = start_pos.x +  (col * element_size.x) + (col * element_gap.x);
        pos.y = start_pos.y + title_dims.y + (row * element_size.y) + (row * element_gap.y);

        TableElement element = TableElement();
        element.init(numbers.at(i));
        element.draw(pos, element_size, (numbers.at(i) <= max_atomic_number) ? true : false, &symbol_font, 25, &num_font, 15);
    }
}

void Progress::drawTitle() {
    const auto title_font = AssetManager::GetFont("itim-40");

    const auto title_dims = MeasureTextEx(title_font, "PROGRESS", 40, 2);
    DrawTextEx(title_font, "PROGRESS", { static_cast<float>(GetScreenWidth()) / 2 - title_dims.x / 2, 10 }, 40, 2, WHITE);

    const auto complete_string = std::to_string(max_atomic_number) + "/" + std::to_string(ELEMENT_COUNT);
    const auto complete_dims = MeasureTextEx(title_font, complete_string.c_str(), 40, 2);
    DrawTextEx(
        title_font, complete_string.c_str(), { static_cast<float>(GetScreenWidth()) - complete_dims.x - 10, 10 }, 40, 2, WHITE);
}

void Progress::getAtomicNumbers() {
    onm_numbers.clear();
    am_numbers.clear();
    aem_numbers.clear();
    h_numbers.clear();
    ng_numbers.clear();
    om_numbers.clear();
    a_numbers.clear();
    ree_numbers.clear();
    tm_numbers.clear();

    for (int i = 0; i < ELEMENT_COUNT+1; i++) {
        switch (PeriodicTable[i].type) {
            case(ElementType::OTHER_NON_METAL):
                onm_numbers.push_back(i);
                break;
            case(ElementType::ALKALI_METAL):
                am_numbers.push_back(i);
                break;
            case(ElementType::ALKALI_EARTH_METAL):
                aem_numbers.push_back(i);
                break;
            case(ElementType::HALOGEN):
                h_numbers.push_back(i);
                break;
            case(ElementType::NOBLE_GAS):
                ng_numbers.push_back(i);
                break;
            case(ElementType::OTHER_METAL):
                om_numbers.push_back(i);
                break;
            case(ElementType::ACTINOID):
                a_numbers.push_back(i);
                break;
            case(ElementType::LANTHANIDE):
                ree_numbers.push_back(i);
                break;
            case(ElementType::TRANSITION_METAL):
                tm_numbers.push_back(i);
                break;
            default: ;
        }
    }
}


