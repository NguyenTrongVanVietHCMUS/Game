#pragma once 
#include<Book/MovingAnimation.hpp>

class Zulan_MovingAnimation :public MovingAnimation
{
private : 
    sf::Time elapsedTime = sf::Time::Zero; 
    sf::Texture death,ring,body,furyRing,furyBody; 
	sf::Sprite deathSprite, ringSprite,bodySprite,furyRingSprite,furyBodySprite;
public:
    Zulan_MovingAnimation(sf::Vector2f& position, float scale, Entity* entity, sf::Vector2f middlePosition = sf::Vector2f(0.5f, 1));
    ~Zulan_MovingAnimation();
    virtual void setSpritePosition()override final; 
    virtual void update(sf::Time dt)override final;
	virtual void getshot(const Entity* other);
    virtual void handleCollision(const Entity* other)override final;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override final;
};