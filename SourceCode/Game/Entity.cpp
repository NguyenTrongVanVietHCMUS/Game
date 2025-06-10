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