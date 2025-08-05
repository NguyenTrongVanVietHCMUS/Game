#pragma once 
#include<Book/Utility.hpp>
class Object; 
class InteractingAnimation
{
protected : 
	enum AnimationState
	{
		Begin,
		Activating,
		Deactivating, 
		End,
	}; 
	Object* owner;
	AnimationState state; 
public :
	InteractingAnimation(Object* owner); 
	~InteractingAnimation();
	virtual void activate(); 
	virtual void deactivate(); 
	virtual void update(sf::Time dt); // Update the animation state
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};