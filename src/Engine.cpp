#include <SFML/Window.hpp>

#include <iostream>
#include <sstream>
#include <cmath>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>
#include <time.h>       /* time */

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
            std::string configPath(getCWD()+"/config/config");
            TiXmlDocument doc(configPath.c_str());

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
    gameMap = new Map(getCWD()+"/ressources/maps/01.map");
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
    //MainView.setSize(1024, 768);

    player = new Player(sf::Vector2f(200.f, 200.f), font, MainView.getSize());
    collisionManager = new CollisionManager(*player, *gameMap);

    gameMap->setPlayer(*player);

    ///******************************************************************************///
    sf::FloatRect port(0, 0, 1, 1);
    //MainView.setViewport(port);

    //MainView.setCenter(player->getPosition());

    Game.setView(MainView);

    ///******************************************************************************///

    mManager.playTheme(gameMap->getTheme());

    sf::Clock ennemy_clock;

    IsRunning=true;
    while(IsRunning)
        {
            while(Game.isOpen())//Fenetre
                {
                    localMousePosition = sf::Mouse::getPosition(Game);

                    /*
                    sf::Time ennemy_time = ennemy_clock.getElapsedTime();
                    if(ennemy_time.asSeconds()>=1)
                    {
                        srand (time(NULL));
                        float x=rand()%100;
                        float y=rand()%100;
                        gameMap->addZombie(Zombie(sf::Vector2f(x,y)));
                        cout<<"create zombie"<<endl;
                    }*/

                    //Pour la répétition il faut utiliser les lignes ci-dessous.
                    x=0.0f;
                    y=0.0f;

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                        x+=-player->getVitesse();

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                        x+=player->getVitesse();

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        y+=-player->getVitesse();

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        y+=player->getVitesse();

                    player->move(x, y);

                    if(collisionManager->CollisionJoueur(x, y))
                        {

                            mManager.playEvent("ressources/sounds/events/impact.ogg");
                            player->move(-x, -y);
                            player->move(collisionManager->getDeplacementX(), collisionManager->getDeplacementY());
                        }

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            if (player->ReadyToShoot()==true)
                                {
                                    sf::Vector2f converted_coord;//la position de la souris est en int
                                    converted_coord.x=(float)localMousePosition.x;//donc on la convertie en float car Player::Shoot(sf::Vector2f, sf::RenderWindow &myRenderWindow)
                                    converted_coord.y=(float)localMousePosition.y;//sf::Vector2f est en float

                                    gameMap->addBullet(Bullet(player->getPosition(), player->Shoot(converted_coord, Game)));
                                }
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
                                            /*cout << "the space key was pressed" << std::endl;
                                            cout << "control:" << WindowEvent.key.control << std::endl;
                                            cout << "alt:" << WindowEvent.key.alt << std::endl;
                                            cout << "shift:" << WindowEvent.key.shift << std::endl;
                                            cout << "system:" << WindowEvent.key.system << std::endl;*/
                                            gameMap->addEnnemy(new Zombie(sf::Vector2f(500,500), *player));
                                        }
                                    if (WindowEvent.key.code == sf::Keyboard::Numpad0)
                                        {
                                            /*cout << "the space key was pressed" << std::endl;
                                            cout << "control:" << WindowEvent.key.control << std::endl;
                                            cout << "alt:" << WindowEvent.key.alt << std::endl;
                                            cout << "shift:" << WindowEvent.key.shift << std::endl;
                                            cout << "system:" << WindowEvent.key.system << std::endl;*/
                                            gameMap->addEnnemy(new Splitter(sf::Vector2f(300,500), *player, 1));
                                        }
                                }
                            if (WindowEvent.type == sf::Event::MouseButtonPressed)
                                if (WindowEvent.mouseButton.button == sf::Mouse::Right)
                                    cout << "the right button was pressed" << std::endl;

                            if (WindowEvent.type == sf::Event::MouseWheelMoved)
                                {
                                    cout << "wheel movement: " << WindowEvent.mouseWheel.delta << endl;

                                    if(WindowEvent.mouseWheel.delta > 0)
                                        MainView.zoom(0.8);
                                    else if(WindowEvent.mouseWheel.delta < 0)
                                        MainView.zoom(1.8);

                                    Game.setView(MainView);
                                }

                        }//pollEvent

                    Vector2i object_pixel_position=Game.mapCoordsToPixel(player->getPosition(), MainView);

                    if(object_pixel_position.x < 300)
                        {
                            MainView.move(-player->getVitesse(), 0.f);
                            player->move_myhud(-player->getVitesse(), 0.f);//On met à jour la position de la HUD
                            Game.setView(MainView);
                        }

                    if(object_pixel_position.x > Game.getSize().x-300)//ignorer avertissement de la comparaison entre expressions entières signée et non signée
                        {
                            MainView.move(player->getVitesse(), 0.f);
                            player->move_myhud(player->getVitesse(), 0.f);
                            Game.setView(MainView);
                        }

                    if(object_pixel_position.y < 300)
                        {
                            MainView.move(0.f, -player->getVitesse());
                            player->move_myhud(0.f, -player->getVitesse());
                            Game.setView(MainView);
                        }

                    if(object_pixel_position.y > Game.getSize().y-300)//ignorer avertissement de la comparaison entre expressions entières signée et non signée
                        {
                            MainView.move(0.f, player->getVitesse());
                            player->move_myhud(0.f, player->getVitesse());
                            Game.setView(MainView);
                        }

                    Game.clear(Color(0,0,0));

                    Game.draw(gameMap->getBackground());
                    gameMap->update(&Game);
                    gameMap->drawObstacles(&Game);
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

CollisionManager* Engine::getCollisionManager() const
{

    return collisionManager;
}

MusicManager* Engine::getMusicManager()
{
    return &mManager;
}

Engine::~Engine()
{
    isAlreadyInstancied = false;
    delete gameMap;
    delete collisionManager;
    Game.close();
}
