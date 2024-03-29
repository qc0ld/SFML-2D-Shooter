#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "enemies.h"
#include "weapons.h"
#include <list>
#include <memory>
#include "list.h"

using namespace sf;
using namespace std;


class Cell {
public:
    Position position;
    Sprite sprite;
    Texture *texture;
    int type;
public:
    virtual void draw(RenderWindow &window, double x, double y);

    int get_type();
};


class Wall : public Cell {
public:
    Wall();
};


class Floor : public Cell {
public:
    Floor();
};

class Game {
public:
    int height;
    int width;
    int check;
    vector<unique_ptr<Enemy>> enemies;
    vector<shared_ptr<Item>> items;
    vector<shared_ptr<Weapon>> weapons;
    unique_ptr<Unit> player;
    Item *clip;
    View view;
    vector<vector<Cell>> map;
    Bullet bullet;
    my::list<Bullet> bullets;
    my::list<Bullet>::iterator it;
    Font font;
    Text *text;

public:
    Game();

    void update_enemies();

    void update_bullets();

    void update_player(int direction);

    void update_weapons();

    void fill_vector();

    void draw_map(RenderWindow &window);

    void draw(RenderWindow &window);

    void check_collision(unique_ptr<Unit> &unit);

    void check_enemy_collision(unique_ptr<Enemy> &unit);

    int get_type(int x, int y);

    int get_enemy(double x_pos, double y_pos);

    int get_item(double x_pos, double y_pos);

    int get_weapon(double x_pos, double y_pos);

    void check_game();

    void update();

    void update_view(RenderWindow &window);

    void pick_up_weapon();

    void drop_weapon();

    void player_attack(RenderWindow &window);

    void enemies_attack();

    void restart();

    void interface(RenderWindow &window);

    bool player_in_range(int number);

    void enemy_walk(int i);

    void update_items();

};

#endif //MAP_H
