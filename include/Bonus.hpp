#ifndef BONUS_INCLUDED_HPP
#define BONUS_INCLUDED_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Bonus : public sf::RectangleShape
{
    public:
        Bonus(sf::Vector2f pos);
        void ramasser();
        bool isRamasse() const;
        virtual ~Bonus();
    protected:
    private:
        enum TypeBonus{VIE};
        TypeBonus typeBonusChoisi ;
        unsigned long bonusVie;
        bool ramasse;
};

#endif // BONUS_INCLUDED_HPP
