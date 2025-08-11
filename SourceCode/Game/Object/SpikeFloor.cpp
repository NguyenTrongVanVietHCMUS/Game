#include<Object/Floor/SpikeFloor.hpp> 
#include<Book/InteractingAnimation/SpikeFloorAnimation.hpp>

SpikeFloor::SpikeFloor(sf::Vector2f position, Hitbox hitbox, float scalex, float scaley) : Object("SpikeFloor", position, hitbox, scalex, scaley)
{
	type = Entity::Type::Object;
	interactingAnimation = std::make_unique<SpikeFloorAnimation>(
		this, scalex, scaley
	);
}

void SpikeFloor::bodyCollide(Entity* entity)
{
	if (entity->type == Entity::Type::Ally)
	{

	}
}
bool SpikeFloor::passAble() const
{
	return true; 
}
