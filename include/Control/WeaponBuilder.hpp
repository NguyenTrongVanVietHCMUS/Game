#pragma once
#include<Book/Weapon2.hpp>
#include<Book/StrategyClass.hpp>
#include<Book/Utility.hpp>


class WeaponBuilder
{
    std::string             _name;
    sf::Vector2f            _position;
    
    std::unique_ptr<IBehavior> _behavior = nullptr;
    std::unique_ptr<IWeaponAnimation> _animation = nullptr;
    std::unique_ptr<ICooldownBehavior> _cooldownBehavior = nullptr;
    std::unique_ptr<AdvanceWeaponComponent> _advanceComponent = nullptr; // Advanced weapon component for combo attacks
    sf::Vector2f            _scaleBulletSpawnPosition = sf::Vector2f(0, 0); // Position where the bullet spawns based on the weapon's scale
    std::string            _soundPath = "Nothing"; // Path to the sound file for the weapon
    State*                  _worldmap;
    float                  _manaUsage = 0.0f;
    WeaponBuilder(std::string name, sf::Vector2f position, State* worldmap = nullptr)
        : _name(std::move(name)), _position(position), _worldmap(worldmap) {}
public:
    static WeaponBuilder create(std::string name, sf::Vector2f position, State* worldmap = nullptr)
    {
        return WeaponBuilder(std::move(name), position, worldmap);
    }

    WeaponBuilder& withBehavior(std::unique_ptr<IBehavior> behavior)
    {
        _behavior = std::move(behavior);
        return *this;
    }

    WeaponBuilder& withAnimation(std::unique_ptr<IWeaponAnimation> animation)
    {
        _animation = std::move(animation);
        return *this;
    }
    WeaponBuilder& withCooldownBehavior(std::unique_ptr<ICooldownBehavior> cooldownBehavior)
    {
        _cooldownBehavior = std::move(cooldownBehavior);
        return *this;
    }
    WeaponBuilder& withCooldownTime(float cooldownTime)
    {
        _cooldownBehavior = std::make_unique<BasicCooldownBehavior>(cooldownTime);
        return *this;
    }
    WeaponBuilder& withAdvanceComponent(std::unique_ptr<AdvanceWeaponComponent> advanceComponent)
    {
        _advanceComponent = std::move(advanceComponent);
        return *this;
    }

    WeaponBuilder& withMap(State* worldmap)
    {
        _worldmap = worldmap;
        return *this;
    }

    WeaponBuilder& withSoundPath(const std::string& soundPath)
    {
        _soundPath = soundPath;
        return *this;
    }

    WeaponBuilder& withScaleBulletSpawnPosition(sf::Vector2f scaleBulletSpawnPosition)
    {
        _scaleBulletSpawnPosition = scaleBulletSpawnPosition;
        return *this;
    }

    WeaponBuilder& withManaUsage(float manaUsage)
    {
        _manaUsage = manaUsage;
        return *this;
    }

    std::shared_ptr<Weapon2> build()
    {

        std::shared_ptr<Weapon2> weapon = std::make_shared<Weapon2>(
            _name,
            _position,
            std::move(_behavior),
            std::move(_animation),
            std::move(_advanceComponent),
            std::move(_cooldownBehavior),
            _scaleBulletSpawnPosition,
            _worldmap
        );
        //if(_soundPath != "Nothing")
        {
            weapon->setSound(_soundPath); // Set the sound path for the weapon
            _soundPath = "Nothing"; // Reset the sound path after setting it
        }

        weapon->setStat("ManaUsage", _manaUsage);
        _manaUsage = 0.0f;
        return weapon;
    }
};