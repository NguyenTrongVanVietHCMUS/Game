#pragma once 
#include<Book/Utility.hpp>
class Object; 
class InteractingAnimation
{
protected : 
	enum AnimationState
	{
		Begin,
		Processing,
		End,
	}; 
	Object* owner;
	AnimationState state; 
public :
	InteractingAnimation(Object* owner); 
	~InteractingAnimation();
	virtual void activate(); 
	virtual void update(sf::Time dt) { std::cout << "WRONG" << std::endl; }; // Update the animation state
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};