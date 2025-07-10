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
bool Entity::update(const sf::Time& dt)
{
    // std::cout<<"Entity updating"<<std::endl;
    return false;
}
void Entity::draw(sf::RenderTarget& target, sf::RenderStates states)const 
{
    hitbox.draw(target,states) ;  
}
Hitbox Entity::getHitbox() const
{
    return hitbox ;
}

void Entity::updateHitboxOnPosition()
{
    hitbox.hitbox = sf::FloatRect(position.x - hitbox.hitbox.width / 2, position.y - hitbox.hitbox.height, hitbox.hitbox.width, hitbox.hitbox.height);
    // Update the hitbox position based on the entity's current position
    // std::cerr << "Updating hitbox position to: " << position.x << ", " << position.y << std::endl;
}


void Entity::collide(const Entity* other)
{
    // Handle collision logic here
    // This is a placeholder function and should be implemented in derived classes
    //std::cout << "Collided with entity: " << other->name << std::endl;
}
