#pragma once
#include <Book/Weapon2.hpp>
#include <Book/Utility.hpp>

class Inventory
{
private:
    std::vector<std::shared_ptr<Weapon2>> weapons; // List of weapons in the inventory
    //std::vector<std::shared_ptr<Skill>> skills; // List of skills in the inventory
    int CurrentWeaponIndex = 0; // Index of the currently active weapon
    int CurrentSkillIndex = 0; // Index of the currently active skill
    int MaxWeapon = 5; // Maximum index for weapons
    int MaxSkill = 1; // Maximum index for skills

public:
    Inventory() {}
    ~Inventory() = default;

    void addWeapon(std::shared_ptr<Weapon2> weapon);
    void addWeapon(std::shared_ptr<Weapon2> weapon, Entity *owner);
    //void addSkill(std::shared_ptr<Skill> skill);

    void removeWeapon(std::shared_ptr<Weapon2> weapon);
    //void removeSkill(std::shared_ptr<Skill> skill);

    void activateWeapon(Entity* target);
    void activateSkill(Entity* user);

    void SwitchWeapon(); // Switch to the next weapon in the inventory
    void SwitchSkill(); // Switch to the next skill in the inventory

    void update(sf::Time dt); // Update the inventory state
    void draw(sf::RenderTarget& target, sf::RenderStates states) const; // Draw the inventory

    std::shared_ptr<Weapon2> getCurrentWeapon() const;
    void removeCurrentWeapon(); // Remove the currently active weapon from the inventory
public:
    void shoot(Entity* shooter, Entity* target); // Shoot the current weapon at the target
    void AimAt(sf::Vector2f position);
};