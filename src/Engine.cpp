#include <SFML/Window.hpp>

#include <dirent.h>

#ifndef WIN32
#include <sys/types.h>
#endif

#include <iostream>
#include <sstream>
#include <cmath>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>
#include <time.h>       /* time */
#include <fstream>

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
            string configPath(getCWD()+"/config/config");
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




       string file_d = getCWD()+"/config/videomode.txt";
    ofstream videomode(file_d.c_str(), ios::out | ios::trunc);  //déclaration du flux et ouverture du fichier

    if(videomode)  // si l'ouverture a réussi
        {
            // instructions
            vector<sf::VideoMode>VideoModesCount = sf::VideoMode::getFullscreenModes();
            for (vector<sf::VideoMode>::iterator i = VideoModesCount.begin(); i != VideoModesCount.end(); ++i)
                {
                    if ((*i).isValid())
                        {
                            videomode<< "Mode " << (*i).width << "x" << (*i).height << "-" << (*i).bitsPerPixel << " is valid" << std::endl;
                        }
                    // Mode is a valid video mode
                }
                videomode<<"Game VideoMode : "<<init_width<<"x"<<init_height<< "-" << init_bitmode<<endl;
            videomode.close();  // on referme le fichier
        }
    else  // sinon
        cerr << "Erreur à l'ouverture !" << endl;

            /***********************************************************************************************/

            Engine::instanceOfEngine = new Engine(VideoMode(init_width, init_height, init_bitmode), is_fullscreen); // Crée une nouvelle instance de l'Engine.
            isAlreadyInstancied = true;
        }

    return instanceOfEngine;
}

Engine::Engine(VideoMode mode, bool fullscreen)
{
    mapNumber = 1;

    ostringstream oss;
    oss << mapNumber;

    if(mapNumber < 10)
        gameMap = new Map(getCWD()+"/ressources/maps/0" + oss.str() + ".map");
    else
        gameMap = new Map(getCWD()+"/ressources/maps/" + oss.str() + ".map");

    loadFiles = new LoadFiles();
    Game = new RenderWindow();

    if(fullscreen)
        Game->create(mode, "Ultra Shooter 0.2", sf::Style::Fullscreen);
    else
        Game->create(mode, "Ultra Shooter 0.2");
}
/*
void Engine::screenshot()
{
    struct dirent* fichierLu = NULL;
    DIR* rep = NULL;
    string cwd = getCWD()+"/ressources/captures/";
    rep = opendir(cwd.c_str());

    if (rep == NULL)
        exit(1);
    while ((fichierLu = readdir(rep)) != NULL) cout<<"-> "<<fichierLu->d_name<<endl;
    if (closedir(rep) == -1)
        exit(-1);
}
*/
int Engine::Run()
{


    Clock fps_clock;
    //Game.setVerticalSyncEnabled(true);
    Game->setFramerateLimit(60);
    Vector2u screen_size=Game->getSize();
    MainView.setSize(screen_size.x, screen_size.y);
    MainView.setCenter(screen_size.x/2, screen_size.y/2);
    //MainView.setSize(1024, 768);
    events = new Events();
    player = new Player(sf::Vector2f(200.f, 200.f), *(loadFiles->getPoliceArial()), MainView.getSize(), TEAM1);
    //cout<<"engine player : "<<player<<endl;
    collisionManager = new CollisionManager(*player, *gameMap);
    menu = new Menu(screen_size);
    menu->afficher();
    widgetManager.setPause(false);
    widgetManager.setCurrentWidgetListener(menu);

    gameEnded = new GameEnded();

    gameMap->setlocalPlayer(*player);

    Game->setView(MainView);

    mManager.playTheme(gameMap->getTheme());
    mManager.setVolume(100);
    sf::Clock ennemy_clock;

    gameMap->loadNextWave();

    fenetreFinJeu = false;
    IsRunning=true;
    while(IsRunning)
        {
            while(Game->isOpen())//Fenetre
                {
                    gestionEvenements(); //Gère tous les évènements.

                    if(fenetreFinJeu && !gameEnded->isActif())
                        {

                            fenetreFinJeu = false;
                            MainView.setCenter(Game->getSize().x/2, Game->getSize().y/2);
                            Game->setView(MainView);
                            menu->afficher();
                            widgetManager.setPause(false);
                            widgetManager.setCurrentWidgetListener(menu);
                        }

                    if(!menu->isActif() && !gameEnded->isActif())
                        {

                            widgetManager.setPause(true);

                            updateView(); //Mets à jour la position de la caméra.
                            Game->clear(Color(0,0,0));
                            drawGame(); //Dessine tous les composants du jeu lors d'une partie.
                            Game->display();
                            lookIfGameOver(); //Regarde si il y a "GAME OVER".
                            nextWaveAndMap(); //Charge la wave ou la map suivante à defaut de wave.
                        }
                    else if(gameEnded->isActif())
                        {

                            fenetreFinJeu = true;

                            Game->clear(Color(0,0,0));
                            gameEnded->draw();
                            Game->display();
                        }
                    else if(menu->isActif())
                        {

                            Game->clear(Color(0,0,0));
                            drawMenu(); //Dessine le menu.
                            Game->display();
                        }
                }
        }
    return 0;
}

