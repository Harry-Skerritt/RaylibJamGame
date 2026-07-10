//
// Created by Harry Skerritt on 09/07/2026.
//

#include "TableElement.h"

#include "../../utils/Element.h"

TableElement::TableElement() {}
TableElement::~TableElement() {}

void TableElement::init(const int an) {
    atomic_number = an;
}


void TableElement::draw(
    const Vector2 pos, const Vector2 size, const bool is_filled,
    const Font* symbol_font, const int symbol_size,
    const Font* num_font, const int num_size
) const {
    const Element e = PeriodicTable[atomic_number];
    const Color fill = is_filled ? getColourForType(e.type) : GRAY;
    const Color text = is_filled ? DARKGRAY : WHITE;

    Rectangle background_rect = { pos.x, pos.y, size.x, size.y };

    DrawRectangleRec(background_rect, fill);

    DrawRectangleLinesEx(background_rect, 3.0f, Fade({0,0,0}, 0.2f));

    const int symbol_width = MeasureTextEx(*symbol_font, e.symbol, symbol_size, 2).x;
    const int num_width = MeasureTextEx(*num_font, std::to_string(atomic_number).c_str(), num_size, 2).x;

    Vector2 symbol_pos = {
        (pos.x + size.x / 2) - (symbol_width / 2),
        pos.y + 2
    };

    DrawTextEx(*symbol_font, e.symbol,symbol_pos, symbol_size, 2, text);

    Vector2 num_pos = {
    (pos.x + size.x / 2) - (num_width / 2),
    (pos.y + size.y / 2) - (num_width / 2) + 10
    };

    DrawTextEx(*num_font, std::to_string(atomic_number).c_str(), num_pos, num_size, 2, text);
}

