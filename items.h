#ifndef ITEMS_H
#define ITEMS_H

#include <SFML/Graphics.hpp>
#include "cmath"
#include "position.h"

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
};


/*class Clip : public Item {
private:
    int clip_capacity;
    int size;
public:
    Clip();

};


class first_aid_kit : public Item {
public:
    first_aid_kit();

    void use_first_aid_kit();
};*/


#endif //ITEMS_H
