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
    states.transform.translate(position);
    skillHolder.draw(target, states); // Draw the skill holder
}

void Gun::handleEvent(const sf::Event& event, sf::RenderWindow* window)
{
    // Handle events for the gun
    skillHolder.handleEvent(event, window); // Handle events for the skill holder
}

void Gun::update(sf::Time deltaTime)
{
    // Update the gun's state
    skillHolder.update(deltaTime); // Update the skill holder
    // Additional update logic for the gun can be added here
}