#include "items.h"


void Item::set_position(double x, double y) {
    position.x = x;
    position.y = y;
}

void Item::draw(RenderWindow &window) {
    sprite.setPosition(position.x, position.y);
    window.draw(sprite);
}