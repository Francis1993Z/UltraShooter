#include "Player.hpp"
#include "GlobalFunctions.h"

using namespace std;
using namespace sf;


Player::Player(sf::Vector2f init_position, sf::Font font, sf::Vector2f sizeWindow):Life(100), Score(0), hud(Life, Score, font, sizeWindow)
{
    rayon=50.f;

    Player::setRadius(rayon);
    Player::setFillColor(sf::Color::Red);
    Player::setPosition(init_position);
    Player::setOrigin(50.f, 50.f);
}

/*void Player::SetRenderWindow(sf::RenderWindow &mynewWindow)
{
mynewWindow.co;

}*/

float Player::Shoot(sf::Vector2f TargetPosition, sf::RenderWindow &myRenderWindow)
{
    Vector2i player_pixel_position=Player::GetWindowPosition(myRenderWindow);

    sf::Vector2f converted_player_coord;

    converted_player_coord.x=(float)player_pixel_position.x;
    converted_player_coord.y=(float)player_pixel_position.y;

    float x1=converted_player_coord.x;
    float y1=converted_player_coord.y;
    float x2=TargetPosition.x;
    float y2=TargetPosition.y;
    float a=x2-x1;
    float o=y2-y1;
    float angle;

    return  angle = atan2(-o, a);

//return GetAngle_v2f(Player::getPosition(), TargetPosition);
}

sf::Vector2i Player::GetWindowPosition(sf::RenderWindow &theRenderWindow) const
{
    return theRenderWindow.mapCoordsToPixel(Player::getPosition(), theRenderWindow.getView());
}

sf::Text Player::getLifeHud()
{
    return hud.getLife();
}

sf::Text Player::getScoreHud()
{
    return hud.getScore();
}

void Player::setSizeWindowHud(sf::Vector2f sizeWindow)
{
    hud.setSizeWindow(sizeWindow);
}

float Player::getRayon(){

    return rayon;
}

 Player::~Player()
{

}
