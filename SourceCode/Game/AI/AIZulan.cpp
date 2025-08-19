#include<Book/AIEnemy.hpp>
#include<Book/Enemy.hpp>
#include<Boss/Zulan.hpp>
void AIZulan::update(Enemy* mob, Entity* target, sf::Time dt)
{
	if (mob->inRange(target))
	{
		std::cerr << "Zulan is in range to attack the target." << std::endl;
		mob->chase(target, dt);
		mob->shoot(target, dt); 
	}
	else
	{
		std::cerr << "Zulan is not in range to attack the target." << std::endl;
		mob->wander(dt);
	}
}