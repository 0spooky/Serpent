 #include "titlescreen.h"
 #include <SFML/graphics.hpp>
 #include "snakebody.h"
 #include <iostream>

void titlescreen::runtitlescreen(sf::RenderWindow &mwindow){
    bool menurunning = true;
    while(menurunning == true)
        {
            mwindow.clear();
            if(!mwindow.isOpen())
                menurunning = false;
            sf::Event event;
            while(mwindow.pollEvent(event))
            {
                switch (event.type)
                {
                case (sf::Event::Closed):
                    mwindow.close();
                    break;
                case (sf::Event::KeyPressed):
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                        menurunning = false;
                    break;
                default:
                    break;
                }
            }
            mwindow.draw(menubacksprite);
            mwindow.draw(titlesnakesprite);
            mwindow.draw(SNAKE);
            mwindow.draw(Pressentertostart);
            mwindow.display();
        }
 }

titlescreen::titlescreen()
{
    if(!titlesnake.loadFromFile("assets/snake.png"))
        std::cout << "ERR: File not found!\n";
    if(!menuback.loadFromFile("assets/menuback.jpg"))
        std::cout << "ERR: File not found!\n";
    titlesnakesprite.setTexture(titlesnake);
    titlesnakesprite.setPosition(180, 180);
    menubacksprite.setTexture(menuback);
    menubacksprite.setColor(sf::Color(150, 200, 200, 255));
    if(!manzanita.loadFromFile("assets/MANZANIT.ttf"))
        std::cout << "ERR: File not found!\n";
    SNAKE.setString("SNAKE");
    SNAKE.setFont(manzanita);
    SNAKE.setPosition(280,100);
    SNAKE.setCharacterSize(128);
    Pressentertostart.setString("Press ENTER to start!");
    Pressentertostart.setFont(manzanita);
    Pressentertostart.setCharacterSize(64);
    Pressentertostart.setPosition(220,400);
}
