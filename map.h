#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "enemies.h"
#include "weapons.h"
#include "array"

using namespace sf;
using namespace std;

enum {
    WALL,
    EMPTY,
    ENEMY,
    PLAYER
};


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


class Map {
public:
    int height;
    int width;
    array<Shooter, 4> shooters;
    int enemy_amount;
    Unit player;
    vector<vector<Cell>> map;
    Bullet bullet;
public:

    Map();

    void update_enemy();

    void update_bullet();

    void update_player(int direction);

    void fill_vector();

    void draw(RenderWindow &window);

    void check_collision();

    int get_type(int x, int y);

    int get_enemy(double x, double y);

    int check_game();
};


#endif //MAP_H
