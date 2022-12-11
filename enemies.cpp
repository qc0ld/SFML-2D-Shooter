#include "enemies.h"


Shooter::Shooter() : Enemy() {
    texture->loadFromFile("Textures/Units/Shooter.png");
}

void Shooter::attack_player() {
    return;
}

