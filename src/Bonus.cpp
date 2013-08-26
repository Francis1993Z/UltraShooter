 #include "Bonus.hpp"
 #include "Engine.hpp"

 using namespace sf;
 using namespace std;

Bonus::Bonus(Vector2f pos)
{
    setPosition(pos);
    Vector2f my_size;
    my_size.x=25;
    my_size.y=25;
    setSize(my_size);
    setOrigin(Vector2f(25/2,25/2));
    setFillColor(Color::Blue);
    typeBonusChoisi = VIE;
    bonusVie = 10;
    ramasse = false;
}

void Bonus::ramasser(){

    if(typeBonusChoisi == VIE && Engine::getInstance()->getPlayer()->modifierVie(bonusVie)){

        ramasse = true;
    }
}

bool Bonus::isRamasse() const{

    return ramasse;
}

Bonus::~Bonus()
{
    //dtor
}