Map* Engine::getMap() const
{
    return gameMap;
}

Player* Engine::getPlayer() const
{
    return player;
}

CollisionManager* Engine::getCollisionManager() const
{

    return collisionManager;
}

MusicManager* Engine::getMusicManager()
{
    return &mManager;
}

LoadFiles* Engine::getLoadFiles() const
{

    return loadFiles;
}

RenderWindow* Engine::getRenderWindow() const
{

    return Game;
}

Menu* Engine::getMenu() const
{

    return menu;
}

void Engine::gestionEvenements()
{
    events->updateEvents();


//Pour des touches séparées(avec délai du système), il vaut mieux utiliser ces lignes là(pollEvent).
    while (Game->pollEvent(WindowEvent))
        {
            if (WindowEvent.type == Event::Closed)
                {
                    Game->close();
                    IsRunning=false;
                }
            if (WindowEvent.type == Event::MouseMoved && !widgetManager.getPause())
                {
                    widgetManager.updatePosSouris(WindowEvent.mouseMove.x, WindowEvent.mouseMove.y);
                }

            if (WindowEvent.type == Event::TextEntered && !widgetManager.getPause())
                {

                    widgetManager.codeKeyPressed(WindowEvent.text.unicode);
                }
            if (WindowEvent.type == sf::Event::MouseButtonPressed)
                if (WindowEvent.mouseButton.button == sf::Mouse::Right)
                    cout << "the right button was pressed" << std::endl;

            if (WindowEvent.type == sf::Event::Resized)
                {
                    MainView.setSize(WindowEvent.size.width, WindowEvent.size.height);
                    Game->setView(MainView);
                }
            if (WindowEvent.type == Event::KeyPressed)
                {
                    if (WindowEvent.key.code == sf::Keyboard::Escape)
                        {
                            Game->close();
                            IsRunning=false;
                        }
                    if(!menu->isActif())
                        {
                            if (WindowEvent.key.code == sf::Keyboard::Space)
                                {

                                    gameMap->addEnnemy(new Zombie(sf::Vector2f(500,500), *player, TEAM2));
                                }
                            if (WindowEvent.key.code == sf::Keyboard::Numpad0)
                                {

                                    gameMap->addEnnemy(new Splitter(sf::Vector2f(300,500), *player, 1, TEAM2));

                                }
                            if (WindowEvent.key.code == sf::Keyboard::Numpad1)
                                {
                                    gameMap->addEnnemy(new Raider(sf::Vector2f(300,500), *player, TEAM2));
                                }
                            //if (WindowEvent.key.code == sf::Keyboard::F12) screenshot();

                        }
                }

            if (WindowEvent.type == sf::Event::MouseWheelMoved)
                {
                    player->change_Weapon(WindowEvent.mouseWheel.delta);
                }

        }//pollEvent

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            localMousePosition = sf::Mouse::getPosition(*Game);
            if (!menu->isActif())
                {
                    player->Shoot();
                }

            else if(!widgetManager.getPause())
                {

                    widgetManager.positionClicSouris(localMousePosition.x, localMousePosition.y);
                }
        }
        else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            player->stopMLAction();
        }


    if(WindowEvent.type == sf::Event::MouseButtonReleased)
        {

            if (WindowEvent.mouseButton.button == sf::Mouse::Left && !widgetManager.getPause())
                {
                    widgetManager.positionRelachementSouris(WindowEvent.mouseButton.x, WindowEvent.mouseButton.y);
                }
        }
}

