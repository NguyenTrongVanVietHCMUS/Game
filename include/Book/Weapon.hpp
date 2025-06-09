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
    Weapon(WeaponType type, EntityType entityType, const std::string& name)
        : type(type), entityType(entityType), name(name) {}
    // Get the name of the weapon
    virtual std::string getName() const = 0;

    // Get the type of the weapon
    WeaponType getType();

    // update draw and handle event
    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window, sf::RenderStates states) = 0;
    virtual void handleEvent(const sf::Event& event) = 0;
private :
    WeaponType type;
    SkillHolder skillHolder; // Skill holder for the weapon
    EntityType entityType;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f position; // Position of the weapon
    std::string name; // Name of the weapon
};

