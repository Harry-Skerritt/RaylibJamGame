//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef ELEMENT_H
#define ELEMENT_H
#include "raylib.h"
#include "Colours.h"
#include <string>

enum ElementType {
    NONE, OTHER_NON_METAL, NOBLE_GAS, ALKALI_METAL,
     ALKALI_EARTH_METAL, OTHER_METAL,
     TRANSITION_METAL, LANTHANIDE, ACTINOID, HALOGEN
};

struct Element {
    const char* symbol;
    const char* full_name;
    ElementType type;
};


static const Element PeriodicTable[] = {
    { "", "", NONE }, // 0
    { "H", "Hydrogen", OTHER_NON_METAL },
    { "He", "Helium", NOBLE_GAS },
    { "Li", "Lithium", ALKALI_METAL },
    { "Be", "Beryllium", ALKALI_EARTH_METAL },
    { "B", "Boron", OTHER_NON_METAL }, { "C", "Carbon", OTHER_NON_METAL },
    { "N", "Nitrogen", OTHER_NON_METAL }, { "O", "Oxygen", OTHER_NON_METAL },
    { "F", "Fluorine", HALOGEN }, { "Ne", "Neon", NOBLE_GAS },
    { "Na", "Sodium", ALKALI_METAL }, { "Mg", "Magnesium", ALKALI_EARTH_METAL },
    { "Al", "Aluminium", OTHER_METAL }, { "Si", "Silicon", OTHER_NON_METAL },
    { "P", "Phosphorus", OTHER_NON_METAL }, { "S", "Sulfur", OTHER_NON_METAL },
    { "Cl", "Chlorine", HALOGEN }, { "Ar", "Argon", NOBLE_GAS },
    { "K", "Potassium", ALKALI_METAL }, { "Ca", "Calcium", ALKALI_EARTH_METAL },
    { "Sc", "Scandium", LANTHANIDE }, { "Ti", "Titanium", TRANSITION_METAL },
    { "V", "Vanadium", TRANSITION_METAL }, { "Cr", "Chromium", TRANSITION_METAL },
    { "Mn", "Manganese", TRANSITION_METAL }, { "Fe", "Iron", TRANSITION_METAL },
    { "Co", "Cobalt", TRANSITION_METAL }, { "Ni", "Nickel", TRANSITION_METAL },
    { "Cu", "Copper", TRANSITION_METAL }, { "Zn", "Zinc", TRANSITION_METAL },
    { "Ga", "Gallium", OTHER_METAL }, { "Ge", "Germanium", OTHER_METAL },
    { "As", "Arsenic", OTHER_NON_METAL }, { "Se", "Selenium", OTHER_NON_METAL },
    { "Br", "Bromine", HALOGEN }, { "Kr", "Krypton", NOBLE_GAS },
    { "Rb", "Rubidium", ALKALI_METAL }, { "Sr", "Strontium", ALKALI_EARTH_METAL },
    { "Y", "Yttrium", LANTHANIDE }, { "Zr", "Zirconium", TRANSITION_METAL },
    { "Nb", "Niobium", TRANSITION_METAL }, { "Mo", "Molybdenum", TRANSITION_METAL },
    { "Tc", "Technetium", TRANSITION_METAL }, { "Ru", "Ruthenium", TRANSITION_METAL },
    { "Rh", "Rhodium", TRANSITION_METAL }, { "Pd", "Palladium", TRANSITION_METAL },
    { "Ag", "Silver", TRANSITION_METAL }, { "Cd", "Cadmium", TRANSITION_METAL },
    { "In", "Indium", OTHER_METAL }, { "Sn", "Tin", OTHER_METAL },
    { "Sb", "Antimony", OTHER_METAL }, { "Te", "Tellurium", OTHER_NON_METAL },
    { "I", "Iodine", HALOGEN }, { "Xe", "Xenon", NOBLE_GAS },
    { "Cs", "Cesium", ALKALI_METAL }, { "Ba", "Barium", ALKALI_EARTH_METAL },
    { "La", "Lanthanum", LANTHANIDE }, { "Ce", "Cerium", LANTHANIDE },
    { "Pr", "Praseodymium", LANTHANIDE }, { "Nd", "Neodymium", LANTHANIDE },
    { "Pm", "Promethium", LANTHANIDE }, { "Sm", "Samarium", LANTHANIDE },
    { "Eu", "Europium", LANTHANIDE }, { "Gd", "Gadolinium", LANTHANIDE },
    { "Tb", "Terbium", LANTHANIDE }, { "Dy", "Dysprosium", LANTHANIDE },
    { "Ho", "Holmium", LANTHANIDE }, { "Er", "Erbium", LANTHANIDE },
    { "Tm", "Thulium", LANTHANIDE }, { "Yb", "Ytterbium", LANTHANIDE },
    { "Lu", "Lutetium", LANTHANIDE }, { "Hf", "Hafnium", TRANSITION_METAL },
    { "Ta", "Tantalum", TRANSITION_METAL }, { "W", "Tungsten", TRANSITION_METAL },
    { "Re", "Rhenium", TRANSITION_METAL }, { "Os", "Osmium", TRANSITION_METAL },
    { "Ir", "Iridium", TRANSITION_METAL }, { "Pt", "Platinum", TRANSITION_METAL },
    { "Au", "Gold", TRANSITION_METAL }, { "Hg", "Mercury", TRANSITION_METAL },
    { "Tl", "Thallium", OTHER_METAL }, { "Pb", "Lead", OTHER_METAL },
    { "Bi", "Bismuth", OTHER_METAL }, { "Po", "Polonium", OTHER_METAL },
    { "At", "Astatine", HALOGEN }, { "Rn", "Radon", NOBLE_GAS },
    { "Fr", "Francium", ALKALI_METAL }, { "Ra", "Radium", ALKALI_EARTH_METAL },
    { "Ac", "Actinium", ACTINOID }, { "Th", "Thorium", ACTINOID },
    { "Pa", "Protactinium", ACTINOID }, { "U", "Uranium", ACTINOID },
    { "Np", "Neptunium", ACTINOID }, { "Pu", "Plutonium", ACTINOID },
    { "Am", "Americium", ACTINOID }, { "Cm", "Curium", ACTINOID },
    { "Bk", "Berkelium", ACTINOID }, { "Cf", "Californium", ACTINOID },
    { "Es", "Einsteinium", ACTINOID }, { "Fm", "Fermium", ACTINOID },
    { "Md", "Mendelevium", ACTINOID }, { "No", "Nobelium", ACTINOID },
    { "Lr", "Lawrencium", ACTINOID }, { "Rf", "Rutherfordium", TRANSITION_METAL },
    { "Db", "Dubnium", TRANSITION_METAL }, { "Sg", "Seaborgium", TRANSITION_METAL },
    { "Bh", "Bohrium", TRANSITION_METAL }, { "Hs", "Hassium", TRANSITION_METAL },
    { "Mt", "Meitnerium", TRANSITION_METAL }, { "Ds", "Darmstadtium", TRANSITION_METAL },
    { "Rg", "Roentgenium", TRANSITION_METAL }, { "Cn", "Copernicium", TRANSITION_METAL },
    { "Nh", "Nihonium", OTHER_METAL }, { "Fl", "Flerovium", OTHER_METAL },
    { "Mc", "Moscovium", OTHER_METAL }, { "Lv", "Livermorium", OTHER_METAL },
    { "Ts", "Tennessine", HALOGEN }, { "Og", "Oganesson", NOBLE_GAS }
};

