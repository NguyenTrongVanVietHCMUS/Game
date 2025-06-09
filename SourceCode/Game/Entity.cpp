#include<Book/Entity.hpp>

Entity::Entity(std::string name , sf::Vector2f position) : name(name) , position(position)
{

}
Entity::~Entity()
{
    // Destructor logic if needed
}   
bool Entity::handleEvent(const sf::Event& event,sf::RenderWindow* window)
{

    return false; 
}
bool Entity::update(sf::Time dt)
{
    return false;
}
void Entity::draw(sf::RenderTarget& target, sf::RenderStates states)const 
{
    
}
sf::Vector2f Entity::getPosition() 
{
    return position; 
}