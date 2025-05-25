#pragma once 
#include <Book/Utility.hpp>
#include<Control/Hitbox.hpp>

class Entity :public sf::Drawable
{
    public :
    Entity(); // Constructor with default position
    ~Entity();
    std::string name ; 
    sf::Vector2f position; // Position of the entity
    Hitbox hitbox ; 
    virtual bool handleEvent(const sf::Event& event); // Handle events
    virtual bool update(sf::Time dt); // Update the entity
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states); // Draw the entity
};