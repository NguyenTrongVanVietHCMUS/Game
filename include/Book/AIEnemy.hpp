#pragma once 
#include<vector>
#include<Book/Character.hpp>
class Enemy; 
class AIEnemy
{
public:
	virtual ~AIEnemy() = default;

	// Virtual function to be overridden by derived classes
	virtual void attack(Enemy* enemy, Entity* target) = 0; 
};
class AIShortRangeEnemy : public AIEnemy
{
public : 
	void attack(Enemy* enemy, Entity* target); 
};
class AIHighRangeEnemy : public AIEnemy
{
public : 
	void attack(Enemy* enemy, Entity* target); 
};