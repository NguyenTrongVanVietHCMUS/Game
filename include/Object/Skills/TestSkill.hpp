#pragma once
#include <Book/Skill.hpp>
#include <Book/Entity.hpp>
#include <Book/Utility.hpp>
#include <Object/Projectiles/Bullet.hpp>
#include <Control/ProjectileHolder.hpp>
// TestSkill for debug purposes, this skill shoot a projectile in the direction of the user
class TestSkill : public Skill
{
private:
	ProjectileHolder _projectileHolder; // Holder for projectiles
	sf::Vector2f _MousePosition; // Direction of the skill, not used in this case but can be useful for future skills

public:
	TestSkill(sf::Time SkillCD) : Skill(SkillCD) {}
	void execute(Entity* user) override
	{
		std::cerr << "Executing TestSkill" << std::endl;
		triggerCooldown();

		// Get the position from user entity
		sf::Vector2f userPosition = user->getPosition();
		// Use the position and mouse position to determine the direction of the bullet
		sf::Vector2f bulletDirection = _MousePosition - userPosition;
		// Check if the direction is zero, if so, set a default direction
		if (bulletDirection == sf::Vector2f(0.f, 0.f)) {
			bulletDirection = user->getDirection(); // Use the user's direction if mouse position is not set
		}
		// Create 2 bullets, one for each side of the user, No need to normalize
		Bullet *bullet = new Bullet("Bullet",user->getPosition(), bulletDirection);
		_projectileHolder.addProjectile(std::unique_ptr<Bullet>(bullet));
		Bullet *bullet2 = new Bullet("Bullet2",user->getPosition(), bulletDirection + sf::Vector2f(50.f, 50.0f)); // Slightly offset the second bullet
		_projectileHolder.addProjectile(std::unique_ptr<Bullet>(bullet2));
	}
	void update(sf::Time dt) override
	{
		if (_cooldownRemaining > sf::Time::Zero) {
			//std::cerr << "Updating TestSkill cooldown : " << _cooldownRemaining.asSeconds() << std::endl;
			_cooldownRemaining -= dt;
		}
		_projectileHolder.updateProjectiles(dt);
	}
	void handleEvent(const sf::Event& event, sf::RenderWindow* window) override
	{
		// Handle events related to the skill here
		_projectileHolder.handleEvents(event, window);

		// Left click to trigger the skill
		
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		
			// Get the mouse position in world coordinates
			_MousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
			std::cerr << "Mouse Position: " << _MousePosition.x << ", " << _MousePosition.y << std::endl;
			triggerSkill();
		}
	}

	Skill* clone() override
	{
		return new TestSkill(_cooldownTime); // Create a new instance of TestSkill
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		_projectileHolder.drawProjectiles(target, states);
	}
};