static constexpr int ELEMENT_COUNT = std::size(PeriodicTable) - 1;

inline Color getColourForType(ElementType type) {
    switch (type) {
        case ALKALI_METAL:        return (Color){ 223, 65, 65, 255 }; // Soft Red
        case ALKALI_EARTH_METAL:  return (Color){ 255, 145, 13, 255 };   // Orange
        case TRANSITION_METAL:    return (Color){ 236, 215, 55, 255 };   // Gold
        case OTHER_METAL:         return (Color){ 108, 237, 179, 255 }; // Steel Grey
        case LANTHANIDE:          return (Color){ 240, 98, 155, 255 }; // Light Pink
        case ACTINOID:            return (Color){ 165, 66, 185, 255 }; // Violet
        case OTHER_NON_METAL:     return (Color){ 71, 198, 216, 255 }; // Sky Blue
        case HALOGEN:             return (Color){ 138, 203, 78, 255 }; // Pale Yellow
        case NOBLE_GAS:           return (Color){ 216, 222, 52, 255 }; // Cyan
        default:                  return Colours::HEX_BACKGROUND;
    }
}

inline std::string getTypePluralString(ElementType type) {
    switch (type) {
        case ALKALI_METAL: return "Alkali Metals";
        case ALKALI_EARTH_METAL: return "Alkali Earth Metals";
        case TRANSITION_METAL: return "Transition Metals";
        case OTHER_METAL: return "Other Metals";
        case LANTHANIDE: return "Lanthanides";
        case ACTINOID: return "Actini Metals";
        case OTHER_NON_METAL: return "Other Non Metals";
        case HALOGEN: return "Halogens";
        case NOBLE_GAS: return "Noble Gases";
    }
}

struct Coord {
    int q, r;

    bool operator==(const Coord& other) const {
        return q == other.q && r == other.r;
    }
};



#endif //ELEMENT_H
