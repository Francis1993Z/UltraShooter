#include "Engine.hpp"
#include <SFML/Window.hpp>
#include "Player.hpp"

#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;
using namespace sf;

template <typename T> string NumberToString ( T Number )
{
    ostringstream ss;
    ss << Number;
    return ss.str();
}



Engine::Engine(sf::VideoMode Mode)
{
    Game.create(Mode, "Ultra Shooter 0.2");

}

int Engine::Run()
{

    sf::Clock fps_clock;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        cerr<<"ERROR : Can't load the font for the HUD"<<endl;
    }


//Game.setVerticalSyncEnabled(true);
    Game.setFramerateLimit(60);
    //MainView.setSize(880, 550); //Ne pas toucher c'est pour ne pas avoir le bug de la fenêtre trop grande sur Windows
    //MainView.setCenter(880/2, 550/2); 
	MainView.setSize(1440, 900);
    MainView.setCenter(1440/2, 900/2);

    player = new Player(sf::Vector2f(200.f, 200.f), font, MainView.getSize());
    Game.setView(MainView);

    IsRunning=true;
    while(IsRunning)
    {

        while(Game.isOpen())//Fenetre
        {


            localMousePosition = sf::Mouse::getPosition(Game);
//Pour la répétition il faut utiliser les lignes ci-dessous.
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                player->move(-15.00f, 00.00f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                player->move(15.00f, 00.00f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                player->move(0.00f, -15.00f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                player->move(0.00f, 15.00f);
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                            sf::Vector2f converted_coord;//la position de la souris est en int
                converted_coord.x=(float)localMousePosition.x;//donc on la convertie en float car Player::Shoot(sf::Vector2f, sf::RenderWindow &myRenderWindow)
                converted_coord.y=(float)localMousePosition.y;//sf::Vector2f est en float

                AllBullets.push_back(Bullet(player->getPosition(), player->Shoot(converted_coord, Game)));

            }
//Pour des touches séparées(avec délai du système), il vaut mieux utiliser ces lignes là(pollEvent).
            while (Game.pollEvent(WindowEvent))
            {
                if (WindowEvent.type == Event::Closed)
                {
                    Game.close();
                    IsRunning=false;
                }
                /* else if (WindowEvent.type == Event::MouseMoved)
                 {
                     MousePosition.x=WindowEvent.mouseMove.x;
                     MousePosition.y=WindowEvent.mouseMove.y;
                 }*/
                if (WindowEvent.type == sf::Event::Resized)
                {
                    // on met à jour la vue, avec la nouvelle taille de la fenêtre
                    MainView.setSize(WindowEvent.size.width, WindowEvent.size.height);
                    //sf::FloatRect visibleArea(0, 0, WindowEvent.size.width, WindowEvent.size.height);
                    //Game.setView(sf::View(visibleArea));
                    Game.setView(MainView);
                }
                if (WindowEvent.type == Event::KeyPressed)
                {
                    if (WindowEvent.key.code == sf::Keyboard::Space)
                    {

                        std::cout << "the space key was pressed" << std::endl;
                        std::cout << "control:" << WindowEvent.key.control << std::endl;
                        std::cout << "alt:" << WindowEvent.key.alt << std::endl;
                        std::cout << "shift:" << WindowEvent.key.shift << std::endl;
                        std::cout << "system:" << WindowEvent.key.system << std::endl;
                    }
                }
                if (WindowEvent.type == sf::Event::MouseButtonPressed)
                {
                    if (WindowEvent.mouseButton.button == sf::Mouse::Right)
                    {
                        std::cout << "the right button was pressed" << std::endl;

                    }
                }
                if (WindowEvent.type == sf::Event::MouseWheelMoved)
                {
                    std::cout << "wheel movement: " << WindowEvent.mouseWheel.delta << std::endl;

                }
            }//pollEvent



            Vector2i object_pixel_position=Game.mapCoordsToPixel(player->getPosition(), MainView);
            if(object_pixel_position.x < 100)
            {
                MainView.move(-15.f, 0.f);
                Game.setView(MainView);
            }
            if(object_pixel_position.x > Game.getSize().x-100)//ignorer avertissement de la comparaison entre expressions entières signée et non signée
            {
                MainView.move(15.f, 0.f);
                Game.setView(MainView);
            }
            if(object_pixel_position.y < 100)
            {
                MainView.move(0.f, -15.f);
                Game.setView(MainView);
            }
            if(object_pixel_position.y > Game.getSize().y-100)//ignorer avertissement de la comparaison entre expressions entières signée et non signée
            {
                MainView.move(0.f, 15.f);
                Game.setView(MainView);
            }


                for(unsigned int n=0; n<AllBullets.size(); n++)
            {
               AllBullets.at(n).UpdatePosition();
               if(CheckIfOutOfWindow(AllBullets.at(n).getPosition()) == true)
{
AllBullets.erase(AllBullets.begin()+n);
}

            }



  Game.clear(Color(255,255,255));

            for(unsigned int n=0; n<AllBullets.size(); n++)
            {
                Game.draw(AllBullets.at(n));
            }

            Game.draw(*player);
            Game.draw(player->getScoreHud());
            Game.draw(player->getLifeHud());
            Game.display();

            /* float currentTime = fps_clock.restart().asSeconds();
            int fps = static_cast<int> ( 1.f / currentTime);
            string fps_string = NumberToString(fps);
             Game.setTitle("Ultra Shooter 0.2 FPS : "+fps_string);*/

        }
        delete player;
    }

    return 0;
}

bool Engine::CheckIfOutOfWindow(sf::Vector2f Position)
{
    sf::Vector2u window_size=Game.getSize();
    if(     static_cast<unsigned int>(Position.x) < 0             ||
            static_cast<unsigned int>(Position.x) > window_size.x ||
            static_cast<unsigned int>(Position.y) < 0             ||
            static_cast<unsigned int>(Position.y) > window_size.y)
    {

        return true;

    }
    else
    {

        return false;

    }
}


Engine::~Engine()
{
    Game.close();
}
