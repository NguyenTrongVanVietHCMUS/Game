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
	bool isTriggered() const { return _isTriggered; } // Check if the skill has been triggered
	void resetTriggered() { _isTriggered = false; } // Reset the triggered state
public :
	virtual void execute(Entity* user) = 0;
	virtual void update(sf::Time dt) = 0;
	virtual void handleEvent(const sf::Event& event) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {}

protected :
	void triggerCooldown() { _cooldownRemaining = _cooldownTime; }
	void triggerSkill() { _isTriggered = true; } // Set the skill as triggered

protected :
	sf::Time _cooldownTime;
	sf::Time _cooldownRemaining;
	bool _isTriggered = false; // Flag to indicate if the skill has been triggered

};
