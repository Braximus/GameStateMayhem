#ifndef DRAWING_CLASS_H
#define DRAWING_CLASS_H

#include "stdafx.h"
class Data;

class Draw_Class: public sf::Drawable, public sf::Transformable
{
	Data&						mData;
	typedef std::unique_ptr<Draw_Class>		Ptr;
	std::deque<Ptr>					Drawing_container;
public:
	explicit				Draw_Class(Data&);
	virtual void				draw(sf::RenderTarget&, sf::RenderStates) const;
	virtual void				add_ptr(Ptr*);
	void					empty_container();
};
#endif
