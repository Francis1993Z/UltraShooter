#include "AutomaticWeapon.hpp"

using namespace std;
using namespace sf;

AutomaticWeapon::AutomaticWeapon()
{

}

void AutomaticWeapon::fire(sf::Vector2f TargetPosition, sf::Vector2f player_pos)
{

/*
   Engine::getInstance()->getMusicManager()->playEvent("ressources/sounds/events/sf_laser_18.ogg");


    Vector2i player_pixel_position = Engine::getInstance()->getRenderWindow()->mapCoordsToPixel(player_pos, Engine::getInstance()->getRenderWindow()->getView());

    Vector2f converted_player_coord;
    converted_player_coord.x=(float)player_pixel_position.x;
    converted_player_coord.y=(float)player_pixel_position.y;

    float x1 = converted_player_coord.x;
    float y1 = converted_player_coord.y;

    float x2 = TargetPosition.x;
    float y2 = TargetPosition.y;

    float a = x2 - x1;
    float o = y2 - y1;
    float angle;

    fire_intervale.restart();

    converted_player_coord.x=(float)player_pixel_position.x;
    converted_player_coord.y=(float)player_pixel_position.y;

    angle = atan2(-o, a);

    tmp_map->addBullet(Bullet(player_pos, angle));
*/
}
