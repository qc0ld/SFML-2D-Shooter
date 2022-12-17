#include "game.h"
#include "cmath"

using namespace std;


void create_map_sketch(vector<vector<char>> &my_map) {
    vector<vector<char>> map = {
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', 'A', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', '#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', '#', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', 'A', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', 'E', ' ', ' ', ' ', ' ', 'P', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    };
    my_map = map;
}


Game::Game() : player(), bullets(), enemies(), items(), weapons(), it(nullptr), itr(nullptr) {
    vector<vector<char>> map_sketch;
    create_map_sketch(map_sketch);
    check = 0;
    height = map_sketch.size();
    width = map_sketch[0].size();
    vector<vector<Cell>> a(height, vector<Cell>(width));
    map = a;

    player.hp = 1000;
    for (int i = 0; i < height; ++i) {
        for (int k = 0; k < width; ++k) {
            if (map_sketch[i][k] == '#') {
                Wall wall;
                map[i][k] = wall;
            } else {
                Floor floor;
                map[i][k] = floor;
                if (map_sketch[i][k] == 'E') {
                    enemies.push_back(make_unique<Shooter>());
                    weapons.push_back(make_shared<ak47>());
                    enemies[enemies.size() - 1]->set_position(i * 16, k * 16);
                    enemies[enemies.size() - 1]->set_weapon(weapons[weapons.size() - 1]);
                } else if (map_sketch[i][k] == 'P') {
                    player.set_position(i * 16, k * 16);
                    map[i][k].type = PLAYER;
                } else if (map_sketch[i][k] == 'A') {
                    weapons.push_back(make_shared<ak47>());
                    weapons[weapons.size() - 1]->set_position(i * 16, k * 16);
                }
            }
        }
    }
    font.loadFromFile("Textures/Fonts/Font.ttf");
    player_hp = new Text;
    player_hp->setFont(font);
    player_hp->setCharacterSize(12);
    player_hp->setFillColor(Color::Yellow);
}

void Game::draw_map(RenderWindow &window) {
    for (int i = 0; i < height; ++i) {
        for (int k = 0; k < width; ++k) {
            map[i][k].draw(window, i * 16, k * 16);
        }
    }
}

void Game::update_enemies() {
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i]->weapon) {
            if (enemies[i]->dead == 0) {
                enemies[i]->weapon->set_position(enemies[i]->position.x + 3, enemies[i]->position.y + 3);
            }
        }
        if (enemies[i]->dead == 1) {
            if (enemies[i]->weapon) {
                enemies[i]->weapon->check = 0;
            }
            map[enemies[i]->position.x / 16][enemies[i]->position.y / 16].type = EMPTY;
            enemies.erase(enemies.begin() + i);
        } else {
            map[enemies[i]->position.x / 16][enemies[i]->position.y / 16].type = ENEMY;
        }
    }
}

void Game::check_collision() {
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

void Game::update_bullets() {
    int x, y, x1, y1;
    it = bullets.begin();
    while (it != bullets.end()) {
        x = it.value().position.x / 16;
        y = it.value().position.y / 16;
        it.value().move_x(sin(it.value().angle) * it.value().speed);
        it.value().move_y(cos(it.value().angle) * it.value().speed);
        if (map[x][y].get_type() == WALL) {
            bullets.erase(it);
        } else if (map[x][y].get_type() == ENEMY) {
            if (it.value().from != ENEMY) {
                if (get_enemy(it.value().position.x, it.value().position.y) != 228) {
                    enemies[get_enemy(it.value().position.x, it.value().position.y)]->get_damage(it.value().damage);
                    bullets.erase(it);
                }
            }
        } else {
            x1 = player.position.x / 16;
            y1 = player.position.y / 16;
            if (x == x1 && y == y1) {
                if (it.value().from != PLAYER) {
                    player.get_damage(it.value().damage);
                    bullets.erase(it);
                }
            }
        }
        ++it;
    }
}


void Game::update_player(int direction) {
    check_collision();
    if (player.weapon) {
        player.weapon->set_position(player.position.x + 3, player.position.y + 3);
    }
    int x = player.position.x / 16;
    int y = player.position.y / 16;
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

int Game::get_enemy(double x_pos, double y_pos) {
    int x = x_pos / 16;
    int y = y_pos / 16;
    int x1, y1;
    for (int i = 0; i < enemies.size(); i++) {
        x1 = enemies[i]->position.x / 16;
        y1 = enemies[i]->position.y / 16;
        if (x1 == x && y1 == y) {
            return i;
        }
    }
    return 228;
}

int Game::get_item(double x_pos, double y_pos) {
    int x = x_pos / 16;
    int y = y_pos / 16;
    int x1, y1;
    for (int i = 0; i < 3; i++) {
        x1 = items[i]->position.x / 16;
        y1 = items[i]->position.y / 16;
        if (x1 == x && y1 == y) {
            return i;
        }
    }
    return 228;
}

int Game::get_weapon(double x_pos, double y_pos) {
    int x = x_pos / 16;
    int y = y_pos / 16;
    int x1, y1;
    for (int i = 0; i < weapons.size(); i++) {
        x1 = weapons[i]->position.x / 16;
        y1 = weapons[i]->position.y / 16;
        if (x1 == x && y1 == y) {
            return i;
        }
    }
    return 228;
}


void Game::update_weapons() {
    if (player.weapon) {
        if (player.weapon->check == 1) {
            if (player.weapon->reload_timer == 0) {
                player.weapon->shot = 0;
            } else {
                player.weapon->reload_timer--;
            }
        }
    }
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i]->weapon) {
            if (enemies[i]->weapon->check == 1) {

                if (enemies[i]->weapon->reload_timer == 0) {
                    enemies[i]->weapon->shot = 0;
                } else {
                    enemies[i]->weapon->reload_timer--;
                }
            }
        }
    }
}


