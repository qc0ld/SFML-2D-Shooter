#ifndef UNIT_H
#define UNIT_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "position.h"
#include "weapons.h"

using namespace sf;

class Unit {
public:
    Position position;
    double speed;
    int hp;
    int size;
    int direction;
    Item *inventory[10];
    Weapon* weapon;
    bool dead;

    Sprite sprite;
    Texture *texture;
public:
    Unit();

    void move_x(double x);

    void move_y(double y);

    void draw(RenderWindow &window);

    void set_weapon(Weapon *new_weapon);

    void set_current_item(int number);

    void get_damage(double damage);

    void set_position(double x, double y);

    void throw_item(int number);

    Position get_position();

    int get_dirrection();

};


#endif //UNIT_H
