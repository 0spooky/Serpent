#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED
#include <SFML/graphics.hpp>
#include <SFML/audio.hpp>
#include <vector>

extern int gamemap[50][40];

class Food{
    int foodposx;
    int foodposy;//Current position of the food
    sf::SoundBuffer eatsound;
    sf::Sound playeat;
public:
    Food();
    int foods_eaten = 0; //Number of foods that have been eaten
    sf::Sprite foodimage;
    bool isEatenQuery(int x, int y);
    void reinitialise();
};

#endif // FOOD_H_INCLUDED
