#pragma once
#include<Book/Utility.hpp> 
#include<Book/Entity.hpp>
#include<Book/MovingAnimation.hpp>
#include<Control/State.hpp>
class Mob : public Entity
{
protected:
    std::unique_ptr<MovingAnimation> movingAnimation;
public:
    Mob(std::string name, sf::Vector2f position);
    ~Mob();
public:
    virtual void collide(const Entity* other);
    virtual bool handleEvent(const sf::Event& event, sf::RenderWindow* window);
    virtual bool update(const sf::Time& deltaTime);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        hitbox.draw(target, states); // Draw the hitbox
        movingAnimation->draw(target, states);
    }
};