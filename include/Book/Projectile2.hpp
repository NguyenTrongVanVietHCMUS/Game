#pragma once
#include <Book/Utility.hpp>
#include <Book/StrategyClass.hpp>
#include <Control/State.hpp>
#include <Book/MovingAnimation.hpp>
#include <Control/State.hpp>
#include <set>
class Projectile2 : public Entity
{
private:
    std::unique_ptr<IMovement> movementStrategy; // Strategy for movement
    std::unique_ptr<ICollision> collisionStrategy; // Strategy for collision handling
    std::unique_ptr<MovingAnimation> movingAnimation; // Animation for the projectile
    std::vector<std::unique_ptr<IStatusEffect>> trailStrategies; // Strategies for visual trails
    std::vector<IStatusEffect *> ProjectileEffects;
    sf::Sprite sprite; // Sprite representing the projectile
    sf::Texture texture; // Texture for the projectile sprite
    std::unordered_map<std::string, float> attributes; // Additional stats for the projectile
    std::string texturePath;
    State* currentMap; // Pointer to the current map or state
    bool isAddedCameraEffect = false; // Flag to check if camera effect is added
    CameraManager* cameraManager = nullptr; // Pointer to the camera manager
private: 
    float debounceTime = 1.0f;
    std::vector<const Entity*> collidedEntitiesFlag;
    std::unordered_map<const Entity*, float> collidedEntities;
public:

    // Basic constructor for builder
    
    Projectile2(std::string name, float lifeTime, sf::Vector2f position, State* currentMap, sf::Texture texture);
    Projectile2(std::string name, float LifeTime, sf::Vector2f position, State* CurrentMap, std::string texturePath,
        std::unique_ptr<IMovement> movement = nullptr, std::unique_ptr<ICollision> collision = nullptr, std::unique_ptr<MovingAnimation> animation = nullptr);

    Projectile2(std::string name,float LifeTime,sf::Vector2f position, float scale, State* CurrentMap, std::string texturePath,
        std::unique_ptr<IMovement> movement = nullptr, std::unique_ptr<ICollision> collision = nullptr, std::unique_ptr<MovingAnimation> animation = nullptr);
    
    void setBehavior(std::unique_ptr<IMovement> movement, std::unique_ptr<ICollision> collision);
    void setMovement(std::unique_ptr<IMovement> movement);
    void setCollision(std::unique_ptr<ICollision> collision);
    void setMovingAnimation(std::unique_ptr<MovingAnimation> animation);
    void addTrailEffect(std::unique_ptr<IStatusEffect> effect);
    void addEffect(IStatusEffect* effect);

    void setSpriteScale(float scale);
    void setSpriteRotation(float angle);
    void setAttribute(const std::string& attributeName, float value);
    float getAttribute(const std::string& attributeName) const;

    bool update(sf::Time dt) override;
    bool AllowCollide(Entity* other) const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void collide(Entity* other) override;

    Projectile2* clone(sf::Vector2f direction)const;
    sf::Vector2f getProjDirection(Entity *other = nullptr) const;

    void setCameraManager(CameraManager* camera);
    void activateEffect(Entity* target = nullptr);
public:
    void selfDelete();
public:
    bool HitboxMode = true;
};