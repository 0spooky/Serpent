#ifndef TITLESCREEN_H_INCLUDED
#define TITLESCREEN_H_INCLUDED
#include <SFML/graphics.hpp>

class titlescreen{
    sf::Texture titlesnake;
    sf::Texture menuback;
    sf::Font manzanita;
public:
    void runtitlescreen(sf::RenderWindow &mwindow);
    sf::Sprite titlesnakesprite;
    sf::Sprite menubacksprite;
    sf::Text SNAKE;
    sf::Text Pressentertostart;
    titlescreen();
};

#endif // TITLESCREEN_H_INCLUDED
