#pragma once
#include <Book/Utility.hpp>
#include <Book/StrategyClass.hpp>
#include <Book/Strategy/CooldownBehavior.hpp>
#include <Book/Entity.hpp>
#include <Control/State.hpp>
#include <Control/State.hpp>
class Weapon2 : public Entity
{
private:
    std::unordered_map<std::string, float> stats;
    std::unique_ptr<IBehavior> behavior; // Strategy for weapon behavior
    std::unique_ptr<IWeaponAnimation> animation; // Animation for the weapon
    std::unique_ptr<ICooldownBehavior> cooldownBehavior; // Cooldown behavior for the weapon
    sf::Vector2f ScaleBulletSpawnPosition = sf::Vector2f(0, 0); // Position where the bullet spawns based on the weapon's scale
    sf::Vector2f OriginalBulletSpawnPosition;
    bool ishold = true;
    State *CurrentMap = nullptr;
    void UpdateBulletSpawnPosition() ;
public:
    Weapon2(std::string nam, sf::Vector2f position,
        std::unique_ptr<IBehavior> behavior = nullptr, std::unique_ptr<IWeaponAnimation> animation = nullptr, State* map = nullptr)
        : behavior(std::move(behavior)), animation(std::move(animation)), Entity(name, position), cooldownBehavior(std::make_unique<BasicCooldownBehavior>(1.0f)), CurrentMap(map){};

    Weapon2(std::string name, sf::Vector2f position,
        std::unique_ptr<IBehavior> behavior, std::unique_ptr<IWeaponAnimation> animation,
        std::unique_ptr<ICooldownBehavior> cooldownBehavior, State* map = nullptr)
        : behavior(std::move(behavior)), animation(std::move(animation)), cooldownBehavior(std::move(cooldownBehavior)), Entity(name, position), CurrentMap(map) {};

    Weapon2(std::string name, sf::Vector2f position, float cooldownTime,
        std::unique_ptr<IBehavior> behavior, std::unique_ptr<IWeaponAnimation> animation, State* map = nullptr)
        : behavior(std::move(behavior)), animation(std::move(animation)), cooldownBehavior(std::make_unique<BasicCooldownBehavior>(cooldownTime)), Entity(name, position), CurrentMap(map) {};

    Weapon2(std::string name, sf::Vector2f position, float cooldownTime, sf::Vector2f scaleBulletSpawnPosition,
        std::unique_ptr<IBehavior> behavior, std::unique_ptr<IWeaponAnimation> animation, State* map = nullptr)
        : behavior(std::move(behavior)), animation(std::move(animation)), cooldownBehavior(std::make_unique<BasicCooldownBehavior>(cooldownTime)), Entity(name, position), ScaleBulletSpawnPosition(scaleBulletSpawnPosition), CurrentMap(map) {};
    
    // This constructor is used by the WeaponBuilder class to create a weapon
    Weapon2(std::string name, sf::Vector2f position,
        std::unique_ptr<IBehavior> behavior, std::unique_ptr<IWeaponAnimation> animation,
        std::unique_ptr<ICooldownBehavior> cooldownBehavior, sf::Vector2f scaleBulletSpawnPosition, State* map = nullptr)
        : behavior(std::move(behavior)), animation(std::move(animation)), cooldownBehavior(std::move(cooldownBehavior)), Entity(name, position), ScaleBulletSpawnPosition(scaleBulletSpawnPosition), CurrentMap(map) {};
 
    Entity::Type ProjectileTypeTransform(Entity* entity) const;
    void setBehavior(std::unique_ptr<IBehavior> newBehavior);
    void setStat(const std::string& statName, float value);
    float getStat(const std::string& statName) const;
    // Target is where the weapon target at base on the behavior 
    // So Target could be user or an entity that being aim
    void activate(Entity* target);

    bool update(sf::Time dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void switchHold( bool isHold, Entity* owner = nullptr);
public:
    sf::Vector2f GetProjectileSpawnPosition() const;
    sf::Texture* getTexture() const {
        if (animation) {
            return animation->getTexture();
        }
        return nullptr; // Return nullptr if no animation is set
    }
};