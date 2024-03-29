#include "game.h"
#include "cmath"
#include <time.h>
#include <random>

using namespace std;


void create_map_sketch(vector<vector<char>> &my_map) {
    vector<vector<char>> map = {
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' ', 'M', ' ', ' ', 'B', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'A', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', 'A', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'M', ' ', '#', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', 'A', ' ', ' ', ' ', '#', ' ', ' ', 'B', ' ', 'M', ' ', ' ', ' ', ' ', '#'},
            {'#', '#', ' ', ' ', ' ', '#', '#', '#', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', 'P', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', ' ', ' ', '#', '#', '#'},
            {'#', ' ', ' ', ' ', ' ', 'B', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'E', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', 'M', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
            {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    };
    my_map = map;
}


Game::Game() : bullets(), enemies(), items(), weapons(), it(nullptr) {
    vector<vector<char>> map_sketch;
    create_map_sketch(map_sketch);

    player = make_unique<Unit>();

    check = 0;

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
                    enemies.push_back(make_unique<Shooter>());
                    weapons.push_back(make_shared<ak47>());
                    enemies[enemies.size() - 1]->set_position(i * 16, k * 16);
                    enemies[enemies.size() - 1]->set_weapon(weapons[weapons.size() - 1]);
                } else if (map_sketch[i][k] == 'P') {
                    player->set_position(i * 16, k * 16);
                    map[i][k].type = PLAYER;
                } else if (map_sketch[i][k] == 'A') {
                    weapons.push_back(make_shared<ak47>());
                    weapons[weapons.size() - 1]->set_position(i * 16, k * 16);
                } else if (map_sketch[i][k] == 'M') {
                    items.push_back(make_shared<Med_kit>());
                    items[items.size() - 1]->set_position(i * 16, k * 16);
                } else if (map_sketch[i][k] == 'B') {
                    items.push_back(make_shared<Ammo_box>());
                    items[items.size() - 1]->set_position(i * 16, k * 16);
                }
            }
        }
    }
    font.loadFromFile("Textures/Fonts/Font.ttf");
    text = new Text;
    text->setFont(font);
    text->setCharacterSize(12);
    text->setFillColor(Color::Yellow);

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

        enemy_walk(i);

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

void Game::enemy_walk(int i) {
    if (enemies.size() != 0) {
        if (enemies[i]->dead == 0) {
            int x = enemies[i]->position.x / 16;
            int y = enemies[i]->position.y / 16;

            if (enemies[i]->walk_timer == 0) {
                enemies[i]->direction = rand() % 4 + 1;
                enemies[i]->walk_timer = enemies[i]->walk_duration;
            } else {
                enemies[i]->walk_timer--;
            }
            enemies[i]->move_with_direction(enemies[i]->direction);
            check_enemy_collision(enemies[i]);
            if (x != enemies[i]->position.x && y != enemies[i]->position.y) {
                map[x][y].type = EMPTY;
            }
        }
    }
}


void Game::check_enemy_collision(unique_ptr<Enemy> &unit) {
    int x = unit->position.x / 16;
    int y = unit->position.y / 16;
    if (unit->direction == 1) {
        if ((map[x][y].get_type() == WALL ||
             map[x][y].get_type() == EMPTY && map[x][y + 1].get_type() == WALL)) {
            unit->move_x(unit->speed + 0.01);
        }
    } else if (unit->direction == 2) {
        if ((map[x][y].get_type() == WALL ||
             map[x][y].get_type() == EMPTY && map[x + 1][y].get_type() == WALL)) {
            unit->move_y(unit->speed + 0.01);
        }
    } else if (unit->direction == 3) {
        if ((map[x + 1][y].get_type() == WALL ||
             map[x + 1][y].get_type() != WALL && map[x + 1][y + 1].get_type() == WALL)) {
            unit->move_x(-unit->speed - 0.01);
        }
    } else if (unit->direction == 4) {
        if ((map[x][y + 1].get_type() == WALL ||
             map[x][y + 1].get_type() != WALL && map[x + 1][y + 1].get_type() == WALL)) {
            unit->move_y(-unit->speed - 0.01);
        }
    }
}

