#ifndef ENEMIES_H
#define ENEMIES_H

#include "unit.h"

class Enemy : public Unit {
public:
    Enemy();

    bool if_player_in_range(double x, double y);

    bool storage_in_range(double x, double y);

    void follow_player();

    virtual void attack_player() = 0;

    void get_to_storage(double x, double y);
};

class Shooter : public Enemy {
public:
    Shooter();

    void attack_player() override;
};

/*
class Melee : public Enemy {
public:
    void attack_player() override;

    Melee();
};



class Friendly : public Enemy {
public:
    void attack_player() override;

    Friendly();
};*/


#endif //ENEMIES_H
