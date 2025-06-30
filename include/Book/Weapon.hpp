// This file defines interfaces for weapon-related functionalities in a book.
#pragma once

#include <Book/Entity.hpp>
#include <Book/Utility.hpp>
#include <Control/ProjectileHolder.hpp>
#include <Control/SkillHolder.hpp>
#include <Control/SkillLoader.hpp>
class Weapon
{
public:
    virtual ~Weapon() = default;
    //Weapon(const Weapon&) = default; // Copy constructor
    Weapon(Entity *Holder, WeaponType type, EntityType entityType, const std::string& name, float damage, float speed);
    // Get the name of the weapon
    virtual std::string getName() {return name;}

    // Get the type of the weapon
    WeaponType getType();

    // update draw and handle event
    virtual void update(const sf::Time& deltaTime) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) = 0;
    virtual void handleEvent(const sf::Event& event,sf::RenderWindow* window) = 0;
    virtual void setCurrentMap(State* map) { skillHolder.setCurrentMap(map); } // Set the map for the weapon
    virtual Weapon* clone() = 0; // Clone the weapon

public:
    void setCooldownTime(float cooldownTime);
    void setDamage(float damage);
    void setSpeed(float speed);
    void setHolder(Entity* holder);
    void UpdateAngle(const sf::Event& event,sf::RenderWindow* window);


protected:
    std::string SkillName;
    float cooldownTime = 0.f; // Cooldown time for the weapon
    float damage = 10.f; // Damage dealt by the weapon
    float speed = 100.f; // Speed of the weapon
    Entity* holder; // Entity that owns the weapon
    WeaponType type;
    SkillHolder skillHolder; // Skill holder for the weapon
    EntityType entityType;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position; // Position of the weapon
    float angle = 0.f; // Angle of the weapon
    std::string name; // Name of the weapon     
};

