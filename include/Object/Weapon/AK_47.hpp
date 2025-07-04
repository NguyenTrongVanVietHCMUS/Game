#pragma once
#include "Book/Weapon.hpp"
#include <Object/SkillLibraryUtility.hpp>
#include <Control/SkillHolder.hpp>
#include <Control/SkillLoader.hpp>
class AK_47 : public Weapon
{
public:
    AK_47(Entity* holder, float cooldownTime = 0.0f)
        : Weapon(holder, WeaponType::WeaponType_Gun, EntityType::EntityType_Ally, "AK_47",3,120)
    {
        if (!texture.loadFromFile("Media/Assets/Weapons/Gun/AK_47.png"))
        {
            throw std::runtime_error("Failed to load AK_47 texture");
        }
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
        skillHolder.setEntity(holder); // Set the entity for the skill holder
        SkillName = "Test Skill"; // Set the skill name for the AK_47
        this->cooldownTime = cooldownTime; // Set the cooldown time for the AK_47
        skillHolder.setSkill(SkillLoader::loadSkills(SkillName, cooldownTime)); // Load and set the skill for the AK_47
        Skill* TargetSkill = SkillLoader::loadSkills(SkillName, cooldownTime); // Load the skill from the skill loader
        TargetSkill->setProjectileSpeed(speed); // Set the projectile speed for the skill
        skillHolder.setSkill(TargetSkill); // Load and set the skill for the gun
    }
    //AK_47(const AK_47& other) = default; // Copy constructor
    ~AK_47()
    {

    }

    // Override methods from Weapon interface
    void draw(sf::RenderTarget& target, sf::RenderStates states) override
    {
        // Draw the gun sprite
    // holder has get position method
        sf::Vector2f holderPosition = holder->getPosition();
        // Offset holder position to align the gun sprite
        //holderPosition.x += 20.f; // Adjust the x position as needed
        holderPosition.y += -15.f; // Adjust the y position as needed

        if (std::abs(angle) <= 90.f) {
            sprite.setRotation(angle); // Set the rotation of the gun based on the angle
            sprite.setScale(0.4f, 0.4f);
        }
        else {
            sprite.setRotation(angle + 180.f); // Adjust rotation for angles greater than 90 degrees
            // flip sprite horizontally if angle is greater than 90 degrees
            sprite.setScale(-0.4f, 0.4f); // Flip the sprite horizontally
        }
        sprite.setOrigin(texture.getSize().x / 2.5f, texture.getSize().y / 2.f); // Set the origin to the center of the sprite
        sprite.setPosition(holderPosition);
        position = holderPosition; // Update the position of the gun
        target.draw(sprite, states);
        skillHolder.draw(target, states);
    }
    void handleEvent(const sf::Event& event, sf::RenderWindow* window) override
    {
        skillHolder.handleEvent(event, window); // Handle events for the skill holder
        UpdateAngle(event, window); // Update the angle of the gun based on mouse movement
    }
    void update(const sf::Time& deltaTime) override
    {
        skillHolder.update(deltaTime); 
    }

    Weapon* clone() override {
        return new AK_47(holder, cooldownTime); 
    };
};