#include <SFML/graphics.hpp>
#include <SFML/audio.hpp>
#include <iostream>
#include "food.h"
#include "snakebody.h"
#include "titlescreen.h"
#include <vector>

int gamemap[50][40]; //the playing field.  Snake is defined by 1's, food is defined by >=2's, and empty space is defined by 0's

void debugmap(){
    for(int test = 0; test < 20; test++)
    {
        for(int testk = 0; testk < 30; testk++)
        {
            std::cout << gamemap[testk][test];
        }
        std::cout << std::endl;
    }
}  //debug stuff

int main()
{
    bool randset = false;  //Has the random seed been randomised?
    bool gamerunning = false;

    int presskey = 0; //Later used to save pressed key and used for math

    sf::RenderWindow window(sf::VideoMode(720, 600), "Snake!", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(15); //Basically sets the speed of the fame
    window.setMouseCursorVisible(false);

    sf::Clock clock; //only used for
    sf::Time time;   //random seed

    sf::Texture snaketexture;
    if(!snaketexture.loadFromFile("assets/snakebody.png"))
        std::cout << "ERR: File not found!\n";

    sf::Texture applefood;
    if(!applefood.loadFromFile("assets/apple2.png"))
        std::cout << "ERR: File not found!\n";

    sf::Texture background;
    if(!background.loadFromFile("assets/pattern.jpg"))
        std::cout << "ERR: File not found!\n";

    sf::Sprite background_sprite;
    background_sprite.setTexture(background);

    titlescreen themenu;

    Food apple;     //initialise the food
    apple.foodimage.setTexture(applefood);  //too lazy to put this in the Food class

    snakebodymanager thesnake;
    snakebody head;
    head.body.setTexture(snaketexture);
    thesnake.totalbody.push_back(head);

    sf::Music gametheme;
    if(!gametheme.openFromFile("assets/loop.wav"))
        std::cout << "ERR: File not found!\n";
    gametheme.setLoop(true);
    gametheme.play();

    while(window.isOpen())
    {
        if(gamerunning == false)
        {
            themenu.runtitlescreen(window);
            for(int i = 0; i < 50; i++)
            {
                for(int j = 0; j < 40; j++)
                    gamemap[i][j] = 0;
            }
            thesnake.bodycount = 1;
            thesnake.notlosing = true;
            thesnake.totalbody.clear();
            thesnake.totalbody.push_back(head);
            apple.reinitialise();
            gamerunning = true;
        }
        //debugmap();                               //MAKE SURE YOU REMOVE BEFORE RELEASE
        window.clear();
        time = clock.getElapsedTime();            //only used for random seed

        sf::Event event;
        while(window.pollEvent(event))
        {
            switch (event.type)
            {
            case (sf::Event::Closed):
                window.close();
                break;
            case (sf::Event::KeyPressed):
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    presskey = 1;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    presskey = 2;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    presskey = 3;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    presskey = 4;
                break;
            default:
                break;
            }
        }
        window.draw(background_sprite);
        if (apple.foods_eaten == 1 && randset == false)  //setting the random seed
            {
                randset = true;                          //random seed now set
                srand(time.asMilliseconds());            //this is the random seed
            }

        if(apple.isEatenQuery(thesnake.totalbody[0].partposx, thesnake.totalbody[0].partposy))   //Test if food is eaten.  If so, spawn new food and...
        {
            thesnake.bodygrow();                                                                 //grow snake body
        }
        thesnake.headmovedirection(presskey);                                                    //register and update movement
        if(thesnake.notlosing == false)                                                          //run during losing conditions
            gamerunning = false;
        thesnake.totalbody[0].body.setPosition(thesnake.totalbody[0].partposx*24, thesnake.totalbody[0].partposy*24); //lock in head sprite position, apparently
        window.draw(apple.foodimage);
        window.draw(thesnake.totalbody[0].body);
        for(int i = 1; i < thesnake.bodycount; i++)                                              //draw every segment of snake body
        {
            window.draw(thesnake.totalbody[i].body);
        }
        window.display();
    }
    return 0;
}
