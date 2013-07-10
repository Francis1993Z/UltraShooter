#include "Obstacle.hpp"

using namespace sf;

Obstacle::Obstacle(Texture* obstacleTexture, int x, int y)
{
    sprite.setTexture(*obstacleTexture);
    sprite.setPosition(x, y);
}

Obstacle::~Obstacle()
{
}

int Obstacle::getWidth() const
{
    return width;
}

int Obstacle::getHeight() const
{
    return height;
}

void Obstacle::draw(RenderWindow* window) const
{
    window->draw(sprite);
}

sf::FloatRect Obstacle::getCollisionBox() const{

    return sprite.getGlobalBounds();
}
