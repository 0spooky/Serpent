#include <SFML/graphics.hpp>
#include <SFML/audio.hpp>
#include <iostream>
#include "food.h"
#include "snakebody.h"
#include "titlescreen.h"
#include "badfood.h"
#include <vector>
#include <string>
#include <sstream>

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

template <typename T>
std::string to_string(const T& value)
{
    std::ostringstream oss;
    oss << value;

    return oss.str();
}

int main()
{
    int score = 0;
    bool randset = false;  //Has the random seed been randomised?
    bool gamerunning = false;

    int presskey = 0; //Later used to save pressed key and used for math

    sf::RenderWindow window(sf::VideoMode(720, 600), "Snake!", sf::Style::Close | sf::Style::Titlebar);
    window.setFramerateLimit(15); //Basically sets the speed of the fame
    window.setMouseCursorVisible(false);

    sf::Clock clock; //only used for
    sf::Time time;   //random seed

    sf::Texture snakeheadtexture;
    if(!snakeheadtexture.loadFromFile("assets/snakehead.png"))
        std::cout << "ERR: File not found!\n";

    sf::Texture snaketexture;
    if(!snaketexture.loadFromFile("assets/snakebody.png"))
        std::cout << "ERR: File not found!\n";

    sf::Texture applefood;
    if(!applefood.loadFromFile("assets/apple2.png"))
        std::cout << "ERR: File not found!\n";

    sf::Texture badapplefood;
    if(!badapplefood.loadFromFile("assets/greenapple.gif"))
        std::cout << "ERR: File not found!\n";

    sf::Texture background;
    if(!background.loadFromFile("assets/pattern.jpg"))
        std::cout << "ERR: File not found!\n";

    sf::Sprite background_sprite;
    background_sprite.setTexture(background);

    titlescreen themenu;

    Food apple;     //initialise the food
    apple.foodimage.setTexture(applefood);  //too lazy to put this in the Food class

    badfoodmanager allbadfood;
    badfood greenapple;
    greenapple.badapple.setTexture(badapplefood);

    snakebodymanager thesnake;
    snakebody head;
    head.body.setTexture(snakeheadtexture);
    head.body.setRotation(180);
    head.body.setOrigin(24,24);
    thesnake.totalbody.push_back(head);

    sf::Music gametheme;
    if(!gametheme.openFromFile("assets/loop.wav"))
        std::cout << "ERR: File not found!\n";
    gametheme.setVolume(33);
    gametheme.setLoop(true);
    gametheme.play();

    sf::SoundBuffer diesound;
    if(!diesound.loadFromFile("assets/beep-3.wav"))
        std::cout << "ERR: File not found!\n";

    sf::Sound diesoundplay;
    diesoundplay.setBuffer(diesound);

    sf::Font velocette;
    if(!velocette.loadFromFile("assets/Velocette.ttf"))
        std::cout << "ERR: File not found!\n";

    sf::Text thescore;
    thescore.setFont(velocette);
    thescore.setCharacterSize(64);
    thescore.setPosition(655, 0);
    thescore.setString("0");

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
            presskey = 0;

            thesnake.bodycount = 1;
            thesnake.notlosing = true;
            thesnake.totalbody.clear();
            thesnake.totalbody.push_back(head);
            thesnake.totalbody[0].body.setRotation(180);
            thesnake.totalbody[0].body.setOrigin(24,24);
            apple.reinitialise();
            allbadfood.badfoodcount = 0;
            allbadfood.foodinventory.clear();
            gamerunning = true;
        }
        debugmap();                               //MAKE SURE YOU REMOVE BEFORE RELEASE
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
                if(presskey != 1 && presskey != 2)
                {
                    if(event.key.code == sf::Keyboard::Up)
                    {
                        presskey = 1;
                        thesnake.totalbody[0].body.setRotation(0);
                        thesnake.totalbody[0].body.setOrigin(0,0);
                    }
                    else if(event.key.code == sf::Keyboard::Down)
                    {
                        presskey = 2;
                        thesnake.totalbody[0].body.setRotation(180);
                        thesnake.totalbody[0].body.setOrigin(24,24);
                    }
                }
                if(presskey != 3 && presskey != 4)
                {
                    if(event.key.code == sf::Keyboard::Right)
                    {
                        presskey = 3;
                        thesnake.totalbody[0].body.setRotation(90);
                        thesnake.totalbody[0].body.setOrigin(0,24);
                    }
                    else if(event.key.code == sf::Keyboard::Left)
                    {
                        presskey = 4;
                        thesnake.totalbody[0].body.setRotation(270);
                        thesnake.totalbody[0].body.setOrigin(24,0);
                    }
                }
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
            score+=10;
            if (score == 100)
                thescore.setPosition(635,0);
            if (score == 200)
                thescore.setPosition(625,0);
            thescore.setString(to_string(score));
            thesnake.bodygrow();                                                                 //grow snake body
            allbadfood.foodinventory.push_back(greenapple);
            allbadfood.foodinventory[allbadfood.badfoodcount].randomisenewpos(thesnake.totalbody[0].partposx, thesnake.totalbody[0].partposy);
            allbadfood.badfoodcount++;

       }
        thesnake.headmovedirection(presskey, snaketexture);                                      //register and update movement

        if(allbadfood.isEatenQuery(thesnake.totalbody[0].partposx, thesnake.totalbody[0].partposy))
            thesnake.notlosing = false;

        if(thesnake.notlosing == false)                                                          //run during losing conditions
        {
            gamerunning = false;
            diesoundplay.play();
            score = 0;
            thescore.setString("0");
        }
        thesnake.totalbody[0].body.setPosition(thesnake.totalbody[0].partposx*24, thesnake.totalbody[0].partposy*24); //lock in head sprite position, apparently
        window.draw(apple.foodimage);
        for(int i = 0; i < allbadfood.badfoodcount; i++)                                              //draw every segment of snake body
        {
            window.draw(allbadfood.foodinventory[i].badapple);
        }
        window.draw(thesnake.totalbody[0].body);
        for(int i = 1; i < thesnake.bodycount; i++)                                              //draw every segment of snake body
        {
            window.draw(thesnake.totalbody[i].body);
        }
        window.draw(thescore);
        window.display();
    }
    return 0;
}
