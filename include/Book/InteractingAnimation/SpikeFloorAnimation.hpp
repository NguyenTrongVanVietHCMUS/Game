#pragma once 

#include<Book/InteractingAnimation/InteractingAnimation.hpp>
#include<Book/Utility.hpp>
class SpikeFloorAnimation : public InteractingAnimation
{
private : 
	bool turn; 
	float scalex; 
	float scaley; 
	sf::Time elapsedTime = sf::Time::Zero;
	sf::Time animationDuration = sf::seconds(1.3f); // Duration of the animation
	
	sf::Texture inactive;
	sf::Texture active;
	sf::Sprite inactiveSprite;
	sf::Sprite activeSprite;
public:
	SpikeFloorAnimation(Object* owner, float scalex, float scaley);
	~SpikeFloorAnimation(); 
	bool canActivate()  override; // Check if the animation can be activated
	virtual void update(sf::Time dt)override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};