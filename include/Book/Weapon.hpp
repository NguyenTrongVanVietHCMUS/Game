// This file defines interfaces for weapon-related functionalities in a book.
#pragma once

#include <Book/Entity.hpp>
#include <Book/Utility.hpp>
#include <Control/ProjectileHolder.hpp>

class Weapon
{
public:
    virtual ~Weapon() = default;

    // Get the name of the weapon
    virtual std::string getName() const = 0;

    // Get the damage dealt by the weapon
    virtual int getDamage() const = 0;

    // Get the range of the weapon
    virtual float getRange() const = 0;

    // Get the type of the weapon
    virtual WeaponType getType() const = 0;

    // update draw and handle event
    virtual void update(sf::Time deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window, sf::RenderStates states) = 0;
    virtual void handleEvent(const sf::Event& event) = 0;
protected :
    WeaponType type;
    EntityType entityType;
    ProjectileHolder projectileHolder;
    sf::Texture texture;
    sf::Sprite sprite;
};

