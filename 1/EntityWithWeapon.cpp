#include "EntityWithWeapon.hpp"

using namespace std;
/*
    sf::Vector2f fpspos(10,10), InitialLightRayPosition(0, Hauteur/2);
  cFPS fps(fpspos, sf::Color::Black);

float MouseX;
float MouseY;

sf::Image pixel;
pixel.Create(2,2,sf::Color(255,0,0));

std::vector<sf::Sprite> LightRay;

float LightRayAngle = 5;

for(int l=0;l<=3000;l++)
{
sf::Vector2f pixelposition;
pixelposition.x=(cos(LightRayAngle*M_PI/180)*l)+InitialLightRayPosition.x;
pixelposition.y=(sin(LightRayAngle*M_PI/180)*l)+InitialLightRayPosition.y;
LightRay.push_back(sf::Sprite(pixel, pixelposition));
cout<<"x:"<<LightRay.at(l).GetPosition().x<<"y:"<<LightRay.at(l).GetPosition().y<<endl;
}*/



  EntityWithWeapon::EntityWithWeapon(Weapon StartWeapon)
  {

  }


bool EntityWithWeapon::ReadyToShoot() const
{
    //cout<<"timer: "<<FireRate-FireRateClock.GetElapsedTime()<<endl;
if(FireRate-FireRateClock.GetElapsedTime()<0)  return true;
else return false;

}

void EntityWithWeapon::Shoot(std::vector<Bullet> & bullet_array, sf::Vector2f MousePosition)
{

          if(MyRenderWindow->GetInput().IsMouseButtonDown(sf::Mouse::Left)==true)
    {
FireRateClock.Reset();

   if(CurrentWeapon == SHOTGUN)
   {
    sf::Vector2f tmppos=StandAnim.GetPosition();
                float aimangle = GetAngle(tmppos.x, tmppos.y, MousePosition.x, MousePosition.y);
                float aimangle2 = aimangle+0.05;
                float aimangle3 = aimangle+0.1;
                float aimangle4 = aimangle-0.1;
                float aimangle5 = aimangle-0.05;
                bullet_array.push_back(Bullet(StandAnim.GetPosition(),1, aimangle2, MyRenderWindow));
                bullet_array.push_back(Bullet(StandAnim.GetPosition(),1, aimangle3, MyRenderWindow));
                bullet_array.push_back(Bullet(StandAnim.GetPosition(),1000, aimangle4, MyRenderWindow));
                bullet_array.push_back(Bullet(StandAnim.GetPosition(),1, aimangle5, MyRenderWindow));
                bullet_array.push_back(Bullet(StandAnim.GetPosition(),1, aimangle, MyRenderWindow));
   }
      else if(CurrentWeapon == MACHINEGUN)
    {
    sf::Vector2f tmppos=StandAnim.GetPosition();
                float aimangle = GetAngle(tmppos.x, tmppos.y, MousePosition.x, MousePosition.y);
                bullet_array.push_back(Bullet(StandAnim.GetPosition(),100, aimangle, MyRenderWindow));

    }

   else
    {
    sf::Vector2f tmppos=GetPosition();
                float aimangle = GetAngle(tmppos.x, tmppos.y, MousePosition.x, MousePosition.y);
                bullet_array.push_back(Bullet(GetPosition(),1, aimangle, MyRenderWindow));

    }

}

    /*if(o_App.GetInput().IsMouseButtonDown(sf::Mouse::Left)==true)
    {
if(FireRateClock.GetElapsedTime()>=FireRate)
{
    FireRateClock.Reset();
}
*/
}

void EntityWithWeapon::ChangeWeapon(Weapon NewWeapon)
{
    if(UnlockedWeaponList[NewWeapon]==false) cout<<"You're using an illegal weapon! F*cking bastard!"<<endl;
    CurrentWeapon = NewWeapon;
}

void EntityWithWeapon::NextWeapon()
{
    cout<<"CurrentWeapon : "<<CurrentWeapon<<endl;

     unsigned int NextFutureWeapon=CurrentWeapon+1;
         unsigned int FutureWeapon = CurrentWeapon + NextFutureWeapon;
    while(CurrentWeapon != FutureWeapon)
    {
    FutureWeapon = CurrentWeapon + NextFutureWeapon;
        cout<<"CurrentWeapon : "<<CurrentWeapon<<endl;
        cout<<"FutureWeapon : "<<FutureWeapon<<endl;
        cout<<"NextFutureWeapon : "<<NextFutureWeapon<<endl;
        if(UnlockedWeaponList[FutureWeapon]==true)
        {
            CurrentWeapon = FutureWeapon;
                    cout<<"CHANGE CurrentWeapon : "<<CurrentWeapon<<endl;
        }
        else if(NextFutureWeapon==WEAPONS_LIST_LIMIT)
        {
            NextFutureWeapon = WEAPONS_LIST_LIMIT-WEAPONS_LIST_LIMIT;
                cout<<"LIST LIMIT NextFutureWeapon : "<<NextFutureWeapon<<endl;
            }
        else
        {
            NextFutureWeapon++;
            }
}
    cout<<"CurrentWeapon : "<<CurrentWeapon<<endl;
}

void EntityWithWeapon::PreviousWeapon()
{
        cout<<"CurrentWeapon : "<<CurrentWeapon<<endl;
     unsigned int PreviousFutureWeapon=10;
    while(CurrentWeapon != PreviousFutureWeapon)
    {
    unsigned int FutureWeapon = CurrentWeapon - PreviousFutureWeapon;
            cout<<"FutureWeapon : "<<FutureWeapon<<endl;
        cout<<"PreviousFutureWeapon : "<<PreviousFutureWeapon<<endl;
        if(UnlockedWeaponList[FutureWeapon]==true) CurrentWeapon = FutureWeapon;
        else if(PreviousFutureWeapon==WEAPONS_LIST_LIMIT-WEAPONS_LIST_LIMIT) PreviousFutureWeapon = WEAPONS_LIST_LIMIT;
        else PreviousFutureWeapon--;
}
    cout<<"CurrentWeapon : "<<CurrentWeapon<<endl;
}
