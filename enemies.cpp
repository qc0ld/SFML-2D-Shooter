#include "enemies.h"


Enemy::Enemy() : Unit() {}

Shooter::Shooter() : Enemy() {
    texture->loadFromFile("Textures/Units/Shooter.png");
}

void Shooter::attack_player() {
    return;
}

