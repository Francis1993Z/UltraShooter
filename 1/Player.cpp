#include "Player.hpp"

using namespace std;
using namespace sf;


 Player::Player(float X, float Y, sf::Color Couleur, float Rayon, float Bordure, sf::Color CouleurBordure, Weapon StartWeapon, sf::RenderWindow &m_App, ImageManager &m_ImgManager) : EntityWithWeapon(StartWeapon)
{
    /*------------------------------------------------------------------------------------------------*/
    CurrentWeapon=MACHINEGUN;
    UnlockedWeaponList[CurrentWeapon] = true;
        UnlockedWeaponList[SHOTGUN] = true;

        for(int AllWeapons=SHOTGUN+1;AllWeapons<WEAPONS_LIST_LIMIT;AllWeapons++)
{
        UnlockedWeaponList[AllWeapons] = false;
}
/*------------------------------------------------------------------------------------------------*/
    IamImmune=true;
    ImmuneTime=3;
    Life=5;
    Score=0;
     cout<<"Life : "<<Life<<endl;
    //rayon=Rayon;
    sf::Shape Circle = Shape::Circle(0, 0, rayon, Couleur, Bordure, CouleurBordure);
Circle.SetPosition(X,Y);
    PlayerShape = Circle;
    FireRate=0.1;
FireRateClock.GetElapsedTime();
MyRenderWindow=&m_App;


StandSprites.push_back(sf::Sprite(*m_ImgManager.GetImage("sprites/player/Stand/player_stand_2.png", sf::Color(255,255,255))));
StandSprites.push_back(sf::Sprite(*m_ImgManager.GetImage("sprites/player/Stand/player_stand_3.png", sf::Color(255,255,255))));
StandSprites.push_back(sf::Sprite(*m_ImgManager.GetImage("sprites/player/Stand/player_stand_4.png", sf::Color(255,255,255))));
StandSprites.push_back(sf::Sprite(*m_ImgManager.GetImage("sprites/player/Stand/player_stand_5.png", sf::Color(255,255,255))));
StandSprites.push_back(sf::Sprite(*m_ImgManager.GetImage("sprites/player/Stand/player_stand_6.png", sf::Color(255,255,255))));
StandSprites.push_back(sf::Sprite(*m_ImgManager.GetImage("sprites/player/Stand/player_stand_7.png", sf::Color(255,255,255))));
StandSprites.push_back(sf::Sprite(*m_ImgManager.GetImage("sprites/player/Stand/player_stand_8.png", sf::Color(255,255,255))));

StandAnim.push_back(&StandSprites.at(0));
StandAnim.push_back(&StandSprites.at(1));
StandAnim.push_back(&StandSprites.at(2));
StandAnim.push_back(&StandSprites.at(3));
StandAnim.push_back(&StandSprites.at(4));
StandAnim.push_back(&StandSprites.at(5));
StandAnim.push_back(&StandSprites.at(6));

StandAnim.SetPosition(X,Y);
StandAnim.SetCenter(StandSprites.at(0).GetSize().x/2, StandSprites.at(0).GetSize().y/2);
   rayon=StandSprites.at(0).GetSize().x/2;

}

void Player::ApplyVelocity(sf::Vector2f velocity)
{
    Velocity = velocity;
}

void Player::Update()
{
    PlayerShape.Move(Velocity);
    Velocity.x=0.00f;
    Velocity.y=0.00f;
}

void Player::Update(float x, float y)
{

    //PlayerShape.Move(x,y);
    StandAnim.Move(x,y);
}

void Player::SetDelayAnimation(float NewDelay)
{
StandAnim.setDelay(NewDelay);
}

void Player::UpdateEvent(sf::RenderWindow &f_App)
{
    if(IamImmune==true)
    {
        if(ImmunityClock.GetElapsedTime()>=ImmuneTime)
        {
            //PlayerShape.SetColor(sf::Color::Blue);
            IamImmune=false;
        }
    }

  if(f_App.GetInput().IsKeyDown(sf::Key::Up))
    {
                            //PlayerShape.Move(0.00f, -10.00f);
                               StandAnim.Move(0.00f, -10.00f);
    }
  else if(f_App.GetInput().IsKeyDown(sf::Key::Down))
    {
                                 //PlayerShape.Move(0.00f, 10.00f);
                                    StandAnim.Move(0.00f, 10.00f);
    }


  if(f_App.GetInput().IsKeyDown(sf::Key::Left))
    {
                           //PlayerShape.Move(-10.00f, 0.00f);
                               StandAnim.Move(-10.00f, 0.00f);
    }
  else if(f_App.GetInput().IsKeyDown(sf::Key::Right))
    {
           //PlayerShape.Move(10.00f, 0.00f);
              StandAnim.Move(10.00f, 0.00f);
    }

      /*if(f_App.GetInput().IsKeyDown(sf::Key::Space))
    {
         if (weapon<=1) weapon++;
         else if(weapon>=2) weapon--;
    }*/

}





 sf::Shape Player::GetShape() const
 {
     return PlayerShape;
 }

LayerAnim Player::GetAnim() const
 {
     return StandAnim;
 }




float Player::GetRayon() const
{
    return rayon;
}

void Player::Death()
{
    Life--;
    PlayerShape.SetPosition(MyRenderWindow->GetWidth()/2, MyRenderWindow->GetHeight()/2);
                PlayerShape.SetColor(sf::Color::Magenta);
 cout<<"Life : "<<Life<<endl;
    IamImmune=true;
    ImmunityClock.Reset();
}

void Player::AddPoint(int point)
{
Score+=point;
}

bool Player::Immunity() const
{
 return IamImmune;
}

int Player::GetScore() const
{
    return Score;
}

int Player::GetLife() const
{
    return Life;
}
/*
int Player::GetWeapon() const
{
    return weapon;
}
*/
