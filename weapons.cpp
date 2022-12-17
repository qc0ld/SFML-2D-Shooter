#include "weapons.h"

using namespace std;

ak47::ak47() : Weapon() {
    check = 0;
    size = 30;
    max_size = 30;
    reload_timer = 0;
    reload_duration = 80;
    shot = 0;

    texture = new Texture;
    texture->loadFromFile("Textures/Items/Weapons/ak47.png");

    sprite.setTexture(*texture);

    font.loadFromFile("Textures/Fonts/Font.ttf");

    text = new Text;
    text->setFont(font);
    text->setCharacterSize(12);
    text->setFillColor(Color::Yellow);
}

void ak47::attack(RenderWindow &window, double x, double y) {
    if (size > 0) {
        cout << size << endl;
        Bullet bullet;
        bullet.set_up(window, x, y);
        clip.push(bullet);
        size--;
    }
}

void ak47::enemy_attack(double player_x, double player_y, double x, double y) {
    if (size > 0) {
        Bullet bullet;
        bullet.enemy_set_up(player_x, player_y, x, y);
        clip.push(bullet);
        size--;
    }
}




Bullet::Bullet() {
    position.x = 0;
    position.y = 0;
    speed = 0.8;
    check = 0;
    damage = 33;
    from = 0;
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

void Bullet::enemy_set_up(double player_x, double player_y, double x, double y) {
    position.x = x + 4;
    position.y = y + 4;
    angle = atan2(player_x - position.x, player_y - position.y);

    check = 1;
}

void Bullet::move_x(double x) {
    position.x = position.x + x;
}

void Bullet::move_y(double y) {
    position.y = position.y + y;
}