void Game::check_game() {
    if (player.dead == 1) {
        check = 1;
    }
    if (enemies.size() == 0) {
        check = 2;
    }
}


void Game::update_view(RenderWindow &window) {
    window.clear();
    view.setCenter(player.position.x + 8, player.position.y + 8);
    view.setSize(320, 180);
    window.setView(view);
}

void Game::update() {
    update_enemies();
     enemies_attack();
    update_bullets();
    update_weapons();
    check_game();
    if (check == 1) {
        restart();
    }
}

void Game::enemies_attack() {
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i]->weapon) {
            if (enemies[i]->weapon->shot == 0) {
                if (enemies[i]->weapon->type() == WEAPON) {
                    enemies[i]->weapon->enemy_attack(player.position.x, player.position.y, enemies[i]->position.x,
                                                     enemies[i]->position.y);
                    if (!enemies[i]->weapon->clip.empty()) {
                        enemies[i]->weapon->shot = 1;
                        enemies[i]->weapon->reload_timer = enemies[i]->weapon->reload_duration;
                        enemies[i]->weapon->clip.top().from = ENEMY;

                        bullets.push_back(enemies[i]->weapon->clip.top());
                        enemies[i]->weapon->clip.pop();
                    }
                }
            }
        }
    }
}

void Game::draw(RenderWindow &window) {
    draw_map(window);
    player.draw(window);
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->draw(window);
    }
    for (int i = 0; i < weapons.size(); i++) {
        weapons[i]->draw(window);
    }
    for (itr = bullets.begin(); itr != bullets.end(); ++itr) {
        itr.value().draw(window);
    }
    interface(window);
    window.display();
}

void Game::pick_up_weapon() {
    if (get_weapon(player.position.x, player.position.y) != 228) {
        if (weapons[get_weapon(player.position.x, player.position.y)]->check == 0) {
            if (weapons[get_weapon(player.position.x, player.position.y)]->type() == WEAPON) {
                weapons[get_weapon(player.position.x, player.position.y)]->check = 1;
                player.set_weapon(weapons[get_weapon(player.position.x, player.position.y)]);
            }
        }
    }
}

void Game::drop_weapon() {
    player.drop_weapon();
}

void Game::player_attack(RenderWindow &window) {
    if (player.weapon) {
        if (player.weapon->shot == 0) {
            if (player.weapon->type() == WEAPON) {
                player.weapon->attack(window, player.position.x, player.position.y);
                if (!player.weapon->clip.empty()) {
                    player.weapon->shot = 1;
                    player.weapon->reload_timer = player.weapon->reload_duration;
                    player.weapon->clip.top().from = PLAYER;
                    bullets.push_back(player.weapon->clip.top());
                    player.weapon->clip.pop();
                }
            }
        }
    }
}

void Game::restart() {
    vector<vector<char>> map_sketch;
    create_map_sketch(map_sketch);
    check = 0;
    for (int i = enemies.size() - 1; i > -1; i--) {
        enemies.erase(enemies.begin() + i);
    }
    for (int i = weapons.size() - 1; i > -1; i--) {
        weapons.erase(weapons.begin() + i);
    }
    for (int i = 0; i < height; ++i) {
        for (int k = 0; k < width; ++k) {
            if (map_sketch[i][k] == '#') {
                map[i][k].type = WALL;
            } else if (map_sketch[i][k] == ' ') {
                map[i][k].type = EMPTY;
            } else if (map_sketch[i][k] == 'E') {
                enemies.push_back(make_unique<Shooter>());
                weapons.push_back(make_shared<ak47>());
                enemies[enemies.size() - 1]->set_position(i * 16, k * 16);
                enemies[enemies.size() - 1]->set_weapon(weapons[weapons.size() - 1]);
                enemy_amount++;
            } else if (map_sketch[i][k] == 'P') {
                player.set_position(i * 16, k * 16);
                player.dead = 0;
                player.hp = 100;
                map[i][k].type = PLAYER;
            } else if (map_sketch[i][k] == 'A') {
                weapons.push_back(make_shared<ak47>());
                weapons[weapons.size() - 1]->set_position(i * 16, k * 16);
            }
        }
    }
}

void Game::interface(RenderWindow &window) {
    if (player.weapon) {
        if (player.weapon->type() == WEAPON) {
            player.weapon->text->setString(to_string(player.weapon->size) + " / 30");

            player.weapon->text->setPosition(player.position.x + 110, player.position.y + 75);

            window.draw(*player.weapon->text);
        }
    }
    player_hp->setString(to_string(player.hp));
    player_hp->setPosition(player.position.x - 140, player.position.y + 75);
    window.draw(*player_hp);
}
