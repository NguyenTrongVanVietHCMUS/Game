#include "Control/SkillManager.hpp"


void SkillManager::setEntity(Entity* entity) {
	this->_entity = entity;
}

void SkillManager::setSkill(Skill* skill) {
	if(_skillFuture.valid()) {
		_skillFuture.wait(); // Wait for the previous skill to finish
	}
	if (skill) {
		this->_SelectedSkill = skill;
	}
}

void SkillManager::UseSkill() {
	if(!_SelectedSkill || !_entity) {
		return; // No skill or entity set
	}
	if(!_SelectedSkill->isReady()) {
		return; // Skill is not ready to be used
	}
	// Use the skill asynchronously
	_isRunning = true;
	asyncExecuteSkill();
}

void SkillManager::asyncExecuteSkill() {
	_skillFuture = std::async(std::launch::async, [this]() {
		if (_entity) {
			_SelectedSkill->execute(_entity);
		}
		_isRunning = false;
	});
}

void SkillManager::SetRunSkill(Skill* skill) {
	setSkill(skill);
	UseSkill();
}

void SkillManager::SetRunSkill(Skill* skill, Entity* entity) {
	if (entity) {
		setEntity(entity);
	}
	setSkill(skill);
	UseSkill();
}

bool SkillManager::isCompleted() const {
	if(!_isRunning) {
		return true; // Skill execution is complete
	}
	if(!_skillFuture.valid()) {
		return true;
	}
	return _skillFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready; // Check if the skill execution is complete
}


void SkillManager::update(const sf::Time& deltaTime) {
	if (_SelectedSkill)
	{
		_SelectedSkill->update(deltaTime);

		if(_isRunning && isCompleted()) {
			_isRunning = false; // Reset running state when skill execution is complete
		}
	}
}

void SkillManager::handleEvent(const sf::Event& event) {
	if (_SelectedSkill && _isRunning)
	{
		_SelectedSkill->handleEvent(event);
	}

	if(event.type == sf::Event::KeyPressed) {
		if(event.key.code == sf::Keyboard::E) { // Example key to trigger skill usage
			UseSkill();
		}
	}
}	