void Game::update_items() {
    int x1 = player->position.x / 16;
    int y1 = player->position.y / 16;
    int x2, y2;

    for (int i = 0; i < items.size(); i++) {
        x2 = items[i]->position.x / 16;
        y2 = items[i]->position.y / 16;
        if (x1 == x2 && y1 == y2) {
            items[i]->use(player);
            if (items[i]->check == 1) {
                items.erase(items.begin() + i);
            }
        }
    }
}


void Game::check_collision(unique_ptr<Unit> &unit) {
    int x = unit->position.x / 16;
    int y = unit->position.y / 16;
    if (unit->direction == 1) {
        if ((map[x][y].get_type() == WALL ||
             map[x][y].get_type() == EMPTY && map[x][y + 1].get_type() == WALL) ||
            (map[x][y].get_type() == ENEMY ||
             map[x][y].get_type() == EMPTY && map[x][y + 1].get_type() == ENEMY)) {
            unit->move_x(unit->speed + 0.01);
        }
    }
    if (unit->direction == 2) {
        if ((map[x][y].get_type() == WALL ||
             map[x][y].get_type() == EMPTY && map[x + 1][y].get_type() == WALL) ||
            (map[x][y].get_type() == ENEMY ||
             map[x][y].get_type() == EMPTY && map[x + 1][y].get_type() == ENEMY)) {
            unit->move_y(unit->speed + 0.01);
        }
    }
    if (unit->direction == 3) {
        if ((map[x + 1][y].get_type() == WALL ||
             map[x + 1][y].get_type() != WALL && map[x + 1][y + 1].get_type() == WALL) ||
            map[x + 1][y].get_type() == ENEMY ||
            map[x + 1][y].get_type() == EMPTY && map[x + 1][y + 1].get_type() == ENEMY) {
            unit->move_x(-unit->speed - 0.01);
        }
    }
    if (unit->direction == 4) {
        if ((map[x][y + 1].get_type() == WALL ||
             map[x][y + 1].get_type() != WALL && map[x + 1][y + 1].get_type() == WALL) ||
            (map[x][y + 1].get_type() == ENEMY ||
             map[x][y + 1].get_type() == EMPTY && map[x + 1][y + 1].get_type() == ENEMY)) {
            unit->move_y(-unit->speed - 0.01);
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
        x = it->position.x / 16;
        y = it->position.y / 16;
        it->move_x(sin(it->angle) * it->speed);
        it->move_y(cos(it->angle) * it->speed);
        if (map[x][y].get_type() == WALL) {
            bullets.erase(it);
        } else if (map[x][y].get_type() == ENEMY) {
            if (it->from != ENEMY) {
                if (get_enemy(it->position.x, it->position.y) != 228) {
                    enemies[get_enemy(it->position.x, it->position.y)]->get_damage(it->damage);
                    bullets.erase(it);
                }
            }
        } else {
            x1 = player->position.x / 16;
            y1 = player->position.y / 16;
            if (x == x1 && y == y1) {
                if (it->from != PLAYER) {
                    player->get_damage(it->damage);
                    bullets.erase(it);
                }
            }
        }
        ++it;
    }
}


void Game::update_player(int direction) {
    check_collision(player);
    if (player->weapon) {
        player->weapon->set_position(player->position.x + 3, player->position.y + 3);
    }
    player->move_with_direction(direction);
    player->direction = direction;
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
    if (player->weapon) {
        if (player->weapon->check == 1) {
            if (player->weapon->reload_timer == 0) {
                player->weapon->shot = 0;
            } else {
                player->weapon->reload_timer--;
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
    if (player->dead == 1) {
        check = 1;
    }
    if (enemies.size() == 0) {
        check = 2;
    }
}


void Game::update_view(RenderWindow &window) {
    window.clear();
    view.setCenter(player->position.x + 8, player->position.y + 8);
    view.setSize(320, 180);
    window.setView(view);
}

void Game::update() {
    update_enemies();
    enemies_attack();

    update_bullets();

    update_items();

    update_weapons();

    check_game();
    if (check == 1) {
        restart();
    }
}

void Game::enemies_attack() {
    for (int i = 0; i < enemies.size(); i++) {
        if (player_in_range(i)) {
            if (enemies[i]->weapon) {
                if (enemies[i]->weapon->shot == 0) {
                    if (enemies[i]->weapon->type() == WEAPON) {
                        enemies[i]->weapon->enemy_attack(player->position.x, player->position.y,
                                                         enemies[i]->position.x,
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
}

bool Game::player_in_range(int number) {
    int lenght = sqrt(pow(player->position.x - enemies[number]->position.x, 2) +
                      pow(player->position.y - enemies[number]->position.y, 2)) / 16;
    if (lenght > 5) {
        return false;
    }
    return true;
}

void Game::draw(RenderWindow &window) {
    int i = 0;
    draw_map(window);
    player->draw(window);
    for (i = 0; i < enemies.size(); i++) {
        enemies[i]->draw(window);
    }
    for (i = 0; i < weapons.size(); i++) {
        weapons[i]->draw(window);
    }
    for (i = 0; i < items.size(); i++) {
        items[i]->draw(window);
    }
    for (it = bullets.begin(); it != bullets.end(); ++it) {
        it->draw(window);
    }
    interface(window);
    window.display();
}

void Game::pick_up_weapon() {
    if (get_weapon(player->position.x, player->position.y) != 228) {
        if (weapons[get_weapon(player->position.x, player->position.y)]->check == 0) {
            if (weapons[get_weapon(player->position.x, player->position.y)]->type() == WEAPON) {
                weapons[get_weapon(player->position.x, player->position.y)]->check = 1;
                player->set_weapon(weapons[get_weapon(player->position.x, player->position.y)]);
            }
        }
    }
}


void Game::drop_weapon() {
    player->drop_weapon();
}

void Game::player_attack(RenderWindow &window) {
    if (player->weapon) {
        if (player->weapon->shot == 0) {
            if (player->weapon->type() == WEAPON) {
                player->weapon->attack(window, player->position.x, player->position.y);
                if (!player->weapon->clip.empty()) {
                    player->weapon->shot = 1;
                    player->weapon->reload_timer = player->weapon->reload_duration;
                    player->weapon->clip.top().from = PLAYER;
                    bullets.push_back(player->weapon->clip.top());
                    player->weapon->clip.pop();
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
    for (int i = items.size() - 1; i > -1; i--) {
        items.erase(items.begin() + i);
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
            } else if (map_sketch[i][k] == 'P') {
                player->set_position(i * 16, k * 16);
                player->dead = 0;
                player->hp = 100;
                map[i][k].type = PLAYER;
            } else if (map_sketch[i][k] == 'A') {
                weapons.push_back(make_shared<ak47>());
                weapons[weapons.size() - 1]->set_position(i * 16, k * 16);
            } else if (map_sketch[i][k] == 'M') {
                items.push_back(make_shared<Med_kit>());
                items[items.size() - 1]->set_position(i * 16, k * 16);
            } else if (map_sketch[i][k] == 'B') {
                items.push_back(make_shared<Ammo_box>());
                items[items.size() - 1]->set_position(i * 16, k * 16);
            }
        }
    }
}

void Game::interface(RenderWindow &window) {
    if (player->weapon) {
        if (player->weapon->type() == WEAPON) {
            player->weapon->text->setString(to_string(player->weapon->size) + " / 30");

            player->weapon->text->setPosition(player->position.x + 110, player->position.y + 75);

            window.draw(*player->weapon->text);
        }
    }
    if (check != 2) {
        text->setString(to_string(player->hp));
        text->setPosition(player->position.x - 140, player->position.y + 75);
    } else {
        text->setCharacterSize(18);
        text->setString("You won! press R to restart");
        text->setPosition(player->position.x - 100, player->position.y - 40);
    }
    window.draw(*text);
}
