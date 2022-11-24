#include "unit.h"

using namespace std;
using namespace sf;

Unit::Unit() : speed(0.2) {
    position.x = 60;
    position.y = 60;
    texture.loadFromFile("Textures/Units/Player.png");
    sprite.setTexture(texture);
}

void Unit::draw(RenderWindow &window) {
    sprite.setPosition(position.x, position.y);
    window.draw(sprite);
}

void Unit::check_collision(vector<vector<Cell>> &map) {
    int x = (position.x / 16);
    int y = (position.y / 16);
    if (direction == 1) {
        if (map[x][y].get_type() == WALL ||
            map[x][y].get_type() != WALL && map[x][y + 1].get_type() == WALL) {
            position.x += speed + 0.01;
        }
    } else if (direction == 2) {
        if (map[x][y].get_type() == WALL ||
            map[x][y].get_type() != WALL && map[x + 1][y].get_type() == WALL) {
            position.y += speed + 0.01;
        }
    } else if (direction == 3) {
        if (map[x + 1][y].get_type() == WALL ||
            map[x + 1][y].get_type() != WALL && map[x + 1][y + 1].get_type() == WALL) {
            position.x -= speed + 0.01;
        }
    } else if (direction == 4) {
        if (map[x][y + 1].get_type() == WALL ||
            map[x][y + 1].get_type() != WALL && map[x + 1][y + 1].get_type() == WALL) {
            position.y -= speed + 0.01;
        }
    }
}


void Unit::update(RenderWindow &window, Map &map) {
    check_collision(map.map);
    if (1 == Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right) == 1) {
        position.x += speed;
        direction = 3;
    } else if (1 == Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left)) {
        position.x -= speed;
        direction = 1;
    } else if (1 == Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) {
        position.y -= speed;
        direction = 2;
    } else if (1 == Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) {
        position.y += speed;
        direction = 4;
    }

    if (Keyboard::isKeyPressed(Keyboard::Space) == 1) {

        Vector2i pixel_pos = Mouse::getPosition(window);
        bullet.world_pos = window.mapPixelToCoords(pixel_pos);

        bullet.position.x = position.x;
        bullet.position.y = position.y;
        bullet.angle = atan2(bullet.world_pos.x - position.x,
                             bullet.world_pos.y - position.y);
        bullet.check = 0;
    }

    bullet.update(window, map);

    bullet.draw(window);
}


Bullet::Bullet() {
    speed = 1;
    check = 1;
    texture.loadFromFile("Textures/Units/Bullet.png");
    sprite.setTexture(texture);
}

void Bullet::draw(RenderWindow &window) {
    sprite.setPosition(position.x, position.y);
    if (check != 3) {
        window.draw(sprite);
    }
}

void Bullet::update(RenderWindow &window, Map &map) {
    if (check == 0) {
        position.x += sin(angle) * speed;
        position.y += cos(angle) * speed;
        if (map.map[position.x / 16][position.y / 16].get_type() == WALL) {
            check = 3;
        }
    }
}