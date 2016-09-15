#include "stdafx.h"
#include "Drawing Class.h"


Draw_Class::Draw_Class(Data& data)
	:mData(data)
{

}

void Draw_Class::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.transform *= getTransform();
	state.texture = NULL; // Za sada
	for (const auto& it : Drawing_container)
		target.draw(*it, state);
}

void Draw_Class::add_ptr(Ptr* pointer)
{
	Drawing_container.push_back(std::move(*pointer));
}

void Draw_Class::empty_container()
{
	if (!Drawing_container.empty())
	{
		for (const auto& it : Drawing_container)
			Drawing_container.pop_back();
	}
}

