#ifndef ITEMS_H
#define ITEMS_H

#include <SFML/Graphics.hpp>
#include "cmath"
#include "memory"


enum {
    WALL,
    EMPTY,
    ENEMY,
    PLAYER,
    ITEM,
    WEAPON
};

typedef struct Position Position;
struct Position {
    float x;
    float y;
};

class Unit;

using namespace std;
using namespace sf;

class Item {
public:
    int check;
    Position position;
    Sprite sprite;
    Texture *texture;
public:

    Item();

    void set_position(double x, double y);

    void draw(RenderWindow &window);

    virtual int type() { return ITEM; }

    virtual void use(unique_ptr<Unit> &unit) = 0;

    ~Item();
};

class Ammo_box : public Item {
public:
    Ammo_box();

    void use(unique_ptr<Unit> &unit) override;


};


class Med_kit : public Item {
public:
    Med_kit();

    void use(unique_ptr<Unit> &unit) override;
};


#endif //ITEMS_H
