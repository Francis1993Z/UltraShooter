#include "Splitter.hpp"
#include "Engine.hpp"
#include "Entity.hpp"

using namespace std;
using namespace sf;

Splitter::Splitter(Vector2f init_Position, Entity& init_Target, unsigned int level, TEAM team)
    :Zombie(init_Position, init_Target, team)
{
    setTexture(*TextureManager::getTexture(getCWD()+"/ressources/ship/Raider.bmp"));

        sf::Image tmpimg = image_manager::get_image(getCWD()+"/ressources/ship/Raider.bmp");
    sf::Vector2u my_sizeu = tmpimg.getSize();
    sf::Vector2f my_sizef;
    my_sizef.x = (float)my_sizeu.x;
    my_sizef.y = (float)my_sizeu.y;
    setPosition(init_Position);
    setOrigin(my_sizef.x/2, my_sizef.x/2);
    float m_size = my_sizef.x;
    float n_size = m_size;
    sf::Vector2f my_size;
    my_level = level;

    e_m = 4;//vitesse
    e_mx = e_m;
    e_my = e_m;

    kill_point = 5;
    vie=7500;
    if (level == 2)
        {
            n_size = m_size / 2;
            kill_point = kill_point * 2;
            vie=25;
            e_mx = e_m * 2;
            e_my = e_m * 2;
            setScale(0.5, 0.5);
        }
    else if (level == 3)
        {
            n_size = m_size / 4;
            kill_point = kill_point * 4;
            vie=10;
            e_mx=e_m*4;
            e_my=e_m*4;
            setScale(0.25, 0.25);
        }
    else if (level == 4)
        {
            n_size = m_size / 8;
            kill_point = kill_point * 8;
            vie=1;
            e_mx=e_m*8;
            e_my=e_m*8;
        }

    my_size.x=n_size;
    my_size.y=n_size;




    d_radius=n_size/2;

    //my_behaviour = ATTACK;
    my_behaviour = STANDBY;

    Vector2f t_pos=my_target->getPosition();

    float a = t_pos.x-init_Position.x;
    float o = t_pos.y-init_Position.y;
    float angle = atan2(-o, a);

    float myrotation = angle;

    setRotation(myrotation);

    m_fx=0.00f;
    m_fy=0.00f;
}


unsigned int Splitter::getNextLevel() const
{
    unsigned int next_level=my_level+1;
    return next_level=my_level+1;
}

unsigned int Splitter::getLevel() const
{
    return my_level;
}

unsigned int Splitter::die() const
{
    if (getLevel() != 3)//le niveau 4 est extremement rapide et petit. C'est trop difficile.
        {
            float rp = getRotation();
            float s_distance = Entity::get_dRadius();

            unsigned int next_level;

            sf::Vector2f base_splitter_pos=getPosition();
            sf::Vector2f NewSplittersPosition1, NewSplittersPosition2;

            ///Calcul des positions des deux nouveaux Splitters pour qu'ils soient séparés
            NewSplittersPosition1.x=((cos(rp*M_PI/180)*s_distance))+base_splitter_pos.x;
            NewSplittersPosition1.y=(-(sin(rp*M_PI/180)*s_distance))+base_splitter_pos.y;
            NewSplittersPosition2.x=(cos(rp*M_PI/180)*(-s_distance))+base_splitter_pos.x;
            NewSplittersPosition2.y=-(sin(rp*M_PI/180)*(-s_distance))+base_splitter_pos.y;

            next_level = getNextLevel();

            Map *tmp_map = Engine::getInstance()->getMap();
            tmp_map->addEnnemy(new Splitter(NewSplittersPosition1, *my_target, next_level, getTeam()));
            tmp_map->addEnnemy(new Splitter(NewSplittersPosition2, *my_target, next_level, getTeam()));

        }
    return getKillPoint();
}
