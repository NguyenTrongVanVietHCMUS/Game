#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <Book/Entity.hpp>

class Entity;

class Skill
{
public :
	explicit Skill(sf::Time cooldownTime) :_cooldownTime(cooldownTime) {};
	void setCooldownTime(sf::Time cooldownTime) { this->_cooldownTime = cooldownTime; }
	bool isReady() const { return _cooldownRemaining <= sf::Time::Zero; }

public :
	virtual void execute(Entity* user) = 0;
	virtual void update(sf::Time dt) = 0;
	virtual void handleEvent(const sf::Event& event) = 0;

protected :
	void triggerCooldown() { _cooldownRemaining = _cooldownTime; }


protected :
	sf::Time _cooldownTime;
	sf::Time _cooldownRemaining;

};


class TestSkill : public Skill
{
public:
	TestSkill(sf::Time SkillCD) : Skill(SkillCD) {}
	void execute(Entity* user) override
	{
		std::cerr << "Executing TestSkill" << std::endl;
		triggerCooldown();
		// Implement skill execution logic here
	}
	void update(sf::Time dt) override
	{
		if (_cooldownRemaining > sf::Time::Zero) {
			std::cerr << "Updating TestSkill cooldown : " << _cooldownRemaining.asSeconds() << std::endl;
			_cooldownRemaining -= dt;
		}
	}
	void handleEvent(const sf::Event& event) override
	{
		// Handle events related to the skill here
	}
};