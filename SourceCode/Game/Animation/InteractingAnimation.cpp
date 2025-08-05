#include<Book/InteractingAnimation/InteractingAnimation.hpp> 

InteractingAnimation::InteractingAnimation(Object* owner)
	:owner(owner),state(Begin)
{

}
InteractingAnimation::~InteractingAnimation()
{

}
void InteractingAnimation::activate()
{

}
void InteractingAnimation::deactivate()
{

}
void InteractingAnimation::update(sf::Time dt)
{
	// do nothing 
}
void InteractingAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
}