bool Engine::loadNextMap()
{
    ++mapNumber;

    ostringstream oss;
    string path;

    oss << mapNumber;

    if(mapNumber < 10)
        path = getCWD()+"/ressources/maps/0" + oss.str() + ".map";
    else
        path = getCWD()+"/ressources/maps/" + oss.str() + ".map";

    if(fileExists(path.c_str()))
        {
            delete gameMap;
            gameMap = new Map(path);
            return true;
        }
    return false;
}

void Engine::updateView()
{

    Vector2i object_pixel_position=Game->mapCoordsToPixel(player->getPosition(), MainView);

    if(object_pixel_position.x < 300)
        {
            MainView.move(-player->getSpeed(), 0.f);
            player->move_myhud(-player->getSpeed(), 0.f);//On met à jour la position de la HUD
            Game->setView(MainView);
        }
    if((unsigned)object_pixel_position.x > Game->getSize().x-300)//ignorer avertissement de la comparaison entre expressions entières signée et non signée
        {
            MainView.move(player->getSpeed(), 0.f);
            player->move_myhud(player->getSpeed(), 0.f);
            Game->setView(MainView);
        }
    if(object_pixel_position.y < 300)
        {
            MainView.move(0.f, -player->getSpeed());
            player->move_myhud(0.f, -player->getSpeed());
            Game->setView(MainView);
        }
    if((unsigned)object_pixel_position.y > Game->getSize().y-300)//ignorer avertissement de la comparaison entre expressions entières signée et non signée
        {
            MainView.move(0.f, player->getSpeed());
            player->move_myhud(0.f, player->getSpeed());
            Game->setView(MainView);
        }
}

void Engine::drawMenu()
{
    menu->draw();
}

void Engine::drawGame()
{

    Game->draw(gameMap->getBackground());
    gameMap->update(Game);
    gameMap->drawObstacles(Game);
    Game->draw(*player);
    Game->draw(player->getScoreHud());
    Game->draw(player->getLifeHud());
}

void Engine::nextWaveAndMap()
{

    if(gameMap->isCurrentWaveOver())
        {
            if(!gameMap->loadNextWave())
                {
                    if(!loadNextMap())
                        {
                            //leaveGame("Jeu termine !");
                            gameEnded->setActif(true, false);
                            MainView.setCenter(Game->getSize().x/2, Game->getSize().y/2);
                            Game->setView(MainView);

                            widgetManager.setCurrentWidgetListener(gameEnded);
                            widgetManager.setPause(false);
                        }
                }
        }

}

void Engine::lookIfGameOver()
{

    if(gameMap->getGameOver())
        {
            //leaveGame("Game Over !");
            gameEnded->setActif(true, true);
            MainView.setCenter(Game->getSize().x/2, Game->getSize().y/2);
            Game->setView(MainView);

            widgetManager.setCurrentWidgetListener(gameEnded);
            widgetManager.setPause(false);
        }
}

void Engine::leaveGame(string cause)
{

    cout<<cause<<endl;
    Game->close();
    IsRunning=false;
}

Engine::~Engine()
{
    isAlreadyInstancied = false;
    Game->close();
    IsRunning=false;

    delete Game;
    delete gameMap;
    //delete player; C'est maintenant Map qui détruit player
    delete collisionManager;
    delete menu;
    delete loadFiles;
    delete gameEnded;
    delete events;
}
