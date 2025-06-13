// This file defines interfaces for weapon-related functionalities in a book.
#pragma once

#include <Book/Entity.hpp>
#include <Book/Utility.hpp>
#include <Control/ProjectileHolder.hpp>
#include <Control/SkillHolder.hpp>

class Weapon
{
public:
    virtual ~Weapon() = default;
    Weapon(Entity *Holder, WeaponType type, EntityType entityType, const std::string& name)
        : holder(Holder), type(type), entityType(entityType), name(name) {}
    // Get the name of the weapon
    virtual std::string getName() {return "No Name";}

    // Get the type of the weapon
    WeaponType getType();

    // update draw and handle event
    virtual void update(const sf::Time& deltaTime) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) = 0;
    virtual void handleEvent(const sf::Event& event,sf::RenderWindow* window) = 0;
    void UpdateAngle(const sf::Event& event,sf::RenderWindow* window);
protected :
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

