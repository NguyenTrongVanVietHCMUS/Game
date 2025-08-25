#include<Book/AIAlly.hpp>
#include<Book/Ally.hpp>

void AIHighRangeAlly::update(Ally* ally, Entity* target, sf::Time dt)
{
	if (target == nullptr)
	{
		ally->chase(ally->getOwner(), dt);
		if (ally->distanceTo(target) <= 32*30.0)
		{
			ally->teleport(ally->getOwner()->getPosition());
		}
	}
	else
	{
		ally->chase(target, dt); 
		if (ally->distanceTo(target) <= ally->getRange())
		{
			ally->shoot(target, dt); 
		}
	}
}