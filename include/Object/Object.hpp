#pragma once 

#include<Book/Entity.hpp>
#include<Book/InteractingAnimation/InteractingAnimation.hpp>

class Object : public Entity
{
protected : 
	std::unique_ptr<InteractingAnimation> interactingAnimation;
public:
    Object(std::string name,sf::Vector2f position, Hitbox hitbox, float scalex, float scaley) :Entity(name, position, hitbox)
    {
        type = Entity::Type::Object;
    }
    virtual void update(Entity* player)
    {
        // if base is called  mean that update doesnt base on player 
	}
    virtual void collide(Entity* entity) 
    {

    }
    virtual void bodyCollide(Entity* entity)
    {
        // do nothing 
	}
    virtual bool update(sf::Time dt)
    {
		//std::cout << "Update Object: " << name << std::endl;
        interactingAnimation->update(dt); 
        return 0;
    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
		interactingAnimation->draw(target, states); 
        Entity::draw(target, states); 
        // do nothing 
    }
};