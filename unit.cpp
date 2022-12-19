#include "unit.h"
#include "game.h"

using namespace std;
using namespace sf;

Unit::Unit() {
    dead = 0;
    hp = 100;
    position.x = 0;
    position.y = 0;
    speed = 0.2;
    weapon = nullptr;
    texture = new Texture;
    texture->loadFromFile("Textures/Units/Player.png");
    sprite.setTexture(*texture);
    walk_timer = 0;
    walk_duration = 400;
}

void Unit::draw(RenderWindow &window) {
    if (dead == 0) {
        sprite.setPosition(position.x, position.y);
        window.draw(sprite);
    }
}

void Unit::move_with_direction(int dir) {
    if (dir == 1) {
        move_x(-speed);
    } else if (dir == 2) {
        move_y(-speed);
    } else if (dir == 3) {
        move_x(speed);
    } else if (dir == 4) {
        move_y(speed);
    }
}

void Unit::move_x(double x) {
    position.x = position.x + x;
}

void Unit::move_y(double y) {
    position.y = position.y + y;
}

void Unit::set_position(double x, double y) {
    position.x = x;
    position.y = y;
}

void Unit::get_damage(double damage) {
    if (hp - damage <= 0) {
        drop_weapon();
        dead = 1;
    } else {
        hp -= damage;
    }
}

void Unit::drop_weapon() {
    if (weapon) {
        weapon->check = 0;
        weapon = nullptr;
    }
}

void Unit::set_weapon(shared_ptr<Weapon>(&new_weapon)) {
    weapon = new_weapon;
    weapon->check = 1;
}
