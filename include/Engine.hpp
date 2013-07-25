#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

#include "Player.hpp"
#include "Bullet.hpp"
#include "Map.hpp"
#include "CollisionManager.hpp"
#include "MusicManager.hpp"
#include "Menu.hpp"
#include "LoadFiles.hpp"
#include "WidgetManager.hpp"

class Map;


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

    bool loadNextMap();

private:

    MusicManager mManager;

    Engine(sf::VideoMode mode, bool fullscreen); // Le constructeur est privé car on ne doit pas pouvoir construire la classe sans passer par la méthode getInstance().
    void updateView();
    void drawGame();
    void drawMenu();
    void lookIfGameOver();
    void nextWaveAndMap();
    void gestionEvenements();

    int mapNumber;

    bool IsRunning;
    static bool isAlreadyInstancied; // Permet de savoir si une instance d'Engine existe déjà ou non.
    static Engine* instanceOfEngine; // Permet de retenir l'adresse de l'instance d'Engine qui a été crée.

    Map* gameMap;   // On utilise un pointeur pour éviter le soucis d'interdépendance.
    Player* player;
    CollisionManager* collisionManager;
    Menu* menu;
    LoadFiles* loadFiles;
    WidgetManager widgetManager;

    sf::Vector2i localMousePosition;
    sf::Event WindowEvent;
    sf::RenderWindow* Game;
    sf::View MainView;
};

#endif // ENGINE_HPP_INCLUDED
