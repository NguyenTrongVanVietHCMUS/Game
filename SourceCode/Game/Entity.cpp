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
void Entity::attachChild(Ptr child)
{
    children.push_back(std::move(child)); // Attach a child entity
}
bool Entity::handleEvent(const sf::Event& event, sf::RenderWindow* window)
{
    // do nothing ; 
    return 1;  
}
bool Entity::update(sf::Time dt)
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

void Entity::updateHitboxOnPosition()
{
    hitbox.hitbox = sf::FloatRect(position.x - hitbox.hitbox.width / 2, position.y - hitbox.hitbox.height, hitbox.hitbox.width, hitbox.hitbox.height);
}
bool Entity::movable()const
{
	return type == Entity::Type::Ally || type == Entity::Type::Enemy || type == Entity::Type::AllyProjectile || type == Entity::Type::EnemyProjectile;
}
float Entity::getRange()const
{   
	throw std::runtime_error("getRange() not implemented for this entity type"); // Default implementation, should be overridden in derived classes
}
bool Entity::inRange(const Entity* other)const
{
    if (other == nullptr)return false; 
	float distance = std::pow(position.x - other->getPosition().x, 2) + std::pow(position.y - other->getPosition().y, 2);
    return distance <= std::pow(this->getRange(), 2);
}
bool Entity::isCollide(const Entity* other)const
{
    return this->getHitbox().isCollide(other->getHitbox());  
}
void Entity::collide(const Entity* other)
{   
    // do nothing for now ; 
}
sf::Vector2f Entity::getHandPosition()const
{
    return position - sf::Vector2f(0,28);
}
bool Entity::isNear(Entity* other) const
{
    if (other == nullptr) return false;
    Hitbox myhitbox = this->getHitbox(); 
    myhitbox.extend(5); 
    return myhitbox.isCollide(other->getHitbox()); 
}