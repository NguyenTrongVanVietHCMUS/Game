#pragma once 
#include<vector>
#include<Book/Character.hpp>
#include<unordered_map>
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
class AIZulan :public AIEnemy
{
	float ElapseTime = 0.0f;
	float NextShootTime = 2.0f;
	float spamShootTime = 0.2f;
	int ShootTime = 0;
	std::string CurrentWeapon;
	bool isShooting = false;
	std::unordered_map<std::string, int> NumShootPerSkill;

	int getNumTimesToShoot(std::string weaponName) const;

public : 
	AIZulan();
	void update(Enemy* enemy, Entity* target, sf::Time dt);
};