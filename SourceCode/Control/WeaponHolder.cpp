#include <Control/WeaponHolder.hpp>

WeaponHolder::WeaponHolder() : currentWeaponIndex(0), currentWeapon(nullptr) {}
WeaponHolder::~WeaponHolder() {
    for (auto weapon : weapons) {
        delete weapon; // Clean up dynamically allocated weapons
    }
}
void WeaponHolder::addWeapon(Weapon* weapon) {
    if (weapon) {
        weapons.push_back(weapon);
        if (weapons.size() == 1) {
            currentWeapon = weapon; // Set the first weapon as the current one
        }
    }
}
void WeaponHolder::removeWeapon(Weapon* weapon) {
    auto it = std::find(weapons.begin(), weapons.end(), weapon);
    if (it != weapons.end()) {
        if (currentWeapon == weapon) {
            currentWeapon = nullptr; // Clear current weapon if it's being removed
        }
        delete *it; // Clean up the weapon
        weapons.erase(it); // Remove from the list
        if (weapons.empty()) {
            currentWeapon = nullptr; // Clear current weapon if no weapons left
        } else {
            // Update current weapon index if needed
            currentWeaponIndex = std::min(currentWeaponIndex, static_cast<int>(weapons.size()) - 1);
            currentWeapon = weapons[currentWeaponIndex];
        }
    }
}
Weapon* WeaponHolder::getCurrentWeapon() const {
    return currentWeapon;
}
void WeaponHolder::setCurrentWeapon(Weapon* weapon) {
    if (weapon) {
        currentWeapon = weapon;
        currentWeaponIndex = std::distance(weapons.begin(), std::find(weapons.begin(), weapons.end(), weapon));
    }
}

void WeaponHolder::update(sf::Time deltaTime) {
    if (currentWeapon) {
        currentWeapon->update(deltaTime);
    }
}

void WeaponHolder::draw(sf::RenderWindow& window, sf::RenderStates states) const {
    if(currentWeapon) {
        currentWeapon->draw(window, states);
    }
}

void WeaponHolder::handleEvent(const sf::Event& event) {
    if (currentWeapon) {
        currentWeapon->handleEvent(event);
    }
}
void WeaponHolder::switchToNextWeapon() {
    if (weapons.empty()) return;
    currentWeaponIndex = (currentWeaponIndex + 1) % weapons.size();
    currentWeapon = weapons[currentWeaponIndex];
}
void WeaponHolder::switchToPreviousWeapon() {
    if (weapons.empty()) return;
    currentWeaponIndex = (currentWeaponIndex - 1 + weapons.size()) % weapons.size();
    currentWeapon = weapons[currentWeaponIndex];
}
int WeaponHolder::getWeaponCount() const {
    return static_cast<int>(weapons.size());
}
