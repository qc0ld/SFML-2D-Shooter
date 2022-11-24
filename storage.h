#ifndef STORAGE_H
#define STORAGE_H
#include "items.h"
#include <SFML/Graphics.hpp>

class Storage{
private:
    float x;
    float y;
    Item *storage[10];
    int size;
public:
    Storage();
    void draw(sf::RenderWindow &window);
};

#endif //STORAGE_H
