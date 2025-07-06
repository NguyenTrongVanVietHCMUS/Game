#include <Book/Inventory.hpp>

void Inventory::addWeapon(std::shared_ptr<Weapon2> weapon) {
    if (weapons.size() < MaxWeapon) {
        weapons.push_back(weapon);
    } else {
        std::cerr << "Inventory is full, cannot add more weapons." << std::endl;
    }
}

void Inventory::addSkill(std::shared_ptr<Skill> skill) {
    if (skills.size() < MaxSkill) {
        skills.push_back(skill);
    } else {
        std::cerr << "Inventory is full, cannot add more skills." << std::endl;
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

void Inventory::removeSkill(std::shared_ptr<Skill> skill) {
    auto it = std::find(skills.begin(), skills.end(), skill);
    if (it != skills.end()) {
        skills.erase(it);
        CurrentSkillIndex = std::max(0, CurrentSkillIndex - 1); // Adjust index if necessary
    } else {
        std::cerr << "Skill not found in inventory." << std::endl;
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

void Inventory::SwitchSkill() {
    if (skills.empty()) {
        std::cerr << "No skills in inventory to switch." << std::endl;
        return;
    }
    CurrentSkillIndex = (CurrentSkillIndex + 1) % skills.size();
    std::cerr << "Switched to skill at index: " << CurrentSkillIndex << std::endl;
}