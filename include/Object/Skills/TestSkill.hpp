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
	
	void execute(Entity* user) override;
	void update(sf::Time dt) override;
	void handleEvent(const sf::Event& event, sf::RenderWindow* window) override;
	Skill* clone() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

