#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <future>
#include <Book/Skill.hpp>
#include <Book/Entity.hpp>
class Skill;
class Entity;

class SkillHolder
{
public :


	void setEntity(Entity *entity);
	void setSkill(Skill *skill);
	void UseSkill();

	void SetRunSkill(Skill* skill);
	void SetRunSkill(Skill* skill, Entity *entity);

	bool isCompleted() const;

public :
	void update(const sf::Time& dt);
	void handleEvent(const sf::Event& event);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected :
	void asyncExecuteSkill();

	Entity* _entity = nullptr;
	Skill* _SelectedSkill = nullptr;
	bool _isRunning = false;
	std::future<void> _skillFuture;
};
