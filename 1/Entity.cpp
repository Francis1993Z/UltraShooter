#include "Entity.hpp"
using namespace std;

void Entity::sePresenter() const
{
    cout<<"Je suis une Entity."<<endl;
}

 sf::Vector2f Entity::GetPosition() const
  {
      //return PlayerShape.GetPosition();
      return StandAnim.GetPosition();
  }

Entity& Entity::getAdresse()
{
    return  *this;
}

    Entity::~Entity()
{

}
/*
AABB UpdateRectPoint(unsigned int Width, unsigned int Height, float Angle, Vector2f RectPos)
{

float hs,ls,hc,lc;
	{
		float c=cosf(Angle*M_PI/180);	// s et c sont définis dans l'accolade donc sont détruites lorsqu'on en sort
		float s=sinf(Angle*M_PI/180); // car ne nous servent plus

		hs=Height*s/2;
		ls=Width*s/2;
		hc=Height*c/2;
		lc=Width*c/2;
	}

	float x=RectPos.x;
	float y=RectPos.y;

AABB RectAABB;

	// Ecriture des résultats aux adresses données en paramètre
	RectAABB.A.x = x- lc - hs; // x - largeur*cos(angle)/2 - hauteur*sin(angle)/2
	RectAABB.B.x = x+ lc - hs; // x + largeur*cos(angle)/2 - hauteur*sin(angle)/2
	RectAABB.C.x = x+lc + hs; // x + largeur*cos(angle)/2 + hauteur*sin(angle)/2
	RectAABB.D.x = x-lc + hs; // x - largeur*cos(angle)/2 + hauteur*sin(angle)/2

	RectAABB.A.y = y- hc + ls; // y + hauteur*cos(angle)/2 - largeur*sin(angle)/2 échanger les signe
	RectAABB.B.y =  y-hc - ls; // y + hauteur*cos(angle)/2 + largeur*sin(angle)/2
	RectAABB.C.y = y+hc - ls; // y - hauteur*cos(angle)/2 + largeur*sin(angle)/2
	RectAABB.D.y = y+hc + ls; // y - hauteur*cos(angle)/2 - largeur*sin(angle)/2

return RectAABB;
}
*/
