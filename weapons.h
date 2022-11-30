#ifndef WEAPONS_H
#define WEAPONS_H

#include "items.h"
#include "position.h"

using namespace sf;

class Weapon : Item {
public:
    Position position;
    double damage;
    double rate_of_fire;
    Sprite sprite;
    Texture texture;
public:
    void make_a_shot();
};

class ak47 : public Weapon {
public:
    ak47();

    void reload(Clip &clip);
};

class Bullet {
public:
    double damage;
    Position position;
    double speed;
    Sprite sprite;
    Texture texture;
    int check;
    double angle;
    Vector2f world_pos;

    Bullet();

    void shoot(double x, double y);

    void update(RenderWindow &window);

    void set_up(RenderWindow &window, double x, double y);

    void draw(RenderWindow &window);

    void move_x(double x);

    void move_y(double y);
};


class knife : public Weapon {
public:
    knife();
};

#endif //WEAPONS_H
