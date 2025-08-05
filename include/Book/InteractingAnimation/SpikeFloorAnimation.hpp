#pragma once 

#include<Book/InteractingAnimation/InteractingAnimation.hpp>
#include<Book/Utility.hpp>
class SpikeFloorAnimation : public InteractingAnimation
{
private : 
	float scalex; 
	float scaley; 
	sf::Time elapsedTime = sf::Time::Zero;
	sf::Time animationDuration = sf::seconds(1.3f); // Duration of the animation
	
	sf::Texture* inactive = new sf::Texture();
	sf::Texture* active = new sf::Texture();
	sf::Sprite* inactiveSprite = new sf::Sprite();
	sf::Sprite* activeSprite = new sf::Sprite();
public:
	SpikeFloorAnimation(Object* owner, float scalex, float scaley);
	~SpikeFloorAnimation(); 
	virtual void update(sf::Time dt)override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};