//
// Created by Harry Skerritt on 06/07/2026.
//

#ifndef MENU_H
#define MENU_H



class Menu {
public:
    void update();
    void draw();
    bool shouldStartGame() const { return start_game; };

private:
    bool start_game = false;
};



#endif //MENU_H
