//
// Created by Harry Skerritt on 10/07/2026.
//

#ifndef ACHIEVEMENTMANAGER_H
#define ACHIEVEMENTMANAGER_H
#include <string>
#include <vector>
#include <raylib.h>

#include "../../utils/Element.h"

struct Achievement {
    std::string title;
    ElementType type;
    float alpha = 0.0f;
    float timer = 0.0f;
    int state = 0;
};

class AchievementManager {
public:
    void add(std::string title, ElementType type);
    void update(float dt);
    void draw(Font font_header, Font font_body);

private:
    std::vector<Achievement> achievements;
    float fadeTime = 1.5f;
    float holdTime = 2.0f;
};



#endif //ACHIEVEMENTMANAGER_H
