#include<Book/InteractingAnimation/CageAnimation.hpp>
#include<Object/Object.hpp>
CageAnimation::CageAnimation(Object* owner, float scalex, float scaley) :scalex(scalex), scaley(scaley), InteractingAnimation(owner)
{
	this->owner = owner; // Set the owner of the chest animation
	//if (this->owner == nullptr)abort();
	// Load textures for the chest animation
	if (!top->loadFromFile("Media/Assets/TileSets/Cage/Top.png"))
	{
		abort();
	}
	if (!bottom->loadFromFile("Media/Assets/TileSets/Cage/Bottom.png"))
	{
		abort();
	}
	if (!brokencage->loadFromFile("Media/Assets/TileSets/Cage/Brokencage.png"))
	{
		abort();
	}
	topSprite->setTexture(*top);
	bottomSprite->setTexture(*bottom);
	brokencageSprite->setTexture(*brokencage);

	topSprite->setScale(scalex, scaley);
	brokencageSprite->setScale(scalex, scaley);
	bottomSprite->setScale(scalex, scaley);
	topSprite->setPosition(owner->getPosition());
	bottomSprite->setPosition(sf::Vector2f(owner->getPosition().x,owner->getPosition().y+brokencage->getSize().y*scaley-bottom->getSize().y*scaley));
	brokencageSprite->setPosition(owner->getPosition());
	
	state = Begin; 
}
CageAnimation::~CageAnimation()
{
	delete topSprite;
	delete brokencageSprite;
	delete bottomSprite;
	delete top;
	delete brokencage;
	delete bottom; 
}
void CageAnimation::activate()
{
	//owner->attachChild(new )
	if (state == Begin)
	{
		state = End;
	}
	else state = End;  
}
void CageAnimation::deactivate()
{
}
void CageAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	if (state == Begin) {
		states.texture = bottom; // Set the texture for the bottom sprite
		target.draw(*bottomSprite, states);
		states.texture = top;
		target.draw(*topSprite, states);
	}
	else
	{
		states.texture = brokencage;
		target.draw(*brokencageSprite, states); 
	}

}