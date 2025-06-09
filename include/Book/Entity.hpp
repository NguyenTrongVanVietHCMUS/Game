#pragma once 
#include <Book/Utility.hpp>
#include<Control/Hitbox.hpp>

class Entity:public sf::Drawable
{
protected: 
    sf::Vector2f position; // Position of the entity ; 
    std::string name ; 

public :
    Entity(std::string name , sf::Vector2f position) ; 
    ~Entity() ;
public :
    Hitbox hitbox ; 
    virtual bool handleEvent(const sf::Event& event,sf::RenderWindow* window); // Handle events
    virtual bool update(sf::Time dt); // Update the entity
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const ; // Draw the entity
    sf::Vector2f getPosition() ; 
};