#include<Book/AIEnemy.hpp>
#include<Book/Enemy.hpp>
#include<Boss/Zulan.hpp>
void AIZulan::update(Enemy* mob, Entity* target, sf::Time dt)
{
	if (mob->inRange(target))
	{
		mob->chase(target, dt);
		mob->shoot(target, dt); 
	}
	else
	{
		mob->wander(dt);
	}
}