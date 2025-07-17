#pragma once
#include <Book/Utility.hpp>
#include <Book/Entity.hpp>
class Projectile2;
class Weapon2;
struct IMovement
{
    virtual void update(Projectile2& projectile, sf::Time dt) = 0;
    virtual std::unique_ptr<IMovement> clone() const = 0;
    virtual ~IMovement() = default;
};

struct ICollision
{
    virtual void collide(Entity& projectile,const Entity *other) = 0;
    virtual std::unique_ptr<ICollision> clone() const = 0;
    virtual ~ICollision() = default;
};

struct IEffect
{
    virtual void apply(Projectile2& projectile) = 0;
    virtual std::unique_ptr<IEffect> clone() const = 0;
    virtual ~IEffect() = default;
};

struct IBehavior
{
    virtual void activate(Weapon2& weapon, Entity* target) = 0;
    virtual ~IBehavior() = default;
};

class ICooldownBehavior
{
protected:
    float cooldownTime; // Time in seconds for the cooldown
    float currentCooldown; // Current cooldown time
public:
    ICooldownBehavior(float cooldownTime) : cooldownTime(cooldownTime), currentCooldown(0.0f) {}
    virtual void update(const sf::Time& dt) = 0;
    bool isReady() const { return currentCooldown >= cooldownTime; }
    void reset() { currentCooldown = 0; }
};

class IWeaponAnimation
{
protected:
    float scale = 1.0f; // Scale of the weapon animation
    float TotalTime = 0.0f; // Total time for the animation
    float CurrentTime = 0.0f; // Current time for the animation
    sf::Vector2f position; // Position of the weapon animation
    sf::Vector2f middlePosition; // Middle position of the weapon animation
    sf::Texture* texture = nullptr; // Texture for the weapon animation
    sf::Sprite sprite; // Sprite for the weapon animation
public:
    IWeaponAnimation(float TotalTime, float scale, sf::Texture* texture, 
                    const sf::Vector2f& position, const sf::Vector2f& middlePosition = sf::Vector2f(0, 0));

    void play(); // This will put CurrentTime to 0 and start the animation
    
public:
    virtual void update(Weapon2& weapon, sf::Time dt) {};
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) {};
    virtual void handleEvent(const sf::Event& event) {};
    virtual ~IWeaponAnimation() = default;


};