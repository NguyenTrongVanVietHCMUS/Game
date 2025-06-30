#pragma once 
#include <Book/Utility.hpp>
#include<Control/Hitbox.hpp>
#include<Control/SkillHolder.hpp>
#include<Book/Skill.hpp>
#include<memory>


class Entity:public sf::Drawable
{

public :

    enum class type { Ally, Enemy };

    Entity(std::string name , sf::Vector2f position); 
    Entity(std::string name , sf::Vector2f position, Hitbox hitbox):name(name),position(position),hitbox(hitbox){}
    virtual ~Entity();

public :

    
    std::string name ; 
    sf::Vector2f position; // Position of the entity
    Hitbox hitbox ;  
    virtual bool handleEvent(const sf::Event& event,sf::RenderWindow*window) ;
    virtual bool update(const sf::Time& dt)  ;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const ; // Draw the entity
    virtual Hitbox getHitbox()const ; // Get the hitbox of the entity
public :
    // utility functions
    void updateHitboxOnPosition(sf::Time deltaTime);
public : 
    // Getters and Setters
    sf::Vector2f getPosition() const { 
        // std::cerr << "Get position : " << position.x << ", " << position.y << std::endl; 
        return position;
     }
    sf::Vector2f getDirection() const { return sf::Vector2f(0.45f, 0.45f); } // Placeholder for direction

    virtual void collide(const Entity* other) ;
    bool operator<(const Entity& other)const{
        return getHitbox().hitbox.top + getHitbox().hitbox.height < other.getHitbox().hitbox.top + other.getHitbox().hitbox.height||(
            getHitbox().hitbox.top + getHitbox().hitbox.height == other.getHitbox().hitbox.top + other.getHitbox().hitbox.height &&
            getHitbox().hitbox.left + getHitbox().hitbox.width < other.getHitbox().hitbox.left + other.getHitbox().hitbox.width
        );
    }
};