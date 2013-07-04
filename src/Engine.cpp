#include <SFML/Window.hpp>

#include <iostream>
#include <sstream>
#include <cmath>

#include <tinyxml.h>

#include "Engine.hpp"
#include "Player.hpp"

using namespace std;
using namespace sf;

bool Engine::isAlreadyInstancied = false;
Engine* Engine::instanceOfEngine = 0;

template <typename T> string NumberToString ( T Number )
{
    ostringstream ss;
    ss << Number;
    return ss.str();
}

/*
    Permet de récupérer une adresse vers une instance d'Engine.
    Si aucun Engine n'a été crée, alors celui-ci sera crée et la fonction retournera son adresse,
    sinon elle retourne l'adresse de l'Engine qui a déjà été crée.
*/
Engine* Engine::getInstance()
{
    if(!isAlreadyInstancied)
    {
        //!Charge le fichier de configuration.
        /***********************************************************************************************/
        int init_width;
        int init_height;
        int init_bitmode;
        bool is_fullscreen;

        TiXmlDocument doc("config");

        if(!doc.LoadFile())
        {
            cerr << "Erreur lors du chargement du fichier de configuration " << endl;
            cerr << "Error #" << doc.ErrorId() << " : " << doc.ErrorDesc() << endl;
            exit(1);
        }

        TiXmlHandle hdl(&doc);
        TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();

        if(!elem)
        {
            cerr << "config corrompue !" << endl;
            exit(2);
        }

        elem->QueryIntAttribute("width", &init_width);
        elem->QueryIntAttribute("height", &init_height);
        elem->QueryIntAttribute("bitmode", &init_bitmode);
        elem = elem->NextSiblingElement(); // iteration
        elem->QueryBoolAttribute("fullscreen", &is_fullscreen);


        /***********************************************************************************************/

        Engine::instanceOfEngine = new Engine(sf::VideoMode(init_width, init_height, init_bitmode), is_fullscreen); // Crée une nouvelle instance de l'Engine.
        isAlreadyInstancied = true;
    }

    return instanceOfEngine;
}

Engine::Engine(sf::VideoMode mode, bool fullscreen)
{
    gameMap = new Map(getWC()+"/ressources/maps/01.map");
    if(fullscreen==true) Game.create(mode, "Ultra Shooter 0.2", sf::Style::Fullscreen);
    else Game.create(mode, "Ultra Shooter 0.2");
}

int Engine::Run()
{
    sf::Clock fps_clock;
    sf::Font font;
    float x(0);
    float y(0);

    if (!font.loadFromFile("ressources/fonts/arial.ttf"))
        cerr<<"ERROR : Can't load the font for the HUD"<<endl;

    //Game.setVerticalSyncEnabled(true);
    Game.setFramerateLimit(60);
    sf::Vector2u screen_size=Game.getSize();
    MainView.setSize(screen_size.x, screen_size.y);
    MainView.setCenter(screen_size.x/2, screen_size.y/2);
    //MainView.setSize(1440, 900);
    //MainView.setCenter(1440/2, 900/2);

    player = new Player(sf::Vector2f(200.f, 200.f), font, MainView.getSize());
    Game.setView(MainView);
    const float player_speed=5;

    IsRunning=true;
    while(IsRunning)
    {
        while(Game.isOpen())//Fenetre
        {
            localMousePosition = sf::Mouse::getPosition(Game);
            //Pour la répétition il faut utiliser les lignes ci-dessous.


            //Ancienne gestion des évènements, à rétablir si le TEST ne convient pas

            /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                player->move(-15.00f, 00.00f);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                player->move(15.00f, 00.00f);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                player->move(0.00f, -15.00f);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                player->move(0.00f, 15.00f);*/
            //Début zone de TEST : Tout marche parfaitement, pour moi ça convient !
            x=0.0f;
            y=0.0f;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                x=-player_speed;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                x=player_speed;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                y=-player_speed;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                y=player_speed;

            player->move(x, y);

            if(CheckIfOutOfWindow(player->getPosition(), player->getRayon()))
            {

                cerr<<"Collision : The player is out of the map !"<<endl;

                player->move(-x, -y);

                if(x>0)
                    x=getMap()->getWidth()-player->getPosition().x-player->getRayon();
                if(x<0)
                    x=-player->getPosition().x+player->getRayon();
                if(y>0)
                    y=getMap()->getHeight()-player->getPosition().y-player->getRayon();
                if(y<0)
                    y=-player->getPosition().y+player->getRayon();

                player->move(x, y);
            }

            //Fin zone de TEST

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2f converted_coord;//la position de la souris est en int
                converted_coord.x=(float)localMousePosition.x;//donc on la convertie en float car Player::Shoot(sf::Vector2f, sf::RenderWindow &myRenderWindow)
                converted_coord.y=(float)localMousePosition.y;//sf::Vector2f est en float

                gameMap->addBullet(Bullet(player->getPosition(), player->Shoot(converted_coord, Game)));
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
                    if (WindowEvent.key.code == sf::Keyboard::Escape)
                    {
                        Game.close();
                        IsRunning=false;
                    }
                    if (WindowEvent.key.code == sf::Keyboard::Space)
                    {
                        cout << "the space key was pressed" << std::endl;
                        cout << "control:" << WindowEvent.key.control << std::endl;
                        cout << "alt:" << WindowEvent.key.alt << std::endl;
                        cout << "shift:" << WindowEvent.key.shift << std::endl;
                        cout << "system:" << WindowEvent.key.system << std::endl;
                    }
                }
                if (WindowEvent.type == sf::Event::MouseButtonPressed)
                    if (WindowEvent.mouseButton.button == sf::Mouse::Right)
                        cout << "the right button was pressed" << std::endl;

                if (WindowEvent.type == sf::Event::MouseWheelMoved)
                    cout << "wheel movement: " << WindowEvent.mouseWheel.delta << std::endl;
            }//pollEvent

            Vector2i object_pixel_position=Game.mapCoordsToPixel(player->getPosition(), MainView);

            if(object_pixel_position.x < 100)
            {
                MainView.move(-5.f, 0.f);
                Game.setView(MainView);
            }
            if(object_pixel_position.x > Game.getSize().x-100)//ignorer avertissement de la comparaison entre expressions entières signée et non signée
            {
                MainView.move(5.f, 0.f);
                Game.setView(MainView);
            }
            if(object_pixel_position.y < 100)
            {
                MainView.move(0.f, -5.f);
                Game.setView(MainView);
            }
            if(object_pixel_position.y > Game.getSize().y-100)//ignorer avertissement de la comparaison entre expressions entières signée et non signée
            {
                MainView.move(0.f, 5.f);
                Game.setView(MainView);
            }

            Game.clear(Color(0,0,0));

            Game.draw(gameMap->getBackground());
            gameMap->update(Game);
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

Map* Engine::getMap() const
{
    return gameMap;
}

bool Engine::CheckIfOutOfWindow(sf::Vector2f Position, float rayon)
{
    sf::Vector2u window_size=Game.getSize();

    if( static_cast<int>(Position.x-rayon) < 0                    ||
            static_cast<unsigned int>(Position.x+rayon) > getMap()->getWidth() ||
            static_cast<int>(Position.y-rayon) < 0                    ||
            static_cast<unsigned int>(Position.y+rayon) > getMap()->getHeight())

        return true;

    else
        return false;
}


Engine::~Engine()
{
    isAlreadyInstancied = false;
    delete gameMap;
    Game.close();
}
