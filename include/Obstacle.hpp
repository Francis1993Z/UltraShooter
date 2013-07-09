#ifndef OBSTACLE_HPP_INCLUDED
#define OBSTACLE_HPP_INCLUDED

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Obstacle
{
    sf::Sprite sprite;

    int width;
    int height;

    sf::FloatRect rect;

public :

    Obstacle(sf::Texture* obstacleTexture, int x, int y);
    ~Obstacle();

    int getWidth() const;
    int getHeight() const;

    void draw(sf::RenderWindow* window) const;

    sf::FloatRect getCollisionBox() const;
};


#endif // OBSTACLE_HPP_INCLUDED
