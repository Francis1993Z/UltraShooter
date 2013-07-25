#ifndef WIDGET_INCLUDED_HPP
#define WIDGET_INCLUDED_HPP

#include <SFML/Graphics.hpp>

class Widget
{
public:
    Widget();
    virtual void draw() = 0;
    virtual sf::FloatRect getCollisionBox() const = 0;
    virtual void setSurvolSouris(bool p_survol) = 0;
    virtual void setClicSouris(bool p_clic) = 0;
    int getId() const;
    virtual ~Widget();
protected:
    int id;
private:
};

#endif // WIDGET_INCLUDED_HPP
