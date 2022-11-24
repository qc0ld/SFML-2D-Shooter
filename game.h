#ifndef GAME_H
#define GAME_H
#include "map.h"

class Game{
public:
    int level;
    int unit_amount;
    int item_amount;
    Map map;
public:
    Game();
    void update();
    void draw(RenderWindow &window);
    bool if_game_won;
    bool if_game_lost;

};


#endif //GAME_H
