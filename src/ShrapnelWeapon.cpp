#include "ShrapnelWeapon.hpp"

#include "Engine.hpp"

using namespace std;
using namespace sf;

ShrapnelWeapon::ShrapnelWeapon(Entity const& my_user, bool p_tirIllimity, unsigned int p_ammunitions, sf::Vector2f pos):Weapon(p_tirIllimity, p_ammunitions, pos)
{
            setTexture(*TextureManager::getTexture(getCWD()+"/ressources/turret/Shrapnel.bmp"));

        sf::Image tmpimg = image_manager::get_image(getCWD()+"/ressources/turret/Shrapnel.bmp");
    sf::Vector2u my_sizeu = tmpimg.getSize();
    sf::Vector2f my_sizef;
    my_sizef.x = (float)my_sizeu.x;
    my_sizef.y = (float)my_sizeu.y;

    setOrigin(my_sizef.x/2, my_sizef.x/2);
       user=&my_user;
updatePosition();

    fire_intervale = 150.00f;
    needRefresh=false;
    symbole = (*(Engine::getInstance()->getLoadFiles()->getSymboleShrapnelWeapon()));
}

void ShrapnelWeapon::fire()
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


            float aimangle2 = angle+0.05;
            float aimangle3 = angle+0.1;
            float aimangle4 = angle-0.1;
            float aimangle5 = angle-0.05;

            Engine::getInstance()->getMap()->addProjectile(new Bullet(getPosition(), angle, user->getTeam()));

            Engine::getInstance()->getMap()->addProjectile(new Bullet(getPosition(), aimangle2, user->getTeam()));

            Engine::getInstance()->getMap()->addProjectile(new Bullet(getPosition(), aimangle3, user->getTeam()));

            Engine::getInstance()->getMap()->addProjectile(new Bullet(getPosition(), aimangle4, user->getTeam()));

            Engine::getInstance()->getMap()->addProjectile(new Bullet(getPosition(), aimangle5, user->getTeam()));

            if(!tirIllimity){

                --ammunitions;
            }
        }
}
