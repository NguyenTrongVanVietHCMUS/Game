#include<Book/InteractingAnimation/SpikeFloorAnimation.hpp>
#include<Object/Object.hpp>
SpikeFloorAnimation::SpikeFloorAnimation(Object* owner, float scalex, float scaley) :scalex(scalex), scaley(scaley), InteractingAnimation(owner)
{
	this->owner = owner; // Set the owner of the chest animation
	state = Begin;
	inactive->loadFromFile("Media/Assets/TileSets/Floor/SpikeFloor0.png"); 
	active->loadFromFile("Media/Assets/TileSets/Floor/SpikeFloor1.png");
	
	inactiveSprite->setTexture(*inactive);
	activeSprite->setTexture(*active);
	
	inactiveSprite->setScale(scalex, scaley); 
	activeSprite->setScale(scalex, scaley);

	inactiveSprite->setPosition(owner->getPosition());
	activeSprite->setPosition(owner->getPosition());

	elapsedTime = sf::Time::Zero; // Initialize elapsed time

}
SpikeFloorAnimation::~SpikeFloorAnimation()
{
	delete inactive;
	delete active;
	delete inactiveSprite;
	delete activeSprite;

}
void SpikeFloorAnimation::update(sf::Time dt)
{
	elapsedTime += dt;
	if(elapsedTime >= animationDuration)
	{
		elapsedTime = animationDuration-elapsedTime; 
		if (state == Begin)
		{
			state = End; 
		}
		else if (state == End)
		{
			state = Begin; 
		}
	}
}
void SpikeFloorAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(state == Begin)
	{
		states.texture = inactive; // Set the texture to inactive
		target.draw(*inactiveSprite, states);
	}
	else if (state == End)
	{
		states.texture = active; // Set the texture to active
		target.draw(*activeSprite, states);
	}
	else
	{
		assert(false && "Invalid state in SpikeFloorAnimation::draw");
	}
}