#pragma once
#include <Book/Utility.hpp>
#include <Book/Entity.hpp>
class Projectile2;
class Weapon2;
struct IMovement
{
protected:
public:
    bool isActive = true;
    virtual void update(Projectile2& projectile,const sf::Time &dt) = 0;
    virtual std::unique_ptr<IMovement> clone() const = 0;
    virtual ~IMovement() = default;
    virtual void setDirection(sf::Vector2f direction) {};
    virtual sf::Vector2f getDirection() const = 0;
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
protected:
    std::string ProjectileName; // Name of the projectile
public: 
    virtual void activate(Weapon2& weapon, Entity* target) = 0;
    virtual std::unique_ptr<IBehavior> clone() const = 0;
    virtual ~IBehavior() = default;

public:
    void setProjectile(std::string ProjectileName) {
        this->ProjectileName = ProjectileName; // Set the projectile for the behavior
    }
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
    virtual std::unique_ptr<ICooldownBehavior> clone() const = 0;
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
    Entity* owner = nullptr;
public:
    IWeaponAnimation(float TotalTime, float scale, sf::Texture* texture, 
                    const sf::Vector2f& position, const sf::Vector2f& middlePosition = sf::Vector2f(0, 0), Entity* owner = nullptr);

    void play(); // This will put CurrentTime to 0 and start the animation
    
public:
    virtual void update(Weapon2& weapon, sf::Time dt)  {};
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const  {};
    virtual void handleEvent(const sf::Event& event) {};
    virtual std::unique_ptr<IWeaponAnimation> clone() const = 0;
    virtual ~IWeaponAnimation() = default;

public:
    sf::Texture* getTexture() const {
        return texture; // Return the texture of the weapon animation
    }

    bool isDone() const {
        return CurrentTime >= TotalTime; // Check if the animation is done
    }

public:
    sf::Vector2f getSpriteSize() const {
        return sf::Vector2f(sprite.getTexture()->getSize().x * sprite.getScale().x, 
                        sprite.getTexture()->getSize().y * sprite.getScale().y);
    }

    void SetOwner(Entity* newOwner) {
		std::cerr << "Setting owner of weapon animation to " << newOwner->name << std::endl;
        owner = newOwner;
    }
};

class CameraManager;

class IStatusEffect{
protected:
    float duration; // Duration of the effect in seconds
    float elapsedTime; // Time elapsed since the effect started
protected:
    void updateElapsedTime(const sf::Time& dt) {
        elapsedTime += dt.asSeconds();
    }
public:
    IStatusEffect(float duration) : duration(duration), elapsedTime(0) {}
    bool isExpired() const { return elapsedTime >= duration; }
    virtual void update(const sf::Time& dt) { updateElapsedTime(dt); }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {}
    virtual ~IStatusEffect() = default;
    virtual bool isActive() const {
        return elapsedTime < duration; // Check if the effect is still active
    }


// Trait of the class 
    virtual void SetCamera(CameraManager* cameraManager) {};
};

