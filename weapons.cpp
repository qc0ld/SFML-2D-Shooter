#include "weapons.h"

using namespace std;
ak47::ak47() : Weapon() {
    check = 0;
    size = 30;
    max_size = 30;
    texture = new Texture;
    texture->loadFromFile("Textures/Items/Weapons/ak47.png");
    sprite.setTexture(*texture);
}


void ak47::attack(RenderWindow &window, double x, double y) {
    if (size > 0) {
        Bullet bullet;
        bullet.set_up(window, x, y);
        clip.push(bullet);
        size--;
    }
}

void ak47::update(vector<vector<Cell>> &map) {
    return;
}


Bullet::Bullet() {
    position.x = 0;
    position.y = 0;
    speed = 1;
    check = 0;
    damage = 33;
    texture = new sf::Texture;
    texture->loadFromFile("Textures/Units/Bullet.png");
    sprite.setTexture(*texture);
}

void Bullet::draw(RenderWindow &window) {
    if (check == 1) {
        sprite.setPosition(position.x, position.y);
        window.draw(sprite);
    }
}

void Bullet::set_up(RenderWindow &window, double x, double y) {
    Vector2i pixel_pos = Mouse::getPosition(window);
    world_pos = window.mapPixelToCoords(pixel_pos);

    position.x = x + 4;
    position.y = y + 4;
    angle = atan2(world_pos.x - position.x,
                  world_pos.y - position.y);
    check = 1;
}

void Bullet::move_x(double x) {
    position.x = position.x + x;
}

void Bullet::move_y(double y) {
    position.y = position.y + y;
}