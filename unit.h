#ifndef UNIT_H
#define UNIT_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "position.h"
#include "weapons.h"
#include <list>
#include <memory>
#include "vector"

using namespace sf;
using namespace std;



class Cell;

class Game;

class Unit {
public:
    Position position;
    double speed;
    int hp;
    int size;
    int direction;
    Item *inventory[10];
    shared_ptr<Weapon> weapon;
    bool dead;

    Sprite sprite;
    Texture *texture;
public:
    Unit();

    void move_x(double x);

    void move_y(double y);

    void draw(RenderWindow &window);

    void set_weapon(shared_ptr<Weapon>(&new_weapon));

    void drop_weapon();

    void set_current_item(int number);

    void get_damage(double damage);

    void set_position(double x, double y);

    void throw_item(int number);

    Position get_position();

    int get_dirrection();

};


#endif //UNIT_H
