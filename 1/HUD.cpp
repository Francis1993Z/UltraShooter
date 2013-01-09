#include "HUD.hpp"

#include "string.h"

using namespace std;
using namespace sf;

HUD::HUD(Player *User, sf::Vector2f Initial_Position, sf::RenderWindow &m_App)
{
    MyRenderWindow=&m_App;

    m_user=User;

    Info_Font.LoadFromFile("times.ttf");

     sprintf(text_Weapon, "Weapon : NULL");


    Weapon.SetFont(Info_Font);
    Weapon.SetSize(26);
    Weapon.SetColor(Color(0,0,0));
    Weapon.SetPosition(370, 20);
    Weapon.SetText(GameOvertxt);

   sprintf(GameOvertxt, "GameOver");

     GameOver.SetFont(Info_Font);
    GameOver.SetSize(46);
    GameOver.SetColor(Color(0,0,0));
    GameOver.SetPosition(MyRenderWindow->GetWidth()/2, MyRenderWindow->GetHeight()/2);
    GameOver.SetText(GameOvertxt);

    sprintf(text_Life, "Life %d", (int)m_user->GetLife());

    //int len = strlen(text_Life);

    Life.SetFont(Info_Font);
    Life.SetSize(26);
    Life.SetColor(Color(0,0,0));
    Life.SetPosition(sf::Vector2f(20,20));
    //Life.SetPosition(Initial_Position);
    Life.SetText(text_Life);

//    sf::Vector2f NextPos = Life.GetCharacterPos(len);


    sprintf(text_Score, "Score %d", (int)m_user->GetScore());
    //len = strlen(text_Score);
    Score.SetFont(Info_Font);
    Score.SetSize(26);
    Score.SetColor(Color(0,0,0));
    Score.SetPosition(sf::Vector2f(270,20));
    //Score.SetPosition(NextPos.x+100, Initial_Position.y);
    Score.SetText(text_Score);
gameover=false;
ShowOutScreenPositionIndicatorX=false;
ShowOutScreenPositionIndicatorY=false;

RectOutX   = sf::Shape::Rectangle(0, 0, 25, 12.5, sf::Color(0,0,0), 1, sf::Color(255,0,0));
RectOutY   = sf::Shape::Rectangle(0, 0, 12.5, 25, sf::Color(0,0,0), 1, sf::Color(255,0,0));

RectOutX.SetCenter(0.00f, 6.25);
RectOutY.SetCenter(6.25, 0.00f);

LargeurWindow=m_App.GetWidth();
HauteurWindow=m_App.GetHeight();
}

void HUD::Update()
{

    sprintf(text_Life, "Life %d", (int)m_user->GetLife());
        Life.SetText(text_Life);
        sprintf(text_Score, "Score %d", (int)m_user->GetScore());
            Score.SetText(text_Score);
/*
            if (m_user->GetWeapon()==2) sprintf(text_Weapon, "Weapon : 2");
            else sprintf(text_Weapon, "Weapon : 1");
            Weapon.SetText(text_Weapon);
*/
if(m_user->GetLife()==0)
{
gameover=true;
}

if(m_user->GetPosition().x<0.00f)
{
    ShowOutScreenPositionIndicatorX=true;

      if(m_user->GetPosition().y<0.00f) RectOutX.SetPosition(0.00f, 0.00f);
    else if(m_user->GetPosition().y>HauteurWindow)   RectOutX.SetPosition(0.00f, HauteurWindow);
   else   RectOutX.SetPosition(0.00f, m_user->GetPosition().y);
   RectOutX.SetRotation(0.00f);


}
else if(m_user->GetPosition().x>LargeurWindow)
{
    ShowOutScreenPositionIndicatorX=true;

   if(m_user->GetPosition().y<0.00f) RectOutX.SetPosition(LargeurWindow, 0.00f);
   else if(m_user->GetPosition().y>HauteurWindow)   RectOutX.SetPosition(LargeurWindow, HauteurWindow);
else RectOutX.SetPosition(LargeurWindow, m_user->GetPosition().y);

      RectOutX.SetRotation(180.00f);
}
else
{
    ShowOutScreenPositionIndicatorX=false;
}

if(m_user->GetPosition().y<0.00f)
{

    ShowOutScreenPositionIndicatorY=true;
         if(m_user->GetPosition().x<0.00f) RectOutY.SetPosition(0.00f, 0.00f);
         else if(m_user->GetPosition().x>LargeurWindow) RectOutX.SetPosition(LargeurWindow, 0.00f);
   else   RectOutY.SetPosition(m_user->GetPosition().x, 0.00f);
      RectOutY.SetRotation(0.00f);

}
else if(m_user->GetPosition().y>HauteurWindow)
{
    ShowOutScreenPositionIndicatorY=true;

            if(m_user->GetPosition().x<0.00f) RectOutY.SetPosition(0.00f, HauteurWindow);
            else if(m_user->GetPosition().x>LargeurWindow) RectOutY.SetPosition(LargeurWindow, HauteurWindow);
            else    RectOutY.SetPosition(m_user->GetPosition().x, HauteurWindow);

      RectOutY.SetRotation(180.00f);
}
else
{
    ShowOutScreenPositionIndicatorY=false;
}


        }

 sf::String HUD::GetWeaponString() const
{
    return GameOver;
}

 sf::String HUD::GetGameOverString() const
{
    return Weapon;
}

sf::String HUD::GetLifeString() const
{
    return Life;
}

sf::String HUD::GetScoreString() const
{
    return Score;
}

bool HUD::ShowIndicatorX() const
{
    return ShowOutScreenPositionIndicatorX;
}

bool HUD::ShowIndicatorY() const
{
 return ShowOutScreenPositionIndicatorY;
}

bool HUD::ShowGameOver() const
{
 return gameover;
}

 sf::Shape HUD::GetIndicatorShapeX() const
 {
     return  RectOutX;
 }

sf::Shape HUD::GetIndicatorShapeY() const
 {
     return  RectOutY;
 }
