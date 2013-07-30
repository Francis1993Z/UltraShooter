#include "AutomaticWeapon.hpp"

#include "Engine.hpp"

using namespace std;
using namespace sf;

AutomaticWeapon::AutomaticWeapon(sf::Shape const& my_user)
{
    user=&my_user;
    fire_intervale = 150.00f;
}

void AutomaticWeapon::fire()
{
    if(fire_intervale_clock.getElapsedTime().asMilliseconds() >= fire_intervale)
        {

            sf::Vector2i localMousePosition = sf::Mouse::getPosition(*Engine::getInstance()->getRenderWindow());

            sf::Vector2f converted_target_coord;//la position de la souris est en int
            converted_target_coord.x=(float)localMousePosition.x;//donc on la convertie en float car Player::Shoot(sf::Vector2f, sf::RenderWindow &myRenderWindow)
            converted_target_coord.y=(float)localMousePosition.y;//sf::Vector2f est en float


            Engine::getInstance()->getMusicManager()->playEvent("ressources/sounds/events/sf_laser_18.ogg");

            Vector2i player_pixel_position = Engine::getInstance()->getRenderWindow()->mapCoordsToPixel(user->getPosition(), Engine::getInstance()->getRenderWindow()->getView());

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

            fire_intervale_clock.restart();


            Engine::getInstance()->getMap()->addBullet(Bullet(user->getPosition(), angle));
        }
}
