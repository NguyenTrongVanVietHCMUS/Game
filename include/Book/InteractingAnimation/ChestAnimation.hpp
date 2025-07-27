#pragma once 
#include<Book/InteractingAnimation/InteractingAnimation.hpp>
#include<Book/Utility.hpp>

class ChestAnimation : public InteractingAnimation
{
private:
	sf::Texture* body = new sf::Texture();
	sf::Texture* bottom = new sf::Texture();
	sf::Texture* left = new sf::Texture();
	sf::Texture* right = new sf::Texture();
	sf::Sprite* bodySprite = new sf::Sprite();
	sf::Sprite* bottomSprite = new sf::Sprite();
	sf::Sprite* leftSprite = new sf::Sprite();
	sf::Sprite* rightSprite = new sf::Sprite();
	float distance;
	float scalex;
	float scaley;
public:
	ChestAnimation(Object* owner, float scalex, float scaley);
	~ChestAnimation(); 
	virtual void activate();
	virtual void update(sf::Time dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};