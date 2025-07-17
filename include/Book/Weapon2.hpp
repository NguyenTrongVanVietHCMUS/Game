#pragma once
#include <Book/Utility.hpp>
#include <Book/StrategyClass.hpp>
#include <Book/Strategy/CooldownBehavior.hpp>
#include <Book/Entity.hpp>
class Weapon2 : public Entity
{
private:
    std::unordered_map<std::string, float> stats;
    std::unique_ptr<IBehavior> behavior; // Strategy for weapon behavior
    std::unique_ptr<IWeaponAnimation> animation; // Animation for the weapon
    std::unique_ptr<ICooldownBehavior> cooldownBehavior; // Cooldown behavior for the weapon
    
public:
    Weapon2(std::string name, sf::Vector2f position,
        std::unique_ptr<IBehavior> behavior = nullptr, std::unique_ptr<IWeaponAnimation> animation = nullptr)
        : behavior(std::move(behavior)), animation(std::move(animation)), Entity(name, position), cooldownBehavior(std::make_unique<BasicCooldownBehavior>(1.0f)) {};
    
        Weapon2(std::string name, sf::Vector2f position, 
        std::unique_ptr<IBehavior> behavior, std::unique_ptr<IWeaponAnimation> animation,
        std::unique_ptr<ICooldownBehavior> cooldownBehavior)
        : behavior(std::move(behavior)), animation(std::move(animation)), cooldownBehavior(std::move(cooldownBehavior)), Entity(name, position) {};

    Weapon2(std::string name, sf::Vector2f position, float cooldownTime,
        std::unique_ptr<IBehavior> behavior, std::unique_ptr<IWeaponAnimation> animation)
        : behavior(std::move(behavior)), animation(std::move(animation)), cooldownBehavior(std::make_unique<BasicCooldownBehavior>(cooldownTime)), Entity(name, position) {};

    void setBehavior(std::unique_ptr<IBehavior> newBehavior);
    void setStat(const std::string& statName, float value);
    float getStat(const std::string& statName) const;
    // Target is where the weapon target at base on the behavior 
    // So Target could be user or an entity that being aim
    void activate(Entity* target);

    bool update(const sf::Time& dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};