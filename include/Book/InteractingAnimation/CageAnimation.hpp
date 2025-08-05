#pragma once 
#include<Book/InteractingAnimation/InteractingAnimation.hpp>
#include<Book/Utility.hpp>
class CageAnimation : public InteractingAnimation
{
private:
	sf::Texture* top = new sf::Texture; 
	sf::Texture* brokencage = new sf::Texture; 
	sf::Texture* bottom = new sf::Texture; 
	sf::Sprite* topSprite = new sf::Sprite; 
	sf::Sprite* brokencageSprite = new sf::Sprite; 
	sf::Sprite* bottomSprite = new sf::Sprite; 
	float scalex;
	float scaley;
public:
	CageAnimation(Object* owner, float scalex, float scaley);
	~CageAnimation();
	virtual void activate();
	virtual void deactivate();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};