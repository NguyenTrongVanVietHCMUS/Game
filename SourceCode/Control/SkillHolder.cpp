#include "Control/SkillHolder.hpp"


void SkillHolder::setEntity(Entity* entity) {
	this->_entity = entity;
}

void SkillHolder::setSkill(Skill* skill) {
	if(_skillFuture.valid()) {
		_skillFuture.wait(); // Wait for the previous skill to finish
	}
	if (skill) {
		if(this->_SelectedSkill) {
			delete this->_SelectedSkill; // Clean up the previous skill
		}
		this->_SelectedSkill = skill;
	}
}

void SkillHolder::UseSkill() {
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

void SkillHolder::asyncExecuteSkill() {
	_skillFuture = std::async(std::launch::async, [this]() {
		if (_entity) {
			_SelectedSkill->execute(_entity);
		}
		_isRunning = false;
	});
}

void SkillHolder::setCooldownTime(float cooldownTime) {
	if (_SelectedSkill) {
		std::cerr << "Setting cooldown time: " << cooldownTime << std::endl;
		_SelectedSkill->setCooldownTime(sf::seconds(cooldownTime)); // Set the cooldown time for the selected skill
	}
}

void SkillHolder::SetRunSkill(Skill* skill) {
	setSkill(skill);
	UseSkill();
}

void SkillHolder::SetRunSkill(Skill* skill, Entity* entity) {
	if (entity) {
		setEntity(entity);
	}
	setSkill(skill);
	UseSkill();
}

bool SkillHolder::isCompleted() const {
	if(!_isRunning) {
		return true; // Skill execution is complete
	}
	if(!_skillFuture.valid()) {
		return true;
	}
	return _skillFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready; // Check if the skill execution is complete
}


void SkillHolder::update(const sf::Time& deltaTime) {
	if (_SelectedSkill)
	{
		_SelectedSkill->update(deltaTime);

		if(_isRunning && isCompleted()) {
			_isRunning = false; // Reset running state when skill execution is complete
		}
		if(_SelectedSkill->isTriggered()) {
		 // Trigger cooldown if the skill was used
			//_SelectedSkill->resetTriggered();
			UseSkill();
		}
	}
}

void SkillHolder::handleEvent(const sf::Event& event, sf::RenderWindow* window) {
	if (_SelectedSkill)
	{
		_SelectedSkill->handleEvent(event, window);
	}
}	

void SkillHolder::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	_SelectedSkill->draw(target, states);
}
