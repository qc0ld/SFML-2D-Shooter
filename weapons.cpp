#include "weapons.h"





ak47::ak47() {
    check = 0;
    texture = new Texture;
    texture->loadFromFile("Textures/Items/Weapons/ak47.png");
    sprite.setTexture(*texture);
}

void ak47::attack() {
    return;
}

Bullet::Bullet() {
    position.x = 0;
    position.y = 0;
    speed = 1;
    check = 0;
    damage = 33;
    texture.loadFromFile("Textures/Units/Bullet.png");
    sprite.setTexture(texture);
}

void Bullet::draw(RenderWindow &window) {
    sprite.setPosition(position.x, position.y);
    if (check == 1) {
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