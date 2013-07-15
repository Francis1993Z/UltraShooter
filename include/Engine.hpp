#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

#include "Player.hpp"
#include "Bullet.hpp"
#include "Map.hpp"
#include "CollisionManager.hpp"
#include "MusicManager.hpp"

class Map;
class CollisionManager; /* Permet d'�viter l'interd�pendance, en effet, Engine a besoin de conna�tre Map mais Map a besoin de Conna�tre Engine
              On pr�vient juste le compilateur que Map sera d�finit plus tard */

/*
    La classe Engine est un Singleton, elle est donc accessible partout dans le programme en faisant : Engine::getInstance().
*/
class Engine
{

public:

    ~Engine();

    int Run();

    bool CheckIfOutOfWindow(sf::Vector2f Position, float deplacement_x, float deplacement_y, float rayon);

    static Engine* getInstance(); //Permet de r�cup�rer l'instance (adresse) de la classe Engine partout dans le programme.

    Map* getMap() const;

    CollisionManager* getCollisionManager() const;

    MusicManager* getMusicManager();

private:

    MusicManager mManager;

    Engine(sf::VideoMode mode, bool fullscreen); // Le constructeur est priv� car on ne doit pas pouvoir construire la classe sans passer par la m�thode getInstance().

    bool IsRunning;
    static bool isAlreadyInstancied; // Permet de savoir si une instance d'Engine existe d�j� ou non.
    static Engine* instanceOfEngine; // Permet de retenir l'adresse de l'instance d'Engine qui a �t� cr�e.

    Map* gameMap;   // On utilise un pointeur pour �viter le soucis d'interd�pendance.
    Player* player;
    CollisionManager* collisionManager;

    sf::Vector2i localMousePosition;
    sf::Event WindowEvent;
    sf::RenderWindow Game;
    sf::View MainView;
};

#endif // ENGINE_HPP_INCLUDED
