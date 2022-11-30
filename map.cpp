#include "map.h"
#include "cmath"

using namespace std;


Map::Map() : player(), bullet() {


    vector<vector<char>> map_sketch = {
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', 'P', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', '#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', '#', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    };
    for (int i = 0; i < 4; i++) {
        Shooter shooter;
        shooters[i] = shooter;
    }
    enemy_amount = 0;
    height = map_sketch.size();
    width = map_sketch[0].size();
    vector<vector<Cell>> a(height, vector<Cell>(width));
    map = a;
    for (int i = 0; i < height; ++i) {
        for (int k = 0; k < width; ++k) {
            if (map_sketch[i][k] == '#') {
                Wall wall;
                map[i][k] = wall;
            } else {
                Floor floor;
                map[i][k] = floor;
                if (map_sketch[i][k] == 'E') {
                    shooters[enemy_amount++].set_position(i * 16, k * 16);
                } else if (map_sketch[i][k] == 'P') {
                    player.set_position(i * 16, k * 16);
                }
            }
        }
    }
}

void Map::draw(RenderWindow &window) {
    for (int i = 0; i < height; ++i) {
        for (int k = 0; k < width; ++k) {
            map[i][k].draw(window, i * 16, k * 16);
        }
    }
}

void Map::update_enemy() {
    for (int i = 0; i < 4; i++) {
        if (shooters[i].dead == 1) {
            enemy_amount--;
            map[shooters[i].position.x / 16][shooters[i].position.y / 16].type = EMPTY;
        } else {
            map[shooters[i].position.x / 16][shooters[i].position.y / 16].type = ENEMY;
        }
    }
}

void Map::check_collision() {
    int x = player.position.x / 16;
    int y = player.position.y / 16;
    if (player.direction == 1) {
        if ((map[x][y].get_type() == WALL ||
             map[x][y].get_type() == EMPTY && map[x][y + 1].get_type() == WALL) ||
            (map[x][y].get_type() == ENEMY ||
             map[x][y].get_type() == EMPTY && map[x][y + 1].get_type() == ENEMY)) {
            player.move_x(player.speed + 0.01);
        }
    }
    if (player.direction == 2) {
        if ((map[x][y].get_type() == WALL ||
             map[x][y].get_type() == EMPTY && map[x + 1][y].get_type() == WALL) ||
            (map[x][y].get_type() == ENEMY ||
             map[x][y].get_type() == EMPTY && map[x + 1][y].get_type() == ENEMY)) {
            player.move_y(player.speed + 0.01);
        }
    }
    if (player.direction == 3) {
        if ((map[x + 1][y].get_type() == WALL ||
             map[x + 1][y].get_type() != WALL && map[x + 1][y + 1].get_type() == WALL) ||
            map[x + 1][y].get_type() == ENEMY ||
            map[x + 1][y].get_type() == EMPTY && map[x + 1][y + 1].get_type() == ENEMY) {
            player.move_x(-player.speed - 0.01);
        }
    }
    if (player.direction == 4) {
        if ((map[x][y + 1].get_type() == WALL ||
             map[x][y + 1].get_type() != WALL && map[x + 1][y + 1].get_type() == WALL) ||
            (map[x][y + 1].get_type() == ENEMY ||
             map[x][y + 1].get_type() == EMPTY && map[x + 1][y + 1].get_type() == ENEMY)) {
            player.move_y(-player.speed - 0.01);
        }
    }
}

Wall::Wall() {
    type = WALL;
    position.x = 0;
    position.y = 0;
    texture = new Texture;
    texture->loadFromFile("Textures/Map/Wall.png");
    sprite.setTexture(*texture);
}

Floor::Floor() {
    type = EMPTY;
    position.x = 0;
    position.y = 0;
    texture = new Texture;
    texture->loadFromFile("Textures/Map/Floor.png");
    sprite.setTexture(*texture);
}

void Cell::draw(RenderWindow &window, double x, double y) {
    sprite.setPosition(x, y);
    window.draw(sprite);
}

int Cell::get_type() {
    return type;
}

void Map::update_bullet() {
    if (bullet.check == 1) {
        bullet.move_x(sin(bullet.angle) * bullet.speed);
        bullet.move_y(cos(bullet.angle) * bullet.speed);
        if (map[bullet.position.x / 16][bullet.position.y / 16].get_type() == WALL) {
            bullet.check = 3;
        }
        if (map[bullet.position.x / 16][bullet.position.y / 16].get_type() == ENEMY) {
            cout << get_enemy(bullet.position.x, bullet.position.y) << endl;
            if (get_enemy(bullet.position.x, bullet.position.y) != 228) {
                shooters[get_enemy(bullet.position.x, bullet.position.y)].get_damage(bullet.damage);
            }
            bullet.check = 3;
        }
    }
}

void Map::update_player(int direction) {
    check_collision();
    if (direction == 1) {
        player.move_x(-player.speed);
    } else if (direction == 2) {
        player.move_y(-player.speed);
    } else if (direction == 3) {
        player.move_x(player.speed);
    } else if (direction == 4) {
        player.move_y(player.speed);
    }
    player.direction = direction;
}

int Map::get_enemy(double x_pos, double y_pos) {
    int x = x_pos / 16;
    int y = y_pos / 16;
    int x1, y1;
    for (int i = 0; i < 4; i++) {
        x1 = shooters[i].position.x / 16;
        y1 = shooters[i].position.y / 16;
        if (x1 == x && y1 == y) {
            return i;
        }
    }
    return 228;
}

int Map::check_game() {
    if (player.dead == 1) {
        return 1;
    }
    if (enemy_amount == 0) {
        return 2;
    }
    return 0;
}

