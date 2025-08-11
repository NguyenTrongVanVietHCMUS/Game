#pragma once 
#include<Book/Utility.hpp> 
#include<Object/Object.hpp>	
class SpikeFloor :public Object
{
public:
	SpikeFloor(sf::Vector2f position, Hitbox hibox, float scalex, float scaley);
	virtual void bodyCollide(Entity* entity);
	virtual bool passAble()const override; 
};