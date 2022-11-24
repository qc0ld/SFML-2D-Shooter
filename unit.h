#ifndef UNIT_H
#define UNIT_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "items.h"
#include "map.h"
#include "storage.h"
#include "weapons.h"

using namespace sf;


class Bullet {
public:
    Position position;
    float speed;
    Sprite sprite;
    Texture texture;
    int check;
    float angle;
    Vector2f world_pos;

    Bullet();

    void shoot(float x, float y, vector<vector<Cell>> &map);

    void update(RenderWindow &window, Map &map);

    void draw(RenderWindow &window);
};

class Unit {
public:
    Position position;
    const float speed;
    int hp;
    int size;
    int direction;
    Item *inventory[10];
    Weapon *curent_item;
    Bullet bullet;
    bool dead;

    Sprite sprite;
    Texture texture;
public:
    Unit();

    void draw(RenderWindow &window);

    void check_collision(vector<vector<Cell>> &map);

    virtual void update(RenderWindow &window, Map &map);

    void pick_up_item(Item &item);

    void set_current_item(int number);

    void get_damage(double damage);

    void throw_item(int number);

    Position get_position();

    int get_dirrection();

};


#endif //UNIT_H
