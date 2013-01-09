#ifndef LAYERANIM_HPP_INCLUDED
#define LAYERANIM_HPP_INCLUDED

#include "Anim.hpp"
#include "Layer.hpp"

/*
*	Animation où chaque frame est repésenter par une couche de Layer.
*/
class LayerAnim :
	public Anim, public Layer
{
public:
	LayerAnim(void);

	//!Retourne le nombre de frame de l'animation
	virtual unsigned int getSize() const;

protected:
	virtual void Render(sf::RenderTarget& Target) const;
};


#endif // LAYERANIM_HPP_INCLUDED
