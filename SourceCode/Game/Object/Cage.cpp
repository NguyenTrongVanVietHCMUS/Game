#include<Object/Chest/Cage.hpp> 
#include<Book/InteractingAnimation/CageAnimation.hpp>

Cage::Cage(sf::Vector2f position, Hitbox hitbox, float scalex, float scaley) : Object("Cage", position, hitbox, scalex, scaley)
{
	type = Entity::Type::Object;
	interactingAnimation = std::make_unique<CageAnimation>(
		this, scalex, scaley
	);
	
}
void Cage::update(Entity* player)
{
	// Check collision with player
	if (this->isNear(player))
	{
		interactingAnimation->activate(); // Activate the interaction animation
	}
}
Hitbox Cage::getBodyHitbox() const
{
	sf::Vector2f position = this->getPosition() - sf::Vector2f(22.0f, 60.0f);
	Hitbox tempHitbox;
	tempHitbox.hitbox = sf::FloatRect(position.x, position.y, 50, 60);
	return tempHitbox; // Return the body hitbox of the cage
}
void Cage::activate()
{
	interactingAnimation->activate();
}
void Cage::deactivate()
{
	abort(); 
}
void Cage::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	interactingAnimation->draw(target, states);
	//Entity::draw(target, states); // Call the base class draw method
	// Draw the chest sprite or any other visual representation here
}
void Cage::collide(Entity* other)
{

}

