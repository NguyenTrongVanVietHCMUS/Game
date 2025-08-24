#pragma once
#include<Book/Utility.hpp> 
#include<Book/Entity.hpp>
#include<Book/MovingAnimation.hpp>
#include<Control/ResourceManager.hpp>
#include<Control/State.hpp>
#include<Book/Inventory.hpp>
#include<Control/WeaponLoader.hpp>
#include<Book/EntityComponent.hpp>
class AIEnemy; 
class Enemy : public Entity
{
protected:
    float sightRange; 
    std::unique_ptr<AIEnemy>aiEnemy; 
    std::unique_ptr<MovingAnimation>movingAnimation;
    std::shared_ptr<Inventory> inventory = std::make_shared<Inventory>();
    float elapseDeathTime = 0.0f;
    float despawnDeathTime = 3.0f;
    EntityAttributeActionComponent attributes;
public:
    Enemy(std::string name, sf::Vector2f position);
    ~Enemy();
public:

    virtual void collide(Entity* other);
    virtual void update(Entity* target , sf::Time dt);
    virtual Hitbox getHitbox() const
    {
        sf::Vector2f position = this->getPosition() - sf::Vector2f(22.0f, 12.0f);
        Hitbox tempHitbox;
        tempHitbox.hitbox = sf::FloatRect(position.x, position.y, 50, 12);
        return tempHitbox; // Return the hitbox of the boar
    }
    virtual Hitbox getBodyHitbox() const override
    {
        sf::Vector2f position = this->getPosition() - sf::Vector2f(22.0f, 60.0f);
        Hitbox tempHitbox;
        tempHitbox.hitbox = sf::FloatRect(position.x, position.y, 50, 60);
        return tempHitbox; // Return the body hitbox of the knight  
    }
public:
    virtual void chase(Entity* target,sf::Time dt);
    virtual void wander(sf::Time dt); 
    virtual void shoot(Entity* target,sf::Time dt); 
    virtual void SwitchWeapon();
    std::string getCurrentWeaponName() const;
public:
    virtual bool isAllowClean();
    virtual bool isDeath();

    virtual float getRange()const final
    {

        return sightRange;
    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        movingAnimation->draw(target, states);
        inventory->draw(target, states);
        
        /*getHitbox().draw(target, states);
        getBodyHitbox().draw(target, states); */
        
        sf::RectangleShape hitbox(sf::Vector2f(getHitbox().hitbox.width, getHitbox().hitbox.height));
        hitbox.setPosition(sf::Vector2f(getHitbox().hitbox.left, getHitbox().hitbox.top));
        hitbox.setFillColor(sf::Color(255, 0, 0, 128)); // semi-transparent red for visibility
        target.draw(hitbox, states); // Draw the hitbox shape

        sf::RectangleShape bodyHitbox(sf::Vector2f(getBodyHitbox().hitbox.width, getBodyHitbox().hitbox.height));
        bodyHitbox.setPosition(sf::Vector2f(getBodyHitbox().hitbox.left, getBodyHitbox().hitbox.top));
        bodyHitbox.setFillColor(sf::Color(0, 255, 0, 100)); // semi-transparent red for visibility
        target.draw(bodyHitbox, states); // Draw the hitbox shape
    }

    void takeDamage(int damage) override;
    void knockBack(sf::Vector2f force) override;
    void knockBack(const Projectile2* projectile, float Force = 1000.0f, Entity *other = nullptr) override;
};