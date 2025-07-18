#include <Book/Inventory.hpp>

void Inventory::addWeapon(std::shared_ptr<Weapon2> weapon) {
    if (weapons.size() < MaxWeapon) {
        weapons.push_back(weapon);
    } else {
        std::cerr << "Inventory is full, cannot add more weapons." << std::endl;
    }
}


void Inventory::removeWeapon(std::shared_ptr<Weapon2> weapon) {
    auto it = std::find(weapons.begin(), weapons.end(), weapon);
    if (it != weapons.end()) {
        weapons.erase(it);
        CurrentWeaponIndex = std::max(0, CurrentWeaponIndex - 1); // Adjust index if necessary
    } else {
        std::cerr << "Weapon not found in inventory." << std::endl;
    }
}



void Inventory::activateWeapon(Entity* target) {
    if (CurrentWeaponIndex < weapons.size()) {
        weapons[CurrentWeaponIndex]->activate(target);
    } else {
        std::cerr << "No weapon is currently selected." << std::endl;
    }
}

void Inventory::activateSkill(Entity* user) {
    std::cerr << "Activating skill at index: " << CurrentSkillIndex << std::endl;
}

void Inventory::SwitchWeapon() {
    if (weapons.empty()) {
        std::cerr << "No weapons in inventory to switch." << std::endl;
        return;
    }
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % weapons.size();
    std::cerr << "Switched to weapon at index: " << CurrentWeaponIndex << std::endl;
}

std::shared_ptr<Weapon2> Inventory::getCurrentWeapon() const {
    if (CurrentWeaponIndex < weapons.size()) {
        return weapons[CurrentWeaponIndex];
    } else {
        std::cerr << "No current weapon available." << std::endl;
        return nullptr;
    }
}


void Inventory::update(sf::Time dt) {
    std::shared_ptr<Weapon2> currentWeapon = getCurrentWeapon();
    if (currentWeapon) {
        currentWeapon->update(dt);
    }
}

void Inventory::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    std::shared_ptr<Weapon2> currentWeapon = getCurrentWeapon();
    if (currentWeapon) {
        currentWeapon->draw(target, states);
    }
}

void Inventory::shoot(Entity* shooter, Entity* target) 
{
    std::shared_ptr<Weapon2> currentWeapon = getCurrentWeapon();
    if (currentWeapon) {
        currentWeapon->setStat("TargetPosX", target->getPosition().x);
        currentWeapon->setStat("TargetPosY", target->getPosition().y);
        
        currentWeapon->activate(shooter);
    } 
}

void Inventory::AimAt(sf::Vector2f position)
{
    std::shared_ptr<Weapon2> currentWeapon = getCurrentWeapon();
    if (currentWeapon) {
        currentWeapon->setStat("TargetPosX", position.x);
        currentWeapon->setStat("TargetPosY", position.y);
    } 
}