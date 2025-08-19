#include<Object/Floor/SpikeFloor.hpp> 
#include<Book/InteractingAnimation/SpikeFloorAnimation.hpp>

SpikeFloor::SpikeFloor(sf::Vector2f position, Hitbox hitbox, float scalex, float scaley) : Object("SpikeFloor", position, hitbox, scalex, scaley)
{
	type = Entity::Type::Object;
	interactingAnimation = std::make_unique<SpikeFloorAnimation>(
		this, scalex, scaley
	);
	bodyHitbox.set(hitbox); 
	this->hitbox.set(Hitbox(sf::FloatRect(-1e9 , -1e9, 1, 1))); // Set hitbox to a non-collidable area
}

void SpikeFloor::bodyCollide(Entity* entity)
{
	if (entity->type == Entity::Type::Ally&&interactingAnimation->canActivate())
	{
		entity->takeDamage(4); 
	}

}
bool SpikeFloor::passAble() const
{
	return true; 
}
