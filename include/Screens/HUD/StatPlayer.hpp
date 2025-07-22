#pragma once 
#include <Book/Utility.hpp>
#include<Book/Character.hpp>

class StatPlayer:public sf::Drawable
{
private : 
	Character*player; 
public : 
	StatPlayer();
	~StatPlayer();
	void setPlayer(Character* player);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const; 
};