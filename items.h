#ifndef ITEMS_H
#define ITEMS_H

#include <SFML/Graphics.hpp>
#include "cmath"
#include "position.h"


enum {
    WALL,
    EMPTY,
    ENEMY,
    PLAYER,
    ITEM,
    WEAPON
};


using namespace std;
using namespace sf;

class Item {
public:
    int check;
    Position position;
    Sprite sprite;
    Texture *texture;
public:

    void set_position(double x, double y);

    void draw(RenderWindow &window);

  //  virtual void update(vector<vector<Cell>> &map) = 0;

    virtual int type() { return ITEM; }

    ~Item();
};

/*class Clip : public Item {
private:
    int clip_capacity;
    int size;
public:
    Clip() {}

    void update(std::vector<std::vector<Cell>> &map) override {}

};*/

/*
class first_aid_kit : public Item {
public:
    first_aid_kit();

    void use_first_aid_kit();
};*/


#endif //ITEMS_H
