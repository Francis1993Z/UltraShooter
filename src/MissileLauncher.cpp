#include "MissileLauncher.hpp"

#include "Engine.hpp"

using namespace std;
using namespace sf;

MissileLauncher::MissileLauncher(Entity const& my_user, bool p_tirIllimity, unsigned int p_ammunitions, sf::Vector2f pos):Weapon(p_tirIllimity, p_ammunitions, pos)
{
            setTexture(*TextureManager::getTexture(getCWD()+"/ressources/turret/Auto.bmp"));

        sf::Image tmpimg = image_manager::get_image(getCWD()+"/ressources/turret/Auto.bmp");
    sf::Vector2u my_sizeu = tmpimg.getSize();
    sf::Vector2f my_sizef;
    my_sizef.x = (float)my_sizeu.x;
    my_sizef.y = (float)my_sizeu.y;

    setOrigin(my_sizef.x/2, my_sizef.x/2);
      user=&my_user;
updatePosition();

    fire_intervale = 500.00f;
    needRefresh=false;//?
}


void MissileLauncher::fire()
{
    if((tirIllimity || (!tirIllimity && ammunitions > 0)) && fire_intervale_clock.getElapsedTime().asMilliseconds() >= fire_intervale)
        {
            if(!tirIllimity){

                --ammunitions;
            }
        }
}
