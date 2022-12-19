#include "enemies.h"


Shooter::Shooter() : Enemy() {
    texture->loadFromFile("Textures/Units/Shooter.png");
    direction = 3;
    speed = 0.1;

}

void Shooter::attack_player(RenderWindow &window, double x, double y) {

}
