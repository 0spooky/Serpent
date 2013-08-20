#include <SFML/graphics.hpp>
#include "food.h"
#include <cstdlib>
#include <iostream>

Food::Food()
{
    foodposx = 22;
    foodposy = 20;
    gamemap[foodposx][foodposy] = 5;
    foodimage.setPosition(foodposx*24, foodposy*24);
    if(!eatsound.loadFromFile("assets/eat.wav"))
        std::cout << "ERR: File not found!\n";
    playeat.setBuffer(eatsound);
};

bool Food::isEatenQuery(int x, int y)
{
    if (gamemap [x][y] >= 2)
    {
        gamemap [x][y] = 1;
        playeat.play();
        foods_eaten++;
        foodposx = rand() % 30;                 //randomise x coordinate
        foodposy = rand() % 25;                 //randomise y coordinate
        gamemap [foodposx][foodposy] += 5;
        foodimage.setPosition(foodposx*24, foodposy*24);
        return true;
    }
    return false;
};

void Food::reinitialise()
{
    foodposx = rand() % 30;
    foodposy = rand() % 25;
    gamemap [foodposx][foodposy] += 5;
    foodimage.setPosition(foodposx*24, foodposy*24);
}
