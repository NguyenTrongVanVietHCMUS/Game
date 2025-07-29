#pragma once 
#include<Book/InteractingAnimation/InteractingAnimation.hpp>
#include<Book/Utility.hpp>
#include<Book/Weapon2.hpp>
class ChestAnimation : public InteractingAnimation
{
private:
	sf::Texture* body = new sf::Texture();
	sf::Texture* bottom = new sf::Texture();
	sf::Texture* left = new sf::Texture();
	sf::Texture* right = new sf::Texture();
	sf::Texture* itemsTexture = nullptr; 
	sf::Sprite* bodySprite = new sf::Sprite();
	sf::Sprite* bottomSprite = new sf::Sprite();
	sf::Sprite* leftSprite = new sf::Sprite();
	sf::Sprite* rightSprite = new sf::Sprite();
	sf::Sprite* itemsSprite = nullptr; 
	float distance;
	float scalex;
	float scaley;
	std::shared_ptr<Weapon2> items = nullptr; 
public:
	ChestAnimation(Object* owner, float scalex, float scaley);
	ChestAnimation(Object* owner, float scalex, float scaley, std::shared_ptr<Weapon2> items);
	~ChestAnimation(); 
	virtual void activate();
	virtual void update(sf::Time dt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	void setItems(std::shared_ptr<Weapon2> newItems);
};