#pragma once 
#include<Book/Utility.hpp> 
#include<Object/Object.hpp>
class Chest :public Object
{
public: 
	Chest(sf::Vector2f position,Hitbox hibox ,float scalex , float scaley); 
	virtual void collide(Entity* entity);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};