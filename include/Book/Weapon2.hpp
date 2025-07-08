#pragma once
#include <Book/Utility.hpp>
#include <Book/StrategyClass.hpp>

class Weapon2
{
private:
    std::unordered_map<std::string, float> stats;
    std::unique_ptr<IBehavior> behavior; // Strategy for weapon behavior

public:
    Weapon2(std::unique_ptr<IBehavior> behavior = nullptr)
        : behavior(std::move(behavior)) {};
    void setBehavior(std::unique_ptr<IBehavior> newBehavior);
    void setStat(const std::string& statName, float value);
    float getStat(const std::string& statName) const;
    // Target is where the weapon target at base on the behavior 
    // So Target could be user or an entity that being aim
    void activate(Entity* target);
};