#pragma once 
#include<vector>
#include<Book/Character.hpp>
class Enemy; 
class AIEnemy
{
public:
	virtual ~AIEnemy() = default;

	// Virtual function to be overridden by derived classes
	virtual void update(Enemy* enemy, Entity* target, sf::Time dt) = 0; 
};
class AIShortRangeEnemy : public AIEnemy
{
public : 
	void update(Enemy* enemy, Entity* target, sf::Time dt); 
};
class AIHighRangeEnemy : public AIEnemy
{
public : 
	void update(Enemy* enemy, Entity* target, sf::Time dt); 
};