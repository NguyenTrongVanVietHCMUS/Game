#include <Object/Weapon/Gun.hpp>

Gun::Gun(Entity* holder, float cooldownTime)
    : Weapon(holder, WeaponType::WeaponType_Gun, EntityType::EntityType_Ally, "Gun")
{
    // Load the texture for the gun
    if (!texture.loadFromFile("Media/Assets/Weapons/Gun/gun.png"))
    {
        throw std::runtime_error("Failed to load gun texture");
    }
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    skillHolder.setEntity(holder); // Set the entity for the skill holder
    skillHolder.setSkill(SkillLoader::loadSkills("Test Skill", cooldownTime)); // Load and set the skill for the gun
}

Gun::~Gun()
{
    // Destructor logic if needed
}

void Gun::draw(sf::RenderTarget& target, sf::RenderStates states)
{
    // Draw the gun sprite
    // holder has get position method
    sf::Vector2f holderPosition = holder->getPosition();
    // Offset holder position to align the gun sprite
    holderPosition.x -= 20.f; // Adjust the x position as needed
    holderPosition.y -= 20.f; // Adjust the y position as needed
    sprite.setRotation(angle); // Set the rotation based on the calculated angle
    sprite.setPosition(holderPosition);
    position = holderPosition; // Update the position of the gun
    target.draw(sprite, states);
    skillHolder.draw(target, states);
}

void Gun::handleEvent(const sf::Event& event, sf::RenderWindow* window)
{
    // Handle events for the gun
    skillHolder.handleEvent(event, window); // Handle events for the skill holder
    UpdateAngle(event, window); // Update the angle of the gun based on mouse movement
}

void Gun::update(sf::Time deltaTime)
{
    // Update the gun's state
    skillHolder.update(deltaTime); // Update the skill holder
    // Additional update logic for the gun can be added here
}