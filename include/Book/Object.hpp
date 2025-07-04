#pragma once 
#include<Book/Utility.hpp> 
#include<Book/Entity.hpp> 
class Object : public Entity
{
public : 
	Object(std::string name , std::string file, sf::Vector2f position,Hitbox hitbox,float scalex , float scaley):Entity(name ,position,hitbox)
	{
			
	}
};