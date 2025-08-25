#include<Book/AIAlly.hpp>
#include<Book/Ally.hpp>

void AIShortRangeAlly::update(Ally* ally , Entity* target, sf::Time dt)
{
	if (ally->distanceTo(ally->getOwner()) >= 32 * 30.0)
	{
		ally->teleport(ally->getOwner()->getPosition());
	}
	else
	{
		if (target == nullptr)
		{
			if (ally->distanceTo(ally->getOwner()) <= 32*3.0)
			{
				ally->wander(dt);
			}
			else
			{
				ally->chase(ally->getOwner(), dt);
			}
		}
		else
		{
			ally->chase(target, dt);
			if(ally->distanceTo(target) <= 64.0)
			{
				ally->shoot(target, dt);
			}
		}
	}
}