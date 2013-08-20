#ifndef SNAKEBODY_H_INCLUDED
#define SNAKEBODY_H_INCLUDED
#include <SFML/graphics.hpp>
#include <vector>

extern int gamemap[50][40];

class snakebody{
public:
    int partposx;
    int partposy;
    sf::Sprite body;
    snakebody();
    snakebody(float partposx, float partposy);
};

class snakebodymanager{
public:
    bool notlosing;
    int bodycount;
    std::vector<snakebody> totalbody;
    void bodygrow();
    int headmovedirection(int direction, sf::Texture &snaketexture);
    snakebodymanager();
};

#endif // SNAKEBODY_H_INCLUDED
