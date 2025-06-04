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
public:
	TestSkill(sf::Time SkillCD) : Skill(SkillCD) {}
	void execute(Entity* user) override
	{
		std::cerr << "Executing TestSkill" << std::endl;
		triggerCooldown();

		
		// Get user position and the direction calculate base on the character position and mouse position
		// Get the direction of bullet
		sf::Vector2f bulletDirection = user->getDirection();
		if (bulletDirection.x == 0 && bulletDirection.y == 0) {
			bulletDirection = sf::Vector2f(1, 0); // Default direction
		}
		Bullet *bullet = new Bullet(user->getPosition(), bulletDirection);
		_projectileHolder.addProjectile(std::unique_ptr<Bullet>(bullet));
	}
	void update(sf::Time dt) override
	{
		if (_cooldownRemaining > sf::Time::Zero) {
			//std::cerr << "Updating TestSkill cooldown : " << _cooldownRemaining.asSeconds() << std::endl;
			_cooldownRemaining -= dt;
		}
		_projectileHolder.updateProjectiles(dt);
	} 
	void handleEvent(const sf::Event& event) override
	{
		// Handle events related to the skill here
		_projectileHolder.handleEvents(event);

		// Left click to trigger the skill
		
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		
			std::cerr << "TestSkill triggered by left click" << std::endl;
			triggerSkill();
		}
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		_projectileHolder.drawProjectiles(target, states);
	}
};