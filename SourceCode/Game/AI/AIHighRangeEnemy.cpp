#include<Book/AIEnemy.hpp>
#include<Book/Enemy.hpp>

void AIHighRangeEnemy::update(Enemy* mob, Entity*target, sf::Time dt)
{
	if(mob->distanceTo(target)<mob->getRange()/2)
	{
		mob->shoot(target, dt);
		if(rand()%100==0)
		{
			mob->wander(dt) ; 
		}
	}
	else if (mob->inRange(target))
	{
		mob->chase(target, dt); 
	}
	else
	{
		mob->wander(dt); 
	}
}	