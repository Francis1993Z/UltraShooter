#include "AutomaticWeapon.hpp"

#include "Engine.hpp"

using namespace std;
using namespace sf;

AutomaticWeapon::AutomaticWeapon(Entity const& my_user, bool p_tirIllimity, unsigned int p_ammunitions, sf::Vector2f pos) : Weapon(p_tirIllimity, p_ammunitions, pos)
{
        setTexture(*TextureManager::getTexture(getCWD()+"/ressources/turret/Auto.bmp"));

        sf::Image tmpimg = image_manager::get_image(getCWD()+"/ressources/turret/Auto.bmp");
    sf::Vector2u my_sizeu = tmpimg.getSize();
    sf::Vector2f my_sizef;
    my_sizef.x = (float)my_sizeu.x;
    my_sizef.y = (float)my_sizeu.y;
    setPosition(init_Position);
    setOrigin(my_sizef.x/2, my_sizef.x/2);


    user=&my_user;
    fire_intervale = 150.00f;
    update();
    needRefresh=false;
    symbole = (*(Engine::getInstance()->getLoadFiles()->getSymboleAutomaticWeapon()));
}

void AutomaticWeapon::fire()
{
    if((tirIllimity || (!tirIllimity && ammunitions > 0)) && fire_intervale_clock.getElapsedTime().asMilliseconds() >= fire_intervale)
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


            Engine::getInstance()->getMap()->addProjectile(new Bullet(user->getPosition(), angle, user->getTeam()));

            if(!tirIllimity){

                --ammunitions;
            }
        }
}

void AutomaticWeapon::fire(sf::Vector2f target_position)
{
    if((tirIllimity || (!tirIllimity && ammunitions > 0)) && fire_intervale_clock.getElapsedTime().asMilliseconds() >= fire_intervale)
        {

            sf::Vector2f converted_target_coord;//la position de la souris est en int
            converted_target_coord.x=(float)target_position.x;//donc on la convertie en float car Player::Shoot(sf::Vector2f, sf::RenderWindow &myRenderWindow)
            converted_target_coord.y=(float)target_position.y;//sf::Vector2f est en float


            Engine::getInstance()->getMusicManager()->playEvent("ressources/sounds/events/sf_laser_18.ogg");

            Vector2i player_pixel_position = Engine::getInstance()->getRenderWindow()->mapCoordsToPixel(user->getPosition(), Engine::getInstance()->getRenderWindow()->getView());

            Vector2f converted_player_coord;
            converted_player_coord.x=(float)player_pixel_position.x;
            converted_player_coord.y=(float)player_pixel_position.y;

            float x1 = user->getPosition().x;
            float y1 = user->getPosition().y;

            float x2 = converted_target_coord.x;
            float y2 = converted_target_coord.y;

            float a = x2 - x1;
            float o = y2 - y1;
            float angle = atan2(-o, a);

            fire_intervale_clock.restart();


            Engine::getInstance()->getMap()->addProjectile(new Bullet(user->getPosition(), angle, user->getTeam()));

            if(!tirIllimity){

                --ammunitions;
            }
        }
}
