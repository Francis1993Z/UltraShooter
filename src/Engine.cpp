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
#include "Hud.hpp"

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
    screen_size2i.x = (int)screen_size.x;
    screen_size2i.y = (int)screen_size.y;
    screen_size2f.x = (float)screen_size.x;
    screen_size2f.y = (float)screen_size.y;
    PlayerView.setSize(screen_size.x, screen_size.y);
    player = new Player(sf::Vector2f(100.f, 100.f), TEAM1);
    PlayerView.setCenter(player->getPosition());
    events = new Events();
    Game->setView(PlayerView);
    collisionManager = new CollisionManager(*player, *gameMap);
    MenuView.setSize(screen_size.x, screen_size.y);
    MenuView.setCenter(screen_size.x/2, screen_size.y/2);
    Game->setView(MenuView);
    menu = new Menu(screen_size, MenuView);
    menu->afficher();
    widgetManager.setPause(false);
    widgetManager.setCurrentWidgetListener(menu);

    gameEnded = new GameEnded();

    gameMap->setlocalPlayer(*player);

    mManager.playTheme(gameMap->getTheme());
    mManager.setVolume(100);
    sf::Clock ennemy_clock;

    gameMap->loadNextWave();

    Game->setView(PlayerView);//<-- pour que la HUD se centre sur le joueur
    localplayer_hud = new Hud();
    player->initHud();
    Game->setView(MenuView);//<-- on revient avec le menu

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
                            PlayerView.setCenter(Game->getSize().x/2, Game->getSize().y/2);
                            Game->setView(MenuView);
                            menu->afficher();
                            widgetManager.setPause(false);
                            widgetManager.setCurrentWidgetListener(menu);
                        }

                    if(!menu->isActif() && !gameEnded->isActif())
                        {
                            widgetManager.setPause(true);

                            //Phase de mise à jour
                                gameMap->update();

                            lookIfGameOver(); //Regarde s'il y a "GAME OVER".
                            nextWaveAndMap(); //Charge la wave ou la map suivante à defaut de wave.

                            //Phase de rendu
                            Game->clear(Color(0,0,0));
                            drawGame(); //Dessine tous les composants du jeu lors d'une partie.
                            Game->display();

                        }
                    else if(gameEnded->isActif())
                        {

                            fenetreFinJeu = true;
                            Game->setView(MenuView);
                            Game->clear(Color(0,0,0));
                            gameEnded->draw();
                            Game->display();
                        }
                    else if(menu->isActif())
                        {
                            Game->setView(MenuView);
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

View Engine::getMenuView() const
{
    return MenuView;
}

View Engine::getPlayerView() const
{
    return PlayerView;
}

Menu* Engine::getMenu() const
{

    return menu;
}

Hud* Engine::getHud() const{

    return localplayer_hud;
}


void Engine::gestionEvenements()
{
    if (widgetManager.getPause())
    events->updateEvents();

            localMousePosition = sf::Mouse::getPosition(*Game);

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
         sf::Vector2f converted_mouse_coord = Game->mapPixelToCoords(localMousePosition);
                    widgetManager.updatePosSouris(converted_mouse_coord.x, converted_mouse_coord.y);
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
                    PlayerView.setSize(WindowEvent.size.width, WindowEvent.size.height);
                    Game->setView(PlayerView);
                    localplayer_hud->setSizeWindow(getScreenSize2f());
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
                    localplayer_hud->updateActualWeapon(player->getSymboleActualWeapon(), player->isTirIllimity(), player->getAmmunitions());
                }

        }//pollEvent

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {

            if (!menu->isActif() && !gameEnded->isActif())
                {
                    player->Shoot();
                }

            else if(!widgetManager.getPause())
                {
                       sf::Vector2f converted_mouse_coord = Game->mapPixelToCoords(localMousePosition);
                    widgetManager.positionClicSouris(converted_mouse_coord.x, converted_mouse_coord.y);
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
                        sf::Vector2f converted_mouse_coord = Game->mapPixelToCoords(localMousePosition);
                    widgetManager.positionRelachementSouris(converted_mouse_coord.x, converted_mouse_coord.y);
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
        PlayerView.setCenter(player->getPosition());
        Game->setView(PlayerView);
                      localplayer_hud->setPositionHud();
}

void Engine::drawMenu()
{
    menu->draw();
}

void Engine::SwitchView()
{
    if (MenuView_ON) Game->setView(PlayerView);
    else             Game->setView(MenuView);
}

void Engine::drawGame()
{
    Game->draw(gameMap->getBackground());

    gameMap->draw(Game);
    Game->draw(*player);
    Game->draw(*player->getWeapon());
    localplayer_hud->draw();
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
                            PlayerView.setCenter(Game->getSize().x/2, Game->getSize().y/2);
                            Game->setView(MenuView);

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
            PlayerView.setCenter(Game->getSize().x/2, Game->getSize().y/2);
            Game->setView(MenuView);

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

Vector2i Engine::getScreenSize2i() const
{
    return screen_size2i;
}

Vector2f Engine::getScreenSize2f() const
{
    return screen_size2f;
}


Engine::~Engine()
{
    isAlreadyInstancied = false;
    Game->close();
    IsRunning=false;

    delete Game;
    delete gameMap;
    delete localplayer_hud;
    //delete player; C'est maintenant Map qui détruit player
    delete collisionManager;
    delete menu;
    delete loadFiles;
    delete gameEnded;
    delete events;
}
