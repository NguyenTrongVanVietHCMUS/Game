#pragma once
#include<Book/Strategyclass.hpp>
#include <nlohmann/json.hpp>
#include <Control/State.hpp>
#include <Book/Strategy/WeaponBehavior.hpp>
#include <Book/Strategy/WeaponAnimation.hpp>
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

    static std::unique_ptr<IWeaponAnimation> createAnimation(const json& data, Entity* owner)
    {
        auto it = animationRegistry().find(data.at("type").get<std::string>());
        if (it != animationRegistry().end())
        {
            return it->second(data, owner);
        }
        throw std::runtime_error("Unknown animation type: " + data.at("type").get<std::string>());
    }

private:
    using BehaviorFactoryMap = std::unordered_map<std::string, std::function<std::unique_ptr<IBehavior>(const json&, State*)>>;
    using AnimationFactoryMap = std::unordered_map<std::string, std::function<std::unique_ptr<IWeaponAnimation>(const json&, Entity*)>>;
    using MovingBehaviorFactoryMap = std::unordered_map<std::string, std::function<std::unique_ptr<IMovement>(const json&, State*)>>;
private:
    static std::unordered_map<std::string, sf::Texture*> textureCache;
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

    static AnimationFactoryMap& animationRegistry()
    {
        static AnimationFactoryMap registry{
            {"Gun Animation", [](const json& data, Entity* owner){
                return std::make_unique<GunAnimation>(
                    data.at("totalTime").get<float>(),
                    data.at("scale").get<float>(),
                    getTexture(data.at("texture").get<std::string>()),
                    owner? owner->getPosition() : sf::Vector2f{0.0f, 0.0f},
                    data.value("startAngle", 0.0f),
                    data.value("endAngle", 0.0f),
                    data.value("recoilOffset", 0.0f),
                    owner,
                    sf::Vector2f(0.4f, 0.6f)
                );
            }}
        };
        return registry;
    }

    static MovingBehaviorFactoryMap& movingBehaviorRegistry()
    {
        static MovingBehaviorFactoryMap registry{
            {"Follow Movement", [](const json& data, State* map){
                return std::make_unique<FollowMovement>(
                    data.at("speedX").get<float>(),
                    data.at("speedY").get<float>(),
                    data.at("projectileSpeed").get<float>(),
                    map,
                    data.value("maxDistance", 60.0f));
            }},
            {"Laser Aim Movement", [](const json& data, State* map){
                return std::make_unique<LaserAimMovement>(
                    data.at("aimTime").get<float>(),
                    sf::Vector2f(data.at("startPositionX").get<float>(), data.at("startPositionY").get<float>()),
                    sf::Vector2f(data.at("endPositionX").get<float>(), data.at("endPositionY").get<float>()),
                    map);
            }}
        };
        return registry;
    }

private:
    static sf::Texture* getTexture(const std::string& texturePath)
    {
        auto it = textureCache.find(texturePath);
        if (it != textureCache.end())
        {
            return it->second;
        }
        sf::Texture* texture = new sf::Texture();
        if (!texture->loadFromFile(texturePath))
        {
            throw std::runtime_error("Failed to load texture: " + texturePath);
        }
        textureCache[texturePath] = texture;
        return texture;
    }
};