#include "items.h"
#include "unit.h"

using namespace sf;

Item::Item() {
    check = 0;
    texture = new Texture;
}

void Item::set_position(double x, double y) {
    position.x = x;
    position.y = y;
}


void Item::draw(RenderWindow &window) {
    if (check == 0) {
        sprite.setPosition(position.x, position.y);
        window.draw(sprite);
    }
}

Item::~Item() {
    delete texture;
}

Med_kit::Med_kit() {
    texture->loadFromFile("Textures/Items/Med_kit.png");
    sprite.setTexture(*texture);
}

void Med_kit::use(unique_ptr<Unit> &unit) {
    if (unit->hp != 100) {
        unit->hp = 100;
        check = 1;
    }
}

Ammo_box::Ammo_box() {
    texture->loadFromFile("Textures/Items/Ammo_box.png");
    sprite.setTexture(*texture);
}

void Ammo_box::use(unique_ptr<Unit> &unit) {
    if (unit->weapon) {
        if (unit->weapon->size != 30) {
            unit->weapon->size = 30;
            check = 1;
        }
    }
}