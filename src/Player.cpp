#include "Player.hpp"
#include "GlobalFunctions.h"
#include "Engine.hpp"

using namespace std;
using namespace sf;

const int vieMax = 100;

Player::Player(sf::Vector2f init_position, TEAM team): Entity(100, team), Score(0)
{
     setTexture(*TextureManager::getTexture(getCWD()+"/ressources/ship/Vessel1.bmp"));

    e_m = 15.00f;//vitesse
    e_mx = e_m;
    e_my = e_m;
    m_fx=0.00f;
    m_fy=0.00f;
    d_radius = 25;
    sf::Image tmpimg = image_manager::get_image(getCWD()+"/ressources/ship/Vessel1.bmp");
    sf::Vector2u my_sizeu = tmpimg.getSize();
    sf::Vector2f my_sizef;
    my_sizef.x = (float)my_sizeu.x;
    my_sizef.y = (float)my_sizeu.y;
    setPosition(init_position);

sf::Vector2f ancrage = searchhotspot(tmpimg);

setOrigin(ancrage.x, ancrage.y);

    actual_weapon=0;

    my_weapon.push_back(new AutomaticWeapon(*this, false, 100, ancrage));
    my_weapon.push_back(new ShrapnelWeapon(*this, false, 10, ancrage));
    my_weapon.push_back(new LaserWeapon(*this, true, 0, ancrage));
}

void Player::Shoot()
{
    my_weapon.at(actual_weapon)->fire();
    Engine::getInstance()->getHud()->updateAmmunitions(isTirIllimity(), getAmmunitions());
}

void Player::update()
{
            my_weapon.at(actual_weapon)->updatePosition();



                   if(my_weapon.at(actual_weapon)->isUpdatable())
        {
                     my_weapon.at(actual_weapon)->update();
        }
}

void Player::stopMLAction()//On stop l'action lié à MouseLeft.
{
    if(my_weapon.at(actual_weapon)->isUpdatable())
        {
            my_weapon.at(actual_weapon)->refresh();
        }
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

    Engine::getInstance()->getHud()->updateScore(Score);
}

bool Player::modifierVie(int pv)//fonction Entity::modifierVie() masquée
{
    if(pv > 0 && vie == vieMax){

        return false;
    }
    else{

        vie+=pv;

        if(vie > vieMax){

            vie = vieMax;
        }

        Engine::getInstance()->getHud()->updateLife(vie, vieMax);

        return true;
    }
}

unsigned long Player::getScore()
{
    return Score;
}

void Player::initHud(){

    Engine::getInstance()->getHud()->init(vie, vieMax, Score, getSymboleActualWeapon(), isTirIllimity(), getAmmunitions());
}

int Player::getVieMax() const{

    return vieMax;
}

Player::~Player()
{

}
