#ifndef WEAPONS_H
#define WEAPONS_H

#include "items.h"

using namespace sf;

class Weapon : public Item {
public:
    double damage;
    double rate_of_fire;
public:

    virtual void attack() = 0;
};

class ak47 : public Weapon {
public:
    ak47();

    void attack() override;
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

    void update(RenderWindow &window);

    void set_up(RenderWindow &window, double x, double y);

    void draw(RenderWindow &window);

    void move_x(double x);

    void move_y(double y);
};


/*class knife : public Weapon {
public:
    knife();
};*/

#endif //WEAPONS_H
