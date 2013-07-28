#include "MissileLauncher.hpp"

#include "Engine.hpp"

using namespace std;
using namespace sf;

MissileLauncher::MissileLauncher(Entity const& my_user)
{
    user=&my_user;
    fire_intervale = 500.00f;
}


void MissileLauncher::fire()
{
if(fire_intervale_clock.getElapsedTime().asMilliseconds() >= fire_intervale)
{


}
}
