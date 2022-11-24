#ifndef WEAPONS_H
#define WEAPONS_H

#include "items.h"

class Weapon {
protected:
    double damage;
    double rate_of_fire;

    void make_a_shot();
};

class ak47 : public Weapon {
public:
    ak47();

    void reload(Clip &clip);
};

class knife : public Weapon {
public:
    knife();
};

#endif //WEAPONS_H
