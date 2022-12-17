#ifndef WEAPONS_H
#define WEAPONS_H

#include "items.h"
#include <stack>
#include <iostream>

using namespace std;
using namespace sf;


class Bullet {
public:
    double damage;
    Position position;
    double speed;
    Sprite sprite;
    Texture *texture;
    int check;
    int from;
    double angle;
    Vector2f world_pos;
public:
    Bullet();

    void update(RenderWindow &window);

    void set_up(RenderWindow &window, double x, double y);

    void enemy_set_up(double player_x, double player_y, double x, double y);

    void draw(RenderWindow &window);

    void move_x(double x);

    void move_y(double y);
};


class Weapon : public Item {
public:
    stack<Bullet> clip;
    int size;
    int max_size;
    double damage;
    int reload_timer;
    int reload_duration;
    bool shot;
    Text *text;
    Font font;
public:

    virtual void attack(RenderWindow &window, double x, double y) = 0;

    virtual void enemy_attack(double player_x, double player_y, double x, double y) = 0;

    int type() override { return WEAPON; }

};


class ak47 : public Weapon {
public:
    ak47();

    void attack(RenderWindow &window, double x, double y) override;

    void enemy_attack(double player_x, double player_y, double x, double y) override;

};


#endif //WEAPONS_H
