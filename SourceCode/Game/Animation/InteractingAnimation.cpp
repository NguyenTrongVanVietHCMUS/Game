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
void InteractingAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw the animation based on the current state
	if (state == Begin)
	{
		// Draw the initial state of the animation
	}
	else if (state == Processing)
	{
		// Draw the processing state of the animation
	}
	else if (state == End)
	{
		// Draw the end state of the animation
	}
}