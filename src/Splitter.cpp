#include "Splitter.hpp"
#include "Engine.hpp"
#include "Player.hpp"

using namespace std;
using namespace sf;

Splitter::Splitter(Vector2f init_Position, Player& init_Target, unsigned int level, TEAM team)
    :Zombie(init_Position, init_Target, team)
{
    float m_size = 100;
    float n_size = m_size;
    sf::Vector2f my_size;
    my_level = level;

    e_m = 4;
    e_mx = e_m;
    e_my = e_m;

    kill_point = 5;
vie=75;
    if (level == 2)
        {
            n_size = m_size / 2;
            kill_point = kill_point * 2;
vie=25;
            e_mx = e_m * 2;
            e_my = e_m * 2;
        }
    else if (level == 3)
        {
            n_size = m_size / 4;
            kill_point = kill_point * 4;
vie=10;
            e_mx=e_m*4;
            e_my=e_m*4;
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
    setSize(my_size);

    setOrigin(Vector2f(my_size.x / 2, my_size.y / 2));
    setFillColor(Color::Green);

    d_radius=n_size/2;

    my_behaviour=ATTACK;

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
            Player *tmp_player = Engine::getInstance()->getPlayer();
            tmp_map->addEnnemy(new Splitter(NewSplittersPosition1, *tmp_player, next_level, getTeam()));
            tmp_map->addEnnemy(new Splitter(NewSplittersPosition2, *tmp_player, next_level, getTeam()));

        }
    return getKillPoint();
}
