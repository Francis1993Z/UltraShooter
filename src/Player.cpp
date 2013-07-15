#include "Player.hpp"
#include "GlobalFunctions.h"
#include "Engine.hpp"

using namespace std;
using namespace sf;


Player::Player(sf::Vector2f init_position, sf::Font font, sf::Vector2f sizeWindow):Life(100), Score(0), hud(Life, Score, font, sizeWindow)
{
    rayon=50.f;

    Player::setRadius(rayon);
    Player::setFillColor(sf::Color::Blue);
    Player::setPosition(init_position);
    Player::setOrigin(50.f, 50.f);
}

/*void Player::SetRenderWindow(sf::RenderWindow &mynewWindow)
{
mynewWindow.co;

}*/

float Player::Shoot(sf::Vector2f TargetPosition, sf::RenderWindow &myRenderWindow)
{
    Vector2i player_pixel_position = GetWindowPosition(myRenderWindow);

    Vector2f converted_player_coord;
    converted_player_coord.x=(float)player_pixel_position.x;
    converted_player_coord.y=(float)player_pixel_position.y;

    float x1 = converted_player_coord.x;
    float y1 = converted_player_coord.y;

    float x2 = TargetPosition.x;
    float y2 = TargetPosition.y;

    float a = x2 - x1;
    float o = y2 - y1;
    cout<<" x1 :"<<x1<<" y1 :"<<y1<<endl;
    cout<<" x2 :"<<x2<<" y2 :"<<y2<<endl;
    float angle;

    weapon_clock.restart();

    converted_player_coord.x=(float)player_pixel_position.x;
    converted_player_coord.y=(float)player_pixel_position.y;

    Engine::getInstance()->getMusicManager()->playEvent("ressources/sounds/events/sf_laser_18.ogg");

    return  angle = atan2(-o, a);

//return GetAngle_v2f(Player::getPosition(), TargetPosition);
}

bool Player::ReadyToShoot() const
{
    Int32 time=weapon_clock.getElapsedTime().asMilliseconds();

    if (time > 80)
        return true;
    else
        return false;
}

Vector2i Player::GetWindowPosition(sf::RenderWindow &theRenderWindow) const
{
    return theRenderWindow.mapCoordsToPixel(Player::getPosition(), theRenderWindow.getView());
}

Text Player::getLifeHud()
{
    return hud.getLife();
}

Text Player::getScoreHud()
{
    return hud.getScore();
}

void Player::move_myhud(float vx, float vy)
{
    hud.Move(vx, vy);
}

void Player::setSizeWindowHud(Vector2f sizeWindow)
{
    hud.setSizeWindow(sizeWindow);
}

float Player::getRayon()
{

    return rayon;
}

float Player::getVitesse() const
{

    return vitesse;
}

sf::FloatRect Player::getCollisionBox()
{

    return getGlobalBounds();
}

void Player::addPoints(int p)
{
    Score=Score+p;
    cout<<Score<<endl;
    hud.updateScore(Score);
}

Player::~Player()
{

}
