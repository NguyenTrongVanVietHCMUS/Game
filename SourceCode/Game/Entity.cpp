#include<Book/Entity.hpp>

Entity::Entity(std::string name , sf::Vector2f position) 
    : name(name) , position(position)
{
	type = Entity::Type::Object; // Set the type of the entity
}

Entity::Entity(std::string name, sf::Vector2f position, Hitbox hitbox) 
    : name(name), position(position), hitbox(hitbox)
{
    type = Entity::Type::Object; // Set the type of the entity
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
    for (Ptr&child : children)
    {
        child->update(dt); 
    }
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

void Entity::updateHitboxOnPosition(sf::Time deltaTime)
{
    hitbox.hitbox = sf::FloatRect(position.x - hitbox.hitbox.width / 2, position.y - hitbox.hitbox.height, hitbox.hitbox.width, hitbox.hitbox.height);
}


void Entity::collide(const Entity* other)
{
    // do nothing by default 
}
