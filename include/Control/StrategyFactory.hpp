#pragma once
#include<Book/Strategyclass.hpp>
#include <nlohmann/json.hpp>
#include <Control/State.hpp>
#include <Book/Strategy/WeaponBehavior.hpp>
using json = nlohmann::json;

class StrategyFactory
{
public:
    static std::unique_ptr<IBehavior> createBehavior(const json& data, State* map = nullptr)
    {
        auto it = behaviorRegistry().find(data.at("type").get<std::string>());
        if (it != behaviorRegistry().end())
        {
            return it->second(data, map);
        }
        throw std::runtime_error("Unknown behavior type: " + data.at("type").get<std::string>());
    }

private:
    using BehaviorFactoryMap = std::unordered_map<std::string, std::function<std::unique_ptr<IBehavior>(const json&, State*)>>;

private:
    // Factory methods for each type of behavior
    static BehaviorFactoryMap& behaviorRegistry()
    {
        static BehaviorFactoryMap registry{
            {"Ranged Weapon Behavior", [](const json& data, State* map){
                return std::make_unique<RangedWeaponBehavior>(map,
                    data.value("projectileSpeed", 500.0f),
                    data.value("spreadAngle", 0.0f));
            }}
        };
        return registry;
    }
};