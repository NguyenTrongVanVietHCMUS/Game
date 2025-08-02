#pragma once
#include<Control/ResourceManager.hpp>
#include<Book/Utility.hpp>
#include<Book/Character.hpp>
#include<Book/Strategy/WeaponBehavior.hpp>
#include<Book/Strategy/WeaponAnimation.hpp>
#include<Control/CameraManager.hpp>
#include <Book/Strategy/StatusEffect/CameraEffect.hpp>
#include<Control/WeaponLoader.hpp>


class Knight : public Character
{
public:
    Knight(sf::Vector2f position,State* state, CameraManager* cameraManager = nullptr): Character("Knight", position, state, cameraManager)
    {
        WeaponLoader weaponLoader(state);
        type = Entity::Type::Ally; 
        movingAnimation = std::make_unique<Character_MovingAnimation>(
            &ResourceManager::getInstance().get<sf::Texture>(Textures::ID::Knight),
            sf::Vector2u(8, 3), 
            0.1f,  // Switch time for the animation
            this->position, 
            2.1f, // Scale of the animation,
            this
        );  
        statusEffect.push_back(std::make_shared<FollowCameraEffect>(cameraManager, this)); // Add follow camera effect
        
        try {
            inventory->addWeapon(weaponLoader.LoadWeapons("AK47"), this); // Load the weapon from JSON file
        } catch (const std::exception& e) {
            std::cerr << "Failed to create inventory: " << e.what() << std::endl;
        }
        inventory->addWeapon(weaponLoader.LoadWeapons("Sword"), this); // Load the Sword weapon from JSON file

        try {
            inventory->addWeapon(weaponLoader.LoadWeapons("ThrowBomb"), this); // Load the ThrowBomb weapon from JSON file
        } catch (const std::exception& e) {
            std::cerr << "Failed to load ThrowBomb weapon: " << e.what() << std::endl;
        }

        try {
            inventory->addWeapon(weaponLoader.LoadWeapons("Laser Gun"), this); // Load the Laser Gun weapon from JSON file
        } catch (const std::exception& e) {
            std::cerr << "Failed to load Laser Gun weapon: " << e.what() << std::endl;
        }

        movingAnimation->speed = 285.0f;
        // Initialize the knight-specific properties here
        std::cerr << "Knight load successfully\n";
    }
    ~Knight() override = default; // Default destructor
    Hitbox getHitbox() const 
    {
        sf::Vector2f position = this->getPosition()-sf::Vector2f(22.0f,12.0f);
        Hitbox tempHitbox;
        tempHitbox.hitbox = sf::FloatRect(position.x, position.y, 50, 12);
        return tempHitbox; // Return the hitbox of the knight
    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        movingAnimation->draw(target, states);
        
        sf::RectangleShape hitboxshape(sf::Vector2f(getHitbox().hitbox.width, getHitbox().hitbox.height));
        hitboxshape.setPosition(sf::Vector2f(getHitbox().hitbox.left, getHitbox().hitbox.top));
		hitboxshape.setFillColor(sf::Color(255, 0, 0, 100)); // Semi-transparent red color for the hitbox
        target.draw(hitboxshape, states); // Draw the hitbox shape
        inventory->draw(target, states); // Draw the inventory
        sf::CircleShape circle(3);
        circle.setPosition(getHandPosition());
        circle.setFillColor(sf::Color::Green); // Set the color of the circle to red
        // Draw the circle at the hand position for debugging purposes
        target.draw(circle, states);
    }
    void collide(const Entity* other) override final 
    {
        if (auto projectile = dynamic_cast<const Projectile2*>(other)) {
            if (projectile->type == Entity::Type::EnemyProjectile) {
                attributes.TakeDamage(static_cast<int>(projectile->getAttribute("Damage")));
            }
        }
        movingAnimation->handleCollision(other); 
	}
};