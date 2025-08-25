#pragma once 
#include<vector>
#include<Book/Character.hpp>
#include<unordered_map>
class Ally;
class AIAlly
{
public:
	virtual ~AIAlly() = default;

	// Virtual function to be overridden by derived classes
	virtual void update(Ally* ally, Entity* target, sf::Time dt) = 0;
};
class AIShortRangeAlly : public AIAlly
{
public:
	void update(Ally* ally, Entity* target, sf::Time dt);
};
class AIHighRangeAlly : public AIAlly
{
public:
	void update(Ally* ally, Entity* target, sf::Time dt);
};