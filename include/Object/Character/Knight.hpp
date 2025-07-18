#pragma once
#include<Control/ResourceManager.hpp>
#include<Book/Utility.hpp>
#include<Book/Character.hpp>
#include<Book/Strategy/WeaponBehavior.hpp>
#include<Book/Strategy/WeaponAnimation.hpp>
class Knight : public Character
{
public:
    Knight(sf::Vector2f position,State* state): Character("Knight", position)
    {
        type = Entity::Type::Ally; 
        movingAnimation = std::make_unique<Character_MovingAnimation>(
            &ResourceManager::getInstance().get<sf::Texture>(Textures::ID::Knight),
            sf::Vector2u(8, 3), 
            0.1f,  // Switch time for the animation
            this->position, 
            2.1f, // Scale of the animation,
            this
        );  

        inventory->addWeapon(
            std::make_shared<Weapon2>(
                "AK_47",
                this->position, // Position of the weapon
                0.1f, // Cooldown time for the weapon
                std::make_unique<RangedWeaponBehavior>(state, 500.0f, 20.0f), // Ranged weapon behavior with speed
                std::make_unique<GunAnimation>(
                    0.2f, // Total time for the animation
                    0.4f, // Scale of the animation
                    &ResourceManager::getInstance().get<sf::Texture>(Textures::ID::AK_47), // Texture for the gun animation
                    this->position, // Position of the gun animation
                    10.0f, // Start angle of the gun animation
                    0.0f, // End angle of the gun animation
                    25.0f, // Recoil offset for the gun animation
                    this, // Owner of the gun animation
                    sf::Vector2f(0.4f, 0.6f) // Middle position for the gun animation
                )
            )
        );
        sf::Texture* swordTexture = new sf::Texture();
        if (!swordTexture->loadFromFile("Media/Assets/Weapons/sword/Scythe.png")) {
            std::cerr << "Failed to load sword texture\n";
        }
        inventory->addWeapon(
            std::make_shared<Weapon2>(
                "Scythe",
                this->position, // Position of the weapon
                0.5f, // Cooldown time for the weapon
                std::make_unique<MeleeWeaponBehavior>(state), // Melee weapon behavior with speed
                std::make_unique<SwordAnimation>(
                    0.2f, // Total time for the animation
                    -1.0f, // Scale of the animation
                    swordTexture, // Texture for the sword animation
                    this->position, // Position of the sword animation
                    -90.0f, // Start angle of the sword animation
                    90.0f, // End angle of the sword animation
                    this, // Owner of the sword animation
                    sf::Vector2f(0.1f, 0.1f) // Middle position for the sword animation
                )
            )
        );
        movingAnimation->speed = 285.0f; 
        // Initialize the knight-specific properties here 
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
        movingAnimation->handleCollision(other); 
	}
};