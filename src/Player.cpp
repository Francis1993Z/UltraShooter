#include "Player.hpp"
#include "GlobalFunctions.h"
#include "Engine.hpp"

using namespace std;
using namespace sf;



Player::Player(sf::Vector2f init_position, sf::Font font, sf::Vector2f sizeWindow, TEAM team): Entity(10000, team), Score(0), hud(vie, Score, font, sizeWindow)
{
    e_m = 15.00f;//vitesse
    e_mx = e_m;
    e_my = e_m;
    m_fx=0.00f;
    m_fy=0.00f;
    d_radius = 25;
    sf::Vector2f my_size;
    my_size.x=50;
    my_size.y=50;
    setSize(my_size);
    setFillColor(sf::Color::Blue);
    setPosition(init_position);
    setOrigin(my_size.x/2, my_size.x/2);
    actual_weapon=0;

    my_weapon.push_back(new AutomaticWeapon(*this));
    my_weapon.push_back(new ShrapnelWeapon(*this));
    my_weapon.push_back(new LaserWeapon(*this));
}

void Player::Shoot()
{
    my_weapon.at(actual_weapon)->fire();
}

void Player::stopMLAction()//On stop l'action lié à MouseLeft.
{
    if(my_weapon.at(actual_weapon)->isUpdatable())
        {
            my_weapon.at(actual_weapon)->refresh();
        }
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

targetdata Player::getTarget() const
{

    sf::Vector2i localMousePosition = sf::Mouse::getPosition(*Engine::getInstance()->getRenderWindow());

    sf::Vector2f converted_target_coord;//la position de la souris est en int
    converted_target_coord.x=(float)localMousePosition.x;//donc on la convertie en float car Player::Shoot(sf::Vector2f, sf::RenderWindow &myRenderWindow)
    converted_target_coord.y=(float)localMousePosition.y;//sf::Vector2f est en float


    //Engine::getInstance()->getMusicManager()->playEvent("ressources/sounds/events/sf_laser_18.ogg");

    Vector2i player_pixel_position = Engine::getInstance()->getRenderWindow()->mapCoordsToPixel(getPosition(), Engine::getInstance()->getRenderWindow()->getView());

    Vector2f converted_player_coord;
    converted_player_coord.x=(float)player_pixel_position.x;
    converted_player_coord.y=(float)player_pixel_position.y;

    float x1 = converted_player_coord.x;
    float y1 = converted_player_coord.y;

    float x2 = converted_target_coord.x;
    float y2 = converted_target_coord.y;

    float a = x2 - x1;
    float o = y2 - y1;
    float angle = atan2(-o, a);
    targetdata data;
    data.angle=angle;
    data.position=converted_target_coord;
    return data;
}

void Player::addPoints(int points)
{
    Score+=points;

    hud.updateScore(Score);
}

void Player::modifierVie(int pv)//fonction Entity::modifierVie() masquée
{
    vie+=pv;
    hud.updateLife(vie);
}

unsigned long Player::getScore()
{
    return Score;
}

Player::~Player()
{

}
