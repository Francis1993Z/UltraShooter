#ifndef LAYER_HPP_INCLUDED
#define LAYER_HPP_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>

typedef std::vector<sf::Drawable*> FrameSet;
typedef FrameSet::const_iterator itFrame;

/*
*	Petite classe simple qui gère le système de couche de drawable.
*	Elle a la même utilisation que std::vector, l'élément à l'indice 0 est le premier affiché.
*/
class Layer :
	public sf::Drawable, public FrameSet
{
 public :
	//!Même constructeur que sf::Drawable
	Layer(const sf::Vector2f& Position = sf::Vector2f(0, 0), const sf::Vector2f& Scale = sf::Vector2f(1, 1), float Rotation = 0.f, const sf::Color& Col = sf::Color(255, 255, 255, 255));

	virtual ~Layer();
protected :
	virtual void Render(sf::RenderTarget& Target) const;
};

#endif // LAYER_HPP_INCLUDED
