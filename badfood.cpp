#include "badfood.h"
#include <SFML/graphics.hpp>
#include <cstdlib>
#include <cmath>

badfood::badfood()
{
    badroll = 0;
    badfoodposx = 40;
    badfoodposy = 30;
    gamemap[40][30] = 10;
    badapple.setPosition(badfoodposx * 24, badfoodposy * 24);
}

bool badfoodmanager::isEatenQuery(int x, int y)
{
    if(gamemap[x][y] == 10)
        return true;
    return false;
}

void badfood::randomisenewpos(int headposx, int headposy)
{
    while(gamemap[badfoodposx][badfoodposy] != 0 && badroll != 1)
        {
        badroll = 0;
        badfoodposx = rand() % 30;                 //randomise x coordinate
        badfoodposy = rand() % 25;                 //randomise y coordinate
        if(abs(badfoodposx - headposx) < 5 && abs(badfoodposy - headposy) < 5)
            badroll = 1;
        }
    badapple.setPosition(badfoodposx * 24, badfoodposy * 24);
    gamemap[badfoodposx][badfoodposy] = 10;
}

badfoodmanager::badfoodmanager()
{
    badfoodcount = 0;
}
