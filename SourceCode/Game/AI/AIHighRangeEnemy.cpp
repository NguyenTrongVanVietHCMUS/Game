#include<Book/AIEnemy.hpp>
#include<Book/Enemy.hpp>

void AIHighRangeEnemy::attack(Enemy* mob, Entity*target)
{
	if (!mob->inRange(target))
	{
		mob->chase(target->getPosition()); 
	} 
}	