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