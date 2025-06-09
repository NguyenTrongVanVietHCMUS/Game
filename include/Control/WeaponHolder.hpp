#pragma once
#include <Book/Weapon.hpp>

class WeaponHolder
{
public:
    // Constructor
    WeaponHolder();

    // Destructor
    ~WeaponHolder();

    // Add a weapon to the holder
    void addWeapon(Weapon* weapon);

    // Remove a weapon from the holder
    void removeWeapon(Weapon* weapon);

    // Get the current weapon
    Weapon* getCurrentWeapon() const;
    // Set the current weapon
    void setCurrentWeapon(Weapon* weapon);
    // update the current weapon based on the index
    void update(sf::Time deltaTime);
    // Draw the current weapon
    void draw(sf::RenderWindow& window, sf::RenderStates states) const;
    // Handle events for the current weapon
    void handleEvent(const sf::Event& event);
    
    // Switch to the next weapon in the holder
    void switchToNextWeapon();
    // Switch to the previous weapon in the holder
    void switchToPreviousWeapon();
    // Get the number of weapons in the holder
    int getWeaponCount() const;

private:
    std::vector<Weapon*> weapons; // List of weapons held
    int currentWeaponIndex; // Index of the currently selected weapon
    Weapon* currentWeapon; // Pointer to the currently selected weapon

};
