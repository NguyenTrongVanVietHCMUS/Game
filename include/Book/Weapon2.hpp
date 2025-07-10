#pragma once
#include <Book/Utility.hpp>
#include <Book/StrategyClass.hpp>
#include <Book/Entity.hpp>
class Weapon2 
{
private:
    std::unordered_map<std::string, float> stats;
    std::unique_ptr<IBehavior> behavior; // Strategy for weapon behavior
    std::unique_ptr<IWeaponAnimation> animation; // Animation for the weapon
    
public:
    Weapon2(std::unique_ptr<IBehavior> behavior = nullptr, std::unique_ptr<IWeaponAnimation> animation = nullptr)
        : behavior(std::move(behavior)), animation(std::move(animation)) {};
    void setBehavior(std::unique_ptr<IBehavior> newBehavior);
    void setStat(const std::string& statName, float value);
    float getStat(const std::string& statName) const;
    // Target is where the weapon target at base on the behavior 
    // So Target could be user or an entity that being aim
    void activate(Entity* target);

    void update(const sf::Time& dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};