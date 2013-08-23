#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <list>
#include <vector>
#include <string>
#include <map>

#include "Player.hpp"
#include "Ennemy.hpp"
#include "Splitter.hpp"//inclue zombi
#include "Raider.hpp"

#include "Obstacle.hpp"
#include "Wave.hpp"
#include "EnnemyFactory.hpp"
#include "Map.hpp"
#include "CollisionManager.hpp"
#include "MusicManager.hpp"
#include "Menu.hpp"
#include "LoadFiles.hpp"
#include "WidgetManager.hpp"
#include "GameEnded.hpp"
#include "Events.hpp"


class Map;
class Events;
class CollisionManager; /* Permet d'éviter l'interdépendance, en effet, Engine a besoin de connaître Map mais Map a besoin de Connaître Engine
              On prévient juste le compilateur que Map sera définit plus tard */

/*
    La classe Engine est un Singleton, elle est donc accessible partout dans le programme en faisant : Engine::getInstance().
*/
class Engine
{
public:

    ~Engine();

    int Run();

    bool CheckIfOutOfWindow(sf::Vector2f Position, float deplacement_x, float deplacement_y, float rayon);

    void leaveGame(std::string cause);

    static Engine* getInstance(); //Permet de récupérer l'instance (adresse) de la classe Engine partout dans le programme.
    //void addEnnemy(Ennemy *e);
    Map* getMap() const;
    Player* getPlayer() const;
    sf::RenderWindow* getRenderWindow() const;
    CollisionManager* getCollisionManager() const;
    MusicManager* getMusicManager();
    LoadFiles* getLoadFiles() const;
    Menu* getMenu() const;
    Hud* getHud() const;

    bool loadNextMap();
    void updateView();
    void SwitchView();
    sf::Vector2i getScreenSize2i() const;
    sf::Vector2f getScreenSize2f() const;
    sf::View getMenuView() const;
    sf::View getPlayerView() const;
private:

    MusicManager mManager;

    Engine(sf::VideoMode mode, bool fullscreen); // Le constructeur est privé car on ne doit pas pouvoir construire la classe sans passer par la méthode getInstance().

    void drawGame();
    void drawMenu();
    void lookIfGameOver();
    void nextWaveAndMap();
    void gestionEvenements();
    void screenshot();

    int mapNumber;

    Hud* localplayer_hud;

    bool fenetreFinJeu, MenuView_ON;
    bool IsRunning;
    static bool isAlreadyInstancied; // Permet de savoir si une instance d'Engine existe déjà ou non.
    static Engine* instanceOfEngine; // Permet de retenir l'adresse de l'instance d'Engine qui a été crée.

    Map* gameMap;   // On utilise un pointeur pour éviter le soucis d'interdépendance.
    Player* player;
    CollisionManager* collisionManager;
    Menu* menu;
    GameEnded* gameEnded;
    LoadFiles* loadFiles;
    WidgetManager widgetManager;
    Events* events;
   sf::Vector2i screen_size2i;
   sf::Vector2f screen_size2f;
    sf::Vector2i localMousePosition;
    sf::Event WindowEvent;
    sf::RenderWindow* Game;
    sf::View PlayerView, MenuView;
};

#endif // ENGINE_HPP_INCLUDED
