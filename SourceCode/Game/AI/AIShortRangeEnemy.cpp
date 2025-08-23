#include<Book/AIEnemy.hpp>
#include<Book/Enemy.hpp>

void AIShortRangeEnemy::update(Enemy* mob, Entity* target,sf::Time dt)
{
	if (mob->inRange(target))
	{
		mob->chase(target,dt);
		if(mob->distanceTo(target)<64.0)
		{
			mob->shoot(target,dt) ; 
		}
	}
	else
	{
		mob->wander(dt); 
	}
}