#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

enum {
    WALL,
    EMPTY
};

typedef struct Position Position;
struct Position {
    float x;
    float y;
};

class Cell {
public:
    Position position;
    Sprite sprite;
    Texture *texture;
    int type;
public:
    virtual int get_type();

    virtual void draw(RenderWindow &window, float x, float y);

};

class Wall : public Cell {
public:
    Wall();
};

class Floor : public Cell {
public:
    Floor();
};

class Map {
protected:
    int height;
    int width;
public:
    vector<vector<Cell>> map;

    Map();

    void fill_vector();

    void draw(RenderWindow &window);

    vector<vector<char>> get_map();

};


#endif //MAP_H
