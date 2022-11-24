#ifndef ENEMIES_H
#define ENEMIES_H

#include "unit.h"

class Enemy : public Unit {
protected:
    bool if_player_in_range(float x, float y);

    bool storage_in_range(float x, float y);

    void follow_player();

    virtual void attack_player() = 0;

    void open_storage(Storage &storage);

    void get_to_storage(float x, float y);
};

class Melee : public Enemy {
private:
    void attack_player() override;

    Melee();
};

class Shooter : public Enemy {
private:
    void attack_player() override;

    Shooter();
};

class Friendly : public Enemy {
private:
    void attack_player() override;

    Friendly();
};


#endif //ENEMIES_H
