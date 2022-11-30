#ifndef GAME_H
#define GAME_H
#include "map.h"

using namespace sf;

class Game{
public:
    int level;
    int unit_amount;
    int item_amount;
    Map map;
    View view;
public:
    Game();
    void update();
    void update_view(RenderWindow &window);
    void draw(RenderWindow &window);
};


#endif //GAME_H
