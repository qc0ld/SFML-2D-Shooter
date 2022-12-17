#include "items.h"
#include "game.h"



void Item::set_position(double x, double y) {
    position.x = x;
    position.y = y;
}


void Item::draw(RenderWindow &window) {
    sprite.setPosition(position.x, position.y);
    window.draw(sprite);
}

Item::~Item() {
    delete texture;
}