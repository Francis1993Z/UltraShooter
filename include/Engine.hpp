#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include <vector>
class Engine
{
public:
    Engine(sf::VideoMode Mode);
    int Run();
    bool CheckIfOutOfWindow(sf::Vector2f Position);
    ~Engine();

private:
    std::vector<Bullet> AllBullets;
    Player* player;
    bool IsRunning;
    sf::Vector2i localMousePosition;
    sf::Event WindowEvent;
    sf::RenderWindow Game;
    sf::View MainView;
};

#endif // ENGINE_HPP_INCLUDED
