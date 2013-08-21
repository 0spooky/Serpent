#ifndef BADFOOD_H_INCLUDED
#define BADFOOD_H_INCLUDED
#include <vector>
#include <SFML/graphics.hpp>

extern int gamemap[50][40];

class badfood{
    char badroll;
    int badfoodposx;
    int badfoodposy;
public:
    sf::Sprite badapple;
    void randomisenewpos(int headposx, int headposy);
    badfood();
};

class badfoodmanager{

public:
    bool isEatenQuery(int x, int y);
    int badfoodcount;
    std::vector<badfood> foodinventory;
    badfoodmanager();
};

#endif // BADFOOD_H_INCLUDED
