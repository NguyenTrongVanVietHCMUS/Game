#include<Book/Entity.hpp>

Entity::Entity()
{
    // Constructor logic
}
Entity::~Entity()
{
    // Destructor logic if needed
}   
bool Entity::handleEvent(const sf::Event& event)
{
    // Handle events
    return false; // Default implementation, can be overridden
}
bool Entity::update(sf::Time dt)
{
    // Update the entity
    return false; // Default implementation, can be overridden
}
void Entity::draw(sf::RenderTarget& target, sf::RenderStates states)const 
{
    // Draw the entity
    // This function should be overridden in derived classes to provide specific drawing logic
}
