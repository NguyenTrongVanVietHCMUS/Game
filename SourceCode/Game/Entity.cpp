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
bool Entity::isAlive() const
{
	return HP > 0; // Check if the entity is alive based on its HP
}

void Entity::takeDamage(int damage)
{
    if(shield > 0)
    {
        shield -= damage; // Reduce shield first
        if(shield < 0)
        {
            shield = 0; // Reset shield to 0
        }
    }
    else
    {
        HP -= damage; // Directly reduce HP if no shield is present
	}
}

void Entity::restoreHealth(int amount)
{
    HP += amount; // Restore health
    if(HP > maxHP) // Ensure HP does not exceed maxHP
    {
        HP = maxHP;
    }
}
void Entity::collide(const Entity* other)
{
    // Handle collision logic here
    // This is a placeholder function and should be implemented in derived classes
    std::cout << "Collided with entity: " << other->name << std::endl;
}