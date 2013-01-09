#include "Bullet.h"


using namespace std;
using namespace sf;

Bullet::Bullet(Vector2f Initial_Position, int Damage, float angle, RenderWindow *APP)
{
    vitesse=15;
    damage=Damage;
    ProjectilePosition.x=Initial_Position.x;
    ProjectilePosition.y=Initial_Position.y;

//            int R = sf::Randomizer::Random(0, 255);
//        int G = sf::Randomizer::Random(0, 255);
  //      int B = sf::Randomizer::Random(0, 255);
        sf::Color bulletcolor;
        int color=sf::Randomizer::Random(0, 5);
        switch(color)
        {
        case 0:
                        bulletcolor=sf::Color::Yellow;
            break;

        case 1:
                        bulletcolor=sf::Color::Green;
            break;

        case 2:
                        bulletcolor=sf::Color::Blue;
            break;

        case 3:
                        bulletcolor=sf::Color::Red;
            break;

        default:
            bulletcolor=sf::Color::Black;
            break;
        }

rayon=3;
Shape tmpShape = Shape::Circle(0, 0, rayon, sf::Color::Black);
    ProjectileSprite = tmpShape;
    ProjectileSprite.SetPosition(Initial_Position);
    ProjectileSprite.SetCenter(ProjectileSprite.GetScale().x/2,ProjectileSprite.GetScale().y/2);

    ProjectileSprite.SetRotation(angle/ M_PI * 180);
   //cout<<"Angle : "<<angle/ M_PI * 180<<endl;
    WinWidth=APP->GetWidth();
    WinHeight=APP->GetHeight();
    grow=true;
}
//Shape Circle = Shape::Circle(X, Y, Rayon, Couleur, [Bordure], [CouleurBordure]);

void Bullet::UpdatePosition()
{


    vx=cos(ProjectileSprite.GetRotation()*M_PI/180) * vitesse;
    vy=sin(ProjectileSprite.GetRotation()*M_PI/180) * vitesse;

    ProjectileSprite.Move(vx,-vy);
    //cout<<"X : "<<ProjectilePosition.x<<" Y : "<<ProjectilePosition.y<<endl;

}

/*bool Bullet::TestCollision(Point tab[4])
{
  int i;
  for(i=0;i<4;i++)
  {
     Point A = tab[i];
     Point B;
     if (i==4-1)  // si c'est le dernier point, on relie au premier
         B = tab[0];
     else           // sinon on relie au suivant.
         B = tab[i+1];
     Vecteur D,T;
     D.x = B.x - A.x;
     D.y = B.y - A.y;
     T.x = ProjectileSprite.GetPosition().x - A.x;
     T.y = ProjectileSprite.GetPosition().y - A.y;
float d = D.x*T.y - D.y*T.x;
     if (d>0)
        return false;  // un point à droite et on arrête tout.
  }
  return true;  // si on sort du for, c'est qu'aucun point n'est à gauche, donc c'est bon.
}
*/
float Bullet::GetRayon() const
{
    return rayon;
}


int Bullet::Hit() const
{
    return damage;
}

Bullet::~Bullet()
{

}





