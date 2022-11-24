#ifndef ITEMS_H
#define ITEMS_H

#define CAPACITY 10


class Item {
protected:
    float x;
    float y;
};


class Clip : public Item {
private:
    int clip_capacity;
    int size;
public:
    Clip();

};


class first_aid_kit : public Item {
public:
    first_aid_kit();

    void use_first_aid_kit();
};


#endif //ITEMS_H
